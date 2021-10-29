---
lang: zh
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: IMP编程指南
---


这里可以看到API的文件：（°1°1  
* [原始版本中文](../../zh/includes.zh/html/)


* [英文版](../../en/includes.en/html/)


* （°1°1°1°1°1°1°法式版由谷歌](../../fr/includes.fr/html/)翻译




# IMP (Ingenic Media Platform) (参见imp_system.h)

## 基本概念
T20 / T21编程基于以下概念：
1.外围设备 (=设备)  
    外围设备完成功能。示例：
     *  帧源：结束视频数据的输出。
     *  编码器：完成视频编码或图像编码功能。
2.组  
    该组是最小的数据输入单位。一个设备可以有多个组，每个组只能接收一个数据输入通道。该组可以有几个结果。  
    该组也是特定 "功能"的容器。有关更多详细信息，请参见通道部分中的说明。
3.出口  
    输出是每组数据输出的最小单位。一组可以有多个输出，每个输出只能产生一个数据通道。
4.电池  
    单元格是指包含有关设备，组和输出的信息的集合。它以IMPCell数据结构表示。
单元格主要用于绑定 (@ref绑定)。根据设备，组和输出的定义，输出是数据输出的节点，组是数据输入的节点。
在Bind中，数据输出节点的单元格索引在输出输出，数据输入节点的单元格索引在输入组 (，因此，单元格，输出数据输入为无意义的值)。
5.通道  
    通道通常是指具有单个功能的单元。在创建实例 (实例化)时，通道会接收特定功能。  
    例如：  
     -  对于编码器，一个通道是H264代码或JPEG编码功能的补充。创建通道时，指定了特定的编码功能 (类型，参数) 


     -  对于IVS，通道可完成特定算法的功能，并在创建通道时指定特定的算法类型参数


     -  对于OSD，有一个类似于Channel的区域，该区域是特定的覆盖区域，可以是PIC (图像)，COVER (闭合)等。 。


     -  对于FrameSource，通道产生原始图像，而FrameSource通道实际上是一个组


     
     通道，除FrameSource) 外，通常还必须在组 (中注册为功能单元，以接收数据。频道在组中注册后，它将接收该组输入的数据。

    各种设备组可以记录的通道数也不同。

## 装订模块 (装订)

通过绑定连接两个组后，源组中的数据将自动发送到目标组。  
因为组是最小的数据输入单位，而输出是最小的数据输出单位，所以在两个IMP_System_，bind (和IMPCell * 两个参数中srcCell的deviceID，groupID和outputID srcCell，IMPCell * dstCell) 有效。  

虽然dstCell仅对deviceID和groupID有效，但outputID作为数据条目没有意义。

范例1： 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```

* 生成一个组，该组生成从FrameSource到Encoder的链接。


* 编码器组中记录了两个通道，因此编码器组具有两个输出H264和JPEG。



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
这是一个典型的Bind程序：两通道代码流。
 * FrameSource具有两个输出，即主流Channel0 (1280x720) 和从属流Channel1 (640x360)。
   *   主码流：FrameSource的Channel0绑定OSD Group.0，OSD Group.0绑定编码器Group.0。其中： 
       * OSD Group.0记录了两个区域，分别用于显示时间戳和字符串信息
       * 编码器Group.0记录了两个通道。 ，分别是H264编码和JPEG编码。其中，如果JPEG编码通道的图像尺寸与FrameSource Channel0)的输入参数 (不匹配，则它将在T10) 进行软件缩放 (。) 达到在任何分辨率下拍摄的目的。
       
注意：
* 建议在系统初始化期间执行所有链接操作。
* 激活 _FrameSource_ 后，不能动态调用绑定和取消绑定操作。仅在取消激活 _FrameSource_后才能取消绑定。

## 功能

### int IMP\_系统\_初始 (空 )
IMP系统的初始化。如果成功，
将返回0。
此API调用后，将初始化基本数据结构，但不会初始化硬件。
注意：必须在执行任何其他操作之前调用此功能以进行初始化。
### int IMP_System_出口 (空)

调用此函数后，将释放所有内存和IMP _handles_ ，并且将关闭硬件。 
注：调用此API后，如果要再次使用IMP，则需要重置IMP系统。

### int64_t IMP_系统_GetTimeStamp (void)

获取IMP系统时间戳（以微秒为单位）。  
返回值：时间（以微秒为单位）。

### int IMP_System_RebaseTimeStamp (以int64_t)为基准
设置IMP系统的时间戳（以微秒为单位）。  
返回：如果成功，则返回0。

### uint32_t IMP_系统_ReadReg32 (uint32_t u32Addr)

读取32位寄存器的值。  

### 空白IMP_System_WriteReg32 (uint32_t regAddr, valeur uint32_t)
将该值写入32位寄存器。

注意：请仔细调用此API并检查注册表的含义，否则可能导致系统错误。

### int IMP_System_GetVersion (IMPVersion * pstVersion) 

获取IMP系统的版本号。

### const char * IMP_System_GetCPUInfo (空)
获取有关CPU型号的信息。  
注意：返回值是一串CPU模型，例如，对于T10，存在 "T10"和 "T10-Lite"。

### int IMP_System_绑定 (IMPCell * srcCell，IMPCell * dstCell)

源单元格和目标之间的链接。

注1：根据设备，组和输出的概念，每个设备可以有多个组，每个组可以有多个输出，组用作设备输入接口，输出用作设备产品接口。因此，链接实际上将输出设备的特定输出连接到输入设备的特定组。

注2：成功链接后，由srcCell (输出) 生成的数据将自动传输到目标Cell (组)。

### int IMP_System_UnBind (IMPCell * srcCell，IMPCell * dstCell)
取消分组源和目标。 

### int IMP_System_GetBindbyDest (IMPCell * dstCell，IMPCell * srcCell)

从源单元中检索与目标相关的信息。




