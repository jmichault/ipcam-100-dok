---
lang: hi
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'कैमरा का विवरण'
---



# विवरण:
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

# टैग शिलालेख
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

एथर्न नेटवर्क कैमरा को कनेक्ट करना, इसे एक आईपी पता प्राप्त होता है, और आप इसे http:    
 डिफ़ॉल्ट उपयोगकर्ता पर कनेक्ट कर सकते हैं:   _admin_    
 डिफ़ॉल्ट पासवर्ड:   _admin_  

5 मिनट के लिए, हम   _telnet_   पोर्ट 9527 से कनेक्ट कर सकते हैं:    
 डिफ़ॉल्ट उपयोगकर्ता:   _root  
  
  
डिफ़ॉल्ट पासवर्ड:   _jco66688  
  
  
इन 5 मिनट के बाद जुड़े रहने के लिए:   `killall -9 auto_run.sh`      
  _(  jco = http://www.cnjabsco.com/   )    _



ओपन पोर्ट: <एच 1> <एच 2>: 80 <एच 4> http  _), 443  (_  http  _   भी!      


रीबूट के कारण   _jco_  सर्वर  _   रोकें:    
```
PS | 
```

मुख्य चैनल को चित्रित किया जा सकता है:    
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

और माध्यमिक:    
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

ऑनलाइन इंटरफ़ेस में प्रदर्शित जानकारी:    
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

प्रोसेसर है:   _ingenic T21_  
  < http://www.ininic.com.cn/en/?product/id/11.html >    
 प्रोसेसर है:  < https: //fr.indasina.com/ingeric-t21-xtreme-2-megapixel-encoding-processor _p16.html>     


  _CMOS_   सेंसर है:   _gc2053_। 

मेमोरी   _RAM_ :   _42 MiB_   कुल,   _36 MiB_   उपयोग योग्य।    

9999 की जई आपको कैमरे की जांच करने की अनुमति देती है:    
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

बंदरगाह   _GPIO_ :    
 46 = इन्फ्रारेड एलईडी।  

चिल्लाने के लिए gpio-harden अवरुद्ध:   
Motor.ko द्वारा अवरुद्ध: 18?   

नियंत्रण   _PTZ_ :    

शीर्ष:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
 नीचे:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_    
 बाएं:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_    
 दाएं:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_    
 रोकें:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_    
 स्थिति 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
 स्थिति 1:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
 साफ़ स्थिति 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

