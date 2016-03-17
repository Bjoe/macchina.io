#
# Makefile
#
# $Id$
#
# Makefile for Z-Wave Devices Bundle
#

BUNDLE_TOOL = $(POCO_BASE)/OSP/BundleCreator/$(POCO_HOST_BINDIR)/bundle

include $(POCO_BASE)/build/rules/global

INCLUDE += -I$(PROJECT_BASE)/devices/ZWay/include
INCLUDE += -I$(PROJECT_BASE)/protocols/Z-Wave/include
INCLUDE += -I$(PROJECT_BASE)/devices/Devices/include

SYSLIBS += -L$(PROJECT_BASE)/devices/ZWay/lib -lzway -lzcommons -lpthread -lxml2 -lz -lm -lcrypto -larchive

objects = BundleActivator ServiceHandler SwitchBinary Sensor Basic

target         = io.macchina.zwave.devices
target_version = 1
target_libs    = IoTDevices IoTZWave PocoRemotingNG PocoOSP PocoUtil PocoXML PocoFoundation

postbuild      = $(SET_LD_LIBRARY_PATH) $(BUNDLE_TOOL) -n$(OSNAME) -a$(OSARCH) -o../bundles Z-WaveDevices.bndlspec

include $(POCO_BASE)/build/rules/dylib

