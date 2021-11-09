---
lang: ja
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: カメラの説明
---



# 説明：
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

# タグ碑文
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

Ethornネットワークカメラを接続すると、IPアドレスを受け取り、http：   
デフォルトのユーザー：  _admin_    
デフォルトのパスワード：  _admin_  で接続できます。

5分間、  _telnet_  からポート9527に接続できます。   
デフォルトユーザー：  _root  
  
  
デフォルトのパスワード：  _jco66688  
  
  
5分後に接続したままにするには：  `killall -9 auto_run.sh`      
  _(  jco = http://www.cnjabsco.com/   )    _



オープンポート：   
   _tcp_ ：80  (_  http  _)、443  (_  HTTP  _  も！      


再起動を発生させずに  _jco_  Server  _  を停止します。   
```
PS | 
```

メインチャネルは次のように表すことができます。   
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

そして二次：   
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

オンラインインターフェイスに表示される情報：   
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

プロセッサは次のとおりです。  _ingenic T21_  
  < http://www.ininic.com.cn/en/?product/id/11.html >    
プロセッサは次のとおりです。 < https： //fr.indasina.com/ingeric-t21-xtreme-2-megapixel-encoding-processor _p16.html>     


  _CMOS_  センサーは次のとおりです。 

メモリ  _RAM_ ：  _42 MiB_  合計、  _36 MiB_  使用可能。    

9999のOATSを使用すると、カメラを確認できます。   
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

ポート  _GPIO_ ：   
 46 =赤外線LED。  

GPIO - SCREAMINGのためにブロックされた：0xDAC1BEAG.  
Motor.ko：18？   

コントロール  _PTZ_ ：   

上：  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
底：  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_    
左：  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_    
右：  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_    
停止：  _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_    
位置2：  _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
位置1：  _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
透明位置2：  _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

