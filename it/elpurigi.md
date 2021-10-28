---
lang: it
lang-niv: auto
lang-ref: 020-elpurigi
layout: page
title: Purificare
---

con firmware originale:

* Accedi alla telecamera con `telnet IP 9527` (utente _root_, password _jco66688_) entro 5 minuti dall'avvio.


* Premere `killall -9 auto_run.sh` per evitare di chiudere la connessione.



con firmware alternativo:

* Avvia il servizio SSH dell'interfaccia Internet


* Collegare alla fotocamera da `ssh IP` (Utente _root_, password _ismart12_).



Quindi, qualunque sia il firmware:

* inizio "gdbserver"della telecamera, ad es. :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* avvia gdb sul computer, ad esempio:

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



