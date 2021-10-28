---
lang: en
lang-niv: auto
lang-ref: 001-originala_firmvaro
layout: page
title: 'Original firmware'
---

# open ports

TCP: 80(HTTP), 443(HTP too!), 554(RTSP), 8004, 8006, 9527(, 9999  
UDP: 67(DHCP), 3702, 8002, 39642 (° 3 ° 3

Port 80: HTTP  
http: // IP: login: _admin:_, Password: _admin_

Port 443: HTTP  
http: // IP: 443: login: _admin:_, Password: _admin_

Port 554: RTSP  
* Main current: 



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

port 8004:? , opened by jco_server



port 8006:? , opened by jco_server




Port 9527: Telnet  
`telnetd IP 9527` : Login: _root_, Password: _jco66688_, accessible for 5 minutes, closed after.  
Not be disconnected after 5 minutes: `killall -9 auto_run.sh`  (° 4 ° 4
To stop JCO_server : 
 
 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

port 9999: used to control the camera, example:

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67: open of udhcpd

UDP 3702:? , opened by jco_server




# internal flash memory
Flash memory is distributed as follows:

score | description |
--- | --- |
mtdblock0 | u-bootloader |
mtdblock1 | boot config |
mtdblock2 | u-boot inheritance uImage, linux-kernel |
mtdblock3 | pumpkins = / |
mtdblock4 | squashfs, mounted on / ipc |
mtdblock5 | jffs2, mounted on / opt |

u-boot (partition mtdblock0) loads the kernel into mtdblock2.  
default options in u-boot loader:  
* bootargs = console = ttyS1,115200n8 mem = 43M @ 0x0 rmem = 21M @ 0x2B00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3


* bootcmd = sf probe; sf read 0x80600000 0x48000 0x280000; bootm 0x80600000


* bootdelay = 1


* baud rate = 115200


* loads\_eoo = 1


* ethaddr = 00: 11: 22: 33: 44: 74


* ipaddr = 192.168.2.84


* serverip = 192.168.2.81


* gatewayip = 192.168.2.1


* netmask = 255.255.255.0



options in mtdblock1:
* baud rate = 115200
* bootcmd = sf probe; sf read 0x80600000 0x48000 0x280000; bootm 0x80600000
* bootdelay = 1
* ethact = Jz4775-9161
* gatewayip = 192.168.2.1
* ipaddr = 192.168.2.84
* loads\_eoo = 1
* netmask = 255.255.255.0
* serverip = 192.168.2.81
* stderr = series
* stdin = series
* stdout = series
* ethaddr =**:**:**:**:**:**
* device\_id =***********
* devinfo = jcoxa***************************************************
* bootargs = console = ttyS1,115200n8 mem = 42M @ 0x0 rmem = 22M @ 0x2A00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3 flash = SF sensor = GC2053 maxheight = 1080 device\_id =*********** ethaddr =**:**:**:**:**:** devinfo = jcoxa*************************************************** cpu = T21 ddr = 64M mtdparts = jz\_sfc: 256K @ 0K(sf-bootloader), 32K @ 256K(sf-bootenv), 1440K @ 288K() sf-kernel), 832K @ 172 8K(sf-rootfs), 4928K @ 2560K(sf-ipcfs), 704K @ 7488 K(sf-miscfs)


Linux version:  
Linux version 3.10.14\_\_isvp\_turkey\_1.0\_\_ (root@localhost.localdomain) (gcc version 4.7.2 (Ingenic r2.3.3 2016.12) ) # 3 PREEMPT Sat Jun 22 10:40:55 CST 2019


Notable files in /:
* _/bin/busybox_ : 
  *     [, [[, ash, awk, base64, basename , blockdev, bootchartd, bunzip2, bzcat, bzip2, cat, chmod, chown, cmp, cp, cut, date, dd, depmod, devmem, df,
  *     dhcprelay, diff, dirname, dmesg , dnsdomainname, du, dumpleases, echo, egrep, expr, fdflush, fdformat, fdisk, fgrep, find, flash\_eraseall,
  *     grego, libera, fandilo, getty, grep , gzip, halt, hd, head, hexdump, hostname, hwclock, ifconfig, init, insmod, iostat, kill, killall, klogd, less,
  *     linuxrc, ln, logger, login, logread , ls, lsmod, md5sum, mdev, mesg, mkdir, mkdosfs, mkfs.vfat, mknod, mktemp, modinfo, modprobe, mount,
  *     montopunkto, mpstat, mv, nc, netstat, passwd , ping, pmap, poweroff, powertop, printf, ps, pstree, pwd, pwdx, readahead, reboot, rev, rm, rmdir,
  *     rmmod, route, sed, sh, dormo, smemcap , sort, stat, strings, swap, swap, sync, system, system, queue, tar on, screenshot, telnet, test, tftp, time,
  *     pause, top, touch, tr, true, tty, udhcpc, udhcpd, umount, unxz, unzip, uptime, users, usleep, vi, volname, watch, wc, kiu, xargs, xz,
  *     xzcat

* / lib: standard libraries.



notable files in _/ipc_ :
* _/ipc/app/jco\_server_
  * main program, made simultaneously server http, rtsp, ...
* _/ipc/drv_ : linux drivers
  * motor.ko
* _/ipc/lib_ : libraries
)  * libimp.so: biblioteko _ingenic_ _IMP_ ( _Ingenic Media Platform_ )


**note: libimp.so differs from the one delivered for the T20, and the one delivered with the T20 is not suitable.**

# GPIO ports

* ports blocked by motor.ko: 18? 38 39 40 41 47 48 49 60?


* ports blocked by audio.ko: 63?


* port 46 = infrared LEDs.


* port 52 =?


* port 64 =?


* port 81 = blue LEDs.



# Core review:
(° 1 ° 1 ° Information:
    `binwalk mtdblock2.bin`
    * 
--------------------------------------------------------------------------------
0 0x0 UIMAGE Header, Header Size: 64 bytes, Header CRC: 0x7b9de864, Created: 2019-06-22 02:41:00, Image Size: 1466358 bytes, Data Address: 0x80010000, Entrance point: 0x80388340, CRC data: 0xb83dca15,

(° 1 ° 1 ° 1 ° Extraction of data of Mtdblock2:
    `tail -c+65  < mtdblock2.bin >mtdblock2.dataz`

Core extraction:

(° 5 ° 5 ° 6 ° 13 ° 13 ° List of conductors included:    `strings kernel|grep "^drivers"`

List of files:
    `strings kernel|grep "\.[cChTsS]$"`









(° 1 °.
