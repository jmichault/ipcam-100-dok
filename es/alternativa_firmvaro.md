---
lang: es
lang-niv: auto
lang-ref: 010-alternativa_firmvaro
layout: page
title: 'Firmware alternativo'
---

# Puesta en marcha

* La instalación crea el archivo _/opt/etc/local.rc_que lanza el firmware original.


* _local.rc_ inicia _run.sh_ desde la tarjeta SD.



# _run.sh_

  * desconectar la red


  * detener _jco_servidor_ y _autorun.sh_.


  * desactiva _/dev/watchdog_ y _/dev/watchdog0_


  * los LED y el motor se inicializan


  * Inicia el archivo   _etc_   si es necesario  


  * redirige _/bin/busybox_ , _/etc_ y _/root_ a la tarjeta SD.


  * predeterminado a _CRONTAB_ si es necesario


  * iniciar servicios (en _config/autostart_)


  * empezar a usar scripts (en _config/userscripts_)


