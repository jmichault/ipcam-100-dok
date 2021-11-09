---
lang: es
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Presentación
---

El propósito de este proyecto es crear un firmware alternativo para esta cámara: 

marca = _WIFI CARAM_  
modelo: _WF-HD820-ZS_  
distinción: _1080P_

Información mostrada en la interfaz de Internet:
```
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

procesador: _ingenic T21_
sensor de video: _GC2053_

# Firmware alternativo

## Qué funciona en firmware alternativo:

* _LAN_   y   _WLAN_  


* Servidor   _RTSP_   Double Stream:   _1920x1080 H264_   y   _640x360 MJPEG_   de forma predeterminada.  


* Parámetros visuales


* Servidor   _HTTP_  


* control del motor


* calibración del motor


* Configuraciones   _PTZ_  


* Cliente   _NTP_  


* Gestione las contraseñas   _http_,   _rtsp_   y el sistema.  


* Control LED blanco e IR  


* Control LED blanco e IR   _ftp_ 


* Control LED blanco e IR   _telnet_ 


* Servidor y cliente   _ssh_  


* detección de movimiento


* envío de correo electrónico


* Enviando   _«telegram»_  


* Modo de noche automático  



## Lo que no se lleva a cabo en el firmware alternativo:

* sistema de sonido


* _OSD_


* actualización de firmware


* detección de movimiento_ir-cut_


* envío de correo electrónico_mqtt_


* Imágenes y videos en la nube  


* etc ...



## Instalación de firmware alternativo

* Copie todo en la carpeta [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) en la raíz de la tarjeta microSD.


* Tal vez establezca la red ( _www/ipcam/config.dist/reto.conf_ )


* Inserte la tarjeta   _microSD_   en la cámara.  


* Conecte la cámara a su red local y encienda la cámara.


* Encuentra la dirección IP de la cámara. También puede conectarse a la cámara WiFi (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Conecte a la cámara `telnet IP 9527` (usuario _root_, contraseña _jco66688_), dentro de los 5 minutos después de girar en la cámara.


* Hacer `killall -9 auto_run.sh` para evitar perder la liga.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* La cámara reinicia ahora:  


    * Puede conectarse a la URL _https://IP_ (usuario _admin_, contraseña _ismart21_).


    * Puede conectarse en el usuario ssh ( _admin_, contraseña _ismart12_).


    * La corriente primaria de video es accesible en  _rtsp://admin:ismart21@IP/stream1_. 


    * El flujo de video secundario es accesible en  _rtsp://admin:ismart21@IP/stream2_. 


    *   El modo WiFi AP está habilitado de forma predeterminada:  
      **   SSID: IPCAM100-XXXXX  
      **   WPA2 Tecla: ISMART21  
      **   Dirección IP de la cámara: 172.25.0.1  

## Desinstalación de firmware alternativo:

* Inicie el servicio SSH en la cámara a través de la interfaz predeterminada).


* Inicie sesión en la cámara `ssh root@IP` (Contraseña _ismart12_).


* Inicie el servicio Telnet con la cámara a través de la interfaz de Internet. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* También puede simplemente quitar la tarjeta microSD.



# Documentos interesantes

Se ha realizado mucho trabajo para cámaras equipadas con un procesador   _ingenic T20_   
  *   Firmware modificado:   <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>  
  *   Fuentes del firmware modificado:   <https://github.com/Dafang-Hacks/Main>  
  *   Otro firmware:   <https://github.com/openmiko/openmiko>  
  *   Lanzamiento de programas sin cambiar el firmware:   <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic-T20-P2P-camera-hacks>  

