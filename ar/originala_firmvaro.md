---
lang: ar
lang-niv: auto
lang-ref: 071-originala_firmvaro
layout: page
title: 'البرامج الثابتة الأصلية'
---

# منافذ مفتوحة

TCP: 80 ( http: )، 443 ( htp أيضا!   
UDP: 67 ( DHCP )، 3702، 8002، 39642 

ميناء 80: http  
http: // ip: تسجيل الدخول: _admin:_، كلمة المرور: _admin_

ميناء 443: http  
http: // ip: 443: تسجيل الدخول: _admin:_، كلمة المرور: _admin_

ميناء 554: RTSP  
* الحالي الحالي: 



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

المنفذ 8004 :؟ ، تم فتحه بواسطة jco_server



المنفذ 8006 :؟ ، تم فتحه بواسطة jco_server




ميناء 9527: Telnet  
`telnetd IP 9527` : تسجيل الدخول: _root_، كلمة المرور: _jco66688_، يمكن الوصول إليها لمدة 5 دقائق، مغلقة بعد.  
لا يتم قطع اتصالها بعد 5 دقائق:  `killall -9 auto_run.sh`   
لوقف JCO_server : 
 
 

```
killall -9 auto_run.sh
killall -9 jco_server;echo 'V'>/dev/watchdog;echo 'V'>/dev/watchdog0
```

المنفذ 9999: يستخدم للتحكم بالكاميرا مثال:

```
IP=xxx.xxx.xxx.xxx
echo "checkuser -act set -user admin -password admin" | nc $IP 9999
echo "list" | nc $IP 9999
echo "pelcod20ctrl -?" | nc $IP 9999
echo "pelcod20ctrl -type 1" | nc $IP 9999
```

UDP 67: فتح udhcpd

UDP 3702 :؟ ، تم فتحه بواسطة jco_server




# ذاكرة فلاش داخلية
يتم توزيع ذاكرة الفلاش على النحو التالي:

النتيجة | الوصف |
--- | --- |
mtdblock0 | u-bootloader |
mtdblock1 | تكوين التمهيد |
mtdblock2 | وراثة u-boot uImage ، linux-kernel |
mtdblock3 | القرع = / |
mtdblock4 | سكواشفس ، مثبتة على / ipc |
mtdblock5 | jffs2 ، مُركب على / opt |

u-boot (قسم mtdblock0) يقوم بتحميل kernel إلى mtdblock2.  
الخيارات الافتراضية في محمل u-boot:  
* bootargs = وحدة التحكم = ttyS1،115200n8 mem = 43M @ 0x0 rmem = 21M @ 0x2B00000 init = / linuxrc rootfstype = squashfs root = / dev / mtdblock3


* bootcmd = مسبار sf ؛ قراءة sf 0x80600000 0x48000 0x280000 ؛ bootm 0x80600000


* التمهيد = 1 (درجة 1 درجة)


* معدل الباود = 115200 (درجة 1 درجة)


* الأحمال\_eoo = 1


* ethaddr = 00: 11: 22: 33: 44: 74 (درجة 1 درجة)


* ipaddr = 192.168.2.84 (درجة 1 درجة)


* serverip = 192.168.2.81


* gatewayip = 192.168.2.1


* قناع الشبكة = 255.255.255.0 (درجة 1 درجة)



الخيارات في mtdblock1: 
 *  baudrato = 115200 
 *  bootcmd = سادس التحقيق. 


إصدار Linux:  
إصدار Linux 3.10.14\_\_isvp\_تركيا\_1.0\_\_ (root@localhost.localdomain) (إصدار مجلس التعاون الخليجي 4.7.2 (Ingenic r2.3.3 2016.12) ) # 3 PREEMPT السبت 22 يونيو 10:40:55 CST 2019)


الملفات البارزة في /:
* _/bin/busybox_ : 
  *     [، [[، الرماد ، awk ، base64 ، الاسم الأساسي ، blockdev، bootchartd، bunzip2، bzcat، bzip2، cat، chmod، chown، cmp، cp، cut، date، dd، depmod، devmem، df،
  *     dhcprelay، diff، dirname، dmesg ، dnsdomainname، du، dumpleases، echo، egrep، expr، fdflush، fdformat، fdisk، fgrep، find، flash\_eraseall،
  *     grego، libera، fandilo، getty، grep ، gzip، halt، hd، head، hexdump، hostname، hwclock، ifconfig، init، insmod، iostat، kill، killall، klogd، less،
  *     linuxrc، ln، logger، login، logread ، ls، lsmod، md5sum، mdev، mesg، mkdir، mkdosfs، mkfs.vfat، mknod، mktemp، modinfo، modprobe، mount،
  *     montopunkto، mpstat، mv، nc، netstat، passwd ، ping، pmap، poweroff، powertop، printf، ps، pstree، pwd، pwdx، readahead، reboot، rev، rm، rmdir،
  *     rmmod، route، sed، sh، dormo، smemcap فرز النظام الأساسي ومبادلة السلاسل والمزامنة ونظام نظام قائمة الانتظار القطران on، screenshot، telnet، test، tftp، time،
  *     pause، top، touch، tr، true، tty، udhcpc، udhcpd، umount، unxz، unzip، uptime، users، usleep، vi ، volname ، watch ، wc ، kiu ، xargs ، xz ،
  *     xzcat

* / lib: مكتبات قياسية.



الملفات البارزة في _/ipc_ :
* _/ipc/app/jco\_server_
  * البرنامج الرئيسي ، تم إنشاؤه في نفس الوقت http ، rtsp ، ...
* _/ipc/drv_ : سائقي لينكس
  * motor.ko
* _/ipc/lib_ : المكتبات
)  * libimp.so: biblioteko _ingenic_ _IMP_ ( _Ingenic Media Platform_ )


**ملاحظة: يختلف libimp أيضًا عن الذي تم تسليمه لـ T20 ، والذي يتم تسليمه مع T20 غير مناسب.**

# منافذ GPIO

* المنافذ المحظورة بواسطة motor.ko: 18؟ 38 39 40 41 47 48 49 60؟


* المنافذ المحظورة بواسطة audio.ko: 63؟


* المنفذ 46 = مصابيح الأشعة تحت الحمراء.


* المنفذ 52 =؟


* المنفذ 64 =؟


* المنفذ 81 = المصابيح الزرقاء.



# الاستعراض الأساسي:
*   معلومات:  
      `binwalk mtdblock2.bin`  
      *   النتيجة:  
 عشرية الوصف عشري * 
--------------------------------------------------------------------------------
0 0x0 Uimage Header، رأس رأس: 64 بايت، رأس CRC: 0x7b9de864، تم الإنشاء: 2019-06-22 02:41:00، صورة الحجم: 1466358 بايت، عنوان البيانات: 0x80010000، نقطة المدخل: 0x80388340، بيانات CRC: 0xb83dca15، نظام التشغيل: Linux، وحدة المعالجة المركزية: MIPS، نوع الصورة: OS Kernel Image، نوع الضغط: LZMA، اسم الصورة:   " Linux-3.10.14  __  isvp  _turkey_  1.0  __]  "  
 64 0x40 بيانات مضغوطة LZMA، خصائص: 0x5D، قاموس الحجم: 16777216 بايت، مضغوط الحجم: -1 بايت  

*   mtdblock2 استخراج التاريخ:  
      `tail -c+65  < mtdblock2.bin >mtdblock2.dataz`   *    *   استخراج الأساس:  
  *     
 *   قائمة برامج التشغيل المدرجة:  
      `strings kernel|grep "^drivers"`  
  < h21  >  قائمة الملفات المصدر:  
      `strings kernel|grep "\.[cChTsS]$"`  
  *    *    
 https: / https يجب أن تساعد github.com/marin-m/vmlinux-to-elf في العثور على الرموز ولكن لا يوجد  < h33  >  البدء ممكن من kallsyms  _token_  الجدول: 0x3aaa1b4  
