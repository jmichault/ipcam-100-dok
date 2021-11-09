---
lang: ar
lang-niv: auto
lang-ref: 060-elpurigi
layout: page
title: تنقية
---

مع البرنامج الثابت الأصلي:

* سجّل الدخول إلى الكاميرا باستخدام مستخدم `telnet IP 9527` ( _root_وكلمة مرور _jco66688_) في غضون 5 دقائق بعد بدء التشغيل.


* اضغط `killall -9 auto_run.sh` لتجنب إغلاق الاتصال.



مع البرامج الثابتة البديلة:

* قم بتشغيل خدمة SSH لواجهة الإنترنت


* الاتصال بالكاميرا حسب  `ssh IP`  ( المستخدم  _root_، كلمة المرور  _ismart12_). 



ثم مهما كانت البرامج الثابتة:

* بدء "gdbserver"للكاميرا ، على سبيل المثال :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`  
  *   ابدأ GDB على الكمبيوتر، على سبيل المثال:  

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```  



