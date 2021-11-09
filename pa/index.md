---
lang: pa
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: ਪੇਸ਼ਕਾਰੀ
---

ਇਸ ਪ੍ਰੋਜੈਕਟ ਦਾ ਉਦੇਸ਼ ਇਸ ਕੈਮਰੇ ਲਈ ਵਿਕਲਪਕ ਫਰਮਵੇਅਰ ਬਣਾਉਣਾ ਹੈ:

ਨਿਸ਼ਾਨ = _WIFI CARAM_  
ਮਾਡਲ: _WF-HD820-ZS_  
ਅੰਤਰ: _1080P_

ਇੰਟਰਨੈੱਟ ਇੰਟਰਫੇਸ ਵਿੱਚ ਪ੍ਰਦਰਸ਼ਤ ਕੀਤੀ ਜਾਣਕਾਰੀ:
```
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

ਪ੍ਰੋਸੈਸਰ: _ingenic T21_
ਵੀਡੀਓ ਸੈਂਸਰ: _GC2053_

# ਵਿਕਲਪਿਕ ਫਰਮਵੇਅਰ

## ਵਿਕਲਪਿਕ ਫਰਮਵੇਅਰ ਵਿੱਚ ਕੀ ਕੰਮ ਕਰਦਾ ਹੈ:

* _LAN_   ਅਤੇ   _WLAN_  


* ਸਰਵਰ   _RTSP_   ਡਬਲ ਸਟ੍ਰੀਮ:   _1920x1080 H264_   ਅਤੇ   _640x360 MJPEG_   ਮੂਲ ਰੂਪ ਵਿੱਚ.  


* ਵਿਜ਼ੂਅਲ ਪੈਰਾਮੀਟਰ


* ਸਰਵਰ   _HTTP_  


* ਇੰਜਣ ਨਿਯੰਤਰਣ


* ਇੰਜਨ ਕੈਲੀਬ੍ਰੇਸ਼ਨ


* ਸੈਟਿੰਗਜ਼   _PTZ_  


* ਕਲਾਇੰਟ   _NTP_  


* ਪਾਸਵਰਡ ਪ੍ਰਬੰਧਿਤ ਕਰੋ   _http_   _rtsp_   ਅਤੇ ਸਿਸਟਮ.  


* ਵ੍ਹਾਈਟ ਐਲਈਡੀ ਕੰਟਰੋਲ ਅਤੇ IR  


* ਵ੍ਹਾਈਟ ਐਲਈਡੀ ਨਿਯੰਤਰਣ ਅਤੇ IR   _ftp_ 


* ਵ੍ਹਾਈਟ ਐਲਈਡੀ ਨਿਯੰਤਰਣ ਅਤੇ IR   _telnet_ 


* ਸਰਵਰ ਅਤੇ ਕਲਾਇੰਟ   _ssh_  


* ਮੋਸ਼ਨ ਖੋਜ


* ਈਮੇਲ ਭੇਜਣਾ


*   _«telegram»_   ਭੇਜ ਰਿਹਾ ਹਾਂ


* ਆਟੋਮੈਟਿਕ ਨਾਈਟ ਮੋਡ  



## ਵਿਕਲਪਕ ਫਰਮਵੇਅਰ ਵਿੱਚ ਕੀ ਨਹੀਂ ਕੀਤਾ ਗਿਆ:

* ਆਵਾਜ਼ ਸਿਸਟਮ


* _OSD_


* ਫਰਮਵੇਅਰ ਅਪਡੇਟ


* ਮੋਸ਼ਨ ਖੋਜ_ir-cut_


* ਈਮੇਲ ਭੇਜਣਾ_mqtt_


* ਬੱਦਲ ਵਿਚ ਸ਼ਿਪਮੈਂਟ ਦੀਆਂ ਤਸਵੀਰਾਂ ਅਤੇ ਵੀਡਿਓ  


* ਆਦਿ ...



## ਵਿਕਲਪਿਕ ਫਰਮਵੇਅਰ ਸਥਾਪਤ ਕਰਨਾ

* ਮਾਈਕ੍ਰੋ ਐਸਡੀ ਕਾਰਡ ਦੇ ਰੂਟ ਤੇ [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) ਫੋਲਡਰ ਵਿੱਚ ਹਰ ਚੀਜ਼ ਦੀ ਨਕਲ ਕਰੋ.


* ਸ਼ਾਇਦ ਨੈੱਟਵਰਕ (  ( _www/ipcam/config.dist/reto.conf_ )ਸੈੱਟ ਕਰੋ


* ਕੈਮਰੇ ਵਿੱਚ ਕਾਰਡ   _microSD_   ਪਾਓ.  


* ਕੈਮਰਾ ਨੂੰ ਆਪਣੇ ਸਥਾਨਕ ਨੈਟਵਰਕ ਨਾਲ ਕਨੈਕਟ ਕਰੋ ਅਤੇ ਕੈਮਰਾ ਚਾਲੂ ਕਰੋ.


* ਕੈਮਰਾ ਦਾ IP ਪਤਾ ਲੱਭੋ. ਤੁਸੀਂ ਕੈਮਰਾ ਵਾਈਫਾਈ (SSID ਨਾਲ ਜੁੜ ਸਕਦੇ ਹੋ: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


*  `telnet IP 9527`  `telnet IP 9527` ਦੁਆਰਾ ਕੈਮਰਾ ਨਾਲ ਜੁੜੋ(ਉਪਭੋਗਤਾ _root_, ਪਾਸਵਰਡ _jco66688_)ਕੈਮਰਾ 'ਤੇ ਘੁੰਮਾਉਣ ਤੋਂ ਬਾਅਦ 5 ਮਿੰਟ ਦੇ ਅੰਦਰ.


* ਲੀਗ ਨੂੰ ਗੁਆਉਣ ਤੋਂ ਬਚਣ ਲਈ `killall -9 auto_run.sh` ਬਣਾਓ.


* ਫਰੂ `cd /opt/media/mmcblk0p1;./install.sh`


* ਮੁੜ ਚਾਲੂ ਕੈਮਰਾ ਹੁਣ:  


    * ਤੁਸੀਂ URL _https://IP_ (ਉਪਭੋਗਤਾ(ਉਪਭੋਗਤਾ _admin_ਉਪਭੋਗਤਾ _admin_, ਪਾਸਵਰਡ _ismart21_).


    * ਤੁਸੀਂ ਐਸਐਸਐਚ (ਉਪਭੋਗਤਾ _admin_, ਪਾਸਵਰਡ _ismart12_)ਵਿੱਚ ਕਨੈਕਟ ਕਰ ਸਕਦੇ ਹੋ.


    * ਪ੍ਰਾਇਮਰੀ ਵੀਡੀਓ ਮੌਜੂਦਾ _rtsp://admin:ismart21@IP/stream1_ਤੇ ਪਹੁੰਚਯੋਗ ਹੈ.


    * ਸੈਕੰਡਰੀ ਵੀਡੀਓ ਮੌਜੂਦਾ _rtsp://admin:ismart21@IP/stream2_ਤੇ ਪਹੁੰਚਯੋਗ ਹੈ.


    *   WiFi AP ਮੋਡ ਮੂਲ ਰੂਪ ਵਿੱਚ ਸਮਰੱਥ ਕੀਤਾ ਗਿਆ ਹੈ:  
      **   SSID: IPcam100-XXXXX  
      **    
      **  )  

## ਵਿਕਲਪਕ ਫਰਮਵੇਅਰ ਨੂੰ ਅਣਇੰਸਟੌਲ ਕਰਨਾ:

* ਡਿਫਾਲਟ ਇੰਟਰਫੇਸ ਦੁਆਰਾ ਕੈਮਰੇ 'ਤੇ ਐਸਐਸਐਚ ਸੇਵਾ ਲਾਂਚ ਕਰੋ).


*  `ssh root@IP`  ( ਪਾਸਵਰਡ  _ismart12_) ਦੁਆਰਾ ਕੈਮਰਾ ਤੇ ਲੌਗਇਨ ਕਰੋ. 


* ਇੰਟਰਨੈਟ ਇੰਟਰਫੇਸ ਦੁਆਰਾ ਕੈਮਰਾ ਨਾਲ ਟੈਲਨੈੱਟ ਸੇਵਾ ਅਰੰਭ ਕਰੋ. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* ਤੁਸੀਂ ਆਸਾਨੀ ਨਾਲ ਮਾਈਕ੍ਰੋ ਐਸਡੀ ਕਾਰਡ ਨੂੰ ਵੀ ਹਟਾ ਸਕਦੇ ਹੋ.



# ਦਿਲਚਸਪ ਦਸਤਾਵੇਜ਼

ਇੱਕ ਪ੍ਰੋਸੈਸਰ   _ingenic T20_   
 ਸੋਧਿਆ ਫਰਮਵੇਅਰ:   <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>    <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic-T20-P2P-camera-hacks>   *   ਹੋਰ ਫਰਮਵੇਅਰ:   <https://github.com/openmiko/openmiko>  
  *   ਪ੍ਰੋਗਰਾਮਾਂ ਨੂੰ ਫਰਮਵੇਅਰ ਨੂੰ ਬਦਲਣ ਤੋਂ ਬਿਨਾਂ ਲਾਂਚ ਕਰੋ:   <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic-T20-P2P-camera-hacks>  

