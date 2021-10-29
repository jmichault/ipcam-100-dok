---
lang: ms
lang-niv: auto
lang-ref: 000-indekso
layout: page
title: Pembentangan
---

Tujuan projek ini adalah untuk mewujudkan firmware alternatif untuk kamera ini: (° 1 ° 1

tanda = _WIFI CARAM_  
model: _WF-HD820-ZS_  
perbezaan: _1080P_

Maklumat yang dipaparkan di antara muka Internet:
```
DeviceName: _INGENIC-V01_
DeviceModel: _IPCAM-100_
DeviceSN: _12345678901_
KernelVersion: _Thu Jul 9 15:46:54 CST 2015_
ServerVersion: _WS3.53.1243-20190717-DANALE-GEN_
WebVersion: _V2.3.4-20190709_
```

pemproses: _ingenic T21_
sensor video: _GC2053_

Dokumentasi API boleh dilihat di sini:  
* [versi asal dalam bahasa Cina](../zh/includes.zh/html/)


* [Versi Bahasa Inggeris](../en/includes.en/html/)


* [Versi Perancis diterjemahkan oleh google](../fr/includes.fr/html/)



# Firmware alternatif

## Apa yang Berfungsi dalam Firmware Alternatif:

* LAN dan WLAN


* Pelayan aliran Dwi DRTTSP: 1920x1080 H264 dan 640X360 MJPEG secara lalai.


* Parameter visual


* Pelayan HTTP


* kawalan enjin


* penentukuran enjin


* Tetapan PTZ


* Pelanggan NTP


* pertukaran kata laluan untuk akses http


* kawalan LED biru dan IR


* Pelayan Ftp


* Pelayan Telnet


* SSH Server dan Client


* pengesanan gerakan


* menghantar e-mel



## Apa yang tidak dilakukan dalam firmware alternatif:

* sistem bunyi


* _OSD_


* Pengurusan Pentadbiran dan sistem RTSP.


* kemas kini firmware


* pengesanan malam automatik


* pengesanan gerakan_ir-cut_


* menghantar e-mel_mqtt_


* dll ...



## Memasang Firmware Alternatif

* Salin semuanya ke folder [ _karto_ ](https://github.com/jmichault/ipcam-100/tree/master/karto) di akar kad microSD.


* Mungkin menetapkan rangkaian ( _www/ipcam/config.dist/reto.conf_ )


* Masukkan kad microSD.


* Sambungkan kamera ke rangkaian tempatan anda dan hidupkan kamera.


* Cari alamat IP kamera. Anda juga boleh menyambung ke kamera WiFi (SSID: _HSIPC-******_), en tiu kazo la IP-adreso estas _172.25.0.1_.


* Sambungkan ke kamera dengan pengguna `telnet IP 9527` ( _root_, kata laluan _jco66688_), dalam masa 5 minit selepas berputar pada kamera.


* Buat `killall -9 auto_run.sh` untuk mengelakkan kehilangan liga.


* Faru `cd /opt/media/mmcblk0p1;./install.sh`


* Anda boleh menyambung ke URL _https://IP_ (, kata laluan _admin_, kata laluan _ismart21_).


* Anda boleh menyambung dalam SSH (pengguna _admin_, kata laluan _ismart12_).


* Arus video utama boleh diakses pada _rtsp://admin:ismart21@IP/stream1_. (° 3 ° 3


* Arus video menengah boleh diakses pada _rtsp://admin:ismart21@IP/stream2_. (° 3 ° 3


(° 1 ° 1 ° 1 Wifi AP Mode diaktifkan oleh lalai:
SSID: IPCAM100-XXXXXX
** WPA2 Key: Ismart21
Alamat IP kamera: 172.25.0.1

## Menyahpasang Firmware Alternatif:

* Lancarkan perkhidmatan SSH pada kamera melalui antara muka lalai).


* Masuk ke kamera dengan `ssh root@IP` (Kata laluan _ismart12_).


* mulakan perkhidmatan telnet dengan kamera melalui antara muka internet. `cd /opt/media/mmcblk0p1;./uninstall.sh;reboot`



* Anda juga boleh mengeluarkan kad microSD dengan mudah.



# Dokumen yang menarik

Banyak kerja dibuat untuk kamera yang dilengkapi dengan pemproses _ingenic T20_ :* Diubahsuai firmware: <https://github.com/ilítístotlyar/xiaomi- Dafang -haks>
Sumber firmware yang diubahsuai: <https://github.com/dafang-hacks/main>
firmware lain <https://github.com/openmiko/openmiko>
* Pelancaran program Tanpa menukar firmware: (° 17 ° 17 ° 17: // https://github.com/thuatenameanameexist/jco-pm203-ffishere-iningenic-t20-p2p-camera-hacks>

