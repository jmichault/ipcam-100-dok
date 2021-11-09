---
lang: zh
lang-niv: auto
lang-ref: 010-alternativa_firmvaro
layout: page
title: 备用固件
---

# 启动

* 安装过程将创建原始固件启动的文件 _/opt/etc/local.rc_。


* _local.rc_ 从SD卡启动 _run.sh_ 。



# _run.sh_

  * 断开网络连接


  * 停止 _jco_服务器_ 和 _autorun.sh_。


  * 停用 _/dev/watchdog_ 和 _/dev/watchdog0_


  * LED和电机已初始化


  * 如果需要，启动  _etc_  文件 


  * 将 _/bin/busybox_ ， _/etc_ 和 _/root_ 重定向到SD卡。


  * 如果需要，默认为 _CRONTAB_ 


  * 启动服务 (在 _config/autostart_)


  * 开始在 _config/userscripts_)中使用脚本 (


