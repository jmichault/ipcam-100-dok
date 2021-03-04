---
lang: pt
lang-niv: auto
lang-ref: 001-originala_firmvaro
layout: page
title: 'Firmware original'
---

A memória Flash é distribuída da seguinte forma:

pontuação | descrição |
--- | --- |
mtdblock0 | u-bootloader |
mtdblock1 | configuração de inicialização |
mtdblock2 | herança de inicialização u uImage, linux-kernel |
mtdblock3 | abóboras = / |
mtdblock4 | squashfs, montado em / ipc |
mtdblock5 | jffs2, montado em / opt |

A partição u-boot (mtdblock0) carrega o kernel no mtdblock2.  
opções padrão no carregador de boot u:  
* bootargs = console = ttyS1,115200n8 mem = 43M @ 0x0 rmem = 21M @ 0x2B00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3


* bootcmd = probe sf; sf ler 0x80600000 0x48000 0x280000; bootm 0x80600000


* atraso de inicialização = 1


* taxa de transmissão = 115200


* cargas\_eoo = 1


* ethaddr = 00: 11: 22: 33: 44: 74


* ipaddr = 192.168.2.84


* serverip = 192.168.2.81


* gatewayip = 192.168.2.1


* máscara de rede = 255.255.255.0



opções em mtdblock1:
* taxa de transmissão = 115200
* bootcmd = sonda sf; sf ler 0x80600000 0x48000 0x280000; bootm 0x80600000
* bootdelay = 1
* ethact = Jz4775-9161
* gatewayip = 192.168.2.1
* ipaddr = 192.168.2.84
* cargas\_eoo = 1
* máscara de rede = 255.255.255.0
* serverip = 192.168.2.81
* stderr = série
* stdin = série
* stdout = série
* ethaddr =**:**:**:**:**:**
* dispositivo\_id =***********
* devinfo = jcoxa***************************************************
* bootargs = console = ttyS1,115200n8 mem = 42M @ 0x0 rmem = 22M @ 0x2A00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3 flash = SF sensor = GC2053 maxheight = 1080 dispositivo\_id =*********** ethaddr =**:**:**:**:**:** devinfo = jcoxa*************************************************** cpu = T21 ddr = 64M mtdparts = jz\_sfc: 256K @ 0K(sf-bootloader), 32K @ 256K(sf-bootenv), 1440K @ 288K() kernel sf), 832K @ 172 8K(sf-rootfs), 4928K @ 2560K(sf-ipcfs), 704K @ 7488 K(sf-miscfs)


Versão Linux:  
Linux versão 3.10.14\_\_isvp\_turquia\_1.0\_\_ (root@localhost.localdomain) (gcc versão 4.7.2 (Ingenic r2.3.3 2016.12) ) # 3 PREEMPT Sáb 22 de junho 10:40:55 CST 2019)


Arquivos notáveis ​​em /:
* _/bin/busybox_ : 
  *     [, [[, cinza, awk, base64, nome de base , blockdev, bootchartd, bunzip2, bzcat, bzip2, cat, chmod, chown, cmp, cp, cut, date, dd, depmod, devmem, df,
  *     dhcprelay, diff, dirname, dmesg , dnsdomainname, du, dumpleases, echo, egrep, expr, fdflush, fdformat, fdisk, fgrep, find, flash\_eraseall,
  *     grego, libera, fandilo, getty, grep , gzip, halt, hd, head, hexdump, hostname, hwclock, ifconfig, init, insmod, iostat, kill, killall, klogd, less,
  *     linuxrc, ln, logger, login, logread , ls, lsmod, md5sum, mdev, mesg, mkdir, mkdosfs, mkfs.vfat, mknod, mktemp, modinfo, modprobe, mount,
  *     montopunkto, mpstat, mv, nc, netstat, passwd , ping, pmap, poweroff, powertop, printf, ps, pstree, pwd, pwdx, readahead, reboot, rev, rm, rmdir,
  *     rmmod, rota, sed, sh, dormo, smemcap , classificar, estatísticas, strings, troca, troca, sincronização, sistema, sistema, fila, tar on, screenshot, telnet, test, tftp, time,
  *     pause, top, touch, tr, true, tty, udhcpc, udhcpd, umount, unxz, unzip, uptime, users, usleep, vi, nome do volume, relógio, wc, kiu, xargs, xz,
  *     xzcat

* / lib: bibliotecas padrão.



arquivos notáveis ​​em _/ipc_ :
* _/ipc/app/jco\_server_
  * programa principal, feito simultaneamente servidor http, rtsp, ...
* _/ipc/drv_ : drivers Linux
  * motor.ko
* _/ipc/lib_ : bibliotecas
)  * libimp.so: biblioteko _ingenic_ _IMP_ ( _Ingenic Media Platform_ )


nota: libimp.so difere daquele entregue para o T20, e aquele entregue com o T20 não é adequado.
