---
lang: it
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Presentazione
---

Lo scopo di questo progetto è creare un firmware alternativo per questa fotocamera: 

segno = _WIFI CARAM_  
modello: _WF-HD820-ZS_  
distinzione: _1080P_

Informazioni visualizzate nell'interfaccia Internet:
```
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

processore: _ingenic T21_
sensore video: _GC2053_

# Firmware alternativo

## Cosa funziona in un firmware alternativo:

* _LAN_   e   _WLAN_  


* Server   _RTSP_   Doppio flusso:   _1920x1080 H264_   e   _640x360 MJPEG_   per impostazione predefinita. . 


* Parametri visivi


* Server   _HTTP_  


* controllo motore


* taratura motore


* Impostazioni   _PTZ_  


* Cliente   _NTP_  


* Gestisci le password   _http_,   _rtsp_   e System. . 


* Controllo a LED bianco e IR  


* Controllo a LED bianco e IR   _ftp_ 


* Controllo a LED bianco e IR   _telnet_ 


* Server e client   _ssh_  


* rilevamento del movimento


* invio email


* Invio   _«telegram»_  


* Modalità notturna automatica  



## Ciò che non viene effettuato nel firmware alternativo:

* diffusione sonora


* _OSD_


* aggiornamento firmware


* rilevamento del movimento_ir-cut_


* invio email_mqtt_


* Immagini e video di spedizione nel cloud  


* ecc ...



## Installazione di firmware alternativo

* Copia tutto nella cartella [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) nella radice della scheda microSD.


* Forse impostare la rete ( _www/ipcam/config.dist/reto.conf_ )


* Inserire la scheda   _microSD_   nella fotocamera. . 


* Collega la videocamera alla rete locale e accendi la videocamera.


* Trova l'indirizzo IP della fotocamera. È anche possibile collegare anche alla fotocamera WiFi (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Collegare alla fotocamera da `telnet IP 9527` (Utente _root_, password _jco66688_), entro 5 minuti dopo aver rotante sulla fotocamera.


* Fare `killall -9 auto_run.sh` per evitare di perdere la lega.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* La fotocamera riavvia ora:  


    * È possibile collegare all'URL _https://IP_ (utente _admin_, password _ismart21_).


    * È possibile connettersi in Utente SSH ( _admin_, password _ismart12_).


    * La corrente video primaria è accessibile a  _rtsp://admin:ismart21@IP/stream1_. .


    * Il flusso video secondario è accessibile a  _rtsp://admin:ismart21@IP/stream2_. .


    *   La modalità AP WiFi è abilitata per impostazione predefinita:  
      **   SSID: IPCAM100-XXXXX  
      **   Tasto WPA2: ISMART21  
      **   Indirizzo IP della fotocamera: 172.25.0.1  

## Disinstallazione del firmware alternativo:

* Avviare il servizio SSH sulla fotocamera tramite l'interfaccia predefinita).


* Accedere alla fotocamera di `ssh root@IP` (password _ismart12_).


* avviare il servizio telnet con la telecamera tramite l'interfaccia Internet. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* Puoi anche rimuovere semplicemente la scheda microSD.



# Documenti interessanti

Molto lavoro è stato realizzato per le telecamere dotate di un processore   _ingenic T20_   
  *   Firmware modificato:   <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>  
  *   Fonti del firmware modificato:   <https://github.com/Dafang-Hacks/Main>  
  *   Altro firmware:   <https://github.com/openmiko/openmiko>  
  *   Avvia i programmi senza modificare il firmware:   <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic-T20-P2P-camera-hacks>  

