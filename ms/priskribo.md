---
lang: ms
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'Keterangan kamera'
---



# Penerangan:
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

# Tag inskripsi
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

Menyambungkan kamera rangkaian ETHORN, ia menerima alamat IP, dan anda boleh menyambung kepadanya di http:    
 Pengguna lalai:   _admin_    
 Kata laluan lalai:   _admin_  

Selama 5 minit, kami boleh berhubung dengan   _telnet_   ke Port 9527:    
 Pengguna Lalai:   _root  
  
  
Kata laluan lalai:   _jco66688  
  
  
Untuk terus berhubung selepas 5 minit:   `killall -9 auto_run.sh`      
  _(  jco = http://www.cnjabsco.com/   )    _



Port Terbuka:    
   _tcp_ : 80  (_  http  _), 443  (_  http  _   juga!      


Hentikan   _jco_  pelayan  _   tanpa menyebabkan reboot:    
```
PS | 
```

Saluran utama boleh digambarkan oleh:    
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

dan sekunder:    
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

Maklumat yang dipaparkan dalam antara muka dalam talian:    
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

Pemproses adalah:   _ingenic T21_  
  < http://www.ininic.com.cn/en/?product/id/11.html >    
 Pemproses adalah:  < https: //fr.indasina.com/ingeric-t21-xtreme-2-megapixel-encoding-prosesor _p16.html>     


Sensor   _CMOS_   ialah:   _gc2053_. 

Memori   _RAM_ :   _42 MiB_   total,   _36 MiB_   boleh digunakan.    

Oats of 9999 membolehkan anda menyemak kamera:    
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

Pelabuhan   _GPIO_ :    
 46 = inframerah LED.  

GPIO-HADEN disekat untuk menjerit:  
Disekat oleh Motor.ko: 18?   

Kawalan   _PTZ_ :    

Atas:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
 Bawah:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_    
 kiri:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_    
 betul:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_    
 henti:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_    
 kedudukan 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
 kedudukan 1:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
 kedudukan jelas 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

