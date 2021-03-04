---
lang: pa
lang-niv: auto
lang-ref: 099-alternativa_firmvaro
layout: page
title: 'ਵਿਕਲਪਿਕ ਫਰਮਵੇਅਰ'
---

# ਸ਼ੁਰੂ ਕਰਣਾ

* ਇੰਸਟਾਲੇਸ਼ਨ ਇੱਕ ਫਾਈਲ _/opt/etc/local.rc_ਬਣਾਉਂਦੀ ਹੈ ਜੋ ਅਸਲ ਫਰਮਵੇਅਰ ਲਾਂਚ ਕਰਦੀ ਹੈ.


* _local.rc_ ਨੇ SD ਕਾਰਡ ਤੋਂ _run.sh_ ਲਾਂਚ ਕੀਤਾ.



# _run.sh_

  * ਨੈਟਵਰਕ ਨੂੰ ਡਿਸਕਨੈਕਟ ਕਰੋ


  * ਸਟਾਪ _jco_ਸਰਵਰ_ ਅਤੇ _autorun.sh_.


  * ਅਯੋਗ _/dev/watchdog_ ਅਤੇ _/dev/watchdog0_


  * ਐਲ.ਈ.ਡੀ. ਅਤੇ ਮੋਟਰ ਚਾਲੂ ਹੋ ਜਾਂਦੇ ਹਨ


  * ਜੇ ਜਰੂਰੀ ਹੋਵੇ ਤਾਂ ਡਾਇਰੈਕਟਰੀ ਆਦਿ ਅਰੰਭ ਕਰੋ


  *  _/bin/busybox_ , _/etc_ ਅਤੇ _/root_ ਨੂੰ SD ਕਾਰਡ ਤੇ ਰੀਡਾਇਰੈਕਟ ਕਰਦਾ ਹੈ.


  * ਮੂਲ ਰੂਪ ਵਿੱਚ _CRONTAB_ ਜੇ ਜਰੂਰੀ ਹੋਵੇ


  * ਸੇਵਾ ਅਰੰਭ ਕਰੋ _crond_, ਨੈਟਵਰਕ, ਸੇਵਾ _ntpd_, ਵੈੱਬ ਸਰਵਿਸ


  *  _config/autostart_)ਵਿਚ ਸੇਵਾਵਾਂ (ਚਾਲੂ ਕਰੋ


  * ਸਕ੍ਰਿਪਟਾਂ ( _config/userscripts_)ਦੀ ਵਰਤੋਂ ਕਰਨਾ ਅਰੰਭ ਕਰੋ


