---
lang: ms
lang-niv: auto
lang-ref: 060-elpurigi
layout: page
title: Bersuci
---

dengan firmware asal:

* Log masuk ke kamera dengan pengguna `telnet IP 9527` ( _root_, kata laluan _jco66688_) dalam masa 5 minit selepas permulaan.


* Tekan `killall -9 auto_run.sh` untuk mengelakkan penutupan sambungan.



dengan firmware alternatif:

* Lancarkan perkhidmatan SSH antara muka Internet


* Sambungkan ke kamera dengan `ssh IP` (, kata laluan _root_, kata laluan _ismart12_).



Kemudian, apa sahaja firmware:

* mula "gdbserver"kamera, mis. :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`  
  *   Mula GDB di komputer, sebagai contoh:  

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```  



