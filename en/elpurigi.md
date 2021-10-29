---
lang: en
lang-niv: auto
lang-ref: 060-elpurigi
layout: page
title: Purify
---

with original firmware:

* Log in to the camera with `telnet IP 9527` (user _root_, password _jco66688_) within 5 minutes after startup.


* Press `killall -9 auto_run.sh` to avoid closing the connection.



with alternative firmware:

* Launch the SSH service of the internet interface


* Connect to the camera by `ssh IP` (user _root_, password _ismart12_).



Then, whatever the firmware:

* start "gdbserver"of the camera, e.g. :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* start gdb on the computer, for example:

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



