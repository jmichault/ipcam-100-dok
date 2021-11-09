---
lang: it
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'Funzionamento del firmware originale'
---

Il firmware è composto da 6 vandali:  

| Partizione |. Tipo | Role |.  
 | ----------- | ------------------------ |. -------------- |  
 |   _mtdblock0_   |   _u-boot_                 | Avvio |.  
 |   _mtdblock1_   | Testo |. Impostazioni |.  
 |   _mtdblock2_   |   _u-boot legacy uImage_   | Core   _linux_   |  
 |   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          | . 

Il primo programma eseguito è   _/linuxrc_.    
 lancia   _/etc/init.d/rcS_.    
 _/etc/init.d/rcS_   Avvia   _/ipc/etc/auto\_run.sh_.    
 _/ipc/etc/auto\_run.sh_   LANCO   _/opt/etc/local.rc_   Prima del lancio   _/ipc/app/jco\_server_.    
 _/ipc/app/jco\_server_   è il programma principale: Serve sia   _rtsp_  Server, Server   _http_, ...  

