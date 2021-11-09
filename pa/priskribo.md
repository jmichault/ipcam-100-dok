---
lang: pa
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'ਕੈਮਰੇ ਦਾ ਵੇਰਵਾ'
---



# ਵੇਰਵਾ:
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

# ਟੈਗ ਸ਼ਿਲਾਲੇਖ
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

ਇੱਕ ਨੋਰਤਾ ਨੈਟਵਰਕ ਕੈਮਰੇ ਨਾਲ ਜੁੜ ਰਿਹਾ ਹੈ, ਇਹ ਇੱਕ IP ਪਤਾ ਪ੍ਰਾਪਤ ਕਰਦਾ ਹੈ, ਅਤੇ ਤੁਸੀਂ ਇਸ ਨਾਲ HTTP ਤੇ ਜੁੜ ਸਕਦੇ ਹੋ:   _admin_    
 ਡਿਫੌਲਟ ਪਾਸਵਰਡ:   _admin_  

5 ਮਿੰਟ ਲਈ, ਅਸੀਂ   _telnet_   ਤੋਂ ਪੋਰਟ 9527:    
 ਡਿਫਾਲਟ ਉਪਭੋਗਤਾ ਨਾਲ ਜੁੜ ਸਕਦੇ ਹਾਂ:   _root  
  
  
ਡਿਫੌਲਟ ਪਾਸਵਰਡ:   _jco66688  
  
  
ਇਹਨਾਂ 5 ਮਿੰਟ ਦੇ ਬਾਅਦ ਜੁੜੇ ਰਹਿਣ ਲਈ:   `killall -9 auto_run.sh`      
  _(  jco = http://www.c.c.com/   )    _



ਬੰਦਰਗਾਹਾਂ ਖੋਲ੍ਹੋ:    
   _tcp_ : 80  (_  http  _), 443  (_  http > HTTP       


ਰੀਬੂਟ ਪੈਦਾ ਕੀਤੇ ਬਿਨਾਂ   _jco_  ਸਰਵਰ  _   ਨੂੰ ਰੋਕੋ:    
```
PS | 
```

ਮੁੱਖ ਚੈਨਲ ਦੁਆਰਾ ਦਰਸਾਇਆ ਜਾ ਸਕਦਾ ਹੈ:    
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

ਅਤੇ ਸੈਕੰਡਰੀ:    
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

Inftern ਨਲਾਈਨ ਇੰਟਰਫੇਸ ਵਿੱਚ ਪ੍ਰਦਰਸ਼ਿਤ ਜਾਣਕਾਰੀ:    
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

ਪ੍ਰੋਸੈਸਰ ਇਹ ਹੈ:   _ingenic T21_  
 
 http://www.inuticom.cn/een/?product.com >    
 thtps: //fr.indasina.com/ingeRix-t21-MagapiciCuding- ਪਰੋਸੈਸਰ _p16.html>     


  _CMOS_   ਸੈਂਸਰ ਹੈ:   _gc2053_. 

ਯਾਦ   _RAM_ :   _42 MiB_   ਕੁੱਲ,   _36 MiB_   ਵਰਤੋਂ ਯੋਗ.    

9999 ਦੇ ਜਵੀ ਤੁਹਾਨੂੰ ਕੈਮਰੇ ਦੀ ਜਾਂਚ ਕਰਨ ਦੀ ਆਗਿਆ ਦਿੰਦੇ ਹਨ:    
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

ਪੋਰਟਸ   _GPIO_ :    
 46 = ਇਨਫਰਾਰੈੱਡ ਐਲਈਡੀ.  

GPIO-Haden ਚੀਕਣ ਲਈ ਬਲੌਕ ਕੀਤਾ ਗਿਆ:  
ਮੋਟਰ.ਕੋ: 18 ਦੁਆਰਾ ਬਲੌਕ ਕੀਤਾ ਗਿਆ?   

ਕੰਟਰੋਲ   _PTZ_ :    

ਸਿਖਰ:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
 
 ਖੱਬੇ:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_    
   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    ਸਥਿਤੀ 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
 ਸਥਿਤੀ) 1:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
 ਸਾਫ ਸਥਿਤੀ 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

