/*
 * IMP IVS Move func header file.
 *
 * Copyright (C) 2016 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_IVS_MOVE_H__
#define __IMP_IVS_MOVE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define IMP_IVS_MOVE_MAX_ROI_CNT		4

#include <imp/imp_ivs.h>

/**
 * @file
 * IMP IVS  Motion detection module 
 */

/**
 * @defgroup MoveDetection
 * @ingroup IMP_IVS
 * @brief  Motion detection interface 
 * @{
 */

/**
 *  Input structure of motion detection algorithm 
 */
typedef struct {
	int             sense[IMP_IVS_MOVE_MAX_ROI_CNT];   /**<  Sensitivity of motion detection ， Range is 0-4 */
	int             skipFrameCnt;                      /*<  Number of detections every other frame  */
	IMPFrameInfo    frameInfo;                         /**<  Frame size information , Just need to configure width with height */
	IMPRect         roiRect[IMP_IVS_MOVE_MAX_ROI_CNT]; /*<  Need to be detected roi Area coordinate information  */
	int             roiRectCnt;                        /*<  Area coordinate information roi Number of regions ， Number of regions 0-4， If 0 : No detection ，1 : Detection roiRect 0
														  area ，2 , Detection roiRect 0,1 , Detection ，3 , Detection roiRect 0,1,2 , Detection ， And so on  */
} IMP_IVS_MoveParam;
// I suppose it has something to do with this sequence of bytes which is located in appfs/etc/sensor/jxf22move.txt:
	// 50 50 14 26 05 2b 3c 96 28 73 14 32 0f 28

/*
 *  The output structure of the motion detection algorithm 
 */
typedef struct {
	int retRoi[IMP_IVS_MOVE_MAX_ROI_CNT];				/*<  Area detection movement result ， versus roiRect Strictly correspond to coordinate information  */
} IMP_IVS_MoveOutput;

/**
 *  Create motion detection interface resources 
 *
 * @fn IMPIVSInterface *IMP_IVS_CreateMoveInterface(IMP_IVS_MoveParam *param);
 *
 * @param[in] param  Input structure parameters of motion detection algorithm 
 *
 * @retval  non- NULL  success , Returns the pointer handle of the motion detection algorithm interface 
 * @retval NULL  failure 
 *
 * @attention  no 
 */
IMPIVSInterface *IMP_IVS_CreateMoveInterface(IMP_IVS_MoveParam *param);

/**
 *  Destroy motion detection interface resources 
 *
 * @fn void IMP_IVS_DestroyMoveInterface(IMPIVSInterface *moveInterface);
 *
 * @param[in] moveInterface  Motion detection algorithm interface pointer handle 
 *
 * @retval  No return value 
 *
 * @attention  No return value 
 */
void IMP_IVS_DestroyMoveInterface(IMPIVSInterface *moveInterface);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __IMP_IVS_MOVE_H__ */
