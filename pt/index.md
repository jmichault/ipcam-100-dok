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
DeviceName: _INGENIC-V01_
DeviceModel: _IPCAM-100_
DeviceSN: _12345678901_
KernelVersion: _Thu Jul 9 15:46:54 CST 2015_
ServerVersion: _WS3.53.1243-20190717-DANALE-GEN_
WebVersion: _V2.3.4-20190709_
```

processador: _ingenic T21_
sensor de vídeo: _GC2053_

A documentação da API pode ser vista aqui:  
* [versão original em chinês](../zh/includes.zh/html/)


* [Versão em inglês](../en/includes.en/html/)


* [Versão francesa traduzida pelo google](../fr/includes.fr/html/)



# Firmware alternativo

## O que funciona no firmware alternativo:

* LAN e WLAN


* DRTTSP Dual Flow Server: 1920x1080 H264 e 640x360 MJPEG por padrão.


* Parâmetros visuais


* Servidor HTTP


* controle do motor


* calibração do motor


* Configurações de PTZ


* Cliente NTP


* alteração de senha para acesso http


* LED azul e controle IR


* Servidor ftp


* Servidor Telnet


* Servidor SSH e Cliente


* detecção de movimento


* enviando e-mail



## O que não é realizado no firmware alternativo:

* sistema de som


* _OSD_


* Gerenciamento de administração e sistema RTSP.


* atualização de firmware


* detecção noturna automática


* detecção de movimento_ir-cut_


* enviando e-mail_mqtt_


* etc ...



## Instalando Firmware Alternativo

* Copie tudo para a pasta [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) na raiz do cartão microSD.


* Talvez defina a rede ( _www/ipcam/config.dist/reto.conf_ )


* Insira o cartão microSD.


* Conecte a câmera à sua rede local e ligue a câmera.


* Encontre o endereço IP da câmera. Você também pode se conectar à câmera WiFi (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Conecte-se à câmera por `telnet IP 9527` (usuário _root_, senha _jco66688_), dentro de 5 minutos após a rotação na câmera.


* Fazer `killall -9 auto_run.sh` para evitar perder a liga.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


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
Fontes do firmware modificado: <https://github.com/dafang-hacks/main>11 ° 12 °) Outros firmware <https://github.com/openmiko/openmiko>
* Lançamento de programas sem alterar o firmware: (° 17 ° 17 ° 17: // https://github.com/thatusenameanameexist/jco-pm203-fisheye-iningenic-t20-p2p-camera-packs>

