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

#define IMP_IVS_MOVE_MAX_ROI_CNT		52

#include <imp/imp_ivs.h>

/**
 * @file
 * IMP IVS Motion detection module 
 */

/**
 * @defgroup MoveDetection
 * @ingroup IMP_IVS
 * @brief Motion detection interface 
 * @{
 */

/**
 * Input structure of motion detection algorithm 
 */
typedef struct {
	int sense[IMP_IVS_MOVE_MAX_ROI_CNT]; /**< Sensitivity of motion detection , The normal camera range is 0-4， The range of the panoramic camera is 0-8 */
	int skipFrameCnt; /*< Number of detections every other frame */
	IMPFrameInfo frameInfo; /**< Frame size information , Just need to configure width with height */
	IMPRect roiRect[IMP_IVS_MOVE_MAX_ROI_CNT]; /*< Need to be detected roi Area coordinate information */
	int roiRectCnt; /*< Need to be detected roi Number of regions ， Range is 0-51， If 0 : No detection ，1 : Detection roiRect 0
														 area ，2 , Detection roiRect 0,1 area ，3 , Detection roiRect 0,1,2 area ， And so on */
} IMP_IVS_MoveParam;

/*
 * The output structure of the motion detection algorithm 
 */
typedef struct {
	int retRoi[IMP_IVS_MOVE_MAX_ROI_CNT];				/*< Area detection movement result ， versus roiRect Strictly correspond to coordinate information ,0: Indicates that no motion was detected ，1 : Indicates that motion is detected */
} IMP_IVS_MoveOutput;

/**
 * Create motion detection interface resources 
 *
 * @fn IMPIVSInterface *IMP_IVS_CreateMoveInterface(IMP_IVS_MoveParam *param);
 *
 * @param[in] param Input structure parameters of motion detection algorithm 
 *
 * @retval non- NULL success , Returns the pointer handle of the motion detection algorithm interface 
 * @retval NULL failure 
 *
 * @attention no 
 */
IMPIVSInterface *IMP_IVS_CreateMoveInterface(IMP_IVS_MoveParam *param);

/**
 * Destroy motion detection interface resources 
 *
 * @fn void IMP_IVS_DestroyMoveInterface(IMPIVSInterface *moveInterface);
 *
 * @param[in] moveInterface Motion detection algorithm interface pointer handle 
 *
 * @retval No return value 
 *
 * @attention no 
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
