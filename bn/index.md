---
lang: bn
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: উপস্থাপনা
---

এই প্রকল্পের উদ্দেশ্যটি এই ক্যামেরার জন্য একটি বিকল্প ফার্মওয়্যার তৈরি করা: 

চিহ্ন = _WIFI CARAM_  
মডেল: _WF-HD820-ZS_  
পার্থক্য: _1080P_

ইন্টারনেট ইন্টারফেসে প্রদর্শিত তথ্য:
```
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

প্রসেসর: _ingenic T21_
ভিডিও সেন্সর: _GC2053_

# বিকল্প ফার্মওয়্যার

## বিকল্প ফার্মওয়্যারের কাজ কী:

* _LAN_   এবং   _WLAN_  


* সার্ভার   _RTSP_   ডাবল স্ট্রিম:   _1920x1080 H264_   এবং   _640x360 MJPEG_   ডিফল্টরূপে। . 


* ভিজ্যুয়াল পরামিতি


* সার্ভার   _HTTP_  


* ইঞ্জিন নিয়ন্ত্রণ


* ইঞ্জিন ক্রমাঙ্কন


* সেটিংস   _PTZ_  


* ক্লায়েন্ট   _NTP_  


* পাসওয়ার্ডগুলি পরিচালনা করুন   _http_,   _rtsp_   এবং সিস্টেম পরিচালনা করুন। . 


* হোয়াইট LED নিয়ন্ত্রণ এবং আইআর  


* হোয়াইট LED কন্ট্রোল এবং আইআর   _ftp_ 


* হোয়াইট LED কন্ট্রোল এবং আইআর   _telnet_ 


* সার্ভার এবং ক্লায়েন্ট   _ssh_  


* গতি সনাক্তকরণ


* ইমেল প্রেরণ


* পাঠানো   _«telegram»_  


* স্বয়ংক্রিয় নাইট মোড  



## কি বিকল্প ফার্মওয়্যার মধ্যে বাহিত হয় না:

* শব্দ সিস্টেম


* _OSD_


* ফার্মওয়্যার আপডেট


* গতি সনাক্তকরণ_ir-cut_


* ইমেল প্রেরণ_mqtt_


* ক্লাউডে চালান চিত্র এবং ভিডিও  


* ইত্যাদি ...



## বিকল্প ফার্মওয়্যার ইনস্টল করা হচ্ছে

* মাইক্রোএসডি কার্ডের মূলটিতে [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) ফোল্ডারে সবকিছু অনুলিপি করুন।


* সম্ভবত নেটওয়ার্কটি সেট করুন ( _www/ipcam/config.dist/reto.conf_ 


* কার্ড   _microSD_   ক্যামেরাটিতে ঢোকান। . 


* আপনার স্থানীয় নেটওয়ার্কে ক্যামেরাটি সংযুক্ত করুন এবং ক্যামেরাটি চালু করুন।


* ক্যামেরা এর আইপি ঠিকানা খুঁজুন। আপনি ক্যামেরা ওয়াইফাই (SSID এ সংযোগ করতে পারেন: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_।


* ক্যামেরাটিতে সংযোগ করুন `telnet IP 9527` (ব্যবহারকারী _root_, পাসওয়ার্ড _jco66688_), ক্যামেরাতে ঘূর্ণায়মান হওয়ার 5 মিনিটের মধ্যে।


* লীগ হারানোর এড়াতে `killall -9 auto_run.sh` করা।


* ফারু `cd /opt/media/mmcblk0p1;./install.sh`


* রিবুট ক্যামেরা এখন:  


    * আপনি URL _https://IP_ (ব্যবহারকারী _admin_, পাসওয়ার্ড _ismart21_)সাথে সংযোগ করতে পারেন।


    * আপনি SSH (ব্যবহারকারী _admin_, পাসওয়ার্ড _ismart12_)সংযোগ করতে পারেন।


    * প্রাথমিক ভিডিও বর্তমান  _rtsp://admin:ismart21@IP/stream1_ এ অ্যাক্সেসযোগ্য। .


    * মাধ্যমিক ভিডিও প্রবাহ  _rtsp://admin:ismart21@IP/stream2_ এ অ্যাক্সেসযোগ্য। .


    *   ওয়াইফাই এপি মোড ডিফল্টরূপে সক্ষম করা হয়েছে:  
      **   ssid: <h2-xxxxx  
      **   WPA2 কী: ISMART21  
      **   আইপি ঠিকানা ক্যামেরা: 172.25.0.1  

## বিকল্প ফার্মওয়্যার আনইনস্টল করা:

* ডিফল্ট ইন্টারফেসের মাধ্যমে ক্যামেরার এসএসএইচ পরিষেবা চালু করুন)।


* ক্যামেরাটিতে লগইন করুন `ssh root@IP` (পাসওয়ার্ড _ismart12_)।


* ইন্টারনেট ইন্টারফেসের মাধ্যমে ক্যামেরা দিয়ে টেলনেট পরিষেবা শুরু করুন। `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* আপনি কেবল মাইক্রোএসডি কার্ডটি সরাতে পারেন।



# আকর্ষণীয় নথি

একটি প্রসেসরের সাথে সজ্জিত ক্যামেরাগুলির জন্য অনেক কাজ করা হয়েছে   _ingenic T20_   
  *   সংশোধিত ফার্মওয়্যার:   <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>  
 সংশোধিত ফার্মওয়্যারের উত্সগুলি:   <https://github.com/Dafang-Hacks/Main>  
  *   অন্যান্য ফার্মওয়্যার:   <https://github.com/openmiko/openmiko>  
  *   ফার্মওয়্যার পরিবর্তন না করে প্রোগ্রাম চালু করুন:   <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic-T20-P2P-camera-hacks>  

