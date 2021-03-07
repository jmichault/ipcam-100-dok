---
lang: ms
lang-niv: auto
lang-ref: 001-originala_firmvaro
layout: page
title: 'Firmware asal'
---

# pelabuhan terbuka

TCP: 80(http), 443(http juga!), 554(rtsp), 8004, 8006, 9527(telnet), 9999
UDP: 67(dhcp), 3702, 8002, 39642

port 80: http
http: // IP: log masuk: _admin:_, kata laluan: _admin_

port 443: http
http: // IP: 443: log masuk: _admin:_, kata laluan: _admin_

port 554: rtsp
* aliran utama: 

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

port 8004 :? , dibuka oleh jco_server



pelabuhan 8006:? , dibuka oleh jco_server




port 9527: telnet
`telnetd IP 9527` : log masuk: _root_, kata laluan: _jco66688_, boleh diakses selama 5 minit, ditutup selepas.
untuk tidak terputus selepas 5 minit: `killall -9 auto_run.sh`
untuk menghentikan jco_server : 
 
 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

port 9999: digunakan untuk mengawal kamera, contoh:

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67: terbuka udhcpd

UDP 3702:? , dibuka oleh jco_server




# memori kilat dalaman
Memori kilat diedarkan seperti berikut:

skor | keterangan |
--- | --- |
mtdblock0 | u-bootloader |
mtdblock1 | konfigurasi but |
mtdblock2 | u-boot warisan uImage, linux-kernel |
mtdblock3 | labu = / |
mtdblock4 | squashfs, dipasang pada / ipc |
mtdblock5 | jffs2, dipasang pada / opt |

u-boot (partition mtdblock0) memuatkan kernel ke dalam mtdblock2.  
pilihan lalai dalam pemuat u-boot:  
* bootargs = console = ttyS1,115200n8 mem = 43M @ 0x0 rmem = 21M @ 0x2B00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3


* bootcmd = sf siasatan; sf baca 0x80600000 0x48000 0x280000; bootm 0x80600000


* bootdelay = 1


* kadar baud = 115200


* muatan\_eoo = 1


* etaddr = 00: 11: 22: 33: 44: 74


* ipaddr = 192.168.2.84


* serverip = 192.168.2.81


* gatewayip = 192.168.2.1


* netmask = 255.255.255.0



pilihan dalam mtdblock1:
* baud rate = 115200
* bootcmd = sf probe; sf baca 0x80600000 0x48000 0x280000; bootm 0x80600000
* bootdelay = 1
* etact = Jz4775-9161
* gatewayip = 192.168.2.1
* ipaddr = 192.168.2.84
* muatan\_eoo = 1
* netmask = 255.255.255.0
* serverip = 192.168.2.81
* stderr = siri
* stdin = siri
* stdout = siri
* etaddr =**:**:**:**:**:**
* peranti\_id =***********
* devinfo = jcoxa***************************************************
* bootargs = konsol = ttyS1,115200n8 mem = 42M @ 0x0 rmem = 22M @ 0x2A00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3 flash = SF sensor = GC2053 maxheight = 1080 device\_id =*********** ethaddr =**:**:**:**:**:** devinfo = jcoxa*************************************************** cpu = T21 ddr = 64 juta bahagian = jz\_sfc: 256K @ 0K(sf-bootloader), 32K @ 256K(sf-bootenv), 1440K @ 288K() sf-kernel), 832K @ 172 8K(sf-rootfs), 4928K @ 2560K(sf-ipcfs), 704K @ 7488 K(sf-miscfs)


Versi Linux:  
Linux versi 3.10.14\_\_isvp\_turkey\_1.0\_\_ (root@localhost.localdomain) (versi gcc 4.7.2 (Ingenic r2.3.3 2016.12) ) # 3 PERMULAAN Sabtu 22 Jun 10:40:55 CST 2019


Fail terkenal dalam /:
* _/bin/busybox_ : 
  *     [, [[, abu, awk, base64, nama basen , blockdev, bootchartd, bunzip2, bzcat, bzip2, cat, chmod, chown, cmp, cp, cut, date, dd, depmod, devmem, df,
  *     dhcprelay, diff, dirname, dmesg , dnsdomainname, du, dumpleases, echo, egrep, expr, fdflush, fdformat, fdisk, fgrep, find, flash\_eraseall,
  *     grego, libera, fandilo, getty, grep , gzip, stop, hd, head, hexdump, hostname, hwclock, ifconfig, init, insmod, iostat, kill, killall, klogd, less,
  *     linuxrc, ln, logger, login, logread , ls, lsmod, md5sum, mdev, mesg, mkdir, mkdosfs, mkfs.vfat, mknod, mktemp, modinfo, modprobe, mount,
  *     montopunkto, mpstat, mv, nc, netstat, passwd , ping, pmap, poweroff, powertop, printf, ps, pstree, pwd, pwdx, readahead, reboot, rev, rm, rmdir,
  *     rmmod, route, sed, sh, dormo, smemcap , sort, stat, string, swap, swap, sync, system, system, queue, tar pada, tangkapan skrin, telnet, ujian, tftp, masa,
  *     jeda, teratas, sentuhan, tr, benar, tty, udhcpc, udhcpd, umount, unxz, unzip, uptime, pengguna, usleep, vi, nama panggilan, jam tangan, wc, kiu, xargs, xz,
  *     xzcat

* / lib: perpustakaan standard.



fail terkenal dalam _/ipc_ :
* _/ipc/app/jco\_server_
  * program utama, dibuat serentak pelayan http, rtsp, ...
* _/ipc/drv_ : pemacu linux
  * motor.ko
* _/ipc/lib_ : perpustakaan
)  * libimp.so: biblioteko _ingenic_ _IMP_ ( _Ingenic Media Platform_ )


**nota: libimp.so berbeza dari yang dihantar untuk T20, dan yang dihantar dengan T20 tidak sesuai.**

# Pelabuhan GPIO

* pelabuhan disekat oleh motor.ko: 18? 38 39 40 41 47 48 49 60?


* port disekat oleh audio.ko: 63?


* port 46 = LED inframerah.


* pelabuhan 52 =?


* port 64 =?


* port 81 = LED biru.




