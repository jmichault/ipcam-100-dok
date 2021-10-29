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
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

procesoro: _ingenic T21_
videosensilo: _GC2053_

# Alternativa firmvaro

## Kio Funkcias en Alternativa Firmware:

* _LAN_ kaj _WLAN_

* Servilo (° 1 ° duobla-fluo: _1920x1080 H264_ kaj _640x360 MJPEG_ defaŭlte. 

* Vidaj parametroj

* Servilo _HTTP_

* motora kontrolo

* motora kalibrado

* Parametroj _PTZ_

* Kliento _NTP_

* Pasvorta administrado _http_, _rtsp_ kaj sistemo. 

* Blanka LED-Kontrolo kaj IR

* Blanka LED-Kontrolo kaj IR _ftp_

* Blanka LED-Kontrolo kaj IR _telnet_

* Servilo kaj kliento _ssh_

* movado-detekto

* sendante retpoŝton

* Sendi _«telegram»_

* Aŭtomata nokta reĝimo


## Kio ne estas efektivigita en la alternativa firmware:

* sondosistemo

* _OSD_

* ĝisdatigo de firmvaro

* movado-detekto_ir-cut_

* sendante retpoŝton_mqtt_

* Sendante bildojn kaj videojn en nubo

* ktp ...


## Instalante Alternativan Firmware

* Kopiu ĉion en la dosierujo [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) ĉe la radiko de la karto microSD.

* Eble agordi la reton ( _www/ipcam/config.dist/reto.conf_ )

* Enmetu la karton _microSD_ en la fotilon. 

* Konekti la fotilon al via loka reto kaj ŝalti la fotilon.

* Trovu la IP-adreson de la fotilo. Vi ankaŭ povas konektiĝi al la WiFi de la fotilo (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.

* Konekti al la fotilo per `telnet IP 9527` (uzanto _root_, pasvorto _jco66688_), ene de 5 minutoj post turnado sur la fotilo.

* Faru `killall -9 auto_run.sh` por eviti perdi la ligon.

* Faru `cd /opt/media/mmcblk0p1;./install.sh`

* La fotilo rekomencas, nun:

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


# Interesaj dokumentoj

Multa laboro estis farita por fotiloj ekipitaj per procesoro _ingenic T20_ :
* modifita firmware: <https://github.com/eliaskotlyar/xiaomi- dafang -Hacks>
* Fontoj de la modifita firmware: <https://github.com/dafang-hacks/main>
17 °) https://github.com/thatusenameAlreadyExist/Jco-pm203-fisheye-ingenic-t20-p2p-camera-hacks>

