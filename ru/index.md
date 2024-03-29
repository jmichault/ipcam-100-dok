---
lang: ru
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Презентация
---

Цель этого проекта состоит в том, чтобы создать альтернативную прошивку для этой камеры: 

отметка = _WIFI CARAM_  
модель: _WF-HD820-ZS_  
различие: _1080P_

Информация, отображаемая в Интернет-интерфейсе:
```
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

процессор: _ingenic T21_
видеосенсор: _GC2053_

# Альтернативная прошивка

## Что работает в альтернативных прошивках:

* _LAN_   и   _WLAN_  


* Сервер   _RTSP_   Двойной поток:   _1920x1080 H264_   и   _640x360 MJPEG_   по умолчанию.  


* Визуальные параметры


* Сервер   _HTTP_  


* управление двигателем


* калибровка двигателя


* Настройки   _PTZ_  


* Клиент   _NTP_  


* Управление паролями   _http_,   _rtsp_   и система.  


* Белый светодиодный контроль и IR  


* Белый светодиодный контроль и IR   _ftp_ 


* Белый светодиодный контроль и IR   _telnet_ 


* Сервер и клиент   _ssh_  


* обнаружение движения


* отправка электронной почты


* Отправка   _«telegram»_  


* Автоматический ночной режим  



## Что не проводится в альтернативной прошивке:

* звуковая система


* _OSD_


* обновление прошивки


* обнаружение движения_ir-cut_


* отправка электронной почты_mqtt_


* Отгрузка изображений и видео в облаке  


* и т.д ...



## Установка альтернативной прошивки

* Скопируйте все в папку [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) в корне карты microSD.


* Возможно установить сеть ( _www/ipcam/config.dist/reto.conf_ )


* Вставьте карту   _microSD_   в камеру.  


* Подключите камеру к локальной сети и включите камеру.


* Найдите IP-адрес камеры. Вы также можете подключиться к Wi-Fi камеры (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Подключитесь к камере `telnet IP 9527` (, пользователя _root_, пароль _jco66688_), в течение 5 минут после вращения на камере.


* Сделайте `killall -9 auto_run.sh` , чтобы не потерять лигу.


* Фару `cd /opt/media/mmcblk0p1;./install.sh`


* Перезагрузка камеры сейчас:  


    * Вы можете подключиться к URL-адресу _https://IP_ ( _admin_, пароль _ismart21_).


    * Вы можете подключиться к пользователю SSH ( _admin_, паролем _ismart12_).


    * Основной видеотек доступен в  _rtsp://admin:ismart21@IP/stream1_. 


    * Вторичный поток видео доступен в  _rtsp://admin:ismart21@IP/stream2_. 


    *   Wi-Fi режим AP включен по умолчанию:  
      **   SSID: IPCAM100-XXXXX  
      **   Клавиша WPA2: ISMART21  
      **   IP-адрес камеры: 172.25.0.1  

## Удаление альтернативной прошивки:

* Запустите сервис SSH на камеру через интерфейс по умолчанию).


* Войдите в камеру по `ssh root@IP` (( _ismart12_).


* запустите службу Telnet с камерой через интернет-интерфейс. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* Вы также можете просто извлечь карту microSD.



# Интересные документы

Большая работа была сделана для камер, оснащенных процессором   _ingenic T20_   
  *   модифицированной прошивкой:   <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>  
  *   Источники модифицированной прошивки:   <https://github.com/Dafang-Hacks/Main>  
  *   Другая прошивка:   <https://github.com/openmiko/openmiko>  
  *   Запуск программ без изменения прошивки:   <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic-T20-P2P-camera-hacks>  

