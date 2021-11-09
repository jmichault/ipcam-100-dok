---
lang: de
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'Beschreibung der Kamera'
---



# Beschreibung:
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

# Tag Inschriften
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

Anschließen der Ethorn-Netzwerkkamera, empfängt er eine IP-Adresse, und Sie können sich unter http:    
 Standard-Benutzer anschließen:   _admin_    
 Standardkennwort:   _admin_  

Für 5 Minuten können wir mit   _telnet_   an Port 9527 herstellen:    
 Standardbenutzer:   _root  
  
  
Standardkennwort:   _jco66688  
  
  
Bleiben Sie nach diesen 5 Minuten verbunden:   `killall -9 auto_run.sh`      
  _(  JCO = http://www.cnjabsco.com/   )    _



Öffnen von Ports:    
   _tcp_ : 80  (_  http  _), 443  (_  http  _   auch!      


Stop   _jco_  Server  _  , ohne zum Neustart zu führen:    
```
PS | 
```

Der Hauptkanal kann von:  dargestellt werden   
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

und sekundär:    
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

Die in der Online-Schnittstelle angezeigten Informationen:    
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

Der Prozessor lautet:   _ingenic T21_  
  < http://www.ininic.com.cn/de/?product/id/11.html >    
 Der Prozessor lautet:  < https: //fr.indassina.com/ingic-t21-xtreme-2-megapixel-coding-Prozessor _p16.html>     


Der   _CMOS_   SENSOR lautet:   _gc2053_. 

Speicher   _RAM_ :   _42 MiB_   Summe,   _36 MiB_   nutzbar.    

Mit dem Hafer von 9999 können Sie die Kamera überprüfen:    
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

Ports   _GPIO_ :    
 46 = Infrarot-LED.  

GPIO-HADEN zum Schreien blockiert:  
Von motor.ko: 18 blockiert?   

Steuerelemente   _PTZ_ :    

Oben:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
 unten:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_    
 links:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_    
 Rechts:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_    
 Anschlag:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_    
 Position 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
 Position 1:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
 Löschen Position 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

