---
lang: de
lang-niv: auto
lang-ref: 060-elpurigi
layout: page
title: Reinigen
---

mit Original-Firmware:

* Melden Sie sich innerhalb von 5 Minuten nach dem Start mit dem Benutzer `telnet IP 9527` ( _root_und dem Kennwort _jco66688_) bei der Kamera an.


* Drücken Sie `killall -9 auto_run.sh` , um ein Schließen der Verbindung zu vermeiden.



mit alternativer Firmware:

* Starten Sie den SSH-Dienst der Internet-Schnittstelle


* Verbinden Sie sich mit der Kamera mit `ssh IP`  _root_ _root_, Passwort _ismart12_).



Dann, unabhängig von der Firmware:

* Start "gdbserver"der Kamera, z. :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`  
  *   GDB auf dem Computer starten, zum Beispiel:  

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```  



