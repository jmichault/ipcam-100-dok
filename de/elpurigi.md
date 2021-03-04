---
lang: de
lang-niv: auto
lang-ref: 020-elpurigi
layout: page
title: Reinigen
---

mit Original-Firmware:

* Melden Sie sich innerhalb von 5 Minuten nach dem Start mit dem Benutzer `telnet IP 9527` ( _root_und dem Kennwort _jco66688_) bei der Kamera an.


* Drücken Sie `killall -9 auto_run.sh` , um ein Schließen der Verbindung zu vermeiden.



mit alternativer Firmware:

* Starten Sie den Webinterface-Telnet-Dienst.


* Melden Sie sich mit dem Benutzer `telnet IP` ( _root_und dem Passwort _ismart12_)bei der Kamera an.


* Drücken Sie `killall -9 run.sh system-emergency-telnet` , um ein Schließen der Verbindung zu vermeiden.



Dann, unabhängig von der Firmware:

* Start "gdbserver"der Kamera, z. :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* Starten Sie gdb auf dem Computer, zum Beispiel:

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



