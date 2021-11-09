---
lang: it
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'Descrizione della fotocamera'
---



# Descrizione:
<https://fr.aliexpress.com/item/4000146161270.html>  
```
    Brand Name: shiningpo
    Style: Dome Camera
    Type: IP Camera
    Connectivity: IP/Network Wireless
    Supported Operating Systems: No
    High Definition: 1080P(Full-HD)
    Lens (mm): 3.6mm
    Installation: Side
    Power Supply(V): DC12V 2A
    Network Interface: RJ-45 10/100Mb Ethernet Slot
    Wall Bracket: Ceiling
    Supported Mobile Systems: Android
    Supported Mobile Systems: ios
    IR Distance(m): 30M-50M
    Special Features: Waterproof / Weatherproof
    Viewing Angle : 140°
    Megapixels: 2MP
    Power Consumption(W): 12W
    Storage: None
    Sensor Brand: SONY
    Alarm Action: Email Photo
    Alarm Action: Local Alarm
    Video Compression Format: H.264
    is_customized: Yes
    Technology: Pan Tilt Zoom
    Power Supply: Normal
    TF Card: None
    Color: White
    Audio Output: Two Way Audio
    Sensor: CMOS
    wifi camera: ip camera
    camara wifi: camara ip
    camera ip: camera wifi
    ip camera wifi: camara vigilancia exterior
    ptz: camara ip ptz
```

# Iscrizioni del tag
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

Collegamento della telecamera di rete Etorn, riceve un indirizzo IP e è possibile connettersi ad esso all'indirizzo http:    
 Utente predefinito:   _admin_    
 Password predefinita:   _admin_  

Per 5 minuti, possiamo connetterci con   _telnet_   alla porta 9527:    
 Utente predefinito:   _root  
  
  
Password predefinita:   _jco66688  
  
  
Per rimanere connesso dopo questi 5 minuti:   `killall -9 auto_run.sh`      
  _(  jco = http://www.cnjabsco.com/   )    _



Apri porte:    
   _tcp_ : 80  (_  HTTP  _), 443  (_  HTTP  _  !      


Stop   _jco_  server  _   senza causare il riavvio:    
```
PS | 
```

Il canale principale può essere rappresentato da:    
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

e secondario:    
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

Le informazioni visualizzate nell'interfaccia online:    
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

Il processore è:   _ingenic T21_  
  < http://www.ininic.com.cn/it/?product/id/11.html >    
 Il processore è:  < https: //fr.indasina.com/ingeric-t21-xtreme-2-megapixel-ecoding- Processore _p16.html>     


Il sensore   _CMOS_   è:   _gc2053_. 

Memoria   _RAM_ :   _42 MiB_   Totale,   _36 MiB_   utilizzabile.    

L'avena del 9999 consente di controllare la fotocamera:    
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

Porte   _GPIO_ :    
 46 = LED a infrarossi.  

GPIO-HADEN BLOCCATO PER URGINGING:  
Bloccato da Motor.Ko: 18?   

Controlli   _PTZ_ :    

TOP:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
 Fondo:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_    
 SINISTRA:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_    
 DESTRA:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_    
 STOP:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_    
 POSIZIONE 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
 Posizione 1:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
 Posizione chiara 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

