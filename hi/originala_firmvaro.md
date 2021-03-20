---
lang: hi
lang-niv: auto
lang-ref: 001-originala_firmvaro
layout: page
title: 'मूल फर्मवेयर'
---

# खुले बंदरगाह

टीसीपी: 80 (डिग्री 0001 डिग्री) HTTP (° 0002 डिग्री), 443 (डिग्री 0003 डिग्री) एचटीपी भी! (° 0004 डिग्री), 554 (000 0005 डिग्री) आरटीएसपी (डिग्री 0006 डिग्री), 8004, 8006, 9527 (डिग्री 0007 डिग्री) टेलिडीड (डिग्री 0008 डिग्री), 99 99 (डिग्री 000 9 डिग्री)  
यूडीपी: 67 (डिग्री 0001 डिग्री) डीएचसीपी (डिग्री 0002 डिग्री), 3702, 8002, 39642 (डिग्री 0003 डिग्री)

पोर्ट 80: HTTP  
http: // आईपी: लॉगिन: (डिग्री डिग्री 0001 डिग्री), पासवर्ड: (डिग्री 0003 डिग्री) (डिग्री 0005 डिग्री)

पोर्ट 443: HTTP  
http: // आईपी: 443: लॉगिन: (डिग्री 0001 डिग्री), पासवर्ड: (° 0003 डिग्री) (डिग्री 0005 डिग्री)

पोर्ट 554: आरटीएसपी (डिग्री 0001 डिग्री)  
* मुख्य वर्तमान: (° 0001 डिग्री) 



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

पोर्ट 8004:? , jco द्वारा खोला गया_server



पोर्ट 8006 :? , jco द्वारा खोला गया_server




पोर्ट 9527: टेलनेट (डिग्री 0001 डिग्री)  
`telnetd IP 9527` : लॉगिन: (° 0003 डिग्री), पासवर्ड: (डिग्री 0005 डिग्री), 5 मिनट के लिए सुलभ, के बाद बंद।  
5 मिनट के बाद डिस्कनेक्ट नहीं होना चाहिए: (° 0001 डिग्री) (° ° 0004 डिग्री)
JCO को रोकने के लिए_server : 
 
 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

पोर्ट 9999: कैमरे को नियंत्रित करने के लिए उपयोग किया जाता है, उदाहरण:

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67: udhcpdद्वारा खुला

यूडीपी 3702:? , jco द्वारा खोला गया_server




# आंतरिक फ्लैश मेमोरी
फ्लैश मेमोरी को निम्नानुसार वितरित किया जाता है:

स्कोर | विवरण |
--- | ---
mtdblock0 | u-बूटलोडर |
mtdblock1 | बूट विन्यास |
mtdblock2 | u- बूट विरासत uImage, लिनक्स-कर्नेल |
mtdblock3 | कद्दू = / |
mtdblock4 | स्क्वैश, घुड़सवार / ipc |
mtdblock5 | jffs2, घुड़सवार / ऑप्ट |

u-boot (विभाजन mtdblock0) कर्नेल को mtdblock2 में लोड करता है।  
यू-बूट लोडर में डिफ़ॉल्ट विकल्प:  
* bootargs = कंसोल = ttyS1,115200n8 mem = 43M @ 0x0 rmem = 21M @ 0x2B00000 init = / linuxrc rootfstype = squashfs root = / dev / mbblock3


* bootcmd = sf जांच; sf 0x80600000 0x48000 0x280000 पढ़ें; बूटम 0x80600000


* बूटडेल = 1


* बॉड दर = 115200


* भार\_eoo = 1


* एत्माद्र्द = 00: 11: 22: 33: 44: 74


* ipaddr = 192.168.2.84


* सर्वरिप = 192.168.2.81


* गेटवे = 192.168.2.1


* नेटमास्क = 255.255.255.0



mtdblock1 में विकल्प:
* बॉड दर = 115200
* bootcmd = sf जांच; sf 0x80600000 0x48000 0x280000 पढ़ें; bootm 0x80600000
* bootdelay = 1
* ethact = Jz4775-9161
* गेटवे = 192.168.2.1
* ipaddr = 192.168.2.84
* लोड\_eoo = 1
* (net 00017 °) नेटमीटर = 255.255.255.0
° 00019 °) सर्वरिप = 192.168.2.81
* stderr = श्रृंखला
* स्टड = श्रृंखला
* stdout = श्रृंखला00026 °)* ethaddr =**:**:**:**:**:****
* डिवाइस\_id =***********
* devinfo = jcoxa**************************************************************) बूटारग्स = कंसोल = ttyS1,115200n8 मेम = 42M @ 0x0 rmem = 22M @ 0x2A00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3 फ़्लैश = SF सेंसर = GC2053 मैक्सहाइट = 1080 डिवाइस\_आईडी = = 00044 °) ethaddr =**:**:**:**:**:**:** : devinfo = jcoxa*************************************************** cpu = T21 ddr = 64M mtdparts = j z\_sfc: 256K @ 0K(sf-bootloader), 32K @ 256K(sf-bootenv (° 00056 °, 1440K @ 288K() sf-kernel), 832K @ 1728K(sf-rootfs), 4928K @ 2560K(sf-ipcfs), 704K @ 7488 K() °) sf-miscfs)


लिनक्स संस्करण:  
लिनक्स संस्करण 3.10.14\_\_isvp\_टर्की\_1.0\_\_ (मूल -localhost.localdomain0008 °)(gcc संस्करण 4.7.2 (Ingenic r2.3.3 2016.12) ) # 3 PREEMPT शनि 22 जून 10:40:55 CBS 2019)


में उल्लेखनीय फ़ाइलें /:
* _/bin/busybox_ : 
  *     [, [[, राख, awk, base64, आधार नाम, ब्लॉकदेव, बूटचर्ड, बंजिप 2, बज़टैट, बज़िप 2, बिल्ली, चामोद, चाउन, सीएमपी, कट, तिथि, डीडी, डेमोड, देवम, डीएफ,
  *     dhcprelay, diff, dirname, dmesg, dnsdomainname, du, dumpleases, echo, egrep, expr, fdflush, fdformat, fdisk, fgrep, find, flash\_ergeall,
  *     grego, libera, fandilo grep, gzip, halt, HD, head, hexdump, hostname, hwclock, ifconfig, init, insmod, iostat, Kill, Killall, klogd, less,
  *       *     linuxrc, ln, logger, login, login logread, ls, lsmod, md5sum, mdev, mesg, mkdirf, mkfs.vfat, mknod, mktemp, modinfo, modprobe, माउंट,

  *       *     (montopunkto ,stvento)। , nc, netstat, passwd, ping, pmap, poweroff, powertop, printf, ps, pstree, pwd, pwdx, readahead, reboot, Rev, rm, rmmir
  *       *     rmmod, मार्ग, sed , श, डॉर्मो, स्मेपेक, सॉर्ट, स्टेट, स्ट्रिंग्स, एक्सचेंज, इन पृथ्वी, सिंक्रोनाइज़, सिस्टम, सिस्टम, क्यू, टार, स्क्रीनशॉट, टेलनेट, टेस्ट, टैफ़्ट, टाइम,
  *     पॉज़, टॉप, टच, ट्र, ट्रू, ट्रू, यूडीपीसी, udhcpd, umount, unxz, unzip, uptime, यूज़र्स, सो, यू, वोनाम, वॉच, wc, who, xargs, xz,
  *     xzcat

* / lib: मानक पुस्तकालय।



 _/ipc_ (उल्लेखनीय 0003 °)* _/ipc/app/jco\_server_


  * मुख्य कार्यक्रम में उल्लेखनीय फाइलें, मुख्य रूप से http सर्वर, rsp। .. °)* _/ipc/drv_ : लिनक्स चालक
  * मोटर।को
* * _/ipc/lib_ : पुस्तकालय
°)


**नोट: libimp.so T20 के लिए दिए गए एक से भिन्न होता है, और T20 के साथ दिया जाने वाला उपयुक्त नहीं है।**

# GPIO पोर्ट

* बंदरगाहों द्वारा अवरुद्ध motor.ko: 18? 38 39 40 41 47 48 49 60?


* बंदरगाहों द्वारा अवरुद्ध ऑडियो।


* पोर्ट 46 = अवरक्त एलईडी।


* पोर्ट 52 =?


* पोर्ट 64 =?


* पोर्ट 81 = नीला एल ई डी।




