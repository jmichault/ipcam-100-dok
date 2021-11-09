---
lang: fr
lang-niv: fonto
lang-ref: 070-kamerao-priskribo
layout: page
title: 'Description de la caméra'
---



# Description :
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

# Inscriptions sur l'étiquette
```
WIFI CARAM
Model : WF-HD820-ZS
Résolution : 1080P
Power Supply : DC12V/1A
SSID : HSIPC-******
Password : 12345678
MAC : 00:88:09:**:**:**
```

En connectant la caméra à un réseau éthernet, elle obtient une adresse IP, et on peut s'y connecter en http :  
utilisateur par défaut : _admin_  
mot de passe par défaut : _admin_

Pendant 5 minutes, on peut se connecter par _telnet_ au port 9527 :  
utilisateur par défaut : _root  
mot de passe par défaut : _jco66688  
Pour rester connecté après ces 5 minutes : `killall -9 auto_run.sh`    
_(jco = http://www.cnjabsco.com/ )  _

Ports ouverts :  
  _tcp_ : 80(_http_), 443(_http_ aussi !), 554(_rtsp_), 8004, 8006, 9527(_telnetd_), 9999    
  _udp_ : 67(_dhcp_), 3702, 8002, 39642    


Arrêter _jco_server_ sans causer un redémarrage :  
```
ps | awk '/[a]uto_run.sh/ {print $1}' | while read PID; do kill -9 $PID; done;
ps | awk '/[j]co_server/ {print $1}' | xargs kill -9 &>/dev/null
echo 'V'>/dev/watchdog
echo 'V'>/dev/watchdog0
rm '/opt/media/mmcblk0p1/cid.txt' &>/dev/null
```

On peut visualiser le canal principal avec :  
```
ffplay -i rtsp://admin:admin@192.168.24.111/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream1
ffplay -i rtsp://admin:admin@192.168.24.39:554/mpeg4/ch0/main/av_stream
```

et le secondaire :  
```
ffplay -i rtsp://admin:admin@192.168.24.39/stream2
ffplay -i rtsp://admin:admin@192.168.24.39:554/stream2
```

Les informations affichées dans l'interface web :  
```
DeviceName:     INGENIC-V01
DeviceModel:    IPCAM-100
DeviceSN:       12345678901
KernelVersion:  Thu Jul 9 15:46:54 CST 2015
ServerVersion:  WS3.53.1243-20190717-DANALE-GEN
WebVersion:     V2.3.4-20190709
OCXVersion:     -1
```

Le processeur est : _ingenic T21_
<http://www.ingenic.com.cn/en/?product/id/11.html>  
<https://fr.indasina.com/ingenic-t21-extreme-2-megapixel-encoding-processor_p16.html>  

Le capteur _CMOS_ est : _gc2053_.  
sources : <https://github.com/mrfixit2001/rk-kernel-fork/blob/develop-4.4/drivers/media/i2c/gc2053.c>  

mémoire _RAM_ : _42 MiB_ total, _36 MiB_ utilisables.  

Le port 9999 permet de contrôler la caméra :  
```
echo "checkuser -act set -user admin -password admin" | nc 192.168.1.155 9999  
echo "list" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -?" | nc 192.168.1.155 9999  
echo "pelcod20ctrl -type 1" | nc 192.168.1.155 9999  
```

Ports _GPIO_ :  
46 = LED infrarouge.  
81 = LED blanche.

GPIO-havenoj blokitaj por studado:  
blokita de motor.ko: 18? 38 39 40 41 47 48 49 60?  
blokita de audio.ko: 63?  
52 64  

contrôles _PTZ_ :  

haut : _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 1 -data1 24 -data2 24_  
bas : _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 2 -data1 24 -data2 24_  
gauche : _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 3 -data1 24 -data2 24_  
droite : _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 4 -data1 24 -data2 24_  
stop : _http://admin:admin@192.168.24.39/?jcpcmd=pelcod20ctrl -type 1 -cmd 9 -data1 24 -data2 24_  
position 2 : _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 1 -data2 2_  
position 1 : _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 2 -data2 1_  
effacer position 2: _http://192.168.24.39/?jcpcmd=pelcod20ctrl -type 2 -cmd 3 -data2 2_  

