---
lang: ja
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 元のファームウェアの操作
---

ファームウェアは6つの破壊者で構成されています： 

| ..パーティション|タイプ| ..役割|  
 | ----------- | --------------------- ------------- |  
 |   _mtdblock0_   |   _u-boot_                 |起動|  
 |   _mtdblock1_   |テキスト|設定|  
 |   _mtdblock2_   | ..   _u-boot legacy uImage_   |コア  _linux_   |  
 | ..   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

実行された最初のプログラムは  _/linuxrc_です。    
彼は  _/etc/init.d/rcS_を起動します。    
 _/etc/init.d/rcS_  は  _/ipc/etc/auto\_run.sh_を起動します。   _/ipc/app/jco\_server_を発射する前に、_/ipc/etc/auto\_run.sh_   LANCO   _/opt/etc/local.rc_  。    
 _/ipc/app/jco\_server_  はメインプログラムです：それは  _rtsp_  Server、Server   _http_、... の両方に役立ちます。 

