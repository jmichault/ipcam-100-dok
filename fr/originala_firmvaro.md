---
lang: fr
lang-niv: fonto
lang-ref: 001-originala_firmvaro
layout: page
title: 'Micrologiciel originel'
---

# ports ouverts

TCP : 80(http), 443(http aussi !), 554(rtsp), 8004, 8006, 9527(telnetd), 9999  
UDP : 67(dhcp), 3702, 8002, 39642

port 80 : http  
http://IP : login : _admin:_, mot de passe : _admin_

port 443 : http  
http://IP:443 : login : _admin:_, mot de passe : _admin_

port 554 : rtsp  
* flux principal : 

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

port 8004 : ? , ouvert par jco_server

port 8006 : ? , ouvert par jco_server


port 9527 : telnet  
`telnetd IP 9527` : login : _root_, mot de passe : _jco66688_, accessible pendant 5 minutes, fermé après.  
pour ne pas être déconnecté au bout des 5 minutes : `killall -9 auto_run.sh`  
pour arrêter jco_server : 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

port 9999 : permet de contrôler la caméra, exemple :

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67 : ouvert par udhcpd

UDP 3702 : ? , ouvert par jco_server


# la mémoire flash interne
La mémoire flash est partitionnée comme suit :

partition| description|
---|---|
mtdblock0 | u-boot loader|
mtdblock1 | config de boot|
mtdblock2 | u-boot legacy uImage, noyau linux|
mtdblock3 | squashfs = /|
mtdblock4 | squashfs, monté sur /ipc|
mtdblock5 | jffs2, monté sur /opt|

u-boot (partition mtdblock0) charge le noyau en mtdblock2.  
options par défaut dans le u-boot loader:  
* bootargs=console=ttyS1,115200n8 mem=43M@0x0 rmem=21M@0x2B00000 init=/linuxrc rootfstype=squashfs root=/dev/mtdblock3
* bootcmd=sf probe;sf read 0x80600000 0x48000 0x280000; bootm 0x80600000
* bootdelay=1
* baudrate=115200
* loads\_echo=1
* ethaddr=00:11:22:33:44:74
* ipaddr=192.168.2.84
* serverip=192.168.2.81
* gatewayip=192.168.2.1
* netmask=255.255.255.0

options dans mtdblock1 :
* baudrate=115200
* bootcmd=sf probe;sf read 0x80600000 0x48000 0x280000; bootm 0x80600000
* bootdelay=1
* ethact=Jz4775-9161
* gatewayip=192.168.2.1
* ipaddr=192.168.2.84
* loads\_echo=1
* netmask=255.255.255.0
* serverip=192.168.2.81
* stderr=serial
* stdin=serial
* stdout=serial
* ethaddr=**:**:**:**:**:**
* device\_id=***********
* devinfo=jcoxa***************************************************
* bootargs=console=ttyS1,115200n8 mem=42M@0x0 rmem=22M@0x2A00000 init=/linuxrc rootfstype=squashfs root=/dev/mtdblock3 flash=SF sensor=GC2053 maxheight=1080 device\_id=*********** ethaddr=**:**:**:**:**:** devinfo=jcoxa*************************************************** cpu=T21 ddr=64M mtdparts=jz\_sfc:256K@0K(sf-bootloader),32K@256K(sf-bootenv),1440K@288K(sf-kernel),832K@1728K(sf-rootfs),4928K@2560K(sf-ipcfs),704K@7488K(sf-miscfs)


version linux :  
Linux version 3.10.14\_\_isvp\_turkey\_1.0\_\_ (root@localhost.localdomain) (gcc version 4.7.2 (Ingenic r2.3.3 2016.12) ) #3 PREEMPT Sat Jun 22 10:40:55 CST 2019


fichiers notables dans / :
* _/bin/busybox_ : 
  *     [, [[, ash, awk, base64, basename, blockdev, bootchartd, bunzip2, bzcat, bzip2, cat, chmod, chown, cmp, cp, cut, date, dd, depmod, devmem, df,
  *     dhcprelay, diff, dirname, dmesg, dnsdomainname, du, dumpleases, echo, egrep, expr, fdflush, fdformat, fdisk, fgrep, find, flash\_eraseall,
  *     flock, free, fuser, getty, grep, gzip, halt, hd, head, hexdump, hostname, hwclock, ifconfig, init, insmod, iostat, kill, killall, klogd, less,
  *     linuxrc, ln, logger, login, logread, ls, lsmod, md5sum, mdev, mesg, mkdir, mkdosfs, mkfs.vfat, mknod, mktemp, modinfo, modprobe, mount,
  *     mountpoint, mpstat, mv, nc, netstat, passwd, ping, pmap, poweroff, powertop, printf, ps, pstree, pwd, pwdx, readahead, reboot, rev, rm, rmdir,
  *     rmmod, route, sed, sh, sleep, smemcap, sort, stat, strings, swapoff, swapon, sync, sysctl, syslogd, tail, tar, tee, telnetd, test, tftp, time,
  *     timeout, top, touch, tr, true, tty, udhcpc, udhcpd, umount, unxz, unzip, uptime, users, usleep, vi, volname, watch, wc, which, xargs, xz,
  *     xzcat

* /lib : bibliothèques standards.

fichiers notables dans _/ipc_ :
* _/ipc/app/jco\_server_
  * programme principal, fait à la fois serveur http, rtsp, ...
* _/ipc/drv_ : drivers linux
  * motor.ko
* _/ipc/lib_ : bibliothéques
  * libimp.so : bibliothèque _ingenic_ _IMP_ ( _Ingenic Media Platform_ )


**note : libimp.so est différente de celle livrée pour le T20, et celle fournie avec le T20 ne convient pas.**

# ports GPIO

* ports bloqués par motor.ko : 18? 38 39 40 41 47 48 49 60?
* ports bloqués par audio.ko : 63?
* port 46 = LEDS infra-rouge.
* port 52 = ?
* port 64 = ?
* port 81 = LEDS bleues.

# examen du noyau :
* informations :
    `binwalk mtdblock2.bin`
    * résultat :
DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
0             0x0             uImage header, header size: 64 bytes, header CRC: 0x7B9DE864, created: 2019-06-22 02:41:00, image size: 1466358 bytes, Data Address: 0x80010000, Entry Point: 0x80388340, data CRC: 0xB83DCA15, OS: Linux, CPU: MIPS, image type: OS Kernel Image, compression type: lzma, image name: "Linux-3.10.14__isvp_turkey_1.0__]"
64            0x40            LZMA compressed data, properties: 0x5D, dictionary size: 16777216 bytes, uncompressed size: -1 bytes

* extraction des données de mtdblock2 :
    `tail -c+65  < mtdblock2.bin >mtdblock2.dataz`
* extraction du noyau :
    `cat mtdblock2.dataz|lzma -d -c -f - >kernel`
* liste des drivers inclus :
    `strings kernel|grep "^drivers"`
* liste des fichiers source :
    `strings kernel|grep "\.[cChTsS]$"`
* liste des symboles
https://github.com/marin-m/vmlinux-to-elf devrait permettre de trouver les symboles, mais il n'y arrive pas
début possible de kallsyms_token_table : 0x3AA1B4
