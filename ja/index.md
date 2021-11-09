---
lang: ja
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: プレゼンテーション
---

このプロジェクトの目的はこのカメラの代替ファームウェアを作成することです。

マーク= _WIFI CARAM_  
モデル： _WF-HD820-ZS_  
区別： _1080P_

インターネットインターフェースに表示される情報：
```
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

プロセッサー： _ingenic T21_
ビデオセンサー： _GC2053_

# 代替ファームウェア

## 代替ファームウェアで機能するもの：

* _LAN_  と  _WLAN_  


* サーバー  _RTSP_   Double Stream：  _1920x1080 H264_  と  _640x360 MJPEG_  デフォルトで。  


* 視覚的パラメータ


* サーバー  _HTTP_  


* エンジン制御


* エンジンキャリブレーション


* 設定  _PTZ_  


* クライアント  _NTP_  


* パスワードを管理します。  _http_、  _rtsp_  、およびシステム。  


* 白色LED制御とIR  


* 白色LED制御とIR   _ftp_ 


* 白色LED制御とIR   _telnet_ 


* サーバーとクライアント  _ssh_  


* 動き検出


* メール送信


* 送信  _«telegram»_  を送信します


* 自動ナイトモード 



## 代替ファームウェアでは何が実行されていないもの：

* サウンドシステム


* _OSD_


* ファームウェアアップデート


* 動き検出_ir-cut_


* メールの送信_mqtt_


* クラウド内の出荷イメージとビデオ 


* など...



## 代替ファームウェアのインストール

* microSDカードのルートにある [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) フォルダーにすべてをコピーします。


* おそらくネットワーク ( _www/ipcam/config.dist/reto.conf_ )を設定します


* カメラにカード  _microSD_  を挿入します。  


* カメラをローカルネットワークに接続し、カメラの電源を入れます。


* カメラのIPアドレスを見つけます。カメラWiFi (SSIDに接続することもできます。 _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_。


* カメラで回転してから5分以内に、 `telnet IP 9527` (のユーザー _root_のユーザー _root_、パスワード _jco66688_)でカメラに接続します。


* リーグを失うことを避けるために `killall -9 auto_run.sh` を作ります。


* ファル `cd /opt/media/mmcblk0p1;./install.sh`


* 今すぐカメラを再起動します。 


    * URL _https://IP_ (ユーザー _admin_、パスワード _ismart21_)に接続できます。


    * SSH (ユーザー _admin_、パスワード _ismart12_)で接続できます。


    * プライマリビデオ電流は _rtsp://admin:ismart21@IP/stream1_でアクセス可能です。 


    * 二次ビデオフローは _rtsp://admin:ismart21@IP/stream2_でアクセス可能です。 


    *   WiFi APモードはデフォルトで有効になっています。 
      **   SSID：IPCAM100-XXXXX  
      **   wpa2キー：ISMART21  
      **   IPアドレスカメラのIPアドレス：172.25.0.1  

## 代替ファームウェアのアンインストール：

* デフォルトインターフェイス)を介してカメラ上のSSHサービスを起動します。


*  `ssh root@IP` (パスワード _ismart12_)でカメラにログインします。


* インターネットインターフェイスを介してカメラでtelnetサービスを開始します。 `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* microSDカードを取り外すこともできます。



# 興味深い文書

修正ファームウェアのプロセッサを搭載したカメラの作業が行われています。  <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>  
  *    *  その他のファームウェア：   <https://github.com/openmiko/openmiko>  
  *  ファームウェアを変更せずにプログラムを起動します。  <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic-T20-P2P-camera-hacks>  

