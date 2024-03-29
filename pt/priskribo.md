---
lang: pt
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'Descrição da câmera'
---



# Descrição:
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

# Inscrições de tags.
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

Conectando a câmera de rede etnorn, recebe um endereço IP e você pode se conectar a ele em http:    
 usuário padrão:   _admin_    
 senha padrão:   _admin_  

Por 5 minutos, podemos nos conectar com   _telnet_   para a porta 9527:    
 Usuário padrão:   _root  
  
  
Senha padrão:   _jco66688  
  
  
Para ficar conectado após estes 5 minutos:   `killall -9 auto_run.sh`      
  _(  jco = http://ww.cnjabsco.com/   )    _



Portas abertas:    
   _tcp_ : 80  (_  http  _), 443  (_  http  _   também!      


Pare   _jco_  Server  _   sem causar reinicialização:    
```
PS | 
```

O canal principal pode ser representado por:    
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

e secundário:    
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

As informações exibidas na interface on-line:    
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

O processador é:   _ingenic T21_  
  < http://www.ininic.com.cn/en/?product/id/11.html >    
 O processador é:  < https: //fr.indasina.com/ingeric-t21-xtreme-2-megapixel-encoding-processor _p16.html>     


O sensor   _CMOS_   é:   _gc2053_. 

Memória   _RAM_ :   _42 MiB_   Total,   _36 MiB_   utilizável.    

A aveia de 9999 permite que você verifique a câmera:    
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

Portas   _GPIO_ :    
 46 = LED infravermelho.  

GPIO-HADEN bloqueado para gritar:  
Bloqueado por motor.ko: 18?   

Controles   _PTZ_ :    

Top:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
 Bottom:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_    
 Esquerda:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_    
 Direito:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_    
 Parada:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_    
 Posição 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
 Posição 1:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
 Clear Posição 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

