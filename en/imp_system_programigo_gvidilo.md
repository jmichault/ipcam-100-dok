---
lang: en
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'Programming Guide   _IMP_'
---


APIs' documentation can be seen here:   
* [  Original version in Chinese  ](../../zh/includes.zh/html/)  


* [  English  ](../../en/includes.en/html/)  


* [  French version Translated by Google  ](../../fr/includes.fr/html/)  




# _IMP_   \(  _Ingenic Media Platform_  \)   \( See   _imp\_system.h_  \)

## basic concepts
The T20 / T21 program is based on the following concepts:  
 1. Device   \( =  _Device_  \)    
 The device completes function.   
      The group is also a container for specific   " Functions  ". See the explanation in the channel section for more details.  
 3. Eligo   \( =  _Output_  \)    
 The output is the smallest data output unit per group.    
 The channel is usually related to a single functional unit.    
 For example:   
     -  For the Codel, channel completes the   _H264_   or code function   _JPEG_.  


     -  For   _IVS_, a channel completes the function of a specific algorithm and the specific algorithm typical parameters are specified during creating the channel 


     -  For  _OSD_, there is a region similar to   _Channel_, a region is a specific supermetated area that can be a top   \( image  \) cover   \( occlusion  \), etc.  


     -  For   _FrameSource_, a channel produces an original image and the channel   _FrameSource_   is actually a group  


    
       The channel, as a functional unit, usually be preserved in the   \( group except   _FrameSource_  \) Receive data.  

    The number of channels that can be recorded by the group of various devices is also different.

## Module link   \(  _Bind_  \)

After two groups are linked by   _Bind_, data from the source group will automatically send to the destination.    
 Since the group is the smallest data input unit and the output is the smallest data output unit, the   _deviceID_,   _groupID_   and   _outputID_    _srcCell_   in the two parameters of   _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_   are valid.    

 

Example 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
Result:    
 *  A group generates a group that generates a link from Framesource to Encoder. 

*  



Example 2:
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
Apply is a typical application   _Bind_ : two-channel code.  

Notes:  
  *   It is recommended that all link operations are made when initializing the system.  

## Functions

### _int IMP\_System\_Init \(void \)_
Beginning of the   _IMP_ system.  
### _int IMP\_System\_Exit \(void\)_

After calling this function, all the memory and   _handles_   _IMP_   will be released, and the hardware unit will be closed.  

### _int64\_t IMP\_System\_GetTimeStamp \(void\)_

Get the timing field of the   _IMP_   system in microseconds. 

### _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_
Define the Timestamp   _IMP_   system in microseconds. 

### _uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_

Read the value of a 32-bit register.  

### _void IMP\_System\_WriteReg32 \(uint32_  t regaddr, value uint32  _t\)_
Write the value in the 32-bit register.  

Note: Please call this API carefully and check the meaning of the registry, otherwise it may cause system errors.

### _int IMP_  System  _GetVersion \(IMPVersion * pstVersion\)_ T Regaddr, Value Uint32 \)

Get the system of the   _IMP_ system.  

### _const char * IMP_  System  _GetCPUInfo \(void\)_
Get information about the CPU model.  
Note: The return value is a string of CPU model, for example, for T10 there is "T10"and "T10-Lite".

### _int IMP_  System   \(

Link between source cell and destination.

Note 1: According to the concepts of Device, Group and Output, each device can have several groups, and each group can have several outputs, Group is used as Device input interface, and Output is used as Device product interface. Therefore the link actually connects a certain output of the output device to a certain Group of the input device.

Note 2: After a successful link, the data generated by   _srcCell_   (  Eligo  )   will be automatically transferred to the destination   (  Group  ).  

### _int IMP_  System   \(
Ungroup the sources and destinations. 

### _int IMP_  System   \(

Retrieves information from the source cell related to the destination.

