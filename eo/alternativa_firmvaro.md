---
lang: eo
lang-niv: auto
lang-ref: 099-alternativa_firmvaro
layout: page
title: 'Alternativa firmvaro'
---

# Ekfunkciigo

* La instalado kreas la dosieron _/opt/etc/local.rc_, kiun lanĉas la originala firmvaro.

* _local.rc_ lanĉas _run.sh_ de la SD-karto.


# _run.sh_

  * malkonekti la reton

  * haltigi _jco_servilon_ kaj _autorun.sh_.

  * malaktivigas _/dev/watchdog_ kaj _/dev/watchdog0_

  * pravalorizas la LEDojn kaj la motoron

  * pravalorizas la adresaron ktp se necese

  * alidirektiloj _/bin/busybox_ , _/etc_ kaj _/root_ al la SDa karto.

  * pravalorizi la _CRONTAB_ se necese

  * startservo _crond_, reto, servo _ntpd_, reteja servo

  * komenci servojn (en _config/autostart_)

  * komenci uzantajn skriptojn (en _config/userscripts_)

