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
DeviceName: _INGENIC-V01_
DeviceModel: _IPCAM-100_
DeviceSN: _12345678901_
KernelVersion: _Thu Jul 9 15:46:54 CST 2015_
ServerVersion: _WS3.53.1243-20190717-DANALE-GEN_
WebVersion: _V2.3.4-20190709_
```

プロセッサー： _ingenic T21_
ビデオセンサー： _GC2053_

プロセッサー _ingenic T20_を搭載したカメラでは、多くの作業が行われています。
* 変更されたファームウェア： <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>
* ソースから変更されたファームウェア： <https://github.com/Dafang-Hacks/Main>
* その他のファームウェア <https://github.com / openmiko / openmiko>
* ファームウェアを変更せずにプログラムを起動する： <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic- T20 -P2Pカメラハック>

APIドキュメントはここで見ることができます：  
* [中国語のオリジナルバージョン](../zh/includes.zh/html/)


* [英語版](../en/includes.en/html/)


* [グーグル翻訳のフランス語版](../fr/includes.fr/html/)



# 代替ファームウェア

## 代替ファームウェアで機能するもの：

* LANおよびWLAN


* DRTTSPデュアルフローサーバー：デフォルトで1920 x 1080 H 264および640 x 360 MJPEG。


* 視覚的パラメータ


* HTTPサーバー


* エンジン制御


* エンジンキャリブレーション


* PTZ設定


* NTPクライアント


* httpアクセスのパスワード変更


* 青色LEDおよびIR制御


* FTPサーバー


* Telnetサーバー


* SSHサーバーとクライアント


* 動き検出


* メール送信



## 代替ファームウェアで機能しないもの：

* サウンドシステム


* _OSD_


* パスワード管理


* ファームウェアアップデート


* 自動夜間検出


* 動き検出_ir-cut_


* メールの送信_mqtt_


* など...



## 代替ファームウェアのインストール

* microSDカードのルートにある [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) フォルダーにすべてをコピーします。


* オプションでネットワークを構成します ( _config/staticip.conf_ 、 _config/resolv.conf_ 、 _config/wpa_supplicant.conf_ )


* microSDカードを挿入します。


* カメラをローカルネットワークに接続し、カメラの電源を入れます。


* カメラのIPアドレスを見つけます。カメラWiFi (SSIDに接続することもできます。 _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_。


* カメラで回転してから5分以内に、 `telnet IP 9527` (のユーザー _root_のユーザー _root_、パスワード _jco66688_)でカメラに接続します。


* リーグを失うことを避けるために `killall -9 auto_run.sh` を作ります。


* ファル `cd /opt/media/mmcblk0p1;./install.sh`


* URL _https://IP_ (ユーザー _admin_、パスワード _ismart21_)に接続できます。


* SSH (ユーザー _admin_、パスワード _ismart12_)で接続できます。


* プライマリビデオ電流は _rtsp://admin:ismart21@IP/stream1_でアクセス可能です。 （°3°3


* 二次ビデオ電流は _rtsp://admin:ismart21@IP/stream2_でアクセス可能です。 （°3°3



## 代替ファームウェアのアンインストール：

* インターネットインターフェイスを介してカメラでtelnetサービスを開始します。


* インターネットインターフェイスを介してカメラでtelnetサービスを開始します。 `telnet IP` 


* インターネットインターフェイスを介してカメラでtelnetサービスを開始します。 `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* microSDカードを取り外すこともできます。


