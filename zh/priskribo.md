---
lang: zh
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 相机的描述
---



# 描述：
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

# 标签铭文
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

它连接录像机网络摄像头，收到IP地址，您可以在HTTP：   
默认用户：  _admin_    
默认密码：  _admin_  

5分钟，我们可以将  _telnet_  连接到端口9527：   
默认用户：  _root  
  
  
默认密码：  _jco66688  
  
  
在这5分钟后保持联系：  `killall -9 auto_run.sh`      
  _(  JCO = http://www.cnjabsco.com/   )    _



打开端口：   
   _tcp_ ：80  (_  HTTP  _)，443  (_  HTTP  _  也！      


停止  _jco_ 服务器 _  而不导致重启：   
```
PS | 
```

主频道可以通过以下方式描绘：   
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

和中学：   
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

在线界面中显示的信息：   
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

处理器是：  _ingenic T21_  
  < http://www.ininic.com.cn/en/?product/id/11.html >    
处理器是： < https： //fr.indasina.com/ingeric-t21-xtreme-2-megapixel-encoding-processor _p16.html>     


  _CMOS_  传感器是：  _gc2053_。 

内存  _RAM_ ：  _42 MiB_  总计，  _36 MiB_  可用。    

9999的燕麦允许您检查相机：   
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

端口  _GPIO_ ：   
 46 =红外LED。  

GPIO-HARDEN被尖叫叫：  
由Motor.ko封锁：18？   

控制  _PTZ_ ：   

顶部：  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
底部：  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_    
左：  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_    
右：  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_    
 STOP：  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_    
位置2：  _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
位置1：  _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
清除位置2：  _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

