---
lang: eo
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'Priskribo de la fotilo'
---



# Priskribo:
https://en.aliexpress.com/item/4000146161270.html
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

Kunlicante ĝin por Eterreto, ĝi Akiras DHCP-ADRESON KAJ NI POVO KONEKTI AL LA REGETO:  
DefAŭlta Uzanto: Admin  
DefAŭlta Pasvorto: Admin  

Dum 5 Minutoj, VI Povas Konekti per Telnet al la Haveso 9527  
DefAŭlta Uzanto: Radiko  
DefAŭlta Pasvorto: jco66688  
Por resti konektita Preter 5 Minutoj: "Killall -9 aŭtomata_run.sh»  
  
(JCO = http://www.cnjabsco.com/ )  

Malfermaj Arenoj:    
TCP: 80(http), 443(http ankaŭ!     

Reta Konduto Kiam Oni LANĉAS JCO_server:  
  
Pridemandas La servilon DNS PRI: www.163.com Kaj DNS.ICTun.com  
Apliko 114.114.114.114 por DNS.ICTun.com  
KONEKTI AL LA HAVEN UDP / 993 DNS.ICTUNC.com  
Konekti al UDP / 993-havenuso de 120,25.129.41  
PrideMandu la servilon DNS PRI: Conn-policy.ICTun.com  
PrideMandu The Servilon DNS PRI: Video-policy.ICTun.com  
KONEKTI AL UDP / 80-Haveno de 52.29.45.252  
Konektas al UDP / 1210-havenuso de 52.29.45.252  
Ligoj al UDP / 21-havenoj de 52,57.135.134  
Konektas al UDP / 1053-havenes de 52.28.62.20  
KONEKTAS AL UDP / 443-Havas de 52.29.58.225  
Konektas al UDP / 123 (NTP) havenuso de 112,74.204.233 (Video-policy.ICTun.com)  
Ligoj al UDP / 993-havenoj de 47.52.99.182  
Konektas al UDP / 1054-havenes de 52.57.127.207  
...  
Noto: ŝanĝu la DefAŭltan Itineron Tian signifis ke la interrila skatolo.   

Haltigi JCO_server sen kaŭzi restartigi:  
  
## Haltu_cloud :  
```
PS | 
```

VI POVO VIDI LA BEFAN VIDEO-Riverton (LAŭ 1080p Aŭ ALIA AGORDO) per:  
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

Kaj la durangana:
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

La instalita firmvaro Indikas:
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

La Procesoro estas: Ingenic T21  
http://www.ingenic.com.cn/en/?product/id/11.html  
https://en.indasina.com/ingenic-t21-extreme-2-megapixel-encoding-processor_p16.html  
  

La CMOS-sensilo estas: GC2053.   
ŝofora Fonto: https://github.com/mrfixit2001/rk-kernel-fork/blob/develop-4.4/drivers/media/i2c/gc2053.c  

RAM: 42Mib Intt, 36 MIB Havebla.   

La Havedo 9999 estas Malfermita kaj Permesas Regi la Fotilon:  
Echo (° 1 ° Checuser -Act Set -USER Admin -Password Admin"|   
Eo (° 1 ° 1 ° listo"|   
Eo (° 1 ° Pelcod203dRL -?   
Eo (° 1 ° 1 ° Pelcod203ctrl -type 1"|   

GPIO-HADENOJ:  
46 = Infraredĝaj legoj.   
81 = Bluaj leĝoj.   

GPIO-HADENOJ BLOKITAJ POR SLUDO:  
Blokita de Motor.ko: 18?   
Blokita de Audio.ko: 63?   
52 64  

Ptz-Kontrolo:  

Supro: http: // admin: admin@192.168.24.39/? Jcpcmd = pelcod20ctrl -type 1 -cmd 1 -gata1 24 -gata2 24  
Msalru: http: // admin: admin@192.168.24.39/? Jcpcmd = pelcod203crl -type 1 -cmd 2 -gata1 24-gafu2 24  
Maldekstre: http: // admin: admin@192.168.24.39/? Jcpcmd = pelcod203crl -type 1 -cmd 3 -gata1 24 -gata2 24  
Dekstre: http: // admin: admin@192.168.24.39/? JCPCMD = Pelcod203crl -Type 1 -CMD 4 -Data1 24 -Atata2 24  
Halto: http: // admin: admin@192.168.24.39/? Jcpcmd = pelcod203crl -type 1 -cmd 9 -gata1 24-Data2 24  

Starigigu pozicion 2: http://192.168.24.39/?jcpcmd=pelcod20ctl -type 2 -cmd 1 -gata2 2  
Iru al 1: http://192.168.24.39/?JJcpcmd=pelcod203trl -type 2 -cmd 2 -gata2 1  
Forigi 2: http://192.168.24.39/?jcpcmd=pelCod203trl -Type 2 -CMD 3 -Data2 2  



