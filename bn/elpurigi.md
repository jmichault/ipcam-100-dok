---
lang: bn
lang-niv: auto
lang-ref: 020-elpurigi
layout: page
title: 'শুদ্ধ করা'
---

মূল ফার্মওয়্যার সহ:

* প্রারম্ভের 5 মিনিটের মধ্যে `telnet IP 9527` (ব্যবহারকারী _root_, পাসওয়ার্ড (to 6 °) দিয়ে ক্যামেরায় লগ ইন করুন।


* সংযোগটি বন্ধ না করার জন্য `killall -9 auto_run.sh` টিপুন।



বিকল্প ফার্মওয়্যার সহ:

* ইন্টারনেট ইন্টারফেসের এসএসএইচ পরিষেবা চালু করুন


* ক্যামেরাটি সংযুক্ত করুন `ssh IP` (ব্যবহারকারী _root_, পাসওয়ার্ড _ismart12_)।



তারপরে, ফার্মওয়্যার যাই হোক না কেন:

* ক্যামেরাটির "gdbserver"শুরু করুন, উদাঃ :  


     `/opt/media/mmcblk0p1/bin/gdbserver localhost:2000 /opt/media/mmcblk0p1/bin/motor`
* কম্পিউটারে জিডিবি শুরু করুন, উদাহরণস্বরূপ:

    ```
    cd programada_medio/toolchain
    bin/mips-linux-uclibc-gnu-gdb ../fontoj/motor/motor 
    target remote 192.168.xxx.xxx:2000
    handle SIGPIPE nostop
    handle SIG32 nostop
    break xxx
    continue 
    ```



