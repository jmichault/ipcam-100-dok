---
lang: it
lang-niv: auto
lang-ref: 001-originala_firmvaro
layout: page
title: 'Firmware originale'
---

# porte aperte

TCP: 80(HTTP), 443(HTP anche!), 554(RTSP), 8004, 8006, 9527(, 9999  
UDP: 67(DHCP), 3702, 8002, 39642 (° 3 ° 3

Porta 80: http  
http: // IP: Login: _admin:_, Password: _admin_

Porta 443: http  
http: // IP: 443: Login: _admin:_, Password: _admin_

Porta 554: RTSP  
* Corrente principale: 



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

porta 8004 :? , aperto da jco_server



porta 8006 :? , aperto da jco_server




Porta 9527: Telnet  
`telnetd IP 9527` : Login: _root_, Password: _jco66688_, accessibile per 5 minuti, chiuso dopo.  
Non essere disconnesso dopo 5 minuti: `killall -9 auto_run.sh`  (° 4 ° 4
Per fermare JCO_server : 
 
 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

porta 9999: usata per controllare la telecamera, esempio:

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67: aperto di udhcpd

UDP 3702 :? , aperto da jco_server




# memoria flash interna
La memoria flash è distribuita come segue:

punteggio | descrizione |
--- | --- |
mtdblock0 | u-bootloader |
mtdblock1 | configurazione di avvio |
mtdblock2 | ereditarietà u-boot uImage, linux-kernel |
mtdblock3 | zucche = / |
mtdblock4 | squashfs, montato su / ipc |
mtdblock5 | jffs2, montato su / opt |

u-boot (partizione mtdblock0) carica il kernel in mtdblock2.  
opzioni predefinite in u-boot loader:  
* bootargs = console = ttyS1,115200n8 mem = 43M @ 0x0 rmem = 21M @ 0x2B00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3


* bootcmd = sonda sf; sf ha letto 0x80600000 0x48000 0x280000; bootm 0x80600000


* bootdelay = 1


* velocità di trasmissione = 115200


* carichi\_eoo = 1


* ethaddr = 00: 11: 22: 33: 44: 74


* ipaddr = 192.168.2.84


* serverip = 192.168.2.81


* gatewayip = 192.168.2.1


* maschera di rete = 255.255.255.0



opzioni in mtdblock1:
* baud rate = 115200
* bootcmd = sf probe; sf ha letto 0x80600000 0x48000 0x280000; bootm 0x80600000
* bootdelay = 1
* ethact = Jz4775-9161
* gatewayip = 192.168.2.1
* ipaddr = 192.168.2.84
* carichi\_eoo = 1
* maschera di rete = 255.255.255.0
* serverip = 192.168.2.81
* stderr = serie
* stdin = serie
* stdout = serie
* ethaddr =**:**:**:**:**:**
* dispositivo\_id =***********
* devinfo = jcoxa***************************************************
* bootargs = console = ttyS1,115200n8 mem = 42M @ 0x0 rmem = 22M @ 0x2A00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3 flash = SF sensor = GC2053 maxheight = 1080 dispositivo\_id =*********** ethaddr =**:**:**:**:**:** devinfo = jcoxa*************************************************** cpu = T21 ddr = 64M mtdparts = jz\_sfc: 256K @ 0K(sf-bootloader), 32K @ 256K(sf-bootenv), 1440K @ 288K() sf-kernel), 832K @ 172 8K(sf-rootfs), 4928K @ 2560K(sf-ipcfs), 704K @ 7488 K(sf-miscfs)


Versione Linux:  
Linux versione 3.10.14\_\_isvp\_turkey\_1.0\_\_ (root@localhost.localdomain) (gcc versione 4.7.2 (Ingenic r2.3.3 2016.12) ) # 3 PREEMPT sab 22 giugno 10:40:55 CST 2019


File notevoli in /:
* _/bin/busybox_ : 
  *     [, [[, ash, awk, base64, basename , blockdev, bootchartd, bunzip2, bzcat, bzip2, cat, chmod, chown, cmp, cp, tagliare, data, dd, depmod, devmem, df,
  *     dhcprelay, diff, dirname, dmesg , dnsdomainname, du, dumpleases, echo, egrep, expr, fdflush, fdformat, fdisk, fgrep, find, flash\_eraseall,
  *     grego, libera, fandilo, getty, grep , gzip, halt, hd, head, hexdump, hostname, hwclock, ifconfig, init, insmod, iostat, kill, killall, klogd, less,
  *     linuxrc, ln, logger, login, logread , ls, lsmod, md5sum, mdev, mesg, mkdir, mkdosfs, mkfs.vfat, mknod, mktemp, modinfo, modprobe, mount,
  *     montopunkto, mpstat, mv, nc, netstat, passwd , ping, pmap, poweroff, powertop, printf, ps, pstree, pwd, pwdx, readahead, riavvio, rev, rm, rmdir,
  *     rmmod, route, sed, sh, dormo, smemcap , sort, stat, strings, swap, swap, sync, system, system, queue, tar su, screenshot, telnet, test, tftp, ora,
  *     pausa, superiore, tocco, tr, true, tty, udhcpc, udhcpd, umount, unxz, unzip, uptime, users, usleep, vi, volname, watch, wc, kiu, xargs, xz,
  *     xzcat

* / lib: librerie standard.



file importanti in _/ipc_ :
* _/ipc/app/jco\_server_
  * programma principale, reso simultaneamente server http, rtsp, ...
* _/ipc/drv_ : driver linux
  * motore.ko
* _/ipc/lib_ : librerie
)  * libimp.so: biblioteko _ingenic_ _IMP_ ( _Ingenic Media Platform_ )


**nota: libimp.so è diverso da quello fornito per il T20 e quello fornito con il T20 non è adatto.**

# Porte GPIO

* porte bloccate da motor.ko: 18? 38 39 40 41 47 48 49 60?


* porte bloccate da audio.ko: 63?


* porta 46 = LED a infrarossi.


* porta 52 =?


* porta 64 =?


* porta 81 = LED blu.



# Revisione principale:
(° 1 ° 1 ° Informazioni:
    `binwalk mtdblock2.bin`


    * 
--------------------------------------------------------------------------------
0 0x0 Intestazione di uImage, Intestazione Dimensione: 64 Bytes, intestazione CRC: 0x7b9de864, Creato: 2019-06-22 02:41:00, Dimensione dell'immagine: 1466358 Bytes, Indirizzo dati: 0x80010000, Punto d'ingresso: 0x80388340, CRC Dati: 0xb83dca15, OS: Linux, CPU: MIPS, Tipo di immagine: OS Kernel Image, Tipo di compressione: LZMA, Nome immagine: "Linux-3.10.14__.

(° 1 ° 1 ° 1 ° Estrazione di dati di MTDBLOCK2:
    `tail -c+65  < mtdblock2.bin >mtdblock2.dataz`

Estrazione del nucleo:


(° 5 ° 5 ° 6 ° 13 ° 13 ° Elenco dei conduttori inclusi:    `strings kernel|grep "^drivers"`

Elenco dei file:
    `strings kernel|grep "\.[cChTsS]$"`









(° 1 °. Raggiunge
.
