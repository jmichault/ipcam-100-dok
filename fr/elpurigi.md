---
lang: fr
lang-niv: fonto
lang-ref: 060-elpurigi
layout: page
title: 'Déboguer'
---

avec le micrologiciel d'origine:

* Connectez-vous à la caméra via `telnet IP 9527` (utilisateur _root_, mot de passe _jco66688_) dans les 5 minutes après le démarrage.
* Faites `killall -9 auto_run.sh` pour éviter de fermer la connexion.

avec le micrologiciel alternatif:

* Lancez le service ssh depuis l'interface web
* Connectez-vous à la caméra via `ssh IP` (utilisateur _root_, mot de passe _ismart12_).

Puis, quel que soit le micrologiciel :

* démarrer «gdbserver» depuis la caméra, par ex. :  
     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* démarrer gdb sur l'ordinateur, par exemple :

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



