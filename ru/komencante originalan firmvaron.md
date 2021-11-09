---
lang: ru
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'Работа оригинальной прошивки'
---

Прошивка состоит из 6 вандалов:  

|. Разбиение Тип |. Роль  
 | ------------ |. ------------------------ |. -------------- |.  
 |   _mtdblock0_   |   _u-boot_                 | Запуск  
 |   _mtdblock1_   | Текст Настройки |.  
 |   _mtdblock2_   |   _u-boot legacy uImage_   | Core   _linux_   |  
 |   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

Первая выполненная программа составляет   _/linuxrc_.    
 он запускает   _/etc/init.d/rcS_.    
 _/etc/init.d/rcS_   запускает   _/ipc/etc/auto\_run.sh_.    
 _/ipc/etc/auto\_run.sh_   lanco   _/opt/etc/local.rc_   Перед запуском   _/ipc/app/jco\_server_.    
 _/ipc/app/jco\_server_   - главная программа: она обслуживает как сервер   _rtsp_ , сервер   _http_, ...  

