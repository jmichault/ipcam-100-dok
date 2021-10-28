---
lang: hi
lang-niv: auto
lang-ref: 020-elpurigi
layout: page
title: शुद्ध
---

मूल फर्मवेयर के साथ:

* स्टार्टअप के बाद 5 मिनट के भीतर `telnet IP 9527` (उपयोगकर्ता _root_, पासवर्ड _jco66688_) के साथ कैमरे में लॉग इन करें।


* कनेक्शन बंद करने से बचने के लिए `killall -9 auto_run.sh` दबाएँ।



वैकल्पिक फर्मवेयर के साथ:

* इंटरनेट इंटरफ़ेस (° ° 0001 डिग्री) की एसएसएच सेवा लॉन्च करें


* कैमरे से (° 000 0001 डिग्री) (° 0003 डिग्री) उपयोगकर्ता (° 000 0004 डिग्री), पासवर्ड _ismart12_)द्वारा कनेक्ट करें।



फिर, जो भी फर्मवेयर:

* कैमरे का प्रारंभ "gdbserver":  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* कंप्यूटर पर gdb शुरू करते हैं, उदाहरण के लिए:

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



