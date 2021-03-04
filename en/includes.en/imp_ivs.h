/*
 * IMP IVS header file.
 *
 * Copyright (C) 2015 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_IVS_H__
#define __IMP_IVS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#include <imp/imp_common.h>

/**
 * @file
 * IMP IVS Module 
 */

#define IMP_IVS_DEFAULT_TIMEOUTMS		(-1)

/**
 * @defgroup IMP_IVS
 * @ingroup imp
 * @brief IVS Intelligent analysis universal interface API
 *
 * @section concept 1  Related concepts 
 * IMP IVS  by IVS Universal interface API Call instantiated IMPIVSInterface To embed intelligent analysis algorithms into SDK Incoming analysis SDK middle frame image. 
 *
 * @subsection IMPIVSInterface 1.1 IMPIVSInterface
 * IMPIVSInterface  General algorithm interface ， The specific algorithm implements this interface and passes it to IMP IVS Reach at SDK The purpose of running specific algorithms in. \n
 *  One channel There is and is only a carrier for a single algorithm instance ， The specific implementation of the general algorithm interface must be passed to the specific channel Ability in SDK Run the algorithm in. 	\n
 * IMPIVSInterface  member param Member function init Parameters.  \n
 * IMP_IVS Will be passed to the member function ProcessAsync Parametric frame External lock ，ProcessAsync Must be used up frame Call after IMP_IVS_ReleaseData freed frame， In order to avoid deadlock. 
 *
 * @section ivs_usage 2  Instructions 
 *  Take motion detection algorithm as an example ， See the specific implementation of the function sample-move_c.c file \n
 * step.1  Initialize the system ， You can directly call the example sample_system_init() function. \n
 *  The entire application can only initialize the system once ， If initialized before ， There is no need to initialize again. \n
 * step.2  initialization framesource \n
 *  If the algorithm used framesource Channel created ， Just use the created channel directly. \n
 *  Just use the created channel directly. framesource Channel not created ， You can call the sample_framesource_init(IVS_FS_CHN, &fs_chn_attr) Create it. \n
 * step.3  create ivs Specific algorithm channel group. \n
 *  Multiple algorithms can share a channel group ， You can also use channel groups separately ， Specific pieces sample_ivs_move_init() \n
 * @code
 * int sample_ivs_move_init(int grp_num)
 * {
 *  	int ret = 0;
 *
 *		ret = IMP_IVS_CreateGroup(grp_num);
 *		if (ret < 0) {
 *			IMP_LOG_ERR(TAG, "IMP_IVS_CreateGroup(%d) failed\n", grp_num);
 *			return -1;
 *		}
 *		return 0;
 * }
 * @endcode
 * step.4  Bind algorithm channel group and framesource Channel group 
 * @code
 *	IMPCell framesource_cell = {DEV_ID_FS, IVS_FS_CHN, 0};
 *	IMPCell ivs_cell = {DEV_ID_IVS, 0, 0};
 *	ret = IMP_System_Bind(&framesource_cell, &ivs_cell);
 *	if (ret < 0) {
 *		IMP_LOG_ERR(TAG, "Bind FrameSource channel%d and ivs0 failed\n", IVS_FS_CHN);
 *		return -1;
 *	}
 * @endcode
 * step.5  start up framesource And algorithm. It is recommended that the algorithm channel number is the same as the algorithm number ， So that it can directly correspond to which algorithm is currently operating. 
 * @code
 *	IMP_FrameSource_SetFrameDepth(0, 0);
 *	ret = sample_framesource_streamon(IVS_FS_CHN);
 *	if (ret < 0) {
 *		IMP_LOG_ERR(TAG, "ImpStreamOn failed\n");
 *		return -1;
 *	}
 *	ret = sample_ivs_move_start(0, 0, &inteface);
 *	if (ret < 0) {
 *		IMP_LOG_ERR(TAG, "sample_ivs_move_start(0, 0) failed\n");
 *		return -1;
 *	}
 * @endcode
 *
 * step.6  Get algorithm results  \n
 * Polling Results, acquisition results, and release results must correspond strictly ， No interruption ;
 *  only Polling The result is returned correctly ， The obtained results will be updated ， Otherwise, the results obtained are unpredictable. 
 * @code
 *	for (i = 0; i < NR_FRAMES_TO_IVS; i++) {
 *		ret = IMP_IVS_PollingResult(0, IMP_IVS_DEFAULT_TIMEOUTMS);
 *		if (ret < 0) {
 *			IMP_LOG_ERR(TAG, "IMP_IVS_PollingResult(%d, %d) failed\n", 0, IMP_IVS_DEFAULT_TIMEOUTMS);
 *			return -1;
 *		}
 *		ret = IMP_IVS_GetResult(0, (void **)&result);
 *		if (ret < 0) {
 *			IMP_LOG_ERR(TAG, "IMP_IVS_GetResult(%d) failed\n", 0);
 *			return -1;
 *		}
 *		IMP_LOG_INFO(TAG, "frame[%d], result->ret=%d\n", i, result->ret);
 *
 *		ret = IMP_IVS_ReleaseResult(0, (void *)result);
 *		if (ret < 0) {
 *			IMP_LOG_ERR(TAG, "IMP_IVS_ReleaseResult(%d) failed\n", 0);
 *			return -1;
 *		}
 *	}
 * @endcode
 * step.7  Release resources 
 * @code
 *  sample_ivs_move_stop(0, inteface);
 *  sample_framesource_streamoff(1);
 *  IMP_System_UnBind(&framesource_cell, &ivs_cell);
 *  sample_ivs_move_exit(0);
 *  sample_framesource_exit(IVS_FS_CHN);
 *  sample_system_exit();
 * @endcode
 * @{
 */

/**
 * ivs  Common interface 
 */
typedef struct {
	void  *param;                             /**<  Input parameters  */
	int   paramSize;                          /**<  Parameter space size  */
	IMPPixelFormat pixfmt;                    /**<  Algorithm requires data format  */
	int  (*init)(void *param);                /**<  Initialization function  */
	void (*exit)(void);                       /**<  Logout function  */
	int  (*PreprocessSync)(IMPFrameInfo *frame);/**<  Preprocessing function ， return value: 0->frame Not free,1->frame Already free;-1-> error ,frame error free */
	int  (*ProcessAsync)(IMPFrameInfo *frame);/**<  Processing function , Must ensure that each used up frame In free status , return value :0-> Actual test returns normally ,1-> Frame skipping detection returns normally ,-1-> Frame skipping detection returns normally  */
	int  (*GetResult)(void **result);         /**<  Get result resources  */
	int  (*ReleaseResult)(void *result);      /**<  Release result resources  */
	int	 (*GetParam)(void *param);            /**<  Get algorithm parameters  */
	int	 (*SetParam)(void *param);            /**<  Set algorithm parameters  */
	int	 (*FlushFrame)(void);                 /**<  Release by outside ProcessAsync All cached after input to the algorithm frame */
} IMPIVSInterface;

/**
 *  Create channel group 
 *
 * @fn int IMP_IVS_CreateGroup(int GrpNum);
 *
 * @param[in] GrpNum IVS Channel group number corresponding to the function 
 *
 * @retval 0  success 
 * @retval -1  failure 
 *
 * @remark  no 
 *
 * @attention  no 
 */
int IMP_IVS_CreateGroup(int GrpNum);

/**
 *  Destroy the channel group 
 *
 * @fn int IMP_IVS_DestroyGroup(int GrpNum);
 *
 * @param[in] GrpNum IVS Destroy the channel group 
 *
 * @retval 0  Destroy the channel group 
 * @retval -1  Destroy the channel group 
 *
 * @remark  Destroy the channel group 
 *
 * @attention  Destroy the channel group 
 */
int IMP_IVS_DestroyGroup(int GrpNum);
/**
 *  Destroy the channel group IVS Function corresponding channel 
 *
 * @fn int IMP_IVS_CreateChn(int ChnNum, IMPIVSInterface *handler);
 *
 * @param[in] ChnNum  Channel number 
 *
 * @param[in] handler IVS Function handle 
 *
 * @retval 0  Function handle 
 * @retval -1  Function handle 
 *
 * @remark  Function handle .
 *
 * @attention  Function handle 
 */
int IMP_IVS_CreateChn(int ChnNum, IMPIVSInterface *handler);

/**
 *  destroy IVS The channel corresponding to the function handle 
 *
 * @fn int IMP_IVS_DestroyChn(int ChnNum);
 *
 * @param[in] ChnNum  The channel corresponding to the function handle 
 *
 * @retval 0  The channel corresponding to the function handle 
 * @retval -1  The channel corresponding to the function handle 
 *
 * @remark  The channel corresponding to the function handle 
 *
 * @attention  The channel corresponding to the function handle 
 */
int IMP_IVS_DestroyChn(int ChnNum);

/**
 *  Register channel to channel group 
 *
 * @fn int IMP_IVS_RegisterChn(int GrpNum, int ChnNum);
 *
 * @param[in] GrpNum IVS Register channel to channel group 
 *
 * @param[in] ChnNum IVS Channel number corresponding to the function 
 *
 * @retval 0  Channel number corresponding to the function 
 * @retval -1  Channel number corresponding to the function 
 *
 * @remark  Will be numbered Chnnum The channel registered to the number is Grpnum Channel group 
 *
 * @attention  Channel group 
 */
int IMP_IVS_RegisterChn(int GrpNum, int ChnNum);

/**
 *  Cancel channel from channel group 
 *
 * @fn int IMP_IVS_UnRegisterChn(int ChnNum);
 *
 * @param[in] ChnNum IVS Cancel channel from channel group 
 *
 * @retval 0  Cancel channel from channel group 
 * @retval -1  Cancel channel from channel group 
 *
 * @remark  The minor number is Grpnum The logout number in the channel group is Chnnum aisle 
 *
 * @attention  aisle 
 */
int IMP_IVS_UnRegisterChn(int ChnNum);

/**
 *  Channel starts to receive images 
 *
 * @fn int IMP_IVS_StartRecvPic(int ChnNum);
 *
 * @param[in] ChnNum  Channel starts to receive images 
 *
 * @retval 0  Channel starts to receive images 
 * @retval -1  Channel starts to receive images 
 *
 * @remark  The channel number is Chnnum of IVS The function channel starts to receive images for intelligent analysis 
 *
 * @attention  The function channel starts to receive images for intelligent analysis 
 */
int IMP_IVS_StartRecvPic(int ChnNum);

/**
 *  Channel stops receiving images 
 *
 * @fn int IMP_IVS_StopRecvPic(int ChnNum);
 *
 * @param[in] ChnNum  Channel stops receiving images 
 *
 * @retval 0  Channel stops receiving images 
 * @retval -1  Channel stops receiving images 
 *
 * @remark  Channel stops receiving images Chnnum Channel stops receiving images IVS Function channel stops receiving images ， Pause intelligent analysis 
 *
 * @attention  Pause intelligent analysis 
 */
int IMP_IVS_StopRecvPic(int ChnNum);

/**
 *  Blocking to determine whether it can be obtained IVS Intelligent analysis result calculated by function 
 *
 * @fn int IMP_IVS_PollingResult(int ChnNum, int timeoutMs);
 *
 * @param[in] ChnNum IVS Intelligent analysis result calculated by function 
 *
 * @param[in] timeout  Maximum waiting time ， unit ms; IMP_IVS_DEFAULT_TIMEOUTMS: Default waiting time inside the library ,0: Don't wait ,>0: Waiting time set by the user 
 *
 * @retval 0  Waiting time set by the user 
 * @retval -1  Waiting time set by the user 
 *
 * @remark  Only the parameters when the channel is created IMPIVSInterface Structure ProcessAsync Function member return 0 Time ， That is, when the actual test returns normally ， this Polling Function returns success 
 *
 * @attention  Function returns success 
 */
int IMP_IVS_PollingResult(int ChnNum, int timeoutMs);

/**
 *  obtain IVS Intelligent analysis result calculated by function 
 *
 * @fn int IMP_IVS_GetResult(int ChnNum, void **result);
 *
 * @param[in] ChnNum IVS Intelligent analysis result calculated by function 
 *
 * @param[in] result IVS The output result of the channel number corresponding to the function ， Returns the result pointer of the intelligent analysis algorithm corresponding to this channel ， External customers do not need to allocate space. 
 *
 * @retval 0  External customers do not need to allocate space. 
 * @retval -1  External customers do not need to allocate space. 
 *
 * @remark  According to different IVS Functionally bound channel , Output the corresponding result .
 *
 * @attention  Output the corresponding result 
 */
int IMP_IVS_GetResult(int ChnNum, void **result);

/**
 *  Output the corresponding result IVS Result resource calculated by function 
 *
 * @fn int IMP_IVS_ReleaseResult(int ChnNum, void *result);
 *
 * @param[in] GrpNum  Channel group number 
 *
 * @param[in] ChnNum IVS Channel group number 
 *
 * @param[in] result IVS Channel group number 
 *
 * @retval 0  Channel group number 
 * @retval -1  Channel group number 
 *
 * @remark  Channel group number IVS Channel group number , Release its output result resources .
 *
 * @attention  Release its output result resources 
 */
int IMP_IVS_ReleaseResult(int ChnNum, void *result);

/**
 *  Release to Datacallback Parameters frame
 *
 * @fn int IMP_IVS_ReleaseData(void *vaddr);
 *
 * @param[in] vaddr  Freed space virtual address 
 *
 * @retval 0  Freed space virtual address 
 * @retval -1  Freed space virtual address 
 *
 * @remark  Must use this function to release the pass to Datacallback Must use this function to release the pass to frame parameter ， Otherwise, it will definitely cause a deadlock. 
 * @remark  This interface is only for algorithm providers ， Customers do not need to pay attention to the use of algorithms. 
 *
 * @attention  Customers do not need to pay attention to the use of algorithms. 
 */
int IMP_IVS_ReleaseData(void *vaddr);

/**
 *  Get channel algorithm parameters 
 *
 * @fn int IMP_IVS_GetParam(int chnNum, void *param);
 *
 * @param[in] ChnNum IVS Get channel algorithm parameters 
 * @param[in] param  Algorithm parameter virtual address pointer 
 *
 * @retval 0  Algorithm parameter virtual address pointer 
 * @retval -1  Algorithm parameter virtual address pointer 
 *
 * @attention  Algorithm parameter virtual address pointer 
 */
int IMP_IVS_GetParam(int chnNum, void *param);

/**
 *  Set channel algorithm parameters 
 *
 * @fn int IMP_IVS_SetParam(int chnNum, void *param);
 *
 * @param[in] ChnNum IVS Set channel algorithm parameters 
 * @param[in] param  Set channel algorithm parameters 
 *
 * @retval 0  Set channel algorithm parameters 
 * @retval -1  Set channel algorithm parameters 
 *
 * @attention  Set channel algorithm parameters 
 */
int IMP_IVS_SetParam(int chnNum, void *param);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_IVS_H__ */
