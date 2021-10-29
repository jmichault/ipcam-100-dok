---
lang: ja
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: プレゼンテーション
---

このプロジェクトの目的は、このカメラの代替のファームウェアを作成することです。（°1°1

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

* _LAN_ と _WLAN_


* サーバー (°1°二重流： _1920x1080 H264_ 、 _640x360 MJPEG_ デフォルトで。  


* 視覚的パラメータ


* サーバー _HTTP_


* エンジン制御


* エンジンキャリブレーション


* パラメータ _PTZ_


* クライアント _NTP_（°3°3


* パスワード管理 _http_、 _rtsp_ およびシステム。  


* 白色LED制御とIR


* 白色LED制御とIR _ftp_


* 白色LED制御とIR _telnet_


* サーバーとクライアント _ssh_（°3°3


* 動き検出


* メール送信


*  _«telegram»_を送る


* 自動ナイトレジーム



## 代替ファームウェアでは何が実行されていないもの：

* サウンドシステム


* _OSD_


* ファームウェアアップデート


* 動き検出_ir-cut_


* メールの送信_mqtt_


* 画像とビデオをクラウドで送信する（°1°1


* など...



## 代替ファームウェアのインストール

* microSDカードのルートにある [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) フォルダーにすべてをコピーします。


* おそらくネットワーク ( _www/ipcam/config.dist/reto.conf_ )を設定します


* カメラにカード _microSD_ を入力してください。  


* カメラをローカルネットワークに接続し、カメラの電源を入れます。


* カメラのIPアドレスを見つけます。カメラWiFi (SSIDに接続することもできます。 _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_。


* カメラで回転してから5分以内に、 `telnet IP 9527` (のユーザー _root_のユーザー _root_、パスワード _jco66688_)でカメラに接続します。


* リーグを失うことを避けるために `killall -9 auto_run.sh` を作ります。


* ファル `cd /opt/media/mmcblk0p1;./install.sh`


* カメラが再開されます：（°1°1


    * URL _https://IP_ (ユーザー _admin_、パスワード _ismart21_)に接続できます。


    * SSH (ユーザー _admin_、パスワード _ismart12_)で接続できます。


    * プライマリビデオ電流は _rtsp://admin:ismart21@IP/stream1_でアクセス可能です。 （°3°3


    * 二次ビデオ電流は _rtsp://admin:ismart21@IP/stream2_でアクセス可能です。 （°3°3


（°1°1°1 WiFi APモードがデフォルトで活性化されます。
    ** SSID：IPCAM100-XXXXXX
    ** °5°）WPA2キー：ISMART21
カメラのIPアドレス：172.25.0.1

## 代替ファームウェアのアンインストール：

* デフォルトインターフェイス)を介してカメラ上のSSHサービスを起動します。


*  `ssh root@IP` (パスワード _ismart12_)でカメラにログインします。


* インターネットインターフェイスを介してカメラでtelnetサービスを開始します。 `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* microSDカードを取り外すこともできます。



# 興味深い文書

プロセッサ _ingenic T20_ を搭載したカメラ用の多くの作業が行われました。
* 修正ファームウェア： <https://github.com/ilílístotlyar/xiaomi- DAFANG -HAK>>
修正ファームウェアのソース： <https://github.com/dafang-hacks/main>
）17°) HTTPS：//Github.com/ThatusEnameAnamexist/jco-pm203-fisheye-ininic-t20-p2p-カメラ - ハック>

