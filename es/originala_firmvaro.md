---
lang: es
lang-niv: auto
lang-ref: 001-originala_firmvaro
layout: page
title: 'Firmware original'
---

La memoria flash se distribuye de la siguiente manera:

puntuación | descripción |
--- | --- |
mtdblock0 | u-bootloader |
mtdblock1 | configuración de arranque |
mtdblock2 | herencia de u-boot uImage, linux-kernel |
mtdblock3 | calabazas = / |
mtdblock4 | squashfs, montado en / ipc |
mtdblock5 | jffs2, montado en / opt |

La partición u-boot (mtdblock0) carga el kernel en mtdblock2.  
opciones predeterminadas en u-boot loader:  
* bootargs = consola = ttyS1,115200n8 mem = 43M @ 0x0 rmem = 21M @ 0x2B00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3


* bootcmd = sonda sf; sf leer 0x80600000 0x48000 0x280000; bootm 0x80600000


* bootdelay = 1


* velocidad en baudios = 115200


* cargas\_eoo = 1


* ethaddr = 00: 11: 22: 33: 44: 74


* ipaddr = 192.168.2.84


* serverip = 192.168.2.81


* gatewayip = 192.168.2.1


* máscara de red = 255.255.255.0



opciones en mtdblock1:
* velocidad en baudios = 115200
* bootcmd = sonda sf; sf leer 0x80600000 0x48000 0x280000; bootm 0x80600000
* bootdelay = 1
* ethact = Jz4775-9161
* gatewayip = 192.168.2.1
* ipaddr = 192.168.2.84
* cargas\_eoo = 1
* máscara de red = 255.255.255.0
* serverip = 192.168.2.81
* stderr = serie
* stdin = serie
* stdout = serie
* ethaddr =**:**:**:**:**:**
* dispositivo\_id =***********
* devinfo = jcoxa***************************************************
* bootargs = consola = ttyS1,115200n8 mem = 42M @ 0x0 rmem = 22M @ 0x2A00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3 flash = SF sensor = GC2053 maxheight = 1080 dispositivo\_id =*********** ethaddr =**:**:**:**:**:** devinfo = jcoxa*************************************************** cpu = T21 ddr = 64M mtdpartes = jz\_sfc: 256K @ 0K(sf-bootloader), 32K @ 256K(sf-bootenv), 1440K @ 288K() sf-kernel), 832K @ 172 8K(sf-rootfs), 4928K @ 2560K(sf-ipcfs), 704K @ 7488 K(sf-miscfs)


Versión de Linux:  
Versión de Linux 3.10.14\_\_isvp\_turquía\_1.0\_\_ (root@localhost.localdomain) (gcc versión 4.7.2 (Ingenic r2.3.3 2016.12) ) # 3 PREEMPT Sáb 22 de junio 10:40:55 CST 2019


Archivos notables en /:
* _/bin/busybox_ : 
  *     [, [[, ash, awk, base64, basename , blockdev, bootchartd, bunzip2, bzcat, bzip2, cat, chmod, chown, cmp, cp, cut, date, dd, depmod, devmem, df,
  *     dhcprelay, diff, dirname, dmesg , dnsdomainname, du, dumpleases, echo, egrep, expr, fdflush, fdformat, fdisk, fgrep, find, flash\_eraseall,
  *     grego, libera, fandilo, getty, grep , gzip, detener, hd, cabeza, hexdump, nombre de host, hwclock, ifconfig, init, insmod, iostat, matar, killall, klogd, menos,
  *     linuxrc, ln, logger, iniciar sesión, logread , ls, lsmod, md5sum, mdev, mesg, mkdir, mkdosfs, mkfs.vfat, mknod, mktemp, modinfo, modprobe, mount,
  *     montopunkto, mpstat, mv, nc, netstat, passwd , ping, pmap, poweroff, powertop, printf, ps, pstree, pwd, pwdx, readahead, reiniciar, rev, rm, rmdir,
  *     rmmod, route, sed, sh, dormo, smemcap , ordenar, estadísticas, cadenas, intercambiar, intercambiar, sincronizar, sistema, sistema, cola, alquitrán en, captura de pantalla, telnet, prueba, tftp, hora,
  *     pausa, parte superior, toque, tr, verdadero, tty, udhcpc, udhcpd, desmontar, unxz, descomprimir, tiempo de actividad, usuarios, usleep, vi, nombrevol, reloj, wc, kiu, xargs, xz,
  *     xzcat

* / lib: bibliotecas estándar.



archivos notables en _/ipc_ :
* _/ipc/app/jco\_server_
  * programa principal, hecho simultáneamente servidor http, rtsp, ...
* _/ipc/drv_ : controladores linux
  * motor.ko
* _/ipc/lib_ : bibliotecas
)  * libimp.so: biblioteko _ingenic_ _IMP_ ( _Ingenic Media Platform_ )


nota: libimp.so difiere del que se entrega para el T20 y el que se entrega con el T20 no es adecuado.
