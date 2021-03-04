/*
 * IMP ISP header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_ISP_H__
#define __IMP_ISP_H__

#include "imp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * ISP Module header file 
 */

/**
 * @defgroup IMP_ISP
 * @ingroup imp
 * @brief  Image signal processing unit. Mainly include image effect settings, mode switching, and Sensor Registration, addition, deletion, etc. 
 *
 * ISP Module has nothing to do with data flow ， No need to proceed Bind， Only applies to effect parameter settings and Sensor control. 
 *
 * ISP The enabling steps of the module are as follows: 
 * @code
 * int ret = 0;
 * ret = IMP_ISP_Open(); // step.1  create ISP Module 
 * if(ret < 0){
 *     printf("Failed to ISPInit\n");
 *     return -1;
 * }
 * IMPSensorInfo sensor;
 * sensor.name = "xxx";
 * sensor.cbus_type = SENSOR_CONTROL_INTERFACE_I2C; // OR SENSOR_CONTROL_INTERFACE_SPI
 * sensor.i2c = {
 * 	.type = "xxx", // I2C Device name ， Must and sensor Driving struct i2c_device_id middle name Unanimous. 
 *	.addr = xx,	//I2C address 
 *	.i2c_adapter_id = xx, //sensor The existing I2C Controller ID
 * }
 * OR
 * sensor.spi = {
 *	.modalias = "xx", //SPI Controller ， Controller sensor Controller struct spi_device_id Controller name Controller 
 *	.bus_num = xx, //SPI Bus address 
 * }
 * ret = IMP_ISP_AddSensor(&sensor); //step.2  add one sensor， Before this operation sensor The driver has been added to the kernel. 
 * if (ret < 0) {
 *     printf("Failed to Register sensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_EnableSensor(void); //step.3  Enable sensor， right now sensor Start outputting images. 
 * if (ret < 0) {
 *     printf("Failed to EnableSensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_EnableTuning(); //step.4  Start outputting images. ISP tuning,  Before calling ISP Debug interface. 
 * if (ret < 0) {
 *     printf("Failed to EnableTuning\n");
 *     return -1;
 * }
 *
 *  For debugging interface, please refer to ISP Debug interface documentation.  //step.5  Effect debugging. 
 *
 * @endcode
 * ISP The uninstallation steps of the module are as follows: 
 * @code
 * int ret = 0;
 * IMPSensorInfo sensor;
 * sensor.name = "xxx";
 * ret = IMP_ISP_DisableTuning(); //step.1  shut down ISP tuning
 * if (ret < 0) {
 *     printf("Failed to disable tuning\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_DisableSensor(); //step.2  shut down sensor， shut down sensor Stop outputting images; before this operation FrameSource All must be closed. 
 * if (ret < 0) {
 *     printf("Failed to disable sensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_DelSensor(&sensor); //step.3  delete sensor， Before this operation sensor Must be closed. 
 * if (ret < 0) {
 *     printf("Failed to disable sensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_Close(); //step.4  Clean up ISP Clean up ， All before this operation sensor Must be deleted. 
 * if (ret < 0) {
 *     printf("Failed to disable sensor\n");
 *     return -1;
 * }
 * @endcode
 *  For more usage methods, please refer to Samples
 * @{
 */

/**
*  Camera control bus type enumeration 
*/
typedef enum {
	TX_SENSOR_CONTROL_INTERFACE_I2C = 1,	/**< I2C Control bus  */
	TX_SENSOR_CONTROL_INTERFACE_SPI,	/**< SPI Control bus  */
} IMPSensorControlBusType;

/**
*  The camera control bus type is I2C Time ， Parameter structure to be configured 
*/
typedef struct {
	char type[20];		/**< I2C Parameter structure to be configured ， Must be driven with the camera struct i2c_device_id in name Variables are consistent  */
	int addr;		/**< I2C Variables are consistent  */
	int i2c_adapter_id;	/**< I2C Variables are consistent  */
} IMPI2CInfo;
/**
*  Variables are consistent SPI Variables are consistent ， Variables are consistent 
*/
typedef struct {
	char modalias[32];	/**< SPI Variables are consistent ， Variables are consistent struct spi_device_id Variables are consistent name Variables are consistent  */
	int bus_num;		/**< SPI Variables are consistent  */
} IMPSPIInfo;

/**
*  Camera registration information structure 
*/
typedef struct {
	char name[32];					/**<  Camera name  */
	IMPSensorControlBusType cbus_type;	/**<  Camera control bus type  */
	union {
		IMPI2CInfo i2c;				/**< I2C Bus information  */
		IMPSPIInfo spi;				/**< SPI Bus information  */
	};
	unsigned short rst_gpio;		/**<  webcam reset Interface link GPIO， Note: this parameter is not enabled now  */
	unsigned short pwdn_gpio;		/**<  Note: this parameter is not enabled now power down Note: this parameter is not enabled now GPIO， Note: this parameter is not enabled now  */
	unsigned short power_gpio;		/**<  Note: this parameter is not enabled now power  Note: this parameter is not enabled now GPIO， Note: this parameter is not enabled now  */
} IMPSensorInfo;

/**
 * @fn int IMP_ISP_Open(void)
 *
 *  turn on ISP turn on 
 *
 * @param  no 
 *
 * @retval 0  success 
 * @retval  non- 0  failure ， Return error code 
 *
 * @remark  Return error code ISP Return error code ， Ready to ISP Add to sensor， And turn on ISP Effect debugging function. 
 *
 * @attention  This function must be added sensor Was called before. 
 */
int IMP_ISP_Open(void);

/**
 * @fn int IMP_ISP_Close(void)
 *
 *  Was called before. ISP Was called before. 
 *
 * @param  Was called before. 
 *
 * @retval 0  Was called before. 
 * @retval  Was called before. 0  Was called before. ， Was called before. 
 *
 * @remark ISP Was called before. ，ISP The module no longer works. 
 *
 * @attention  Before using this function ， Must guarantee all FrameSource And the effect debugging function has been closed ， all sensor Have been uninstalled .
 */
int IMP_ISP_Close(void);

/**
 * @fn int IMP_ISP_AddSensor(IMPSensorInfo *pinfo)
 *
 *  Have been uninstalled sensor， Used to ISP Module provides data source 
 *
 * @param[in] pinfo  Need to add sensor Information pointer 
 *
 * @retval 0  Information pointer 
 * @retval  Information pointer 0  Information pointer ， Information pointer 
 *
 * @remark  Add a camera ， Used to provide images. 
 *
 * @attention  Used to provide images. ， It must be ensured that the camera driver has been registered into the kernel .
 */
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);

/**
 * @fn int IMP_ISP_DelSensor(IMPSensorInfo *pinfo)
 *
 *  Delete one sensor
 *
 * @param[in] pinfo  Need to be deleted sensor Need to be deleted 
 *
 * @retval 0  Need to be deleted 
 * @retval  Need to be deleted 0  Need to be deleted ， Need to be deleted 
 *
 * @remark  Delete a camera. 
 *
 * @attention  Delete a camera. ， Must ensure that the camera has stopped working ， Called IMP_ISP_DisableSensor function .
 */
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);

/**
 * @fn int IMP_ISP_EnableSensor(void)
 *
 *  Enable one sensor
 *
 * @param  Enable one 
 *
 * @retval 0  Enable one 
 * @retval  Enable one 0  Enable one ， Enable one 
 *
 * @remark  Enable a camera ， Make it start transferring images ,  such FrameSource To output the image ， at the same time ISP Only then can the effect be debugged. 
 *
 * @attention  Only then can the effect be debugged. ， It must be ensured that the camera has been added ISP It must be ensured that the camera has been added .
 */
int IMP_ISP_EnableSensor(void);

/**
 * @fn int IMP_ISP_DisableSensor(void)
 *
 *  Disable one sensor
 *
 * @param  Disable one 
 *
 * @retval 0  Disable one 
 * @retval  Disable one 0  Disable one ， Disable one 
 *
 * @remark  Disable a camera ， Stop transferring images ,  Stop transferring images FrameSource Unable to output image ， Unable to output image ISP The effect can not be debugged either. 
 *
 * @attention  The effect can not be debugged either. ， The effect can not be debugged either. FrameSource Have stopped outputting images ， At the same time, the effect debugging is also in the disabled state .
 */
int IMP_ISP_DisableSensor(void);

/**
 * @fn int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value)
 *
 *  Set up sensor The value of a register 
 *
 * @param[in] reg  Register address 
 *
 * @param[in] value  Register value 
 *
 * @retval 0  Register value 
 * @retval  Register value 0  Register value ， Register value 
 *
 * @remark  You can set one directly sensor The value of the register. 
 *
 * @attention  The value of the register. ， It must be ensured that the camera has been enabled .
 */
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value);

/**
 * @fn int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *value)
 *
 *  Obtain sensor Obtain 
 *
 * @param[in] reg  Obtain 
 *
 * @param[in] value  Pointer to register value 
 *
 * @retval 0  Pointer to register value 
 * @retval  Pointer to register value 0  Pointer to register value ， Pointer to register value 
 *
 * @remark  You can get one directly sensor You can get one directly 
 *
 * @attention  You can get one directly ， You can get one directly .
 */
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *value);

typedef enum {
	IMPISP_TUNING_OPS_MODE_DISABLE,			/**<  Disable the module function  */
	IMPISP_TUNING_OPS_MODE_ENABLE,			/**<  Enable the module function  */
	IMPISP_TUNING_OPS_MODE_BUTT,			/**<  Used to judge the validity of parameters ， The parameter size must be less than this value  */
} IMPISPTuningOpsMode;

typedef enum {
	IMPISP_TUNING_OPS_TYPE_AUTO,			/**<  The operation of the module is automatic mode  */
	IMPISP_TUNING_OPS_TYPE_MANUAL,			/**<  The operation of this module is manual mode  */
	IMPISP_TUNING_OPS_TYPE_BUTT,			/**<  The operation of this module is manual mode ， The operation of this module is manual mode  */
} IMPISPTuningOpsType;

/**
 * @fn int IMP_ISP_EnableTuning(void)
 *
 *  The operation of this module is manual mode ISP Effect debugging function 
 *
 * @param  Effect debugging function 
 *
 * @retval 0  Effect debugging function 
 * @retval  Effect debugging function 0  Effect debugging function ， Effect debugging function 
 *
 * @attention  Effect debugging function ， Must guarantee IMP_ISP_EnableSensor Was executed and returned successfully .
 */
int IMP_ISP_EnableTuning(void);

/**
 * @fn int IMP_ISP_DisableTuning(void)
 *
 *  Disable ISP Disable 
 *
 * @param  Disable 
 *
 * @retval 0  Disable 
 * @retval  Disable 0  Disable ， Disable 
 *
 * @attention  Disable ， It must be ensured that the sensor prior to ， Disable first ISP Effect debugging (that is, call this function) .
 */
int IMP_ISP_DisableTuning(void);

/**
 * @fn int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den)
 *
 *  Set camera output frame rate 
 *
 * @param[in] fps_num  Set the numerator parameter of the frame rate 
 * @param[in] fps_den  Set the denominator parameter of the frame rate 
 *
 * @retval 0  Set the denominator parameter of the frame rate 
 * @retval  Set the denominator parameter of the frame rate 0  Set the denominator parameter of the frame rate ， Set the denominator parameter of the frame rate 
 *
 * @attention  Set the denominator parameter of the frame rate ， Set the denominator parameter of the frame rate IMP_ISP_EnableSensor  with  IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);

/**
 * @fn int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den)
 *
 *  Get the camera output frame rate 
 *
 * @param[in] fps_num  Get a pointer to the frame rate molecular parameters 
 * @param[in] fps_den  Get a pointer to the frame rate denominator parameter 
 *
 * @retval 0  Get a pointer to the frame rate denominator parameter 
 * @retval  Get a pointer to the frame rate denominator parameter 0  Get a pointer to the frame rate denominator parameter ， Get a pointer to the frame rate denominator parameter 
 *
 * @attention  Get a pointer to the frame rate denominator parameter ， Get a pointer to the frame rate denominator parameter IMP_ISP_EnableSensor  Get a pointer to the frame rate denominator parameter  IMP_ISP_EnableTuning Get a pointer to the frame rate denominator parameter 
 * @attention  This function must be called to obtain the camera's default frame rate before the frame channel is enabled to start transmitting data. 
 */
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);

/**
 * ISP Anti-flicker property parameter structure. 
 */
typedef enum {
	IMPISP_ANTIFLICKER_DISABLE,	/**<  Anti-flicker property parameter structure. ISP Anti-flash function  */
	IMPISP_ANTIFLICKER_50HZ,	/**<  Anti-flash function ISP Anti-flash function ,  And set the frequency to 50HZ */
	IMPISP_ANTIFLICKER_60HZ,	/**<  And set the frequency to ISP And set the frequency to ， And set the frequency to 60HZ */
	IMPISP_ANTIFLICKER_BUTT,	/**<  And set the frequency to ， And set the frequency to  */
} IMPISPAntiflickerAttr;

/**
 * @fn int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr)
 *
 *  And set the frequency to ISP Anti-flash properties 
 *
 * @param[in] attr  Set parameter value 
 *
 * @retval 0  Set parameter value 
 * @retval  Set parameter value 0  Set parameter value ， Set parameter value 
 *
 * @attention  Set parameter value ， Set parameter value ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);

/**
 * @fn int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr)
 *
 *  obtain ISP obtain 
 *
 * @param[in] pattr  Get parameter value pointer 
 *
 * @retval 0  Get parameter value pointer 
 * @retval  Get parameter value pointer 0  Get parameter value pointer ， Get parameter value pointer 
 *
 * @attention  Get parameter value pointer ， Get parameter value pointer ISP Get parameter value pointer .
 */
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);

/**
 * ISP  Dynamic range compression module operation mode. 
 */
typedef enum {
	IMPISP_DRC_MANUAL,				/**< ISP  Dynamic range compression module manual mode  */
	IMPISP_DRC_UNLIMIT,				/**< ISP  Highest compression mode of dynamic range compression module  */
	IMPISP_DRC_HIGH,				/**< ISP  Dynamic range compression module high compression mode  */
	IMPISP_DRC_MEDIUM,				/**< ISP  Compression mode in the dynamic range compression module  */
	IMPISP_DRC_LOW,					/**< ISP  Dynamic range compression module low compression mode  */
	IMPISP_DRC_DISABLE,				/**< ISP  Dynamic range compression module is not enabled  */
} IMPISPDrcMode;

/**
 * ISP  Dynamic range compression module attribute parameters. 
 */
typedef struct {
	IMPISPDrcMode mode;				/**< ISP  Dynamic range compression module operation mode selection  */
	unsigned char drc_strength;			/**<  Target value set in manual mode ， The value range is [0, 0xff] */
	unsigned char slop_max;				/**<  Strength control parameters ， Strength control parameters [0, oxff] */
	unsigned char slop_min;				/**<  Strength control parameters ， Strength control parameters [0, oxff] */
	unsigned short black_level;			/**< DRC Enhanced minimum pixel value ， Enhanced minimum pixel value [0, oxfff] */
	unsigned short white_level;			/**< DRC Enhanced maximum pixel value ， Enhanced maximum pixel value [0, oxfff] */
} IMPISPDrcAttr;

/**
 * @fn int IMP_ISP_Tuning_SetRawDRC(IMPISPDrcAttr *pinfo)
 *
 *  Enhanced maximum pixel value ISP RAW Figure dynamic range compression module parameters 
 *
 * @param[in] pinfo  Dynamic range parameter pointer 
 *
 * @retval 0  Dynamic range parameter pointer 
 * @retval  Dynamic range parameter pointer 0  Dynamic range parameter pointer ， Dynamic range parameter pointer 
 *
 * @remark  Dynamic range parameter pointer RGB RAW Graph dynamic range compression operation type ， strength ， The maximum and minimum pixel values ​​that need to be enhanced. 
 *
 * @attention  The maximum and minimum pixel values ​​that need to be enhanced. ， The maximum and minimum pixel values ​​that need to be enhanced. ISP The maximum and minimum pixel values ​​that need to be enhanced. .
 */
int IMP_ISP_Tuning_SetRawDRC(IMPISPDrcAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo)
 *
 *  The maximum and minimum pixel values ​​that need to be enhanced. ISP RAW The maximum and minimum pixel values ​​that need to be enhanced. 
 *
 * @param[in] pinfo  The maximum and minimum pixel values ​​that need to be enhanced. 
 *
 * @retval 0  The maximum and minimum pixel values ​​that need to be enhanced. 
 * @retval  The maximum and minimum pixel values ​​that need to be enhanced. 0  The maximum and minimum pixel values ​​that need to be enhanced. ， The maximum and minimum pixel values ​​that need to be enhanced. 
 *
 * @remark  The maximum and minimum pixel values ​​that need to be enhanced. RGB RAW The maximum and minimum pixel values ​​that need to be enhanced. ， The maximum and minimum pixel values ​​that need to be enhanced. ， The maximum and minimum pixel values ​​that need to be enhanced. 
 *
 * @attention  The maximum and minimum pixel values ​​that need to be enhanced. ， The maximum and minimum pixel values ​​that need to be enhanced. ISP The maximum and minimum pixel values ​​that need to be enhanced. .
 */
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);

/**
 * ISP  Attribute parameters of the spatial noise reduction module. 
 */
typedef struct {
	IMPISPTuningOpsMode enable;			/**<  Enable spatial noise reduction  */
	IMPISPTuningOpsType type;				/**<  Space noise reduction function operation type ， Automatic or manual  */
	unsigned char sinter_strength;				/**<  Space noise reduction intensity ， Manual mode is effective ， Manual mode is effective [0, 0xff] */
} IMPISPSinterDenoiseAttr;

/**
 * ISP  Time domain noise reduction module operation mode. 
 */
typedef enum {
	IMPISP_TEMPER_DISABLE,				/**< ISP  Time domain noise reduction module is not enabled  */
	IMPISP_TEMPER_AUTO,					/**< ISP  Time domain noise reduction module automatic mode  */
	IMPISP_TEMPER_MANUAL,				/**< ISP  Time domain noise reduction module manual mode  */
} IMPISPTemperMode;

/**
 * ISP  Attribute parameters of the time domain noise reduction module. 
 */
typedef struct imp_isp_temper_denoise_attr {
	IMPISPTemperMode type;					/**<  Time domain noise reduction function operation type ， Time domain noise reduction function operation type ， Time domain noise reduction function operation type  */
	unsigned char temper_strength;				/**<  Time domain noise reduction intensity ， Time domain noise reduction intensity ， Time domain noise reduction intensity [0, 0xff] */
} IMPISPTemperDenoiseAttr;


/**
 * @fn int IMP_ISP_Tuning_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo)
 *
 *  Time domain noise reduction intensity ISP  Spatial noise reduction module parameters 
 *
 * @param[in] pinfo  Time domain noise reduction parameter pointer 
 *
 * @retval 0  Time domain noise reduction parameter pointer 
 * @retval  Time domain noise reduction parameter pointer 0  Time domain noise reduction parameter pointer ， Time domain noise reduction parameter pointer 
 *
 * @remark  Set the correction parameters of the spatial noise reduction module. 
 *
 * @attention  Set the correction parameters of the spatial noise reduction module. ， Set the correction parameters of the spatial noise reduction module. ISP Set the correction parameters of the spatial noise reduction module. .
 */
int IMP_ISP_Tuning_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo)
 *
 *  Set the correction parameters of the spatial noise reduction module. ISP  Set the correction parameters of the spatial noise reduction module. 
 *
 * @param[in] pinfo  Spatial noise reduction parameter pointer 
 *
 * @retval 0  Spatial noise reduction parameter pointer 
 * @retval  Spatial noise reduction parameter pointer 0  Spatial noise reduction parameter pointer ， Spatial noise reduction parameter pointer 
 *
 * @remark  Obtain the correction parameters of the spatial noise reduction module. 
 *
 * @attention  Obtain the correction parameters of the spatial noise reduction module. ， Obtain the correction parameters of the spatial noise reduction module. ISP Obtain the correction parameters of the spatial noise reduction module. .
 */
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
#if 0
/**
* @fn int IMP_ISP_Tuning_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
*
*  Obtain the correction parameters of the spatial noise reduction module. ISP  Time domain noise reduction module mode 
*
* @param[in] pinfo  Time domain noise reduction module mode 
*
* @retval 0  Time domain noise reduction module mode 
* @retval  Time domain noise reduction module mode 0  Time domain noise reduction module mode ， Time domain noise reduction module mode 
*
* @remark  Set the mode parameters of the time domain noise reduction module ， The default automatic mode. 
*
* @attention  The default automatic mode. ， The default automatic mode. ISP The default automatic mode. .
*/
int IMP_ISP_Tuning_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
#endif
/**
 * @fn int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo)
 *
 *  The default automatic mode. ISP  Time domain noise reduction module parameters 
 *
 * @param[in] pinfo  Time domain noise reduction module parameters 
 *
 * @retval 0  Time domain noise reduction module parameters 
 * @retval  Time domain noise reduction module parameters 0  Time domain noise reduction module parameters ， Time domain noise reduction module parameters 
 *
 * @remark  Set the correction parameters of the time domain noise reduction module ， The module is turned on by default; because the module requires additional memory ， Please close the module if you don’t need it ， The memory is released once it is closed ， Can no longer be opened. 
 *
 * @attention  Can no longer be opened. ， Can no longer be opened. ISP Can no longer be opened. .
 */
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo)
 *
 *  Can no longer be opened. ISP  Can no longer be opened. 
 *
 * @param[in] pinfo  Time domain noise reduction module parameter pointer 
 *
 * @retval 0  Time domain noise reduction module parameter pointer 
 * @retval  Time domain noise reduction module parameter pointer 0  Time domain noise reduction module parameter pointer ， Time domain noise reduction module parameter pointer 
 *
 * @remark  Obtain the correction parameters of the time domain noise reduction module. 
 *
 * @attention  Obtain the correction parameters of the time domain noise reduction module. ， Obtain the correction parameters of the time domain noise reduction module. ISP Obtain the correction parameters of the time domain noise reduction module. .
 */
int IMP_ISP_Tuning_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode)
 *
 *  Obtain the correction parameters of the time domain noise reduction module. ISP  Whether the wide dynamic module is enabled 
 *
 * @param[in] mode  Wide dynamic module parameters 
 *
 * @retval 0  Wide dynamic module parameters 
 * @retval  Wide dynamic module parameters 0  Wide dynamic module parameters ， Wide dynamic module parameters 
 *
 * @remark  Set wide dynamic module calibration parameters ， Set wide dynamic module calibration parameters ， Set wide dynamic module calibration parameters ， Set wide dynamic module calibration parameters ， Set wide dynamic module calibration parameters 
 *
 * @attention  Set wide dynamic module calibration parameters ， Set wide dynamic module calibration parameters ISP Set wide dynamic module calibration parameters .
 */
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetWDRAttr(IMPISPTuningOpsMode *pmode)
 *
 *  Set wide dynamic module calibration parameters ISP  Current state of the wide dynamic module 
 *
 * @param[in] pmode  Wide dynamic module parameter pointer 
 *
 * @retval 0  Wide dynamic module parameter pointer 
 * @retval  Wide dynamic module parameter pointer 0  Wide dynamic module parameter pointer ， Wide dynamic module parameter pointer 
 *
 * @remark  Obtain the correction parameters of the wide dynamic module. 
 *
 * @attention  Obtain the correction parameters of the wide dynamic module. ， Obtain the correction parameters of the wide dynamic module. ISP Obtain the correction parameters of the wide dynamic module. .
 */
int IMP_ISP_Tuning_GetWDRAttr(IMPISPTuningOpsMode *pmode);

/**
 * ISP  Comprehensive extension function ， Scene mode selection. 
 */
typedef enum {
	IMPISP_SCENE_MODE_AUTO = 0,					/**<  Automatic mode  */
	IMPISP_SCENE_MODE_BEACH_SNOW = 2,				/**<  Beach snow scene mode  */
	IMPISP_SCENE_MODE_CANDLE_LIGHT = 3,				/**<  Candle light mode  */
	IMPISP_SCENE_MODE_DAWN_DUSK = 4,				/**<  Evening mode  */
	IMPISP_SCENE_MODE_FALL_COLORS = 5,				/**<  Autumn scene mode  */
	IMPISP_SCENE_MODE_FIREWORKS = 6,				/**<  Fireworks scene mode  */
	IMPISP_SCENE_MODE_LANDSCAPE = 7,				/**<  Landscape mode  */
	IMPISP_SCENE_MODE_NIGHT = 8,					/**<  Night mode  */
	IMPISP_SCENE_MODE_PARTY_INDOOR = 9,				/**<  Indoor party mode  */
	IMPISP_SCENE_MODE_SPORTS = 11,					/**<  Sport mode  */
	IMPISP_SCENE_MODE_SUNSET = 12,					/**<  Sunset mode  */
	IMPISP_SCENE_MODE_TEXT = 13,					/**<  Text mode  */
	IMPISP_SCENE_MODE_NIGHT_PORTRAIT = 14,				/**<  Night portrait mode  */
} IMPISPSceneMode;

/**
 * @fn int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode)
 *
 *  Night portrait mode ISP  Comprehensive effect scene mode 
 *
 * @param[in] mode  Effect scene mode parameters 
 *
 * @retval 0  Effect scene mode parameters 
 * @retval  Effect scene mode parameters 0  Effect scene mode parameters ， Effect scene mode parameters 
 *
 * @attention  Effect scene mode parameters ， Effect scene mode parameters ISP Effect scene mode parameters .
 */
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetSceneMode(IMPISPSceneMode *pmode)
 *
 *  Effect scene mode parameters ISP  Effect scene mode parameters 
 *
 * @param[in] pmode  Effect scene mode parameter pointer 
 *
 * @retval 0  Effect scene mode parameter pointer 
 * @retval  Effect scene mode parameter pointer 0  Effect scene mode parameter pointer ， Effect scene mode parameter pointer 
 *
 * @attention  Effect scene mode parameter pointer ， Effect scene mode parameter pointer ISP Effect scene mode parameter pointer .
 */
int IMP_ISP_Tuning_GetSceneMode(IMPISPSceneMode *pmode);

/**
 * ISP  Effect scene mode parameter pointer ， Color mode selection. 
 */
typedef enum {
	IMPISP_COLORFX_MODE_AUTO = 0,				/**<  Color mode selection.  */
	IMPISP_COLORFX_MODE_BW = 1,				/**<  Black and white mode  */
	IMPISP_COLORFX_MODE_SEPIA = 2,				/**<  Sepia mode  */
	IMPISP_COLORFX_MODE_NEGATIVE = 3,			/**<  Reverse color mode  */
	IMPISP_COLORFX_MODE_VIVID = 9,				/**<  Vivid mode  */
} IMPISPColorfxMode;

/**
 * @fn int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode)
 *
 *  Vivid mode ISP  Multi-effect color mode 
 *
 * @param[in] mode  Color mode parameters 
 *
 * @retval 0  Color mode parameters 
 * @retval  Color mode parameters 0  Color mode parameters ， Color mode parameters 
 *
 * @attention  Color mode parameters ， Color mode parameters ISP Color mode parameters .
 */
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetColorfxMode(IMPISPColorfxMode *pmode)
 *
 *  Color mode parameters ISP  Color mode parameters 
 *
 * @param[in] pmode  Color mode parameter pointer 
 *
 * @retval 0  Color mode parameter pointer 
 * @retval  Color mode parameter pointer 0  Color mode parameter pointer ， Color mode parameter pointer 
 *
 * @attention  Color mode parameter pointer ， Color mode parameter pointer ISP Color mode parameter pointer .
 */
int IMP_ISP_Tuning_GetColorfxMode(IMPISPColorfxMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetBrightness(unsigned char bright)
 *
 *  Color mode parameter pointer ISP  Comprehensive effect picture brightness 
 *
 * @param[in] bright  Picture brightness parameter 
 *
 * @retval 0  Picture brightness parameter 
 * @retval  Picture brightness parameter 0  Picture brightness parameter ， Picture brightness parameter 
 *
 * @remark  The default value is 128， more than the 128 Increase brightness ， Less than 128 Decrease the brightness. 
 *
 * @attention  Decrease the brightness. ， Decrease the brightness. ISP Decrease the brightness. .
 */
int IMP_ISP_Tuning_SetBrightness(unsigned char bright);

/**
 * @fn int IMP_ISP_Tuning_GetBrightness(unsigned char *pbright)
 *
 *  Decrease the brightness. ISP  Decrease the brightness. 
 *
 * @param[in] bright  Picture brightness parameter pointer 
 *
 * @retval 0  Picture brightness parameter pointer 
 * @retval  Picture brightness parameter pointer 0  Picture brightness parameter pointer ， Picture brightness parameter pointer 
 *
 * @remark  Picture brightness parameter pointer 128， Picture brightness parameter pointer 128 Picture brightness parameter pointer ， Picture brightness parameter pointer 128 Picture brightness parameter pointer 
 *
 * @attention  Picture brightness parameter pointer ， Picture brightness parameter pointer ISP Picture brightness parameter pointer .
 */
int IMP_ISP_Tuning_GetBrightness(unsigned char *pbright);

/**
 * @fn int IMP_ISP_Tuning_SetContrast(unsigned char contrast)
 *
 *  Picture brightness parameter pointer ISP  Comprehensive effect picture contrast 
 *
 * @param[in] contrast  Picture contrast parameter 
 *
 * @retval 0  Picture contrast parameter 
 * @retval  Picture contrast parameter 0  Picture contrast parameter ， Picture contrast parameter 
 *
 * @remark  Picture contrast parameter 128， Picture contrast parameter 128 Increase contrast ， Increase contrast 128 Reduce the contrast. 
 *
 * @attention  Reduce the contrast. ， Reduce the contrast. ISP Reduce the contrast. .
 */
int IMP_ISP_Tuning_SetContrast(unsigned char contrast);

/**
 * @fn int IMP_ISP_Tuning_GetContrast(unsigned char *pcontrast)
 *
 *  Reduce the contrast. ISP  Reduce the contrast. 
 *
 * @param[in] contrast  Picture contrast parameter pointer 
 *
 * @retval 0  Picture contrast parameter pointer 
 * @retval  Picture contrast parameter pointer 0  Picture contrast parameter pointer ， Picture contrast parameter pointer 
 *
 * @remark  Picture contrast parameter pointer 128， Picture contrast parameter pointer 128 Picture contrast parameter pointer ， Picture contrast parameter pointer 128 Picture contrast parameter pointer 
 *
 * @attention  Picture contrast parameter pointer ， Picture contrast parameter pointer ISP Picture contrast parameter pointer .
 */
int IMP_ISP_Tuning_GetContrast(unsigned char *pcontrast);

 /**
 * @fn int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness)
 *
 *  Picture contrast parameter pointer ISP  Comprehensive effect picture sharpness 
 *
 * @param[in] sharpness  Picture sharpness parameter value 
 *
 * @retval 0  Picture sharpness parameter value 
 * @retval  Picture sharpness parameter value 0  Picture sharpness parameter value ， Picture sharpness parameter value 
 *
 * @remark  Picture sharpness parameter value 128， Picture sharpness parameter value 128 Increase sharpness ， Increase sharpness 128 Reduce sharpness. 
 *
 * @attention  Reduce sharpness. ， Reduce sharpness. ISP Reduce sharpness. .
 */
int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness);

/**
 * @fn int IMP_ISP_Tuning_GetSharpness(unsigned char *psharpness)
 *
 *  Reduce sharpness. ISP  Reduce sharpness. 
 *
 * @param[in] sharpness  Picture sharpness parameter pointer 
 *
 * @retval 0  Picture sharpness parameter pointer 
 * @retval  Picture sharpness parameter pointer 0  Picture sharpness parameter pointer ， Picture sharpness parameter pointer 
 *
 * @remark  Picture sharpness parameter pointer 128， Picture sharpness parameter pointer 128 Picture sharpness parameter pointer ， Picture sharpness parameter pointer 128 Picture sharpness parameter pointer 
 *
 * @attention  Picture sharpness parameter pointer ， Picture sharpness parameter pointer ISP Picture sharpness parameter pointer .
 */
int IMP_ISP_Tuning_GetSharpness(unsigned char *psharpness);

/**
 * @fn int IMP_ISP_Tuning_SetSaturation(unsigned char sat)
 *
 *  Picture sharpness parameter pointer ISP  Comprehensive effect picture saturation 
 *
 * @param[in] sat  Picture saturation parameter value 
 *
 * @retval 0  Picture saturation parameter value 
 * @retval  Picture saturation parameter value 0  Picture saturation parameter value ， Picture saturation parameter value 
 *
 * @remark  Picture saturation parameter value 128， Picture saturation parameter value 128 Increase saturation ， Increase saturation 128 Decrease saturation. 
 *
 * @attention  Decrease saturation. ， Decrease saturation. ISP Decrease saturation. .
 */
int IMP_ISP_Tuning_SetSaturation(unsigned char sat);

/**
 * @fn int IMP_ISP_Tuning_GetSaturation(unsigned char *psat)
 *
 *  Decrease saturation. ISP  Decrease saturation. 
 *
 * @param[in] sat  Picture saturation parameter pointer 
 *
 * @retval 0  Picture saturation parameter pointer 
 * @retval  Picture saturation parameter pointer 0  Picture saturation parameter pointer ， Picture saturation parameter pointer 
 *
 * @remark  Picture saturation parameter pointer 128， Picture saturation parameter pointer 128 Picture saturation parameter pointer ， Picture saturation parameter pointer 128 Picture saturation parameter pointer 
 *
 * @attention  Picture saturation parameter pointer ， Picture saturation parameter pointer ISP Picture saturation parameter pointer .
 */
int IMP_ISP_Tuning_GetSaturation(unsigned char *psat);
#if 0
/**
 * @fn int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode)
 *
 *  bypass ISP Module handling ， Direct output sensor image 
 *
 * @param[in] mode  Whether to bypass ISP Module processing parameters 
 *
 * @retval 0  Module processing parameters 
 * @retval  Module processing parameters 0  Module processing parameters ， Module processing parameters 
 *
 * @remark  If the function is enabled ，sensor The output image will not go through ISP Any processing of the module ， Direct output. 
 *
 * @attention  Direct output. ， Direct output. ISP Direct output. .
 */
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode);
#endif
/**
 * @fn int IMP_ISP_Tuning_SetFWFreeze(IMPISPTuningOpsMode mode)
 *
 *  freeze ISP Firmware operation ， Enable means freeze ISP firmware ， this is ISP The automatic algorithm will stop; if not enabled, it means ISP The firmware works normally. 
 *
 * @param[in] mode  Is it frozen ISP Firmware parameters 
 *
 * @retval 0  Firmware parameters 
 * @retval  Firmware parameters 0  Firmware parameters ， Firmware parameters 
 *
 * @attention  Firmware parameters ， Firmware parameters ISP Firmware parameters .
 */
int IMP_ISP_Tuning_SetFWFreeze(IMPISPTuningOpsMode mode);


/**
 * @fn int IMP_ISP_Tuning_SaveAllParam(char *path)
 *
 *  save ISP All debugging parameters of the module 
 *
 * @param[in] path  Path parameter pointer 
 *
 * @retval 0  Path parameter pointer 
 * @retval  Path parameter pointer 0  Path parameter pointer ， Path parameter pointer 
 *
 * @remark  Save all debugged ISP parameter. 
 *
 * @attention  parameter. ， parameter. ISP parameter. .
 */
int IMP_ISP_Tuning_SaveAllParam(char *path);

/**
 * @fn int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable)
 *
 * ISP Whether the module bypass
 *
 * @param[in] enable  whether bypass Output mode 
 *
 * @retval 0  Output mode 
 * @retval  Output mode 0  Output mode ， Output mode 
 *
 * @remark  Output mode 
 *
 * @attention  Output mode ， Output mode ISP Module is closed .
 */
int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable);

/**
 * @fn int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain)
 *
 *  Module is closed ISP The overall gain value of the output image 
 *
 * @param[in] gain  Get the pointer of the gain value parameter , The data storage format is [24.8]， high 24bit Is an integer ， low 8bit Is a decimal. 
 *
 * @retval 0  Is a decimal. 
 * @retval  Is a decimal. 0  Is a decimal. ， Is a decimal. 
 *
 * @attention  Is a decimal. ， Is a decimal. IMP_ISP_EnableSensor  Is a decimal.  IMP_ISP_EnableTuning Is a decimal. 
 */
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);

/**
 *  Is a decimal. ISP Whether the image mirror effect function is enabled 
 *
 * @fn int IMP_ISP_Tuning_SetISPHflip(IMPISPTuningOpsMode mode)
 *
 * @param[in] mode  Whether to enable the mirror effect 
 *
 * @retval 0  Whether to enable the mirror effect 
 * @retval  Whether to enable the mirror effect 0  Whether to enable the mirror effect ， Whether to enable the mirror effect 
 *
 * @attention  Whether to enable the mirror effect ，IMP_ISP_EnableTuning Whether to enable the mirror effect 
 */
int IMP_ISP_Tuning_SetISPHflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPHflip(IMPISPTuningOpsMode *pmode)
 *
 *  Whether to enable the mirror effect ISP The operating status of the image mirror effect function 
 *
 * @param[in] pmode  Operation parameter pointer 
 *
 * @retval 0  Operation parameter pointer 
 * @retval  Operation parameter pointer 0  Operation parameter pointer ， Operation parameter pointer 
 *
 * @attention  Operation parameter pointer ，IMP_ISP_EnableTuning Operation parameter pointer 
 */
int IMP_ISP_Tuning_GetISPHflip(IMPISPTuningOpsMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode)
 *
 *  Operation parameter pointer ISP Whether the image upside down effect function is enabled 
 *
 * @param[in] mode  Whether to enable the image up and down reverse 
 *
 * @retval 0  Whether to enable the image up and down reverse 
 * @retval  Whether to enable the image up and down reverse 0  Whether to enable the image up and down reverse ， Whether to enable the image up and down reverse 
 *
 * @attention  Whether to enable the image up and down reverse ，IMP_ISP_EnableTuning Whether to enable the image up and down reverse 
 */
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPVflip(IMPISPTuningOpsMode *pmode)
 *
 *  Whether to enable the image up and down reverse ISP The operating status of the image upside down effect function 
 *
 * @param[in] pmode  The operating status of the image upside down effect function 
 *
 * @retval 0  The operating status of the image upside down effect function 
 * @retval  The operating status of the image upside down effect function 0  The operating status of the image upside down effect function ， The operating status of the image upside down effect function 
 *
 * @attention  The operating status of the image upside down effect function ，IMP_ISP_EnableTuning The operating status of the image upside down effect function 
 */
int IMP_ISP_Tuning_GetISPVflip(IMPISPTuningOpsMode *pmode);

/**
 * ISP  Working mode configuration ， Normal mode or night vision mode. 
 */
typedef enum {
	IMPISP_RUNNING_MODE_DAY = 0,				/**<  Normal mode  */
	IMPISP_RUNNING_MODE_NIGHT = 1,				/**<  Night vision mode  */
	IMPISP_RUNNING_MODE_BUTT,					/**<  Max  */
} IMPISPRunningMode;

/**
 * @fn int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode)
 *
 *  Max ISP Operating mode ， Normal mode or night vision mode; the default is normal mode. 
 *
 * @param[in] mode Operating mode parameters 
 *
 * @retval 0  Operating mode parameters 
 * @retval  Operating mode parameters 0  Operating mode parameters ， Operating mode parameters 
 *
 *  Example: 
 * @code
 * IMPISPRunningMode mode;
 *
 *	if( it is during a night now){
		mode = IMPISP_RUNNING_MODE_NIGHT
	}else{
		mode = IMPISP_RUNNING_MODE_DAY;
	}
	ret = IMP_ISP_Tuning_SetISPRunningMode(mode);
	if(ret){
		IMP_LOG_ERR(TAG, "IMP_ISP_Tuning_SetISPRunningMode error !\n");
		return -1;
	}
 *
 * @endcode
 *
 * @attention  Example: ，IMP_ISP_EnableTuning Example: 
 */
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode)
 *
 *  Example: ISP Example: ， Example: 
 *
 * @param[in] pmode Example: 
 *
 * @retval 0  Example: 
 * @retval  Example: 0  Example: ， Example: 
 *
 * @attention  Example: ，IMP_ISP_EnableTuning Example: 
 */
int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode);

/**
 * ISP  Automatic exposure strategy configuration ， Normal mode or exposure priority mode. 
 **/
typedef enum {
	IMPISP_AE_STRATEGY_SPLIT_BALANCED = 0,              /**<  Normal mode or exposure priority mode.  */
	IMPISP_AE_STRATEGY_SPLIT_INTEGRATION_PRIORITY = 1,      /**<  Exposure priority mode  */
	IMPISP_AE_STRATEGY_BUTT,                    /**<  Exposure priority mode  */
} IMPISPAeStrategy;

/**
 * @fn int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy strategy)
 *
 *  Exposure priority mode ISP Exposure priority mode ， Exposure priority mode ， Normal mode or exposure priority mode; the default is normal mode. 
 *
 * @param[in] strategy  Automatic exposure strategy parameters 
 *
 * @retval 0  Automatic exposure strategy parameters 
 * @retval  Automatic exposure strategy parameters 0  Automatic exposure strategy parameters ， Automatic exposure strategy parameters 
 *  Automatic exposure strategy parameters 
 * @code
 * IMPISPAeStrategy strategy;
 *
 *  if( it is a normal scence){
		mode = IMPISP_AE_STRATEGY_SPLIT_BALANCED
	 }else{
		mode = IMPISP_AE_STRATEGY_SPLIT_INTEGRATION_PRIORITY;
     }
	 ret = IMP_ISP_Tuning_SetAeStrategy(strategy);
	if(ret){
	IMP_LOG_ERR(TAG, "IMP_ISP_Tuning_SetAeStrategy error !\n");
	return -1;
	}
*
* @endcode
*
* @attention  Automatic exposure strategy parameters ，IMP_ISP_EnableTuning Automatic exposure strategy parameters 
*/
int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy strategy);

/**
* @fn int IMP_ISP_Tuning_GetAeStrategy(IMPISPAeStrategy *pstrategy)
*
*  Automatic exposure strategy parameters ISP Automatic exposure strategy parameters ， Automatic exposure strategy parameters 
* @param[in] pstrategy  Automatic exposure strategy parameter pointer 
*
* @retval 0  Automatic exposure strategy parameter pointer 
* @retval  Automatic exposure strategy parameter pointer 0  Automatic exposure strategy parameter pointer ， Automatic exposure strategy parameter pointer 
*
* @attention  Automatic exposure strategy parameter pointer ，IMP_ISP_EnableTuning Automatic exposure strategy parameter pointer 
*/
int IMP_ISP_Tuning_GetAeStrategy(IMPISPAeStrategy *pstrategy);

/**
 * gamma
 */
typedef struct {
	uint16_t gamma[129];		/**< gamma Parameter array ， Have 129 Points  */
} IMPISPGamma;

/**
* @fn int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma)
*
*  Points GAMMA parameter .
* @param[in] gamma gamma parameter 
*
* @retval 0  parameter 
* @retval  parameter 0  parameter ， parameter 
*
* @attention  parameter ，IMP_ISP_EnableTuning parameter 
*/
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma)
*
*  parameter GAMMA parameter .
* @param[out] gamma gamma parameter 
*
* @retval 0  parameter 
* @retval  parameter 0  parameter ， parameter 
*
* @attention  parameter ，IMP_ISP_EnableTuning parameter 
*/
int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_SetAeComp(int comp)
*
*  parameter AE make up. AE Compensation parameters can adjust the image AE target， The recommended setting range is [90-150].
* @param[in] comp AE Compensation parameter 
*
* @retval 0  Compensation parameter 
* @retval  Compensation parameter 0  Compensation parameter ， Compensation parameter 
*
* @attention  Compensation parameter ，IMP_ISP_EnableTuning Compensation parameter 
*/
int IMP_ISP_Tuning_SetAeComp(int comp);

/**
* @fn int IMP_ISP_Tuning_GetAeComp(int *comp)
*
*  Compensation parameter AE Compensation parameter 
* @param[out] comp AE Compensation parameter 
*
* @retval 0  Compensation parameter 
* @retval  Compensation parameter 0  Compensation parameter ， Compensation parameter 
*
* @attention  Compensation parameter ，IMP_ISP_EnableTuning Compensation parameter 
*/
int IMP_ISP_Tuning_GetAeComp(int *comp);

/**
 *  Exposure mode 
 */
enum isp_core_expr_mode {
	ISP_CORE_EXPR_MODE_AUTO,			/**<  Exposure mode  */
	ISP_CORE_EXPR_MODE_MANUAL,			/**<  Manual mode  */
};

/**
 *  Exposure unit 
 */
enum isp_core_expr_unit {
	ISP_CORE_EXPR_UNIT_LINE,			/**<  Row  */
	ISP_CORE_EXPR_UNIT_US,				/**<  millisecond  */
};

/**
 *  Exposure parameters 
 */
typedef union isp_core_expr_attr{
	struct {
		enum isp_core_expr_mode mode;		/**<  Set exposure mode  */
		enum isp_core_expr_unit unit;		/**<  Set exposure unit  */
		uint16_t time;
	} s_attr;
	struct {
		enum isp_core_expr_mode mode;			/**<  Acquired exposure mode  */
		uint16_t integration_time;		/**<  Exposure time ， Unit is line  */
		uint16_t integration_time_min;	/**<  Minimum exposure time obtained ， Minimum exposure time obtained  */
		uint16_t integration_time_max;	/**<  Maximum exposure time obtained ， Maximum exposure time obtained  */
		uint16_t one_line_expr_in_us;		/**<  The number of microseconds corresponding to the exposure time of the acquired line  */
	} g_attr;
}IMPISPExpr;


/**
 * @fn int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr)
 *
 *  The number of microseconds corresponding to the exposure time of the acquired line AE The number of microseconds corresponding to the exposure time of the acquired line 
 *
 * @param[in] expr AE The number of microseconds corresponding to the exposure time of the acquired line 
 *
 * @retval 0  The number of microseconds corresponding to the exposure time of the acquired line 
 * @retval  The number of microseconds corresponding to the exposure time of the acquired line 0  The number of microseconds corresponding to the exposure time of the acquired line ， The number of microseconds corresponding to the exposure time of the acquired line 
 *
 * @attention  The number of microseconds corresponding to the exposure time of the acquired line ，IMP_ISP_EnableTuning The number of microseconds corresponding to the exposure time of the acquired line 
 */
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr);

/**
 * @fn int IMP_ISP_Tuning_GetExpr(IMPISPExpr *expr)
 *
 *  The number of microseconds corresponding to the exposure time of the acquired line AE The number of microseconds corresponding to the exposure time of the acquired line 
 *
 * @param[out] expr AE The number of microseconds corresponding to the exposure time of the acquired line 
 *
 * @retval 0  The number of microseconds corresponding to the exposure time of the acquired line 
 * @retval  The number of microseconds corresponding to the exposure time of the acquired line 0  The number of microseconds corresponding to the exposure time of the acquired line ， The number of microseconds corresponding to the exposure time of the acquired line 
 *
 * @attention  The number of microseconds corresponding to the exposure time of the acquired line ，IMP_ISP_EnableTuning The number of microseconds corresponding to the exposure time of the acquired line 
 */
int IMP_ISP_Tuning_GetExpr(IMPISPExpr *expr);

/**
 *  Exposure statistics area selection 
 */
typedef union isp_core_ae_roi_select{
	struct {
		unsigned endy :8;                   /**<  End point y coordinate  (0 ~ 255)*/
		unsigned endx :8;                   /**<  coordinate x coordinate  (0 ~ 255)*/
		unsigned starty :8;                 /**<  Starting point y Starting point  (0 ~ 255)*/
		unsigned startx :8;                 /**<  Starting point x Starting point  (0 ~ 255)*/
	};
	uint32_t value;
} IMPISPAERoi;

/**
 * @fn int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi)
 *
 *  Starting point AE Statistics area. 
 *
 * @param[out] isp_ae_roi AE Rectangular statistical area parameters. 
 *
 * @retval 0  Rectangular statistical area parameters. 
 * @retval  Rectangular statistical area parameters. 0  Rectangular statistical area parameters. ， Rectangular statistical area parameters. 
 *
 * @attention  Rectangular statistical area parameters. ，IMP_ISP_EnableTuning Rectangular statistical area parameters. 
 */
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);

/**
 * @fn int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi)
 *
 *  Rectangular statistical area parameters. AE Rectangular statistical area parameters. 
 *
 * @param[in] isp_ae_roi AE Rectangular statistical area parameters. 
 *
 * @retval 0  Rectangular statistical area parameters. 
 * @retval  Rectangular statistical area parameters. 0  Rectangular statistical area parameters. ， Rectangular statistical area parameters. 
 *
 * @attention  Rectangular statistical area parameters. ，IMP_ISP_EnableTuning Rectangular statistical area parameters. 
 */
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);

/**
 *  White balance mode 
 */
enum isp_core_wb_mode {
	ISP_CORE_WB_MODE_AUTO = 0,			/**<  White balance mode  */
	ISP_CORE_WB_MODE_MANUAL,			/**<  White balance mode  */
	ISP_CORE_WB_MODE_DAY_LIGHT,			/**<  sunny day  */
	ISP_CORE_WB_MODE_CLOUDY,			/**<  cloudy day  */
	ISP_CORE_WB_MODE_INCANDESCENT,		/**<  Incandescent lamp  */
	ISP_CORE_WB_MODE_FLOURESCENT,		/**<  Fluorescent lamp  */
	ISP_CORE_WB_MODE_TWILIGHT,			/**<  dusk  */
	ISP_CORE_WB_MODE_SHADE,				/**<  shadow  */
	ISP_CORE_WB_MODE_WARM_FLOURESCENT,	/**<  Warm fluorescent lamp  */
};

/**
 *  White balance parameters 
 */
typedef struct isp_core_wb_attr{
	enum isp_core_wb_mode mode;		/**<  White balance parameters ， Divided into automatic and manual modes  */
	uint16_t rgain;			/**<  Red gain ， Effective in manual mode  */
	uint16_t bgain;			/**<  Blue gain ， Blue gain  */
}IMPISPWB;

/**
 * @fn int IMP_ISP_Tuning_SetWB(IMPISPWB *wb)
 *
 *  Set the white balance function settings. Can set automatic and manual mode ， Manual mode is mainly set by rgain [[[ bgain achieve. 
 *
 * @param[in] wb  Set the white balance parameters. 
 *
 * @retval 0  Set the white balance parameters. 
 * @retval  Set the white balance parameters. 0  Set the white balance parameters. ， Set the white balance parameters. 
 *
 * @attention  Set the white balance parameters. ，IMP_ISP_EnableTuning Set the white balance parameters. 
 */
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_GetWB(IMPISPWB *wb)
 *
 *  Get the white balance function setting. 
 *
 * @param[out] wb  The obtained white balance parameters. 
 *
 * @retval 0  The obtained white balance parameters. 
 * @retval  The obtained white balance parameters. 0  The obtained white balance parameters. ， The obtained white balance parameters. 
 *
 * @attention  The obtained white balance parameters. ，IMP_ISP_EnableTuning The obtained white balance parameters. 
 */
int IMP_ISP_Tuning_GetWB(IMPISPWB *wb);

/**
 * @fn IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb)
 *
 *  Obtain white balance statistics. 
 *
 * @param[out] wb  The obtained white balance statistics. 
 *
 * @retval 0  The obtained white balance statistics. 
 * @retval  The obtained white balance statistics. 0  The obtained white balance statistics. ， The obtained white balance statistics. 
 *
 * @attention  The obtained white balance statistics. ，IMP_ISP_EnableTuning The obtained white balance statistics. 
 */
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB* isp_wb_attr)
 *
 *  The obtained white balance statistics. ISP The obtained white balance statistics. AWB of CWF The position of the light source 
 *
 * @param[out] isp_wb_attr CWF Light source position coordinates 
 *
 * @retval 0  Light source position coordinates 
 * @retval  Light source position coordinates 0  Light source position coordinates ， Light source position coordinates 
 *
 * @attention  Light source position coordinates ，IMP_ISP_EnableTuning Light source position coordinates 
 */
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);

/**
 * @fn int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr)
 *
 *  Light source position coordinates ISP Light source position coordinates AWB Light source position coordinates CWF Light source position coordinates 
 *
 * @param[in] isp_wb_attr CWF Light source position coordinates 
 *
 * @retval 0  Light source position coordinates 
 * @retval  Light source position coordinates 0  Light source position coordinates ， Light source position coordinates 
 *  Light source position coordinates 
 * @code
 * IMPISPWB isp_wb_attr;
 *
 *isp_wb_attr.rgain = x;
 *isp_wb_attr.bgain = y;
 *IMP_ISP_Tuning_Awb_SetCwfShift(isp_wb_attr);
 if(ret){
 IMP_LOG_ERR(TAG, "IMP_ISP_Tuning_Awb_SetCwfShift error !\n");
 return -1;
 }
 *
 * @endcode
 *
 * @attention  Light source position coordinates ，IMP_ISP_EnableTuning Light source position coordinates 
 */
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);

/**
 * @fn int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain)
 *
 *  Light source position coordinates sensor You can set the maximum Again . 
 *
 * @param[in] gain sensor The maximum that can be set again.0 Means 1x，32 Means 2x， And so on. 
 *
 * @retval 0  And so on. 
 * @retval  And so on. 0  And so on. ， And so on. 
 *
 * @attention  And so on. ，IMP_ISP_EnableTuning And so on. 
 */
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);

/**
 * @fn int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain)
 *
 *  And so on. sensor And so on. Again And so on. 
 *
 * @param[out] gain sensor And so on. again.0 And so on. 1x，32 And so on. 2x， And so on. 
 *
 * @retval 0  And so on. 
 * @retval  And so on. 0  And so on. ， And so on. 
 *
 * @attention  And so on. ，IMP_ISP_EnableTuning And so on. 
 */
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain)
 *
 *  And so on. ISP And so on. Dgain And so on. 
 *
 * @param[in] ISP Dgain  And so on. dgain.0 And so on. 1x，32 And so on. 2x， And so on. 
 *
 * @retval 0  And so on. 
 * @retval  And so on. 0  And so on. ， And so on. 
 *
 * @attention  And so on. ，IMP_ISP_EnableTuning And so on. 
 */
int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain);

/**
 * @fn int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain)
 *
 *  And so on. ISP Set maximum Dgain Set maximum 
 *
 * @param[out] ISP Dgain  Can get the largest set dgain.0 Can get the largest set 1x，32 Can get the largest set 2x， Can get the largest set 
 *
 * @retval 0  Can get the largest set 
 * @retval  Can get the largest set 0  Can get the largest set ， Can get the largest set 
 *
 * @attention  Can get the largest set ，IMP_ISP_EnableTuning Can get the largest set 
 */
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void))
 *
 *  Set the video loss function. When it appears sensor When there is a problem with the connection line to the motherboard ， The set callback function will be executed. 
 *
 * @param[in] cb  Callback. 
 *
 * @retval 0  Callback. 
 * @retval  Callback. 0  Callback. ， Callback. 
 *
 * @attention  Callback. ，IMP_ISP_EnableTuning Callback. 
 */
int IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void));

/**
 * @fn int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength)
 *
 *  Set the intensity of strong light suppression. 
 *
 * @param[in] strength  Strong light suppression intensity parameter . The value range is [ 0-10], 0 Indicates that the function is turned off. 
 *
 * @retval 0  Indicates that the function is turned off. 
 * @retval  Indicates that the function is turned off. 0  Indicates that the function is turned off. ， Indicates that the function is turned off. 
 *
 * @attention  Indicates that the function is turned off. ，IMP_ISP_EnableTuning Indicates that the function is turned off. 
 */
int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength);

/**
 * @fn int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio)
 *
 *  Indicates that the function is turned off. 3D Noise reduction intensity. 
 *
 * @param[in] ratio  Intensity adjustment ratio . If set to 90 It means that it is set to the default value 90%. It means that it is set to the default value 50-150].
 *
 * @retval 0  It means that it is set to the default value 
 * @retval  It means that it is set to the default value 0  It means that it is set to the default value ， It means that it is set to the default value 
 *
 * @attention  It means that it is set to the default value ，IMP_ISP_EnableTuning It means that it is set to the default value 
 */
int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio)
 *
 *  It means that it is set to the default value 2D It means that it is set to the default value 
 *
 * @param[in] ratio  It means that it is set to the default value . It means that it is set to the default value 90 It means that it is set to the default value 90%. It means that it is set to the default value 50-150].
 *
 * @retval 0  It means that it is set to the default value 
 * @retval  It means that it is set to the default value 0  It means that it is set to the default value ， It means that it is set to the default value 
 *
 * @attention  It means that it is set to the default value ，IMP_ISP_EnableTuning It means that it is set to the default value 
 */
int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetDPStrength(uint32_t ratio)
 *
 *  It means that it is set to the default value DPC strength. 
 *
 * @param[in] ratio  strength. . strength. 90 strength. 90%. strength. 50-150].
 *
 * @retval 0  strength. 
 * @retval  strength. 0  strength. ， strength. 
 *
 * @attention  strength. ，IMP_ISP_EnableTuning strength. 
 */
int IMP_ISP_Tuning_SetDPStrength(uint32_t ratio);

/**
 * ISP ANTIFOG  Operating mode. 
 */
typedef enum {
	ANTIFOG_DISABLE,			/**<  Operating mode.  */
	ANTIFOG_STRONG,				/**<  Strong  */
	ANTIFOG_MEDIUM,				/**<  Strong  */
	ANTIFOG_WEAK,				/**<  weak  */
}IMPISPAntiFogAttr;

/**
* @fn int IMP_ISP_Tuning_SetAntiFogAttr(IMPISPAntiFogAttr attr)
*
*  weak ANTIFOG Attributes. 
* @param[in] attr ANTIFOG Attribute parameter 
*
* @retval 0  Attribute parameter 
* @retval  Attribute parameter 0  Attribute parameter ， Attribute parameter 
*
* @attention  Attribute parameter ，IMP_ISP_EnableTuning Attribute parameter 
*/
int IMP_ISP_Tuning_SetAntiFogAttr(IMPISPAntiFogAttr attr);

/**
 * ISP EV  Attribute parameter 
 */
typedef struct {
	uint32_t ev;			/**<  Exposure value  */
	uint32_t expr_us;		/**<  Exposure time  */
	uint32_t ev_log2;		/**<log Format exposure time  */
	uint32_t again;			/**<  Analog gain  */
	uint32_t dgain;			/**<  Digital gain  */
	uint32_t gain_log2;		/**< log Format gain  */
}IMPISPEVAttr;

/**
* @fn int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr)
*
*  Format gain EV Format gain 
* @param[out] attr EV Format gain 
*
* @retval 0  Format gain 
* @retval  Format gain 0  Format gain ， Format gain 
*
* @attention  Format gain ，IMP_ISP_EnableTuning Format gain 
*/
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

/**
 * @}
 */

#endif /* __IMP_ISP_H__ */
