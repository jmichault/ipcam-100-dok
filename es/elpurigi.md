---
lang: es
lang-niv: auto
lang-ref: 020-elpurigi
layout: page
title: Purificar
---

con firmware original:

* Inicie sesión en la cámara con `telnet IP 9527` (usuario _root_, contraseña _jco66688_) dentro de los 5 minutos posteriores al inicio.


* Presione `killall -9 auto_run.sh` para evitar cerrar la conexión.



con firmware alternativo:

* Inicie el servicio telnet de la interfaz web


* Inicie sesión en la cámara con `telnet IP` (usuario _root_, contraseña _ismart12_).


* Presione `killall -9 run.sh system-emergency-telnet` para evitar cerrar la conexión.



Entonces, sea cual sea el firmware:

* iniciar "gdbserver"de la cámara, p. ej. :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* inicie gdb en la computadora, por ejemplo:

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



