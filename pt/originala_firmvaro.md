---
lang: pt
lang-niv: auto
lang-ref: 071-originala_firmvaro
layout: page
title: 'Firmware original'
---

# portas abertas

TCP: 80(http), 443(HTP também!), 554(RTSP), 8004, 8006, 9527(, 9999  
UDP: 67 ( DHCP ), 3702, 8002, 39642 

Porta 80: http  
http: // ip: login: _admin:_, senha: _admin_

Porta 443: http  
http: // ip: 443: LOGIN: _admin:_, Senha: _admin_

Porta 554: RTSP  
* Principal atual: 



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

porta 8004 :? , aberto por jco_server



porta 8006 :? , aberto por jco_server




Porta 9527: Telnet  
`telnetd IP 9527` : Login: _root_, Senha: _jco66688_, acessível por 5 minutos, fechado depois.  
Não desconecte após 5 minutos:  `killall -9 auto_run.sh`   
Para parar JCO_server : 
 
 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

porta 9999: usada para controlar a câmera, exemplo:

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67: aberto de udhcpd

UDP 3702 :? , aberto por jco_server




# memória flash interna
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


**observação: libimp.so difere daquele fornecido com o T20, e o fornecido com o T20 não é adequado.**

# Portas GPIO

* portas bloqueadas por motor.ko: 18? 38 39 40 41 47 48 49 60?


* portas bloqueadas por audio.ko: 63?


* porta 46 = LEDs infravermelhos.


* porta 52 =?


* porta 64 =?


* porta 81 = LEDs azuis.



# Revisão Core:
*   Informação:  
      `binwalk mtdblock2.bin`  
      *   Resultado:  
 Descrição hexadecimal decimal  
--------------------------------------------------------------------------------
0 0x0 Uimage Header, Header Size: 64 Bytes, Header CRC: 0x7b9DE864, criado: 2019-06-22 02:41:00, Image Size: 1466358 BYTES, DATE Address: 0x80010000, Entry Point: 0x80388340, Data CRC: 0xb83DCA15, SO: Linux, CPU: MIPS, Tipo de imagem: Imagem do kernel do SO, Tipo de compressão: LZMA, Nome da imagem:   " Linux-3.10.14  __  ISVP  _turkey_  1.0  __]  "  
 64 0X40 Dados compactados LZMA, Propriedades: 0x5d, Tamanho do Dicionário: 16777216 bytes, tamanho compactado: -1 bytes  

Extração de dados de *   mtdblock2:  
      `tail -c+65  < mtdblock2.bin >mtdblock2.dataz`  
  *   Extração de núcleo:  
  *   
 *   Lista de drivers incluídos:  
      `strings kernel|grep "^drivers"`  
  < H21  >  Lista de arquivos de origem:  
      `strings kernel|grep "\.[cChTsS]$"`  
  *   Lista de símbolos  
 https: / / github.com/marin-m/vmlinux-to-elf deve ajudar a encontrar símbolos, mas não existem  < H33  >  Comece por kallsyms  _token_  Tabela: 0x3AA1B4  
