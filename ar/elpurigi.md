---
lang: ar
lang-niv: auto
lang-ref: 020-elpurigi
layout: page
title: تنقية
---

مع البرنامج الثابت الأصلي:

* سجّل الدخول إلى الكاميرا باستخدام مستخدم `telnet IP 9527` ( _root_وكلمة مرور _jco66688_) في غضون 5 دقائق بعد بدء التشغيل.


* اضغط `killall -9 auto_run.sh` لتجنب إغلاق الاتصال.



مع البرامج الثابتة البديلة:

* إطلاق خدمة Telnet لواجهة الويب


* قم بتسجيل الدخول إلى الكاميرا باستخدام `telnet IP` (مستخدم _root_، كلمة مرور _ismart12_).


* اضغط `killall -9 run.sh system-emergency-telnet` لتجنب إغلاق الاتصال.



ثم مهما كانت البرامج الثابتة:

* بدء "gdbserver"للكاميرا ، على سبيل المثال :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* ابدأ gdb على الكمبيوتر ، على سبيل المثال:

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



