---
lang: hi
lang-niv: auto
lang-ref: 099-alternativa_firmvaro
layout: page
title: 'वैकल्पिक फर्मवेयर'
---

# चालू होना

* स्थापना फ़ाइल _/opt/etc/local.rc_बनाता है, जिसे मूल फर्मवेयर द्वारा लॉन्च किया जाता है।


* _local.rc_ एसडी कार्ड से _run.sh_ लॉन्च होता है।



# _run.sh_

  * डिस्कनेक्ट नेटवर्क


  * रोक _jco_सर्वर_ और _autorun.sh_।


  * निष्क्रिय _/dev/watchdog_ और _/dev/watchdog0_


  * एल ई डी और मोटर को इनिशियलाइज़ करता है


  * यदि आवश्यक हो तो निर्देशिका आदि को आरंभ करें


  * एसडी कार्ड में रीडायरेक्ट _/bin/busybox_ , _/etc_ और _/root_ ।


  * डिफ़ॉल्ट _CRONTAB_ आवश्यक है


  * प्रारंभ सेवा _crond_, नेटवर्क, सेवा _ntpd_, वेब सेवा


  * आरंभ सेवाएं ( _config/autostart_)


  * लिपियों ( _config/userscripts_)का उपयोग करना शुरू करें


