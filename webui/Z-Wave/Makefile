#
# Makefile
#
# $Id$
#
# Makefile for macchina.io zwave web ui
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle
PAGECOMPILER = $(POCO_BASE)/PageCompiler/$(POCO_HOST_BINDIR)/cpspc

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/devices/ZWay/include -I$(PROJECT_BASE)/protocols/Z-Wave/include

objects =  \
    BundleActivator \
    ZWayRequestHandler \
    Handler \
    Inclusion \
    Exclusion \
    ShowNodes \
    ServiceState \
    ResetController

target         = io.macchina.webui.zwave
target_version = 1
target_libs    = IoTZWave PocoOSPWeb PocoOSP PocoNet PocoUtil PocoJSON PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -Npng,gif,jpg -o../bundles Z-WaveWebUi.bndlspec

include $(POCO_BASE)/build/rules/dylib

# Rule for runnning PageCompiler
src/%.cpp: src/%.cpsp 
	@echo "** Compiling Page" $<
	$(PAGECOMPILER) --OSP $<
