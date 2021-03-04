---
lang: it
lang-niv: auto
lang-ref: 099-alternativa_firmvaro
layout: page
title: 'Firmware alternativo'
---

# Avviare

* L'installazione crea il file _/opt/etc/local.rc_che lancia il firmware originale.


* _local.rc_ si avvia _run.sh_ dalla scheda SD.



# _run.sh_

  * scollegare la rete


  * stop _jco_server_ e _autorun.sh_.


  * disattiva _/dev/watchdog_ e _/dev/watchdog0_


  * vengono inizializzati i led e il motore


  * inizializzare la directory ecc. se necessario


  * reindirizza _/bin/busybox_ , _/etc_ e _/root_ alla scheda SD.


  * predefinito a _CRONTAB_ se necessario


  * inizio servizio _crond_, rete, servizio _ntpd_, servizio web


  * inizio servizi (in _config/autostart_)


  * inizia a usare gli script (in _config/userscripts_)


