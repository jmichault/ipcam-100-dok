---
lang: zh
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: 介绍
---

该项目的目标是为该相机创建替代固件：

标记= _WIFI CARAM_  
型号： _WF-HD820-ZS_  
区别： _1080P_

Internet界面中显示的信息：
```
DeviceName: _INGENIC-V01_
DeviceModel: _IPCAM-100_
DeviceSN: _12345678901_
KernelVersion: _Thu Jul 9 15:46:54 CST 2015_
ServerVersion: _WS3.53.1243-20190717-DANALE-GEN_
WebVersion: _V2.3.4-20190709_
```

处理器： _ingenic T21_
视频传感器： _GC2053_

配备处理器 _ingenic T20_的相机已经做了很多工作。
* 修改的固件： <https://github.com/EliasKotlyar/Xiaomi-Dafang-Hacks>
* 来源修改后的固件： <https://github.com/Dafang-Hacks/Main>
* 其他固件 <https://github.com / openmiko / openmiko>
* 在不更改固件的情况下启动程序： <https://github.com/ThatUsernameAlreadyExist/JCO-PM203-Fisheye-Ingenic- T20 -P2P相机镜头>

API文档可以在这里查看：  
* [中文原始版本](../zh/includes.zh/html/)


* [英文版](../en/includes.en/html/)


* [法语版本由Google翻译](../fr/includes.fr/html/)



# 备用固件

## 在替代固件中有效的方法：

* LAN和WLAN


* DRTTSP双流服务器：默认情况下，1920x1080 H264和640x360 MJPEG。


* 视觉参数


* HTTP服务器


* 发动机控制


* 发动机校准


* 云台设置


* NTP客户端


* http访问的密码更改


* 蓝色LED和IR控制


* ftp服务器


* Telnet服务器


* SSH服务器和客户端



## 在备用固件中什么不起作用：

* 音响系统


* _OSD_


* 密码管理。


* 固件更新


* 自动夜间检测


* 移动侦测


* 运动检测_ir-cut_


* 发送电子邮件


* 发送电子邮件_mqtt_


* 等...



## 相机准备

* 将相机连接到本地网络，然后打开相机电源。


* 查找摄像机的IP地址。


* 通过URL _"http://IP"_ (用户 _admin_，密码 _admin_)连接到摄像机


* 在选项卡 "音频和视频"中，将主流设置为720p，单击 "保存"。


* 您可以在选项卡 "网络"中设置电缆网络。



## 安装备用固件

* 将所有内容复制到microSD卡根目录下的 [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) 文件夹中。


* 可选配置网络 ( _config/staticip.conf_ ， _config/resolv.conf_ ， _config/wpa_请求方.conf_ )


* 插入microSD卡。


* 将相机连接到本地网络，然后打开相机电源。


* 以 `telnet IP 9527` (用户 _root_，密码 _jco66688_)登录到摄像机。


* 按 `killall -9 auto_run.sh` 避免关闭连接。


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* 您可以连接到URL _"https://IP"_ (用户 _admin_，密码 _jco66688_)。


* 初级视频电流可在 _rtsp://admin:ismart21@IP/stream1_上访问。 （°3°3


* 辅助视频电流可在 _rtsp://admin:ismart21@IP/stream2_处访问。 （°3°3



## 卸载备用固件：

* 通过互联网接口用摄像机启动telnet服务。


* 通过互联网接口用摄像机启动telnet服务。 `telnet IP` 


* 通过互联网接口用摄像机启动telnet服务。 `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* 您也可以简单地卸下microSD卡。


