---
lang: eo
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'Priskribo de la fotilo'
---



# Priskribo:
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

# Etikedaj surskriboj
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

Konektante la fotilon al Ethorn-reto, ĝi ricevas IP-adreson, kaj vi povas konektiĝi al ĝi ĉe http:   
Defaŭlta Uzanto:  _admin_   
Defaŭlta Pasvorto:  _admin_ 

Dum 5 minutoj, ni povas konekti per  _telnet_  al haveno 9527:   
Defaŭlta Uzanto:  _root  
  
Defaŭlta Pasvorto:  _jco66688  
  
Por resti konektita post ĉi tiuj 5 minutoj:  `killall -9 auto_run.sh`     
 _( JCO = http://www.cnjabsco.com/  )   _


Malfermu havenojn:   
  _tcp_ : 80 (_ http _), 443 (_ http _  ankaŭ!     


Halti  _jco_ servilo _  sen kaŭzi reboot:   
```
PS | 
```

La ĉefa kanalo povas esti bildigita per:   
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

kaj sekundara:   
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

La informoj montritaj en la interreta interfaco:   
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

La procesoro estas:  _ingenic T21_ 
 <http://www.ingenic.com.cn/en/?product/id/11.html>   
La procesoro estas: <https://fr.indasina.com/ingenic-t21-extreme-2-megapixel-encoding-processor_p16.html>     

La sensor  _CMOS_  estas:  _gc2053_.   
Fontoj:  < https://github.com/mrfixit2001/rk-kernel-for-/blob/develop-4.4/drivers/media/i2c/gc2053.c >   

Memoro  _RAM_ :  _42 MiB_  Totalo,  _36 MiB_  Uzebla.   

La aveno de 9999 permesas vin kontroli la fotilon:   
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

Havenoj  _GPIO_ :   
46 = Transruĝa LED.   
81 = Blanka LED. 

GPIO-HADENOJ BLOKITAJ POR SLUDO:  
Blokita de Motor.ko: 18?   
Blokita de Audio.ko: 63?   
52 64  

Kontroloj  _PTZ_ :   

Supro:  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_   
Fundo:  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_   
Maldekstra:  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_   
Uste:  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_   
Haltu:  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_   
Pozicio 2:  _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_   
Pozicio 1:  _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_   
Klara pozicio 2:  _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_   

