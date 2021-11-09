---
lang: zh
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: '编程指南  _IMP_'
---


APIS的文档可以在这里看到：  
* [ 中文 ](../../zh/includes.zh/html/)  的原始版本


* [ 英文 ](../../en/includes.en/html/)  


* [ 法语版本由Google  ](../../fr/includes.fr/html/)  翻译




# _IMP_   \(  _Ingenic Media Platform_  \)   \(见  _imp\_system.h_  \)

## 基本概念
T20 / T21程序基于以下概念： 
 1.设备  \( =  _Device_  \)    
该设备完成功能。示例： 
       *    _Framesource_ ：完成视频剪辑的输出。  
       *    _Encoder_ ：完成视频代码或图像代码功能。  
 2.组  \( =  _Group_  \) \)本组是最小的数据输入单元。设备可以具有多个组，并且每个组只能接收一个数据输入通道。该组可以有几个结果。   
     该组也是特定  "功能 "的容器。有关更多详细信息，请参阅“通道”部分中的说明。  
 3. Eligo   \( =  _Output_  \)    
输出是每组最小的数据输出单元。    
信道通常与单个功能单元相关。    
例如：  
     -  对于Codel，通道完成  _H264_  或代码功能  _JPEG_。  


     -  对于  _IVS_，通道完成特定算法的功能，并且在创建通道期间指定了特定算法典型参数


     -  对于 _OSD_，存在类似于  _Channel_的区域，区域是可以是顶部  \(图像 \)盖子  \(遮挡 \)等的特定的超细化区域。  


     -  对于  _FrameSource_，频道产生原始图像，并且通道  _FrameSource_  实际上是一个组 


    
      作为功能单元的信道通常保留在  _FrameSource_  \)接收数据之外的  \(组中。  

    各种设备组可以记录的通道数也不同。

## 模块链接  \(  _Bind_  \)

通过  _Bind_链接两组后，来自源组的数据将自动发送到目标。    
因为组是最小的数据输入单元和输出是最小的数据输出单元，所述  _deviceID_，  _groupID_  和  _outputID_    _srcCell_  在  _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_  的两个参数是有效的。    

虽然  _dstCell_  仅对  _deviceID_  和  _groupID_有效，但是  _outputID_  不喜欢数据入口。  

范例1： 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
结果：   
 * 组生成一个组，该组生成从框架到编码器的链接。 

* 在编码器组中注册了两个通道，因此编码器组有两种产品：  _H264_  和  _JPEG_。  



示例2：
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
应用是一个典型的应用程序  _Bind_ ：双通道代码。  

注意： 
  *  建议在初始化系统时进行所有链路操作。  

## 功能

### _int IMP\_System\_Init \(void \)_
  _IMP_系统的开头。  
### _int IMP\_System\_Exit \(void\)_系统的开头。 \_

调用此功能后，将释放所有内存和  _handles_   _IMP_  ，硬件单元将关闭。  

### 调用此功能后，将释放所有内存和_int64\_t IMP\_System\_GetTimeStamp \(void\)_ \_，硬件单元将关闭。  \(

获取microSeconds中  _IMP_  系统的定时字段。    
返回：微量的时间。 

### 获取microSeconds中_int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_系统的定时字段。 \_返回：微量的时间。  \(
以微秒为单位定义时间戳  _IMP_  系统。    
返回：如果成功，则为0。 

### 以微秒为单位定义时间戳_uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_系统。 \_返回：如果成功，则为0。 \_

读取32位寄存器的值。  

### _void IMP\_System\_WriteReg32 \(uint32_  t regaddr，值uint32  _t\)_
在32位寄存器中写入值。  

注意：请仔细调用此API并检查注册表的含义，否则可能导致系统错误。

### _int IMP_ 系统 _GetVersion \(IMPVersion * pstVersion\)_

获取  _IMP_系统的系统。  

### _const char * IMP_ 系统 _GetCPUInfo \(void\)_
获取有关CPU型号的信息。  
注意：返回值是一串CPU模型，例如，对于T10，存在 "T10"和 "T10-Lite"。

### _int IMP_ 系统  \(

源单元格和目标之间的链接。

注1：根据设备，组和输出的概念，每个设备可以有多个组，每个组可以有多个输出，组用作设备输入接口，输出用作设备产品接口。因此，链接实际上将输出设备的特定输出连接到输入设备的特定组。

注2：成功链接后，由  _srcCell_   (  eligo  )  生成的数据将自动传送到目标  ( 组 )。  

### _int IMP_ 系统  \(
取消分组源和目标。 

### _int IMP_ 系统  \(

从源单元中检索与目标相关的信息。

