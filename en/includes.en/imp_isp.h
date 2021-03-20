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
 * @brief Image signal processing unit. Sensor Registration, addition, deletion, etc. 
 *
 * ISP Module has nothing to do with data flow ， No need to proceed Bind， Only applies to effect parameter settings and Sensor control. 
 *
 * ISP The enabling steps of the module are as follows: 
 * @code
 * int ret = 0;
 * ret = IMP_ISP_Open(); // step.1 create ISP Module 
 * if(ret < 0){
 * printf("Failed to ISPInit\n");
 * return -1;
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
 *	.modalias = "xx", //SPI Device name ， Must and sensor Driving struct spi_device_id middle name Unanimous. 
 *	.bus_num = xx, //SPI Bus address 
 * }
 * ret = IMP_ISP_AddSensor(&sensor); //step.2 add one sensor， Before this operation sensor The driver has been added to the kernel. 
 * if (ret < 0) {
 * printf("Failed to Register sensor\n");
 * return -1;
 * }
 *
 * ret = IMP_ISP_EnableSensor(void); //step.3 Enable sensor， right now sensor Start outputting images. 
 * if (ret < 0) {
 * printf("Failed to EnableSensor\n");
 * return -1;
 * }
 *
 * ret = IMP_ISP_EnableTuning(); //step.4 Enable ISP tuning, Before calling ISP Debug interface. 
 * if (ret < 0) {
 * printf("Failed to EnableTuning\n");
 * return -1;
 * }
 *
 * For debugging interface, please refer to ISP Debug interface documentation. //step.5 Effect debugging. 
 *
 * @endcode
 * ISP The uninstallation steps of the module are as follows: 
 * @code
 * int ret = 0;
 * IMPSensorInfo sensor;
 * sensor.name = "xxx";
 * ret = IMP_ISP_DisableTuning(); //step.1 shut down ISP tuning
 * if (ret < 0) {
 * printf("Failed to disable tuning\n");
 * return -1;
 * }
 *
 * ret = IMP_ISP_DisableSensor(); //step.2 shut down sensor， right now sensor Stop outputting images; before this operation FrameSource All must be closed. 
 * if (ret < 0) {
 * printf("Failed to disable sensor\n");
 * return -1;
 * }
 *
 * ret = IMP_ISP_DelSensor(&sensor); //step.3 delete sensor， Before this operation sensor Must be closed. 
 * if (ret < 0) {
 * printf("Failed to disable sensor\n");
 * return -1;
 * }
 *
 * ret = IMP_ISP_Close(); //step.4 Clean up ISP Module ， All before this operation sensor Must be deleted. 
 * if (ret < 0) {
 * printf("Failed to disable sensor\n");
 * return -1;
 * }
 * @endcode
 * For more usage methods, please refer to Samples
 * @{
 */

/**
* Camera control bus type enumeration 
*/
typedef enum {
	TX_SENSOR_CONTROL_INTERFACE_I2C = 1,	/**< I2C Control bus */
	TX_SENSOR_CONTROL_INTERFACE_SPI,	/**< SPI Control bus */
} IMPSensorControlBusType;

/**
* The type of camera control bus is I2C Time ， Parameter structure to be configured 
*/
typedef struct {
	char type[20];		/**< I2C Device name ， Must be driven with the camera struct i2c_device_id in name Variables are consistent */
	int addr;		/**< I2C address */
	int i2c_adapter_id;	/**< I2C Controller */
} IMPI2CInfo;
/**
* The type of camera control bus is SPI Time ， Parameter structure to be configured 
*/
typedef struct {
	char modalias[32];	/**< SPI Device name ， Must be driven with the camera struct spi_device_id in name Variables are consistent */
	int bus_num;		/**< SPI Bus address */
} IMPSPIInfo;

/**
* Camera registration information structure 
*/
typedef struct {
	char name[32];					/**< Camera name */
	IMPSensorControlBusType cbus_type;	/**< Camera control bus type */
	union {
		IMPI2CInfo i2c;				/**< I2C Bus information */
		IMPSPIInfo spi;				/**< SPI Bus information */
	};
	unsigned short rst_gpio;		/**< webcam reset Interface link GPIO， Note: this parameter is not enabled now */
	unsigned short pwdn_gpio;		/**< webcam power down Interface link GPIO， Note: this parameter is not enabled now */
	unsigned short power_gpio;		/**< webcam power Interface link GPIO， Note: this parameter is not enabled now */
} IMPSensorInfo;

/**
 * @fn int IMP_ISP_Open(void)
 *
 * turn on ISP Module 
 *
 * @param no 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark create ISP Module ， Ready to ISP Add to sensor， And turn on ISP Effect debugging function. 
 *
 * @attention This function must be added sensor Was called before. 
 */
int IMP_ISP_Open(void);

/**
 * @fn int IMP_ISP_Close(void)
 *
 * shut down ISP Module 
 *
 * @param no 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark ISP Module ，ISP The module no longer works. 
 *
 * @attention Before using this function ， Must guarantee all FrameSource And the effect debugging function has been closed ， all sensor Have been uninstalled .
 */
int IMP_ISP_Close(void);

/**
 * @fn int IMP_ISP_AddSensor(IMPSensorInfo *pinfo)
 *
 * add one sensor， Used to ISP Module provides data source 
 *
 * @param[in] pinfo Need to add sensor Information pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Add a camera ， Used to provide images. 
 *
 * @attention Before using this function ， It must be ensured that the camera driver has been registered into the kernel .
 */
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);

/**
 * @fn int IMP_ISP_DelSensor(IMPSensorInfo *pinfo)
 *
 * Delete one sensor
 *
 * @param[in] pinfo Need to be deleted sensor Information pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Delete a camera. 
 *
 * @attention Before using this function ， It must be ensured that the camera has stopped working ， Called IMP_ISP_DisableSensor function .
 */
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);

/**
 * @fn int IMP_ISP_EnableSensor(void)
 *
 * Enable one sensor
 *
 * @param no 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Enable a camera ， Make it start transferring images , such FrameSource To output the image ， at the same time ISP Only then can the effect be debugged. 
 *
 * @attention Before using this function ， It must be ensured that the camera has been added ISP Module .
 */
int IMP_ISP_EnableSensor(void);

/**
 * @fn int IMP_ISP_DisableSensor(void)
 *
 * Disable one sensor
 *
 * @param no 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Disable a camera ， Stop transmitting images , such FrameSource Unable to output image ， at the same time ISP The effect can not be debugged either. 
 *
 * @attention Before using this function ， Must guarantee all FrameSource Have stopped outputting images ， At the same time, the effect debugging is also in the disabled state .
 */
int IMP_ISP_DisableSensor(void);

/**
 * @fn int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value)
 *
 * Set up sensor The value of a register 
 *
 * @param[in] reg Register address 
 *
 * @param[in] value Register value 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark You can set one directly sensor The value of the register. 
 *
 * @attention Before using this function ， It must be ensured that the camera has been enabled .
 */
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value);

/**
 * @fn int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *value)
 *
 * Obtain sensor The value of a register 
 *
 * @param[in] reg Register address 
 *
 * @param[in] value Pointer to register value 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark You can get one directly sensor The value of the register. 
 *
 * @attention Before using this function ， It must be ensured that the camera has been enabled .
 */
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *value);

typedef enum {
	IMPISP_TUNING_OPS_MODE_DISABLE,			/**< Disable the module function */
	IMPISP_TUNING_OPS_MODE_ENABLE,			/**< Enable the module function */
	IMPISP_TUNING_OPS_MODE_BUTT,			/**< Used to judge the validity of parameters ， The parameter size must be less than this value */
} IMPISPTuningOpsMode;

typedef enum {
	IMPISP_TUNING_OPS_TYPE_AUTO,			/**< The operation of the module is automatic mode */
	IMPISP_TUNING_OPS_TYPE_MANUAL,			/**< The operation of this module is manual mode */
	IMPISP_TUNING_OPS_TYPE_RANGE, /**< The operation of this module is the setting range mode */
	IMPISP_TUNING_OPS_TYPE_BUTT,			/**< Used to judge the validity of parameters ， The parameter size must be less than this value */
} IMPISPTuningOpsType;

/**
 * @fn int IMP_ISP_EnableTuning(void)
 *
 * Enable ISP Effect debugging function 
 *
 * @param no 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee IMP_ISP_EnableSensor Was executed and returned successfully .
 */
int IMP_ISP_EnableTuning(void);

/**
 * @fn int IMP_ISP_DisableTuning(void)
 *
 * Disable ISP Effect debugging function 
 *
 * @param no 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， It must be ensured that the sensor prior to ， Disable first ISP Effect debugging (that is, call this function) .
 */
int IMP_ISP_DisableTuning(void);

/**
 * @fn int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den)
 *
 * Set camera output frame rate 
 *
 * @param[in] fps_num Set the numerator parameter of the frame rate 
 * @param[in] fps_den Set the denominator parameter of the frame rate 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee IMP_ISP_EnableSensor with IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);

/**
 * @fn int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den)
 *
 * Get camera output frame rate 
 *
 * @param[in] fps_num Get a pointer to the frame rate molecular parameters 
 * @param[in] fps_den Get a pointer to the frame rate denominator parameter 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee IMP_ISP_EnableSensor with IMP_ISP_EnableTuning Has been called. 
 * @attention This function must be called to obtain the camera's default frame rate before the frame channel is enabled to start transmitting data. 
 */
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);

/**
 * ISP Anti-flicker property parameter structure. 
 */
typedef enum {
	IMPISP_ANTIFLICKER_DISABLE,	/**< Disable ISP Anti-flash function */
	IMPISP_ANTIFLICKER_50HZ,	/**< Enable ISP Anti-flash function , And set the frequency to 50HZ */
	IMPISP_ANTIFLICKER_60HZ,	/**< Enable ISP Anti-flash function ， And set the frequency to 60HZ */
	IMPISP_ANTIFLICKER_BUTT,	/**< Used to judge the validity of parameters ， The parameter size must be less than this value */
} IMPISPAntiflickerAttr;

/**
 * @fn int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr)
 *
 * Set up ISP Anti-flash properties 
 *
 * @param[in] attr Set parameter value 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);

/**
 * @fn int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr)
 *
 * obtain ISP Anti-flash properties 
 *
 * @param[in] pattr Get parameter value pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);

/**
 * ISP Dynamic range compression module operation mode. 
 */
typedef enum {
	IMPISP_DRC_MANUAL,				/**< ISP Dynamic range compression module manual mode */
	IMPISP_DRC_UNLIMIT,				/**< ISP Highest compression mode of dynamic range compression module */
	IMPISP_DRC_HIGH,				/**< ISP Dynamic range compression module high compression mode */
	IMPISP_DRC_MEDIUM,				/**< ISP Compression mode in the dynamic range compression module */
	IMPISP_DRC_LOW,					/**< ISP Dynamic range compression module low compression mode */
	IMPISP_DRC_DISABLE,				/**< ISP Dynamic range compression module is not enabled */
	IMPISP_DRC_RANGE,				/**< ISP Dynamic range compression module range setting mode */
} IMPISPDrcMode;

/**
 * ISP Dynamic range compression module attribute parameters. 
 */
typedef struct {
	IMPISPDrcMode mode;				/**< ISP Dynamic range compression module operation mode selection */
	unsigned char drc_strength;			/**< Target value set in manual mode ， The value range is [0, 0xff] */
	unsigned char dval_max;				/**< Range mode maximum ， The value range is [0, 0xff] */
	unsigned char dval_min;				/**< Range mode minimum ， The value range is [0, 0xff] */
	unsigned char slop_max;				/**< Strength control parameters ， The value range is [0, oxff] */
	unsigned char slop_min;				/**< Strength control parameters ， The value range is [0, oxff] */
	unsigned short black_level;			/**< DRC Enhanced minimum pixel value ， The value range is [0, oxfff] */
	unsigned short white_level;			/**< DRC Enhanced maximum pixel value ， The value range is [0, oxfff] */
} IMPISPDrcAttr;

/**
 * @fn int IMP_ISP_Tuning_SetRawDRC(IMPISPDrcAttr *pinfo)
 *
 * Set up ISP RAW Figure dynamic range compression module parameters 
 *
 * @param[in] pinfo Dynamic range parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Set up RGB RAW Graph dynamic range compression operation type ， strength ， The maximum and minimum pixel values ​​ that need to be enhanced. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetRawDRC(IMPISPDrcAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo)
 *
 * Obtain ISP RAW Figure dynamic range compression module parameters 
 *
 * @param[in] pinfo Dynamic range parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Set up RGB RAW Graph dynamic range compression operation type ， strength ， The maximum and minimum pixel values ​​ that need to be enhanced. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);

/**
 * ISP Attribute parameters of the spatial noise reduction module. 
 */
typedef struct {
	IMPISPTuningOpsMode enable;			/**< Enable spatial noise reduction function */
	IMPISPTuningOpsType type;				/**< Space noise reduction function operation type ， Automatic or manual */
	unsigned char sinter_strength;				/**< Space noise reduction intensity ， Manual mode is effective ， The value range is [0, 0xff] */
	unsigned char sval_max;				/**< Space noise reduction intensity ， Manual mode is effective ， The value range is [0, 0xff] */
	unsigned char sval_min;				/**< Space noise reduction intensity ， Manual mode is effective ， The value range is [0, 0xff] */
} IMPISPSinterDenoiseAttr;

/**
 * ISP Time domain noise reduction module operation mode. 
 */
typedef enum {
	IMPISP_TEMPER_DISABLE,				/**< ISP Time domain noise reduction module is not enabled */
	IMPISP_TEMPER_AUTO,					/**< ISP Time domain noise reduction module automatic mode */
	IMPISP_TEMPER_MANUAL,				/**< ISP Time domain noise reduction module manual mode */
	IMPISP_TEMPER_RANGE,				/**< ISP Time domain noise reduction module range setting mode */
} IMPISPTemperMode;

/**
 * ISP Attribute parameters of the time domain noise reduction module. 
 */
typedef struct imp_isp_temper_denoise_attr {
	IMPISPTemperMode type;					/**< Time domain noise reduction function operation type ， Disable ， Automatic or manual */
	unsigned char temper_strength;				/**< Time domain noise reduction intensity ， Manual mode is effective ， The value range is [0, 0xff] */
	unsigned char tval_max;						/**< Maximum spatial noise reduction range setting mode , The value range is [0, 0xff] */
	unsigned char tval_min;						/**< Space noise reduction range setting mode minimum , The value range is [0, 0xff] */
} IMPISPTemperDenoiseAttr;


/**
 * @fn int IMP_ISP_Tuning_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo)
 *
 * Set up ISP Spatial noise reduction module parameters 
 *
 * @param[in] pinfo Time domain noise reduction parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Set the correction parameters of the spatial noise reduction module. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo)
 *
 * Obtain ISP Spatial noise reduction module parameters 
 *
 * @param[in] pinfo Spatial noise reduction parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Obtain the correction parameters of the spatial noise reduction module. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
#if 0
/**
* @fn int IMP_ISP_Tuning_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
*
* Set up ISP Time domain noise reduction module mode 
*
* @param[in] pinfo Time domain noise reduction parameter pointer 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @remark Set time domain noise reduction module mode parameters ， The default automatic mode. 
*
* @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
*/
int IMP_ISP_Tuning_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
#endif
/**
 * @fn int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo)
 *
 * Set up ISP Time domain noise reduction module parameters 
 *
 * @param[in] pinfo Time domain noise reduction parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Set the correction parameters of the time domain noise reduction module ， The module is turned on by default; because the module requires additional memory ， Please close the module if you don ’ t need it ， The memory is released once it is closed ， Can no longer be opened. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo)
 *
 * Obtain ISP Time domain noise reduction module parameters 
 *
 * @param[in] pinfo Time domain noise reduction module parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Obtain the correction parameters of the time domain noise reduction module. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode)
 *
 * Set up ISP Whether the wide dynamic module is enabled 
 *
 * @param[in] mode Wide dynamic module parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Set wide dynamic module calibration parameters ， The module is turned on by default; because the module requires additional memory ， Please close the module if you don ’ t need it ， The memory is released once it is closed ， Can no longer be opened. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetWDRAttr(IMPISPTuningOpsMode *pmode)
 *
 * Obtain ISP Current state of the wide dynamic module 
 *
 * @param[in] pmode Wide dynamic module parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Obtain the correction parameters of the wide dynamic module. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetWDRAttr(IMPISPTuningOpsMode *pmode);

/**
 * ISP Comprehensive extension function ， Scene mode selection. 
 */
typedef enum {
	IMPISP_SCENE_MODE_AUTO = 0,					/**< Automatic mode */
	IMPISP_SCENE_MODE_BEACH_SNOW = 2,				/**< Beach snow scene mode */
	IMPISP_SCENE_MODE_CANDLE_LIGHT = 3,				/**< Candle light mode */
	IMPISP_SCENE_MODE_DAWN_DUSK = 4,				/**< Evening mode */
	IMPISP_SCENE_MODE_FALL_COLORS = 5,				/**< Autumn scene mode */
	IMPISP_SCENE_MODE_FIREWORKS = 6,				/**< Fireworks scene mode */
	IMPISP_SCENE_MODE_LANDSCAPE = 7,				/**< Landscape mode */
	IMPISP_SCENE_MODE_NIGHT = 8,					/**< Night mode */
	IMPISP_SCENE_MODE_PARTY_INDOOR = 9,				/**< Indoor party mode */
	IMPISP_SCENE_MODE_SPORTS = 11,					/**< Sport mode */
	IMPISP_SCENE_MODE_SUNSET = 12,					/**< Sunset mode */
	IMPISP_SCENE_MODE_TEXT = 13,					/**< Text mode */
	IMPISP_SCENE_MODE_NIGHT_PORTRAIT = 14,				/**< Night portrait mode */
} IMPISPSceneMode;

/**
 * @fn int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode)
 *
 * Set up ISP Comprehensive effect scene mode 
 *
 * @param[in] mode Effect scene mode parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetSceneMode(IMPISPSceneMode *pmode)
 *
 * Obtain ISP Comprehensive effect scene mode 
 *
 * @param[in] pmode Effect scene mode parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetSceneMode(IMPISPSceneMode *pmode);

/**
 * ISP Comprehensive extension function ， Color mode selection. 
 */
typedef enum {
	IMPISP_COLORFX_MODE_AUTO = 0,				/**< Automatic mode */
	IMPISP_COLORFX_MODE_BW = 1,				/**< Black and white mode */
	IMPISP_COLORFX_MODE_SEPIA = 2,				/**< Sepia mode */
	IMPISP_COLORFX_MODE_NEGATIVE = 3,			/**< Reverse color mode */
	IMPISP_COLORFX_MODE_VIVID = 9,				/**< Vivid mode */
} IMPISPColorfxMode;

/**
 * @fn int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode)
 *
 * Set up ISP Multi-effect color mode 
 *
 * @param[in] mode Color mode parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetColorfxMode(IMPISPColorfxMode *pmode)
 *
 * Obtain ISP Multi-effect color mode 
 *
 * @param[in] pmode Color mode parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetColorfxMode(IMPISPColorfxMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetBrightness(unsigned char bright)
 *
 * Set up ISP Comprehensive effect picture brightness 
 *
 * @param[in] bright Picture brightness parameter 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark The default value is 128， more than the 128 Increase brightness ， Less than 128 Decrease the brightness. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetBrightness(unsigned char bright);

/**
 * @fn int IMP_ISP_Tuning_GetBrightness(unsigned char *pbright)
 *
 * Obtain ISP Comprehensive effect picture brightness 
 *
 * @param[in] bright Picture brightness parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark The default value is 128， more than the 128 Increase brightness ， Less than 128 Decrease the brightness. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetBrightness(unsigned char *pbright);

/**
 * @fn int IMP_ISP_Tuning_SetContrast(unsigned char contrast)
 *
 * Set up ISP Comprehensive effect picture contrast 
 *
 * @param[in] contrast Picture contrast parameter 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark The default value is 128， more than the 128 Increase contrast ， Less than 128 Reduce the contrast. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetContrast(unsigned char contrast);

/**
 * @fn int IMP_ISP_Tuning_GetContrast(unsigned char *pcontrast)
 *
 * Obtain ISP Comprehensive effect picture contrast 
 *
 * @param[in] contrast Picture contrast parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark The default value is 128， more than the 128 Increase contrast ， Less than 128 Reduce the contrast. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetContrast(unsigned char *pcontrast);

 /**
 * @fn int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness)
 *
 * Set up ISP Comprehensive effect picture sharpness 
 *
 * @param[in] sharpness Picture sharpness parameter value 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark The default value is 128， more than the 128 Increase sharpness ， Less than 128 Reduce sharpness. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness);

/**
 * @fn int IMP_ISP_Tuning_GetSharpness(unsigned char *psharpness)
 *
 * Obtain ISP Comprehensive effect picture sharpness 
 *
 * @param[in] sharpness Picture sharpness parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark The default value is 128， more than the 128 Increase sharpness ， Less than 128 Reduce sharpness. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetSharpness(unsigned char *psharpness);

/**
 * @fn int IMP_ISP_Tuning_SetSaturation(unsigned char sat)
 *
 * Set up ISP Comprehensive effect picture saturation 
 *
 * @param[in] sat Picture saturation parameter value 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark The default value is 128， more than the 128 Increase saturation ， Less than 128 Decrease saturation. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetSaturation(unsigned char sat);

/**
 * @fn int IMP_ISP_Tuning_GetSaturation(unsigned char *psat)
 *
 * Obtain ISP Comprehensive effect picture saturation 
 *
 * @param[in] sat Picture saturation parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark The default value is 128， more than the 128 Increase saturation ， Less than 128 Decrease saturation. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetSaturation(unsigned char *psat);
#if 0
/**
 * @fn int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode)
 *
 * bypass ISP Module handling ， Direct output sensor image 
 *
 * @param[in] mode Whether to bypass ISP Module processing parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark If the function is enabled ，sensor The output image will not go through ISP Any processing of the module ， Direct output. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode);
#endif
/**
 * @fn int IMP_ISP_Tuning_SetFWFreeze(IMPISPTuningOpsMode mode)
 *
 * freeze ISP Firmware operation ， Enable means freeze ISP firmware ， this is ISP The automatic algorithm will stop; if not enabled, it means ISP The firmware works normally. 
 *
 * @param[in] mode Is it frozen ISP Firmware parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetFWFreeze(IMPISPTuningOpsMode mode);


/**
 * @fn int IMP_ISP_Tuning_SaveAllParam(char *path)
 *
 * save ISP All debugging parameters of the module 
 *
 * @param[in] path Path parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Save all debugging ISP parameter. 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SaveAllParam(char *path);

/**
 * @fn int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable)
 *
 * ISP Whether the module bypass
 *
 * @param[in] enable whether bypass Output mode 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no 
 *
 * @attention Before using this function ， Must guarantee ISP Module is closed .
 */
int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable);

/**
 * @fn int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain)
 *
 * Obtain ISP The overall gain value of the output image 
 *
 * @param[in] gain Get the pointer of the gain value parameter , The data storage format is [24.8]， high 24bit Is an integer ， low 8bit Is a decimal. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee IMP_ISP_EnableSensor with IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);

/**
 * Set up ISP Whether the image mirror effect function is enabled 
 *
 * @fn int IMP_ISP_Tuning_SetISPHflip(IMPISPTuningOpsMode mode)
 *
 * @param[in] mode Whether to enable mirror effect 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetISPHflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPHflip(IMPISPTuningOpsMode *pmode)
 *
 * Obtain ISP The operating status of the image mirror effect function 
 *
 * @param[in] pmode Operation parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetISPHflip(IMPISPTuningOpsMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode)
 *
 * Set up ISP Whether the image upside down effect function is enabled 
 *
 * @param[in] mode Whether to enable the image up and down reverse 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPVflip(IMPISPTuningOpsMode *pmode)
 *
 * Obtain ISP The operating status of the image upside down effect function 
 *
 * @param[in] pmode Operation parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetISPVflip(IMPISPTuningOpsMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetISPHVflip(IMPISPTuningOpsMode hmode, IMPISPTuningOpsMode vmode)
 *
 * Set up ISP image H/V Whether the reversal effect function is enabled 
 *
 * @param[in] hmode Whether to enable image H Reverse 
 * @param[in] vmode Whether to enable image V Reverse 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetISPHVflip(IMPISPTuningOpsMode hmode, IMPISPTuningOpsMode vmode);

/**
 * @fn int IMP_ISP_Tuning_GetISPHVflip(IMPISPTuningOpsMode *phmode, IMPISPTuningOpsMode *pvmode)
 *
 * Obtain ISP image H/V The operating status of the reverse effect function 
 *
 * @param[in] phmode Operation parameter pointer 
 * @param[in] pvmode Operation parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetISPHVflip(IMPISPTuningOpsMode *phmode, IMPISPTuningOpsMode *pvmode);

/**
 * ISP Working mode configuration ， Normal mode or night vision mode. 
 */
typedef enum {
	IMPISP_RUNNING_MODE_DAY = 0,				/**< Normal mode */
	IMPISP_RUNNING_MODE_NIGHT = 1,				/**< Night vision mode */
	IMPISP_RUNNING_MODE_BUTT,					/**< Max */
} IMPISPRunningMode;

/**
 * @fn int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode)
 *
 * Set up ISP Operating mode ， Normal mode or night vision mode; the default is normal mode. 
 *
 * @param[in] mode Operating mode parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * Example: 
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
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode)
 *
 * Obtain ISP Operating mode ， Normal mode or night vision mode. 
 *
 * @param[in] pmode Operation parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode);

/**
 * ISP Automatic exposure strategy configuration ， Normal mode or exposure priority mode. 
 **/
typedef enum {
	IMPISP_AE_STRATEGY_SPLIT_BALANCED = 0, /**< Normal mode */
	IMPISP_AE_STRATEGY_SPLIT_INTEGRATION_PRIORITY = 1, /**< Exposure priority mode */
	IMPISP_AE_STRATEGY_BUTT, /**< Max */
} IMPISPAeStrategy;

/**
 * @fn int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy strategy)
 *
 * Set up ISP Operating mode ， Automatic exposure strategy configuration ， Normal mode or exposure priority mode; the default is normal mode. 
 *
 * @param[in] strategy Automatic exposure strategy parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 * Example: 
 * @code
 * IMPISPAeStrategy strategy;
 *
 * if( it is a normal scence){
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
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy strategy);

/**
* @fn int IMP_ISP_Tuning_GetAeStrategy(IMPISPAeStrategy *pstrategy)
*
* Obtain ISP Automatic exposure strategy configuration ， Normal mode or exposure priority mode. 
* @param[in] pstrategy Automatic exposure strategy parameter pointer 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_GetAeStrategy(IMPISPAeStrategy *pstrategy);

/**
 * gamma
 */
typedef struct {
	uint16_t gamma[129];		/**< gamma Parameter array ， Have 129 Points */
} IMPISPGamma;

/**
* @fn int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma)
*
* Set up GAMMA parameter .
* @param[in] gamma gamma parameter 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma)
*
* Obtain GAMMA parameter .
* @param[out] gamma gamma parameter 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_SetAeComp(int comp)
*
* Set up AE make up. AE Compensation parameters can adjust the image AE target， The recommended setting range is [90-150].
* @param[in] comp AE Compensation parameter 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_SetAeComp(int comp);

/**
* @fn int IMP_ISP_Tuning_GetAeComp(int *comp)
*
* Obtain AE make up. 
* @param[out] comp AE Compensation parameter 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_GetAeComp(int *comp);

/**
 * Exposure mode 
 */
enum isp_core_expr_mode {
	ISP_CORE_EXPR_MODE_AUTO,			/**< Automatic mode */
	ISP_CORE_EXPR_MODE_MANUAL,			/**< Manual mode */
};

/**
 * Exposure unit 
 */
enum isp_core_expr_unit {
	ISP_CORE_EXPR_UNIT_LINE,			/**< Row */
	ISP_CORE_EXPR_UNIT_US,				/**< millisecond */
};

/**
 * Exposure parameters 
 */
typedef union isp_core_expr_attr{
	struct {
		enum isp_core_expr_mode mode;		/**< Set exposure mode */
		enum isp_core_expr_unit unit;		/**< Set exposure unit */
		uint16_t time;
	} s_attr;
	struct {
		enum isp_core_expr_mode mode;			/**< Acquired exposure mode */
		uint16_t integration_time;		/**< Exposure time ， Unit is line */
		uint16_t integration_time_min;	/**< Minimum exposure time obtained ， Unit is line */
		uint16_t integration_time_max;	/**< Maximum exposure time obtained ， Unit is line */
		uint16_t one_line_expr_in_us;		/**< The number of microseconds corresponding to the exposure time of the acquired line */
	} g_attr;
}IMPISPExpr;


/**
 * @fn int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr)
 *
 * Set up AE parameter. 
 *
 * @param[in] expr AE parameter. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr);

/**
 * @fn int IMP_ISP_Tuning_GetExpr(IMPISPExpr *expr)
 *
 * Obtain AE parameter. 
 *
 * @param[out] expr AE parameter. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetExpr(IMPISPExpr *expr);

/**
 * Exposure statistics area selection 
 */
typedef union isp_core_ae_roi_select{
	struct {
		unsigned endy :8; /**< End point y coordinate (0 ~ 255)*/
		unsigned endx :8; /**< End point x coordinate (0 ~ 255)*/
		unsigned starty :8; /**< Starting point y coordinate (0 ~ 255)*/
		unsigned startx :8; /**< Starting point x coordinate (0 ~ 255)*/
	};
	uint32_t value;
} IMPISPAERoi;

/**
 * @fn int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi)
 *
 * Obtain AE Statistics area. 
 *
 * @param[out] isp_ae_roi AE Rectangular statistical area parameters. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);

/**
 * @fn int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi)
 *
 * Set up AE Statistics area. 
 *
 * @param[in] isp_ae_roi AE Rectangular statistical area parameters. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);

/**
 * White balance mode 
 */
enum isp_core_wb_mode {
	ISP_CORE_WB_MODE_AUTO = 0,			/**< Automatic mode */
	ISP_CORE_WB_MODE_MANUAL,			/**< Manual mode */
	ISP_CORE_WB_MODE_DAY_LIGHT,			/**< sunny day */
	ISP_CORE_WB_MODE_CLOUDY,			/**< cloudy day */
	ISP_CORE_WB_MODE_INCANDESCENT,		/**< Incandescent lamp */
	ISP_CORE_WB_MODE_FLOURESCENT,		/**< Fluorescent lamp */
	ISP_CORE_WB_MODE_TWILIGHT,			/**< dusk */
	ISP_CORE_WB_MODE_SHADE,				/**< shadow */
	ISP_CORE_WB_MODE_WARM_FLOURESCENT,	/**< Warm fluorescent lamp */
};

/**
 * White balance parameters 
 */
typedef struct isp_core_wb_attr{
	enum isp_core_wb_mode mode;		/**< White balance mode ， Divided into automatic and manual modes */
	uint16_t rgain;			/**< Red gain ， Effective in manual mode */
	uint16_t bgain;			/**< Blue gain ， Effective in manual mode */
}IMPISPWB;

/**
 * @fn int IMP_ISP_Tuning_SetWB(IMPISPWB *wb)
 *
 * Set the white balance function settings. ， Manual mode is mainly set by rgain [[[ bgain achieve. 
 *
 * @param[in] wb Set the white balance parameters. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_GetWB(IMPISPWB *wb)
 *
 * Get the white balance function setting. 
 *
 * @param[out] wb The obtained white balance parameters. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetWB(IMPISPWB *wb);

/**
 * @fn IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb)
 *
 * Obtain white balance statistics. 
 *
 * @param[out] wb The obtained white balance statistics. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB* isp_wb_attr)
 *
 * Obtain ISP in AWB of CWF The position of the light source 
 *
 * @param[out] isp_wb_attr CWF Light source position coordinates 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);

/**
 * @fn int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr)
 *
 * Set up ISP in AWB of CWF The position of the light source 
 *
 * @param[in] isp_wb_attr CWF Light source position coordinates 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 * Example: 
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
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);

/**
 * @fn int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain)
 *
 * Set up sensor You can set the maximum Again . 
 *
 * @param[in] gain sensor The maximum that can be set again.0 Means 1x，32 Means 2x， And so on. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */

typedef struct isp_core_rgb_coefft_wb_attr {
		unsigned short rgb_coefft_wb_r;
		unsigned short rgb_coefft_wb_g;
		unsigned short rgb_coefft_wb_b;

}IMPISPCOEFFTWB;
/**
 * @fn IMP_ISP_Tuning_Awb_GetRgbCoefft(IMPISPCOEFFTWB *isp_core_rgb_coefft_wb_attr)
 *
 * Obtain sensor AWB RGB Channel offset parameter. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_Awb_GetRgbCoefft(IMPISPCOEFFTWB *isp_core_rgb_coefft_wb_attr);
/**
 * @fn IMP_ISP_Tuning_Awb_SetRgbCoefft(IMPISPCOEFFTWB *isp_core_rgb_coefft_wb_attr)
 *
 * Set up sensor Can be set AWB RGB Channel offset parameter. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 *
 * Example: 
 * @code
 * IMPISPCOEFFTWB isp_core_rgb_coefft_wb_attr;
 *
 *isp_core_rgb_coefft_wb_attr.rgb_coefft_wb_r=x;
 *isp_core_rgb_coefft_wb_attr.rgb_coefft_wb_g=y;
 *isp_core_rgb_coefft_wb_attr.rgb_coefft_wb_b=z;
 *IMP_ISP_Tuning_Awb_SetRgbCoefft(&isp_core_rgb_coefft_wb_attr);
 if(ret){
 IMP_LOG_ERR(TAG, "IMP_ISP_Tuning_Awb_SetRgbCoefft error !\n");
 return -1;
 }
*/
int IMP_ISP_Tuning_Awb_SetRgbCoefft(IMPISPCOEFFTWB *isp_core_rgb_coefft_wb_attr);

int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);

/**
 * @fn int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain)
 *
 * Obtain sensor You can set the maximum Again . 
 *
 * @param[out] gain sensor The maximum that can be set again.0 Means 1x，32 Means 2x， And so on. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain)
 *
 * Set up ISP The maximum that can be set Dgain . 
 *
 * @param[in] ISP Dgain The maximum that can be set dgain.0 Means 1x，32 Means 2x， And so on. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain);

/**
 * @fn int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain)
 *
 * Obtain ISP Set maximum Dgain . 
 *
 * @param[out] ISP Dgain Can get the largest set dgain.0 Means 1x，32 Means 2x， And so on. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void))
 *
 * Set the video loss function. sensor When there is a problem with the connection line to the motherboard ， The set callback function will be executed. 
 *
 * @param[in] cb Callback. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void));

/**
 * @fn int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength)
 *
 * Set the intensity of strong light suppression. 
 *
 * @param[in] strength Strong light suppression intensity parameter . The value range is [ 0-10], 0 Indicates that the function is turned off. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength);

/**
 * @fn int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio)
 *
 * Set up 3D Noise reduction intensity. 
 *
 * @param[in] ratio Intensity adjustment ratio . If set to 90 Means set to the default value 90%. The value range is [ 50-150].
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio)
 *
 * Set up 2D Noise reduction intensity. 
 *
 * @param[in] ratio Intensity adjustment ratio . If set to 90 Means set to the default value 90%. The value range is [ 50-150].
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetDPStrength(uint32_t ratio)
 *
 * Set up DPC strength. 
 *
 * @param[in] ratio Intensity adjustment ratio . If set to 90 Means set to the default value 90%. The value range is [ 50-150].
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetDPStrength(uint32_t ratio);

/**
 * ISP ANTIFOG Operating mode. 
 */
typedef enum {
	ANTIFOG_DISABLE,			/**< shut down */
	ANTIFOG_STRONG,				/**< Strong */
	ANTIFOG_MEDIUM,				/**< in */
	ANTIFOG_WEAK,				/**< weak */
}IMPISPAntiFogAttr;

/**
* @fn int IMP_ISP_Tuning_SetAntiFogAttr(IMPISPAntiFogAttr attr)
*
* Set up ANTIFOG Attributes. 
* @param[in] attr ANTIFOG Attribute parameter 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_SetAntiFogAttr(IMPISPAntiFogAttr attr);

/**
 * ISP EV parameter. 
 */
typedef struct {
	uint32_t ev;			/**< Exposure value */
	uint32_t expr_us;		/**< Exposure time */
	uint32_t ev_log2;		/**<log Format exposure time */
	uint32_t again;			/**< Analog gain */
	uint32_t dgain;			/**< Digital gain */
	uint32_t gain_log2;		/**< log Format gain */
}IMPISPEVAttr;

/**
* @fn int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr)
*
* Obtain EV Attributes. 
* @param[out] attr EV Attribute parameter 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);

/**
* @fn int IMP_ISP_Tuning_EnableMovestate(void)
*
* when sensor During exercise ， Set up ISP Enter the state of exercise. 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_EnableMovestate(void);

/**
* @fn int IMP_ISP_Tuning_DisableMovestate(void)
*
* when sensor Return from motion to rest ， Set up ISP Disable the motion state. 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @attention Before using this function ，IMP_ISP_Tuning_EnableMovestate Has been called. 
*/
int IMP_ISP_Tuning_DisableMovestate(void);

/**
* Mode selection options 
*/
typedef enum {
	IMPISP_TUNING_MODE_AUTO, /**< The operation of the module is automatic mode */
	IMPISP_TUNING_MODE_MANUAL, /**< The operation of this module is manual mode */
	IMPISP_TUNING_MODE_RANGE, /**< The operation of this module is the setting range mode */
	IMPISP_TUNING_MODE_BUTT, /**< Used to judge the validity of parameters ， The parameter size must be less than this value */
} IMPISPTuningMode;

/**
* Exposure parameters 
*/
typedef struct {
	IMPISPTuningMode mode; /**< Exposure mode ， Divided into automatic mode, manual mode, and setting range mode */
	uint16_t integration_time; /** Exposure time */
	uint16_t max_integration_time; /**< Maximum exposure time */
} IMPISPITAttr;

/**
 * @fn int IMP_ISP_Tuning_SetIntegrationTime(IMPISPITAttr *itattr)
 *
 * Set up AE parameter. 
 *
 * @param[in] itattr Exposure parameters. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetIntegrationTime(IMPISPITAttr *itattr);

/**
 * @fn int IMP_ISP_Tuning_GetIntegrationTime(IMPISPITAttr *itattr)
 *
 * Get exposure related parameters. 
 *
 * @param[out] itattr Exposure parameters. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetIntegrationTime(IMPISPITAttr *itattr);

/**
* Weight information 
*/
typedef struct {
	unsigned char weight[15][15]; /**< Weight information of each area [0 ~ 15]*/
} IMPISPWeight;

/**
 * @fn int IMP_ISP_Tuning_SetAeWeight(IMPISPWeight *ae_weight)
 *
 * Set up AE The weight of the statistical area. 
 *
 * @param[in] ae_weight Weight information for each area. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetAeWeight(IMPISPWeight *ae_weight);

/**
 * @fn int IMP_ISP_Tuning_GetAeWeight(IMPISPWeight *ae_weight)
 *
 * Obtain AE The weight of the statistical area. 
 *
 * @param[out] ae_weight Weight information for each area. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetAeWeight(IMPISPWeight *ae_weight);

/**
 * @fn int IMP_ISP_Tuning_SetAwbWeight(IMPISPWeight *awb_weight)
 *
 * Set up AWB The weight of the statistical area. 
 *
 * @param[in] awb_weight Weight information for each area. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetAwbWeight(IMPISPWeight *awb_weight);

/**
 * @fn int IMP_ISP_Tuning_GetAwbWeight(IMPISPWeight *awb_weight)
 *
 * Obtain AWB The weight of the statistical area. 
 *
 * @param[out] awb_weight Weight information for each area. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetAwbWeight(IMPISPWeight *awb_weight);

/**
* AE Statistics parameter 
*/
typedef struct {
	unsigned char ae_histhresh[4]; /**< AE Statistical histogram bin boundary [0 ~ 255]*/
	unsigned short ae_hist[5]; /**< AE Statistical histogram bin value [0 ~ 65535]*/
	unsigned char ae_stat_nodeh; /**< Number of effective statistical areas in the horizontal direction [0 ~ 15]*/
	unsigned char ae_stat_nodev; /**< Number of effective statistical areas in the vertical direction [0 ~ 15]*/
} IMPISPAEHist;

/**
 * @fn int IMP_ISP_Tuning_SetAeHist(IMPISPAEHist *ae_hist)
 *
 * Set up AE Statistics related parameters. 
 *
 * @param[in] ae_hist AE Statistics related parameters. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetAeHist(IMPISPAEHist *ae_hist);

/**
 * @fn int IMP_ISP_Tuning_GetAeHist(IMPISPAEHist *ae_hist)
 *
 * Obtain AE Statistics. 
 *
 * @param[out] ae_hist AE Statistics information. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetAeHist(IMPISPAEHist *ae_hist);

typedef struct {
	unsigned short ae_sta_zone[15*15];		/**AE Statistics for each block */
} IMPISPAEZone;

/**
 * @fn int IMP_ISP_Tuning_GetAeZone(IMPISPAEZone *ae_zone)
 *
 * Obtain AE Statistics for each block 
 *
 * @param[out] ae_zone AE The statistical value of each block. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetAeZone(IMPISPAEZone *ae_zone);

/**
* AWB Statistics 
*/
struct isp_core_awb_sta_info{
	unsigned short r_gain; /**< AWB Weighted r/g average value [0 ~ 4095]*/
	unsigned short b_gain; /**< AWB Weighted b/g average value [0 ~ 4095]*/
	unsigned int awb_sum; /**< Used for AWB Counted pixels [0 ~ 4294967295]*/
};
/**
* AWB Statistical mode 
*/
enum isp_core_awb_stats_mode{
	IMPISP_AWB_STATS_LEGACY_MODE = 0, /**< Delay mode */
	IMPISP_AWB_STATS_CURRENT_MODE = 1, /**< Current mode */
	IMPISP_AWB_STATS_MODE_BUTT,
};
/**
* AWB Statistics parameter 
*/
typedef struct {
	struct isp_core_awb_sta_info awb_stat; /**< AWB Statistics */
	enum isp_core_awb_stats_mode awb_stats_mode; /**< AWB Statistical mode */
	unsigned short awb_whitelevel; /**< AWB Upper limit of statistics [0 ~ 1023]*/
	unsigned short awb_blacklevel; /**< AWB Statistical value lower limit [0 ~ 1023]*/
	unsigned short cr_ref_max; /**< AWB Statistical white spot area r/g Max [0 ~ 4095]*/
	unsigned short cr_ref_min; /**< AWB Statistical white spot area r/g Minimum [0 ~ 4095]*/
	unsigned short cb_ref_max; /**< AWB Statistical white spot area b/g Max [0 ~ 4095]*/
	unsigned short cb_ref_min; /**< AWB Statistical white spot area b/g Max [0 ~ 4095]*/
	unsigned char awb_stat_nodeh; /**< Number of effective statistical areas in the horizontal direction [0 ~ 15]*/
	unsigned char awb_stat_nodev; /**< Number of effective statistical areas in the vertical direction [0 ~ 15]*/
} IMPISPAWBHist;

struct isp_core_wb_zone_info{
	unsigned short red_green; 	/**< r_gain*/
	unsigned short blue_green; 	/**< b_gain*/
	unsigned int sum; 			/**< Number of pixels used for statistics */
};

typedef struct {
	struct isp_core_wb_zone_info awb_sta_zone[15][15];		/** AWB Statistics for each block */
} IMPISPAWBZone;

/**
 * @fn int int IMP_ISP_Tuning_GetAwbZone(IMPISPAWBZone *awb_zone)
 *
 * Obtain AWB The statistical value of each block. 
 *
 * @param[out] awb_zone AWB Statistics for each block 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetAwbZone(IMPISPAWBZone *awb_zone);

/**
 * @fn int IMP_ISP_Tuning_GetAwbHist(IMPISPAWBHist *awb_hist)
 *
 * Obtain AWB Statistics. 
 *
 * @param[out] awb_hist AWB Statistics information. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetAwbHist(IMPISPAWBHist *awb_hist);

/**
 * @fn int IMP_ISP_Tuning_SetAwbHist(IMPISPAWBHist *awb_hist)
 *
 * Set up AWB Statistics related parameters. 
 *
 * @param[in] awb_hist AWB Statistics related parameters. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetAwbHist(IMPISPAWBHist *awb_hist);

/**
* AF Statistics 
*/
struct isp_core_af_sta_info{
	unsigned short af_metrics;/**< AF Main statistic [0 ~ 65535]*/
	unsigned short af_metrics_alt;/**< AWB Sub-statistics [0 ~ 65535]*/
	unsigned short af_thresh_read;/**< AF Main statistic threshold [0 ~ 65535]*/
	unsigned short af_intensity_read;/**< AF Statistic value [0 ~ 65535]*/
	unsigned short af_intensity_zone;/**< AF Statistical value lightness area value [0 ~ 65535]*/
	unsigned int af_total_pixels;/**< Used for AF Counted pixels [0 ~ 4294967295]*/
	unsigned int af_counted_pixels;/**< Used for AF Cumulative value of counted pixels [0 ~ 4294967295]*/
};
/**
* AF Statistics parameter 
*/
typedef struct {
	struct isp_core_af_sta_info af_stat; /**< AF Main statistics information */
	unsigned char af_metrics_shift; /**< AF Main statistic value reduction parameter [0 ~ 15]*/
	unsigned short af_thresh; /**< AF Main statistic threshold [0 ~ 65535]*/
	unsigned short af_thresh_alt; /**< AF Secondary statistic threshold [0 ~ 65535]*/
	unsigned char af_stat_nodeh; /**< Number of effective statistical areas in the horizontal direction [0 ~ 15]*/
	unsigned char af_stat_nodev; /**< Number of effective statistical areas in the vertical direction [0 · 15]*/
	unsigned char af_np_offset; /**< AF Statistical noise feature shift [0 ~ 255]*/
	unsigned char af_intensity_mode; /**< AF Lightness Standardization Mode [0 ~ 7]*/
	unsigned char af_skipx; /**< horizontal direction AF Jump statistics [0 ~ 5]*/
	unsigned char af_offsetx; /**< horizontal direction AF Offset statistics [0 ~ 1]*/
	unsigned char af_skipy; /**< Vertical direction AF Jump statistics [0 ~ 6]*/
	unsigned char af_offsety; /**< Vertical direction AF Offset statistics [0 ~ 1]*/
	unsigned char af_scale_top; /**< Bottom half of reduced parameters [0 ~ 4]*/
	unsigned char af_scale_bottom; /**< Top half reduction parameters [0 ~ 4]*/
} IMPISPAFHist;

/**
 * @fn int IMP_ISP_Tuning_GetAfHist(IMPISPAFHist *af_hist);
 *
 * Obtain AF Statistics. 
 *
 * @param[out] af_hist AF Statistics information. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetAfHist(IMPISPAFHist *af_hist);

/**
 * @fn int IMP_ISP_Tuning_SetAfHist(IMPISPAFHist *af_hist)
 *
 * Set up AF Statistics related parameters. 
 *
 * @param[in] af_hist AF Statistics related parameters. 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetAfHist(IMPISPAFHist *af_hist);

/**
 * ISP Wait Frame parameter. 
 */
typedef struct {
	uint32_t timeout;		/**< overtime time ， unit ms */
	uint64_t cnt;			/**< Frame statistics */
}IMPISPWaitFrameAttr;

/**
* @fn int IMP_ISP_Tuning_WaitFrame(IMPISPWaitFrameAttr *attr)
* Wait for the end of the frame 
*
* @param[out] attr Wait for the end of frame attribute 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_WaitFrame(IMPISPWaitFrameAttr *attr);

typedef enum {
	IMPISP_SHAD_SCALE_L,		/**< Mesh Shading Zoom factor 0 */
	IMPISP_SHAD_SCALE_M,		/**< Mesh Shading Zoom factor 1 */
	IMPISP_SHAD_SCALE_H,		/**< Mesh Shading Zoom factor 2 */
	IMPISP_SHAD_SCALE_U,		/**< Mesh Shading Zoom factor 3 */
} IMPISPMeshShadingScale;

/**
* @fn int IMP_ISP_Tuning_SetMeshShadingScale(IMPISPMeshShadingScale scale)
* Set up Mesh Shading Zoom factor 
*
* @param[out] scale Mesh Shading Zoom factor 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_SetMeshShadingScale(IMPISPMeshShadingScale scale);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

/**
 * @}
 */

#endif /* __IMP_ISP_H__ */
