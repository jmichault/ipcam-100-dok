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
 * @brief Video source ， Yes IMP Image data source of the system ， You can set the image resolution, crop, zoom and other attributes ， And the back-end noise reduction function 
 *
 * FrameSource Is a data flow related concept ， Image resolution can be set ， Format etc. ， And provide the original image to the back end. 
 *
 * FrameSource The structure is as follows: 
 * @image html FrameSource.png
 * As shown in FIG ，FrameSource There are three outputs ， All three outputs can be used for encoding ， among them: 
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
 * ret = IMP_FrameSource_CreateChn(0, &fs_chn_attr); //step.1 create Channel 0
 * if (ret < 0) {
 * printf("FrameSource_CreateChn(0) error\n");
 * goto createchn_err;
 * }
 *
 * ret = IMP_FrameSource_EnableChn(0); //step.2 Enable Channel 0，channel 0 Start outputting image 
 * if (ret < 0) {
 * printf("EnableChn(0) error\n";
 * return enablechn_err;
 * }
 *
 * // So far ，FrameSource Start to the back end Group Transfer data 
 *
 * ret = IMP_FrameSource_DisableChn(0); //step.3 Disable channel 0，channel 0 Stop outputting images 
 * if (ret < 0) {
 * printf("FrameSource_DisableChn(0) error\n");
 * return disablechn_err;
 * }
 *
 * ret = IMP_FrameSource_DestroyChn(0); //step.4 destroy channel 0
 * if (ret < 0) {
 * printf("FrameSource_DestroyChn error\n");
 * return destorychn_err;
 * }
 * @endcode
 * For more usage methods, please refer to Samples
 * @{
 */

/**
* Channel tailoring structure 
*/
typedef struct {
	int enable;		/**< Enable cropping function */
	int left;		/**< Crop left starting point */
	int top;		/**< Starting point */
	int width;		/**< Image cropping width */
	int height;		/**< Image cropping height */
} IMPFSChnCrop;

/**
* Channel zoom structure 
*/
typedef struct {
	int enable;		/**< Enable zoom function */
	int outwidth;	/**< Image width after zooming */
	int outheight;	/**< Image height after zooming */
} IMPFSChnScaler;

typedef enum {
	FS_PHY_CHANNEL,			/**< Physical channel */
	FS_EXT_CHANNEL,			/**< Expand the channel */
} IMPFSChnType;

/**
* aisle FIFO Types of 
*/
typedef enum {
	FIFO_CACHE_PRIORITY = 0,	/**< FIFO Priority cache ， Then output the data */
	FIFO_DATA_PRIORITY,			/**< FIFO Priority output data ， Then cache */
} IMPFSChnFifoType;

/**
* aisle FIFO Attribute structure 
*/
typedef struct {
	int maxdepth;				/**< FIFO Maximum depth */
	IMPFSChnFifoType type;			/**< aisle FIFO Types of */
} IMPFSChnFifoAttr;

/**
 * Channel attribute structure 
 */
typedef struct {
	int picWidth;				/**< Picture width */
	int picHeight;				/**< Picture height */
	IMPPixelFormat pixFmt;		/**< Image Format */
	IMPFSChnCrop crop;			/**< Image cropping attributes */
	IMPFSChnScaler scaler;		/**< Image zoom attribute */
	int outFrmRateNum;			/**< The output frame rate numerator of the channel */
	int outFrmRateDen;			/**< Denominator of the output frame rate of the channel */
	int nrVBs;					/**< Video buffer Quantity */
	IMPFSChnType type;			/**< Channel type */
} IMPFSChnAttr;

/**
 * @fn int IMP_FrameSource_CreateChn(int chnNum, IMPFSChnAttr *chnAttr)
 *
 * Create channel 
 *
 * @param[in] chnNum Channel number 
 * @param[in] chnAttr Channel attribute structure pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Create channel ， Provide data sources for back-end modules ; \n
 * You can set the relevant attributes of the channel ， Include: image width ， Picture height ， Image Format ， The output frame rate of the channel , Cache buf number ， Crop and zoom attributes. \n
 * for T10， aisle 0 [[[ 1 Can only be set as a physical channel ， aisle 2,3 Can only be set as an expansion channel. 
 *
 * @attention no. 
 */
int IMP_FrameSource_CreateChn(int chnNum, IMPFSChnAttr *chn_attr);

/**
 * @fn IMP_FrameSource_DestroyChn(int chnNum)
 *
 * Destroy channel 
 *
 * @param[in] chnNum Channel number 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Destroy channel 
 *
 * @attention If the program has called IMP_FrameSource_EnableChn， Must call IMP_FrameSource_DisableChn after that ， Use this function again. 
 */
int IMP_FrameSource_DestroyChn(int chnNum);

/**
 * @fn int IMP_FrameSource_EnableChn(int chnNum)
 *
 * Enable channel 
 *
 * @param[in] chnNum Channel number 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no 
 *
 * @attention Before using this function ， It must be ensured that the enabled channel has been created .
 */
int IMP_FrameSource_EnableChn(int chnNum);

/**
 * @fn int IMP_FrameSource_DisableChn(int chnNum)
 *
 * Close the channel 
 *
 * @param[in] chnNum Channel number 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no 
 *
 * @attention no 
 */
int IMP_FrameSource_DisableChn(int chnNum);

/**
 * @fn int IMP_FrameSource_GetChnAttr(int chnNum, IMPFSChnAttr *chnAttr)
 *
 * Get channel properties 
 *
 * @param[in] chnNum Channel number 
 *
 * @param[out] chnAttr Channel attribute structure pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Get the relevant attributes of the channel ， Include: image width ， Picture height ， Image Format ， The output frame rate of the channel , Cache buf number ， Crop and zoom properties .
 *
 * @attention no 
 */
int IMP_FrameSource_GetChnAttr(int chnNum, IMPFSChnAttr *chnAttr);

/**
 * @fn int IMP_FrameSource_SetChnAttr(int chnNum, const IMPFSChnAttr *chnAttr)
 *
 * Set channel properties 
 *
 * @param[in] chnNum Channel number 
 *
 * @param[in] chnAttr Channel attribute structure pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark You can set the relevant attributes of the channel ， Include: image width ， Picture height ， Image Format ， The output frame rate of the channel , Cache buf number ， Crop and zoom properties .
 *
 * @attention no 
 */
int IMP_FrameSource_SetChnAttr(int chnNum, const IMPFSChnAttr *chnAttr);

/**
 * @fn IMP_FrameSource_SetFrameDepth(int chnNum, int depth)
 *
 * Set the maximum depth of the image that can be obtained 
 *
 * @param[in] chnNum Channel number 
 * @param[in] depth Set the maximum depth value of the image that can be obtained 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark
 *
 * 1. This interface is used to set the number of video image frames buffered in a channel. ， The user can obtain a certain number of continuous image data. 
 *
 * 2. If specified depth for 0， Indicates that the system does not need to cache images for this channel ， Therefore, the user cannot obtain the image data of the channel. ， which is depth The default is 0 . 
 *
 * 3. The system will automatically update the oldest image data ， To ensure that once users start to get ， You can get the most recent image. 
 *
 * 4. The system automatically stops caching new images because it cannot get images ， The user also cannot obtain new images. 
 *
 * 5. The system will automatically update the oldest image data that the user has not yet acquired ， Ensure that the cached image queue is the latest image. ， The resulting image may not be continuous. 
 *
 * 6. This function can call location ， There is no requirement. 
 *
 * @attention no .
 */
int IMP_FrameSource_SetFrameDepth(int chnNum, int depth);

/**
 * @fn IMP_FrameSource_GetFrameDepth(int chnNum, int *depth);
 *
 * Maximum depth of acquired image 
 *
 * @param[in] chnNum Channel number 
 * @param[out] depth The maximum depth value of the acquired image 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no .
 *
 * @attention no .
 */
int IMP_FrameSource_GetFrameDepth(int chnNum, int *depth);

/**
 * @fn IMP_FrameSource_GetFrame(int chnNum, IMPFrameInfo **frame);
 *
 * Acquired image 
 *
 * @param[in] chnNum Channel number 
 * @param[out] frame Acquired image 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark
 *
 * 1. This interface can obtain the video image information of the specified channel. 
 *
 * 2. This interface is valid only after the channel has been enabled. 
 *
 * 3. Support multiple acquisitions and then release ， However, it is recommended to pair the acquisition and release interfaces. 
 *
 * 4. The default timeout period of this interface is 2s， which is 2s Still have not got the image inside ， The timeout returns. 
 *
 * @attention no .
 */
int IMP_FrameSource_GetFrame(int chnNum, IMPFrameInfo **frame);

/**
 * @fn IMP_FrameSource_GetTimedFrame(int chnNum, IMPFrameTimestamp *framets, int block, void *framedata, IMPFrameInfo *frame);
 *
 * Get the image at the specified time 
 *
 * @param[in] chnNum Channel number 
 * @param[in] framets Time information 
 * @param[in] block Blocking properties 
 * @param[in] framedata Copy the memory pointer of the image 
 * @param[in] frame Get image information 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark
 *
 * 1. This interface can obtain the video image information of the specified channel at the specified time. 
 *
 * 2. This interface is valid only after the channel has been enabled. 
 *
 * 3. This interface needs to be set up first IMP_FrameSource_SetMaxDelay with IMP_FrameSource_SetDelay . 
 *
 * @attention no .
 */
int IMP_FrameSource_GetTimedFrame(int chnNum, IMPFrameTimestamp *framets, int block, void *framedata, IMPFrameInfo *frame);

/**
 * @fn IMP_FrameSource_ReleaseFrame(int chnNum, IMPFrameInfo *frame);
 *
 * Release the acquired image 
 *
 * @param[in] chnNum Channel number 
 * @param[in] frame Release the acquired image 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no .
 *
 * @attention no .
 */
int IMP_FrameSource_ReleaseFrame(int chnNum, IMPFrameInfo *frame);

/**
 * @fn IMP_FrameSource_SnapFrame(int chnNum, IMPPixelFormat fmt, int width, int height, void *framedata, IMPFrameInfo *frame);
 *
 * Get image 
 *
 * @param[in] chnNum Channel number 
 * @param[in] fmt Image format 
 * @param[in] width Image width 
 * @param[in] height Image height 
 * @param[in] framedata Copy the memory pointer of the image 
 * @param[in] frame Get image information 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark
 *
 * 1. This interface can obtain a frame of images in a specified format and size; the current format supports NV12，YUYV422 ; The size is the same as the channel resolution; no need to call IMP_FrameSource_SetFrameDepth interface .
 *
 * 2. This interface is valid only after the channel has been enabled. 
 *
 *
 * @attention no .
 */
int IMP_FrameSource_SnapFrame(int chnNum, IMPPixelFormat fmt, int width, int height, void *framedata, IMPFrameInfo *frame);

/**
 * @fn IMP_FrameSource_SetMaxDelay(int chnNum, int maxcnt);
 *
 * Set the maximum delay frame number 
 *
 * @param[in] chnNum Channel number 
 * @param[in] maxcnt Maximum delay ， Unit frame 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no .
 *
 * @attention When using it, you need to use the function IMP_FrameSource_CreateChn versus IMP_FrameSource_EnableChn Call between .
 */
int IMP_FrameSource_SetMaxDelay(int chnNum, int maxcnt);

/**
 * @fn IMP_FrameSource_GetMaxDelay(int chnNum, int *maxcnt);
 *
 * Get the maximum number of delayed frames 
 *
 * @param[in] chnNum Channel number 
 * @param[out] maxcnt Maximum delay ， Unit frame 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no .
 *
 * @attention When using it, you need to use the function IMP_FrameSource_CreateChn after that .
 */
int IMP_FrameSource_GetMaxDelay(int chnNum, int *maxcnt);

/**
 * @fn IMP_FrameSource_SetDelay(int chnNum, int cnt);
 *
 * Set the number of delayed frames 
 *
 * @param[in] chnNum Channel number 
 * @param[in] cnt delay ， Unit frame 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no .
 *
 * @attention When using it, you need to use the function IMP_FrameSource_SetMaxDelay Call after .
 */
int IMP_FrameSource_SetDelay(int chnNum, int cnt);

/**
 * @fn IMP_FrameSource_GetDelay(int chnNum, int *cnt);
 *
 * Get the number of delayed frames 
 *
 * @param[in] chnNum Channel number 
 * @param[out] cnt delay ， Unit frame 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no .
 *
 * @attention When using it, you need to use the function IMP_FrameSource_CreateChn after that .
 */
int IMP_FrameSource_GetDelay(int chnNum, int *cnt);

/**
 * @fn IMP_FrameSource_SetChnFifoAttr(int chnNum, IMPFSChnFifoAttr *attr);
 *
 * Set channel maximum buffer FIFO Attributes 
 *
 * @param[in] chnNum Channel number 
 * @param[in] attr	FIFO Attributes ， include FIFO Maximum depth ， Unit frame FIFO Types of .
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no .
 *
 * @attention When using it, you need to use the function IMP_FrameSource_CreateChn versus IMP_FrameSource_EnableChn Call between .
 */
int IMP_FrameSource_SetChnFifoAttr(int chnNum, IMPFSChnFifoAttr *attr);

/**
 * @fn IMP_FrameSource_GetChnFifoAttr(int chnNum, IMPFSChnFifoAttr *attr);
 *
 * Get channel maximum buffer FIFO Attributes 
 *
 * @param[in] chnNum Channel number 
 * @param[out] attr	FIFO Attributes .
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no .
 *
 * @attention When using it, you need to use the function IMP_FrameSource_CreateChn after that .
 */
int IMP_FrameSource_GetChnFifoAttr(int chnNum, IMPFSChnFifoAttr *attr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

/**
 * @}
 */

#endif /* __IMP_FRAMESOURCE_H__ */
