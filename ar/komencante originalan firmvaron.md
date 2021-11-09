---
lang: ar
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'تشغيل البرامج الثابتة الأصلية'
---

تتكون البرامج الثابتة من 6 مخربين:  

| التقسيم |. النوع |. الدور |  
 | ----------- |. ---------------------- | ------------- |.  
 |   _mtdblock0_   |   _u-boot_                 | بدءا من |.  
 |   _mtdblock1_   | نص | الإعدادات |  
 |   _mtdblock2_   |   _u-boot legacy uImage_   | الأساسية   _linux_   |  
 |   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

البرنامج الأول الذي تم تنفيذه هو   _/linuxrc_.    
 يطلق   _/etc/init.d/rcS_.    
 _/etc/init.d/rcS_   تطلق   _/ipc/etc/auto\_run.sh_.    
 _/ipc/etc/auto\_run.sh_   lanco   _/opt/etc/local.rc_   قبل إطلاق   _/ipc/app/jco\_server_.    
 _/ipc/app/jco\_server_   هو البرنامج الرئيسي: إنه يخدم كل من   _rtsp_  الخادم والخادم   _http_ ...  

