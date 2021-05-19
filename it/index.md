---
lang: it
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Presentazione
---

L'obiettivo di questo progetto è creare un firmware alternativo per questa fotocamera:

segno = _WIFI CARAM_  
modello: _WF-HD820-ZS_  
distinzione: _1080P_

Informazioni visualizzate nell'interfaccia Internet:
```
DeviceName: _INGENIC-V01_
DeviceModel: _IPCAM-100_
DeviceSN: _12345678901_
KernelVersion: _Thu Jul 9 15:46:54 CST 2015_
ServerVersion: _WS3.53.1243-20190717-DANALE-GEN_
WebVersion: _V2.3.4-20190709_
```

processore: _ingenic T21_
sensore video: _GC2053_

Molto lavoro è stato fatto per le telecamere dotate di processore _ingenic T20_.
* firmware modificato: <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>
* fonti da firmware modificato: <https://github.com/Dafang-Hacks/Main>
* altro firmware <https://github.com / openmiko / openmiko>
* avvio di programmi senza modificare il firmware: <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic- T20 -Hack fotocamera P2P>

La documentazione API può essere visualizzata qui:  
* [versione originale in cinese](../zh/includes.zh/html/)


* [Versione inglese](../en/includes.en/html/)


* [Versione francese tradotta da google](../fr/includes.fr/html/)



# Firmware alternativo

## Cosa funziona in un firmware alternativo:

* LAN e WLAN


* DRTTSP Dual Flow Flow Server: 1920x1080 H264 e 640x360 MJPEG per impostazione predefinita.


* Parametri visivi


* Server HTTP


* controllo motore


* taratura motore


* Impostazioni PTZ


* Cliente NTP


* cambio password per accesso http


* LED blu e controllo IR


* Server ftp


* Server Telnet


* Server ssh e client


* rilevamento del movimento


* invio email



## Cosa non funziona nel firmware alternativo:

* diffusione sonora


* _OSD_


* Gestione della password.


* aggiornamento firmware


* rilevamento notturno automatico


* rilevamento del movimento_ir-cut_


* invio email_mqtt_


* ecc ...



## Preparazione della fotocamera

* Collega la videocamera alla rete locale e accendi la videocamera.


* Trova l'indirizzo IP della telecamera.


* Connessione alla telecamera tramite URL _"http://IP"_ (utente _admin_, password _admin_)


* nella scheda "Audio e video", impostare lo stream principale a 720p, fare clic su "Salva".


* potresti essere in grado di impostare la rete via cavo nella scheda "Rete".



## Installazione di firmware alternativo

* Copia tutto nella cartella [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) nella radice della scheda microSD.


* opzionalmente configurare la rete ( _config/staticip.conf_ , _config/resolv.conf_ , _config/wpa_supplicant.conf_ )


* Inserisci la scheda microSD.


* Collega la videocamera alla rete locale e accendi la videocamera.


* Collegare alla fotocamera da `telnet IP 9527` (Utente _root_, password _jco66688_), entro 5 minuti dopo aver rotante sulla fotocamera.


* Fare `killall -9 auto_run.sh` per evitare di perdere la lega.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* È possibile collegare all'URL (° 1 ° utente( _admin_, password _ismart21_).


* È possibile collegarsi all'utente SSH ( _admin_, password _ismart12_).


* La corrente video primaria è accessibile a _rtsp://admin:ismart21@IP/stream1_. (° 3 ° 3


* La corrente video secondaria è accessibile a _rtsp://admin:ismart21@IP/stream2_. (° 3 ° 3



## Disinstallazione del firmware alternativo:

* avviare il servizio telnet con la telecamera tramite l'interfaccia Internet.


* avviare il servizio telnet con la telecamera tramite l'interfaccia Internet. `telnet IP` 


* avviare il servizio telnet con la telecamera tramite l'interfaccia Internet. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* Puoi anche rimuovere semplicemente la scheda microSD.


