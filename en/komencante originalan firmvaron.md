---
lang: en
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'Operation of the original firmware'
---

The firmware consists of 6 vandals:  

| Partition Type | Role  
 | ----------- | ---------------------- | ------------- |  
 |   _mtdblock0_   |   _u-boot_                 | Starting  
 |   _mtdblock1_   | Text Settings |  
 |   _mtdblock2_   |   _u-boot legacy uImage_   | Core   _linux_   |  
 |   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

The first program executed is   _/linuxrc_.    
 He launches   _/etc/init.d/rcS_.    
 _/etc/init.d/rcS_   launches   _/ipc/etc/auto\_run.sh_.    
 _/ipc/etc/auto\_run.sh_   Lanco   _/opt/etc/local.rc_   Before launching   _/ipc/app/jco\_server_.    
 _/ipc/app/jco\_server_   is the main program: It serves both   _rtsp_  server, server   _http_, ...  

