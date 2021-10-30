---
lang: bn
lang-niv: auto
lang-ref: 010-alternativa_firmvaro
layout: page
title: 'বিকল্প ফার্মওয়্যার'
---

# স্টার্ট আপ

* ইনস্টলেশনটি ফর্মওয়্যারটি প্রবর্তন করে _/opt/etc/local.rc_ফাইল তৈরি করে।


* _local.rc_ এসডি কার্ড থেকে _run.sh_ চালু করে।



# _run.sh_

  * নেটওয়ার্কটি সংযোগ বিচ্ছিন্ন করুন


  *  _jco_সার্ভার_ এবং _autorun.sh_বন্ধ করুন।


  * নিষ্ক্রিয় _/dev/watchdog_ এবং _/dev/watchdog0_


  * এলইডি এবং মোটর সূচনা হয়


  * প্রয়োজনে ডিরেক্টরি ইত্যাদি সূচনা করুন


  *  _/bin/busybox_ , _/etc_ এবং _/root_ এসডি কার্ডে পুনঃনির্দেশ করুন।


  * ডিফল্ট _CRONTAB_ প্রয়োজন হলে


  *  _config/autostart_)এ পরিষেবা (শুরু করুন


  *  _config/userscripts_)এ স্ক্রিপ্টগুলি (ব্যবহার শুরু করুন


