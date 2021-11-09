---
lang: hi
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'मूल फर्मवेयर का संचालन'
---

फर्मवेयर में 6 वंडल होते हैं:  

| विभाजन | टाइप करें | भूमिका |  
 | ----------- | ---------------------- | ------------- |  
 |   _mtdblock0_   |   _u-boot_                 | शुरू करने |  
 |   _mtdblock1_   | पाठ | सेटिंग्स | <एच 10> |   _mtdblock2_   |   _u-boot legacy uImage_   | कोर   _linux_   |  
 |   _mtdblock3_   | <एच 20> |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

निष्पादित पहला प्रोग्राम   _/linuxrc_ है।    
 वह   _/etc/init.d/rcS_ लॉन्च करता है।    
 _/etc/init.d/rcS_   लॉन्च   _/ipc/etc/auto\_run.sh_।    
 _/ipc/etc/auto\_run.sh_   lanco   _/opt/etc/local.rc_     _/ipc/app/jco\_server_ लॉन्च करने से पहले।    
 _/ipc/app/jco\_server_   मुख्य कार्यक्रम है: यह   _rtsp_  सर्वर, सर्वर   _http_, ...  दोनों परोसता है 

