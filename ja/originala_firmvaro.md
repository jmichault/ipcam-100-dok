---
lang: ja
lang-niv: auto
lang-ref: 071-originala_firmvaro
layout: page
title: 元のファームウェア
---

# 開いているポート

TCP：80(HTTP)、443(HTPも！)、554(RTSP)、8004,8006,9527(、9999  
UDP：67(DHCP)、3702,8002,39642

ポート80：HTTP  
http：// IP：ログイン： _admin:_、パスワード： _admin_

ポート443：HTTP  
http：// IP：443：ログイン： _admin:_、パスワード： _admin_

ポート554：RTSP  
* 主流: 



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

ポート8004 :？ 、jcoによって開かれました_server



ポート8006 :？ 、jcoによって開かれました_server




ポート9527：Telnet  
`telnetd IP 9527` ：ログイン： _root_、パスワード： _jco66688_、5分間アクセス可能で、後に閉じます。  
5分後に切断しないでください： `killall -9 auto_run.sh`   
JCO_server : 
を停止する 
 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

ポート9999：カメラの制御に使用されます。例：

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67：udhcpdのオープン

UDP 3702：？ 、jcoによって開かれました_server




# 内部フラッシュメモリ
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


**注：libimp.soはT20用に提供されたものとは異なり、T20で提供されたものは適切ではありません。**

# GPIOポート

* motor.koによってブロックされたポート：18？ 38 39 40 41 47 48 49 60？


* audio.koによってブロックされたポート：63？


* ポート46 =赤外線LED。


* ポート52 =？


* ポート64 =？


* ポート81 =青色LED。



# コアレビュー：
*  情報： 
      `binwalk mtdblock2.bin`  
      *  結果： 
 10進数の16進数の説明 
--------------------------------------------------------------------------------
0 0x0 Uimageヘッダー、ヘッダーサイズ：64バイト、ヘッダーCRC：0x7b9DE864、作成：2019-06-22 02:41:00、画像サイズ：1466358バイト、日付アドレス：0x80010000、エントリポイント：0x80388340、データCRC：0xb83DCA15、 OS：Linux、CPU：MIPS、イメージタイプ：OSカーネルイメージ、圧縮タイプ：LZMA、イメージ名：  " Linux-3.10.14  __  ISVP  _turkey_  1.0  __]  "  
 64 0X40 LZMA圧縮データ、プロパティ：0x5d、ディクショナリサイズ：16777216バイト、圧縮サイズ：-1バイト 

*   mtdblock2データ抽出： 
      `tail -c+65  < mtdblock2.bin >mtdblock2.dataz`  
  *  コア抽出： 
  *   
 *  含まれているドライバーのリスト： 
      `strings kernel|grep "^drivers"`  
  < H21  > ソースファイルのリスト： 
      `strings kernel|grep "\.[cChTsS]$"`  
  *  シンボルリスト 
 https：/ / github.com/marin-m/vmlinux-to-elfはシンボルの検索に役立つはずですが、存在しません < H33  >  kallsymsから始めましょう _token_ 表：0x3AA1B4  
