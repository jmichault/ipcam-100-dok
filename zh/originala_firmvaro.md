---
lang: zh
lang-niv: auto
lang-ref: 001-originala_firmvaro
layout: page
title: 原始固件
---

# 打开端口

TCP：80(HTTP)，443(HTP也！)，554(RTSP)，8004,8006,9527(，9999  
UDP：67(DHCP)，3702,8002,39642（°3°3

端口80：HTTP  
http：// ip：登录: _admin:_，密码： _admin_

端口443：HTTP  
http：// ip：443：登录: _admin:_，密码： _admin_

端口554：RTSP  
* 主电流： 



    ```
    IP=xxx.xxx.xxx.xxx
    ffplay -i rtsp://admin:admin@$IP/stream1
    ffplay -i rtsp://admin:admin@$IP/mpeg4/ch0/main/av_stream



    ```
* flux secondaire :



    ```
    IP=xxx.xxx.xxx.xxx
    ffplay -i rtsp://admin:admin@$IP/stream2
    ffplay -i rtsp://admin:admin@$IP/mpeg4/ch1/main/av_stream
    ````

端口8004 ：？ ，由jco打开_server



端口8006 ：？ ，由jco打开_server




端口9527：Telnet  
`telnetd IP 9527` ：登录: _root_，密码： _jco66688_，可访问5分钟，关闭后。  
5分钟后不断开： `killall -9 auto_run.sh`  （°4°4
停止JCO_server : 
 
 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

端口9999：用于控制摄像机，例如：

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67：打开udhcpd

UDP 3702 ：？ ，由jco打开_server




# 内部闪存
闪存的分配方式如下：

得分|描述|
--- | --- |
mtdblock0 | u-bootloader |
mtdblock1 |引导配置|
mtdblock2 | u-boot继承uImage，linux内核|
mtdblock3 |南瓜= / |
mtdblock4 | squashfs，安装在/ ipc上|
mtdblock5 | jffs2，安装在/ opt |

u-boot (分区mtdblock0) 将内核加载到mtdblock2中。  
u-boot加载器中的默认选项：  
* bootargs =控制台= ttyS1,115200n8 mem = 43M @ 0x0 rmem = 21M @ 0x2B00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3


* bootcmd = sf探针； sf读取0x80600000 0x48000 0x280000;引导0x80600000


* 引导延迟= 1


* 波特率= 115200


* 负载\_eoo = 1


* ethaddr = 00：11：22：33：44：74


* ipaddr = 192.168.2.84


* serverip = 192.168.2.81


* gatewayip = 192.168.2.1


* 网络掩码= 255.255.255.0



mtdblock1中的选项：
* 波特率= 115200
* bootcmd = SF探头; sf读取0x80600000 0x48000 0x280000; bootm 0x80600000
* bootdelay = 1
* ethact = Jz4775-9161
* gatewayip = 192.168.2.1
* ipaddr = 192.168.2.84
* 负载\_eoo = 1
* 网络掩码= 255.255.255.0
* serverip = 192.168.2.81
* stderr =系列
* stdin =系列
* stdout =系列
* ethaddr =**：**：**：**：**：**
* 设备\_id =***********
* devinfo = jcoxa***************************************************
* bootargs =控制台= ttyS1,115200n8 mem = 42M @ 0x0 rmem = 22M @ 0x2A00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3 flash = SF传感器= GC2053最大高度= 1080设备\_id =*********** ethaddr =**：**：**：**：**：** devinfo = jcoxa*************************************************** cpu = T21 ddr = 64M mtdparts = jz\_sfc：256K @ 0K(sf-bootloader)，32K @ 256K(sf-bootenv)，1440K @ 288K(））SF内核)，832K @ 172 8K(sf-rootfs)，4928K @ 2560K(sf-ipcfs)，704K @ 7488 K(sf-miscfs)


Linux版本：  
Linux版本3.10.14\_\_isvp\_火鸡\_1.0\_\_ (root@localhost.localdomain) (gcc版本4.7.2 (Ingenic r2.3.3 2016.12) ) ＃3 PREEMPT Sat Jun 22 10:40:55 CST 2019


值得注意的文件位于/：
* _/bin/busybox_ ： 
  *     [， [[，ash，awk，base64，basename ，blockdev，bootchartd，bunzip2，bzcat，bzip2，cat，chmod，chown，cmp，cp，cut，date，dd，depmod，devmem，df，
  *     dhcprelay，diff，dirname，dmesg ，dnsdomainname，du，dumpleases，echo，egrep，expr，fdflush，fdformat，fdisk，fgrep，查找，闪存\_擦除全部，
  *     grego，libera，fandilo，getty，grep ，gzip，halt，hd，head，hexdump，主机名，hwclock，ifconfig，init，insmod，iostat，kill，killall，klogd，更少，
  *     linuxrc，ln，记录器，登录名，logread ，ls，lsmod，md5sum，mdev，mesg，mkdir，mkdosfs，mkfs.vfat，mknod，mktemp，modinfo，modprobe，mount，
  *     montopunkto，mpstat，mv，nc，netstat，passwd ，ping，pmap，poweroff，powertop，printf，ps，pstree，pwd，pwdx，readahead，重启，rev，rm，rmdir，
  *     rmmod，路由，sed，sh，dormo，smemcap ，排序，状态，字符串，交换，交换，同步，系统，系统，队列，焦油上，屏幕快照，telnet，测试，tftp，时间，
  *     暂停，顶部，触摸，tr，true，tty，udhcpc，udhcpd，umount，unxz，unzip，正常运行时间，用户，usleep， vi，volname，watch，wc，kiu，xargs，xz
  *     xzcat

* / lib：标准库。



 _/ipc_ ：
* _/ipc/app/jco\_server_
  * 主程序中的重要文件，同时已创建服务器http，rtsp，...
* _/ipc/drv_ ：linux驱动程序
  * motor.ko
* _/ipc/lib_ ：库
）  * libimp.so：biblioteko _ingenic_ _IMP_ ( _Ingenic Media Platform_ )


**注：libimp.so与为T20交付的交付不一样，并且不随T20交付的交付。**

# GPIO端口

* 由motor.ko阻止的端口：18？ 38 39 40 41 47 48 49 60？


* 被audio.ko阻止的端口：63？


* 端口46 =红外LED。


* 端口52 =？


* 端口64 =？


* 端口81 =蓝色LED



# 核心审查：
（°1°1°的信息：
    `binwalk mtdblock2.bin`
    * 
--------------------------------------------------------------------------------
0 0x0 uimage标题，标题大小：64字节，标题CRC：0x7b9de864，创建：2019-06-22 02:41:00，图像尺寸：1466358字节，数据地址：0x80010000，入口点：0x80388340，CRC数据：0xB83DCA15， OS：Linux，CPU：MIPS，图像类型：OS内核图像，压缩类型：LZMA，图像名称： "Linux-3.10.14__。

（°1°1°1°1°提取MTDBLOCK2的数据：
    `tail -c+65  < mtdblock2.bin >mtdblock2.dataz`

核心提取：

（°5°5°6°13°13°13°导体列表：    `strings kernel|grep "^drivers"`

文件列表：
    `strings kernel|grep "\.[cChTsS]$"`









（°1°。到达
。
