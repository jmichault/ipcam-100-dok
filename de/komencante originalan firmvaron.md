---
lang: de
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'Betrieb der ursprünglichen Firmware'
---

Die Firmware besteht aus 6 Vandalen:  

| Partition | Typ | Rolle |  
 | ------------ | -------------------------------------- | -------------- |  
 |   _mtdblock0_   |   _u-boot_                 | Start |  
 |   _mtdblock1_   | Text | Einstellungen |  
 |   _mtdblock2_   |   _u-boot legacy uImage_   | Kern   _linux_   |  
 |   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

Das erste ausgeführte Programm ist   _/linuxrc_.    
 er startet   _/etc/init.d/rcS_.    
 _/etc/init.d/rcS_   startet   _/ipc/etc/auto\_run.sh_.    
 _/ipc/etc/auto\_run.sh_   LANCO   _/opt/etc/local.rc_   Vor dem Start   _/ipc/app/jco\_server_.    
 _/ipc/app/jco\_server_   ist das Hauptprogramm: Es dient sowohl   _rtsp_  -Server, Server   _http_, ...  

