---
lang: ar
lang-niv: auto
lang-ref: 010-alternativa_firmvaro
layout: page
title: 'البرامج الثابتة البديلة'
---

# أبدء

* ينشئ التثبيت الملف _/opt/etc/local.rc_الذي يبدأ تشغيل البرنامج الثابت الأصلي.


* _local.rc_ تنطلق _run.sh_ من بطاقة SD.



# _run.sh_

  * افصل الشبكة


  * توقف الخادم _jco__ و _autorun.sh_.


  * يعطل _/dev/watchdog_ و _/dev/watchdog0_


  * تتم تهيئة المصابيح والمحرك


  * تهيئة الدليل وما إلى ذلك إذا لزم الأمر


  * يعيد التوجيه _/bin/busybox_ و _/etc_ و _/root_ إلى بطاقة SD.


  * افتراضي إلى _CRONTAB_ إذا لزم الأمر


  * بدء الخدمات (في _config/autostart_)


  * ابدأ باستخدام البرامج النصية (في _config/userscripts_)


