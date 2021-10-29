---
lang: pt
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Apresentação
---

O objetivo deste projeto é criar firmware alternativo para esta câmera: (° 1 ° 1

marca = _WIFI CARAM_  
modelo: _WF-HD820-ZS_  
distinção: _1080P_

Informações exibidas na interface da Internet:
```
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

processador: _ingenic T21_
sensor de vídeo: _GC2053_

# Firmware alternativo

## O que funciona no firmware alternativo:

* _LAN_ e _WLAN_


* Servidor (° 1 ° Fluxo duplo: _1920x1080 H264_ e _640x360 MJPEG_ por padrão.  


* Parâmetros visuais


* Servidor _HTTP_


* controle do motor


* calibração do motor


* Parâmetros _PTZ_(° 3 ° 3


* Cliente _NTP_(° 3 ° 3


* Administração de Senha _http_, _rtsp_ e sistema.  


* Controle de LED branco e IR


* Controle de LED branco e IR _ftp_


* Controle de LED branco e IR _telnet_


* Servidor e cliente _ssh_(° 3 ° 3


* detecção de movimento


* enviando e-mail


* Enviar _«telegram»_


* Regime Noturno Automático



## O que não é realizado no firmware alternativo:

* sistema de som


* _OSD_


* atualização de firmware


* detecção de movimento_ir-cut_


* enviando e-mail_mqtt_


* Envio de imagens e vídeos em nuvem (° 1 ° 1


* etc ...



## Instalando Firmware Alternativo

* Copie tudo para a pasta [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) na raiz do cartão microSD.


* Talvez defina a rede ( _www/ipcam/config.dist/reto.conf_ )


* Digite o cartão _microSD_ na câmera.  


* Conecte a câmera à sua rede local e ligue a câmera.


* Encontre o endereço IP da câmera. Você também pode se conectar à câmera WiFi (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Conecte-se à câmera por `telnet IP 9527` (usuário _root_, senha _jco66688_), dentro de 5 minutos após a rotação na câmera.


* Fazer `killall -9 auto_run.sh` para evitar perder a liga.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* A câmera retoma, agora: (° 1 ° 1


    * Você pode se conectar ao URL _https://IP_ (usuário _admin_, Senha _ismart21_).


    * Você pode se conectar no usuário SSH ( _admin_, senha _ismart12_).


    * A corrente de vídeo principal é acessível a _rtsp://admin:ismart21@IP/stream1_. (° 3 ° 3


    * A corrente de vídeo secundária é acessível a _rtsp://admin:ismart21@IP/stream2_. (° 3 ° 3


(° 1 ° 1 ° 1 Modo AP WiFi é ativado por padrão:
    ** SSID: IPCAM100-XXXXXX
WPA2 Key: ismart21
Endereço IP da câmera: 172.25.0.1

## Desinstalando firmware alternativo:

* Inicie o serviço SSH na câmera através da interface padrão).


* Faça login na câmera por `ssh root@IP` (Senha _ismart12_).


* inicie o serviço telnet com a câmera por meio da interface da Internet. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* Você também pode simplesmente remover o cartão microSD.



# Documentos interessantes

Muito trabalho foi feito para câmeras equipadas com um processador _ingenic T20_ :
* Firmware modificado: <https://github.com/ilílístotlyar/xiaomi- Dafang -haks>
Fontes do firmware modificado: <https://github.com/dafang-hacks/main>) 17 °) https://github.com/thatusenameanamexist/jco-pm203-fishe-ininic-t20-p2p-camera-hacks>

