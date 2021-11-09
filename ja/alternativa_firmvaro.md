---
lang: ja
lang-niv: auto
lang-ref: 010-alternativa_firmvaro
layout: page
title: 代替ファームウェア
---

# 起動

* インストールにより、元のファームウェアが起動するファイル _/opt/etc/local.rc_が作成されます。


* _local.rc_ SDカードから _run.sh_ 起動します。



# _run.sh_

  * ネットワークを切断します


  * サーバー_ と _autorun.sh_を停止します _jco_。


  *  _/dev/watchdog_ および _/dev/watchdog0_を非アクティブ化します


  * LEDとモーターが初期化されます


  * 必要に応じて  _etc_  ファイルを起動します 


  *  _/bin/busybox_ 、 _/etc_ 、 _/root_ をSDカードにリダイレクトします。


  * 必要に応じてデフォルトで _CRONTAB_ 


  *  _config/autostart_)でサービスを開始 (


  *  _config/userscripts_)でスクリプト (の使用を開始します


