---
lang: ru
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'Описание камеры'
---



# Описание:
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

# Теги надписи
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

Подключение сетевой камеры Ethorn, она получает IP-адрес, и вы можете подключиться к нему по адресу http:    
 Пользователь по умолчанию:   _admin_    
 Пароль по умолчанию:   _admin_  

В течение 5 минут мы можем подключиться с   _telnet_   для порта 9527:    
 Пользователь по умолчанию:   _root  
  
  
Пароль по умолчанию:   _jco66688  
  
  
Чтобы оставаться на связи после этих 5 минут:   `killall -9 auto_run.sh`      
  _(  JCO = http://www.cnjabsco.com/   )    _



Открытые порты:    
   _tcp_ : 80  (_  http  _), 443  (_  http  _        


Остановите   _jco_  Сервер  _   Не вызывая перезагрузка:    
```
PS | 
```

Основной канал может быть изображен:    
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

и вторичный:    
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

Информация, отображаемая в интерфейсе онлайн:    
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

Процессор:   _ingenic T21_  
  < http://www.ininic.com.cn/en/?product/id/11.html >    
 процессор:  < https: //fr.indasina.com/ingeric-t21-xtreme-2-megapixel-encoding-Processor _p16.html>     


Датчик   _CMOS_  :   _gc2053_. 

Память   _RAM_ :   _42 MiB_   Всего,   _36 MiB_   Используется.    

Овес 9999 позволяет проверить камеру:    
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

Порты   _GPIO_ :    
 46 = инфракрасный светодиод.  

Gpio-Haden заблокирован для криков:  
Заблокирован Motor.ko: 18?   

Управление   _PTZ_ :    

Верх:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
 Нижняя:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_    
 Слева:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_    
 Верно:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_    
 Стоп:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_    
 Положение 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
 позиция 1:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
 Очистить положение 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

