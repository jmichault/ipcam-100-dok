---
lang: it
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Presentazione
---

Lo scopo di questo progetto è creare firmware alternativo per questa fotocamera: (° 1 ° 1

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



## Ciò che non viene effettuato nel firmware alternativo:

* diffusione sonora


* _OSD_


* Gestione amministrativa e sistema RTSP.


* aggiornamento firmware


* rilevamento notturno automatico


* rilevamento del movimento_ir-cut_


* invio email_mqtt_


* ecc ...



## Installazione di firmware alternativo

* Copia tutto nella cartella [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) nella radice della scheda microSD.


* Forse impostare la rete ( _www/ipcam/config.dist/reto.conf_ )


* Inserisci la scheda microSD.


* Collega la videocamera alla rete locale e accendi la videocamera.


* Trova l'indirizzo IP della fotocamera. È anche possibile collegare anche alla fotocamera WiFi (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Collegare alla fotocamera da `telnet IP 9527` (Utente _root_, password _jco66688_), entro 5 minuti dopo aver rotante sulla fotocamera.


* Fare `killall -9 auto_run.sh` per evitare di perdere la lega.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* È possibile collegare all'URL _https://IP_ (utente _admin_, password _ismart21_).


* È possibile connettersi in Utente SSH ( _admin_, password _ismart12_).


* La corrente video primaria è accessibile a _rtsp://admin:ismart21@IP/stream1_. (° 3 ° 3


* La corrente video secondaria è accessibile a _rtsp://admin:ismart21@IP/stream2_. (° 3 ° 3


(° 1 ° 1 ° 1 WiFi Modalità AP è attivata per impostazione predefinita:
** SSID: IPCAM100-XXXXXX
** Chiave WPA2: ISMART21
Indirizzo IP della fotocamera: 172.25.0.1

## Disinstallazione del firmware alternativo:

* Avviare il servizio SSH sulla fotocamera tramite l'interfaccia predefinita).


* Accedere alla fotocamera di `ssh root@IP` (password _ismart12_).


* avviare il servizio telnet con la telecamera tramite l'interfaccia Internet. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* Puoi anche rimuovere semplicemente la scheda microSD.



# Documenti interessanti

Molto lavoro è stato realizzato per telecamere dotato di un processore _ingenic T20_ :
* Firmware modificato: <https://github.com/ilílístotlyar/xiaomi- Dafang -Haks>
Fonti del firmware modificato: <https://github.com/dafang-hacks/main>>
Altro firmware <https://github.com/openmiko/openmiko>
* Avvio dei programmi senza modificare il firmware: (° 17 ° 17 ° 17: // https://github.com/thatusenameanameexist/jco-pm203-fiseye-ingenic-t20-P2P-camera-Hacks>

