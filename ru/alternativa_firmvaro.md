---
lang: ru
lang-niv: auto
lang-ref: 010-alternativa_firmvaro
layout: page
title: 'Альтернативная прошивка'
---

# Запускать

* При установке создается файл _/opt/etc/local.rc_, запускаемый исходной прошивкой.


* _local.rc_ запускается _run.sh_ с SD-карты.



# _run.sh_

  * отключить сеть


  * остановить _jco_сервер_ и _autorun.sh_.


  * отключает _/dev/watchdog_ и _/dev/watchdog0_


  * светодиоды и двигатель инициализируются


  * при необходимости инициализировать каталог и т. д.


  * перенаправляет _/bin/busybox_ , _/etc_ и _/root_ на SD-карту.


  * по умолчанию _CRONTAB_ , если требуется


  * запуск сервисов (через _config/autostart_)


  * начать использовать скрипты (в _config/userscripts_)


