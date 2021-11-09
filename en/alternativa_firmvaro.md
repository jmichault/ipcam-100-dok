---
lang: en
lang-niv: auto
lang-ref: 010-alternativa_firmvaro
layout: page
title: 'Alternative firmware'
---

# Start-up

* The installation creates the file _/opt/etc/local.rc_that the original firmware launches.


* _local.rc_ launches _run.sh_ from the SD card.



# _run.sh_

  * disconnect the network


  * stop _jco_server_ and _autorun.sh_.


  * deactivates _/dev/watchdog_ and _/dev/watchdog0_


  * the LEDs and the motor are initialized


  * Starts the   _etc_   file if necessary  


  * redirects _/bin/busybox_ , _/etc_ and _/root_ to the SD card.


  * default to _CRONTAB_ if required


  * start services (in _config/autostart_)


  * start using scripts (in _config/userscripts_)


