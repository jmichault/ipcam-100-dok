---
lang: pt
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Apresentação
---

O objetivo deste projeto é criar um firmware alternativo para esta câmera:

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

Muito trabalho foi feito para câmeras equipadas com um processador _ingenic T20_.
* firmware modificado: <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>
* fontes de firmware modificado: <https://github.com/Dafang-Hacks/Main>
* outro firmware <https://github.com / openmiko / openmiko>
* lançando programas sem alterar o firmware: <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic- T20 -P2P câmera hacks>

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



## O que não funciona em firmware alternativo:

* sistema de som


* _OSD_


* Gerenciamento de senha.


* atualização de firmware


* detecção noturna automática


* detecção de movimento_ir-cut_


* enviando e-mail_mqtt_


* etc ...



## Preparação da câmera

* Conecte a câmera à sua rede local e ligue a câmera.


* Encontre o endereço IP da câmera.


* Conecte-se à câmera por URL _"http://IP"_ (usuário _admin_, senha _admin_)


* na guia "Áudio e vídeo", defina o stream principal para 720p, clique em "Salvar".


* você pode ser capaz de definir a rede de cabos na guia "Rede".



## Instalando Firmware Alternativo

* Copie tudo para a pasta [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) na raiz do cartão microSD.


* opcionalmente configurar a rede ( _config/staticip.conf_ , _config/resolv.conf_ , _config/wpa_suplicant.conf_ )


* Insira o cartão microSD.


* Conecte a câmera à sua rede local e ligue a câmera.


* Conecte-se à câmera por `telnet IP 9527` (usuário _root_, senha _jco66688_), dentro de 5 minutos após a rotação na câmera.


* Fazer `killall -9 auto_run.sh` para evitar perder a liga.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* Você pode se conectar à URL (° 1 ° Usuário( _admin_, Senha _ismart21_).


* Você pode se conectar ao usuário ssh ( _admin_, senha _ismart12_).


* A corrente de vídeo principal é acessível a _rtsp://admin:ismart21@IP/stream1_. (° 3 ° 3


* A corrente de vídeo secundária é acessível a _rtsp://admin:ismart21@IP/stream2_. (° 3 ° 3



## Desinstalando firmware alternativo:

* inicie o serviço telnet com a câmera por meio da interface da Internet.


* inicie o serviço telnet com a câmera por meio da interface da Internet. `telnet IP` 


* inicie o serviço telnet com a câmera por meio da interface da Internet. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* Você também pode simplesmente remover o cartão microSD.


