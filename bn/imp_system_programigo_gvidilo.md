---
lang: bn
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'প্রোগ্রামিং গাইড   _IMP_'
---


  
* [  চীনা  ](../../zh/includes.zh/html/)   মূল সংস্করণ


* [  ইংরেজি  ](../../en/includes.en/html/)  


* [  ফরাসি সংস্করণ Google  ](../../fr/includes.fr/html/)   দ্বারা অনুবাদ করা হয়েছে




# _IMP_   \(  _Ingenic Media Platform_  \)   \(   _imp\_system.h_  \) দেখুন

## মৌলিক ধারণা
  
      গ্রুপটি নির্দিষ্ট   " ফাংশন  " এর জন্য একটি ধারক। আরো বিস্তারিত জানার জন্য চ্যানেল বিভাগে ব্যাখ্যা দেখুন।  
 3. Eligo   \( =  _Output_  \)    
 আউটপুটটি গ্রুপ প্রতি ক্ষুদ্রতম ডাটা আউটপুট ইউনিট।    
 চ্যানেল সাধারণত একটি একক কার্যকরী ইউনিট সম্পর্কিত হয়।    
 উদাহরণস্বরূপ:   
     -   


     -    _IVS_ এর জন্য, একটি চ্যানেল একটি নির্দিষ্ট অ্যালগরিদমের ফাংশনটি সম্পন্ন করে এবং নির্দিষ্ট অ্যালগরিদম বৈশিষ্টসূচক পরামিতিগুলি চ্যানেল তৈরি করার সময় নির্দিষ্ট করা হয়েছে 


     -   _OSD_ এর জন্য   _Channel_ এর অনুরূপ একটি অঞ্চল রয়েছে, একটি অঞ্চল একটি নির্দিষ্ট সুপারমেটেটেড এলাকা যা একটি শীর্ষ   \( চিত্র  \) কভার   \( occlusion  \), ইত্যাদি হতে পারে। . 


     -   


    
       চ্যানেল, একটি কার্যকরী ইউনিট হিসাবে, সাধারণত   _FrameSource_  \) ডেটা গ্রহণ করে   _FrameSource_  গোষ্ঠীতে সংরক্ষিত করা হবে। . 

    বিভিন্ন ডিভাইসের গ্রুপ দ্বারা রেকর্ড করা যায় এমন চ্যানেলের সংখ্যাও আলাদা is

## মডিউল লিঙ্ক   \(  _Bind_  \)

দুইটি গ্রুপের সাথে সংযোগ করা হয়েছে   _Bind_ দ্বারা, সোর্স গ্রুপের ডেটা স্বয়ংক্রিয়ভাবে গন্তব্যে পাঠাবে।    
 গ্রুপটি ক্ষুদ্রতম ডেটা ইনপুট ইউনিট এবং আউটপুটটি ক্ষুদ্রতম ডাটা আউটপুট ইউনিট,   _deviceID_,   _groupID_   এবং   _outputID_    _srcCell_   দুটি প্যারামিটারগুলিতে   _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_   বৈধ। .   

 

উদাহরণ 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
ফলাফল:    
 *  একটি গ্রুপ একটি গ্রুপ তৈরি করে যা ফ্রেমসোর্স থেকে এনকোডার থেকে একটি লিঙ্ক তৈরি করে। .

*  



উদাহরণ 2:
```
// flux de données principal
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};
IMPCell osd_grp0 = {DEV_ID_OSD, 0, 0};
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0};
int ret = IMP_System_Bind(&fs_chn0, &osd_grp0);
if (ret < 0)
    printf("Bind FrameSource Channel0 and OSD Group0 failed\n");

int ret = IMP_System_Bind(&osd_grp0, &enc_grp0);
if (ret < 0)
    printf("Bind OSD Group0 and Encoder Group0 failed\n");

// flux de données lié 
IMPCell fs_chn1_output0 = {DEV_ID_FS, 1, 0};
IMPCell ivs_grp0 = {DEV_ID_IVS, 0, 0};
IMPCell osd_grp1 = {DEV_ID_OSD, 1, 0};
IMPCell enc_grp1 = {DEV_ID_ENC, 1, 0};

int ret = IMP_System_Bind(&fs_chn1_output0, &ivs_grp0);
if (ret < 0)
    printf("Bind FrameSource Channel1 and IVS Group0 failed\n");

int ret = IMP_System_Bind(&ivs_grp0, &osd_grp1);
if (ret < 0)
    printf("Bind IVS Group0 and OSD Group1 failed\n");

int ret = IMP_System_Bind(&osd_grp1, &enc_grp1);
if (ret < 0)
    printf("Bind OSD Group1 and Encoder Group1 failed\n");
```
 

 

## কার্যাদি

### _int IMP\_System\_Init \(void \)_.
 
### _int IMP\_System\_Exit \(void\)_.

 

### _int64\_t IMP\_System\_GetTimeStamp \(void\)_.

মাইক্রোসেকেন্ডে   _IMP_   সিস্টেমের সময় ক্ষেত্রটি পান।    
 রিটার্ন: মাইক্রোকেন্ডে সময়। .

### মাইক্রোসেকেন্ডে _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_ সিস্টেমের সময় ক্ষেত্রটি পান। \_ রিটার্ন: মাইক্রোকেন্ডে সময়।  \(.
Microseconds মধ্যে টাইমস্ট্যাম্প   _IMP_   সিস্টেম নির্ধারণ করুন।    
 রিটার্ন: 0 সফল হলে 0। .

### Microseconds মধ্যে টাইমস্ট্যাম্প _uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_ সিস্টেম নির্ধারণ করুন। \_ রিটার্ন: 0 সফল হলে 0। \_.

32-বিট নিবন্ধকের মান পড়ুন।  

### _void IMP\_System\_WriteReg32 \(uint32_  টি রেগেডড্ড, মান UINT32  _t\)_
 

দ্রষ্টব্য: দয়া করে এই API এ সাবধানতার সাথে কল করুন এবং রেজিস্ট্রিটির অর্থ যাচাই করুন, অন্যথায় এটি সিস্টেমের ত্রুটির কারণ হতে পারে।

### _int IMP_  সিস্টেম  _GetVersion \(IMPVersion * pstVersion\)_

 

### _const char * IMP_  সিস্টেম  _GetCPUInfo \(void\)_
সিপিইউ মডেল সম্পর্কে তথ্য পান।  
দ্রষ্টব্য: রিটার্ন মানটি সিপিইউ মডেলের একটি স্ট্রিং, উদাহরণস্বরূপ, টি 10 ​​এর জন্য রয়েছে "টি 10 ​​"এবং "টি 10-লাইট"।

### _int IMP_  সিস্টেম   \(

উত্স ঘর এবং গন্তব্যের মধ্যে লিঙ্ক।

নোট 1: ডিভাইস, গোষ্ঠী এবং আউটপুট ধারণাগুলি অনুসারে, প্রতিটি ডিভাইসে বিভিন্ন গ্রুপ থাকতে পারে এবং প্রতিটি গ্রুপের বেশ কয়েকটি আউটপুট থাকতে পারে, গ্রুপটি ডিভাইস ইনপুট ইন্টারফেস হিসাবে ব্যবহৃত হয়, এবং আউটপুট ডিভাইস পণ্য ইন্টারফেস হিসাবে ব্যবহৃত হয়। সুতরাং লিঙ্কটি আউটপুট ডিভাইসের একটি নির্দিষ্ট আউটপুটকে ইনপুট ডিভাইসের একটি নির্দিষ্ট গ্রুপের সাথে সংযুক্ত করে।

 

### _int IMP_  সিস্টেম   \(
উত্স এবং গন্তব্যগুলি গ্রুপমুক্ত করুন। 

### _int IMP_  সিস্টেম   \(

গন্তব্য সম্পর্কিত সোর্স সেল থেকে তথ্য পুনরুদ্ধার করে।

