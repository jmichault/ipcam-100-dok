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
 * @section concept 1 Related concepts 
 * IMP IVS by IVS Universal interface API Call instantiated IMPIVSInterface To embed intelligent analysis algorithms into SDK Incoming analysis SDK middle frame image. 
 *
 * @subsection IMPIVSInterface 1.1 IMPIVSInterface
 * IMPIVSInterface General algorithm interface ， The specific algorithm implements this interface and passes it to IMP IVS Reach at SDK The purpose of running specific algorithms in. \n
 * One channel There is and is only a carrier for a single algorithm instance ， The specific implementation of the general algorithm interface must be passed to the specific channel Ability in SDK Run the algorithm in. 	\n
 * IMPIVSInterface member param Member function init Parameters. \n
 * IMP_IVS Will be passed to the member function ProcessAsync Parametric frame External lock ，ProcessAsync Must be used up frame Call after IMP_IVS_ReleaseData freed frame， To avoid deadlock. 
 *
 * @section ivs_usage 2 Instructions 
 * Take motion detection algorithm as an example ， See the specific implementation of the function sample-move_c.c file \n
 * step.1 Initialize the system ， You can directly call the example sample_system_init() function. \n
 * The entire application can only initialize the system once ， If initialized before ， There is no need to initialize again. \n
 * step.2 initialization framesource \n
 * If the algorithm used framesource Channel created ， Just use the created channel directly. \n
 * If the algorithm used framesource Channel not created ， You can call the sample_framesource_init(IVS_FS_CHN, &fs_chn_attr) Create it. \n
 * step.3 create ivs Specific algorithm channel group. \n
 * Multiple algorithms can share a channel group ， You can also use channel groups separately ， Specific pieces sample_ivs_move_init() \n
 * @code
 * int sample_ivs_move_init(int grp_num)
 * {
 * 	int ret = 0;
 *
 *		ret = IMP_IVS_CreateGroup(grp_num);
 *		if (ret < 0) {
 *			IMP_LOG_ERR(TAG, "IMP_IVS_CreateGroup(%d) failed\n", grp_num);
 *			return -1;
 *		}
 *		return 0;
 * }
 * @endcode
 * step.4 Bind algorithm channel group and framesource Channel group 
 * @code
 *	IMPCell framesource_cell = {DEV_ID_FS, IVS_FS_CHN, 0};
 *	IMPCell ivs_cell = {DEV_ID_IVS, 0, 0};
 *	ret = IMP_System_Bind(&framesource_cell, &ivs_cell);
 *	if (ret < 0) {
 *		IMP_LOG_ERR(TAG, "Bind FrameSource channel%d and ivs0 failed\n", IVS_FS_CHN);
 *		return -1;
 *	}
 * @endcode
 * step.5 start up framesource And algorithm. ， So that it can directly correspond to which algorithm is currently operating. 
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
 * step.6 Get algorithm results \n
 * Polling Results, acquisition results, and release results must correspond strictly ， No interruption ;
 * only Polling The result is returned correctly ， The obtained results will be updated ， Otherwise, the results obtained are unpredictable. 
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
 * step.7 Release resources 
 * @code
 * sample_ivs_move_stop(0, inteface);
 * sample_framesource_streamoff(1);
 * IMP_System_UnBind(&framesource_cell, &ivs_cell);
 * sample_ivs_move_exit(0);
 * sample_framesource_exit(IVS_FS_CHN);
 * sample_system_exit();
 * @endcode
 * @{
 */

/**
 * ivs Common interface 
 */
typedef struct IMPIVSInterface IMPIVSInterface;

struct IMPIVSInterface {
	void *param;													/**< Input parameters */
	int paramSize;												/**< Parameter space size */
	IMPPixelFormat pixfmt;											/**< Algorithm requires data format */
	int (*init)(IMPIVSInterface *inf);								/**< Initialization function */
	void (*exit)(IMPIVSInterface *inf);								/**< Logout function */
	int (*preProcessSync)(IMPIVSInterface *inf, IMPFrameInfo *frame);/**< Preprocessing function ， Incorrectly passed into this function frame Additional lock ， So no need free frame， return value: >=0 correct ，<0 :error */
	int (*processAsync)(IMPIVSInterface *inf, IMPFrameInfo *frame);/**< Processing function , SDK IVS The module is frame Additional lock ， Therefore, the function must be frame Use as soon as possible after use free_data Function unlock ; This function must be implemented , The result of the algorithm is produced by this function ; return value :0-> Actual test returns normally ,1-> Frame skipping detection returns normally ,-1-> error */
	int (*getResult)(IMPIVSInterface *inf, void **result);			/**< Get result resources */
	int (*releaseResult)(IMPIVSInterface *inf, void *result);		/**< Release result resources */
	int	 (*getParam)(IMPIVSInterface *inf, void *param);			/**< Get algorithm parameters */
	int	 (*setParam)(IMPIVSInterface *inf, void *param);			/**< Set algorithm parameters */
	int	 (*flushFrame)(IMPIVSInterface *inf);						/**< Release by outside processAsync All cached after input to the algorithm frame */
	void *priv;														/**< Private variable */
};

/**
 * Create channel group 
 *
 * @fn int IMP_IVS_CreateGroup(int GrpNum);
 *
 * @param[in] GrpNum IVS Channel group number corresponding to the function 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark no 
 *
 * @attention no 
 */
int IMP_IVS_CreateGroup(int GrpNum);

/**
 * Destroy the channel group 
 *
 * @fn int IMP_IVS_DestroyGroup(int GrpNum);
 *
 * @param[in] GrpNum IVS Channel group number corresponding to the function 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark no 
 *
 * @attention no 
 */
int IMP_IVS_DestroyGroup(int GrpNum);
/**
 * create IVS Function corresponding channel 
 *
 * @fn int IMP_IVS_CreateChn(int ChnNum, IMPIVSInterface *handler);
 *
 * @param[in] ChnNum Channel number 
 *
 * @param[in] handler IVS Function handle 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark no .
 *
 * @attention no 
 */
int IMP_IVS_CreateChn(int ChnNum, IMPIVSInterface *handler);

/**
 * destroy IVS The channel corresponding to the function handle 
 *
 * @fn int IMP_IVS_DestroyChn(int ChnNum);
 *
 * @param[in] ChnNum Channel number 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark no 
 *
 * @attention no 
 */
int IMP_IVS_DestroyChn(int ChnNum);

/**
 * Register channel to channel group 
 *
 * @fn int IMP_IVS_RegisterChn(int GrpNum, int ChnNum);
 *
 * @param[in] GrpNum IVS Channel group number corresponding to the function 
 *
 * @param[in] ChnNum IVS Channel number corresponding to the function 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark Will be numbered Chnnum The channel registered to the number is Grpnum Channel group 
 *
 * @attention no 
 */
int IMP_IVS_RegisterChn(int GrpNum, int ChnNum);

/**
 * Cancel channel from channel group 
 *
 * @fn int IMP_IVS_UnRegisterChn(int ChnNum);
 *
 * @param[in] ChnNum IVS Channel number corresponding to the function 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark The minor number is Grpnum The logout number in the channel group is Chnnum aisle 
 *
 * @attention no 
 */
int IMP_IVS_UnRegisterChn(int ChnNum);

/**
 * Channel starts to receive images 
 *
 * @fn int IMP_IVS_StartRecvPic(int ChnNum);
 *
 * @param[in] ChnNum Channel number 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark The channel number is Chnnum of IVS The function channel starts to receive images for intelligent analysis 
 *
 * @attention no 
 */
int IMP_IVS_StartRecvPic(int ChnNum);

/**
 * Channel stops receiving images 
 *
 * @fn int IMP_IVS_StopRecvPic(int ChnNum);
 *
 * @param[in] ChnNum Channel number 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark The channel number is Chnnum of IVS Function channel stops receiving images ， Pause intelligent analysis 
 *
 * @attention no 
 */
int IMP_IVS_StopRecvPic(int ChnNum);

/**
 * Blocking to determine whether it can be obtained IVS Intelligent analysis result calculated by function 
 *
 * @fn int IMP_IVS_PollingResult(int ChnNum, int timeoutMs);
 *
 * @param[in] ChnNum IVS Channel number corresponding to the function 
 *
 * @param[in] timeout Maximum waiting time ， unit ms; IMP_IVS_DEFAULT_TIMEOUTMS: Default waiting time inside the library ,0: Don't wait ,>0: Waiting time set by the user 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark Only the parameters when the channel is created IMPIVSInterface Structure ProcessAsync Function member return 0 Time ， That is, when the actual test returns normally ， this Polling Function returns success 
 *
 * @attention no 
 */
int IMP_IVS_PollingResult(int ChnNum, int timeoutMs);

/**
 * obtain IVS Intelligent analysis result calculated by function 
 *
 * @fn int IMP_IVS_GetResult(int ChnNum, void **result);
 *
 * @param[in] ChnNum IVS Channel number corresponding to the function 
 *
 * @param[in] result IVS The output result of the channel number corresponding to the function ， Returns the result pointer of the intelligent analysis algorithm corresponding to this channel ， External customers do not need to allocate space. 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark According to different IVS Functionally bound channel , Output the corresponding result .
 *
 * @attention no 
 */
int IMP_IVS_GetResult(int ChnNum, void **result);

/**
 * freed IVS Result resource calculated by function 
 *
 * @fn int IMP_IVS_ReleaseResult(int ChnNum, void *result);
 *
 * @param[in] GrpNum Channel group number 
 *
 * @param[in] ChnNum IVS Channel number corresponding to the function 
 *
 * @param[in] result IVS The output result of the channel number corresponding to the function 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark According to different IVS Functionally bound channel , Release its output result resources .
 *
 * @attention no 
 */
int IMP_IVS_ReleaseResult(int ChnNum, void *result);

/**
 * Release to Datacallback Parameters frame
 *
 * @fn int IMP_IVS_ReleaseData(void *vaddr);
 *
 * @param[in] vaddr Freed space virtual address 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @remark Must use this function to release the pass to Datacallback of frame parameter ， Otherwise, it will definitely cause a deadlock. 
 * @remark This interface is only for algorithm providers ， Customers do not need to pay attention to the use of algorithms. 
 *
 * @attention no 
 */
int IMP_IVS_ReleaseData(void *vaddr);

/**
 * Get channel algorithm parameters 
 *
 * @fn int IMP_IVS_GetParam(int chnNum, void *param);
 *
 * @param[in] ChnNum IVS Channel number corresponding to the function 
 * @param[in] param Algorithm parameter virtual address pointer 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @attention no 
 */
int IMP_IVS_GetParam(int chnNum, void *param);

/**
 * Set channel algorithm parameters 
 *
 * @fn int IMP_IVS_SetParam(int chnNum, void *param);
 *
 * @param[in] ChnNum IVS Channel number corresponding to the function 
 * @param[in] param Algorithm parameter virtual address pointer 
 *
 * @retval 0 success 
 * @retval -1 failure 
 *
 * @attention no 
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
