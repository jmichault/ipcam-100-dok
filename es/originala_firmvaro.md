---
lang: es
lang-niv: auto
lang-ref: 071-originala_firmvaro
layout: page
title: 'Firmware original'
---

# puertos abiertos

TCP: 80(HTTP), 443(¡HTP también!), 554(RTSP), 8004, 8006, 9527(, 9999  
UDP: 67 ( DHCP ), 3702, 8002, 39642 

Puerto 80: http  
http: // IP: Iniciar sesión: _admin:_, contraseña: _admin_

Puerto 443: http  
http: // IP: 443: Iniciar sesión: _admin:_, contraseña: _admin_

Puerto 554: RTSP  
* Corriente principal: 



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

puerto 8004 :? , abierto por jco_server



puerto 8006 :? , abierto por jco_server




Puerto 9527: Telnet  
`telnetd IP 9527` : Iniciar sesión: _root_, contraseña: _jco66688_, accesible durante 5 minutos, cerrado después.  
No se desconecte después de 5 minutos:  `killall -9 auto_run.sh`   
Para detener a JCO_server : 
 
 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

puerto 9999: utilizado para controlar la cámara, ejemplo:

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67: abierto de udhcpd

UDP 3702 :? , abierto por jco_server




# memoria flash interna
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


**nota: libimp.so difiere del suministrado para el T20, y el suministrado con el T20 no es adecuado.**

# Puertos GPIO

* puertos bloqueados por motor.ko: 18? 38 39 40 41 47 48 49 60?


* puertos bloqueados por audio.ko: 63?


* puerto 46 = LED infrarrojos.


* puerto 52 =?


* puerto 64 =?


* puerto 81 = LED azules.



# Revisión del núcleo:
*   Información:  
      `binwalk mtdblock2.bin`  
      *   Resultado:  
 Decimal Hexadecimal Descripción  
--------------------------------------------------------------------------------
0 0x0 UIMage Encabezado, encabezado Tamaño: 64 bytes, encabezado CRC: 0x7b9de864, Creado: 2019-06-22 02:41:00, Tamaño de la imagen: 1466358 Bytes, Bytes, Discurso de datos: 0x80010000, Punto de entrada: 0x80388340, Datos de CRC: 0xb83dca15, OS: Linux, CPU: MIPS, Tipo de imagen: Imagen del kernel de OS, Tipo de compresión: LZMA, Nombre de la imagen:   " Linux-3.10.14  __  ISVP  _turkey_  1.0  __]  "  
 64 0x40 Datos comprimidos LZMA, Propiedades: 0x5D, Diccionario Tamaño: 16777216 Bytes, Tamaño comprimido: -1 Bytes  

*   MTDBLOCK2 EXTRACCIÓN FECHA:  
      `tail -c+65  < mtdblock2.bin >mtdblock2.dataz`  
  *   Extracción de núcleo:  
  *   
 *   Lista de controladores incluidos:  
      `strings kernel|grep "^drivers"`  
  < H21  >  Lista de archivos fuente:  
      `strings kernel|grep "\.[cChTsS]$"`  
  *   Lista de símbolos  
 HTTPS: / / / / github.com/marin-m/vmlinux-- para ayudar a encontrar símbolos, pero no se puede  < H33  >  Posible de Kallsyms  _token_  Tabla: 0x3aaA1B4  
