---
lang: hi
lang-niv: auto
lang-ref: 071-originala_firmvaro
layout: page
title: 'मूल फर्मवेयर'
---

# खुले बंदरगाह

टीसीपी: 80 <एच 1> http ), 443 ( htp भी!   
यूडीपी: 67 (डिग्री 0001 डिग्री) डीएचसीपी (डिग्री 0002 डिग्री), 3702, 8002, 39642 (डिग्री 0003 डिग्री)

पोर्ट 80: HTTP  
http: // आईपी: लॉगिन: (डिग्री डिग्री 0001 डिग्री), पासवर्ड: (डिग्री 0003 डिग्री) (डिग्री 0005 डिग्री)

पोर्ट 443: HTTP  
http: // ip: 443: लॉगिन:  _admin:_, पासवर्ड:  _admin_ 

पोर्ट 554: आरटीएसपी (डिग्री 0001 डिग्री)  
* मुख्य वर्तमान:  



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
`telnetd IP 9527` : लॉगिन:  _root_, पासवर्ड:  _jco66688_, 5 मिनट के लिए सुलभ, बंद के बाद।   
5 मिनट के बाद डिस्कनेक्ट नहीं किया जाना चाहिए:  `killall -9 auto_run.sh`   
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



MTDBLOCK1 में विकल्प: 
 *  Baurato = 115200 
 *  bootcmd = एस एफ जांच; 


लिनक्स संस्करण:  
लिनक्स संस्करण 3.10.14 \_ \_ isvp \_ melaegro \_ 1.0 \_ \_  ( root@localhost.localdomain )  ( GCC संस्करण 4.7.2  ( इंजेनिक आर 2 .3.3 2016.12 )  )  # 3 Preemp SAB जून 22 10:40:55 CST 2019 


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



 _/ipc_  
 *  _/ipc/app/jco\_server_ 
   *  मुख्य प्रोग्राम में उल्लेखनीय फ़ाइलें, एक ही समय में किए गए सर्वर http, rtsp, ... 
 *  _/ipc/drv_ : लिनक्स ड्राइवर < H14>   *  motor.ko 
 *  _/ipc/lib_ : पुस्तकालय 
   *  libimp.so: लाइब्रेरी  _ingenic_  _IMP_  (  _Ingenic Media Platform_  )  <h30 >


**नोट: libimp.so T20 के लिए दिए गए एक से भिन्न होता है, और T20 के साथ दिया जाने वाला उपयुक्त नहीं है।**

# GPIO पोर्ट

* बंदरगाहों द्वारा अवरुद्ध motor.ko: 18? 38 39 40 41 47 48 49 60?


* बंदरगाहों द्वारा अवरुद्ध ऑडियो।


* पोर्ट 46 = अवरक्त एलईडी।


* पोर्ट 52 =?


* पोर्ट 64 =?


* पोर्ट 81 = नीला एल ई डी।



# कोर समीक्षा:
*   जानकारी:  
      `binwalk mtdblock2.bin`  
      *   परिणाम:  
 दशमलव हेक्साडेसिमल विवरण  
--------------------------------------------------------------------------------
0 0x0 uiMage हेडर, हेडर आकार: 64 बाइट्स, हेडर सीआरसी: 0x7b9de864, बनाया गया: 2019-06-22 02:41:00, छवि का आकार: 1466358 बाइट्स, डेटा पता: 0x80010000, प्रवेश बिंदु: 0x80388340, सीआरसी डेटा: 0xb83dca15, ओएस: लिनक्स, सीपीयू: एमआईपीएस, छवि का प्रकार: ओएस कर्नेल छवि, संपीड़न प्रकार: एलजेएमए, छवि का नाम: <एच 1> लिनक्स -3.10.14  __  आईएसवीपी <एच 3> 1.0 <एच 5> <एच 6> <एच 7> 64 0x40 Lzma संपीड़ित डेटा, गुण: 0x5 डी, शब्दकोश आकार: 16777216 बाइट्स, संपीड़ित आकार: -1 बाइट्स  

*   mtdblock2 तिथि निष्कर्षण:  
      `tail -c+65  < mtdblock2.bin >mtdblock2.dataz`  
  *   कोर निष्कर्षण:  
  *   
 *   ड्राइवरों की सूची शामिल:  
      `strings kernel|grep "^drivers"`  
  < h21  >  स्रोत फ़ाइलों की सूची:  
      `strings kernel|grep "\.[cChTsS]$"`  
  *   प्रतीक सूची  
 https: / / github.com/marin-m/vmlinux-to- प्रतीकों को खोजने में मदद करनी चाहिए, लेकिन kallsyms से  < h33  >  संभव नहीं है  _token_  तालिका: 0x3aaa1b4  
