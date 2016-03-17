macchina.io
===========

*An open-source toolkit for building embedded IoT applications that connect sensors, devices and cloud services.*
						
macchina.io is a new open source software toolkit for quickly building
embedded applications for the Internet of Things that run on Linux-based
devices like the Raspberry Pi, Beaglebone or RED brick. macchina.io
implements a web-enabled, modular and extensible JavaScript and C++
runtime environment and provides readily available, easy to use building
blocks that allow your application to talk to various sensors and
devices, as well as cloud services.

macchina.io is based on the [POCO C++ Libraries](http://pocoproject.org) and
uses the [V8 JavaScript engine](https://code.google.com/p/v8/).

For more information, including documentation, please see the 
[macchina.io website](http://macchina.io) or see original repo
[macchina.io github](https://github.com/macchina-io/macchina.io)


Z-Wave (ALPHA) support
-----------------------

Following OSGi bundles implements Z-Wave support: 
 * io.macchina.zway
 * io.macchina.zwave
 * io.macchina.zwave.devices
 * io.macchina.webui.zwave
 
The Z-Wave protocol is implemented in io.macchina.zwave. At the moment there
are only following Z-Wave command classes are implemented:
 * Basic command class (default for all Z-Wave nodes)
 * Meter command class (for sensor devices)
 * SwitchBinary command class
 
To use Z-Wave, a controller and thirdparty Libraries are needed. 
The OSGi bundle io.macchina.zway has support for Z-Way Z-Wave Controller 
from [Z-Wave.me](http://www.zwave.me). See:
 * [RaZberry - for Raspberry PI platform](http://razberry.z-wave.me/)
 * [UZBWAY - USB Stick](http://www.zwave.me/index.php?id=28)

Download the latest tarball from [Z-Wave.me](http://razberry.zwave.me/z-way-server/)
Extract the tarball.
Copy following files and directories from z-way-server/ folder to macchina.io/:
- z-way-server/libs/libxml2.so*    -> macchina.io/devices/ZWay/lib
- z-way-server/libs/libzcommons.so -> macchina.io/devices/ZWay/lib
- z-way-server/libs/libzway.so     -> macchina.io/devices/ZWay/lib
- z-way-server/libzway/*.h         -> macchina.io/devices/ZWay/include/
- z-way-server/ZDDX                -> macchina.io/server/zwave/ZDDX
- z-way-server/translations        -> macchina.io/server/zwave/translations
- z-way-server/config              -> macchina.io/server/zwave/config

See also in macchina.io/devices/ZWay/README.

This version is a proof of concept and not yet ready.

