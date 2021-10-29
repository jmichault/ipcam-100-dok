---
lang: en
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Presentation
---

The purpose of this project is to create alternative firmware for this camera: (° 1 ° 1

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

API documentation can be viewed here:  
* [original version in Chinese](../zh/includes.zh/html/)


* [English version](../en/includes.en/html/)


* [French version translated by google](../fr/includes.fr/html/)



# Alternative firmware

## What Works in Alternative Firmware:

* LAN and WLAN


* DRTTSP Dual Flow Server: 1920x1080 H264 and 640x360 MJPEG by default.


* Visual parameters


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


* motion detection


* sending email



## What is not carried out in the alternative firmware:

* sound system


* _OSD_


* Administration management and RTSP system.


* firmware update


* automatic night detection


* motion detection_ir-cut_


* sending email_mqtt_


* etc ...



## Installing Alternative Firmware

* Copy everything to the [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) folder at the root of the microSD card.


* Perhaps set the network ( _www/ipcam/config.dist/reto.conf_ )


* Insert the microSD card.


* Connect the camera to your local network and turn on the camera.


* Find the camera's IP address. You can also connect to the camera wifi (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Connect to the camera by `telnet IP 9527` (User _root_, Password _jco66688_), within 5 minutes after rotating on the camera.


* Make `killall -9 auto_run.sh` to avoid losing the league.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* You can connect to the URL _https://IP_ (user _admin_, password _ismart21_).


* You can connect in SSH (user _admin_, password _ismart12_).


* The primary video current is accessible at _rtsp://admin:ismart21@IP/stream1_. (° 3 ° 3


* The secondary video current is accessible at _rtsp://admin:ismart21@IP/stream2_. (° 3 ° 3


(° 1 ° 1 ° 1 WiFi AP mode is activated by default:
** SSID: ipcam100-xxxxxx
** WPA2 key: ismart21 (° 6 ° 6 ° 6

## Uninstalling Alternative Firmware:

* Launch the SSH service on the camera through the default interface).


* Login to the camera by `ssh root@IP` (Password _ismart12_).


* start the telnet service with the camera via the internet interface. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* You can also simply remove the microSD card.



# Interesting documents

Much work was made for cameras equipped with a processor _ingenic T20_ :
* modified firmware: <https://github.com/Ilílístotlyar/xiaomi- Dafang -Haks (°

