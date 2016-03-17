#include "ZWayRequestHandler.h"

#include <sstream>

#include "Poco/Exception.h"
#include "Poco/Format.h"
#include "Poco/SharedPtr.h"

#include "Poco/JSON/Object.h"

#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"

#include "IoT/ZWave/Service.h"


namespace IoT {
namespace Web {
namespace ZWave {


ZWayRequestHandler::ZWayRequestHandler(Poco::OSP::BundleContext::Ptr bundleContext)
	: bundleContext_(bundleContext)
{
}

void ZWayRequestHandler::sendErrorResponse(
	Poco::Net::HTTPServerResponse& response,
	Poco::Net::HTTPResponse::HTTPStatus status)
{
	response.setStatusAndReason(status);
	response.setContentLength(0);
	response.setChunkedTransferEncoding(false);
	response.send();
}

void ZWayRequestHandler::handleRequest(
	Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response)
{
	bundleContext_->logger().information("Handle request");
	try
	{
		Poco::OSP::Web::WebSessionManager::Ptr webSessionManager =
			Poco::OSP::ServiceFinder::findByName<Poco::OSP::Web::WebSessionManager>(
					bundleContext_,
					Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
		Poco::OSP::Auth::AuthService::Ptr authService =	Poco::OSP::ServiceFinder::findByName<Poco::OSP::Auth::AuthService>(
				bundleContext_, "osp.auth");

		std::string appName = bundleContext_->thisBundle()->properties().getString("websession.id");
		Poco::OSP::Web::WebSession::Ptr webSession = webSessionManager->find(appName, request);
		if (!webSession.isNull() && webSession->has("username"))
		{
			std::string username = webSession->getValue<std::string>("username");
			if (authService->authorize(username, "bundleAdmin"))
			{
				response.setChunkedTransferEncoding(false);
				response.setContentType("application/json");

				Poco::SharedPtr<Poco::Net::HTMLForm> form =	new Poco::Net::HTMLForm();
				form->load(request, request.stream());

				if (form->has("command"))
				{
					std::string command = form->get("command");
					bundleContext_->logger().information(Poco::format("command %s", command));
					const IoT::Web::ZWave::Command::Handler::Ptr commandHandler = commandHandlers_.at(command);
					Poco::JSON::Object json = commandHandler->handle(bundleContext_, form);
					std::ostringstream os;
					json.stringify(os, 2);
					bundleContext_->logger().information(os.str());
					response.send() << os.str();
				}
				else
				{
					bundleContext_->logger().error("No command found");
					response.send() << "unhandle";
				}
			}
			else
			{
				bundleContext_->logger().error(Poco::format("Forbidden for username %s", username));
				sendErrorResponse(response, Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
			}
		}
		else
		{
			bundleContext_->logger().error("Web session or username not exist.");
			sendErrorResponse(response, Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
		}
	}
	catch (Poco::Exception& exception)
	{
		std::string errorText = exception.displayText();
		bundleContext_->logger().error(Poco::format("HTML form exception: %s", errorText));
		sendErrorResponse(response, Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
	}
}

Poco::Net::HTTPRequestHandler* ZWayRequestHandlerFactory::createRequestHandler(
		const Poco::Net::HTTPServerRequest& /*request*/)
{
	return new ZWayRequestHandler(context());
}


} } } // namespace IoT::Web::ZWave
