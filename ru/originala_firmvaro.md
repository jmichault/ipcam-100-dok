---
lang: ru
lang-niv: auto
lang-ref: 071-originala_firmvaro
layout: page
title: 'Оригинальная прошивка'
---

# открытые порты

TCP: 80(HTTP), 443(HTP тоже!), 554(RTSP), 8004, 8006, 9527(, 9999  
UDP: 67 ( DHCP ), 3702, 8002, 39642 

Порт 80: HTTP  
http: // IP: Логин: _admin:_, Пароль: _admin_

Порт 443: http  
http: // ip: 443: Логин: _admin:_, Пароль: _admin_

Порт 554: RTSP  
* Основной ток: 



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

порт 8004 :? , открыто jco_server



порт 8006 :? , открыто jco_server




Порт 9527: Telnet  
`telnetd IP 9527` : Логин: _root_, Пароль: _jco66688_, доступный в течение 5 минут, закрыт после.  
Не отключайтесь через 5 минут:  `killall -9 auto_run.sh`   
Чтобы остановить JCO_server : 
 
 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

порт 9999: используется для управления камерой, например:

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67: открытие udhcpd

UDP 3702 :? , открыто jco_server




# внутренняя флеш-память
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


**примечание: libimp.so отличается от того, который поставляется с T20, а тот, который поставляется с T20, не подходит.**

# Порты GPIO

* порты заблокированы motor.ko: 18? 38 39 40 41 47 48 49 60?


* порты заблокированы audio.ko: 63?


* порт 46 = инфракрасные светодиоды.


* порт 52 =?


* порт 64 =?


* порт 81 = синие светодиоды.



# Основной обзор:
*   Информация:  
      `binwalk mtdblock2.bin`  
      *   Результат:  
 Десятичное шестнадцатеричное описание  
--------------------------------------------------------------------------------
0 0x0 Заголовок Uimage, размер заголовка: 64 байта, CRC заголовка: 0x7b9DE864, создано: 2019-06-22 02:41:00, размер изображения: 1466358 BYTES, DATE Address: 0x80010000, точка входа: 0x80388340, CRC данных: 0xb83DCA15, ОС: Linux, ЦП: MIPS, Тип образа: Образ ядра ОС, Тип сжатия: LZMA, Имя образа:   " Linux-3.10.14  __  ISVP  _turkey_  1.0  __]  "  
 64 0X40 Сжатые данные LZMA, свойства: 0x5d, размер словаря: 16777216 байт, сжатый размер: -1 байт  

*   Извлечение данных mtdblock2:  
      `tail -c+65  < mtdblock2.bin >mtdblock2.dataz`  
  *   Извлечение ядра:  
  *   
 *   Список включенных драйверов:  
      `strings kernel|grep "^drivers"`  
  < H21  >  Список исходных файлов:  
      `strings kernel|grep "\.[cChTsS]$"`  
  *   Список символов  
 https: / / github.com/marin-m/vmlinux-to-elf должен помочь найти символы, но не существуют  < H33  >  Начать с kallsyms  _token_  Таблица: 0x3AA1B4  
