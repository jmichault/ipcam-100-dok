---
lang: bn
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'ক্যামেরা বর্ণনা'
---



# বর্ণনা:
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

# ট্যাগ শিলালিপি
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

Enthorn নেটওয়ার্ক ক্যামেরাটি সংযুক্ত করে, এটি একটি আইপি ঠিকানা পায়, এবং আপনি এটিতে সংযোগ করতে পারেন http:    
 ডিফল্ট ব্যবহারকারী:   _admin_    
 ডিফল্ট পাসওয়ার্ড:   _admin_  

5 মিনিটের জন্য, আমরা   _telnet_   থেকে পোর্ট 9527:    
 ডিফল্ট ব্যবহারকারী:   _root  
 এর সাথে সংযোগ করতে পারি  
  
ডিফল্ট পাসওয়ার্ড:   _jco66688  
  
  
এই 5 মিনিটের পরে সংযুক্ত থাকার জন্য:   `killall -9 auto_run.sh`      
  _(  jco = http://www.cnjabsco.com/   )    _



ওপেন পোর্টস:    
   _tcp_ : 80  (_  HTTP  _), 443  (_  HTTP  _   এছাড়াও!      


  _jco_  সার্ভার  _   রিবুট ছাড়াই বন্ধ করুন:    
```
PS | 
```

প্রধান চ্যানেলটি চিত্রিত করা যেতে পারে:    
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

এবং সেকেন্ডারি:    
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

অনলাইন ইন্টারফেসে প্রদর্শিত তথ্য:    
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

প্রসেসর হল:   _ingenic T21_  
  < http://www.ininic.com.cn/en/?product/id/11.HTML >    
 প্রসেসর হল:  < HTTPS: //fr.indasina.com/ingeric-t21-xtreme-2-megapixel-encoding-processor _p16.html>     


  _CMOS_   সেন্সরটি হল:   _gc2053_। 

মেমরি   _RAM_ :   _42 MiB_   মোট,   _36 MiB_   ব্যবহারযোগ্য।    

9999 এর ওটগুলি আপনাকে ক্যামেরাটি পরীক্ষা করার অনুমতি দেয়:    
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

পোর্ট   _GPIO_ :    
 46 = ইনফ্রারেড LED।  

জিপিও-হাদেন স্ক্রেটিংয়ের জন্য অবরুদ্ধ:  
Motor.ko দ্বারা অবরুদ্ধ: 18?   

নিয়ন্ত্রণ   _PTZ_ :    

শীর্ষ:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
 নীচে:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_    
 বাম:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_      _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    DISHE:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_    
 অবস্থান 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
 অবস্থান 1:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
 সাফ অবস্থান 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

