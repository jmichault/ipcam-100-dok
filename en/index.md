---
lang: en
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Presentation
---

The goal of this project is to create an alternative firmware for this camera:

mark = _WIFI CARAM_  
model: _WF-HD820-ZS_  
distinction: _1080P_

Information displayed in the Internet interface:
```
DeviceName: _INGENIC-V01_
DeviceModel: _IPCAM-100_
DeviceSN: _12345678901_
KernelVersion: _Thu Jul 9 15:46:54 CST 2015_
ServerVersion: _WS3.53.1243-20190717-DANALE-GEN_
WebVersion: _V2.3.4-20190709_
```

processor: _ingenic T21_
video sensor: _GC2053_

A lot of work has been done for cameras equipped with a processor _ingenic T20_.
* modified firmware: <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>
* sources from modified firmware: <https://github.com/Dafang-Hacks/Main>
* other firmware <https://github.com / openmiko / openmiko>
* launching programs without changing the firmware: <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic- T20 -P2P camera hacks>

API documentation can be viewed here:  
* [original version in Chinese](../zh/includes.zh/html/)


* [French version translated by google](../fr/includes.fr/html/)


* [English version translated by google](../en/includes.en/html/)



# Alternative firmware

## What Works in Alternative Firmware:

* LAN and WLAN


* RTSP-double-fluid server: 1280x720 H264 and 640x360 MJPEG (° 1 ° 1


* HTTP server


* engine control


* engine calibration


* PTZ settings


* NTP client


* password change for http access


* blue LED and IR control


* Ftp server


* Telnet server


* SSH server and client



## What doesn't work in alternative firmware:

* Visual parameters


* sound system


* _OSD_


* firmware update


* automatic night detection


* motion detection


* motion detection_ir-cut_


* sending email


* sending email_mqtt_


* etc ...



## Camera preparation

* Connect the camera to your local network and turn on the camera.


* Find the IP address of the camera.


* Connect to the camera with URL _"http://IP"_ (user _admin_, password _admin_)


* in the tab "Audio and video", set the main stream to 720p, click "Save".


* you may be able to set the cable network in the tab "Network".



## Installing Alternative Firmware

* Copy everything to the [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) folder at the root of the microSD card.


* optionally configure the network ( _config/staticip.conf_ , _config/resolv.conf_ , _config/wpa_supplicant.conf_ )


* Insert the microSD card.


* Connect the camera to your local network and turn on the camera.


* Log in to the camera with `telnet IP 9527` (user _root_, password _jco66688_).


* Press `killall -9 auto_run.sh` to avoid closing the connection.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* You can connect to the URL _"https://IP"_ (user _admin_, password _jco66688_).



## Uninstalling Alternative Firmware:

* start the telnet service with the camera via the internet interface.


* start the telnet service with the camera via the internet interface. `telnet IP` 


* start the telnet service with the camera via the internet interface. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* You can also simply remove the microSD card.


