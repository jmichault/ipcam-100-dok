---
lang: ar
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: '                                                                                                                                                     _IMP_ ﺔﺠﻣﺮﺒﻟﺍ ﻞﻴﻟﺩ'
---


                                                                                                                                   :ﺎﻨﻫ API ﻖﺋﺎﺛﻭ ﻰﻠﻋ ﻉﻼ﻿ﻃﻻ﻿ﺍ ﻦﻜﻤﻳ  
* [  النسخة الأصلية باللغة الصينية  ](../../zh/includes.zh/html/)  


* [  الانجليزية  ](../../en/includes.en/html/)  


* [  النسخة الفرنسية ترجمتها Google  ](../../fr/includes.fr/html/)  




# _IMP_   \(  _Ingenic Media Platform_  \)   \( ﺮﻈﻧﺍ   _imp\_system.h_  \)

## مفاهيم أساسية
 .ﺞﺋﺎﺘﻧ ﺓﺪﻋ ﺔﻋﻮﻤﺠﻤﻠﻟ ﻥﻮﻜﻳ ﻥﺃ ﻦﻜﻤﻳ .ﻂﻘﻓ ﺓﺪﺣﺍﻭ ﺕﺎﻧﺎﻴﺑ ﻝﺎﺧﺩﺇ ﺓﺎﻨﻗ ﻝﺎﺒﻘﺘﺳﺍ ﺔﻋﻮﻤﺠﻣ ﻞﻜﻟ ﻦﻜﻤﻳﻭ ﺕﺎﻋﻮﻤﺠﻣ ﺓﺪﻋ ﻰﻠﻋ ﺯﺎﻬﺠﻟﺍ ﻱﻮﺘﺤﻳ ﻥﺃ ﻦﻜﻤﻳ .ﺕﺎﻧﺎﻴﺑ ﻝﺎﺧﺩﺇ ﺓﺪﺣﻭ ﺮﻐﺻﺃ ﻲﻫ ﺔﻋﻮﻤﺠﻤﻟ  
      المجموعة هي أيضا حاوية لمعينة   " وظائف  ". انظر التفسير في قسم القناة لمزيد من التفاصيل.  
 3. Eligo   \( =  _Output_  \)    
 الإخراج هو أصغر وحدة إخراج البيانات لكل مجموعة.    
 تتصل القناة عادة بوحدة وظيفية واحدة.    
 على سبيل المثال:   
     -                                                                                                      _JPEG_.  ﺩﻮﻜﻟﺍ ﺔﻔﻴﻇﻭ ﻭﺃ   _H264_   ﺓﺎﻨﻘﻟﺍ ﻞﻤﻜﺗ ، ﺮﻴﻔﺸﺘﻟﺍ ﺯﺎﻬﺠﻟ ﺔﺒﺴﻨﻟﺎﺑ 


     -                                                     ﺓﺎﻨﻘﻟﺍ ءﺎﺸﻧﺇ ﺪﻨﻋ ﺓﺩﺪﺤﻤﻟﺍ ﺔﻴﻣﺯﺭﺍﻮﺨﻟﺍ ﻉﻮﻧ ﺕﺎﻤﻠﻌﻣ ﺪﻳﺪﺤﺗ ﻢﺘﻳﻭ ﺓﺩﺪﺤﻣ ﺔﻴﻣﺯﺭﺍﻮﺧ ﺔﻔﻴﻇﻭ ﺓﺎﻨﻘﻟﺍ ﻞﻤﻜﺗ ،   _IVS_ ﻰﻟﺇ ﺔﺒﺴﻨﻟﺎﺑ


     -  ل  _OSD_، هناك منطقة مشابهة ل   _Channel_، المنطقة هي منطقة مظلمة محددة يمكن أن تكون أعلى   \( صورة  \) غطاء   \( انسداد  \)، إلخ.  


     -                                                                                        ﺔﻋﻮﻤﺠﻣ ﻊﻗﺍﻮﻟﺍ ﻲﻓ ﻲﻫ   _FrameSource_   ﺓﺎﻨﻘﻟﺍﻭ ﺔﻴﻠﺻﺃ ﺓﺭﻮﺻ ﺓﺎﻨﻘﻟﺍ ﺞﺘﻨﺗ ،   _FrameSource_ ﻰﻟﺇ ﺔﺒﺴﻨﻟﺎﺑ 


    
       القناة، كوحدة وظيفية، عادة ما يتم الحفاظ عليها في المجموعة   \( باستثناء   _FrameSource_  \) تلقي البيانات.  

    يختلف أيضًا عدد القنوات التي يمكن تسجيلها بواسطة مجموعة الأجهزة المختلفة.

##                                                                                                                                             \(  _Bind_  \) ﺓﺪﺣﻮﻟﺍ ﻂﺑﺍﺭ

بعد ترتبط مجموعتين ب   _Bind_، سيتم إرسال البيانات من المجموعة المصدر تلقائيا إلى الوجهة تلقائيا.    
 نظرا لأن المجموعة هي أصغر وحدة إدخال البيانات والإخراج هو أصغر وحدة إخراج البيانات، فإن   _deviceID_،   _groupID_   و   _outputID_    _srcCell_   في اثنين من المعلمات   _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_   صالحة.    

                                                                               .ﺕﺎﻧﺎﻴﺑ ﻝﺎﺧﺩﺈﻛ ﻰﻨﻌﻣ ﻪﻟ ﻥﻮﻜﻳ ﻻ﻿   _outputID_   ﻥﺈﻓ ،   _groupID_ ﻭ   _deviceID_   ـﻟ ﻂﻘﻓ ﺎﺤًﻟﺎﺻ   _dstCell_   ﻥﻮﻜﻳ ﺎﻤﻨﻴﺑ 

مثال 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
                                                                                        <Encoder. <h3 ﻰﻟﺇ FrameSource ﻦﻣ ﺎﻃًﺎﺒﺗﺭﺍ ﺊﺸﻨﺗ ﺔﻋﻮﻤﺠﻣ    
 *  ﺊﺸﻨﻳ :ﺔﺠﻴﺘﻨﻟﺍ

*                                                                               _JPEG_.  ﻭ   _H264_   :ﻥﺎﺠﺘﻨﻣ ﺎﻬﻳﺪﻟ Encoder Group ﻥﺈﻓ ﺍﺬﻟ ، Encoder Group ﻲﻓ ﻦﻴﺗﺎﻨﻗ ﻞﻴﺠﺴﺗ ﻢﺗ 



المثال 2:
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
                                                                                                                   .ﺓﺎﻨﻘﻟﺍ ﻲﺋﺎﻨﺛ ﺰﻣﺭ :  _Bind_  ﻲﺟﺫﻮﻤﻧ ﻖﻴﺒﻄﺗ ﻮﻫ ﻖﻴﺒﻄﺗ 

                                                                                             .ﻡﺎﻈﻨﻟﺍ ﺔﺌﻴﻬﺗ ﺪﻨﻋ ﻁﺎﺒﺗﺭﻻ﻿ﺍ ﺕﺎﻴﻠﻤﻋ ﻊﻴﻤﺟ ءﺍﺮﺟﺈﺑ ﻰﺻﻮﻳ  
  *   :ﺕﺎﻈﺣﻼ﻿ﻣ 

## المهام

### _int IMP\_System\_Init \(void \)_
                                                                                                                                           _IMP_.  ﻡﺎﻈﻨﻟﺍ ﻞﻴﻐﺸﺗ ءﺪﺑ 
### _int IMP\_System\_Exit \(void\)_

                                                                    .ﺓﺰﻬﺟﻷ﻿ﺍ ﺓﺪﺣﻭ ﻞﻴﻐﺸﺗ ﻑﺎﻘﻳﺇ ﻢﺘﻴﺳﻭ ،   _handles_   _IMP_   ﻭ ﺓﺮﻛﺍﺬﻟﺍ ﻞﻛ ﺮﻳﺮﺤﺗ ﻢﺘﻴﺳ ، ﺔﻔﻴﻇﻮﻟﺍ ﻩﺬﻫ ءﺎﻋﺪﺘﺳﺍ ﺪﻌﺑ 

### _int64\_t IMP\_System\_GetTimeStamp \(void\)_

                                                                                   .ﺔﻴﻧﺎﺛﻭﺮﻜﻴﻤﻟﺎﺑ ﺖﻗﻮﻟﺍ :ﺓﺩﻮﻌﻟﺍ    
 .ﺔﻴﻧﺎﺛﻭﺮﻜﻴﻤﻟﺎﺑ   _IMP_   ﻡﺎﻈﻨﻟﺍ ﺖﻗﻭ ﻞﻘﺣ ﻰﻠﻋ ﻞﺼﺣﺍ

### _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_
                                                                                       .ﺡﺎﺠﻨﻟﺍ ﺔﻟﺎﺣ ﻲﻓ 0 :ﺓﺩﻮﻌﻟﺍ    
 .ﺔﻴﻧﺎﺛﻭﺮﻜﻴﻤﻟﺎﺑ   _IMP_   ﻲﻨﻣﺰﻟﺍ ﻊﺑﺎﻄﻟﺍ ﻡﺎﻈﻧ ﺩﺪﺣ

### _uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_

اقرأ قيمة التسجيل 32 بت.  

### _void IMP\_System\_WriteReg32 \(uint32_  ر regaddr، قيمة UINT32  _t\)_
 

ملاحظة: يرجى الاتصال بواجهة برمجة التطبيقات هذه بعناية والتحقق من معنى السجل ، وإلا فقد يتسبب ذلك في حدوث أخطاء في النظام.

### _int IMP_  النظام  _GetVersion \(IMPVersion * pstVersion\)_

 

### _const char * IMP_  النظام  _GetCPUInfo \(void\)_
احصل على معلومات حول طراز وحدة المعالجة المركزية.  
ملاحظة: القيمة المرجعة هي سلسلة من طراز وحدة المعالجة المركزية ، على سبيل المثال ، بالنسبة إلى T10 ، هناك "T10"و "T10-Lite".

### _int IMP_  النظام   \(

ربط بين خلية المصدر والوجهة.

ملاحظة 1: وفقًا لمفاهيم الجهاز والمجموعة والإخراج ، يمكن أن يكون لكل جهاز عدة مجموعات ، ويمكن أن يكون لكل مجموعة عدة مخرجات ، ويتم استخدام المجموعة كواجهة إدخال للجهاز ، ويتم استخدام الإخراج كواجهة منتج للجهاز. لذلك ، يقوم الارتباط فعليًا بتوصيل إخراج معين لجهاز الإخراج بمجموعة معينة من جهاز الإدخال.

 

### _int IMP_  النظام   \(
فك تجميع المصادر والوجهات. 

### _int IMP_  النظام   \(

يسترجع المعلومات من الخلية المصدر المتعلقة بالوجهة.

