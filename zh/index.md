---
lang: zh
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: 介绍
---

该项目的目的是为此相机创建替代固件：（°1°1

标记= _WIFI CARAM_  
型号： _WF-HD820-ZS_  
区别： _1080P_

Internet界面中显示的信息：
```
DeviceName: INGENIC-V01
DeviceModel: IPCAM-100
DeviceSN: 12345678901
KernelVersion: Thu Jul 9 15:46:54 CST 2015
ServerVersion: WS3.53.1243-20190717-DANALE-GEN
WebVersion: V2.3.4-20190709
```

处理器： _ingenic T21_
视频传感器： _GC2053_

# 备用固件

## 在替代固件中有效的方法：

* _LAN_ 和 _WLAN_


* 服务器 (°1°双流： _1920x1080 H264_ 和 _640x360 MJPEG_ 默认情况下。  


* 视觉参数


* 服务器 _HTTP_


* 发动机控制


* 发动机校准


* 参数 _PTZ_（°3°3


* 客户 _NTP_（°3°3


* 密码管理 _http_， _rtsp_ 和系统。  


* 白色LED控制和IR


* 白色LED控制和IR _ftp_


* 白色LED控制和IR _telnet_


* 服务器和客户端 _ssh_（°3°3


* 移动侦测


* 发送电子邮件


* 发送 _«telegram»_


* 自动夜间政权



## 什么不是在替代固件中执行的：

* 音响系统


* _OSD_


* 固件更新


* 运动检测_ir-cut_


* 发送电子邮件_mqtt_


* 在云中发送图像和视频（°1°1


* 等...



## 安装备用固件

* 将所有内容复制到microSD卡根目录下的 [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) 文件夹中。


* 也许设置网络 ( _www/ipcam/config.dist/reto.conf_ ))


* 在相机中输入卡 _microSD_ 。  


* 将相机连接到本地网络，然后打开相机电源。


* 找到相机的IP地址。您还可以连接到相机WiFi (SSID： _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_。


* 通过 `telnet IP 9527` ( _root_，密码 _jco66688_)，在相机上旋转后的5分钟内连接到相机。


* 制作 `killall -9 auto_run.sh` 以避免失去联盟。


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* 相机简历，现在：（°1°1


    * 您可以连接到URL _https://IP_ (用户 _admin_，密码 _ismart21_)。


    * 您可以在SSH (用户 _admin_，密码 _ismart12_)中连接。


    * 初级视频电流可在 _rtsp://admin:ismart21@IP/stream1_上访问。 （°3°3


    * 辅助视频电流可在 _rtsp://admin:ismart21@IP/stream2_处访问。 （°3°3


（°1°1°1°1 WiFi AP模式默认激活：
    ** SSID：IPCAM100-XXXXXX
    ** WPA2键：ISMart21
相机的IP地址：172.25.0.1

## 卸载备用固件：

* 通过默认接口)在相机上启动SSH服务。


* 通过 `ssh root@IP` (密码 _ismart12_)登录相机。


* 通过互联网接口用摄像机启动telnet服务。 `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* 您也可以简单地卸下microSD卡。



# 有趣的文件

适用于配备处理器 _ingenic T20_ 的摄像机
* 修改固件： <https://github.com/ilílístotlyar/xiaomi-大丰 - 哈哈>>
修改固件的来源： <https://github.com/dafang-hacks/main>
17°) https://github.com/thatusenameanamexist/jco-pm203-fisheye-ininic-t20-p2p-camera-hacks>

