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
 * ISP Fichier d'en-tête du module 
 */

/**
 * @defgroup IMP_ISP
 * @ingroup lutin
 * @brief Unité de traitement du signal d'image. 
 *
 * ISP Le module n'a rien à voir avec le flux de données ， Pas besoin de continuer Bind， S'applique uniquement aux réglages des paramètres d'effet et Sensor contrôler. 
 *
 * ISP Les étapes d'activation du module sont les suivantes: 
 * @code 
 * int ret = 0;
 * ret = IMP_ISP_Open(); // step.1 créer ISP Module 
 * if(ret < 0){
 * printf("Failed to ISPInit\n");
 * return -1;
 * }
 * IMPSensorInfo sensor;
 * sensor.name = "xxx";
 * sensor.cbus_type = SENSOR_CONTROL_INTERFACE_I2C; // OR SENSOR_CONTROL_INTERFACE_SPI
 * sensor.i2c = {
 * 	.type = "xxx", // I2C Nom de l'appareil ， Doit et sensor Conduite struct i2c_device_id milieu name Unanime. 
 *	.addr = xx,	//I2C adresse 
 *	.i2c_adapter_id = xx, //sensor L'existant I2C Manette ID
 * }
 * OR
 * sensor.spi = {
 *	.modalias = "xx", //SPI Device name ， Must and sensor Driving struct spi_device_id middle name Unanimous. 
 *	.bus_num = xx, //SPI Adresse de bus 
 * }
 * ret = IMP_ISP_AddSensor(&sensor); //step.2 ajoute un sensor， Avant cette opération sensor Le pilote a été ajouté au noyau. 
 * if (ret < 0) {
 * printf("Failed to Register sensor\n");
 * return -1;
 * }
 *
 * ret = IMP_ISP_EnableSensor(void); //step.3 Permettre sensor， à l'heure actuelle sensor Démarrez la sortie des images. 
 * if (ret < 0) {
 * printf("Failed to EnableSensor\n");
 * return -1;
 * }
 *
 * ret = IMP_ISP_EnableTuning(); //step.4 Enable ISP tuning, Avant d'appeler ISP Interface de débogage. 
 * if (ret < 0) {
 * printf("Failed to EnableTuning\n");
 * return -1;
 * }
 *
 * Pour l'interface de débogage, veuillez vous référer à ISP Documentation de l'interface de débogage. //step.5 Débogage des effets. 
 *
 * @endcode 
 * ISP Les étapes de désinstallation du module sont les suivantes: 
 * @code 
 * int ret = 0;
 * IMPSensorInfo sensor;
 * sensor.name = "xxx";
 * ret = IMP_ISP_DisableTuning(); //step.1 fermer ISP tuning
 * if (ret < 0) {
 * printf("Failed to disable tuning\n");
 * return -1;
 * }
 *
 * ret = IMP_ISP_DisableSensor(); //step.2 shut down sensor， right now sensor Arrêter la sortie des images; avant cette opération FrameSource Tout doit être fermé. 
 * if (ret < 0) {
 * printf("Failed to disable sensor\n");
 * return -1;
 * }
 *
 * ret = IMP_ISP_DelSensor(&sensor); //step.3 effacer sensor， Avant cette opération sensor Doit être fermé. 
 * if (ret < 0) {
 * printf("Failed to disable sensor\n");
 * return -1;
 * }
 *
 * ret = IMP_ISP_Close(); //step.4 Nettoyer ISP Module ， Tout avant cette opération sensor Doit être supprimé. 
 * if (ret < 0) {
 * printf("Failed to disable sensor\n");
 * return -1;
 * }
 * @endcode 
 * Pour plus de méthodes d'utilisation, veuillez vous référer à Samples
 * @{
 */

/**
* Énumération des types de bus de contrôle de caméra 
*/
typedef enum {
	TX_SENSOR_CONTROL_INTERFACE_I2C = 1,	/**< I2C Bus de contrôle */
	TX_SENSOR_CONTROL_INTERFACE_SPI,	/**< SPI Control bus */
} IMPSensorControlBusType;

/**
* Le type de bus de contrôle de la caméra est I2C Temps ， Structure des paramètres à configurer 
*/
typedef struct {
	char type[20];		/**< I2C Device name ， Doit être conduit avec la caméra struct i2c_device_id dans name Les variables sont cohérentes */
	int addr;		/**< I2C address */
	int i2c_adapter_id;	/**< I2C Controller */
} IMPI2CInfo;
/**
* The type of camera control bus is SPI Time ， The parameter structure that needs to be configured 
*/
typedef struct {
	char modalias[32];	/**< SPI Device name ， Must be driven with the camera struct spi_device_id in name Variables are consistent */
	int bus_num;		/**< SPI Bus address */
} IMPSPIInfo;

/**
* Structure des informations d'enregistrement de la caméra 
*/
typedef struct {
	char name[32];					/**< Nom de la caméra */
	IMPSensorControlBusType cbus_type;	/**< Type de bus de contrôle de caméra */
	union {
		IMPI2CInfo i2c;				/**< I2C Informations sur le bus */
		IMPSPIInfo spi;				/**< SPI Bus information */
	};
	unsigned short rst_gpio;		/**< webcam reset Lien d'interface GPIO， Remarque: ce paramètre n'est pas activé maintenant */
	unsigned short pwdn_gpio;		/**< webcam power down Interface link GPIO， Note: this parameter is not enabled now */
	unsigned short power_gpio;		/**< webcam power Interface link GPIO， Note: this parameter is not enabled now */
} IMPSensorInfo;

/**
 * @fn int IMP_ISP_Open (vide)
 *
 * allumer ISP Module 
 *
 * @param non
 *
 * @retval 0 succès
 * @retval Échec différent de zéro, retour du code d'erreur
 *
 * @remark Créez un module ISP, préparez-vous à ajouter un capteur au FAI et activez la fonction de débogage d'effet ISP.
 *
 * @attention Cette fonction doit être appelée avant d'ajouter le capteur.
 */
int IMP_ISP_Open(void);

/**
 * @fn int IMP_ISP_Close (vide)
 *
 * shut down ISP Module 
 *
 * @param no 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Module ISP, le module ISP ne fonctionne plus.
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que toutes les fonctions de débogage FrameSource et d'effets ont été fermées et que tous les capteurs ont été désinstallés.
 */
int IMP_ISP_Close(void);

/**
 * @fn int IMP_ISP_AddSensor (IMPSensorInfo * pinfo)
 *
 * add one sensor， Habitué ISP Le module fournit la source de données 
 *
 * @param[in] pinfo Besoin d'ajouter un pointeur d'informations sur le capteur
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Ajoutez une caméra pour fournir des images.
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que le pilote de l'appareil photo a été enregistré dans le noyau.
 */
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);

/**
 * @fn int IMP_ISP_DelSensor (IMPSensorInfo * pinfo)
 *
 * Supprimer un sensor
 *
 * @param[in] pinfo doit supprimer le pointeur d'information du capteur
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Supprimer une caméra.
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que la caméra a cessé de fonctionner, c'est-à-dire que la fonction IMP_ISP_DisableSensor est appelée.
 */
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);

/**
 * @fn int IMP_ISP_EnableSensor (void)
 *
 * Activer un sensor
 *
 * @param no 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Permettez à une caméra de commencer à transmettre des images, afin que FrameSource puisse produire des images et que le FAI puisse effectuer le débogage des effets.
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que la caméra a été ajoutée au module ISP.
 */
int IMP_ISP_EnableSensor(void);

/**
 * @fn int IMP_ISP_DisableSensor (void)
 *
 * Désactiver un sensor
 *
 * @param no 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark N'activez pas une caméra pour arrêter la transmission d'image, FrameSource ne peut donc pas produire d'images et le FAI ne peut pas effectuer le débogage des effets.
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que toutes les FrameSources ont arrêté de sortir des images et que le débogage d'effet est également à l'état désactivé.
 */
int IMP_ISP_DisableSensor(void);

/**
 * @fn int IMP_ISP_SetSensorRegister (uint32_t reg, valeur uint32_t)
 *
 * Installation sensor La valeur d'un registre 
 *
 * @param[in] adresse de registre d'enregistrement
 *
 * @param[in] valeur du registre valeur
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Vous pouvez régler directement la valeur d'un registre de capteur.
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que la caméra a été activée.
 */
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value);

/**
 * @fn int IMP_ISP_GetSensorRegister (uint32_t reg, uint32_t * valeur)
 *
 * Obtenir sensor The value of a register 
 *
 * @param[in] reg Register address 
 *
 * @param[in] pointeur de valeur pour enregistrer la valeur
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Vous pouvez obtenir directement la valeur d'un registre de capteur.
 *
 * @attention Before using this function ， It must be ensured that the camera has been enabled .
 */
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *value);

typedef enum {
	IMPISP_TUNING_OPS_MODE_DISABLE,			/**< Désactiver la fonction du module */
	IMPISP_TUNING_OPS_MODE_ENABLE,			/**< Activer la fonction du module */
	IMPISP_TUNING_OPS_MODE_BUTT,			/**< Utilisé pour juger de la validité des paramètres ， La taille du paramètre doit être inférieure à cette valeur */
} IMPISPTuningOpsMode;

typedef enum {
	IMPISP_TUNING_OPS_TYPE_AUTO,			/**< Le fonctionnement du module est en mode automatique */
	IMPISP_TUNING_OPS_TYPE_MANUAL,			/**< Le fonctionnement de ce module est en mode manuel */
	IMPISP_TUNING_OPS_TYPE_BUTT,			/**< Used to judge the validity of parameters ， The parameter size must be less than this value */
} IMPISPTuningOpsType;

/**
 * @fn int IMP_ISP_EnableTuning (void)
 *
 * Enable ISP Fonction de débogage d'effet 
 *
 * @param no 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que IMP_ISP_EnableSensor est exécuté et renvoie correctement.
 */
int IMP_ISP_EnableTuning(void);

/**
 * @fn int IMP_ISP_DisableTuning (void)
 *
 * Désactiver ISP Effect debugging function 
 *
 * @param no 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que le débogage d'effet ISP n'est pas activé (c'est-à-dire que cette fonction est appelée) avant que le capteur ne soit désactivé.
 */
int IMP_ISP_DisableTuning(void);

/**
 * @fn int IMP_ISP_Tuning_SetSensorFPS (uint32_t fps_num, uint32_t fps_den)
 *
 * Définir la fréquence d'images de sortie de la caméra 
 *
 * @param[in] fps_num définit le paramètre numérateur de la fréquence d'images
 * @param[in] fps_den définit le paramètre dénominateur de la fréquence d'images
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que IMP_ISP_EnableSensor et IMP_ISP_EnableTuning ont été appelés.
 */
int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);

/**
 * @fn int IMP_ISP_Tuning_GetSensorFPS (uint32_t * fps_num, uint32_t * fps_den)
 *
 * Obtenez la fréquence d'images de sortie de la caméra 
 *
 * @param[in] fps_num Récupère le pointeur du paramètre du numérateur de la fréquence d'images
 * @param[in] fps_den Récupère le pointeur du paramètre du dénominateur de fréquence d'images
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee IMP_ISP_EnableSensor with IMP_ISP_EnableTuning Has been called. 
 * @attention Cette fonction doit être appelée pour obtenir la fréquence d'images par défaut de la caméra avant que le canal d'image ne soit activé pour démarrer la transmission des données.
 */
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);

/**
 * ISP Structure des paramètres de propriété anti-scintillement. 
 */
typedef enum {
	IMPISP_ANTIFLICKER_DISABLE,	/**< Disable ISP Fonction anti-flash */
	IMPISP_ANTIFLICKER_50HZ,	/**< Enable ISP Anti-flash function , Et réglez la fréquence sur 50HZ */
	IMPISP_ANTIFLICKER_60HZ,	/**< Enable ISP Anti-flash function ， And set the frequency to 60HZ */
	IMPISP_ANTIFLICKER_BUTT,	/**< Used to judge the validity of parameters ， The parameter size must be less than this value */
} IMPISPAntiflickerAttr;

/**
 * @fn int IMP_ISP_Tuning_SetAntiFlickerAttr (IMPISPAntiflickerAttr attr)
 *
 * Set up ISP Propriétés anti-flash 
 *
 * @param[in] attr définir la valeur du paramètre
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que la fonction de débogage d'effet ISP a été activée.
 */
int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);

/**
 * @fn int IMP_ISP_Tuning_GetAntiFlickerAttr (IMPISPAntiflickerAttr * pattr)
 *
 * obtenir ISP Anti-flash properties 
 *
 * @param[in] pattr Récupère le pointeur de valeur de paramètre
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);

/**
 * ISP Mode de fonctionnement du module de compression de plage dynamique. 
 */
typedef enum {
	IMPISP_DRC_MANUAL,				/**< ISP Mode manuel du module de compression de plage dynamique */
	IMPISP_DRC_UNLIMIT,				/**< ISP Mode de compression le plus élevé du module de compression de plage dynamique */
	IMPISP_DRC_HIGH,				/**< ISP Mode de compression élevée du module de compression de plage dynamique */
	IMPISP_DRC_MEDIUM,				/**< ISP Mode de compression dans le module de compression de plage dynamique */
	IMPISP_DRC_LOW,					/**< ISP Mode de compression basse du module de compression de plage dynamique */
	IMPISP_DRC_DISABLE,				/**< ISP Le module de compression de plage dynamique n'est pas activé */
} IMPISPDrcMode;

/**
 * ISP Paramètres d'attribut du module de compression de plage dynamique. 
 */
typedef struct {
	IMPISPDrcMode mode;				/**< ISP Sélection du mode de fonctionnement du module de compression de plage dynamique */
	unsigned char drc_strength;			/**< Valeur cible définie en mode manuel ， La plage de valeurs est [0, 0xff] */
	unsigned char slop_max;				/**< Paramètres de contrôle de la force ， The value range is [0, oxff] */
	unsigned char slop_min;				/**< Strength control parameters ， The value range is [0, oxff] */
	unsigned short black_level;			/**< DRC Valeur de pixel minimale améliorée ， The value range is [0, oxfff] */
	unsigned short white_level;			/**< DRC Valeur de pixel maximale améliorée ， The value range is [0, oxfff] */
} IMPISPDrcAttr;

/**
 * @fn int IMP_ISP_Tuning_SetRawDRC (IMPISPDrcAttr * pinfo)
 *
 * Set up ISP RAW Figure paramètres du module de compression de plage dynamique 
 *
 * @param[in] pointeur de paramètre de plage dynamique pinfo
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Définissez le type d'opération et l'intensité de la compression de la plage dynamique des images RVB RAW, ainsi que les valeurs de pixels maximales et minimales qui doivent être améliorées.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetRawDRC(IMPISPDrcAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetRawDRC (IMPISPDrcAttr * pinfo)
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
 * ISP Paramètres d'attribut du module de réduction du bruit spatial. 
 */
typedef struct {
	IMPISPTuningOpsMode enable;			/**< Activer la fonction de réduction du bruit spatial */
	IMPISPTuningOpsType type;				/**< Type d'opération de la fonction de réduction du bruit spatial ， Automatique ou manuel */
	unsigned char sinter_strength;				/**< Intensité de la réduction du bruit spatial ， Le mode manuel est efficace ， The value range is [0, 0xff] */
} IMPISPSinterDenoiseAttr;

/**
 * ISP Mode de fonctionnement du module de réduction du bruit dans le domaine temporel. 
 */
typedef enum {
	IMPISP_TEMPER_DISABLE,				/**< ISP Le module de réduction du bruit dans le domaine temporel n'est pas activé */
	IMPISP_TEMPER_AUTO,					/**< ISP Mode automatique du module de réduction du bruit dans le domaine temporel */
	IMPISP_TEMPER_MANUAL,				/**< ISP Mode manuel du module de réduction du bruit dans le domaine temporel */
} IMPISPTemperMode;

/**
 * ISP Paramètres d'attribut du module de réduction du bruit dans le domaine temporel. 
 */
typedef struct imp_isp_temper_denoise_attr {
	IMPISPTemperMode type;					/**< Type d'opération de la fonction de réduction du bruit dans le domaine temporel ， Disable ， Automatic or manual */
	unsigned char temper_strength;				/**< Intensité de la réduction du bruit dans le domaine temporel ， Manual mode is effective ， The value range is [0, 0xff] */
} IMPISPTemperDenoiseAttr;


/**
 * @fn int IMP_ISP_Tuning_SetSinterDnsAttr (IMPISPSinterDenoiseAttr * pinfo)
 *
 * Set up ISP Paramètres du module de réduction du bruit spatial 
 *
 * @param[in] pointeur de paramètre de réduction du bruit dans le domaine temporel pinfo
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Définissez les paramètres de correction du module de réduction du bruit spatial.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetSinterDnsAttr (IMPISPSinterDenoiseAttr * pinfo)
 *
 * Obtain ISP Spatial noise reduction module parameters 
 *
 * @param[in] pointeur de paramètre de réduction du bruit de l'espace pinfo
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Obtenez les paramètres de correction du module de réduction du bruit spatial.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
#if 0
/**
* @fn int IMP_ISP_Tuning_SetTemperDnsCtl (IMPISPTemperDenoiseAttr * pinfo);
*
* Set up ISP Mode du module de réduction du bruit dans le domaine temporel 
*
* @param[in] pinfo Time domain noise reduction parameter pointer 
*
* @retval 0 success 
* @retval non- 0 failure ， Return error code 
*
* @remark Définissez les paramètres de mode du module de réduction du bruit dans le domaine temporel, le mode automatique par défaut.
*
* @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
*/
int IMP_ISP_Tuning_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
#endif
/**
 * @fn int IMP_ISP_Tuning_SetTemperDnsAttr (IMPISPTemperDenoiseAttr * pinfo)
 *
 * Set up ISP Paramètres du module de réduction du bruit dans le domaine temporel 
 *
 * @param[in] pinfo Time domain noise reduction parameter pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Définissez les paramètres de correction du module de réduction du bruit dans le domaine temporel, et le module est activé par défaut; comme le module nécessite de la mémoire supplémentaire, veuillez éteindre le module si vous n'en avez pas besoin. Une fois la mémoire désactivée, il sera être rel â chée et ne peut plus être remise sous tension.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetTemperDnsAttr (IMPISPTemperDenoiseAttr * pinfo)
 *
 * Obtain ISP Time domain noise reduction module parameters 
 *
 * @param[in] pinfo Pointeur de paramètre du module de réduction du bruit dans le domaine temporel
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Obtenez les paramètres de correction du module de réduction du bruit dans le domaine temporel.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_SetWDRAttr (mode IMPISPTuningOpsMode)
 *
 * Set up ISP Si le module dynamique large est activé 
 *
 * @param[in] paramètres du module dynamique à l'échelle du mode
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Définissez les paramètres d'étalonnage du module dynamique large, le module est activé par défaut; parce que le module nécessite de la mémoire supplémentaire, veuillez éteindre le module si vous n'en avez pas besoin. Une fois que vous éteignez la mémoire, elle sera libérée et ne pourra plus être rallumé.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetWDRAttr (IMPISPTuningOpsMode * pmode)
 *
 * Obtain ISP État actuel du module dynamique large 
 *
 * @param[in] pointeur de paramètre de module dynamique large pmode
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Obtenez les paramètres de correction du module dynamique large.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetWDRAttr(IMPISPTuningOpsMode *pmode);

/**
 * ISP Fonction d'extension complète ， Sélection du mode scène. 
 */
typedef enum {
	IMPISP_SCENE_MODE_AUTO = 0,					/**< Mode automatique */
	IMPISP_SCENE_MODE_BEACH_SNOW = 2,				/**< Mode scène de neige sur la plage */
	IMPISP_SCENE_MODE_CANDLE_LIGHT = 3,				/**< Mode lumière bougie */
	IMPISP_SCENE_MODE_DAWN_DUSK = 4,				/**< Mode soirée */
	IMPISP_SCENE_MODE_FALL_COLORS = 5,				/**< Mode scène d'automne */
	IMPISP_SCENE_MODE_FIREWORKS = 6,				/**< Mode scène de feux d'artifice */
	IMPISP_SCENE_MODE_LANDSCAPE = 7,				/**< Mode paysage */
	IMPISP_SCENE_MODE_NIGHT = 8,					/**< Mode nuit */
	IMPISP_SCENE_MODE_PARTY_INDOOR = 9,				/**< Mode fête en intérieur */
	IMPISP_SCENE_MODE_SPORTS = 11,					/**< Mode sport */
	IMPISP_SCENE_MODE_SUNSET = 12,					/**< Mode coucher de soleil */
	IMPISP_SCENE_MODE_TEXT = 13,					/**< Mode texte */
	IMPISP_SCENE_MODE_NIGHT_PORTRAIT = 14,				/**< Mode portrait de nuit */
} IMPISPSceneMode;

/**
 * @fn int IMP_ISP_Tuning_SetSceneMode (mode IMPISPSceneMode)
 *
 * Set up ISP Mode scène d'effets complet 
 *
 * @param[in] mode Paramètre de mode de scène d'effet
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetSceneMode (IMPISPSceneMode * pmode)
 *
 * Obtain ISP Comprehensive effect scene mode 
 *
 * @param[in] pointeur de paramètre de mode scène d'effet pmode
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetSceneMode(IMPISPSceneMode *pmode);

/**
 * ISP Comprehensive extension function ， Sélection du mode couleur. 
 */
typedef enum {
	IMPISP_COLORFX_MODE_AUTO = 0,				/**< Automatic mode */
	IMPISP_COLORFX_MODE_BW = 1,				/**< Mode noir et blanc */
	IMPISP_COLORFX_MODE_SEPIA = 2,				/**< Mode sépia */
	IMPISP_COLORFX_MODE_NEGATIVE = 3,			/**< Mode couleur inversé */
	IMPISP_COLORFX_MODE_VIVID = 9,				/**< Mode vif */
} IMPISPColorfxMode;

/**
 * @fn int IMP_ISP_Tuning_SetColorfxMode (mode IMPISPColorfxMode)
 *
 * Set up ISP Mode couleur multi-effets 
 *
 * @param[in] paramètre de mode couleur
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetColorfxMode (IMPISPColorfxMode * pmode)
 *
 * Obtain ISP Multi-effect color mode 
 *
 * @param[in] pointeur de paramètre de mode couleur pmode
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_GetColorfxMode(IMPISPColorfxMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetBrightness (caractère non signé brillant)
 *
 * Set up ISP Luminosité d'image complète 
 *
 * @param[in] Paramètre de luminosité de l'image lumineuse
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark La valeur par défaut est 128, plus de 128 augmente la luminosité, moins de 128 diminue la luminosité.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetBrightness(unsigned char bright);

/**
 * @fn int IMP_ISP_Tuning_GetBrightness (caractère non signé * pbright)
 *
 * Obtain ISP Comprehensive effect picture brightness 
 *
 * @param[in] Pointeur de paramètre de luminosité de l'image lumineuse
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
 * @fn int IMP_ISP_Tuning_SetContrast (contraste de caractères non signé)
 *
 * Set up ISP Contraste d'image complet 
 *
 * @param[in] contraste paramètre de contraste de l'image
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark La valeur par défaut est 128, plus de 128 augmente le contraste, moins de 128 réduit le contraste.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetContrast(unsigned char contrast);

/**
 * @fn int IMP_ISP_Tuning_GetContrast (caractère non signé * pcontrast)
 *
 * Obtain ISP Comprehensive effect picture contrast 
 *
 * @param[in] pointeur de paramètre de contraste de l'image de contraste
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
 * @fn int IMP_ISP_Tuning_SetSharpness (netteté des caractères non signés)
 *
 * Set up ISP Netteté d'image complète 
 *
 * @param[in] netteté image valeur du paramètre de netteté
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark La valeur par défaut est 128, plus de 128 augmente la netteté, moins de 128 diminue la netteté.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness);

/**
 * @fn int IMP_ISP_Tuning_GetSharpness (caractère non signé * psharpness)
 *
 * Obtain ISP Comprehensive effect picture sharpness 
 *
 * @param[in] pointeur de paramètre de netteté de l'image de netteté
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
 * @fn int IMP_ISP_Tuning_SetSaturation (caractère non signé sat)
 *
 * Set up ISP Saturation complète de l'image avec effet 
 *
 * @param[in] saturation de l'image valeur du paramètre de saturation
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark La valeur par défaut est 128, plus de 128 augmente la saturation, moins de 128 diminue la saturation.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetSaturation(unsigned char sat);

/**
 * @fn int IMP_ISP_Tuning_GetSaturation (caractère non signé * psat)
 *
 * Obtain ISP Comprehensive effect picture saturation 
 *
 * @param[in] pointeur de paramètre de saturation d'image sat
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
 * @fn int IMP_ISP_Tuning_SetISPProcess (mode IMPISPTuningOpsMode)
 *
 * contourne ISP Manipulation des modules ， Sortie directe sensor image 
 *
 * @param[in] mode s'il faut contourner les paramètres de traitement du module ISP
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Si cette fonction est activée, l'image sortie par le capteur sera sortie directement sans aucun traitement par le module ISP.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode);
#endif
/**
 * @fn int IMP_ISP_Tuning_SetFWFreeze (mode IMPISPTuningOpsMode)
 *
 * Geler ISP Fonctionnement du micrologiciel ， Activer signifie geler ISP firmware ， c'est ISP L'algorithme automatique s'arrêtera; s'il n'est pas activé, cela signifie ISP Le firmware fonctionne normalement. 
 *
 * @param[in] mode s'il faut geler les paramètres du micrologiciel du FAI
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SetFWFreeze(IMPISPTuningOpsMode mode);


/**
 * @fn int IMP_ISP_Tuning_SaveAllParam (char * chemin)
 *
 * sauvegarder ISP Tous les paramètres de débogage du module 
 *
 * @param[in] pointeur de paramètre de chemin de chemin
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Enregistrez tous les paramètres du FAI pour le débogage.
 *
 * @attention Before using this function ， Must guarantee ISP The effect debugging function has been enabled .
 */
int IMP_ISP_Tuning_SaveAllParam(char *path);

/**
 * @fn int IMP_ISP_Tuning_SetISPBypass (activation IMPISPTuningOpsMode)
 *
 * ISP Si le module bypass
 *
 * @param[in] activer s'il faut contourner le mode de sortie
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no 
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que le module ISP est fermé.
 */
int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable);

/**
 * @fn int IMP_ISP_Tuning_GetTotalGain (uint32_t * gain)
 *
 * Obtain ISP La valeur de gain globale de l'image de sortie 
 *
 * @param[in] gain est un pointeur pour obtenir le paramètre de valeur de gain, son format de stockage de données est [24,8], le haut 24 bits est un entier et le bas 8 bits est un décimal.
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention Before using this function ， Must guarantee IMP_ISP_EnableSensor with IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);

/**
 * Set up ISP Si la fonction d'effet de miroir d'image est activée 
 *
 * @fn int IMP_ISP_Tuning_SetISPHflip (mode IMPISPTuningOpsMode)
 *
 * @param[in] mode s'il faut activer l'effet miroir
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention Avant d'utiliser cette fonction, IMP_ISP_EnableTuning a été appelé.
 */
int IMP_ISP_Tuning_SetISPHflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPHflip (IMPISPTuningOpsMode * pmode)
 *
 * Obtain ISP L'état de fonctionnement de la fonction d'effet de miroir d'image 
 *
 * @param[in] pointeur de paramètre d'opération pmode
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetISPHflip(IMPISPTuningOpsMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetISPVflip (mode IMPISPTuningOpsMode)
 *
 * Set up ISP Si la fonction d'effet inverse de l'image vers le haut et vers le bas est activée 
 *
 * @param[in] mode s'il faut activer l'inversion de l'image vers le haut et vers le bas
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPVflip (IMPISPTuningOpsMode * pmode)
 *
 * Obtain ISP L'état de fonctionnement de l'image de haut en bas de la fonction d'effet inverse 
 *
 * @param[in] pmode Operation parameter pointer 
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetISPVflip(IMPISPTuningOpsMode *pmode);

/**
 * ISP Configuration du mode de fonctionnement ， Mode normal ou mode de vision nocturne. 
 */
typedef enum {
	IMPISP_RUNNING_MODE_DAY = 0,				/**< Mode normal */
	IMPISP_RUNNING_MODE_NIGHT = 1,				/**< Mode vision nocturne */
	IMPISP_RUNNING_MODE_BUTT,					/**< Max */
} IMPISPRunningMode;

/**
 * @fn int IMP_ISP_Tuning_SetISPRunningMode (mode IMPISPRunningMode)
 *
 * Set up ISP Mode de fonctionnement ， Mode normal ou mode de vision nocturne; le mode par défaut est le mode normal. 
 *
 * @param[in] paramètre de mode de fonctionnement de mode
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * Exemple: 
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
 * @fn int IMP_ISP_Tuning_GetISPRunningMode (IMPISPRunningMode * pmode)
 *
 * Obtain ISP Operating mode ， Normal mode or night vision mode. 
 *
 * @param[in] pointeur de paramètre d'opération pmode
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode);

/**
 * ISP Configuration de la stratégie d'exposition automatique ， Mode normal ou mode de priorité d'exposition. 
 **/
typedef enum {
	IMPISP_AE_STRATEGY_SPLIT_BALANCED = 0, /**< Normal mode */
	IMPISP_AE_STRATEGY_SPLIT_INTEGRATION_PRIORITY = 1, /**< Mode de priorité d'exposition */
	IMPISP_AE_STRATEGY_BUTT, /**< Max */
} IMPISPAeStrategy;

/**
 * @fn int IMP_ISP_Tuning_SetAeStrategy (stratégie IMPISPAeStrategy)
 *
 * Set up ISP Operating mode ， Automatic exposure strategy configuration ， Mode normal ou mode de priorité d'exposition; le mode par défaut est le mode normal. 
 *
 * @param[in] stratégie Paramètres de stratégie d'exposition automatique
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
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
* @fn int IMP_ISP_Tuning_GetAeStrategy (IMPISPAeStrategy * pstrategy)
*
* Obtain ISP Automatic exposure strategy configuration ， Normal mode or exposure priority mode. 
* @param[in] Pointeur de paramètre de stratégie d'exposition automatique pstrategy
*
* @retval 0 成功 
* @retval 非 0 失败 ， 返回错误码 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_GetAeStrategy(IMPISPAeStrategy *pstrategy);

/**
 * gamma
 */
typedef struct {
	uint16_t gamma[129];		/**< gamma Tableau de paramètres ， Ont 129 Points */
} IMPISPGamma;

/**
* @fn int IMP_ISP_Tuning_SetGamma (IMPISPGamma * gamma)
*
* Set up GAMMA paramètre .
* @param[in] paramètre gamma gamma
*
* @retval 0 成功 
* @retval 非 0 失败 ， 返回错误码 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_GetGamma (IMPISPGamma * gamma)
*
* Obtain GAMMA parameter .
* @param[out] gamma gamma parameter 
*
* @retval 0 成功 
* @retval 非 0 失败 ， 返回错误码 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_SetAeComp (int comp)
*
* Set up AE se réconcilier. AE Les paramètres de compensation peuvent ajuster l'image AE target， La plage de réglage recommandée est [90-150].
* @param[in] comp Paramètres de compensation AE
*
* @retval 0 成功 
* @retval 非 0 失败 ， 返回错误码 
*
* @attention Before using this function ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_SetAeComp(int comp);

/**
* @fn int IMP_ISP_Tuning_GetAeComp (int * comp)
*
* Obtain AE make up. 
* @param[out] comp AE Compensation parameter 
*
* @retval 0 成功 
* @retval 非 0 失败 ， 返回错误码 
*
* @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_GetAeComp(int *comp);

/**
 * Mode d'exposition 
 */
enum isp_core_expr_mode {
	ISP_CORE_EXPR_MODE_AUTO,			/**< Automatic mode */
	ISP_CORE_EXPR_MODE_MANUAL,			/**< Mode manuel */
};

/**
 * Unité d'exposition 
 */
enum isp_core_expr_unit {
	ISP_CORE_EXPR_UNIT_LINE,			/**< Rangée */
	ISP_CORE_EXPR_UNIT_US,				/**< milliseconde */
};

/**
 * Paramètres d'exposition 
 */
typedef union isp_core_expr_attr{
	struct {
		enum isp_core_expr_mode mode;		/**< Définir le mode d'exposition */
		enum isp_core_expr_unit unit;		/**< Définir l'unité d'exposition */
		uint16_t time;
	} s_attr;
	struct {
		enum isp_core_expr_mode mode;			/**< Mode d'exposition acquis */
		uint16_t integration_time;		/**< Délai d'exposition ， L'unité est la ligne */
		uint16_t integration_time_min;	/**< Temps d'exposition minimum obtenu ， Unit is line */
		uint16_t integration_time_max;	/**< Temps d'exposition maximal obtenu ， Unit is line */
		uint16_t one_line_expr_in_us;		/**< Le nombre de microsecondes correspondant au temps d'exposition de la ligne acquise */
	} g_attr;
}IMPISPExpr;


/**
 * @fn int IMP_ISP_Tuning_SetExpr (IMPISPExpr * expr)
 *
 * Set up AE paramètre. 
 *
 * @param[in] paramètre expr AE.
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr);

/**
 * @fn int IMP_ISP_Tuning_GetExpr (IMPISPExpr * expr)
 *
 * Obtain AE parameter. 
 *
 * @param[out] expr AE parameter. 
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetExpr(IMPISPExpr *expr);

/**
 * Sélection de la zone des statistiques d'exposition 
 */
typedef union isp_core_ae_roi_select{
	struct {
		unsigned endy :8; /**< Point final y coordonner (0 ~ 255)*/
		unsigned endx :8; /**< End point x coordinate (0 ~ 255)*/
		unsigned starty :8; /**< Point de départ y coordinate (0 ~ 255)*/
		unsigned startx :8; /**< Starting point x coordinate (0 ~ 255)*/
	};
	uint32_t value;
} IMPISPAERoi;

/**
 * @fn int IMP_ISP_Tuning_AE_GetROI (IMPISPAERoi * isp_ae_roi)
 *
 * Obtain AE Zone de statistiques. 
 *
 * @param[out] isp_ae_roi AE Paramètres de la zone statistique rectangulaire.
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);

/**
 * @fn int IMP_ISP_Tuning_AE_SetROI (IMPISPAERoi * isp_ae_roi)
 *
 * Set up AE Statistics area. 
 *
 * @param[in] isp_ae_roi AE Rectangular statistical area parameters. 
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);

/**
 * Mode de balance des blancs 
 */
enum isp_core_wb_mode {
	ISP_CORE_WB_MODE_AUTO = 0,			/**< Automatic mode */
	ISP_CORE_WB_MODE_MANUAL,			/**< Manual mode */
	ISP_CORE_WB_MODE_DAY_LIGHT,			/**< journée ensoleillée */
	ISP_CORE_WB_MODE_CLOUDY,			/**< temps nuageux */
	ISP_CORE_WB_MODE_INCANDESCENT,		/**< Lampe à incandescence */
	ISP_CORE_WB_MODE_FLOURESCENT,		/**< Lampe fluorescente */
	ISP_CORE_WB_MODE_TWILIGHT,			/**< crépuscule */
	ISP_CORE_WB_MODE_SHADE,				/**< ombre */
	ISP_CORE_WB_MODE_WARM_FLOURESCENT,	/**< Lampe fluorescente chaude */
};

/**
 * Paramètres de balance des blancs 
 */
typedef struct isp_core_wb_attr{
	enum isp_core_wb_mode mode;		/**< White balance mode ， Divisé en modes automatique et manuel */
	uint16_t rgain;			/**< Gain rouge ， Efficace en mode manuel */
	uint16_t bgain;			/**< Gain bleu ， Effective in manual mode */
}IMPISPWB;

/**
 * @fn int IMP_ISP_Tuning_SetWB (IMPISPWB * wb)
 *
 * Définissez les paramètres de la fonction de balance des blancs. ， Le mode manuel est principalement défini par rgain [[[ bgain atteindre. 
 *
 * @param[in] wb Jeu de paramètres de balance des blancs.
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_GetWB (IMPISPWB * wb)
 *
 * Obtenez le réglage de la fonction de balance des blancs. 
 *
 * @param[out] wb Paramètre de balance des blancs obtenu.
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetWB(IMPISPWB *wb);

/**
 * @fn IMP_ISP_Tuning_GetWB_Statis (IMPISPWB * wb)
 *
 * Obtenez des statistiques de balance des blancs. 
 *
 * @param[out] wb Statistiques de balance des blancs obtenues.
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_Awb_GetCwfShift (IMPISPWB * isp_wb_attr)
 *
 * Obtain ISP in AWB de CWF La position de la source lumineuse 
 *
 * @param[out] isp_wb_attr Coordonnées de la position de la source lumineuse CWF
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);

/**
 * @fn int IMP_ISP_Tuning_Awb_SetCwfShift (IMPISPWB * isp_wb_attr)
 *
 * Set up ISP in AWB of CWF The position of the light source 
 *
 * @param[in] isp_wb_attr CWF Light source position coordinates 
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
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
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);

/**
 * @fn int IMP_ISP_Tuning_SetMaxAgain (gain uint32_t)
 *
 * Set up sensor Vous pouvez définir le maximum Again . 
 *
 * @param[in] Le maximum que le capteur de gain peut régler est de nouveau: 0 signifie 1x, 32 signifie 2x, et ainsi de suite.
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);

/**
 * @fn int IMP_ISP_Tuning_GetMaxAgain (uint32_t * gain)
 *
 * Obtain sensor You can set the maximum Again . 
 *
 * @param[out] gain sensor The maximum that can be set again.0 Means 1x，32 Means 2x， And so on. 
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetMaxDgain (gain uint32_t)
 *
 * Set up ISP Le maximum qui peut être défini Dgain . 
 *
 * @param[in] Le gain maximal qui peut être défini par le FAI Dgain.0 signifie 1x, 32 signifie 2x, et ainsi de suite.
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain);

/**
 * @fn int IMP_ISP_Tuning_GetMaxDgain (uint32_t * gain)
 *
 * Obtain ISP Définir le maximum Dgain . 
 *
 * @param[out] ISP Dgain peut obtenir le gain maximum défini.0 signifie 1x, 32 signifie 2x, et ainsi de suite.
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetVideoDrop (void (* cb) (void))
 *
 * Réglez la fonction de perte vidéo. sensor En cas de problème avec la ligne de connexion à la carte mère ， La fonction de rappel définie sera exécutée. 
 *
 * @param[in] fonction de rappel cb.
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void));

/**
 * @fn int IMP_ISP_Tuning_SetHiLightDepress (force uint32_t)
 *
 * Réglez l'intensité de la forte suppression de la lumière. 
 *
 * @param[in] force Le paramètre d'intensité de suppression de la lumière forte La plage de valeurs est [0-10], 0 signifie que la fonction est désactivée.
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength);

/**
 * @fn int IMP_ISP_Tuning_SetTemperStrength (rapport uint32_t)
 *
 * Set up 3D Intensité de la réduction du bruit. 
 *
 * @param[in] ratio: Le rapport de réglage de l'intensité. S'il est réglé sur 90, cela signifie qu'il est réglé sur 90% de la valeur par défaut. La plage de valeurs est [50-150].
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetSinterStrength (rapport uint32_t)
 *
 * Set up 2D Noise reduction intensity. 
 *
 * @param[in] ratio Intensity adjustment ratio . If set to 90 It means that it is set to the default value 90%. The value range is [ 50-150].
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetDPStrength (rapport uint32_t)
 *
 * Set up DPC force. 
 *
 * @param[in] ratio Intensity adjustment ratio . If set to 90 It means that it is set to the default value 90%. The value range is [ 50-150].
 *
 * @retval 0 成功 
 * @retval 非 0 失败 ， 返回错误码 
 *
 * @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
 */
int IMP_ISP_Tuning_SetDPStrength(uint32_t ratio);

/**
 * ISP ANTIFOG Mode de fonctionnement. 
 */
typedef enum {
	ANTIFOG_DISABLE,			/**< shut down */
	ANTIFOG_STRONG,				/**< Fort */
	ANTIFOG_MEDIUM,				/**< in */
	ANTIFOG_WEAK,				/**< faible */
}IMPISPAntiFogAttr;

/**
* @fn int IMP_ISP_Tuning_SetAntiFogAttr (IMPISPAntiFogAttr attr)
*
* Set up ANTIFOG Les attributs. 
* @param[in] attr Paramètres d'attribut ANTIFOG
*
* @retval 0 成功 
* @retval 非 0 失败 ， 返回错误码 
*
* @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
*/
int IMP_ISP_Tuning_SetAntiFogAttr(IMPISPAntiFogAttr attr);

/**
 * ISP EV parameter. 
 */
typedef struct {
	uint32_t ev;			/**< Valeur d'exposition */
	uint32_t expr_us;		/**< Délai d'exposition */
	uint32_t ev_log2;		/**<log Formater le temps d'exposition */
	uint32_t again;			/**< Gain analogique */
	uint32_t dgain;			/**< Gain numérique */
	uint32_t gain_log2;		/**< log Gain de format */
}IMPISPEVAttr;

/**
* @fn int IMP_ISP_Tuning_GetEVAttr (IMPISPEVAttr * attr)
*
* Obtain EV Attributes. 
* @param[out] attr Paramètres d'attribut EV
*
* @retval 0 成功 
* @retval 非 0 失败 ， 返回错误码 
*
* @attention 在使用这个函数之前 ，IMP_ISP_EnableTuning Has been called. 
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
