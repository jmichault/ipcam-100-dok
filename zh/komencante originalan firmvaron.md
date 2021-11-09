---
lang: zh
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 原始固件的操作
---

固件由6个破坏者组成： 

|分区|类型|角色|  
 | ----------- | --------------------- | -------------- |  
 |   _mtdblock0_   |   _u-boot_                 |起点|  
 |   _mtdblock1_   |文本|设置|  
 |   _mtdblock2_   |   _u-boot legacy uImage_   |核心  _linux_   |  
 |   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

执行的第一个程序是  _/linuxrc_。    
他推出了  _/etc/init.d/rcS_。    
 _/etc/init.d/rcS_  启动  _/ipc/etc/auto\_run.sh_。    
 _/ipc/etc/auto\_run.sh_   Lanco   _/opt/etc/local.rc_  在启动  _/ipc/app/jco\_server_之前。    
 _/ipc/app/jco\_server_  是主程序：它提供  _rtsp_ 服务器，服务器  _http_，...  

