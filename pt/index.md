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

* _LAN_   e   _WLAN_  


* Servidor   _RTSP_   Duplo Stream:   _1920x1080 H264_   e   _640x360 MJPEG_   por padrão.  


* Parâmetros visuais


* Servidor   _HTTP_  


* controle do motor


* calibração do motor


* Configurações   _PTZ_  


* Cliente   _NTP_  


* Gerenciar senhas   _http_,   _rtsp_   e sistema.  


* Controle de LED branco e IR  


* Controle de LED branco e IR   _ftp_ 


* Controle de LED branco e IR   _telnet_ 


* Servidor e cliente   _ssh_  


* detecção de movimento


* enviando e-mail


* Envio   _«telegram»_  


* Modo Noite Automático  



## O que não é realizado no firmware alternativo:

* sistema de som


* _OSD_


* atualização de firmware


* detecção de movimento_ir-cut_


* enviando e-mail_mqtt_


* Imagens de envio e vídeos na nuvem  


* etc ...



## Instalando Firmware Alternativo

* Copie tudo para a pasta [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) na raiz do cartão microSD.


* Talvez defina a rede ( _www/ipcam/config.dist/reto.conf_ )


* Insira o cartão   _microSD_   na câmera.  


* Conecte a câmera à sua rede local e ligue a câmera.


* Encontre o endereço IP da câmera. Você também pode se conectar à câmera WiFi (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Conecte-se à câmera por `telnet IP 9527` (usuário _root_, senha _jco66688_), dentro de 5 minutos após a rotação na câmera.


* Fazer `killall -9 auto_run.sh` para evitar perder a liga.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* A câmera reinicializa agora:  


    * Você pode se conectar ao URL _https://IP_ (usuário _admin_, Senha _ismart21_).


    * Você pode se conectar no usuário SSH ( _admin_, senha _ismart12_).


    * A corrente de vídeo principal é acessível a  _rtsp://admin:ismart21@IP/stream1_. 


    * O fluxo de vídeo secundário é acessível em  _rtsp://admin:ismart21@IP/stream2_. 


    *   WiFi AP Mode é ativado por padrão:  
      **   SSID: IPCAM100-XXXXX  
      **   WPA2 Key: ismart21  
      **   endereço IP da câmera: 172.25.0.1  

## Desinstalando firmware alternativo:

* Inicie o serviço SSH na câmera através da interface padrão).


* Faça login na câmera por `ssh root@IP` (Senha _ismart12_).


* inicie o serviço telnet com a câmera por meio da interface da Internet. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* Você também pode simplesmente remover o cartão microSD.



# Documentos interessantes

Muito trabalho foi feito para câmeras equipadas com um processador   _ingenic T20_   
  
 Firmware modificado:   <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>  
  *   Fontes do firmware modificado:   <https://github.com/Dafang-Hacks/Main>  
  *   outro firmware:   <https://github.com/openmiko/openmiko>  
  *   programas de lançamento sem alterar o firmware:   <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic-T20-P2P-camera-hacks>  

