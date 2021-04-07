---
lang: eo
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Prezento
---

La celo de ĉi tiu projekto estas krei alternativan firmvaron por ĉi tiu fotilo:

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

Multa laboro estis farita por fotiloj ekipitaj kun procesoro _ingenic T20_.
* modifita firmvaro: <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>
* fontoj de modifita firmvaro: <https://github.com/Dafang-Hacks/Main>
* alia firmvaro <https://github.com / openmiko / openmiko>
* lanĉante programojn sen ŝanĝi la firmvaron: <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic- T20 -P2P-fotilo-hakoj>

API-dokumentaro videblas ĉi tie:  
* [originala versio en la ĉina](../zh/includes.zh/html/)

* [Angla versio](../en/includes.en/html/)

* [Franca versio tradukita de google](../fr/includes.fr/html/)


# Alternativa firmvaro

## Kio Funkcias en Alternativa Firmware:

* LAN kaj WLAN

* RTSP-duobla-flua servilo: 1280x720 H264 kaj 640x360 MJpeg

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


## Kio ne funkcias en alternativa firmvaro:

* Vidaj parametroj

* sondosistemo

* _OSD_

* ĝisdatigo de firmvaro

* aŭtomata nokta detekto

* movado-detekto

* movado-detekto_ir-cut_

* sendante retpoŝton

* sendante retpoŝton_mqtt_

* ktp ...


## Kamera preparado

* Konekti la fotilon al via loka reto kaj ŝalti la fotilon.

* Trovu la IP-adreson de la fotilo.

* Konekti al la fotilo per URL _"http://IP"_ (uzanto _admin_, pasvorto _admin_)

* en la langeto "Aŭdio kaj video", agordu la ĉefan rivereton al 720p, alklaku "Konservu".

* eble agordu la kablan reton en la langeto "Reto".


## Instalante Alternativan Firmware

* Kopiu ĉion en la dosierujo [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) ĉe la radiko de la karto microSD.

* laŭvole agordi la reton ( _config/staticip.conf_ , _config/resolv.conf_ , _config/wpa_supplicant.conf_ )

* Enmetu la karton microSD.

* Konekti la fotilon al via loka reto kaj ŝalti la fotilon.

* Ensalutu ĉe la fotilo per `telnet IP 9527` (uzanto _root_, pasvorto _jco66688_).

* Premu `killall -9 auto_run.sh` por eviti fermi la konekton.

* Faru `cd /opt/media/mmcblk0p1;./install.sh`

* Vi povas konekti al la URL _"https://IP"_ (uzanto _admin_, pasvorto _jco66688_).


## Malinstalanta Alternativan Firmware:

* komencu la telnet-servon per la fotilo per la interreta interfaco.

* komencu la telnet-servon per la fotilo per la interreta interfaco. `telnet IP` 

* komencu la telnet-servon per la fotilo per la interreta interfaco. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`


* Vi ankaŭ povas simple forigi la karton microSD.

