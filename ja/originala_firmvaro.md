---
lang: ja
lang-niv: auto
lang-ref: 001-originala_firmvaro
layout: page
title: 元のファームウェア
---

フラッシュメモリは次のように分散されます：

スコア|説明|
--- | --- |
mtdblock0 | u-ブートローダー|
mtdblock1 |ブート構成|
mtdblock2 | u-boot継承uImage、linux-kernel |
mtdblock3 |カボチャ= / |
mtdblock4 | / ipcにマウントされたsquashfs |
mtdblock5 | jffs2、マウント/ opt |

u-boot (パーティションmtdblock0) は、カーネルをmtdblock2にロードします。  
u-bootローダーのデフォルトオプション：  
* bootargs = console = ttyS1,115200n8 mem = 43M @ 0x0 rmem = 21M @ 0x2B00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3


* bootcmd = sfプローブ; sf読み取り0x806000000x48000 0x280000;ブート0x80600000


* bootdelay = 1


* ボーレート= 115200


* 負荷\_eoo = 1


* ethaddr = 00：11：22：33：44：74


* ipaddr = 192.168.2.84


* serverip = 192.168.2.81


* Gatewayip = 192.168.2.1


* ネットマスク= 255.255.255.0



mtdblock1のオプション：
* ボーレート= 115200
* bootcmd = sfプローブ; sf読み取り0x806000000x48000 0x280000; bootm 0x80600000
* bootdelay = 1
* ethact = Jz4775-9161
* gatewayip = 192.168.2.1
* ipaddr = 192.168.2.84
* 負荷\_eoo = 1
* ネットマスク= 255.255.255.0
* serverip = 192.168.2.81
* stderr =シリーズ
* stdin =シリーズ
* stdout =シリーズ
* ethaddr =**:**:**:**:**:**
* デバイス\_id =***********
* devinfo = jcoxa***************************************************
* bootargs =コンソール= ttyS1,115200n8 mem = 42M @ 0x0 rmem = 22M @ 0x2A00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3 flash = SFセンサー= GC2053 maxheight = 1080デバイス\_id =*********** ethaddr =**:**:**:**:**:** devinfo = jcoxa*************************************************** cpu = T21 ddr = 64M mtdparts = jz\_sfc：256K @ 0K(sf-ブートローダー)、32K @ 256K(sf-bootenv)、1440K @ 288K(）sf-kernel)、832K @ 172 8K(sf-rootfs)、4928K @ 2560K(sf-ipcfs)、704K @ 7488 K(sf-miscfs)


Linuxバージョン：  
Linuxバージョン3.10.14\_\_isvp\_turkey\_1.0\_\_ (root@localhost.localdomain) (gccバージョン4.7.2 (Ingenic r2.3.3 2016.12) ) ＃3 PREEMPT Sat Jun 22 10:40:55 CST 2019


/の注目すべきファイル：
* _/bin/busybox_ : 
  *     [、 [[、ash、awk、base64、basename 、blockdev、bootchartd、bunzip2、bzcat、bzip2、cat、chmod、chown、cmp、cp、cut、date、dd、depmod、devmem、df、
  *     dhcprelay、diff、dirname、dmesg 、dnsdomainname、du、dumpleases、echo、egrep、expr、fdflush、fdformat、fdisk、fgrep、find、flash\_eraseall、
  *     grego、libera、fandilo、getty、grep 、gzip、halt、hd、head、hexdump、hostname、hwclock、ifconfig、init、insmod、iostat、kill、killall、klogd、less、
  *     linuxrc、ln、logger、login、logread 、ls、lsmod、md5sum、mdev、mesg、mkdir、mkdosfs、mkfs.vfat、mknod、mktemp、modinfo、modprobe、mount、
  *     montopunkto、mpstat、mv、nc、netstat、passwd 、ping、pmap、poweroff、powertop、printf、ps、pstree、pwd、pwdx、readahead、reboot、rev、rm、rmdir、
  *     rmmod、route、sed、sh、dormo、smemcap 、sort、stat、strings、swap、swap、sync、system、system、queue、tar on、screenshot、telnet、test、tftp、time、
  *     pause、top、touch、tr、true、tty、udhcpc、udhcpd、umount、unxz、unzip、uptime、users、usleep、 vi、volname、watch、wc、kiu、xargs、xz、
  *     xzcat

* / lib：標準ライブラリ。



 _/ipc_ の注目すべきファイル：
* _/ipc/app/jco\_server_
  * メインプログラム、サーバーhttp、rtsp、...
* _/ipc/drv_ ：Linuxドライバー
  * motor.ko
* _/ipc/lib_ ：ライブラリー
）  * libimp.so：biblioteko _ingenic_ _IMP_ ( _Ingenic Media Platform_ )


注：libimp.soはT20用に提供されたものとは異なり、T20で提供されたものは適切ではありません。
