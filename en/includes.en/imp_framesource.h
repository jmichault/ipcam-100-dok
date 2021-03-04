/*
 * IMP FrameSource header file.
 *
 * Copyright (C) 2015 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_FRAMESOURCE_H__
#define __IMP_FRAMESOURCE_H__

#include "imp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * FrameSource Module header file 
 */

/**
 * @defgroup IMP_FrameSource
 * @ingroup imp
 * @brief  Video source ， Yes IMP Image data source of the system ， You can set the image resolution, crop, zoom and other attributes ， And the back-end noise reduction function 
 *
 * FrameSource Is a data flow related concept ， Image resolution can be set ， Format etc. ， And provide the original image to the back end. 
 *
 * FrameSource The structure is as follows: 
 * @image html FrameSource.png
 *  As shown in FIG ，FrameSource There are three outputs ， All three outputs can be used for encoding ， among them: 
 * * Channel 0 Generally as a high-definition video stream 
 * * Channel 1 Generally as a standard definition video stream ， or IVS Only algorithmic data source 
 * * Channel 2 Is to expand the channel ， Use in special applications ， Generally not recommended 
 *
 * FrameSource The initialization steps are as follows (take two outputs as an example): 
 * @code
 * IMPFSChnAttr fs_chn_attr;
 * fs_chn_attr.pixFmt = PIX_FMT_NV12;
 * fs_chn_attr.outFrmRateNum = SENSOR_FRAME_RATE;
 * fs_chn_attr.outFrmRateDen = 1;
 * fs_chn_attr.nrVBs = 3;
 * fs_chn_attr.type = FS_PHY_CHANNEL;
 *
 * fs_chn_attr.crop.enable = 1;
 * fs_chn_attr.crop.top = 0;
 * fs_chn_attr.crop.left = 0;
 * fs_chn_attr.crop.width = 960;
 * fs_chn_attr.crop.height = 640;
 *
 * fs_chn_attr.scaler.enable = 1;
 * fs_chn_attr.scaler.outwidth = 320;
 * fs_chn_attr.scaler.outheight = 240;
 *
 * ret = IMP_FrameSource_CreateChn(0, &fs_chn_attr); //step.1  create Channel 0
 * if (ret < 0) {
 *     printf("FrameSource_CreateChn(0) error\n");
 *     goto createchn_err;
 * }
 *
 * ret = IMP_FrameSource_EnableChn(0); //step.2 Enable Channel 0，channel 0 Start outputting image 
 * if (ret < 0) {
 *     printf("EnableChn(0) error\n";
 *     return enablechn_err;
 * }
 *
 * // So far ，FrameSource Start to the back end Group Transfer data 
 *
 * ret = IMP_FrameSource_DisableChn(0); //step.3 Disable channel 0，channel 0 Stop outputting images 
 * if (ret < 0) {
 *     printf("FrameSource_DisableChn(0) error\n");
 *     return disablechn_err;
 * }
 *
 * ret = IMP_FrameSource_DestroyChn(0); //step.4  destroy channel 0
 * if (ret < 0) {
 *     printf("FrameSource_DestroyChn error\n");
 *     return destorychn_err;
 * }
 * @endcode
 *  For more usage methods, please refer to Samples
 * @{
 */

/**
*  Channel tailoring structure 
*/
typedef struct {
	int enable;		/**<  Enable cropping function  */
	int left;		/**<  Crop left starting point  */
	int top;		/**<  Starting point  */
	int width;		/**<  Image cropping width  */
	int height;		/**<  Image cropping height  */
} IMPFSChnCrop;

/**
*  Channel zoom structure 
*/
typedef struct {
	int enable;		/**<  Enable zoom function  */
	int outwidth;	/**<  Image width after zooming  */
	int outheight;	/**<  Image height after zooming  */
} IMPFSChnScaler;

typedef enum {
	FS_PHY_CHANNEL,			/**<  Physical channel  */
	FS_EXT_CHANNEL,			/**<  Expand the channel  */
} IMPFSChnType;

/**
 *  Channel attribute structure 
 */
typedef struct {
	int picWidth;				/**<  Picture width  */
	int picHeight;				/**<  Picture height  */
	IMPPixelFormat pixFmt;		/**<  Image Format  */
	IMPFSChnCrop crop;			/**<  Image cropping attributes  */
	IMPFSChnScaler scaler;		/**<  Image zoom attribute  */
	int outFrmRateNum;			/**<  The output frame rate numerator of the channel  */
	int outFrmRateDen;			/**<  Denominator of the output frame rate of the channel  */
	int nrVBs;					/**< Video buffer Quantity  */
	IMPFSChnType type;			/**<  Channel type  */
} IMPFSChnAttr;

/**
 * @fn int IMP_FrameSource_CreateChn(int chnNum, IMPFSChnAttr *chnAttr)
 *
 *  Create channel 
 *
 * @param[in] chnNum  Channel number 
 * @param[in] chnAttr  Channel attribute structure pointer 
 *
 * @retval 0  success 
 * @retval  non- 0  failure ， Return error code 
 *
 * @remark  Return error code ， Provide data sources for back-end modules ; \n
 *  You can set the relevant attributes of the channel ， Include: image width ， Include: image width ， Include: image width ， The output frame rate of the channel ,  Cache buf number ， Crop and zoom attributes. \n
 *  for T10， aisle 0 [[[ 1 Can only be set as a physical channel ， Can only be set as a physical channel 2,3 Can only be set as an expansion channel. 
 *
 * @attention  no. 
 */
int IMP_FrameSource_CreateChn(int chnNum, IMPFSChnAttr *chn_attr);

/**
 * @fn IMP_FrameSource_DestroyChn(int chnNum)
 *
 *  Destroy channel 
 *
 * @param[in] chnNum  Destroy channel 
 *
 * @retval 0  Destroy channel 
 * @retval  Destroy channel 0  Destroy channel ， Destroy channel 
 *
 * @remark  Destroy channel 
 *
 * @attention  If the program has called IMP_FrameSource_EnableChn， Must call IMP_FrameSource_DisableChn after that ， Use this function again. 
 */
int IMP_FrameSource_DestroyChn(int chnNum);

/**
 * @fn int IMP_FrameSource_EnableChn(int chnNum)
 *
 *  Enable channel 
 *
 * @param[in] chnNum  Enable channel 
 *
 * @retval 0  Enable channel 
 * @retval  Enable channel 0  Enable channel ， Enable channel 
 *
 * @remark  no 
 *
 * @attention  Before using this function ， It must be ensured that the enabled channel has been created .
 */
int IMP_FrameSource_EnableChn(int chnNum);

/**
 * @fn int IMP_FrameSource_DisableChn(int chnNum)
 *
 *  Close the channel 
 *
 * @param[in] chnNum  Close the channel 
 *
 * @retval 0  Close the channel 
 * @retval  Close the channel 0  Close the channel ， Close the channel 
 *
 * @remark  Close the channel 
 *
 * @attention  Close the channel 
 */
int IMP_FrameSource_DisableChn(int chnNum);

/**
 * @fn int IMP_FrameSource_GetChnAttr(int chnNum, IMPFSChnAttr *chnAttr)
 *
 *  Get channel properties 
 *
 * @param[in] chnNum  Get channel properties 
 *
 * @param[out] chnAttr  Get channel properties 
 *
 * @retval 0  Get channel properties 
 * @retval  Get channel properties 0  Get channel properties ， Get channel properties 
 *
 * @remark  Get the relevant attributes of the channel ， Get the relevant attributes of the channel ， Get the relevant attributes of the channel ， Get the relevant attributes of the channel ， Get the relevant attributes of the channel ,  Get the relevant attributes of the channel buf Get the relevant attributes of the channel ， Crop and zoom properties .
 *
 * @attention  Crop and zoom properties 
 */
int IMP_FrameSource_GetChnAttr(int chnNum, IMPFSChnAttr *chnAttr);

/**
 * @fn int IMP_FrameSource_SetChnAttr(int chnNum, const IMPFSChnAttr *chnAttr)
 *
 *  Set channel properties 
 *
 * @param[in] chnNum  Set channel properties 
 *
 * @param[in] chnAttr  Set channel properties 
 *
 * @retval 0  Set channel properties 
 * @retval  Set channel properties 0  Set channel properties ， Set channel properties 
 *
 * @remark  Set channel properties ， Set channel properties ， Set channel properties ， Set channel properties ， Set channel properties ,  Set channel properties buf Set channel properties ， Set channel properties .
 *
 * @attention  Set channel properties 
 */
int IMP_FrameSource_SetChnAttr(int chnNum, const IMPFSChnAttr *chnAttr);

/**
 * @fn IMP_FrameSource_SetFrameDepth(int chnNum, int depth)
 *
 *  Set the maximum depth of the image that can be obtained 
 *
 * @param[in] chnNum  Channel number 
 * @param[in] depth  Set the maximum depth value of the image that can be obtained 
 *
 * @retval 0  Set the maximum depth value of the image that can be obtained 
 * @retval  Set the maximum depth value of the image that can be obtained 0  Set the maximum depth value of the image that can be obtained ， Set the maximum depth value of the image that can be obtained 
 *
 * @remark
 *
 * 1. This interface is used to set the number of video image frames buffered in a channel. When the user sets to cache multiple frames of video images ， The user can obtain a certain number of continuous image data. 
 *
 * 2. If specified depth for 0， Indicates that the system does not need to cache images for this channel ， Therefore, the user cannot obtain the image data of the channel. The system does not cache images for the channel by default ， which is depth The default is 0 . 
 *
 * 3. The system will automatically update the oldest image data ， To ensure that once users start to get ， You can get the most recent image. 
 *
 * 4. The system automatically stops caching new images because it cannot get images ， The user also cannot obtain new images. Therefore, users are recommended to ensure that the acquisition and release interfaces are paired. 
 *
 * 5. The system will automatically update the oldest image data that the user has not yet acquired ， Ensure that the cached image queue is the latest image. Because the user cannot guarantee the speed of acquisition ， The resulting image may not be continuous. 
 *
 * 6. This function can call location ， There is no requirement. But it can only be used once. 
 *
 * @attention  There is no requirement. But it can only be used once. .
 */
int IMP_FrameSource_SetFrameDepth(int chnNum, int depth);

/**
 * @fn IMP_FrameSource_GetFrameDepth(int chnNum, int *depth);
 *
 *  Maximum depth of acquired image 
 *
 * @param[in] chnNum  Maximum depth of acquired image 
 * @param[out] depth  The maximum depth value of the acquired image 
 *
 * @retval 0  The maximum depth value of the acquired image 
 * @retval  The maximum depth value of the acquired image 0  The maximum depth value of the acquired image ， The maximum depth value of the acquired image 
 *
 * @remark  The maximum depth value of the acquired image .
 *
 * @attention  The maximum depth value of the acquired image .
 */
int IMP_FrameSource_GetFrameDepth(int chnNum, int *depth);

/**
 * @fn IMP_FrameSource_GetFrame(int chnNum, IMPFrameInfo **frame);
 *
 *  Acquired image 
 *
 * @param[in] chnNum  Acquired image 
 * @param[out] frame  Acquired image 
 *
 * @retval 0  Acquired image 
 * @retval  Acquired image 0  Acquired image ， Acquired image 
 *
 * @remark
 *
 * 1. This interface can obtain the video image information of the specified channel. The image information mainly includes: the width, height, pixel format of the image, and the starting address of the image data. 
 *
 * 2. This interface is valid only after the channel has been enabled. 
 *
 * 3. Support multiple acquisitions and then release ， However, it is recommended to pair the acquisition and release interfaces. 
 *
 * 4. The default timeout period of this interface is  2s， The default timeout period of this interface is 2s  Still have not got the image inside ， The timeout returns. 
 *
 * @attention  The timeout returns. .
 */
int IMP_FrameSource_GetFrame(int chnNum, IMPFrameInfo **frame);

/**
 * @fn IMP_FrameSource_ReleaseFrame(int chnNum, IMPFrameInfo *frame);
 *
 *  Release the acquired image 
 *
 * @param[in] chnNum  Release the acquired image 
 * @param[in] frame  Release the acquired image 
 *
 * @retval 0  Release the acquired image 
 * @retval  Release the acquired image 0  Release the acquired image ， Release the acquired image 
 *
 * @remark  Release the acquired image .
 *
 * @attention  Release the acquired image .
 */
int IMP_FrameSource_ReleaseFrame(int chnNum, IMPFrameInfo *frame);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

/**
 * @}
 */

#endif /* __IMP_FRAMESOURCE_H__ */
