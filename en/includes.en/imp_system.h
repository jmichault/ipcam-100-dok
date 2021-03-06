/*
 * IMP System header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_SYSTEM_H__
#define __IMP_SYSTEM_H__

#include "imp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP System module header file 
 */

/**
 * @defgroup imp IMP(Ingenic Media Platform)
 */

/**
 * @defgroup IMP_System
 * @ingroup imp
 * @brief System control module ， include IMP Basic functions and related functions bound between modules 
 * @section concept 1 Related concepts 
 * System control mainly realizes the connection of various modules ， Define the function of the data flow. 
 *
 * @subsection device 1.1 Device
 * Device It is a collection to complete a certain (class) function. FrameSource Complete the output of video source data ，Encoder Complete the function of video coding or image coding. FrameSource with Encoder Just Device the concept of. \n
 * Device Just a collection concept ， It is not a specific data flow node. 
 *
 * @subsection group 1.2 Group
 * Group It is the smallest unit of data input. Device There can be multiple Group， Each Group Only one data input can be received. Group Can have multiple outputs ( @ref output ). \n
 * Group It's also a container for specific \"functions\" ， You can see @ref channel Part of the explanation. 
 *
 * @subsection output 1.3 Output
 * Output Is an Group The smallest unit of data output for one channel. Group There can be multiple Output， Each Output Only one channel of data can be output. 
 *
 * @subsection cell 1.4 Cell
 * Cell Refers to contains Device [[[ Group [[[ Output Information collection. @ref IMPCell The data structure is presented. \n
 * Cell Mainly used Bind ( @ref bind ). Device [[[ Group [[[ Output Definition ，Output As data output node ， and Group As the data input node. \n
 * in Bind Time data output node Cell Index to output Output， Data entry node Cell Index to input Group (Therefore as data input Cell，Output Is a meaningless value). 
 *
 * @subsection channel 1.5 Channel
 * Channel Usually refers to a single function unit ，Channel in Create Time ( Instantiate ) When the specific function is assigned. \n
 * E.g: \n
 * * for Encoder， One Channel Complete the way H264 Code or JPEG Coding function ， Specific coding function ( Types of ， parameter ) Specified at channel creation 
 * * for IVS， One Channel Complete the function of a specific algorithm ， The specific algorithm type parameters are specified when the channel is created 
 * * for OSD， Have the same Channel Similar concepts Region， One Region Is a specific overlapping area ， Can be PIC( image )，COVER( Occlude ) Wait 
 * * for FrameSource， One Channel Output one original image ，FrameSource of Channel Is actually Group
 *
 * Channel As a functional unit ， usually need Register To Group in (FrameSource except )， To receive the data. Channel Register to Group Middle and rear ， Will get Group Entered data. \n
 * different Device of Group can Register of Channel The numbers are also different. 
 *
 * @section bind 2 Module binding ( Bind ) 
 * Two Group after Bind After connection ， source Group The data will be automatically sent to the destination Group . \n
 * due to Group Is the smallest unit of data input ，Output Is the smallest unit of data output ， therefore IMP_System_Bind(IMPCell *srcCell, IMPCell *dstCell) Of the two parameters srcCell of deviceID, groupID, outputID It is vaild 
 * and dstCell only deviceID with groupID effective ，outputID As data input is meaningless. \n
 * The picture below is a simple Bind example of. 
 * @image html system_bind0.jpg
 * In the picture above ， Achieved FrameSource One output Bind To Encoder one of Group . 
 * in Encoder Group in Register Got two Channel， therefore Encoder Group Have H264 with JPEG Two outputs. 
 * Reference Code: 
 * @code
 * IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};			//FrameSource deviceID:DEV_ID_FS groupID:0 outputID:0
 * IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0};		//ENC deviceID:DEV_ID_ENC groupID:0 outputID:0, Here enc_grp0 The third parameter is meaningless. 
 * int ret = IMP_System_Bind(&fs_chn0, &enc_grp0);
 * if (ret < 0)
 * printf("Bind FrameSource Channel0 and Encoder Group0 failed\n");
 * @endcode
 * Bind Concatenate the data stream of the system ， According to different product functional requirements ，Bind The strategy may also be different. 
 *
 * The following is a typical dual-channel code stream product application Bind Schematic diagram: 
 *
 * @image html typical_application.png
 *
 * In the picture above ，FrameSource There are two outputs ， Respectively are Channel0 Main stream (1280x720) with Channel1 Slave stream (640x360) . \n
 * * Main stream: FrameSource of Channel0 Bind OSD Group.0，OSD Group.0 Bind Encoder Group.0 . 
 * * OSD Group.0 Registered two Region， Used to display timestamp and string information respectively 
 * * Encoder Group.0 Registered two Channel， Separately H264 Encoding and JPEG coding. JPEG If the image size of the encoding channel is not equal to the input setting ( FrameSource of Channel0 ) ， Then it will zoom (Software at T10)， Achieve the purpose of capturing any resolution 
 * * From the code stream: FrameSource of Channel1 Bind IVS Group.0，IVS Group.0 Bind OSD Group.1，OSD Group.1 Bind Encoder Group.1 . 
 * * IVS Group.0 Registered one Channel， Used for motion detection 
 * * OSD Group.1 Registered two Region， Used to display timestamp and string information respectively 
 * * Encoder Group.1 Registered one Channel， get on H264 coding 
 * * One thing worth noting here is ，IVS Bind in OSD prior to ， Because of OSD Timestamp may cause IVS Misjudgment of motion detection 
 *
 * Reference Code: \n
 * Main stream data stream Bind : 
 * @code
 * IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};
 * IMPCell osd_grp0 = {DEV_ID_OSD, 0, 0};
 * IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0};
 * int ret = IMP_System_Bind(&fs_chn0, &osd_grp0);
 * if (ret < 0)
 * printf("Bind FrameSource Channel0 and OSD Group0 failed\n");
 *
 * int ret = IMP_System_Bind(&osd_grp0, &enc_grp0);
 * if (ret < 0)
 * printf("Bind OSD Group0 and Encoder Group0 failed\n");
 * @endcode
 * Data stream from code stream Bind : 
 * @code
 * IMPCell fs_chn1_output0 = {DEV_ID_FS, 1, 0};
 * IMPCell ivs_grp0 = {DEV_ID_IVS, 0, 0};
 * IMPCell osd_grp1 = {DEV_ID_OSD, 1, 0};
 * IMPCell enc_grp1 = {DEV_ID_ENC, 1, 0};
 *
 * int ret = IMP_System_Bind(&fs_chn1_output0, &ivs_grp0);
 * if (ret < 0)
 * printf("Bind FrameSource Channel1 and IVS Group0 failed\n");
 *
 * int ret = IMP_System_Bind(&ivs_grp0, &osd_grp1);
 * if (ret < 0)
 * printf("Bind IVS Group0 and OSD Group1 failed\n");
 *
 * int ret = IMP_System_Bind(&osd_grp1, &enc_grp1);
 * if (ret < 0)
 * printf("Bind OSD Group1 and Encoder Group1 failed\n");
 *
 * @endcode
 *
 * @attention Suggest all Bind The operation is carried out when the system is initialized. 
 * @attention in FrameSource After enabling Bind with UnBind Operation cannot be called dynamically ， need Disable FrameSource Can be done later UnBind . 
 * @attention DestroyGroup To be in UnBind It can only be done afterwards. 
 *
 * Bind Can be a tree structure ， The following figure is an example: 
 * @image html different_output.png
 * In the picture above ，FrameSource of Channel 1(Group.1) Backend respectively Bind Got two Group， Separately from Output.0 with Output.1 Output Data. Bind The benefit is ，IVS Group With OSD Group.1 Work in parallel. 
 * @attention In this example Bind Ways may affect ordinary motion detection ， Therefore, this method is not recommended for normal motion detection. 
 *
 * @{
 */

/**
 * IMP System version number definition .
 */
typedef struct {
	char aVersion[64];	/**< IMP System version number */
} IMPVersion;

/**
 * @fn int IMP_System_Init(void)
 *
 * IMP system initialization .
 *
 * @param no .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks this API After the call, the basic data structure will be initialized ， But will not initialize the hardware unit .
 *
 * @attention in IMP You must call this interface to initialize before any operation of .
 */
int IMP_System_Init(void);

/**
 * @fn int IMP_System_Exit(void)
 *
 * IMP System deinitialization .
 *
 * @param no .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks This function will be released after calling IMP All memory and handles ， And close the hardware unit .
 *
 * @attention Calling this API Rear ， To use again IMP You need to do it again IMP system initialization .
 */
int IMP_System_Exit(void);

/**
 * @fn int64_t IMP_System_GetTimeStamp(void)
 *
 * obtain IMP System timestamp ， The unit is microseconds. 
 *
 * @param no. 
 *
 * @retval time (usec)
 *
 * @remarks The time stamp is automatically initialized after the system is initialized. 
 *
 * @attention no. 
 */
int64_t IMP_System_GetTimeStamp(void);

/**
 * @fn int IMP_System_RebaseTimeStamp(int64_t basets)
 *
 * Set up IMP System timestamp ， The unit is microseconds. 
 *
 * @param[in] basets Base time. 
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no. 
 *
 * @attention no. 
 */
int IMP_System_RebaseTimeStamp(int64_t basets);

/**
 * @fn uint32_t IMP_System_ReadReg32(uint32_t u32Addr)
 *
 * Read 32 The value of the bit register. 
 *
 * @param[in] regAddr The physical address of the register. 
 *
 * @retval The value of the register ( 32 Bit) 
 *
 * @remarks no. 
 *
 * @attention no. 
 */
uint32_t IMP_System_ReadReg32(uint32_t regAddr);

/**
 * @fn void IMP_System_WriteReg32(uint32_t regAddr, uint32_t value)
 *
 * to 32 Write the value in the bit register. 
 *
 * @param[in] regAddr The physical address of the register. 
 * @param[in] value The value to be written. 
 *
 * @retval no 
 *
 * @remarks no. 
 *
 * @attention Please be careful to call this before you are not clear about the meaning of the register API， Otherwise, system errors may result. 
 */
void IMP_System_WriteReg32(uint32_t regAddr, uint32_t value);

/**
 * @fn int IMP_System_GetVersion(IMPVersion *pstVersion)
 *
 * Obtain IMP System version number .
 *
 * @param[out] pstVersion IMP System version number structure pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_System_GetVersion(IMPVersion *pstVersion);

/**
 * @fn const char* IMP_System_GetCPUInfo(void)
 *
 * Obtain CPU Model information .
 *
 * @param no .
 *
 * @retval CPU Model string .
 *
 * @remarks The return value is CPU Model type string , For example for T10 Say , Have "T10" and "T10-Lite".
 *
 * @attention no .
 */
const char* IMP_System_GetCPUInfo(void);

/**
 * @fn int IMP_System_Bind(IMPCell *srcCell, IMPCell *dstCell)
 *
 * Binding source Cell And purpose Cell.
 *
 * @param[in] srcCell source Cell pointer .
 * @param[in] dstCell purpose Cell pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks according to Device [[[ Group with Output the concept of ， Each Device There may be more than one Group， Each Group There may be more than one Output，
 * Group As Device Input interface ， and Output As Device Output interface . So the binding actually outputs Device Of 
 * A Output Connect to input Device Some of Group on .
 * @remarks After the binding relationship is successful ， source Cell(Output) The generated data will be automatically transmitted to the destination Cell(Group).
 *
 * @attention no. 
 */
int IMP_System_Bind(IMPCell *srcCell, IMPCell *dstCell);

/**
 * @fn int IMP_System_UnBind(IMPCell *srcCell, IMPCell *dstCell)
 *
 * De-source Cell And purpose Cell Binding .
 *
 * @param[in] srcCell source Cell pointer .
 * @param[in] dstCell purpose Cell pointer .
 *
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no. 
 */
int IMP_System_UnBind(IMPCell *srcCell, IMPCell *dstCell);

/**
 * @fn int IMP_System_GetBindbyDest(IMPCell *dstCell, IMPCell *srcCell)
 *
 * Get bound in purpose Cell Source of Cell information .
 *
 * @param[in] dstCell purpose Cell pointer .
 * @param[out] srcCell source Cell pointer .
 *
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no. 
 */
int IMP_System_GetBindbyDest(IMPCell *dstCell, IMPCell *srcCell);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_SYSTEM_H__ */
