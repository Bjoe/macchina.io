#
# Makefile
#
# $Id: //poco/1.4/Net/samples/TimeServer/Makefile#1 $
#
# Makefile for Poco TimeServer
#

include $(POCO_BASE)/build/rules/global

objects = TimeServer

target         = TimeServer
target_version = 1
target_libs    = PocoUtil PocoJSON PocoNet PocoXML PocoFoundation

include $(POCO_BASE)/build/rules/exec

ifdef POCO_UNBUNDLED
        SYSLIBS += -lz -lpcre -lexpat
endif
