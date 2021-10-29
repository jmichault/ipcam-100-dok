---
lang: fr
lang-niv: fonto
lang-ref: 010-alternativa_firmvaro
layout: page
title: 'Le micrologiciel alternatif'
---

# Démarrage

* L'installation crée le fichier _/opt/etc/local.rc_, qui est lancé par le micrologiciel d'origine.
* _local.rc_ lance _run.sh_ depuis la carte SD.

# _run.sh_

  * déconnecte le réseau
  * arrête _jco_server_ et _autorun.sh_.
  * désactive _/dev/watchdog_ et _/dev/watchdog0_
  * initialise les LED et le moteur
  * initialise le répertoire etc si nécessaire
  * redirige _/bin/busybox_ , _/etc_ et _/root_ vers la carte SD.
  * initialise la _CRONTAB_ si nécessaire
  * démarre les services (dans _config/autostart_)
  * démarre les scripts utilisateur (dans _config/userscripts_)
