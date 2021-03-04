---
lang: pa
lang-niv: auto
lang-ref: 020-elpurigi
layout: page
title: ਸ਼ੁੱਧ
---

ਅਸਲ ਫਰਮਵੇਅਰ ਨਾਲ:

* ਸ਼ੁਰੂ ਹੋਣ ਤੋਂ 5 ਮਿੰਟ ਦੇ ਅੰਦਰ ( `telnet IP 9527` (ਉਪਭੋਗਤਾ _root_, ਪਾਸਵਰਡ _jco66688_) ਨਾਲ ਕੈਮਰੇ ਵਿੱਚ ਲੌਗ ਇਨ ਕਰੋ.


* ਕਨੈਕਸ਼ਨ ਬੰਦ ਕਰਨ ਤੋਂ ਬਚਣ ਲਈ `killall -9 auto_run.sh` ਦਬਾਓ.



ਵਿਕਲਪਕ ਫਰਮਵੇਅਰ ਦੇ ਨਾਲ:

* ਵੈਬ ਇੰਟਰਫੇਸ ਟੈਲਨੈੱਟ ਸੇਵਾ ਲਾਂਚ ਕਰੋ


*  `telnet IP` (ਉਪਭੋਗਤਾ _root_, ਪਾਸਵਰਡ _ismart12_)ਨਾਲ ਕੈਮਰਾ ਤੇ ਲੌਗ ਇਨ ਕਰੋ.


* ਕਨੈਕਸ਼ਨ ਬੰਦ ਕਰਨ ਤੋਂ ਬਚਣ ਲਈ `killall -9 run.sh system-emergency-telnet` ਦਬਾਓ.



ਫਿਰ, ਜੋ ਵੀ ਫਰਮਵੇਅਰ ਹੈ:

* ਕੈਮਰੇ ਦਾ ਸਟਾਰਟ "ਜੀਡੀਬਸਰਵਰ", ਉਦਾ. :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* ਕੰਪਿdਟਰ ਤੇ ਜੀਡੀਬੀ ਚਾਲੂ ਕਰੋ, ਉਦਾਹਰਣ ਵਜੋਂ:

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



