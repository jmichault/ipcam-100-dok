---
lang: de
lang-niv: auto
lang-ref: 010-alternativa_firmvaro
layout: page
title: 'Alternative Firmware'
---

# Anlaufen

* Bei der Installation wird die Datei _/opt/etc/local.rc_erstellt, die von der ursprünglichen Firmware gestartet wird.


* _local.rc_ startet _run.sh_ von der SD-Karte.



# _run.sh_

  * Trennen Sie das Netzwerk


  * Stopp _jco_Server_ und _autorun.sh_.


  * deaktiviert _/dev/watchdog_ und _/dev/watchdog0_


  * Die LEDs und der Motor werden initialisiert


  * Startet bei Bedarf die   _etc_   -e  


  * leitet _/bin/busybox_ , _/etc_ und _/root_ auf die SD-Karte um.


  * Standardmäßig _CRONTAB_ , falls erforderlich


  * Service starten (in _config/autostart_)


  * Beginnen Sie mit der Verwendung von Skripten (in _config/userscripts_).


