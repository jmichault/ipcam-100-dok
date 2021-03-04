---
lang: ms
lang-niv: auto
lang-ref: 099-alternativa_firmvaro
layout: page
title: 'Firmware alternatif'
---

# Memulakan

* Pemasangan membuat fail _/opt/etc/local.rc_yang dilancarkan oleh firmware asal.


* _local.rc_ dilancarkan _run.sh_ dari kad SD.



# _run.sh_

  * putuskan sambungan rangkaian


  * henti _jco_pelayan_ dan _autorun.sh_.


  * menyahaktifkan _/dev/watchdog_ dan _/dev/watchdog0_


  * LED dan motor diinisialisasi


  * memulakan direktori dll jika perlu


  * mengarahkan _/bin/busybox_ , _/etc_ dan _/root_ ke kad SD.


  * lalai ke _CRONTAB_ jika diperlukan


  * memulakan perkhidmatan _crond_, rangkaian, perkhidmatan _ntpd_, perkhidmatan web


  * memulakan perkhidmatan (dalam _config/autostart_)


  * mula menggunakan skrip (dalam _config/userscripts_)


