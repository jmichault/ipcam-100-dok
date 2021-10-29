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
DeviceName: _INGENIC-V01_
DeviceModel: _IPCAM-100_
DeviceSN: _12345678901_
KernelVersion: _Thu Jul 9 15:46:54 CST 2015_
ServerVersion: _WS3.53.1243-20190717-DANALE-GEN_
WebVersion: _V2.3.4-20190709_
```

Prozessor: _ingenic T21_
Videosensor: _GC2053_

Die API-Dokumentation kann hier eingesehen werden:  
* [Originalversion in Chinesisch](../zh/includes.zh/html/)


* [Englische Version](../en/includes.en/html/)


* [Französische Version übersetzt von Google](../fr/includes.fr/html/)



# Alternative Firmware

## Was funktioniert in alternativer Firmware:

* LAN und WLAN


* DRTTSP Dual Flow Server: 1920x1080 H264 und 640x360 MJPEG standardmäßig.


* Visuelle Parameter


* HTTP-Server


* Motorsteuerung


* Motorkalibrierung


* PTZ-Einstellungen


* NTP-Client


* Passwortänderung für http-Zugang


* blaue LED und IR-Steuerung


* FTP-Server


* Telnet-Server


* SSH-Server und Client


* Bewegungserkennung


* E-Mail senden



## Was wird nicht in der alternativen Firmware durchgeführt:

* Soundsystem


* _OSD_


* Verwaltungsmanagement und RTSP-System.


* Firmware-Update


* automatische Nachterkennung


* Bewegungserkennung_ir-cut_


* E-Mail senden_mqtt_


* etc ...



## Alternative Firmware installieren

* Kopieren Sie alles in den Ordner [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) im Stammverzeichnis der microSD-Karte.


* Stellen Sie vielleicht das Netzwerk ( _www/ipcam/config.dist/reto.conf_ )einstellen


* Legen Sie die microSD-Karte ein.


* Schließen Sie die Kamera an Ihr lokales Netzwerk an und schalten Sie die Kamera ein.


* Finden Sie die IP-Adresse der Kamera. Sie können auch eine Verbindung zur Kamera-WiFi (SSID herstellen: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Verbinden Sie sich mit der Kamera mit `telnet IP 9527`  _root_ _root_, Passwort _jco66688_), innerhalb von 5 Minuten nach dem Drehen der Kamera.


* Verdienen `killall -9 auto_run.sh` , um die Liga zu vermeiden.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* Sie können eine Verbindung mit der URL _https://IP_ (benutzer _admin_verbinden, Passwort _ismart21_).


* Sie können in SSH (Benutzer _admin_, Passwort _ismart12_)verbinden.


* Der primäre Videostrom ist bei _rtsp://admin:ismart21@IP/stream1_erreichbar. (° 3 ° 3


* Der sekundäre Videostrom ist bei _rtsp://admin:ismart21@IP/stream2_erreichbar. (° 3 ° 3


(° 1 ° 1 ° 1 WiFi AP-Modus wird standardmäßig aktiviert:
** SSID: IPCAM100-XXXXXX
** WPA2-Taste: ismart21
IP-Adresse der Kamera: 172.25.0.1

## Alternative Firmware deinstallieren:

* Starten Sie den SSH-Dienst in der Kamera über die Standardschnittstelle).


* Melden Sie sich bei der Kamera mit `ssh root@IP` ( _ismart12_)an.


* Starten Sie den Telnet-Dienst mit der Kamera über die Internetschnittstelle. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* Sie können die microSD-Karte auch einfach entfernen.



# Interessante Dokumente

Es wurde viel Arbeit für Kameras hergestellt, die mit einem Prozessor ausgestattet sind _ingenic T20_ :
* modifizierte Firmware: <https://github.com/ilílístoTlyar/xiaomi- Dafang -Haks>
Quellen der modifizierten Firmware: <https://github.com/dafang-hacks/main>
Andere Firmware <https://github.com/openmiko/openmiko>
* Einführung von Programmen ohne Änderung der Firmware: (° 17 ° 17 ° 17: // https://github.com/thatusenameAnamaExist/jco-pm203-fisheye-inenen-t20-p2P-Camera-Hacks>

