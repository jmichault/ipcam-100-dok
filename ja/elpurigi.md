---
lang: ja
lang-niv: auto
lang-ref: 020-elpurigi
layout: page
title: 清める
---

元のファームウェアの場合：

* 起動後5分以内に `telnet IP 9527` (ユーザー _root_、パスワード _jco66688_) でカメラにログインします。


* 接続が閉じないようにするには、 `killall -9 auto_run.sh` を押します。



代替ファームウェアの場合：

* Webインターフェイスtelnetサービスを起動します


*  `telnet IP` (ユーザー _root_、パスワード _ismart12_)でカメラにログインします。


* 接続が閉じないようにするには、 `killall -9 run.sh system-emergency-telnet` を押します。



次に、ファームウェアが何であれ：

* カメラの開始 "gdbserver"、例： ：  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* コンピューターでgdbを起動します。例：

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



