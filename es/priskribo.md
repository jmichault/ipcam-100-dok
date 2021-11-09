---
lang: es
lang-niv: auto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'Descripción de la cámara'
---



# Descripción:
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

# Inscripciones de etiquetas
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

Conexión de la cámara de red de Ethorn, recibe una dirección IP, y puede conectarse a él en http:    
 usuario predeterminado:   _admin_    
 Contraseña predeterminada:   _admin_  

Durante 5 minutos, podemos conectarnos con   _telnet_   al puerto 9527:    
 usuario predeterminado:   _root  
  
  
Contraseña predeterminada:   _jco66688  
  
  
Para mantenerse conectado después de estos 5 minutos:   `killall -9 auto_run.sh`      
  _(  JCO = http://www.cnjabsco.com/   )    _



Puertos abiertos:    
   _tcp_ : 80  (_  HTTP  _), 443  (_  HTTP  _   ¡También!      


STOP   _jco_  Server  _   sin causar reinicio:    
```
PS | 
```

El canal principal puede ser representado por:    
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

y secundario:    
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

La información que se muestra en la interfaz en línea:    
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

El procesador es:   _ingenic T21_  
  < http://www.ininic.com.cn/en/?product/id/11.html >    
 El procesador es:  < HTTPS: //fr.indasina.com/ingeric-t21-xtreme-2-megapixel-encoding-processor _p16.html>     


El sensor   _CMOS_   es:   _gc2053_. 

Memoria   _RAM_ :   _42 MiB_   Total,   _36 MiB_   utilizable.    

La avena de 9999 le permite revisar la cámara:    
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

Puertos   _GPIO_ :    
 46 = LED infrarrojo.  

GPIO-Haden bloqueado para gritar:  
Bloqueado por Motor.Ko: 18?   

Controles   _PTZ_ :    

Top:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_    
 Fondo:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_    
 Izquierda:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_    
 Derecha:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_    
 Parada:   _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_    
 Posición 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_    
 Posición 1:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_    
 Posición transparente 2:   _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_    

