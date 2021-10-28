---
lang: es
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Presentación
---

El propósito de este proyecto es crear firmware alternativo para esta cámara: (° 1 ° 1 1

marca = _WIFI CARAM_  
modelo: _WF-HD820-ZS_  
distinción: _1080P_

Información mostrada en la interfaz de Internet:
```
DeviceName: _INGENIC-V01_
DeviceModel: _IPCAM-100_
DeviceSN: _12345678901_
KernelVersion: _Thu Jul 9 15:46:54 CST 2015_
ServerVersion: _WS3.53.1243-20190717-DANALE-GEN_
WebVersion: _V2.3.4-20190709_
```

procesador: _ingenic T21_
sensor de video: _GC2053_

La documentación de la API se puede ver aquí:  
* [versión original en chino](../zh/includes.zh/html/)


* [versión en inglés](../en/includes.en/html/)


* [Versión francesa traducida por google](../fr/includes.fr/html/)



# Firmware alternativo

## Qué funciona en firmware alternativo:

* LAN y WLAN


* DRTTSP Dual Flow Server: 1920x1080 H264 y 640x360 MJPEG de forma predeterminada.


* Parámetros visuales


* Servidor HTTP


* control del motor


* calibración del motor


* Configuración de PTZ


* Cliente NTP


* cambio de contraseña para acceso http


* LED azul y control de infrarrojos


* Servidor ftp


* Servidor Telnet


* SSH Server y Cliente


* detección de movimiento


* envío de correo electrónico



## Lo que no se lleva a cabo en el firmware alternativo:

* sistema de sonido


* _OSD_


* Gestión de la administración y sistema RTSP.


* actualización de firmware


* detección nocturna automática


* detección de movimiento_ir-cut_


* envío de correo electrónico_mqtt_


* etc ...



## Instalación de firmware alternativo

* Copie todo en la carpeta [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) en la raíz de la tarjeta microSD.


* Tal vez establezca la red ( _www/ipcam/config.dist/reto.conf_ )


* Inserta la tarjeta microSD.


* Conecte la cámara a su red local y encienda la cámara.


* Encuentra la dirección IP de la cámara. También puede conectarse a la cámara WiFi (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Conecte a la cámara `telnet IP 9527` (usuario _root_, contraseña _jco66688_), dentro de los 5 minutos después de girar en la cámara.


* Hacer `killall -9 auto_run.sh` para evitar perder la liga.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* Puede conectarse a la URL _https://IP_ (usuario _admin_, contraseña _ismart21_).


* Puede conectarse en el usuario ssh ( _admin_, contraseña _ismart12_).


* La corriente de video primaria es accesible en _rtsp://admin:ismart21@IP/stream1_. (° 3 ° 3


* La corriente de video secundaria es accesible en _rtsp://admin:ismart21@IP/stream2_. (° 3 ° 3


(° 1 ° 1 ° 1 WiFi AP El modo se activa por defecto:
** SSID: IPCAM100-XXXXXX
** Llave WPA2: ISMART21
Dirección IP de la cámara: 172.25.0.1

## Desinstalación de firmware alternativo:

* Inicie el servicio SSH en la cámara a través de la interfaz predeterminada).


* Inicie sesión en la cámara `ssh root@IP` (Contraseña _ismart12_).


* Inicie el servicio Telnet con la cámara a través de la interfaz de Internet. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* También puede simplemente quitar la tarjeta microSD.



## Documentos interesantes

Se hizo mucho trabajo para cámaras equipadas con un procesador _ingenic T20_ :
* * Firmware modificado: <https://github.com/ilílístotlyar/xiomi- Dafang -Haks>
Fuentes del firmware modificado: <https://github.com/dafang-hacks/main>
Otro firmware <https://github.com/openmiko/openmiko>

* Lanzamiento de programas sin cambiar el firmware: (° 17 ° 17 ° 17: // https://github.com/thatusenameanteexist/jcO-pm203-feyeye-iningenic-t20-p2p-camera-hacks>

