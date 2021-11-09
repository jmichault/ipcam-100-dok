---
lang: de
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Präsentation
---

Der Zweck dieses Projekts besteht darin, alternative Firmware für diese Kamera zu erstellen:

Markierung = _WIFI CARAM_  
Modell: _WF-HD820-ZS_  
Unterscheidung: _1080P_

In der Internetschnittstelle angezeigte Informationen:
```
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

Prozessor: _ingenic T21_
Videosensor: _GC2053_

# Alternative Firmware

## Was funktioniert in alternativer Firmware:

* _LAN_   und   _WLAN_  


* Server   _RTSP_   Doppelstrom:   _1920x1080 H264_   und   _640x360 MJPEG_   standardmäßig.  


* Visuelle Parameter


* Server   _HTTP_  


* Motorsteuerung


* Motorkalibrierung


* Einstellungen   _PTZ_  


* Client   _NTP_  


* Verwalten Sie Kennwörter   _http_,   _rtsp_   und -system.  


* Weiße LED-Steuerung und IR  


* Weiße LED-Steuerung und IR   _ftp_ 


* Weiße LED-Steuerung und IR   _telnet_ 


* Server und Client   _ssh_  


* Bewegungserkennung


* E-Mail senden


* Senden   _«telegram»_  


* Automatischer Nachtmodus  



## Was wird nicht in der alternativen Firmware durchgeführt:

* Soundsystem


* _OSD_


* Firmware-Update


* Bewegungserkennung_ir-cut_


* E-Mail senden_mqtt_


* Sendungsbilder und Videos in der Cloud  


* etc ...



## Alternative Firmware installieren

* Kopieren Sie alles in den Ordner [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) im Stammverzeichnis der microSD-Karte.


* Stellen Sie vielleicht das Netzwerk ( _www/ipcam/config.dist/reto.conf_ )einstellen


* Legen Sie die Karte   _microSD_   in die Kamera ein.  


* Schließen Sie die Kamera an Ihr lokales Netzwerk an und schalten Sie die Kamera ein.


* Finden Sie die IP-Adresse der Kamera. Sie können auch eine Verbindung zur Kamera-WiFi (SSID herstellen: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Verbinden Sie sich mit der Kamera mit `telnet IP 9527`  _root_ _root_, Passwort _jco66688_), innerhalb von 5 Minuten nach dem Drehen der Kamera.


* Verdienen `killall -9 auto_run.sh` , um die Liga zu vermeiden.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* Die Neustarts-Kamera jetzt:  


    * Sie können eine Verbindung mit der URL _https://IP_ (benutzer _admin_verbinden, Passwort _ismart21_).


    * Sie können in SSH (Benutzer _admin_, Passwort _ismart12_)verbinden.


    * Der primäre Videostrom ist bei  _rtsp://admin:ismart21@IP/stream1_ zugänglich. 


    * Der sekundäre Videostrom ist bei  _rtsp://admin:ismart21@IP/stream2_ zugänglich. 


    *   WiFi AP-Modus ist standardmäßig aktiviert:  
      **   SSID: IPCAM100-XXXXX  
      **   WPA2-Taste: ISMART21  
      **   IP-Adresse der Kamera: 172.25.0.1  

## Alternative Firmware deinstallieren:

* Starten Sie den SSH-Dienst in der Kamera über die Standardschnittstelle).


* Melden Sie sich bei der Kamera mit `ssh root@IP` ( _ismart12_)an.


* Starten Sie den Telnet-Dienst mit der Kamera über die Internetschnittstelle. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* Sie können die microSD-Karte auch einfach entfernen.



# Interessante Dokumente

Für Kameras wurde viel Arbeit gemacht, die mit einem Prozessor-Firmware mit Prozessor   _ingenic T20_   
  *   ausgestattet sind:   <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>  
  *   Quellen der modifizierten Firmware:   <https://github.com/Dafang-Hacks/Main>  
  *   Andere Firmware:   <https://github.com/openmiko/openmiko>  
  *   Startprogramme ohne Änderung der Firmware:   <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic-T20-P2P-camera-hacks>  

