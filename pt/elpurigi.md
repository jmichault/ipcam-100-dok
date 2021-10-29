---
lang: pt
lang-niv: auto
lang-ref: 060-elpurigi
layout: page
title: Purificar
---

com firmware original:

* Faça login na câmera com `telnet IP 9527` (usuário _root_, senha _jco66688_) dentro de 5 minutos após a inicialização.


* Pressione `killall -9 auto_run.sh` para evitar o fechamento da conexão.



com firmware alternativo:

* Inicie o serviço SSH da interface da Internet


* Conecte-se à câmera por `ssh IP` (usuário _root_, senha _ismart12_).



Então, seja qual for o firmware:

* start "gdbserver"da câmera, por ex. :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* inicie o gdb no computador, por exemplo:

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



