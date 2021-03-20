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
 * @ingroup imp
 * @brief Unité de traitement du signal d'image. Sensor Enregistrement, ajout, suppression, etc. 
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
 *	.modalias = "xx", //SPI Nom de l'appareil ， Doit et sensor Conduite struct spi_device_id milieu name Unanime. 
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
 * ret = IMP_ISP_EnableTuning(); //step.4 Permettre ISP tuning, Avant d'appeler ISP Interface de débogage. 
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
 * ret = IMP_ISP_DisableSensor(); //step.2 fermer sensor， à l'heure actuelle sensor Arrêter la sortie des images; avant cette opération FrameSource Tout doit être fermé. 
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
	TX_SENSOR_CONTROL_INTERFACE_SPI,	/**< SPI Bus de contrôle */
} IMPSensorControlBusType;

/**
* Le type de bus de contrôle de la caméra est I2C Temps ， La structure des paramètres à configurer 
*/
typedef struct {
	char type[20];		/**< I2C Nom de l'appareil ， Doit être conduit avec la caméra struct i2c_device_id dans name Les variables sont cohérentes */
	int addr;		/**< I2C adresse */
	int i2c_adapter_id;	/**< I2C Manette */
} IMPI2CInfo;
/**
* Le type de bus de contrôle de la caméra est SPI Temps ， La structure des paramètres à configurer 
*/
typedef struct {
	char modalias[32];	/**< SPI Nom de l'appareil ， Doit être conduit avec la caméra struct spi_device_id dans name Les variables sont cohérentes */
	int bus_num;		/**< SPI Adresse de bus */
} IMPSPIInfo;

/**
* Structure des informations d'enregistrement de la caméra 
*/
typedef struct {
	char name[32];					/**< Nom de la caméra */
	IMPSensorControlBusType cbus_type;	/**< Type de bus de contrôle de caméra */
	union {
		IMPI2CInfo i2c;				/**< I2C Informations sur le bus */
		IMPSPIInfo spi;				/**< SPI Informations sur le bus */
	};
	unsigned short rst_gpio;		/**< webcam reset Lien d'interface GPIO， Remarque: ce paramètre n'est pas activé maintenant */
	unsigned short pwdn_gpio;		/**< webcam power down Lien d'interface GPIO， Remarque: ce paramètre n'est pas activé maintenant */
	unsigned short power_gpio;		/**< webcam power Lien d'interface GPIO， Remarque: ce paramètre n'est pas activé maintenant */
} IMPSensorInfo;

/**
 * @fn int IMP_ISP_Open(void)
 *
 * allumer ISP Module 
 *
 * @param non 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark créer ISP Module ， Prêt à ISP Ajouter à sensor， Et allumer ISP Fonction de débogage d'effet. 
 *
 * @attention Cette fonction doit être ajoutée sensor A été appelé avant. 
 */
int IMP_ISP_Open(void);

/**
 * @fn int IMP_ISP_Close(void)
 *
 * fermer ISP Module 
 *
 * @param non 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark ISP Module ，ISP Le module ne fonctionne plus. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir tout FrameSource Et la fonction de débogage d'effet a été désactivée ， tout sensor Ont été désinstallés .
 */
int IMP_ISP_Close(void);

/**
 * @fn int IMP_ISP_AddSensor(IMPSensorInfo *pinfo)
 *
 * ajoute un sensor， Habitué ISP Le module fournit la source de données 
 *
 * @param[in] pinfo Besoin d'ajouter sensor Pointeur d'information 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Ajouter une caméra ， Utilisé pour fournir des images. 
 *
 * @attention Avant d'utiliser cette fonction ， Il faut s'assurer que le pilote de la caméra a été enregistré dans le noyau .
 */
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);

/**
 * @fn int IMP_ISP_DelSensor(IMPSensorInfo *pinfo)
 *
 * Supprimer un sensor
 *
 * @param[in] pinfo Doit être supprimé sensor Pointeur d'information 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Supprimer une caméra. 
 *
 * @attention Avant d'utiliser cette fonction ， Il faut s'assurer que la caméra a cessé de fonctionner ， Appelé IMP_ISP_DisableSensor fonction .
 */
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);

/**
 * @fn int IMP_ISP_EnableSensor(void)
 *
 * Activer un sensor
 *
 * @param non 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Activer une caméra ， Faites-le commencer à transférer des images , tel FrameSource Pour sortir l'image ， à la fois ISP Ce n'est qu'alors que l'effet peut être débogué. 
 *
 * @attention Avant d'utiliser cette fonction ， Il faut s'assurer que la caméra a été ajoutée ISP Module .
 */
int IMP_ISP_EnableSensor(void);

/**
 * @fn int IMP_ISP_DisableSensor(void)
 *
 * Désactiver un sensor
 *
 * @param non 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Désactiver une caméra ， Arrêter de transmettre des images , tel FrameSource Impossible de sortir l'image ， à la fois ISP L'effet ne peut pas non plus être débogué. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir tout FrameSource Ont arrêté de sortir des images ， Dans le même temps, le débogage des effets est également à l'état désactivé .
 */
int IMP_ISP_DisableSensor(void);

/**
 * @fn int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value)
 *
 * Installation sensor La valeur d'un registre 
 *
 * @param[in] reg Adresse d'inscription 
 *
 * @param[in] value Enregistrer la valeur 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Vous pouvez en définir un directement sensor La valeur du registre. 
 *
 * @attention Avant d'utiliser cette fonction ， Il faut s'assurer que la caméra a été activée .
 */
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value);

/**
 * @fn int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *value)
 *
 * Obtenir sensor La valeur d'un registre 
 *
 * @param[in] reg Adresse d'inscription 
 *
 * @param[in] value Pointeur pour enregistrer la valeur 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Vous pouvez en obtenir un directement sensor La valeur du registre. 
 *
 * @attention Avant d'utiliser cette fonction ， Il faut s'assurer que la caméra a été activée .
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
	IMPISP_TUNING_OPS_TYPE_RANGE, /**< Le fonctionnement de ce module est le mode de plage de réglage */
	IMPISP_TUNING_OPS_TYPE_BUTT,			/**< Utilisé pour juger de la validité des paramètres ， La taille du paramètre doit être inférieure à cette valeur */
} IMPISPTuningOpsType;

/**
 * @fn int IMP_ISP_EnableTuning(void)
 *
 * Permettre ISP Fonction de débogage d'effet 
 *
 * @param non 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir IMP_ISP_EnableSensor A été exécuté et renvoyé avec succès .
 */
int IMP_ISP_EnableTuning(void);

/**
 * @fn int IMP_ISP_DisableTuning(void)
 *
 * Désactiver ISP Fonction de débogage d'effet 
 *
 * @param non 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Il faut s'assurer que le sensor antérieur à ， Désactiver d'abord ISP Débogage d'effet (c'est-à-dire, appelez cette fonction) .
 */
int IMP_ISP_DisableTuning(void);

/**
 * @fn int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den)
 *
 * Définir la fréquence d'images de sortie de la caméra 
 *
 * @param[in] fps_num Définir le paramètre du numérateur de la fréquence d'images 
 * @param[in] fps_den Définir le paramètre dénominateur de la fréquence d'images 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir IMP_ISP_EnableSensor avec IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);

/**
 * @fn int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den)
 *
 * Obtenez la fréquence d'images de sortie de la caméra 
 *
 * @param[in] fps_num Obtenez un pointeur sur les paramètres moléculaires de la fréquence d'images 
 * @param[in] fps_den Obtenir un pointeur vers le paramètre du dénominateur de la fréquence d'images 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir IMP_ISP_EnableSensor avec IMP_ISP_EnableTuning A été appelé. 
 * @attention Cette fonction doit être appelée pour obtenir la fréquence d'images par défaut de la caméra avant que le canal d'image ne soit activé pour démarrer la transmission des données. 
 */
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);

/**
 * ISP Structure des paramètres de propriété anti-scintillement. 
 */
typedef enum {
	IMPISP_ANTIFLICKER_DISABLE,	/**< Désactiver ISP Fonction anti-flash */
	IMPISP_ANTIFLICKER_50HZ,	/**< Permettre ISP Fonction anti-flash , Et réglez la fréquence sur 50HZ */
	IMPISP_ANTIFLICKER_60HZ,	/**< Permettre ISP Fonction anti-flash ， Et réglez la fréquence sur 60HZ */
	IMPISP_ANTIFLICKER_BUTT,	/**< Utilisé pour juger de la validité des paramètres ， La taille du paramètre doit être inférieure à cette valeur */
} IMPISPAntiflickerAttr;

/**
 * @fn int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr)
 *
 * Installation ISP Propriétés anti-flash 
 *
 * @param[in] attr Définir la valeur du paramètre 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);

/**
 * @fn int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr)
 *
 * obtenir ISP Propriétés anti-flash 
 *
 * @param[in] pattr Obtenir le pointeur de valeur de paramètre 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
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
	IMPISP_DRC_RANGE,				/**< ISP Mode de réglage de la plage du module de compression de plage dynamique */
} IMPISPDrcMode;

/**
 * ISP Paramètres d'attribut du module de compression de plage dynamique. 
 */
typedef struct {
	IMPISPDrcMode mode;				/**< ISP Sélection du mode de fonctionnement du module de compression de plage dynamique */
	unsigned char drc_strength;			/**< Valeur cible définie en mode manuel ， La plage de valeurs est [0, 0xff] */
	unsigned char dval_max;				/**< Mode de portée maximum ， La plage de valeurs est [0, 0xff] */
	unsigned char dval_min;				/**< Mode de portée minimum ， La plage de valeurs est [0, 0xff] */
	unsigned char slop_max;				/**< Paramètres de contrôle de la force ， La plage de valeurs est [0, oxff] */
	unsigned char slop_min;				/**< Paramètres de contrôle de la force ， La plage de valeurs est [0, oxff] */
	unsigned short black_level;			/**< DRC Valeur de pixel minimale améliorée ， La plage de valeurs est [0, oxfff] */
	unsigned short white_level;			/**< DRC Valeur de pixel maximale améliorée ， La plage de valeurs est [0, oxfff] */
} IMPISPDrcAttr;

/**
 * @fn int IMP_ISP_Tuning_SetRawDRC(IMPISPDrcAttr *pinfo)
 *
 * Installation ISP RAW Figure paramètres du module de compression de plage dynamique 
 *
 * @param[in] pinfo Pointeur de paramètre de plage dynamique 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Installation RGB RAW Type d'opération de compression de plage dynamique graphique ， force ， Les valeurs de pixel maximum et minimum qui doivent être améliorées. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetRawDRC(IMPISPDrcAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo)
 *
 * Obtenir ISP RAW Figure paramètres du module de compression de plage dynamique 
 *
 * @param[in] pinfo Pointeur de paramètre de plage dynamique 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Installation RGB RAW Type d'opération de compression de plage dynamique graphique ， force ， Les valeurs de pixel maximum et minimum qui doivent être améliorées. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);

/**
 * ISP Paramètres d'attribut du module de réduction du bruit spatial. 
 */
typedef struct {
	IMPISPTuningOpsMode enable;			/**< Activer la fonction de réduction du bruit spatial */
	IMPISPTuningOpsType type;				/**< Type d'opération de la fonction de réduction du bruit spatial ， Automatique ou manuel */
	unsigned char sinter_strength;				/**< Intensité de la réduction du bruit spatial ， Le mode manuel est efficace ， La plage de valeurs est [0, 0xff] */
	unsigned char sval_max;				/**< Intensité de la réduction du bruit spatial ， Le mode manuel est efficace ， La plage de valeurs est [0, 0xff] */
	unsigned char sval_min;				/**< Intensité de la réduction du bruit spatial ， Le mode manuel est efficace ， La plage de valeurs est [0, 0xff] */
} IMPISPSinterDenoiseAttr;

/**
 * ISP Mode de fonctionnement du module de réduction du bruit dans le domaine temporel. 
 */
typedef enum {
	IMPISP_TEMPER_DISABLE,				/**< ISP Le module de réduction du bruit dans le domaine temporel n'est pas activé */
	IMPISP_TEMPER_AUTO,					/**< ISP Mode automatique du module de réduction du bruit dans le domaine temporel */
	IMPISP_TEMPER_MANUAL,				/**< ISP Mode manuel du module de réduction du bruit dans le domaine temporel */
	IMPISP_TEMPER_RANGE,				/**< ISP Mode de réglage de la plage du module de réduction du bruit dans le domaine temporel */
} IMPISPTemperMode;

/**
 * ISP Paramètres d'attribut du module de réduction du bruit dans le domaine temporel. 
 */
typedef struct imp_isp_temper_denoise_attr {
	IMPISPTemperMode type;					/**< Type d'opération de la fonction de réduction du bruit dans le domaine temporel ， Désactiver ， Automatique ou manuel */
	unsigned char temper_strength;				/**< Intensité de la réduction du bruit dans le domaine temporel ， Le mode manuel est efficace ， La plage de valeurs est [0, 0xff] */
	unsigned char tval_max;						/**< Mode de réglage de la plage de réduction maximale du bruit spatial , La plage de valeurs est [0, 0xff] */
	unsigned char tval_min;						/**< Mode de réglage de la plage de réduction du bruit spatial minimum , La plage de valeurs est [0, 0xff] */
} IMPISPTemperDenoiseAttr;


/**
 * @fn int IMP_ISP_Tuning_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo)
 *
 * Installation ISP Paramètres du module de réduction du bruit spatial 
 *
 * @param[in] pinfo Pointeur de paramètre de réduction du bruit dans le domaine temporel 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Définissez les paramètres de correction du module de réduction du bruit spatial. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo)
 *
 * Obtenir ISP Paramètres du module de réduction du bruit spatial 
 *
 * @param[in] pinfo Pointeur de paramètre de réduction du bruit spatial 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Obtenez les paramètres de correction du module de réduction du bruit spatial. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
#if 0
/**
* @fn int IMP_ISP_Tuning_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
*
* Installation ISP Mode du module de réduction du bruit dans le domaine temporel 
*
* @param[in] pinfo Pointeur de paramètre de réduction du bruit dans le domaine temporel 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @remark Définir les paramètres du mode du module de réduction du bruit dans le domaine temporel ， Le mode automatique par défaut. 
*
* @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
*/
int IMP_ISP_Tuning_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
#endif
/**
 * @fn int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo)
 *
 * Installation ISP Paramètres du module de réduction du bruit dans le domaine temporel 
 *
 * @param[in] pinfo Pointeur de paramètre de réduction du bruit dans le domaine temporel 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Définissez les paramètres de correction du module de réduction du bruit dans le domaine temporel ， Le module est activé par défaut, car le module nécessite de la mémoire supplémentaire ， Veuillez fermer le module si vous n'en avez pas besoin ， La mémoire est libérée une fois fermée ， Ne peut plus être ouvert. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo)
 *
 * Obtenir ISP Paramètres du module de réduction du bruit dans le domaine temporel 
 *
 * @param[in] pinfo Pointeur de paramètre du module de réduction du bruit dans le domaine temporel 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Obtenez les paramètres de correction du module de réduction du bruit temporel. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode)
 *
 * Installation ISP Si le module dynamique large est activé 
 *
 * @param[in] mode Paramètres de module dynamiques larges 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Définir les paramètres d'étalonnage du module dynamique large ， Le module est activé par défaut, car le module nécessite de la mémoire supplémentaire ， Veuillez fermer le module si vous n'en avez pas besoin ， La mémoire est libérée une fois fermée ， Ne peut plus être ouvert. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetWDRAttr(IMPISPTuningOpsMode *pmode)
 *
 * Obtenir ISP État actuel du module dynamique large 
 *
 * @param[in] pmode Large pointeur de paramètres de module dynamique 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Obtenez les paramètres de correction du module dynamique large. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
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
 * @fn int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode)
 *
 * Installation ISP Mode scène d'effets complet 
 *
 * @param[in] mode Paramètres du mode scène d'effet 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetSceneMode(IMPISPSceneMode *pmode)
 *
 * Obtenir ISP Mode scène d'effets complet 
 *
 * @param[in] pmode Pointeur de paramètre du mode scène d'effet 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_GetSceneMode(IMPISPSceneMode *pmode);

/**
 * ISP Fonction d'extension complète ， Sélection du mode couleur. 
 */
typedef enum {
	IMPISP_COLORFX_MODE_AUTO = 0,				/**< Mode automatique */
	IMPISP_COLORFX_MODE_BW = 1,				/**< Mode noir et blanc */
	IMPISP_COLORFX_MODE_SEPIA = 2,				/**< Mode sépia */
	IMPISP_COLORFX_MODE_NEGATIVE = 3,			/**< Mode couleur inversé */
	IMPISP_COLORFX_MODE_VIVID = 9,				/**< Mode vif */
} IMPISPColorfxMode;

/**
 * @fn int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode)
 *
 * Installation ISP Mode couleur multi-effets 
 *
 * @param[in] mode Paramètres du mode couleur 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetColorfxMode(IMPISPColorfxMode *pmode)
 *
 * Obtenir ISP Mode couleur multi-effets 
 *
 * @param[in] pmode Pointeur de paramètre de mode couleur 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_GetColorfxMode(IMPISPColorfxMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetBrightness(unsigned char bright)
 *
 * Installation ISP Luminosité d'image complète 
 *
 * @param[in] bright Paramètre de luminosité de l'image 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128， plus que le 128 Augmenter la luminosité ， Moins que 128 Diminuez la luminosité. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetBrightness(unsigned char bright);

/**
 * @fn int IMP_ISP_Tuning_GetBrightness(unsigned char *pbright)
 *
 * Obtenir ISP Luminosité d'image complète 
 *
 * @param[in] bright Pointeur de paramètre de luminosité de l'image 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128， plus que le 128 Augmenter la luminosité ， Moins que 128 Diminuez la luminosité. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_GetBrightness(unsigned char *pbright);

/**
 * @fn int IMP_ISP_Tuning_SetContrast(unsigned char contrast)
 *
 * Installation ISP Contraste d'image complet 
 *
 * @param[in] contrast Paramètre de contraste de l'image 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128， plus que le 128 Augmenter le contraste ， Moins que 128 Réduisez le contraste. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetContrast(unsigned char contrast);

/**
 * @fn int IMP_ISP_Tuning_GetContrast(unsigned char *pcontrast)
 *
 * Obtenir ISP Contraste d'image complet 
 *
 * @param[in] contrast Pointeur de paramètre de contraste de l'image 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128， plus que le 128 Augmenter le contraste ， Moins que 128 Réduisez le contraste. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_GetContrast(unsigned char *pcontrast);

 /**
 * @fn int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness)
 *
 * Installation ISP Netteté d'image complète 
 *
 * @param[in] sharpness Valeur du paramètre de netteté de l'image 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128， plus que le 128 Augmenter la netteté ， Moins que 128 Réduisez la netteté. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness);

/**
 * @fn int IMP_ISP_Tuning_GetSharpness(unsigned char *psharpness)
 *
 * Obtenir ISP Netteté d'image complète 
 *
 * @param[in] sharpness Pointeur de paramètre de netteté de l'image 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128， plus que le 128 Augmenter la netteté ， Moins que 128 Réduisez la netteté. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_GetSharpness(unsigned char *psharpness);

/**
 * @fn int IMP_ISP_Tuning_SetSaturation(unsigned char sat)
 *
 * Installation ISP Saturation complète de l'image avec effet 
 *
 * @param[in] sat Valeur du paramètre de saturation de l'image 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128， plus que le 128 Augmenter la saturation ， Moins que 128 Diminue la saturation. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetSaturation(unsigned char sat);

/**
 * @fn int IMP_ISP_Tuning_GetSaturation(unsigned char *psat)
 *
 * Obtenir ISP Saturation complète de l'image avec effet 
 *
 * @param[in] sat Pointeur de paramètre de saturation de l'image 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128， plus que le 128 Augmenter la saturation ， Moins que 128 Diminue la saturation. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_GetSaturation(unsigned char *psat);
#if 0
/**
 * @fn int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode)
 *
 * contourne ISP Manipulation des modules ， Sortie directe sensor image 
 *
 * @param[in] mode Que ce soit pour contourner ISP Paramètres de traitement du module 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Si la fonction est activée ，sensor L'image de sortie ne passera pas ISP Tout traitement du module ， Sortie directe. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode);
#endif
/**
 * @fn int IMP_ISP_Tuning_SetFWFreeze(IMPISPTuningOpsMode mode)
 *
 * Geler ISP Fonctionnement du micrologiciel ， Activer signifie geler ISP firmware ， c'est ISP L'algorithme automatique s'arrêtera; s'il n'est pas activé, cela signifie ISP Le firmware fonctionne normalement. 
 *
 * @param[in] mode Est-ce gelé ISP Paramètres du micrologiciel 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetFWFreeze(IMPISPTuningOpsMode mode);


/**
 * @fn int IMP_ISP_Tuning_SaveAllParam(char *path)
 *
 * sauvegarder ISP Tous les paramètres de débogage du module 
 *
 * @param[in] path Pointeur de paramètre de chemin 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Enregistrer tout le débogage ISP paramètre. 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SaveAllParam(char *path);

/**
 * @fn int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable)
 *
 * ISP Si le module bypass
 *
 * @param[in] enable qu'il s'agisse bypass Mode de sortie 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP Le module est fermé .
 */
int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable);

/**
 * @fn int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain)
 *
 * Obtenir ISP La valeur de gain globale de l'image de sortie 
 *
 * @param[in] gain Obtenez le pointeur du paramètre de valeur de gain , Le format de stockage des données est [24.8]， haut 24bit Est un entier ， faible 8bit Est un décimal. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir IMP_ISP_EnableSensor avec IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);

/**
 * Installation ISP Si la fonction d'effet de miroir d'image est activée 
 *
 * @fn int IMP_ISP_Tuning_SetISPHflip(IMPISPTuningOpsMode mode)
 *
 * @param[in] mode Activer ou non l'effet miroir 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetISPHflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPHflip(IMPISPTuningOpsMode *pmode)
 *
 * Obtenir ISP L'état de fonctionnement de la fonction d'effet de miroir d'image 
 *
 * @param[in] pmode Pointeur de paramètre d'opération 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetISPHflip(IMPISPTuningOpsMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode)
 *
 * Installation ISP Si la fonction d'effet d'image à l'envers est activée 
 *
 * @param[in] mode Activer ou non l'image inversée de haut en bas 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPVflip(IMPISPTuningOpsMode *pmode)
 *
 * Obtenir ISP L'état de fonctionnement de l'image de haut en bas de la fonction d'effet inverse 
 *
 * @param[in] pmode Pointeur de paramètre d'opération 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetISPVflip(IMPISPTuningOpsMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetISPHVflip(IMPISPTuningOpsMode hmode, IMPISPTuningOpsMode vmode)
 *
 * Installation ISP image H/V Si la fonction d'effet inverse est activée 
 *
 * @param[in] hmode Activer ou non l'image H Sens inverse 
 * @param[in] vmode Activer ou non l'image V Sens inverse 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetISPHVflip(IMPISPTuningOpsMode hmode, IMPISPTuningOpsMode vmode);

/**
 * @fn int IMP_ISP_Tuning_GetISPHVflip(IMPISPTuningOpsMode *phmode, IMPISPTuningOpsMode *pvmode)
 *
 * Obtenir ISP image H/V L'état de fonctionnement de la fonction d'effet inverse 
 *
 * @param[in] phmode Pointeur de paramètre d'opération 
 * @param[in] pvmode Pointeur de paramètre d'opération 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetISPHVflip(IMPISPTuningOpsMode *phmode, IMPISPTuningOpsMode *pvmode);

/**
 * ISP Configuration du mode de fonctionnement ， Mode normal ou mode de vision nocturne. 
 */
typedef enum {
	IMPISP_RUNNING_MODE_DAY = 0,				/**< Mode normal */
	IMPISP_RUNNING_MODE_NIGHT = 1,				/**< Mode vision nocturne */
	IMPISP_RUNNING_MODE_BUTT,					/**< Max */
} IMPISPRunningMode;

/**
 * @fn int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode)
 *
 * Installation ISP Mode de fonctionnement ， Mode normal ou mode de vision nocturne; le mode par défaut est le mode normal. 
 *
 * @param[in] mode Paramètres du mode de fonctionnement 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
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
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode)
 *
 * Obtenir ISP Mode de fonctionnement ， Mode normal ou mode de vision nocturne. 
 *
 * @param[in] pmode Pointeur de paramètre d'opération 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode);

/**
 * ISP Configuration de la stratégie d'exposition automatique ， Mode normal ou mode de priorité d'exposition. 
 **/
typedef enum {
	IMPISP_AE_STRATEGY_SPLIT_BALANCED = 0, /**< Mode normal */
	IMPISP_AE_STRATEGY_SPLIT_INTEGRATION_PRIORITY = 1, /**< Mode de priorité d'exposition */
	IMPISP_AE_STRATEGY_BUTT, /**< Max */
} IMPISPAeStrategy;

/**
 * @fn int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy strategy)
 *
 * Installation ISP Mode de fonctionnement ， Configuration de la stratégie d'exposition automatique ， Mode normal ou mode de priorité d'exposition; le mode par défaut est le mode normal. 
 *
 * @param[in] strategy Paramètres de stratégie d'exposition automatique 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 * Exemple: 
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
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy strategy);

/**
* @fn int IMP_ISP_Tuning_GetAeStrategy(IMPISPAeStrategy *pstrategy)
*
* Obtenir ISP Configuration de la stratégie d'exposition automatique ， Mode normal ou mode de priorité d'exposition. 
* @param[in] pstrategy Pointeur de paramètre de stratégie d'exposition automatique 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_GetAeStrategy(IMPISPAeStrategy *pstrategy);

/**
 * gamma
 */
typedef struct {
	uint16_t gamma[129];		/**< gamma Tableau de paramètres ， Ont 129 Points */
} IMPISPGamma;

/**
* @fn int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma)
*
* Installation GAMMA paramètre .
* @param[in] gamma gamma paramètre 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma)
*
* Obtenir GAMMA paramètre .
* @param[out] gamma gamma paramètre 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_SetAeComp(int comp)
*
* Installation AE se réconcilier. AE Les paramètres de compensation peuvent ajuster l'image AE target， La plage de réglage recommandée est [90-150].
* @param[in] comp AE Paramètre de compensation 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_SetAeComp(int comp);

/**
* @fn int IMP_ISP_Tuning_GetAeComp(int *comp)
*
* Obtenir AE se réconcilier. 
* @param[out] comp AE Paramètre de compensation 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_GetAeComp(int *comp);

/**
 * Mode d'exposition 
 */
enum isp_core_expr_mode {
	ISP_CORE_EXPR_MODE_AUTO,			/**< Mode automatique */
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
		uint16_t integration_time_min;	/**< Temps d'exposition minimum obtenu ， L'unité est la ligne */
		uint16_t integration_time_max;	/**< Temps d'exposition maximal obtenu ， L'unité est la ligne */
		uint16_t one_line_expr_in_us;		/**< Le nombre de microsecondes correspondant au temps d'exposition de la ligne acquise */
	} g_attr;
}IMPISPExpr;


/**
 * @fn int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr)
 *
 * Installation AE paramètre. 
 *
 * @param[in] expr AE paramètre. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr);

/**
 * @fn int IMP_ISP_Tuning_GetExpr(IMPISPExpr *expr)
 *
 * Obtenir AE paramètre. 
 *
 * @param[out] expr AE paramètre. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetExpr(IMPISPExpr *expr);

/**
 * Sélection de la zone des statistiques d'exposition 
 */
typedef union isp_core_ae_roi_select{
	struct {
		unsigned endy :8; /**< Point final y coordonner (0 ~ 255)*/
		unsigned endx :8; /**< Point final x coordonner (0 ~ 255)*/
		unsigned starty :8; /**< Point de départ y coordonner (0 ~ 255)*/
		unsigned startx :8; /**< Point de départ x coordonner (0 ~ 255)*/
	};
	uint32_t value;
} IMPISPAERoi;

/**
 * @fn int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi)
 *
 * Obtenir AE Zone de statistiques. 
 *
 * @param[out] isp_ae_roi AE Paramètres de zone statistique rectangulaire. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);

/**
 * @fn int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi)
 *
 * Installation AE Zone de statistiques. 
 *
 * @param[in] isp_ae_roi AE Paramètres de zone statistique rectangulaire. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);

/**
 * Mode de balance des blancs 
 */
enum isp_core_wb_mode {
	ISP_CORE_WB_MODE_AUTO = 0,			/**< Mode automatique */
	ISP_CORE_WB_MODE_MANUAL,			/**< Mode manuel */
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
	enum isp_core_wb_mode mode;		/**< Mode de balance des blancs ， Divisé en modes automatique et manuel */
	uint16_t rgain;			/**< Gain rouge ， Efficace en mode manuel */
	uint16_t bgain;			/**< Gain bleu ， Efficace en mode manuel */
}IMPISPWB;

/**
 * @fn int IMP_ISP_Tuning_SetWB(IMPISPWB *wb)
 *
 * Définissez les paramètres de la fonction de balance des blancs. ， Le mode manuel est principalement défini par rgain [[[ bgain atteindre. 
 *
 * @param[in] wb Réglez les paramètres de balance des blancs. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_GetWB(IMPISPWB *wb)
 *
 * Obtenez le réglage de la fonction de balance des blancs. 
 *
 * @param[out] wb Les paramètres de balance des blancs obtenus. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetWB(IMPISPWB *wb);

/**
 * @fn IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb)
 *
 * Obtenez des statistiques de balance des blancs. 
 *
 * @param[out] wb Les statistiques de balance des blancs obtenues. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB* isp_wb_attr)
 *
 * Obtenir ISP dans AWB de CWF La position de la source lumineuse 
 *
 * @param[out] isp_wb_attr CWF Coordonnées de la position de la source lumineuse 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);

/**
 * @fn int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr)
 *
 * Installation ISP dans AWB de CWF La position de la source lumineuse 
 *
 * @param[in] isp_wb_attr CWF Coordonnées de la position de la source lumineuse 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 * Exemple: 
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
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);

/**
 * @fn int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain)
 *
 * Installation sensor Vous pouvez définir le maximum Again . 
 *
 * @param[in] gain sensor Le maximum qui peut être défini again.0 Moyens 1x，32 Moyens 2x， Etc. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */

typedef struct isp_core_rgb_coefft_wb_attr {
		unsigned short rgb_coefft_wb_r;
		unsigned short rgb_coefft_wb_g;
		unsigned short rgb_coefft_wb_b;

}IMPISPCOEFFTWB;
/**
 * @fn IMP_ISP_Tuning_Awb_GetRgbCoefft(IMPISPCOEFFTWB *isp_core_rgb_coefft_wb_attr)
 *
 * Obtenir sensor AWB RGB Paramètre de décalage de canal. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_Awb_GetRgbCoefft(IMPISPCOEFFTWB *isp_core_rgb_coefft_wb_attr);
/**
 * @fn IMP_ISP_Tuning_Awb_SetRgbCoefft(IMPISPCOEFFTWB *isp_core_rgb_coefft_wb_attr)
 *
 * Installation sensor Peut être mis en place AWB RGB Paramètre de décalage de canal. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 *
 * Exemple: 
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
 * Obtenir sensor Vous pouvez définir le maximum Again . 
 *
 * @param[out] gain sensor Le maximum qui peut être défini again.0 Moyens 1x，32 Moyens 2x， Etc. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain)
 *
 * Installation ISP Le maximum qui peut être défini Dgain . 
 *
 * @param[in] ISP Dgain Le maximum qui peut être défini dgain.0 Moyens 1x，32 Moyens 2x， Etc. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain);

/**
 * @fn int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain)
 *
 * Obtenir ISP Définir le maximum Dgain . 
 *
 * @param[out] ISP Dgain Peut obtenir le plus grand ensemble dgain.0 Moyens 1x，32 Moyens 2x， Etc. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void))
 *
 * Réglez la fonction de perte vidéo. sensor En cas de problème avec la ligne de connexion à la carte mère ， La fonction de rappel définie sera exécutée. 
 *
 * @param[in] cb Rappeler. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void));

/**
 * @fn int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength)
 *
 * Réglez l'intensité de la forte suppression de la lumière. 
 *
 * @param[in] strength Paramètre d'intensité de suppression de la lumière forte . La plage de valeurs est [ 0-10], 0 Indique que la fonction est désactivée. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength);

/**
 * @fn int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio)
 *
 * Installation 3D Intensité de la réduction du bruit. 
 *
 * @param[in] ratio Rapport d'ajustement d'intensité . Si défini sur 90 Moyens définis sur la valeur par défaut 90%. La plage de valeurs est [ 50-150].
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio)
 *
 * Installation 2D Intensité de la réduction du bruit. 
 *
 * @param[in] ratio Rapport d'ajustement d'intensité . Si défini sur 90 Moyens définis sur la valeur par défaut 90%. La plage de valeurs est [ 50-150].
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetDPStrength(uint32_t ratio)
 *
 * Installation DPC force. 
 *
 * @param[in] ratio Rapport d'ajustement d'intensité . Si défini sur 90 Moyens définis sur la valeur par défaut 90%. La plage de valeurs est [ 50-150].
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetDPStrength(uint32_t ratio);

/**
 * ISP ANTIFOG Mode de fonctionnement. 
 */
typedef enum {
	ANTIFOG_DISABLE,			/**< fermer */
	ANTIFOG_STRONG,				/**< Fort */
	ANTIFOG_MEDIUM,				/**< dans */
	ANTIFOG_WEAK,				/**< faible */
}IMPISPAntiFogAttr;

/**
* @fn int IMP_ISP_Tuning_SetAntiFogAttr(IMPISPAntiFogAttr attr)
*
* Installation ANTIFOG Les attributs. 
* @param[in] attr ANTIFOG Paramètre d'attribut 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_SetAntiFogAttr(IMPISPAntiFogAttr attr);

/**
 * ISP EV paramètre. 
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
* @fn int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr)
*
* Obtenir EV Les attributs. 
* @param[out] attr EV Paramètre d'attribut 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);

/**
* @fn int IMP_ISP_Tuning_EnableMovestate(void)
*
* lorsque sensor Pendant l'exercice ， Installation ISP Entrez l'état de l'exercice. 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_EnableMovestate(void);

/**
* @fn int IMP_ISP_Tuning_DisableMovestate(void)
*
* lorsque sensor Retour du mouvement au repos ， Installation ISP Désactivez l'état de mouvement. 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_Tuning_EnableMovestate A été appelé. 
*/
int IMP_ISP_Tuning_DisableMovestate(void);

/**
* Options de sélection de mode 
*/
typedef enum {
	IMPISP_TUNING_MODE_AUTO, /**< Le fonctionnement du module est en mode automatique */
	IMPISP_TUNING_MODE_MANUAL, /**< Le fonctionnement de ce module est en mode manuel */
	IMPISP_TUNING_MODE_RANGE, /**< Le fonctionnement de ce module est le mode de plage de réglage */
	IMPISP_TUNING_MODE_BUTT, /**< Utilisé pour juger de la validité des paramètres ， La taille du paramètre doit être inférieure à cette valeur */
} IMPISPTuningMode;

/**
* Paramètres d'exposition 
*/
typedef struct {
	IMPISPTuningMode mode; /**< Mode d'exposition ， Divisé en mode automatique, mode manuel et mode de plage de réglage */
	uint16_t integration_time; /** Délai d'exposition */
	uint16_t max_integration_time; /**< Temps d'exposition maximum */
} IMPISPITAttr;

/**
 * @fn int IMP_ISP_Tuning_SetIntegrationTime(IMPISPITAttr *itattr)
 *
 * Installation AE paramètre. 
 *
 * @param[in] itattr Paramètres d'exposition. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetIntegrationTime(IMPISPITAttr *itattr);

/**
 * @fn int IMP_ISP_Tuning_GetIntegrationTime(IMPISPITAttr *itattr)
 *
 * Obtenez les paramètres liés à l'exposition. 
 *
 * @param[out] itattr Paramètres d'exposition. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetIntegrationTime(IMPISPITAttr *itattr);

/**
* Informations sur le poids 
*/
typedef struct {
	unsigned char weight[15][15]; /**< Informations de poids de chaque zone [0 ~ 15]*/
} IMPISPWeight;

/**
 * @fn int IMP_ISP_Tuning_SetAeWeight(IMPISPWeight *ae_weight)
 *
 * Installation AE Le poids de la zone statistique. 
 *
 * @param[in] ae_weight Informations de poids pour chaque zone. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetAeWeight(IMPISPWeight *ae_weight);

/**
 * @fn int IMP_ISP_Tuning_GetAeWeight(IMPISPWeight *ae_weight)
 *
 * Obtenir AE Le poids de la zone statistique. 
 *
 * @param[out] ae_weight Informations de poids pour chaque zone. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetAeWeight(IMPISPWeight *ae_weight);

/**
 * @fn int IMP_ISP_Tuning_SetAwbWeight(IMPISPWeight *awb_weight)
 *
 * Installation AWB Le poids de la zone statistique. 
 *
 * @param[in] awb_weight Informations de poids pour chaque zone. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetAwbWeight(IMPISPWeight *awb_weight);

/**
 * @fn int IMP_ISP_Tuning_GetAwbWeight(IMPISPWeight *awb_weight)
 *
 * Obtenir AWB Le poids de la zone statistique. 
 *
 * @param[out] awb_weight Informations de poids pour chaque zone. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetAwbWeight(IMPISPWeight *awb_weight);

/**
* AE Paramètre statistique 
*/
typedef struct {
	unsigned char ae_histhresh[4]; /**< AE Histogramme statistique bin frontière [0 ~ 255]*/
	unsigned short ae_hist[5]; /**< AE Histogramme statistique bin évaluer [0 ~ 65535]*/
	unsigned char ae_stat_nodeh; /**< Nombre de zones statistiques effectives dans le sens horizontal [0 ~ 15]*/
	unsigned char ae_stat_nodev; /**< Nombre de zones statistiques effectives dans le sens vertical [0 ~ 15]*/
} IMPISPAEHist;

/**
 * @fn int IMP_ISP_Tuning_SetAeHist(IMPISPAEHist *ae_hist)
 *
 * Installation AE Paramètres liés aux statistiques. 
 *
 * @param[in] ae_hist AE Paramètres liés aux statistiques. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetAeHist(IMPISPAEHist *ae_hist);

/**
 * @fn int IMP_ISP_Tuning_GetAeHist(IMPISPAEHist *ae_hist)
 *
 * Obtenir AE Statistiques. 
 *
 * @param[out] ae_hist AE Informations statistiques. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetAeHist(IMPISPAEHist *ae_hist);

typedef struct {
	unsigned short ae_sta_zone[15*15];		/**AE Statistiques pour chaque bloc */
} IMPISPAEZone;

/**
 * @fn int IMP_ISP_Tuning_GetAeZone(IMPISPAEZone *ae_zone)
 *
 * Obtenir AE Statistiques pour chaque bloc 
 *
 * @param[out] ae_zone AE La valeur statistique de chaque bloc. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetAeZone(IMPISPAEZone *ae_zone);

/**
* AWB Statistiques 
*/
struct isp_core_awb_sta_info{
	unsigned short r_gain; /**< AWB Pondéré r/g valeur moyenne [0 ~ 4095]*/
	unsigned short b_gain; /**< AWB Pondéré b/g valeur moyenne [0 ~ 4095]*/
	unsigned int awb_sum; /**< Utilisé pour AWB Pixels comptés [0 ~ 4294967295]*/
};
/**
* AWB Mode statistique 
*/
enum isp_core_awb_stats_mode{
	IMPISP_AWB_STATS_LEGACY_MODE = 0, /**< Mode retard */
	IMPISP_AWB_STATS_CURRENT_MODE = 1, /**< Mode actuel */
	IMPISP_AWB_STATS_MODE_BUTT,
};
/**
* AWB Paramètre statistique 
*/
typedef struct {
	struct isp_core_awb_sta_info awb_stat; /**< AWB Statistiques */
	enum isp_core_awb_stats_mode awb_stats_mode; /**< AWB Mode statistique */
	unsigned short awb_whitelevel; /**< AWB Limite supérieure des statistiques [0 ~ 1023]*/
	unsigned short awb_blacklevel; /**< AWB Limite inférieure de la valeur statistique [0 ~ 1023]*/
	unsigned short cr_ref_max; /**< AWB Zone de tache blanche statistique r/g Max [0 ~ 4095]*/
	unsigned short cr_ref_min; /**< AWB Zone de tache blanche statistique r/g Le minimum [0 ~ 4095]*/
	unsigned short cb_ref_max; /**< AWB Zone de tache blanche statistique b/g Max [0 ~ 4095]*/
	unsigned short cb_ref_min; /**< AWB Zone de tache blanche statistique b/g Max [0 ~ 4095]*/
	unsigned char awb_stat_nodeh; /**< Nombre de zones statistiques effectives dans le sens horizontal [0 ~ 15]*/
	unsigned char awb_stat_nodev; /**< Nombre de zones statistiques effectives dans le sens vertical [0 ~ 15]*/
} IMPISPAWBHist;

struct isp_core_wb_zone_info{
	unsigned short red_green; 	/**< r_gain*/
	unsigned short blue_green; 	/**< b_gain*/
	unsigned int sum; 			/**< Nombre de pixels utilisés pour les statistiques */
};

typedef struct {
	struct isp_core_wb_zone_info awb_sta_zone[15][15];		/** AWB Statistiques pour chaque bloc */
} IMPISPAWBZone;

/**
 * @fn int int IMP_ISP_Tuning_GetAwbZone(IMPISPAWBZone *awb_zone)
 *
 * Obtenir AWB La valeur statistique de chaque bloc. 
 *
 * @param[out] awb_zone AWB Statistiques pour chaque bloc 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetAwbZone(IMPISPAWBZone *awb_zone);

/**
 * @fn int IMP_ISP_Tuning_GetAwbHist(IMPISPAWBHist *awb_hist)
 *
 * Obtenir AWB Statistiques. 
 *
 * @param[out] awb_hist AWB Informations statistiques. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetAwbHist(IMPISPAWBHist *awb_hist);

/**
 * @fn int IMP_ISP_Tuning_SetAwbHist(IMPISPAWBHist *awb_hist)
 *
 * Installation AWB Paramètres liés aux statistiques. 
 *
 * @param[in] awb_hist AWB Paramètres liés aux statistiques. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetAwbHist(IMPISPAWBHist *awb_hist);

/**
* AF Statistiques 
*/
struct isp_core_af_sta_info{
	unsigned short af_metrics;/**< AF Statistique principale [0 ~ 65535]*/
	unsigned short af_metrics_alt;/**< AWB Sous-statistiques [0 ~ 65535]*/
	unsigned short af_thresh_read;/**< AF Seuil statistique principal [0 ~ 65535]*/
	unsigned short af_intensity_read;/**< AF Valeur statistique [0 ~ 65535]*/
	unsigned short af_intensity_zone;/**< AF Valeur statistique valeur de la zone de luminosité [0 ~ 65535]*/
	unsigned int af_total_pixels;/**< Utilisé pour AF Pixels comptés [0 ~ 4294967295]*/
	unsigned int af_counted_pixels;/**< Utilisé pour AF Valeur cumulée des pixels comptés [0 ~ 4294967295]*/
};
/**
* AF Paramètre statistique 
*/
typedef struct {
	struct isp_core_af_sta_info af_stat; /**< AF Principales informations statistiques */
	unsigned char af_metrics_shift; /**< AF Principal paramètre de réduction de la valeur statistique [0 ~ 15]*/
	unsigned short af_thresh; /**< AF Seuil statistique principal [0 ~ 65535]*/
	unsigned short af_thresh_alt; /**< AF Seuil statistique secondaire [0 ~ 65535]*/
	unsigned char af_stat_nodeh; /**< Nombre de zones statistiques effectives dans le sens horizontal [0 ~ 15]*/
	unsigned char af_stat_nodev; /**< Nombre de zones statistiques effectives dans le sens vertical [0 · 15]*/
	unsigned char af_np_offset; /**< AF Changement de caractéristique de bruit statistique [0 ~ 255]*/
	unsigned char af_intensity_mode; /**< AF Mode de normalisation de la légèreté [0 ~ 7]*/
	unsigned char af_skipx; /**< direction horizontale AF Statistiques de saut [0 ~ 5]*/
	unsigned char af_offsetx; /**< direction horizontale AF Statistiques de décalage [0 ~ 1]*/
	unsigned char af_skipy; /**< Direction verticale AF Statistiques de saut [0 ~ 6]*/
	unsigned char af_offsety; /**< Direction verticale AF Statistiques de décalage [0 ~ 1]*/
	unsigned char af_scale_top; /**< Moitié inférieure des paramètres réduits [0 ~ 4]*/
	unsigned char af_scale_bottom; /**< Paramètres de réduction de la moitié supérieure [0 ~ 4]*/
} IMPISPAFHist;

/**
 * @fn int IMP_ISP_Tuning_GetAfHist(IMPISPAFHist *af_hist);
 *
 * Obtenir AF Statistiques. 
 *
 * @param[out] af_hist AF Informations statistiques. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetAfHist(IMPISPAFHist *af_hist);

/**
 * @fn int IMP_ISP_Tuning_SetAfHist(IMPISPAFHist *af_hist)
 *
 * Installation AF Paramètres liés aux statistiques. 
 *
 * @param[in] af_hist AF Paramètres liés aux statistiques. 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetAfHist(IMPISPAFHist *af_hist);

/**
 * ISP Wait Frame paramètre. 
 */
typedef struct {
	uint32_t timeout;		/**< temps supplémentaire ， unité ms */
	uint64_t cnt;			/**< Frame statistiques */
}IMPISPWaitFrameAttr;

/**
* @fn int IMP_ISP_Tuning_WaitFrame(IMPISPWaitFrameAttr *attr)
* Attendez la fin du cadre 
*
* @param[out] attr Attendre l'attribut de fin de trame 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_WaitFrame(IMPISPWaitFrameAttr *attr);

typedef enum {
	IMPISP_SHAD_SCALE_L,		/**< Mesh Shading Facteur de zoom 0 */
	IMPISP_SHAD_SCALE_M,		/**< Mesh Shading Facteur de zoom 1 */
	IMPISP_SHAD_SCALE_H,		/**< Mesh Shading Facteur de zoom 2 */
	IMPISP_SHAD_SCALE_U,		/**< Mesh Shading Facteur de zoom 3 */
} IMPISPMeshShadingScale;

/**
* @fn int IMP_ISP_Tuning_SetMeshShadingScale(IMPISPMeshShadingScale scale)
* Installation Mesh Shading Facteur de zoom 
*
* @param[out] scale Mesh Shading Facteur de zoom 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
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
