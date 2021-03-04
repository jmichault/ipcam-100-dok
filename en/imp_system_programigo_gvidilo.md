

# IMP (Ingenic Media Platform) (see imp_system.h)

## basic concepts
T20 / T21 programming is based on the following concepts:
1. Peripheral (= Device)  
    The peripheral completes a function. Examples:
     *  Frame source: ends the output of video data.
     *  Encoder: completes the video encoding or image encoding function.
2. Group  
    The group is the smallest data input unit. A device can have several groups and each group can receive only one data input channel. The group can have several results.  
    The group is also a container for specific "functions". See the explanation in the channel section for more details.
3. Exit  
    The output is the smallest unit of data output per group. A group can have several outputs and each output can produce only one data channel.
4. Cell  
    The cell refers to a collection containing information about the device, the group, and the output. It is presented in the IMPCell data structure.
The cell is mainly used for Bind (@ref bind). According to the definition of Device, Group and Output, Output is the node for data output and Group is the node for data input.
In Bind, the cell index of the data output node is at the Output output, and the cell index of the data input node is at the input group (so that the Cell, Output data input is a nonsensical value).
5. Channel  
    The channel generally refers to a unit with a single function. The channel receives a specific function when it is created (instantiation).  
    For example:  
     -  For the encoder, one channel complements the H264 code or JPEG encoding function. The specific encoding function (type, parameter) is specified when creating the channel


     -  For IVS, a channel completes the function of a specific algorithm and specific algorithmic type parameters are specified when creating the channel


     -  For OSD, there is a region similar to Channel, region is a specific overlay area, which can be PIC (image), COVER (closure), and so on.


     -  For FrameSource, a channel produces an original image and the FrameSource channel is actually a group


     
     The channel, as a functional unit, must generally be registered in the group (in addition to FrameSource) to receive data. After the channel is registered in the group, it will receive the data entered by the group.

    The number of channels that can be recorded by the group of various devices is also different.

## Binding modules (Bind)

Once two groups are connected by Bind, the data from the source group will be automatically sent to the destination group.  
Because the group is the smallest data input unit and the output is the smallest data output unit, the deviceID, groupID and outputID of srcCell in both parameters of IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell) valid.  

While dstCell is valid only for deviceID and groupID, outputID does not make sense as a data entry.

Example 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```

* a group is generated that generates a link from FrameSource to Encoder.


* Two channels are recorded in Encoder Group, so Encoder Group has two outputs H264 and JPEG.



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
This is a typical Bind program: a two-channel code stream.
 * FrameSource has two outputs, namely the main stream Channel0 (1280x720) and the slave stream Channel1 (640x360).
   *   Main stream: FrameSource Channel0 Bind OSD Group.0, OSD Group.0 Bind Encoder Group.0. Among them: 
       * OSD Group.0 recorded two regions that are used to display timestamp and string information respectively
       * Encoder Group .0 recorded two channels . , which are H264 encoding and JPEG encoding respectively. Among them, if the image size of the JPEG encoding channel does not match the input parameter (of FrameSource Channel0), then it will be scaled (software at T10) ) achieve the goal of capturing at any resolution.
       
Notes:
* it is recommended that all link operations be performed during system initialization.
* Bind and UnBind operations cannot be called dynamically after _FrameSource_ is activated. UnBind is done only after deactivation _FrameSource_.

## Functions

### int IMP\_System\_Init (empty )
Initialization of the IMP system.
returns 0 if successful.
After this API call, the basic data structure will be initialized, but the hardware will not be initialized.
Attention: This function must be called for initiation before any other operation.
### int IMP_System_Exit (empty)

After calling this function, all memory and IMP _handles_ will be released, and the hardware will be shut down. 
Note: After calling this API, if you want to use IMP again, you need to reset the IMP system.

### int64_t IMP_System_GetTimeStamp (void)

Get the IMP system timestamp in microseconds.  
Return: time in microseconds.

### int IMP_System_RebaseTimeStamp (bases int64_t)
Set the IMP system timestamp in microseconds.  
Return: 0 if successful.

### uint32_t IMP_System_ReadReg32 (uint32_t u32Addr)

Read the value of a 32-bit register.  

### blank IMP_System_WriteReg32 (uint32_t regAddr, valeur uint32_t)
Write the value to the 32-bit register.

Note: Please call this API carefully and check the meaning of the registry, otherwise it may cause system errors.

### int IMP_System_GetVersion (IMPVersion * pstVersion) 

Get the version number of the IMP system.

### const char * IMP_System_GetCPUInfo (empty)
Get information about the CPU model.  
Note: The return value is a string of CPU model, for example, for T10 there is "T10"and "T10-Lite".

### int IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell)

Link between source cell and destination.

Note 1: According to the concepts of Device, Group and Output, each device can have several groups, and each group can have several outputs, Group is used as Device input interface, and Output is used as Device product interface. Therefore the link actually connects a certain output of the output device to a certain Group of the input device.

Note 2: After a successful link, the data generated by srcCell (Output) will be automatically transmitted to the destination Cell (Group).

### int IMP_System_UnBind (IMPCell * srcCell, IMPCell * dstCell)
Ungroup the sources and destinations. 

### int IMP_System_GetBindbyDest (IMPCell * dstCell, IMPCell * srcCell)

Retrieves information from the source cell related to the destination.




