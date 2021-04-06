/*
 * IMP IVS Move func header file.
 *
 * Copyright (C) 2016 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_IVS_BASE_MOVE_H__
#define __IMP_IVS_BASE_MOVE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define IMP_IVS_MOVE_MAX_ROI_CNT		16

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
 * Input structure of basic motion detection algorithm 
 */
typedef struct {
	int skipFrameCnt; /*< Number of detections every other frame */
	int referenceNum; /*< Specify the position relative to the current frame -referenceNum Reference frame */
	int sadMode; /*< SAD mode ,0 Means 8*8*/
	int sense; /*< Sensitivity ,0-3, The greater the value, the greater the sensitivity */
	IMPFrameInfo frameInfo; /**< Frame size information , Just need to configure width with height */

} IMP_IVS_BaseMoveParam;

/*
 * Output structure of basic motion detection algorithm 
 */
typedef struct {
	int ret;
	uint8_t* data;
	int datalen;
} IMP_IVS_BaseMoveOutput;

/**
 * Create motion detection interface resources 
 *
 * @fn IMPIVSInterface *IMP_IVS_CreateBaseMoveInterface(IMP_IVS_BaseMoveParam *param);
 *
 * @param[in] param Input structure parameters of motion detection algorithm 
 *
 * @retval non- NULL success , Returns the pointer handle of the motion detection algorithm interface 
 * @retval NULL failure 
 *
 * @attention no 
 */
IMPIVSInterface *IMP_IVS_CreateBaseMoveInterface(IMP_IVS_BaseMoveParam *param);

/**
 * Destroy motion detection interface resources 
 *
 * @fn void IMP_IVS_DestroyBaseMoveInterface(IMPIVSInterface *moveInterface);
 *
 * @param[in] moveInterface Motion detection algorithm interface pointer handle 
 *
 * @retval No return value 
 *
 * @attention no 
 */
void IMP_IVS_DestroyBaseMoveInterface(IMPIVSInterface *moveInterface);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __IMP_IVS_MOVE_H__ */
