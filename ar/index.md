---
lang: ar
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: عرض
---

الغرض من هذا المشروع هو إنشاء برنامج ثابت بديل لهذه الكاميرا: 

علامة = _WIFI CARAM_  
الموديل: _WF-HD820-ZS_  
تمييز: _1080P_

المعلومات المعروضة في واجهة الإنترنت:
```
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

المعالج: _ingenic T21_
مستشعر الفيديو: _GC2053_

# البرامج الثابتة البديلة

## ما الذي يعمل في البرامج الثابتة البديلة:

* _LAN_   و   _WLAN_  


* الخادم   _RTSP_   دفق مزدوج:   _1920x1080 H264_   و   _640x360 MJPEG_   افتراضيا.  


* المعلمات المرئية


* الخادم   _HTTP_  


* التحكم في المحرك


* معايرة المحرك


* الإعدادات   _PTZ_  


* العميل   _NTP_  


* إدارة كلمات المرور   _http_،   _rtsp_   ونظامها.  


* سيطرة LED بيضاء و IR  


* التحكم الصمام الأبيض والأحرف IR   _ftp_ 


* التحكم الصمام الأبيض والأحرف IR   _telnet_ 


* الخادم والعميل   _ssh_  


* كشف الحركة


* إرسال بريد إلكتروني


* إرسال   _«telegram»_  


* الوضع الليلي التلقائي  



## ما لا يتم تنفيذه في البرامج الثابتة البديلة:

* نظام الصوت


* _OSD_


* تحديث البرنامج الثابت


* كشف الحركة_ir-cut_


* إرسال بريد إلكتروني_mqtt_


* شحنة الصور ومقاطع الفيديو في السحابة  


* إلخ ...



## تثبيت البرامج الثابتة البديلة

* انسخ كل شيء إلى المجلد [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) في جذر بطاقة microSD.


* ربما تعيين الشبكة ( _www/ipcam/config.dist/reto.conf_ )


* أدخل البطاقة   _microSD_   في الكاميرا.  


* قم بتوصيل الكاميرا بشبكتك المحلية وقم بتشغيل الكاميرا.


* ابحث عن عنوان IP للكاميرا. يمكنك أيضا الاتصال بالكاميرا WiFi (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* الاتصال بالكاميرا حسب  `telnet IP 9527`  ( المستخدم  _root_، كلمة المرور  _jco66688_)، في غضون 5 دقائق بعد التدوير على الكاميرا. 


* افعل  `killall -9 auto_run.sh`  لتجنب فقدان الرابط. 


* فارو `cd /opt/media/mmcblk0p1;./install.sh`


* إعادة تمهيد الكاميرا الآن:  


    * يمكنك الاتصال بعنوان URL  _https://IP_  ( المستخدم  _admin_، كلمة المرور  _ismart21_). 


    * يمكنك الاتصال في SSH  ( المستخدم  _admin_، كلمة المرور  _ismart12_). 


    * يمكن الوصول إلى Video Video الحالي في  _rtsp://admin:ismart21@IP/stream1_. 


    * يمكن الوصول إلى تدفق الفيديو الثانوي في  _rtsp://admin:ismart21@IP/stream2_. 


    *   يتم تمكين وضع WiFi AP بشكل افتراضي:  
      **   SSID: IPCAM100-XXXXX  
      **   مفتاح WPA2: ISMART21  
      **   عنوان IP للكاميرا: 172.25.0.1  

## إلغاء تثبيت البرامج الثابتة البديلة:

* قم بتشغيل خدمة SSH على الكاميرا من خلال الواجهة الافتراضية ). 


* تسجيل الدخول إلى الكاميرا حسب  `ssh root@IP`  ( كلمة المرور  _ismart12_). 


* ابدأ خدمة telnet بالكاميرا عبر واجهة الإنترنت. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* يمكنك أيضًا إزالة بطاقة microSD ببساطة.



# وثائق مثيرة للاهتمام

تم إجراء الكثير من العمل للكاميرات المزودة بمعالج   _ingenic T20_   
  *    *   تعديل البرامج الثابتة:   <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>  
  *   مصادر البرامج الثابتة المعدلة:   <https://github.com/Dafang-Hacks/Main>  
  *   البرامج الثابتة الأخرى:   <https://github.com/openmiko/openmiko>  
  *   قم بإطلاق برامج دون تغيير البرامج الثابتة:   <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic-T20-P2P-camera-hacks>  

