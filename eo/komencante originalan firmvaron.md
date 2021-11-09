---
lang: eo
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'Funkciado de la originala firmware'
---

La firmware konsistas el 6 vandoj: 

| Dispartigo | Tipo | Rolo | 
 | ----------- | ---------------------- | ------------- | 
 |  _mtdblock0_  |  _u-boot_                | Komencante | 
 |  _mtdblock1_  | Teksto | Agordoj | 
 |  _mtdblock2_  |  _u-boot legacy uImage_  | Kerno  _linux_  | 
 |  _mtdblock3_  |  _squashfs_              |  _/_            | 
 |  _mtdblock4_  |  _squashfs_              |  _/ipc_         | 
 |  _mtdblock5_  |  _jffs1_                 |  _/opt_         | 

La unua programo ekzekutita estas  _/linuxrc_.   
Li lanĉas  _/etc/init.d/rcS_.   
_/etc/init.d/rcS_  lanĉas  _/ipc/etc/auto\_run.sh_.   
_/ipc/etc/auto\_run.sh_  lanco  _/opt/etc/local.rc_  Antaŭ ol lanĉi  _/ipc/app/jco\_server_.   
_/ipc/app/jco\_server_  estas la ĉefa programo: i servas ambaŭ  _rtsp_ servilo, servilo  _http_, ... 

