---
lang: es
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Presentación
---

El objetivo de este proyecto es crear un firmware alternativo para esta cámara:

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

Se ha trabajado mucho para las cámaras equipadas con un procesador _ingenic T20_.
* firmware modificado: <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>
* fuentes de firmware modificado: <https://github.com/Dafang-Hacks/Main>
* otro firmware <https://github.com / openmiko / openmiko>
* iniciar programas sin cambiar el firmware: <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic- T20 -Hacks de cámara P2P>

La documentación de la API se puede ver aquí:  
* [versión original en chino](../zh/includes.zh/html/)


* [versión en inglés](../en/includes.en/html/)


* [Versión francesa traducida por google](../fr/includes.fr/html/)



# Firmware alternativo

## Qué funciona en firmware alternativo:

* LAN y WLAN


* RTSP-Double-Fluid Server: 1280x720 H264 y 640x360 MJPEG


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



## Qué no funciona en firmware alternativo:

* Parámetros visuales


* sistema de sonido


* _OSD_


* actualización de firmware


* detección nocturna automática


* detección de movimiento


* detección de movimiento_ir-cut_


* envío de correo electrónico


* envío de correo electrónico_mqtt_


* etc ...



## Preparación de la cámara

* Conecte la cámara a su red local y encienda la cámara.


* Busque la dirección IP de la cámara.


* Conéctese a la cámara por URL _"http://IP"_ (usuario _admin_, contraseña _admin_)


* en la pestaña "Audio y video", configure la transmisión principal en 720p, haga clic en "Guardar".


* es posible que pueda configurar la red de cable en la pestaña "Red".



## Instalación de firmware alternativo

* Copie todo en la carpeta [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) en la raíz de la tarjeta microSD.


* opcionalmente configurar la red ( _config/staticip.conf_ , _config/resolv.conf_ , _config/wpa_suplicant.conf_ )


* Inserta la tarjeta microSD.


* Conecte la cámara a su red local y encienda la cámara.


* Inicie sesión en la cámara con `telnet IP 9527` (usuario _root_, contraseña _jco66688_).


* Presione `killall -9 auto_run.sh` para evitar cerrar la conexión.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* Puede conectarse a la URL _"https://IP"_ (usuario _admin_, contraseña _jco66688_).



## Desinstalación de firmware alternativo:

* Inicie el servicio Telnet con la cámara a través de la interfaz de Internet.


* Inicie el servicio Telnet con la cámara a través de la interfaz de Internet. `telnet IP` 


* Inicie el servicio Telnet con la cámara a través de la interfaz de Internet. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* También puede simplemente quitar la tarjeta microSD.


