---
lang: eo
lang-niv: auto
lang-ref: 060-elpurigi
layout: page
title: Elpurigi
---

kun originala firmvaro:

* Ensalutu ĉe la fotilo per `telnet IP 9527` (uzanto _root_, pasvorto _jco66688_) ene de 5 minutoj post ekfunkciigo.

* Premu `killall -9 auto_run.sh` por eviti fermi la konekton.


kun alternativa firmvaro:

* Lanĉu la SSH-servon de la interreta interfaco

* Konekti al la fotilo per `ssh IP` (uzanto _root_, pasvorto _ismart12_).


Tiam, kia ajn la firmvaro:

* starti "gdbserver" de la fotilo, ekz. :  

     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* startu gdb en la komputilo, ekzemple:

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



