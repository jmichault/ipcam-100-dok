---
lang: ru
lang-niv: auto
lang-ref: 001-originala_firmvaro
layout: page
title: 'Оригинальная прошивка'
---

Флэш-память распределяется следующим образом:

оценка | описание |
--- | --- |
mtdblock0 | u-загрузчик |
mtdblock1 | конфигурация загрузки |
mtdblock2 | u-boot наследование uImage, linux-kernel |
mtdblock3 | тыквы = / |
mtdblock4 | squashfs, установленный на / ipc |
mtdblock5 | jffs2, установленный на / opt |

u-boot (раздел mtdblock0) загружает ядро ​​в mtdblock2.  
параметры по умолчанию в загрузчике u-boot:  
* bootargs = console = ttyS1,115200n8 mem = 43M @ 0x0 rmem = 21M @ 0x2B00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3


* bootcmd = зонд SF; sf читать 0x80600000 0x48000 0x280000; bootm 0x80600000


* bootdelay = 1


* скорость передачи = 115200


* нагрузки\_eoo = 1


* ethaddr = 00: 11: 22: 33: 44: 74


* ipaddr = 192.168.2.84


* serverip = 192.168.2.81


* gatewayip = 192.168.2.1


* маска сети = 255.255.255.0



параметры в mtdblock1:
* скорость передачи = 115200
* bootcmd = зонд SF; sf читать 0x80600000 0x48000 0x280000; bootm 0x80600000
* bootdelay = 1
* ethact = Jz4775-9161
* gatewayip = 192.168.2.1
* ipaddr = 192.168.2.84
* нагрузки\_eoo = 1
* netmask = 255.255.255.0
* serverip = 192.168.2.81
* stderr = серия
* stdin = серия
* stdout = серия
* ethaddr =**:**:**:**:**:**
* устройство\_id =***********
* devinfo = jcoxa***************************************************
* bootargs = console = ttyS1,115200n8 mem = 42M @ 0x0 rmem = 22M @ 0x2A00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3 flash = SF sensor = GC2053 maxheight = 1080 device\_id =*********** ethaddr =**:**:**:**:**:** devinfo = jcoxa*************************************************** cpu = T21 ddr = 64M mtdparts = jz\_sfc: 256K при 0K(sf-bootloader), 32K при 256K(sf-bootenv), 1440K при 288K()) sf-ядро), 832K @ 172 8K(sf-rootfs), 4928K при 2560K(sf-ipcfs), 704K при 7488 K(sf-miscfs)


Версия Linux:  
Версия Linux 3.10.14\_\_isvp\_turkey\_1.0\_\_ (root@localhost.localdomain) (gcc версия 4.7.2 (Ingenic r2.3.3 2016.12) ) # 3 PREEMPT Сб 22 июня 10:40:55 CST 2019


Известные файлы в /:
* _/bin/busybox_ : 
  *     [, [[, ash, awk, base64, basename , blockdev, bootchartd, bunzip2, bzcat, bzip2, cat, chmod, chown, cmp, cp, cut, date, dd, depmod, devmem, df,
  *     dhcprelay, diff, dirname, dmesg , dnsdomainname, du, dumpleases, echo, egrep, expr, fdflush, fdformat, fdisk, fgrep, find, flash\_eraseall,
  *     grego, libera, fandilo, getty, grep , gzip, halt, hd, head, hexdump, hostname, hwclock, ifconfig, init, insmod, iostat, kill, killall, klogd, less,
  *     linuxrc, ln, logger, login, logread , ls, lsmod, md5sum, mdev, mesg, mkdir, mkdosfs, mkfs.vfat, mknod, mktemp, modinfo, modprobe, mount,
  *     montopunkto, mpstat, mv, nc, netstat, passwd , ping, pmap, poweroff, powertop, printf, ps, pstree, pwd, pwdx, readahead, reboot, rev, rm, rmdir,
  *     rmmod, route, sed, sh, dormo, smemcap , сортировка, статистика, строки, своп, своп, синхронизация, система, система, очередь, tar вкл, скриншот, telnet, тест, tftp, время,
  *     пауза, вверх, касание, tr, true, tty, udhcpc, udhcpd, umount, unxz, unzip, uptime, users, usleep, vi, имя, часы, wc, kiu, xargs, xz,
  *     xzcat

* / lib: стандартные библиотеки.



известные файлы в _/ipc_ :
* _/ipc/app/jco\_server_
  * основной программе, созданной одновременно сервером http, rtsp, ...
* _/ipc/drv_ : драйверы Linux
  * motor.ko
* _/ipc/lib_ : библиотеки
)  * libimp.so: biblioteko _ingenic_ _IMP_ ( _Ingenic Media Platform_ )


примечание: libimp.so отличается от того, который поставляется для T20, а тот, который поставляется с T20, не подходит.
