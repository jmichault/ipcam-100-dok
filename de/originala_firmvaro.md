---
lang: de
lang-niv: auto
lang-ref: 001-originala_firmvaro
layout: page
title: 'Original Firmware'
---

# offene Ports

TCP: 80(http), 443(http auch!), 554(rtsp), 8004, 8006, 9527(Telnet), 9999
UDP: 67(dhcp), 3702, 8002, 39642

Port 80: http
http: // IP: Login: _admin:_, Passwort: _admin_

Port 443: http
http: // IP: 443: Login: _admin:_, Passwort: _admin_

Port 554: RTSP
* Hauptstrom: 

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

Port 8004:? , geöffnet von jco_server



Port 8006:? , geöffnet von jco_server




Port 9527: Telnet
`telnetd IP 9527` : Login: _root_, Passwort: _jco66688_, 5 Minuten zugänglich, danach geschlossen.
darf nach 5 Minuten nicht getrennt werden: `killall -9 auto_run.sh`
um jco zu stoppen_server : 
 
 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

Port 9999: Dient zur Steuerung der Kamera, Beispiel:

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67: offen von udhcpd

UDP 3702:? , geöffnet von jco_server




# interner Flash-Speicher
Der Flash-Speicher ist wie folgt verteilt:

Punktzahl | Beschreibung |
--- | --- |
mtdblock0 | U-Bootloader |
mtdblock1 | Boot-Konfiguration |
mtdblock2 | u-boot Vererbung uImage, Linux-Kernel |
mtdblock3 | Kürbisse = / |
mtdblock4 | squashfs, montiert auf / ipc |
mtdblock5 | jffs2, montiert auf / opt |

u-boot (Partition mtdblock0) lädt den Kernel in mtdblock2.  
Standardoptionen im U-Boot-Loader:  
* bootargs = console = ttyS1,115200n8 mem = 43M @ 0x0 rmem = 21M @ 0x2B00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3


* bootcmd = sf probe; sf read 0x80600000 0x48000 0x280000; bootm 0x80600000


* Bootdelay = 1


* Baudrate = 115200


* Lasten\_eoo = 1


* ethaddr = 00: 11: 22: 33: 44: 74


* ipaddr = 192,168,2,84


* serverip = 192.168.2.81


* Gatewayip = 192.168.2.1


* Netzmaske = 255,255,255,0



Optionen in mtdblock1:
* Baudrate = 115200
* bootcmd = sf probe; sf read 0x80600000 0x48000 0x280000; bootm 0x80600000
* bootdelay = 1
* ethact = Jz4775-9161
* gatewayip = 192.168.2.1
* ipaddr = 192,168,2,84
* Lasten\_eoo = 1
* Netzmaske = 255,255,255,0
* serverip = 192.168.2.81
* stderr = Serie
* stdin = Serie
* stdout = Serie
* ethaddr =**:**:**:**:**:**
* Gerät\_id =***********
* devinfo = jcoxa***************************************************
* bootargs = console = ttyS1,115200n8 mem = 42M @ 0x0 rmem = 22M @ 0x2A00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3 flash = SF sensor = GC2053 maxheight = 1080 Geräte\_id =*********** ethaddr =**:**:**:**:**:** devinfo = jcoxa*************************************************** cpu = T21 ddr = 64 M mtdparts = jz\_sfc: 256 K @ 0 K(sf-Bootloader), 32 K @ 256 K(sf-bootenv), 1440 K @ 288 K()) SF-Kernel), 832K @ 172 8 K(sf-rootfs), 4928 K @ 2560 K(sf-ipcfs), 704 K @ 7488 K(sf-miscfs)


Linux-Version:  
Linux Version 3.10.14\_\_isvp\_Truthahn\_1.0\_\_ (root@localhost.localdomain) (gcc Version 4.7.2 (Ingenic r2.3.3 2016.12) ) # 3 VOREMPT Sa 22.06. 10:40:55 CST 2019)


Bemerkenswerte Dateien in /:
* _/bin/busybox_ : 
  *     [, [[, Asche, awk, base64, Basisname , blockdev, bootchartd, bunzip2, bzcat, bzip2, cat, chmod, chown, cmp, cp, cut, date, dd, depmod, devmem, df,
  *     dhcprelay, diff, dirname, dmesg , dnsdomainname, du, dumpleases, echo, egrep, expr, fdflush, fdformat, fdisk, fgrep, find, flash\_eraseall,
  *     grego, libera, fandilo, getty, grep , gzip, halt, hd, head, hexdump, hostname, hwclock, ifconfig, init, insmod, iostat, kill, killall, klogd, weniger,
  *     linuxrc, ln, logger, login, logread , ls, lsmod, md5sum, mdev, mesg, mkdir, mkdosfs, mkfs.vfat, mknod, mktemp, modinfo, modprobe, mount,
  *     montopunkto, mpstat, mv, nc, netstat, passwd , ping, pmap, poweroff, powertop, printf, ps, pstree, pwd, pwdx, readahead, neustart, rev, rm, rmdir,
  *     rmmod, route, sed, sh, dormo, smemcap , sortieren, stat, Strings, Swap, Swap, Sync, System, System, Warteschlange, Teer on, Screenshot, Telnet, Test, tftp, Zeit,
  *     Pause, oben, berühren, tr, wahr, tty, udhcpc, udhcpd, umount, unxz, entpacken, Verfügbarkeit, Benutzer, usleep, vi, volname, watch, wc, kiu, xargs, xz,
  *     xzcat

* / lib: Standardbibliotheken.



Bemerkenswerte Dateien in _/ipc_ :
* _/ipc/app/jco\_server_
  * Hauptprogramm, gleichzeitig Server http, rtsp, ...
* _/ipc/drv_ : Linux-Treiber
  * motor.ko
* _/ipc/lib_ : Bibliotheken
)  * libimp.so: biblioteko _ingenic_ _IMP_ ( _Ingenic Media Platform_ )


**Hinweis: libimp.so unterscheidet sich von dem für den T20 gelieferten und der mit dem T20 gelieferte ist nicht geeignet.**

# GPIO-Ports

* Ports von motor.ko blockiert: 18? 38 39 40 41 47 48 49 60?


* Ports von audio.ko blockiert: 63?


* Port 46 = Infrarot-LEDs.


* Port 52 =?


* Port 64 =?


* Port 81 = blaue LEDs.




