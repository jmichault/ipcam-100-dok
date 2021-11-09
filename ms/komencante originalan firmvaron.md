---
lang: ms
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'Operasi firmware asal'
---

Firmware ini terdiri daripada 6 Vandals:  

| partition | menaip | peranan |  
 | ----------- | ---------------------- | ------------- |  
 |   _mtdblock0_   |   _u-boot_                 | bermula |  
 |   _mtdblock1_   | teks | tetapan |  
 |   _mtdblock2_   |   _u-boot legacy uImage_   | Core   _linux_   |  
 |   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

Program pertama yang dilaksanakan adalah   _/linuxrc_.    
 dia melancarkan   _/etc/init.d/rcS_.    
 _/etc/init.d/rcS_   Lancar   _/ipc/etc/auto\_run.sh_.    
 _/ipc/etc/auto\_run.sh_   Lanco   _/opt/etc/local.rc_   Sebelum melancarkan   _/ipc/app/jco\_server_.    
 _/ipc/app/jco\_server_   adalah program utama: ia menyajikan kedua-dua   _rtsp_  pelayan, pelayan   _http_, ...  

