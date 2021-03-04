---
lang: ru
lang-niv: auto
lang-ref: 020-elpurigi
layout: page
title: Очистить
---

с оригинальной прошивкой:

* Войдите в камеру с помощью `telnet IP 9527` (пользователя _root_, пароля _jco66688_) в течение 5 минут после запуска.


* Нажмите `killall -9 auto_run.sh` , чтобы не закрывать соединение.



с альтернативной прошивкой:

* Запустить telnet-сервис веб-интерфейса


* Войдите в камеру, используя `telnet IP` (пользователя _root_, пароль _ismart12_).


* Нажмите `killall -9 run.sh system-emergency-telnet` , чтобы не закрывать соединение.



Тогда какой бы прошивкой:

* start "gdbserver"камеры, например :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* запустить GDB на компьютере, например:

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



