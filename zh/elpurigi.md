---
lang: zh
lang-niv: auto
lang-ref: 020-elpurigi
layout: page
title: 净化
---

使用原始固件：

* 启动后5分钟内，以 `telnet IP 9527` (用户 _root_，密码 _jco66688_) 登录到摄像机。


* 按 `killall -9 auto_run.sh` 避免关闭连接。



带有备用固件：

* 启动Web界面telnet服务


* 以 `telnet IP` (用户 _root_，密码 _ismart12_)登录到摄像机。


* 按 `killall -9 run.sh system-emergency-telnet` 避免关闭连接。



然后，无论使用哪种固件：

* 相机的启动 "gdbserver"，例如：  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* 在计算机上启动gdb，例如：

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



