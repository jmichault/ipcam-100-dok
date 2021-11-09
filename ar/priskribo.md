---
lang: ar
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'وصف الكاميرا'
---



# وصف:
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

# النقوش العلامة
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

توصيل كاميرا شبكة Ethorn، وهو يتلقى عنوان IP، ويمكنك الاتصال به على http:    
 المستخدم الافتراضي:   _admin_    
 كلمة المرور الافتراضية:   _admin_  

لمدة 5 دقائق، يمكننا التواصل مع   _telnet_   إلى Port 9527:    
 المستخدم الافتراضي:   _root  
  
  
كلمة المرور الافتراضية:   _jco66688  
  
  
للبقاء على اتصال بعد هذه الدقائق 5:   `killall -9 auto_run.sh`      
  _(  jco = http://www.cnjabsco.com/   )    _



المنافذ المفتوحة:    
   _tcp_ : 80  (_  http  _)، 443  (_  http  _   أيضا!      


إيقاف   _jco_  الخادم  _   دون التسبب في إعادة التشغيل:    
```
PS | 
```

يمكن تصوير القناة الرئيسية بقلم:    
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

والثانوي:    
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

المعلومات المعروضة في الواجهة عبر الإنترنت:    
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

المعالج هو:   _ingenic T21_  
  < http://www.ininic.com.cn/en/؟product/Id/11.html >    
 المعالج هو:  < https: //fr.indasina.com/ingeric-t21-xtreme-2-megapixel-encoding-processor _p16.html>     


جهاز استشعار   _CMOS_   هو:   _gc2053_. 

الذاكرة   _RAM_ :   _42 MiB_   المجموع،   _36 MiB_   قابلة للاستخدام.    

الشوفان 9999 يسمح لك للتحقق من الكاميرا:    
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

المنافذ   _GPIO_ :    
 46 = LED الأشعة تحت الحمراء.  

منعت GPIO-Haden للصراخ:  
منعت بواسطة motor.ko: 18؟   

الضوابط   _PTZ_ :    

أعلى:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
 أسفل:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_    
 اليسار:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_    
 right:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_    
 stop:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_    
 موضع 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
 موضع 1:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
 واضح الموقف 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

