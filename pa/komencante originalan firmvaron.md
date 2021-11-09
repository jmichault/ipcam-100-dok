---
lang: pa
lang-niv: auto
lang-ref: 061-originala_firmvaro
layout: page
title: 'ਅਸਲ ਫਰਮਵੇਅਰ ਦਾ ਸੰਚਾਲਨ'
---

ਫਰਮਵੇਅਰ ਵਿੱਚ 6 ਵਾਂਡਸ ਹੁੰਦੇ ਹਨ:  

| ਭਾਗ ਟਾਈਪ ਕਰੋ | ਭੂਮਿਕਾ  
 | ----------- | ---------------------- | ------------- |  
 |   _mtdblock0_   |   _u-boot_                 | ਸ਼ੁਰੂ ਕਰਨ  
 |   _mtdblock1_   | ਪਾਠ ਸੈਟਿੰਗ |  
 |   _mtdblock2_   |   _u-boot legacy uImage_   | ਕੋਰ   _linux_   |  
 |   _mtdblock3_   |   _squashfs_               |   _/_             |  
 |   _mtdblock4_   |   _squashfs_               |   _/ipc_          |  
 |   _mtdblock5_   |   _jffs1_                  |   _/opt_          |  

ਚਲਾਇਆ ਗਿਆ ਪਹਿਲਾ ਪ੍ਰੋਗਰਾਮ   _/linuxrc_ ਹੈ.    
 ਉਸਨੇ ਲਾਂਚ ਕੀਤਾ   _/etc/init.d/rcS_.    
 _/etc/init.d/rcS_   ਲਾਂਚਾਂ   _/ipc/etc/auto\_run.sh_.    
 _/ipc/etc/auto\_run.sh_   LANCO   _/opt/etc/local.rc_     _/ipc/app/jco\_server_.    
 _/ipc/app/jco\_server_   ਮੁੱਖ ਪ੍ਰੋਗਰਾਮ ਹੈ: ਇਹ ਦੋਵੇਂ   _rtsp_  ਸਰਵਰ, ਸਰਵਰ   _http_, ... ) 

