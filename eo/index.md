---
lang: eo
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Prezento
---

La celo de ĉi tiu projekto estas krei alternativan firmvaron por ĉi tiu kamerao:

marko = _WIFI CARAM_  
modelo: _WF-HD820-ZS_  
distingivo: _1080P_

Informoj montrataj en la interreta interfaco:
```
DeviceName: _INGENIC-V01_
DeviceModel: _IPCAM-100_
DeviceSN: _12345678901_
KernelVersion: _Thu Jul 9 15:46:54 CST 2015_
ServerVersion: _WS3.53.1243-20190717-DANALE-GEN_
WebVersion: _V2.3.4-20190709_
```

procesoro: _ingenic T21_
videosensilo: _GC2053_

API-dokumentaro videblas ĉi tie:  
* [originala versio en la ĉina](../zh/includes.zh/html/)

* [Angla versio](../en/includes.en/html/)

* [Franca versio tradukita de google](../fr/includes.fr/html/)


# Alternativa firmvaro

## Kio Funkcias en Alternativa Firmware:

* LAN kaj WLAN

* DRTSP Dual Flow Server: 1920x1080 H264 kaj 640x360 MJpeg defaŭlte.

* Vidaj parametroj

* HTTP-servilo

* motora kontrolo

* motora kalibrado

* Agordoj de PTZ

* NTP-kliento

* pasvorta ŝanĝo por http-aliro

* blua LED kaj IR-kontrolo

* Ftp-servilo

* Telnet-servilo

* SSH-servilo kaj kliento

* movado-detekto

* sendante retpoŝton


## Kio ne estas efektivigita en la alternativa firmware:

* sondosistemo

* _OSD_

* Administrado de Pasvortoj kaj Sistemo de RTSP.

* ĝisdatigo de firmvaro

* aŭtomata nokta detekto

* movado-detekto_ir-cut_

* sendante retpoŝton_mqtt_

* ktp ...


## Instalante Alternativan Firmware

* Kopiu ĉion en la dosierujo [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) ĉe la radiko de la karto microSD.

* Eble agordi la reton ( _www/ipcam/config.dist/reto.conf_ )

* Enmetu la karton microSD.

* Konekti la fotilon al via loka reto kaj ŝalti la fotilon.

* Trovu la IP-adreson de la fotilo. Vi ankaŭ povas konektiĝi al la WiFi de la fotilo (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.

* Konekti al la fotilo per `telnet IP 9527` (uzanto _root_, pasvorto _jco66688_), ene de 5 minutoj post turnado sur la fotilo.

* Faru `killall -9 auto_run.sh` por eviti perdi la ligon.

* Faru `cd /opt/media/mmcblk0p1;./install.sh`

* Vi povas konektiĝi al la URL _https://IP_ (uzanto _admin_, pasvorto _ismart21_).

* Vi povas konektiĝi en SSH (uzanto _admin_, pasvorto _ismart12_).

* La primara video-fluo estas alirebla ĉe _rtsp://admin:ismart21@IP/stream1_.

* La sekundara video-fluo estas alirebla ĉe _rtsp://admin:ismart21@IP/stream2_.

(° 1 ° WiFi AP-reĝimo estas aktivigita defaŭlte:
** SSID: IPCAM100-XXXXXX
** WPA2-ŝlosilo: ismart21
IP-adreso de la fotilo: 172.25.0.1

## Malinstalanta Alternativan Firmware:

* Lanĉu la servon SSH sur la fotilo tra la defaŭlta interfaco).

* Ensalutu al la fotilo per `ssh root@IP` (pasvorto _ismart12_).

* komencu la telnet-servon per la fotilo per la interreta interfaco. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`


* Vi ankaŭ povas simple forigi la karton microSD.


## Interesaj dokumentoj

Multa laboro estis farita por fotiloj ekipitaj per procesoro _ingenic T20_ :
* modifita firmware: <https://github.com/eliaskotlyar/xiaomi- dafang -Hacks>
* Fontoj de la modifita firmware: <https://github.com/dafang-hacks/main>
* Aliaj firmware <https://github.com/openmiko/openmiko>
* lanĉo de programoj sen ŝanĝi la firmware: (° 17 ° Https://github.com/thatusenameAlreadyExist/jco-pm203-fisheye-ingenic-t20-p2p-camera-hacks>

