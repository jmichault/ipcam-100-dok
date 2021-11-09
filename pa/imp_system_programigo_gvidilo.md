---
lang: pa
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'ਪ੍ਰੋਗਰਾਮਿੰਗ ਗਾਈਡ   _IMP_'
---


ਅਪਿਸ ਦੇ ਦਸਤਾਵੇਜ਼ ਇੱਥੇ ਵੇਖੇ ਜਾ ਸਕਦੇ ਹਨ:  
* [  ਚੀਨੀ ਵਿੱਚ ਅਸਲ ਸੰਸਕਰਣ  ](../../zh/includes.zh/html/)  


* [  ਅੰਗਰੇਜ਼ੀ  ](../../en/includes.en/html/)  


* [  ਫ੍ਰੈਂਚ ਵਰਜਨ ਨੇ ਗੂਗਲ <ਐਚ 2>  ਦੁਆਰਾ ਅਨੁਵਾਦ ਕੀਤਾ




# _IMP_   \( \)   \(   _imp\_system.h_  \) ਦੇਖੋ

## ਬੁਨਿਆਦੀ ਧਾਰਨਾ
T20 / T21 ਪ੍ਰੋਗਰਾਮ ਹੇਠ ਲਿਖੀਆਂ ਧਾਰਨਾਵਾਂ ਤੇ ਅਧਾਰਤ ਹੈ:  
 = ਡਿਵਾਈਸ   \( =    
 ਡਿਵਾਈਸ ਫੰਕਸ਼ਨ ਦੇ ਅਧਾਰ ਤੇ. ਉਦਾਹਰਣ:  
       *    _Framesource_ : ਵੀਡੀਓ ਕਲਿੱਪਾਂ ਦੀ ਆਉਟਪੁੱਟ ਨੂੰ ਪੂਰਾ ਕਰੋ.  
       *    _Encoder_ : ਵੀਡੀਓ ਕੋਡ ਜਾਂ ਚਿੱਤਰ ਕੋਡ ਫੰਕਸ਼ਨ ਨੂੰ ਪੂਰਾ ਕਰੋ.  
 ਸਮੂਹ   \( =  _Group_     
    
 ਸਮੂਹ ਸਭ ਤੋਂ ਛੋਟਾ ਡਾਟਾ-ਇਨਪੁਟ ਯੂਨਿਟ ਹੈ. ਇੱਕ ਉਪਕਰਣ ਵਿੱਚ ਮਲਟੀਪਲ ਸਮੂਹ ਹੋ ਸਕਦੇ ਹਨ ਅਤੇ ਹਰੇਕ ਸਮੂਹ ਨੂੰ ਸਿਰਫ ਇੱਕ ਹੀ ਡਾਟਾ ਇੰਪੁੱਟ ਚੈਨਲ ਪ੍ਰਾਪਤ ਹੋ ਸਕਦਾ ਹੈ. ਸਮੂਹ ਦੇ ਕਈ ਨਤੀਜੇ ਹੋ ਸਕਦੇ ਹਨ.   
      ਸਮੂਹ ਵਿਸ਼ੇਸ਼   " ਫੰਕਸ਼ਨਾਂ  " ਲਈ ਇੱਕ ਕੰਟੇਨਰ ਵੀ ਹੈ. ਵਧੇਰੇ ਜਾਣਕਾਰੀ ਲਈ ਚੈਨਲ ਭਾਗ ਵਿੱਚ ਸਪਸ਼ਟੀਕਰਨ ਵੇਖੋ.  
 3. ਫਿਰੋ   \( =  _Output_  \)    
 ਆਉਟਪੁੱਟ ਪ੍ਰਤੀ ਸਮੂਹ ਪ੍ਰਤੀ ਸਮੂਹ ਸਭ ਤੋਂ ਛੋਟਾ ਜਿਹਾ ਡਾਟਾ ਆਉਟਪੁੱਟ ਯੂਨਿਟ ਹੈ.    
 ਚੈਨਲ ਆਮ ਤੌਰ 'ਤੇ ਇਕੱਲੇ ਕਾਰਜਸ਼ੀਲ ਇਕਾਈ ਨਾਲ ਸਬੰਧਤ ਹੁੰਦਾ ਹੈ. <P11> ਉਦਾਹਰਣ ਲਈ:   
     -  ਕੋਡੈਲ ਲਈ, ਚੈਨਲ   _H264_   ਜਾਂ ਕੋਡ ਫੰਕਸ਼ਨ   _JPEG_ ਨੂੰ ਪੂਰਾ ਕਰਦਾ ਹੈ.  


     -    _IVS_ ਲਈ, ਇੱਕ ਚੈਨਲ ਲਈ ਇੱਕ ਖਾਸ ਐਲਗੋਰਿਦਮ ਦੇ ਕੰਮ ਨੂੰ ਪੂਰਾ ਕਰਦਾ ਹੈ ਅਤੇ ਚੈਨਲ ਬਣਾਉਣ ਦੇ ਖਾਸ ਪੈਰਾਮੀਟਰ ਚੈਨਲ ਨੂੰ  ਬਣਾਉਣ ਦੇ ਦੌਰਾਨ ਨਿਰਧਾਰਤ ਕੀਤੇ ਗਏ ਹਨ


     -  ਲਈ  _OSD_ ਦੇ ਸਮਾਨ ਖੇਤਰ ਹੈ, ਇੱਕ ਖੇਤਰ ਇੱਕ ਖਾਸ ਸੁਪਰ ਵਿਗਾੜ ਖੇਤਰ ਹੈ ਜੋ ਇੱਕ ਚੋਟੀ ਦਾ   \( Ext   \( CascLacts  \), ਆਦਿ ਹੋ ਸਕਦਾ ਹੈ.  


     -  ਲਈ   _FrameSource_ ਲਈ, ਇੱਕ ਚੈਨਲ ਇੱਕ ਅਸਲੀ ਚਿੱਤਰ ਅਤੇ ਚੈਨਲ ਬਣਾਉਂਦਾ ਹੈ   _FrameSource_   ਅਸਲ ਵਿੱਚ ਇੱਕ ਸਮੂਹ  ਤਿਆਰ ਕਰਦਾ ਹੈ 


    
       ਚੈਨਲ, ਇੱਕ ਕਾਰਜਸ਼ੀਲ ਇਕਾਈ ਦੇ ਤੌਰ ਤੇ, ਆਮ ਤੌਰ ਤੇ   \( ਸਮੂਹ ਨੂੰ ਸਿਵਾਏ   \( \) ਡਾਟਾ ਪ੍ਰਾਪਤ ਕਰੋ.  

    ਵੱਖ-ਵੱਖ ਡਿਵਾਈਸਾਂ ਦੇ ਸਮੂਹ ਦੁਆਰਾ ਰਿਕਾਰਡ ਕੀਤੇ ਜਾ ਸਕਦੇ ਚੈਨਲਾਂ ਦੀ ਗਿਣਤੀ ਵੀ ਵੱਖਰੀ ਹੈ.

## ਮੋਡੀ ule ਲ ਲਿੰਕ   \(  _Bind_  \)

ਦੋ ਸਮੂਹਾਂ ਨਾਲ ਸੰਪਰਕ ਕਰੋ   _Bind_ ਦੁਆਰਾ, ਸਰੋਤ ਸਮੂਹ ਤੋਂ ਡੇਟਾ ਆਪਣੇ ਆਪ ਮੰਜ਼ਿਲ ਤੇ ਭੇਜ ਦੇਵੇਗਾ.    
 ਕਿਉਂਕਿ ਸਮੂਹ ਸਭ ਤੋਂ ਛੋਟਾ ਡਾਟਾ ਇਨਪੁਟ ਯੂਨਿਟ ਹੈ ਅਤੇ ਆਉਟਪੁਟ ਸਭ ਤੋਂ ਛੋਟਾ ਡੇਟਾ ਆਉਟਪੁੱਟ ਯੂਨਿਟ,   _groupID_     _groupID_     _Bind_   _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_     _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_   _srcCell_     _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_   _srcCell_     _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_   _srcCell_   _srcCell_   _srcCell_   _srcCell_  ) ਵੈਧ ਹਨ.    

ਜਦੋਂ ਕਿ   _dstCell_   ਸਿਰਫ   _deviceID_   ਅਤੇ   _groupID_,   _outputID_   ਲਈ ਯੋਗ ਹੈ.  

ਉਦਾਹਰਨ 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
ਨਤੀਜਾ: *  *  ਇੱਕ ਸਮੂਹ ਇੱਕ ਸਮੂਹ ਤਿਆਰ ਕਰਦਾ ਹੈ ਜੋ ਕਿ ਇਨਕੋਡਰ ਕਰਨ ਲਈ ਫਰੇਸੋਰਸ ਤੋਂ ਲਿੰਕ ਤਿਆਰ ਕਰਦਾ ਹੈ. 

* ਦੋ ਚੈਨਲ ਏਨਕੋਡਰ ਸਮੂਹ ਵਿੱਚ ਰਜਿਸਟਰ ਹੋਏ ਹਨ, ਇਸ ਲਈ ਏਨਕੋਡਰ ਸਮੂਹ ਵਿੱਚ ਦੋ ਉਤਪਾਦ ਹਨ:   _H264_   ਅਤੇ   _JPEG_.  



ਉਦਾਹਰਣ 2:
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
ਲਾਗੂ ਕਰੋ ਇੱਕ ਆਮ ਕਾਰਜ   _Bind_ : ਦੋ-ਚੈਨਲ ਕੋਡ.  

ਨੋਟਸ:  
  *   ਸਿਸਟਮ ਨੂੰ ਅਰੰਭ ਕਰਨ ਵੇਲੇ ਸਾਰੇ ਲਿੰਕ ਓਪਰੇਸ਼ਨ ਕੀਤੇ ਜਾਂਦੇ ਹਨ.  

## ਕਾਰਜ

### _int IMP\_System\_Init \(void \)_
  _IMP_ ਸਿਸਟਮ ਦੀ ਸ਼ੁਰੂਆਤ.  
### _int IMP\_System\_Exit \(void\)_ ਸਿਸਟਮ ਦੀ ਸ਼ੁਰੂਆਤ. \_

ਇਸ ਫੰਕਸ਼ਨ ਨੂੰ ਬੁਲਾਉਣ ਤੋਂ ਬਾਅਦ, ਸਾਰੀ ਮੈਮੋਰੀ ਅਤੇ   _handles_   _IMP_   ਜਾਰੀ ਕੀਤੇ ਜਾਣਗੇ, ਅਤੇ ਹਾਰਡਵੇਅਰ ਯੂਨਿਟ ਬੰਦ ਹੋ ਜਾਵੇਗਾ.  

### ਇਸ ਫੰਕਸ਼ਨ ਨੂੰ ਬੁਲਾਉਣ ਤੋਂ ਬਾਅਦ, ਸਾਰੀ ਮੈਮੋਰੀ ਅਤੇ _int64\_t IMP\_System\_GetTimeStamp \(void\)_ \_ ਜਾਰੀ ਕੀਤੇ ਜਾਣਗੇ, ਅਤੇ ਹਾਰਡਵੇਅਰ ਯੂਨਿਟ ਬੰਦ ਹੋ ਜਾਵੇਗਾ.  \(

ਮਾਈਕ੍ਰੋਜ਼ਕੌਂਡਸ ਵਿੱਚ   _IMP_   ਸਿਸਟਮ ਦਾ ਟਾਈਮਿੰਗ ਖੇਤਰ ਪ੍ਰਾਪਤ ਕਰੋ.    
 ਵਾਪਸੀ: ਮਾਈਕ੍ਰੋਕੇਕੈਂਡ ਵਿੱਚ ਸਮਾਂ. 

### ਮਾਈਕ੍ਰੋਜ਼ਕੌਂਡਸ ਵਿੱਚ _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_ ਸਿਸਟਮ ਦਾ ਟਾਈਮਿੰਗ ਖੇਤਰ ਪ੍ਰਾਪਤ ਕਰੋ. \_ ਵਾਪਸੀ: ਮਾਈਕ੍ਰੋਕੇਕੈਂਡ ਵਿੱਚ ਸਮਾਂ.  \(
ਟਾਈਮਸਟੈਂਪ <ਮਾਈਕ੍ਰੋਜ਼ਕੌਂਡ ਵਿੱਚ ਸਿਸਟਮ ਨੂੰ ਪ੍ਰਭਾਸ਼ਿਤ ਕਰੋ.    
 ਵਾਪਸੀ: 0 ਜੇ ਸਫਲ. 

### ਟਾਈਮਸਟੈਂਪ <ਮਾਈਕ੍ਰੋਜ਼ਕੌਂਡ ਵਿੱਚ ਸਿਸਟਮ ਨੂੰ ਪ੍ਰਭਾਸ਼ਿਤ ਕਰੋ. \_ ਵਾਪਸੀ: 0 ਜੇ ਸਫਲ. \_

ਇੱਕ 32-ਬਿੱਟ ਰਜਿਸਟਰ ਦਾ ਮੁੱਲ ਪੜ੍ਹੋ.  

### _void IMP\_System\_WriteReg32 \(uint32_  t regaddr, ਮੁੱਲ Uint32  _t\)_
32-ਬਿੱਟ ਰਜਿਸਟਰ ਵਿਚ ਮੁੱਲ ਲਿਖੋ.  

ਨੋਟ: ਕਿਰਪਾ ਕਰਕੇ ਇਸ API ਨੂੰ ਧਿਆਨ ਨਾਲ ਕਾਲ ਕਰੋ ਅਤੇ ਰਜਿਸਟਰੀ ਦੇ ਅਰਥਾਂ ਦੀ ਜਾਂਚ ਕਰੋ, ਨਹੀਂ ਤਾਂ ਇਹ ਸਿਸਟਮ ਦੀਆਂ ਗਲਤੀਆਂ ਦਾ ਕਾਰਨ ਬਣ ਸਕਦਾ ਹੈ.

### _int IMP_  ਸਿਸਟਮ  _GetVersion \(IMPVersion * pstVersion\)_

  _IMP_ ਸਿਸਟਮ ਦੀ ਪ੍ਰਣਾਲੀ ਪ੍ਰਾਪਤ ਕਰੋ.  

### _const char * IMP_  ਸਿਸਟਮ  _GetCPUInfo \(void\)_
ਸੀਪੀਯੂ ਮਾਡਲ ਬਾਰੇ ਜਾਣਕਾਰੀ ਪ੍ਰਾਪਤ ਕਰੋ.  
ਨੋਟ: ਵਾਪਸੀ ਮੁੱਲ ਸੀਪੀਯੂ ਮਾਡਲ ਦੀ ਇੱਕ ਸਤਰ ਹੈ, ਉਦਾਹਰਣ ਵਜੋਂ, ਟੀ 10 ਲਈ "ਟੀ 10"ਅਤੇ "ਟੀ 10-ਲਾਈਟ"ਹੈ.

### _int IMP_  ਸਿਸਟਮ   \(

ਸਰੋਤ ਸੈੱਲ ਅਤੇ ਮੰਜ਼ਿਲ ਦੇ ਵਿਚਕਾਰ ਲਿੰਕ.

ਨੋਟ 1: ਡਿਵਾਈਸ, ਸਮੂਹ ਅਤੇ ਆਉਟਪੁੱਟ ਦੀਆਂ ਧਾਰਨਾਵਾਂ ਦੇ ਅਨੁਸਾਰ, ਹਰੇਕ ਡਿਵਾਈਸ ਦੇ ਕਈ ਸਮੂਹ ਹੋ ਸਕਦੇ ਹਨ, ਅਤੇ ਹਰੇਕ ਸਮੂਹ ਦੇ ਕਈ ਆਉਟਪੁੱਟ ਹੋ ਸਕਦੇ ਹਨ, ਸਮੂਹ ਨੂੰ ਡਿਵਾਈਸ ਇੰਪੁੱਟ ਇੰਟਰਫੇਸ ਵਜੋਂ ਵਰਤਿਆ ਜਾਂਦਾ ਹੈ, ਅਤੇ ਆਉਟਪੁੱਟ ਨੂੰ ਡਿਵਾਈਸ ਉਤਪਾਦ ਇੰਟਰਫੇਸ ਵਜੋਂ ਵਰਤਿਆ ਜਾਂਦਾ ਹੈ. ਇਸਲਈ ਲਿੰਕ ਅਸਲ ਵਿੱਚ ਆਉਟਪੁੱਟ ਡਿਵਾਈਸ ਦੇ ਇੱਕ ਖਾਸ ਆਉਟਪੁੱਟ ਨੂੰ ਇਨਪੁਟ ਡਿਵਾਈਸ ਦੇ ਇੱਕ ਸਮੂਹ ਨਾਲ ਜੋੜਦਾ ਹੈ.

ਨੋਟ 2: ਇੱਕ ਸਫਲ ਲਿੰਕ ਤੋਂ ਬਾਅਦ,   _srcCell_   (  F3> FAT ਨੂੰ ਆਪਣੇ ਆਪ ਮੰਜ਼ਿਲ   (  ਸਮੂਹ  ) ਤੱਕ ਤਬਦੀਲ ਕੀਤਾ ਜਾਏਗਾ.  

### _int IMP_  ਸਿਸਟਮ   \(
ਸਰੋਤਾਂ ਅਤੇ ਮੰਜ਼ਿਲਾਂ ਦਾ ਸੰਗਠਨ ਕਰੋ. 

### _int IMP_  ਸਿਸਟਮ   \(

ਮੰਜ਼ਿਲ ਨਾਲ ਜੁੜੇ ਸਰੋਤ ਸੈੱਲ ਤੋਂ ਜਾਣਕਾਰੀ ਪ੍ਰਾਪਤ ਕਰਦਾ ਹੈ.

