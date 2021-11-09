---
lang: bn
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'মূল ফার্মওয়্যার অপারেশন'
---

ফার্মওয়্যার 6 ভন্ডাল ধারণ করে:  

| পার্টিশন | টাইপ করুন | ভূমিকা |  
 | ----------- | ---------------------- | ------------- |  
 |   _mtdblock0_   |   _u-boot_                 | শুরু |  
 |   _mtdblock1_   | টেক্সট | সেটিংস |  
 |   _mtdblock2_   |   _u-boot legacy uImage_   | কোর   _linux_   |  
 |   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

মৃত্যুদন্ড কার্যকর প্রথম প্রোগ্রাম   _/linuxrc_।    
 তিনি   _/etc/init.d/rcS_ চালু করেন।    
 _/etc/init.d/rcS_     _/ipc/etc/auto\_run.sh_ চালু করে।    
 _/ipc/etc/auto\_run.sh_   lanco   _/opt/etc/local.rc_     _/ipc/app/jco\_server_ চালু করার আগে।    
 _/ipc/app/jco\_server_   প্রধান প্রোগ্রাম: এটি   _rtsp_  সার্ভার, সার্ভার   _http_ উভয়ই সরবরাহ করে ...  

