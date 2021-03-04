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
 * @brief  Unité de traitement du signal d'image. Inclut principalement les paramètres d'effet d'image, le changement de mode et Sensor Enregistrement, ajout, suppression, etc. 
 *
 * ISP Le module n'a rien à voir avec le flux de données ， Pas besoin de continuer Bind， S'applique uniquement aux réglages des paramètres d'effet et Sensor contrôler. 
 *
 * ISP Les étapes d'activation du module sont les suivantes: 
 * @code
 * int ret = 0;
 * ret = IMP_ISP_Open(); // step.1  créer ISP Module 
 * if(ret < 0){
 *     printf("Failed to ISPInit\n");
 *     return -1;
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
 *	.modalias = "xx", //SPI Manette ， Manette sensor Manette struct spi_device_id Manette name Manette 
 *	.bus_num = xx, //SPI Adresse de bus 
 * }
 * ret = IMP_ISP_AddSensor(&sensor); //step.2  ajoute un sensor， Avant cette opération sensor Le pilote a été ajouté au noyau. 
 * if (ret < 0) {
 *     printf("Failed to Register sensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_EnableSensor(void); //step.3  Permettre sensor， à l'heure actuelle sensor Démarrez la sortie des images. 
 * if (ret < 0) {
 *     printf("Failed to EnableSensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_EnableTuning(); //step.4  Démarrez la sortie des images. ISP tuning,  Avant d'appeler ISP Interface de débogage. 
 * if (ret < 0) {
 *     printf("Failed to EnableTuning\n");
 *     return -1;
 * }
 *
 *  Pour l'interface de débogage, veuillez vous référer à ISP Documentation de l'interface de débogage.  //step.5  Débogage des effets. 
 *
 * @endcode
 * ISP Les étapes de désinstallation du module sont les suivantes: 
 * @code
 * int ret = 0;
 * IMPSensorInfo sensor;
 * sensor.name = "xxx";
 * ret = IMP_ISP_DisableTuning(); //step.1  fermer ISP tuning
 * if (ret < 0) {
 *     printf("Failed to disable tuning\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_DisableSensor(); //step.2  fermer sensor， fermer sensor Arrêter la sortie des images; avant cette opération FrameSource Tout doit être fermé. 
 * if (ret < 0) {
 *     printf("Failed to disable sensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_DelSensor(&sensor); //step.3  effacer sensor， Avant cette opération sensor Doit être fermé. 
 * if (ret < 0) {
 *     printf("Failed to disable sensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_Close(); //step.4  Nettoyer ISP Nettoyer ， Tout avant cette opération sensor Doit être supprimé. 
 * if (ret < 0) {
 *     printf("Failed to disable sensor\n");
 *     return -1;
 * }
 * @endcode
 *  Pour plus de méthodes d'utilisation, veuillez vous référer à Samples
 * @{
 */

/**
*  Énumération des types de bus de contrôle de caméra 
*/
typedef enum {
	TX_SENSOR_CONTROL_INTERFACE_I2C = 1,	/**< I2C Bus de contrôle  */
	TX_SENSOR_CONTROL_INTERFACE_SPI,	/**< SPI Bus de contrôle  */
} IMPSensorControlBusType;

/**
*  Le type de bus de contrôle de la caméra est I2C Temps ， La structure des paramètres à configurer 
*/
typedef struct {
	char type[20];		/**< I2C La structure des paramètres à configurer ， Doit être conduit avec la caméra struct i2c_device_id dans name Les variables sont cohérentes  */
	int addr;		/**< I2C Les variables sont cohérentes  */
	int i2c_adapter_id;	/**< I2C Les variables sont cohérentes  */
} IMPI2CInfo;
/**
*  Les variables sont cohérentes SPI Les variables sont cohérentes ， Les variables sont cohérentes 
*/
typedef struct {
	char modalias[32];	/**< SPI Les variables sont cohérentes ， Les variables sont cohérentes struct spi_device_id Les variables sont cohérentes name Les variables sont cohérentes  */
	int bus_num;		/**< SPI Les variables sont cohérentes  */
} IMPSPIInfo;

/**
*  Structure des informations d'enregistrement de la caméra 
*/
typedef struct {
	char name[32];					/**<  Nom de la caméra  */
	IMPSensorControlBusType cbus_type;	/**<  Type de bus de contrôle de caméra  */
	union {
		IMPI2CInfo i2c;				/**< I2C Informations sur le bus  */
		IMPSPIInfo spi;				/**< SPI Informations sur le bus  */
	};
	unsigned short rst_gpio;		/**<  webcam reset Lien d'interface GPIO， Remarque: ce paramètre n'est pas activé maintenant  */
	unsigned short pwdn_gpio;		/**<  Remarque: ce paramètre n'est pas activé maintenant power down Remarque: ce paramètre n'est pas activé maintenant GPIO， Remarque: ce paramètre n'est pas activé maintenant  */
	unsigned short power_gpio;		/**<  Remarque: ce paramètre n'est pas activé maintenant power  Remarque: ce paramètre n'est pas activé maintenant GPIO， Remarque: ce paramètre n'est pas activé maintenant  */
} IMPSensorInfo;

/**
 * @fn int IMP_ISP_Open(void)
 *
 *  allumer ISP allumer 
 *
 * @param  non 
 *
 * @retval 0  Succès 
 * @retval  non- 0  échec ， Renvoyer le code d'erreur 
 *
 * @remark  Renvoyer le code d'erreur ISP Renvoyer le code d'erreur ， Prêt à ISP Ajouter à sensor， Et allumer ISP Fonction de débogage d'effet. 
 *
 * @attention  Cette fonction doit être ajoutée sensor A été appelé avant. 
 */
int IMP_ISP_Open(void);

/**
 * @fn int IMP_ISP_Close(void)
 *
 *  A été appelé avant. ISP A été appelé avant. 
 *
 * @param  A été appelé avant. 
 *
 * @retval 0  A été appelé avant. 
 * @retval  A été appelé avant. 0  A été appelé avant. ， A été appelé avant. 
 *
 * @remark ISP A été appelé avant. ，ISP Le module ne fonctionne plus. 
 *
 * @attention  Avant d'utiliser cette fonction ， Doit garantir tout FrameSource Et la fonction de débogage d'effet a été fermée ， tout sensor Ont été désinstallés .
 */
int IMP_ISP_Close(void);

/**
 * @fn int IMP_ISP_AddSensor(IMPSensorInfo *pinfo)
 *
 *  Ont été désinstallés sensor， Habitué ISP Le module fournit la source de données 
 *
 * @param[in] pinfo  Besoin d'ajouter sensor Pointeur d'information 
 *
 * @retval 0  Pointeur d'information 
 * @retval  Pointeur d'information 0  Pointeur d'information ， Pointeur d'information 
 *
 * @remark  Ajouter une caméra ， Utilisé pour fournir des images. 
 *
 * @attention  Utilisé pour fournir des images. ， Il faut s'assurer que le pilote de la caméra a été enregistré dans le noyau .
 */
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);

/**
 * @fn int IMP_ISP_DelSensor(IMPSensorInfo *pinfo)
 *
 *  Supprimer un sensor
 *
 * @param[in] pinfo  Doit être supprimé sensor Doit être supprimé 
 *
 * @retval 0  Doit être supprimé 
 * @retval  Doit être supprimé 0  Doit être supprimé ， Doit être supprimé 
 *
 * @remark  Supprimer une caméra. 
 *
 * @attention  Supprimer une caméra. ， Il faut s'assurer que la caméra a cessé de fonctionner ， Appelé IMP_ISP_DisableSensor fonction .
 */
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);

/**
 * @fn int IMP_ISP_EnableSensor(void)
 *
 *  Activer un sensor
 *
 * @param  Activer un 
 *
 * @retval 0  Activer un 
 * @retval  Activer un 0  Activer un ， Activer un 
 *
 * @remark  Activer une caméra ， Faites-le commencer à transférer des images ,  tel FrameSource Pour sortir l'image ， à la fois ISP Ce n'est qu'alors que l'effet peut être débogué. 
 *
 * @attention  Ce n'est qu'alors que l'effet peut être débogué. ， Il faut s'assurer que la caméra a été ajoutée ISP Il faut s'assurer que la caméra a été ajoutée .
 */
int IMP_ISP_EnableSensor(void);

/**
 * @fn int IMP_ISP_DisableSensor(void)
 *
 *  Désactiver un sensor
 *
 * @param  Désactiver un 
 *
 * @retval 0  Désactiver un 
 * @retval  Désactiver un 0  Désactiver un ， Désactiver un 
 *
 * @remark  Désactiver une caméra ， Arrêter de transmettre des images ,  Arrêter de transmettre des images FrameSource Impossible de sortir l'image ， Impossible de sortir l'image ISP L'effet ne peut pas non plus être débogué. 
 *
 * @attention  L'effet ne peut pas non plus être débogué. ， L'effet ne peut pas non plus être débogué. FrameSource Ont arrêté de sortir des images ， Dans le même temps, le débogage des effets est également à l'état désactivé .
 */
int IMP_ISP_DisableSensor(void);

/**
 * @fn int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value)
 *
 *  Installation sensor La valeur d'un registre 
 *
 * @param[in] reg  Adresse d'inscription 
 *
 * @param[in] value  Enregistrer la valeur 
 *
 * @retval 0  Enregistrer la valeur 
 * @retval  Enregistrer la valeur 0  Enregistrer la valeur ， Enregistrer la valeur 
 *
 * @remark  Vous pouvez en définir un directement sensor La valeur du registre. 
 *
 * @attention  La valeur du registre. ， Il faut s'assurer que la caméra a été activée .
 */
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value);

/**
 * @fn int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *value)
 *
 *  Obtenir sensor Obtenir 
 *
 * @param[in] reg  Obtenir 
 *
 * @param[in] value  Pointeur pour enregistrer la valeur 
 *
 * @retval 0  Pointeur pour enregistrer la valeur 
 * @retval  Pointeur pour enregistrer la valeur 0  Pointeur pour enregistrer la valeur ， Pointeur pour enregistrer la valeur 
 *
 * @remark  Vous pouvez en obtenir un directement sensor Vous pouvez en obtenir un directement 
 *
 * @attention  Vous pouvez en obtenir un directement ， Vous pouvez en obtenir un directement .
 */
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *value);

typedef enum {
	IMPISP_TUNING_OPS_MODE_DISABLE,			/**<  Désactiver la fonction du module  */
	IMPISP_TUNING_OPS_MODE_ENABLE,			/**<  Activer la fonction du module  */
	IMPISP_TUNING_OPS_MODE_BUTT,			/**<  Utilisé pour juger de la validité des paramètres ， La taille du paramètre doit être inférieure à cette valeur  */
} IMPISPTuningOpsMode;

typedef enum {
	IMPISP_TUNING_OPS_TYPE_AUTO,			/**<  Le fonctionnement du module est en mode automatique  */
	IMPISP_TUNING_OPS_TYPE_MANUAL,			/**<  Le fonctionnement de ce module est en mode manuel  */
	IMPISP_TUNING_OPS_TYPE_BUTT,			/**<  Le fonctionnement de ce module est en mode manuel ， Le fonctionnement de ce module est en mode manuel  */
} IMPISPTuningOpsType;

/**
 * @fn int IMP_ISP_EnableTuning(void)
 *
 *  Le fonctionnement de ce module est en mode manuel ISP Fonction de débogage d'effet 
 *
 * @param  Fonction de débogage d'effet 
 *
 * @retval 0  Fonction de débogage d'effet 
 * @retval  Fonction de débogage d'effet 0  Fonction de débogage d'effet ， Fonction de débogage d'effet 
 *
 * @attention  Fonction de débogage d'effet ， Doit garantir IMP_ISP_EnableSensor A été exécuté et renvoyé avec succès .
 */
int IMP_ISP_EnableTuning(void);

/**
 * @fn int IMP_ISP_DisableTuning(void)
 *
 *  Désactiver ISP Désactiver 
 *
 * @param  Désactiver 
 *
 * @retval 0  Désactiver 
 * @retval  Désactiver 0  Désactiver ， Désactiver 
 *
 * @attention  Désactiver ， Il faut s'assurer que le sensor antérieur à ， Désactiver d'abord ISP Débogage d'effet (c'est-à-dire, appelez cette fonction) .
 */
int IMP_ISP_DisableTuning(void);

/**
 * @fn int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den)
 *
 *  Définir la fréquence d'images de sortie de la caméra 
 *
 * @param[in] fps_num  Définir le paramètre du numérateur de la fréquence d'images 
 * @param[in] fps_den  Définir le paramètre dénominateur de la fréquence d'images 
 *
 * @retval 0  Définir le paramètre dénominateur de la fréquence d'images 
 * @retval  Définir le paramètre dénominateur de la fréquence d'images 0  Définir le paramètre dénominateur de la fréquence d'images ， Définir le paramètre dénominateur de la fréquence d'images 
 *
 * @attention  Définir le paramètre dénominateur de la fréquence d'images ， Définir le paramètre dénominateur de la fréquence d'images IMP_ISP_EnableSensor  avec  IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);

/**
 * @fn int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den)
 *
 *  Obtenir la fréquence d'images de sortie de la caméra 
 *
 * @param[in] fps_num  Obtenez un pointeur sur les paramètres moléculaires de la fréquence d'images 
 * @param[in] fps_den  Obtenir un pointeur vers le paramètre du dénominateur de la fréquence d'images 
 *
 * @retval 0  Obtenir un pointeur vers le paramètre du dénominateur de la fréquence d'images 
 * @retval  Obtenir un pointeur vers le paramètre du dénominateur de la fréquence d'images 0  Obtenir un pointeur vers le paramètre du dénominateur de la fréquence d'images ， Obtenir un pointeur vers le paramètre du dénominateur de la fréquence d'images 
 *
 * @attention  Obtenir un pointeur vers le paramètre du dénominateur de la fréquence d'images ， Obtenir un pointeur vers le paramètre du dénominateur de la fréquence d'images IMP_ISP_EnableSensor  Obtenir un pointeur vers le paramètre du dénominateur de la fréquence d'images  IMP_ISP_EnableTuning Obtenir un pointeur vers le paramètre du dénominateur de la fréquence d'images 
 * @attention  Cette fonction doit être appelée pour obtenir la fréquence d'images par défaut de la caméra avant que le canal d'image ne soit activé pour démarrer la transmission des données. 
 */
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);

/**
 * ISP Structure des paramètres de propriété anti-scintillement. 
 */
typedef enum {
	IMPISP_ANTIFLICKER_DISABLE,	/**<  Structure des paramètres de propriété anti-scintillement. ISP Fonction anti-flash  */
	IMPISP_ANTIFLICKER_50HZ,	/**<  Fonction anti-flash ISP Fonction anti-flash ,  Et réglez la fréquence sur 50HZ */
	IMPISP_ANTIFLICKER_60HZ,	/**<  Et réglez la fréquence sur ISP Et réglez la fréquence sur ， Et réglez la fréquence sur 60HZ */
	IMPISP_ANTIFLICKER_BUTT,	/**<  Et réglez la fréquence sur ， Et réglez la fréquence sur  */
} IMPISPAntiflickerAttr;

/**
 * @fn int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr)
 *
 *  Et réglez la fréquence sur ISP Propriétés anti-flash 
 *
 * @param[in] attr  Définir la valeur du paramètre 
 *
 * @retval 0  Définir la valeur du paramètre 
 * @retval  Définir la valeur du paramètre 0  Définir la valeur du paramètre ， Définir la valeur du paramètre 
 *
 * @attention  Définir la valeur du paramètre ， Définir la valeur du paramètre ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);

/**
 * @fn int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr)
 *
 *  obtenir ISP obtenir 
 *
 * @param[in] pattr  Obtenir le pointeur de valeur de paramètre 
 *
 * @retval 0  Obtenir le pointeur de valeur de paramètre 
 * @retval  Obtenir le pointeur de valeur de paramètre 0  Obtenir le pointeur de valeur de paramètre ， Obtenir le pointeur de valeur de paramètre 
 *
 * @attention  Obtenir le pointeur de valeur de paramètre ， Obtenir le pointeur de valeur de paramètre ISP Obtenir le pointeur de valeur de paramètre .
 */
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);

/**
 * ISP  Mode de fonctionnement du module de compression de plage dynamique. 
 */
typedef enum {
	IMPISP_DRC_MANUAL,				/**< ISP  Mode manuel du module de compression de plage dynamique  */
	IMPISP_DRC_UNLIMIT,				/**< ISP  Mode de compression le plus élevé du module de compression de plage dynamique  */
	IMPISP_DRC_HIGH,				/**< ISP  Mode de compression élevée du module de compression de plage dynamique  */
	IMPISP_DRC_MEDIUM,				/**< ISP  Mode de compression dans le module de compression de plage dynamique  */
	IMPISP_DRC_LOW,					/**< ISP  Mode de compression basse du module de compression de plage dynamique  */
	IMPISP_DRC_DISABLE,				/**< ISP  Le module de compression de plage dynamique n'est pas activé  */
} IMPISPDrcMode;

/**
 * ISP  Paramètres d'attribut du module de compression de plage dynamique. 
 */
typedef struct {
	IMPISPDrcMode mode;				/**< ISP  Sélection du mode de fonctionnement du module de compression de plage dynamique  */
	unsigned char drc_strength;			/**<  Valeur cible définie en mode manuel ， La plage de valeurs est [0, 0xff] */
	unsigned char slop_max;				/**<  Paramètres de contrôle de la force ， Paramètres de contrôle de la force [0, oxff] */
	unsigned char slop_min;				/**<  Paramètres de contrôle de la force ， Paramètres de contrôle de la force [0, oxff] */
	unsigned short black_level;			/**< DRC Valeur de pixel minimale améliorée ， Valeur de pixel minimale améliorée [0, oxfff] */
	unsigned short white_level;			/**< DRC Valeur de pixel maximale améliorée ， Valeur de pixel maximale améliorée [0, oxfff] */
} IMPISPDrcAttr;

/**
 * @fn int IMP_ISP_Tuning_SetRawDRC(IMPISPDrcAttr *pinfo)
 *
 *  Valeur de pixel maximale améliorée ISP RAW Figure paramètres du module de compression de plage dynamique 
 *
 * @param[in] pinfo  Pointeur de paramètre de plage dynamique 
 *
 * @retval 0  Pointeur de paramètre de plage dynamique 
 * @retval  Pointeur de paramètre de plage dynamique 0  Pointeur de paramètre de plage dynamique ， Pointeur de paramètre de plage dynamique 
 *
 * @remark  Pointeur de paramètre de plage dynamique RGB RAW Type d'opération de compression de plage dynamique graphique ， force ， Les valeurs de pixel maximum et minimum qui doivent être améliorées. 
 *
 * @attention  Les valeurs de pixel maximum et minimum qui doivent être améliorées. ， Les valeurs de pixel maximum et minimum qui doivent être améliorées. ISP Les valeurs de pixel maximum et minimum qui doivent être améliorées. .
 */
int IMP_ISP_Tuning_SetRawDRC(IMPISPDrcAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo)
 *
 *  Les valeurs de pixel maximum et minimum qui doivent être améliorées. ISP RAW Les valeurs de pixel maximum et minimum qui doivent être améliorées. 
 *
 * @param[in] pinfo  Les valeurs de pixel maximum et minimum qui doivent être améliorées. 
 *
 * @retval 0  Les valeurs de pixel maximum et minimum qui doivent être améliorées. 
 * @retval  Les valeurs de pixel maximum et minimum qui doivent être améliorées. 0  Les valeurs de pixel maximum et minimum qui doivent être améliorées. ， Les valeurs de pixel maximum et minimum qui doivent être améliorées. 
 *
 * @remark  Les valeurs de pixel maximum et minimum qui doivent être améliorées. RGB RAW Les valeurs de pixel maximum et minimum qui doivent être améliorées. ， Les valeurs de pixel maximum et minimum qui doivent être améliorées. ， Les valeurs de pixel maximum et minimum qui doivent être améliorées. 
 *
 * @attention  Les valeurs de pixel maximum et minimum qui doivent être améliorées. ， Les valeurs de pixel maximum et minimum qui doivent être améliorées. ISP Les valeurs de pixel maximum et minimum qui doivent être améliorées. .
 */
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);

/**
 * ISP  Paramètres d'attribut du module de réduction du bruit spatial. 
 */
typedef struct {
	IMPISPTuningOpsMode enable;			/**<  Activer la fonction de réduction du bruit spatial  */
	IMPISPTuningOpsType type;				/**<  Type d'opération de la fonction de réduction du bruit spatial ， Automatique ou manuel  */
	unsigned char sinter_strength;				/**<  Intensité de la réduction du bruit spatial ， Le mode manuel est efficace ， Le mode manuel est efficace [0, 0xff] */
} IMPISPSinterDenoiseAttr;

/**
 * ISP  Mode de fonctionnement du module de réduction du bruit dans le domaine temporel. 
 */
typedef enum {
	IMPISP_TEMPER_DISABLE,				/**< ISP  Le module de réduction du bruit dans le domaine temporel n'est pas activé  */
	IMPISP_TEMPER_AUTO,					/**< ISP  Mode automatique du module de réduction du bruit dans le domaine temporel  */
	IMPISP_TEMPER_MANUAL,				/**< ISP  Mode manuel du module de réduction du bruit dans le domaine temporel  */
} IMPISPTemperMode;

/**
 * ISP  Paramètres d'attribut du module de réduction du bruit dans le domaine temporel. 
 */
typedef struct imp_isp_temper_denoise_attr {
	IMPISPTemperMode type;					/**<  Type d'opération de la fonction de réduction du bruit dans le domaine temporel ， Type d'opération de la fonction de réduction du bruit dans le domaine temporel ， Type d'opération de la fonction de réduction du bruit dans le domaine temporel  */
	unsigned char temper_strength;				/**<  Intensité de la réduction du bruit dans le domaine temporel ， Intensité de la réduction du bruit dans le domaine temporel ， Intensité de la réduction du bruit dans le domaine temporel [0, 0xff] */
} IMPISPTemperDenoiseAttr;


/**
 * @fn int IMP_ISP_Tuning_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo)
 *
 *  Intensité de la réduction du bruit dans le domaine temporel ISP  Paramètres du module de réduction du bruit spatial 
 *
 * @param[in] pinfo  Pointeur de paramètre de réduction du bruit dans le domaine temporel 
 *
 * @retval 0  Pointeur de paramètre de réduction du bruit dans le domaine temporel 
 * @retval  Pointeur de paramètre de réduction du bruit dans le domaine temporel 0  Pointeur de paramètre de réduction du bruit dans le domaine temporel ， Pointeur de paramètre de réduction du bruit dans le domaine temporel 
 *
 * @remark  Définissez les paramètres de correction du module de réduction du bruit spatial. 
 *
 * @attention  Définissez les paramètres de correction du module de réduction du bruit spatial. ， Définissez les paramètres de correction du module de réduction du bruit spatial. ISP Définissez les paramètres de correction du module de réduction du bruit spatial. .
 */
int IMP_ISP_Tuning_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo)
 *
 *  Définissez les paramètres de correction du module de réduction du bruit spatial. ISP  Définissez les paramètres de correction du module de réduction du bruit spatial. 
 *
 * @param[in] pinfo  Pointeur de paramètre de réduction du bruit spatial 
 *
 * @retval 0  Pointeur de paramètre de réduction du bruit spatial 
 * @retval  Pointeur de paramètre de réduction du bruit spatial 0  Pointeur de paramètre de réduction du bruit spatial ， Pointeur de paramètre de réduction du bruit spatial 
 *
 * @remark  Obtenez les paramètres de correction du module de réduction du bruit spatial. 
 *
 * @attention  Obtenez les paramètres de correction du module de réduction du bruit spatial. ， Obtenez les paramètres de correction du module de réduction du bruit spatial. ISP Obtenez les paramètres de correction du module de réduction du bruit spatial. .
 */
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
#if 0
/**
* @fn int IMP_ISP_Tuning_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
*
*  Obtenez les paramètres de correction du module de réduction du bruit spatial. ISP  Mode du module de réduction du bruit dans le domaine temporel 
*
* @param[in] pinfo  Mode du module de réduction du bruit dans le domaine temporel 
*
* @retval 0  Mode du module de réduction du bruit dans le domaine temporel 
* @retval  Mode du module de réduction du bruit dans le domaine temporel 0  Mode du module de réduction du bruit dans le domaine temporel ， Mode du module de réduction du bruit dans le domaine temporel 
*
* @remark  Définissez les paramètres de mode du module de réduction du bruit dans le domaine temporel ， Le mode automatique par défaut. 
*
* @attention  Le mode automatique par défaut. ， Le mode automatique par défaut. ISP Le mode automatique par défaut. .
*/
int IMP_ISP_Tuning_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
#endif
/**
 * @fn int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo)
 *
 *  Le mode automatique par défaut. ISP  Paramètres du module de réduction du bruit dans le domaine temporel 
 *
 * @param[in] pinfo  Paramètres du module de réduction du bruit dans le domaine temporel 
 *
 * @retval 0  Paramètres du module de réduction du bruit dans le domaine temporel 
 * @retval  Paramètres du module de réduction du bruit dans le domaine temporel 0  Paramètres du module de réduction du bruit dans le domaine temporel ， Paramètres du module de réduction du bruit dans le domaine temporel 
 *
 * @remark  Définissez les paramètres de correction du module de réduction du bruit dans le domaine temporel ， Le module est activé par défaut, car le module nécessite de la mémoire supplémentaire ， Veuillez fermer le module si vous n'en avez pas besoin ， La mémoire est libérée une fois fermée ， Ne peut plus être ouvert. 
 *
 * @attention  Ne peut plus être ouvert. ， Ne peut plus être ouvert. ISP Ne peut plus être ouvert. .
 */
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo)
 *
 *  Ne peut plus être ouvert. ISP  Ne peut plus être ouvert. 
 *
 * @param[in] pinfo  Pointeur de paramètre du module de réduction du bruit dans le domaine temporel 
 *
 * @retval 0  Pointeur de paramètre du module de réduction du bruit dans le domaine temporel 
 * @retval  Pointeur de paramètre du module de réduction du bruit dans le domaine temporel 0  Pointeur de paramètre du module de réduction du bruit dans le domaine temporel ， Pointeur de paramètre du module de réduction du bruit dans le domaine temporel 
 *
 * @remark  Obtenez les paramètres de correction du module de réduction du bruit dans le domaine temporel. 
 *
 * @attention  Obtenez les paramètres de correction du module de réduction du bruit dans le domaine temporel. ， Obtenez les paramètres de correction du module de réduction du bruit dans le domaine temporel. ISP Obtenez les paramètres de correction du module de réduction du bruit dans le domaine temporel. .
 */
int IMP_ISP_Tuning_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode)
 *
 *  Obtenez les paramètres de correction du module de réduction du bruit dans le domaine temporel. ISP  Si le module dynamique large est activé 
 *
 * @param[in] mode  Paramètres de module dynamiques larges 
 *
 * @retval 0  Paramètres de module dynamiques larges 
 * @retval  Paramètres de module dynamiques larges 0  Paramètres de module dynamiques larges ， Paramètres de module dynamiques larges 
 *
 * @remark  Définir les paramètres d'étalonnage du module dynamique large ， Définir les paramètres d'étalonnage du module dynamique large ， Définir les paramètres d'étalonnage du module dynamique large ， Définir les paramètres d'étalonnage du module dynamique large ， Définir les paramètres d'étalonnage du module dynamique large 
 *
 * @attention  Définir les paramètres d'étalonnage du module dynamique large ， Définir les paramètres d'étalonnage du module dynamique large ISP Définir les paramètres d'étalonnage du module dynamique large .
 */
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetWDRAttr(IMPISPTuningOpsMode *pmode)
 *
 *  Définir les paramètres d'étalonnage du module dynamique large ISP  État actuel du module dynamique large 
 *
 * @param[in] pmode  Large pointeur de paramètres de module dynamique 
 *
 * @retval 0  Large pointeur de paramètres de module dynamique 
 * @retval  Large pointeur de paramètres de module dynamique 0  Large pointeur de paramètres de module dynamique ， Large pointeur de paramètres de module dynamique 
 *
 * @remark  Obtenez les paramètres de correction du module dynamique large. 
 *
 * @attention  Obtenez les paramètres de correction du module dynamique large. ， Obtenez les paramètres de correction du module dynamique large. ISP Obtenez les paramètres de correction du module dynamique large. .
 */
int IMP_ISP_Tuning_GetWDRAttr(IMPISPTuningOpsMode *pmode);

/**
 * ISP  Fonction d'extension complète ， Sélection du mode scène. 
 */
typedef enum {
	IMPISP_SCENE_MODE_AUTO = 0,					/**<  Mode automatique  */
	IMPISP_SCENE_MODE_BEACH_SNOW = 2,				/**<  Mode scène de neige sur la plage  */
	IMPISP_SCENE_MODE_CANDLE_LIGHT = 3,				/**<  Mode lumière bougie  */
	IMPISP_SCENE_MODE_DAWN_DUSK = 4,				/**<  Mode soirée  */
	IMPISP_SCENE_MODE_FALL_COLORS = 5,				/**<  Mode scène d'automne  */
	IMPISP_SCENE_MODE_FIREWORKS = 6,				/**<  Mode scène de feux d'artifice  */
	IMPISP_SCENE_MODE_LANDSCAPE = 7,				/**<  Mode paysage  */
	IMPISP_SCENE_MODE_NIGHT = 8,					/**<  Mode nuit  */
	IMPISP_SCENE_MODE_PARTY_INDOOR = 9,				/**<  Mode fête en intérieur  */
	IMPISP_SCENE_MODE_SPORTS = 11,					/**<  Mode sport  */
	IMPISP_SCENE_MODE_SUNSET = 12,					/**<  Mode coucher de soleil  */
	IMPISP_SCENE_MODE_TEXT = 13,					/**<  Mode texte  */
	IMPISP_SCENE_MODE_NIGHT_PORTRAIT = 14,				/**<  Mode portrait de nuit  */
} IMPISPSceneMode;

/**
 * @fn int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode)
 *
 *  Mode portrait de nuit ISP  Mode scène d'effets complet 
 *
 * @param[in] mode  Paramètres du mode scène d'effet 
 *
 * @retval 0  Paramètres du mode scène d'effet 
 * @retval  Paramètres du mode scène d'effet 0  Paramètres du mode scène d'effet ， Paramètres du mode scène d'effet 
 *
 * @attention  Paramètres du mode scène d'effet ， Paramètres du mode scène d'effet ISP Paramètres du mode scène d'effet .
 */
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetSceneMode(IMPISPSceneMode *pmode)
 *
 *  Paramètres du mode scène d'effet ISP  Paramètres du mode scène d'effet 
 *
 * @param[in] pmode  Pointeur de paramètre du mode scène d'effet 
 *
 * @retval 0  Pointeur de paramètre du mode scène d'effet 
 * @retval  Pointeur de paramètre du mode scène d'effet 0  Pointeur de paramètre du mode scène d'effet ， Pointeur de paramètre du mode scène d'effet 
 *
 * @attention  Pointeur de paramètre du mode scène d'effet ， Pointeur de paramètre du mode scène d'effet ISP Pointeur de paramètre du mode scène d'effet .
 */
int IMP_ISP_Tuning_GetSceneMode(IMPISPSceneMode *pmode);

/**
 * ISP  Pointeur de paramètre du mode scène d'effet ， Sélection du mode couleur. 
 */
typedef enum {
	IMPISP_COLORFX_MODE_AUTO = 0,				/**<  Sélection du mode couleur.  */
	IMPISP_COLORFX_MODE_BW = 1,				/**<  Mode noir et blanc  */
	IMPISP_COLORFX_MODE_SEPIA = 2,				/**<  Mode sépia  */
	IMPISP_COLORFX_MODE_NEGATIVE = 3,			/**<  Mode couleur inversé  */
	IMPISP_COLORFX_MODE_VIVID = 9,				/**<  Mode vif  */
} IMPISPColorfxMode;

/**
 * @fn int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode)
 *
 *  Mode vif ISP  Mode couleur multi-effets 
 *
 * @param[in] mode  Paramètres du mode couleur 
 *
 * @retval 0  Paramètres du mode couleur 
 * @retval  Paramètres du mode couleur 0  Paramètres du mode couleur ， Paramètres du mode couleur 
 *
 * @attention  Paramètres du mode couleur ， Paramètres du mode couleur ISP Paramètres du mode couleur .
 */
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetColorfxMode(IMPISPColorfxMode *pmode)
 *
 *  Paramètres du mode couleur ISP  Paramètres du mode couleur 
 *
 * @param[in] pmode  Pointeur de paramètre de mode couleur 
 *
 * @retval 0  Pointeur de paramètre de mode couleur 
 * @retval  Pointeur de paramètre de mode couleur 0  Pointeur de paramètre de mode couleur ， Pointeur de paramètre de mode couleur 
 *
 * @attention  Pointeur de paramètre de mode couleur ， Pointeur de paramètre de mode couleur ISP Pointeur de paramètre de mode couleur .
 */
int IMP_ISP_Tuning_GetColorfxMode(IMPISPColorfxMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetBrightness(unsigned char bright)
 *
 *  Pointeur de paramètre de mode couleur ISP  Luminosité d'image complète 
 *
 * @param[in] bright  Paramètre de luminosité de l'image 
 *
 * @retval 0  Paramètre de luminosité de l'image 
 * @retval  Paramètre de luminosité de l'image 0  Paramètre de luminosité de l'image ， Paramètre de luminosité de l'image 
 *
 * @remark  La valeur par défaut est 128， plus que le 128 Augmenter la luminosité ， Moins que 128 Diminuez la luminosité. 
 *
 * @attention  Diminuez la luminosité. ， Diminuez la luminosité. ISP Diminuez la luminosité. .
 */
int IMP_ISP_Tuning_SetBrightness(unsigned char bright);

/**
 * @fn int IMP_ISP_Tuning_GetBrightness(unsigned char *pbright)
 *
 *  Diminuez la luminosité. ISP  Diminuez la luminosité. 
 *
 * @param[in] bright  Pointeur de paramètre de luminosité de l'image 
 *
 * @retval 0  Pointeur de paramètre de luminosité de l'image 
 * @retval  Pointeur de paramètre de luminosité de l'image 0  Pointeur de paramètre de luminosité de l'image ， Pointeur de paramètre de luminosité de l'image 
 *
 * @remark  Pointeur de paramètre de luminosité de l'image 128， Pointeur de paramètre de luminosité de l'image 128 Pointeur de paramètre de luminosité de l'image ， Pointeur de paramètre de luminosité de l'image 128 Pointeur de paramètre de luminosité de l'image 
 *
 * @attention  Pointeur de paramètre de luminosité de l'image ， Pointeur de paramètre de luminosité de l'image ISP Pointeur de paramètre de luminosité de l'image .
 */
int IMP_ISP_Tuning_GetBrightness(unsigned char *pbright);

/**
 * @fn int IMP_ISP_Tuning_SetContrast(unsigned char contrast)
 *
 *  Pointeur de paramètre de luminosité de l'image ISP  Contraste d'image complet 
 *
 * @param[in] contrast  Paramètre de contraste de l'image 
 *
 * @retval 0  Paramètre de contraste de l'image 
 * @retval  Paramètre de contraste de l'image 0  Paramètre de contraste de l'image ， Paramètre de contraste de l'image 
 *
 * @remark  Paramètre de contraste de l'image 128， Paramètre de contraste de l'image 128 Augmenter le contraste ， Augmenter le contraste 128 Réduisez le contraste. 
 *
 * @attention  Réduisez le contraste. ， Réduisez le contraste. ISP Réduisez le contraste. .
 */
int IMP_ISP_Tuning_SetContrast(unsigned char contrast);

/**
 * @fn int IMP_ISP_Tuning_GetContrast(unsigned char *pcontrast)
 *
 *  Réduisez le contraste. ISP  Réduisez le contraste. 
 *
 * @param[in] contrast  Pointeur de paramètre de contraste de l'image 
 *
 * @retval 0  Pointeur de paramètre de contraste de l'image 
 * @retval  Pointeur de paramètre de contraste de l'image 0  Pointeur de paramètre de contraste de l'image ， Pointeur de paramètre de contraste de l'image 
 *
 * @remark  Pointeur de paramètre de contraste de l'image 128， Pointeur de paramètre de contraste de l'image 128 Pointeur de paramètre de contraste de l'image ， Pointeur de paramètre de contraste de l'image 128 Pointeur de paramètre de contraste de l'image 
 *
 * @attention  Pointeur de paramètre de contraste de l'image ， Pointeur de paramètre de contraste de l'image ISP Pointeur de paramètre de contraste de l'image .
 */
int IMP_ISP_Tuning_GetContrast(unsigned char *pcontrast);

 /**
 * @fn int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness)
 *
 *  Pointeur de paramètre de contraste de l'image ISP  Netteté d'image complète 
 *
 * @param[in] sharpness  Valeur du paramètre de netteté de l'image 
 *
 * @retval 0  Valeur du paramètre de netteté de l'image 
 * @retval  Valeur du paramètre de netteté de l'image 0  Valeur du paramètre de netteté de l'image ， Valeur du paramètre de netteté de l'image 
 *
 * @remark  Valeur du paramètre de netteté de l'image 128， Valeur du paramètre de netteté de l'image 128 Augmenter la netteté ， Augmenter la netteté 128 Réduisez la netteté. 
 *
 * @attention  Réduisez la netteté. ， Réduisez la netteté. ISP Réduisez la netteté. .
 */
int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness);

/**
 * @fn int IMP_ISP_Tuning_GetSharpness(unsigned char *psharpness)
 *
 *  Réduisez la netteté. ISP  Réduisez la netteté. 
 *
 * @param[in] sharpness  Pointeur de paramètre de netteté de l'image 
 *
 * @retval 0  Pointeur de paramètre de netteté de l'image 
 * @retval  Pointeur de paramètre de netteté de l'image 0  Pointeur de paramètre de netteté de l'image ， Pointeur de paramètre de netteté de l'image 
 *
 * @remark  Pointeur de paramètre de netteté de l'image 128， Pointeur de paramètre de netteté de l'image 128 Pointeur de paramètre de netteté de l'image ， Pointeur de paramètre de netteté de l'image 128 Pointeur de paramètre de netteté de l'image 
 *
 * @attention  Pointeur de paramètre de netteté de l'image ， Pointeur de paramètre de netteté de l'image ISP Pointeur de paramètre de netteté de l'image .
 */
int IMP_ISP_Tuning_GetSharpness(unsigned char *psharpness);

/**
 * @fn int IMP_ISP_Tuning_SetSaturation(unsigned char sat)
 *
 *  Pointeur de paramètre de netteté de l'image ISP  Saturation complète de l'image avec effet 
 *
 * @param[in] sat  Valeur du paramètre de saturation de l'image 
 *
 * @retval 0  Valeur du paramètre de saturation de l'image 
 * @retval  Valeur du paramètre de saturation de l'image 0  Valeur du paramètre de saturation de l'image ， Valeur du paramètre de saturation de l'image 
 *
 * @remark  Valeur du paramètre de saturation de l'image 128， Valeur du paramètre de saturation de l'image 128 Augmenter la saturation ， Augmenter la saturation 128 Diminue la saturation. 
 *
 * @attention  Diminue la saturation. ， Diminue la saturation. ISP Diminue la saturation. .
 */
int IMP_ISP_Tuning_SetSaturation(unsigned char sat);

/**
 * @fn int IMP_ISP_Tuning_GetSaturation(unsigned char *psat)
 *
 *  Diminue la saturation. ISP  Diminue la saturation. 
 *
 * @param[in] sat  Pointeur de paramètre de saturation de l'image 
 *
 * @retval 0  Pointeur de paramètre de saturation de l'image 
 * @retval  Pointeur de paramètre de saturation de l'image 0  Pointeur de paramètre de saturation de l'image ， Pointeur de paramètre de saturation de l'image 
 *
 * @remark  Pointeur de paramètre de saturation de l'image 128， Pointeur de paramètre de saturation de l'image 128 Pointeur de paramètre de saturation de l'image ， Pointeur de paramètre de saturation de l'image 128 Pointeur de paramètre de saturation de l'image 
 *
 * @attention  Pointeur de paramètre de saturation de l'image ， Pointeur de paramètre de saturation de l'image ISP Pointeur de paramètre de saturation de l'image .
 */
int IMP_ISP_Tuning_GetSaturation(unsigned char *psat);
#if 0
/**
 * @fn int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode)
 *
 *  contourne ISP Manipulation des modules ， Sortie directe sensor image 
 *
 * @param[in] mode  Que ce soit pour contourner ISP Paramètres de traitement du module 
 *
 * @retval 0  Paramètres de traitement du module 
 * @retval  Paramètres de traitement du module 0  Paramètres de traitement du module ， Paramètres de traitement du module 
 *
 * @remark  Si la fonction est activée ，sensor L'image de sortie ne passera pas ISP Tout traitement du module ， Sortie directe. 
 *
 * @attention  Sortie directe. ， Sortie directe. ISP Sortie directe. .
 */
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode);
#endif
/**
 * @fn int IMP_ISP_Tuning_SetFWFreeze(IMPISPTuningOpsMode mode)
 *
 *  Geler ISP Fonctionnement du micrologiciel ， Activer signifie geler ISP firmware ， c'est ISP L'algorithme automatique s'arrêtera; s'il n'est pas activé, cela signifie ISP Le firmware fonctionne normalement. 
 *
 * @param[in] mode  Est-ce gelé ISP Paramètres du micrologiciel 
 *
 * @retval 0  Paramètres du micrologiciel 
 * @retval  Paramètres du micrologiciel 0  Paramètres du micrologiciel ， Paramètres du micrologiciel 
 *
 * @attention  Paramètres du micrologiciel ， Paramètres du micrologiciel ISP Paramètres du micrologiciel .
 */
int IMP_ISP_Tuning_SetFWFreeze(IMPISPTuningOpsMode mode);


/**
 * @fn int IMP_ISP_Tuning_SaveAllParam(char *path)
 *
 *  sauvegarder ISP Tous les paramètres de débogage du module 
 *
 * @param[in] path  Pointeur de paramètre de chemin 
 *
 * @retval 0  Pointeur de paramètre de chemin 
 * @retval  Pointeur de paramètre de chemin 0  Pointeur de paramètre de chemin ， Pointeur de paramètre de chemin 
 *
 * @remark  Enregistrer tout le débogage ISP paramètre. 
 *
 * @attention  paramètre. ， paramètre. ISP paramètre. .
 */
int IMP_ISP_Tuning_SaveAllParam(char *path);

/**
 * @fn int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable)
 *
 * ISP Si le module bypass
 *
 * @param[in] enable  qu'il s'agisse bypass Mode de sortie 
 *
 * @retval 0  Mode de sortie 
 * @retval  Mode de sortie 0  Mode de sortie ， Mode de sortie 
 *
 * @remark  Mode de sortie 
 *
 * @attention  Mode de sortie ， Mode de sortie ISP Le module est fermé .
 */
int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable);

/**
 * @fn int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain)
 *
 *  Le module est fermé ISP La valeur de gain globale de l'image de sortie 
 *
 * @param[in] gain  Obtenez le pointeur du paramètre de valeur de gain , Le format de stockage des données est [24.8]， haut 24bit Est un entier ， faible 8bit Est un décimal. 
 *
 * @retval 0  Est un décimal. 
 * @retval  Est un décimal. 0  Est un décimal. ， Est un décimal. 
 *
 * @attention  Est un décimal. ， Est un décimal. IMP_ISP_EnableSensor  Est un décimal.  IMP_ISP_EnableTuning Est un décimal. 
 */
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);

/**
 *  Est un décimal. ISP Si la fonction d'effet de miroir d'image est activée 
 *
 * @fn int IMP_ISP_Tuning_SetISPHflip(IMPISPTuningOpsMode mode)
 *
 * @param[in] mode  Activer ou non l'effet miroir 
 *
 * @retval 0  Activer ou non l'effet miroir 
 * @retval  Activer ou non l'effet miroir 0  Activer ou non l'effet miroir ， Activer ou non l'effet miroir 
 *
 * @attention  Activer ou non l'effet miroir ，IMP_ISP_EnableTuning Activer ou non l'effet miroir 
 */
int IMP_ISP_Tuning_SetISPHflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPHflip(IMPISPTuningOpsMode *pmode)
 *
 *  Activer ou non l'effet miroir ISP L'état de fonctionnement de la fonction d'effet de miroir d'image 
 *
 * @param[in] pmode  Pointeur de paramètre d'opération 
 *
 * @retval 0  Pointeur de paramètre d'opération 
 * @retval  Pointeur de paramètre d'opération 0  Pointeur de paramètre d'opération ， Pointeur de paramètre d'opération 
 *
 * @attention  Pointeur de paramètre d'opération ，IMP_ISP_EnableTuning Pointeur de paramètre d'opération 
 */
int IMP_ISP_Tuning_GetISPHflip(IMPISPTuningOpsMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode)
 *
 *  Pointeur de paramètre d'opération ISP Si la fonction d'effet d'image à l'envers est activée 
 *
 * @param[in] mode  Activer ou non l'image inversée de haut en bas 
 *
 * @retval 0  Activer ou non l'image inversée de haut en bas 
 * @retval  Activer ou non l'image inversée de haut en bas 0  Activer ou non l'image inversée de haut en bas ， Activer ou non l'image inversée de haut en bas 
 *
 * @attention  Activer ou non l'image inversée de haut en bas ，IMP_ISP_EnableTuning Activer ou non l'image inversée de haut en bas 
 */
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPVflip(IMPISPTuningOpsMode *pmode)
 *
 *  Activer ou non l'image inversée de haut en bas ISP L'état de fonctionnement de l'image de haut en bas de la fonction d'effet inverse 
 *
 * @param[in] pmode  L'état de fonctionnement de l'image de haut en bas de la fonction d'effet inverse 
 *
 * @retval 0  L'état de fonctionnement de l'image de haut en bas de la fonction d'effet inverse 
 * @retval  L'état de fonctionnement de l'image de haut en bas de la fonction d'effet inverse 0  L'état de fonctionnement de l'image de haut en bas de la fonction d'effet inverse ， L'état de fonctionnement de l'image de haut en bas de la fonction d'effet inverse 
 *
 * @attention  L'état de fonctionnement de l'image de haut en bas de la fonction d'effet inverse ，IMP_ISP_EnableTuning L'état de fonctionnement de l'image de haut en bas de la fonction d'effet inverse 
 */
int IMP_ISP_Tuning_GetISPVflip(IMPISPTuningOpsMode *pmode);

/**
 * ISP  Configuration du mode de travail ， Mode normal ou mode de vision nocturne. 
 */
typedef enum {
	IMPISP_RUNNING_MODE_DAY = 0,				/**<  Mode normal  */
	IMPISP_RUNNING_MODE_NIGHT = 1,				/**<  Mode vision nocturne  */
	IMPISP_RUNNING_MODE_BUTT,					/**<  Max  */
} IMPISPRunningMode;

/**
 * @fn int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode)
 *
 *  Max ISP Mode de fonctionnement ， Mode normal ou mode de vision nocturne; le mode par défaut est le mode normal. 
 *
 * @param[in] mode Paramètres du mode de fonctionnement 
 *
 * @retval 0  Paramètres du mode de fonctionnement 
 * @retval  Paramètres du mode de fonctionnement 0  Paramètres du mode de fonctionnement ， Paramètres du mode de fonctionnement 
 *
 *  Exemple: 
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
 * @attention  Exemple: ，IMP_ISP_EnableTuning Exemple: 
 */
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode)
 *
 *  Exemple: ISP Exemple: ， Exemple: 
 *
 * @param[in] pmode Exemple: 
 *
 * @retval 0  Exemple: 
 * @retval  Exemple: 0  Exemple: ， Exemple: 
 *
 * @attention  Exemple: ，IMP_ISP_EnableTuning Exemple: 
 */
int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode);

/**
 * ISP  Configuration de la stratégie d'exposition automatique ， Mode normal ou mode de priorité d'exposition. 
 **/
typedef enum {
	IMPISP_AE_STRATEGY_SPLIT_BALANCED = 0,              /**<  Mode normal ou mode de priorité d'exposition.  */
	IMPISP_AE_STRATEGY_SPLIT_INTEGRATION_PRIORITY = 1,      /**<  Mode de priorité d'exposition  */
	IMPISP_AE_STRATEGY_BUTT,                    /**<  Mode de priorité d'exposition  */
} IMPISPAeStrategy;

/**
 * @fn int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy strategy)
 *
 *  Mode de priorité d'exposition ISP Mode de priorité d'exposition ， Mode de priorité d'exposition ， Mode normal ou mode de priorité d'exposition; le mode par défaut est le mode normal. 
 *
 * @param[in] strategy  Paramètres de stratégie d'exposition automatique 
 *
 * @retval 0  Paramètres de stratégie d'exposition automatique 
 * @retval  Paramètres de stratégie d'exposition automatique 0  Paramètres de stratégie d'exposition automatique ， Paramètres de stratégie d'exposition automatique 
 *  Paramètres de stratégie d'exposition automatique 
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
* @attention  Paramètres de stratégie d'exposition automatique ，IMP_ISP_EnableTuning Paramètres de stratégie d'exposition automatique 
*/
int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy strategy);

/**
* @fn int IMP_ISP_Tuning_GetAeStrategy(IMPISPAeStrategy *pstrategy)
*
*  Paramètres de stratégie d'exposition automatique ISP Paramètres de stratégie d'exposition automatique ， Paramètres de stratégie d'exposition automatique 
* @param[in] pstrategy  Pointeur de paramètre de stratégie d'exposition automatique 
*
* @retval 0  Pointeur de paramètre de stratégie d'exposition automatique 
* @retval  Pointeur de paramètre de stratégie d'exposition automatique 0  Pointeur de paramètre de stratégie d'exposition automatique ， Pointeur de paramètre de stratégie d'exposition automatique 
*
* @attention  Pointeur de paramètre de stratégie d'exposition automatique ，IMP_ISP_EnableTuning Pointeur de paramètre de stratégie d'exposition automatique 
*/
int IMP_ISP_Tuning_GetAeStrategy(IMPISPAeStrategy *pstrategy);

/**
 * gamma
 */
typedef struct {
	uint16_t gamma[129];		/**< gamma Tableau de paramètres ， Ont 129 Points  */
} IMPISPGamma;

/**
* @fn int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma)
*
*  Points GAMMA paramètre .
* @param[in] gamma gamma paramètre 
*
* @retval 0  paramètre 
* @retval  paramètre 0  paramètre ， paramètre 
*
* @attention  paramètre ，IMP_ISP_EnableTuning paramètre 
*/
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma)
*
*  paramètre GAMMA paramètre .
* @param[out] gamma gamma paramètre 
*
* @retval 0  paramètre 
* @retval  paramètre 0  paramètre ， paramètre 
*
* @attention  paramètre ，IMP_ISP_EnableTuning paramètre 
*/
int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_SetAeComp(int comp)
*
*  paramètre AE se réconcilier. AE Les paramètres de compensation peuvent ajuster l'image AE target， La plage de réglage recommandée est [90-150].
* @param[in] comp AE Paramètre de compensation 
*
* @retval 0  Paramètre de compensation 
* @retval  Paramètre de compensation 0  Paramètre de compensation ， Paramètre de compensation 
*
* @attention  Paramètre de compensation ，IMP_ISP_EnableTuning Paramètre de compensation 
*/
int IMP_ISP_Tuning_SetAeComp(int comp);

/**
* @fn int IMP_ISP_Tuning_GetAeComp(int *comp)
*
*  Paramètre de compensation AE Paramètre de compensation 
* @param[out] comp AE Paramètre de compensation 
*
* @retval 0  Paramètre de compensation 
* @retval  Paramètre de compensation 0  Paramètre de compensation ， Paramètre de compensation 
*
* @attention  Paramètre de compensation ，IMP_ISP_EnableTuning Paramètre de compensation 
*/
int IMP_ISP_Tuning_GetAeComp(int *comp);

/**
 *  Mode d'exposition 
 */
enum isp_core_expr_mode {
	ISP_CORE_EXPR_MODE_AUTO,			/**<  Mode d'exposition  */
	ISP_CORE_EXPR_MODE_MANUAL,			/**<  Mode manuel  */
};

/**
 *  Unité d'exposition 
 */
enum isp_core_expr_unit {
	ISP_CORE_EXPR_UNIT_LINE,			/**<  Rangée  */
	ISP_CORE_EXPR_UNIT_US,				/**<  milliseconde  */
};

/**
 *  Paramètres d'exposition 
 */
typedef union isp_core_expr_attr{
	struct {
		enum isp_core_expr_mode mode;		/**<  Définir le mode d'exposition  */
		enum isp_core_expr_unit unit;		/**<  Définir l'unité d'exposition  */
		uint16_t time;
	} s_attr;
	struct {
		enum isp_core_expr_mode mode;			/**<  Mode d'exposition acquis  */
		uint16_t integration_time;		/**<  Délai d'exposition ， L'unité est la ligne  */
		uint16_t integration_time_min;	/**<  Temps d'exposition minimum obtenu ， Temps d'exposition minimum obtenu  */
		uint16_t integration_time_max;	/**<  Temps d'exposition maximal obtenu ， Temps d'exposition maximal obtenu  */
		uint16_t one_line_expr_in_us;		/**<  Le nombre de microsecondes correspondant au temps d'exposition d'une ligne  */
	} g_attr;
}IMPISPExpr;


/**
 * @fn int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr)
 *
 *  Le nombre de microsecondes correspondant au temps d'exposition d'une ligne AE Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 
 *
 * @param[in] expr AE Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 
 *
 * @retval 0  Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 
 * @retval  Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 0  Le nombre de microsecondes correspondant au temps d'exposition d'une ligne ， Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 
 *
 * @attention  Le nombre de microsecondes correspondant au temps d'exposition d'une ligne ，IMP_ISP_EnableTuning Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 
 */
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr);

/**
 * @fn int IMP_ISP_Tuning_GetExpr(IMPISPExpr *expr)
 *
 *  Le nombre de microsecondes correspondant au temps d'exposition d'une ligne AE Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 
 *
 * @param[out] expr AE Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 
 *
 * @retval 0  Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 
 * @retval  Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 0  Le nombre de microsecondes correspondant au temps d'exposition d'une ligne ， Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 
 *
 * @attention  Le nombre de microsecondes correspondant au temps d'exposition d'une ligne ，IMP_ISP_EnableTuning Le nombre de microsecondes correspondant au temps d'exposition d'une ligne 
 */
int IMP_ISP_Tuning_GetExpr(IMPISPExpr *expr);

/**
 *  Sélection de la zone des statistiques d'exposition 
 */
typedef union isp_core_ae_roi_select{
	struct {
		unsigned endy :8;                   /**<  Point final y coordonner  (0 ~ 255)*/
		unsigned endx :8;                   /**<  coordonner x coordonner  (0 ~ 255)*/
		unsigned starty :8;                 /**<  Point de départ y Point de départ  (0 ~ 255)*/
		unsigned startx :8;                 /**<  Point de départ x Point de départ  (0 ~ 255)*/
	};
	uint32_t value;
} IMPISPAERoi;

/**
 * @fn int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi)
 *
 *  Point de départ AE Zone de statistiques. 
 *
 * @param[out] isp_ae_roi AE Paramètres de zone statistique rectangulaire. 
 *
 * @retval 0  Paramètres de zone statistique rectangulaire. 
 * @retval  Paramètres de zone statistique rectangulaire. 0  Paramètres de zone statistique rectangulaire. ， Paramètres de zone statistique rectangulaire. 
 *
 * @attention  Paramètres de zone statistique rectangulaire. ，IMP_ISP_EnableTuning Paramètres de zone statistique rectangulaire. 
 */
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);

/**
 * @fn int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi)
 *
 *  Paramètres de zone statistique rectangulaire. AE Paramètres de zone statistique rectangulaire. 
 *
 * @param[in] isp_ae_roi AE Paramètres de zone statistique rectangulaire. 
 *
 * @retval 0  Paramètres de zone statistique rectangulaire. 
 * @retval  Paramètres de zone statistique rectangulaire. 0  Paramètres de zone statistique rectangulaire. ， Paramètres de zone statistique rectangulaire. 
 *
 * @attention  Paramètres de zone statistique rectangulaire. ，IMP_ISP_EnableTuning Paramètres de zone statistique rectangulaire. 
 */
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);

/**
 *  Mode de balance des blancs 
 */
enum isp_core_wb_mode {
	ISP_CORE_WB_MODE_AUTO = 0,			/**<  Mode de balance des blancs  */
	ISP_CORE_WB_MODE_MANUAL,			/**<  Mode de balance des blancs  */
	ISP_CORE_WB_MODE_DAY_LIGHT,			/**<  journée ensoleillée  */
	ISP_CORE_WB_MODE_CLOUDY,			/**<  temps nuageux  */
	ISP_CORE_WB_MODE_INCANDESCENT,		/**<  Lampe à incandescence  */
	ISP_CORE_WB_MODE_FLOURESCENT,		/**<  Lampe fluorescente  */
	ISP_CORE_WB_MODE_TWILIGHT,			/**<  crépuscule  */
	ISP_CORE_WB_MODE_SHADE,				/**<  ombre  */
	ISP_CORE_WB_MODE_WARM_FLOURESCENT,	/**<  Lampe fluorescente chaude  */
};

/**
 *  Paramètres de balance des blancs 
 */
typedef struct isp_core_wb_attr{
	enum isp_core_wb_mode mode;		/**<  Paramètres de balance des blancs ， Divisé en modes automatique et manuel  */
	uint16_t rgain;			/**<  Gain rouge ， Efficace en mode manuel  */
	uint16_t bgain;			/**<  Gain bleu ， Gain bleu  */
}IMPISPWB;

/**
 * @fn int IMP_ISP_Tuning_SetWB(IMPISPWB *wb)
 *
 *  Définissez les paramètres de la fonction de balance des blancs. Peut définir le mode automatique et manuel ， Le mode manuel est principalement défini par rgain [[[ bgain atteindre. 
 *
 * @param[in] wb  Réglez les paramètres de balance des blancs. 
 *
 * @retval 0  Réglez les paramètres de balance des blancs. 
 * @retval  Réglez les paramètres de balance des blancs. 0  Réglez les paramètres de balance des blancs. ， Réglez les paramètres de balance des blancs. 
 *
 * @attention  Réglez les paramètres de balance des blancs. ，IMP_ISP_EnableTuning Réglez les paramètres de balance des blancs. 
 */
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_GetWB(IMPISPWB *wb)
 *
 *  Obtenez le réglage de la fonction de balance des blancs. 
 *
 * @param[out] wb  Les paramètres de balance des blancs obtenus. 
 *
 * @retval 0  Les paramètres de balance des blancs obtenus. 
 * @retval  Les paramètres de balance des blancs obtenus. 0  Les paramètres de balance des blancs obtenus. ， Les paramètres de balance des blancs obtenus. 
 *
 * @attention  Les paramètres de balance des blancs obtenus. ，IMP_ISP_EnableTuning Les paramètres de balance des blancs obtenus. 
 */
int IMP_ISP_Tuning_GetWB(IMPISPWB *wb);

/**
 * @fn IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb)
 *
 *  Obtenez des statistiques de balance des blancs. 
 *
 * @param[out] wb  Les statistiques de balance des blancs obtenues. 
 *
 * @retval 0  Les statistiques de balance des blancs obtenues. 
 * @retval  Les statistiques de balance des blancs obtenues. 0  Les statistiques de balance des blancs obtenues. ， Les statistiques de balance des blancs obtenues. 
 *
 * @attention  Les statistiques de balance des blancs obtenues. ，IMP_ISP_EnableTuning Les statistiques de balance des blancs obtenues. 
 */
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB* isp_wb_attr)
 *
 *  Les statistiques de balance des blancs obtenues. ISP Les statistiques de balance des blancs obtenues. AWB de CWF La position de la source lumineuse 
 *
 * @param[out] isp_wb_attr CWF Coordonnées de la position de la source lumineuse 
 *
 * @retval 0  Coordonnées de la position de la source lumineuse 
 * @retval  Coordonnées de la position de la source lumineuse 0  Coordonnées de la position de la source lumineuse ， Coordonnées de la position de la source lumineuse 
 *
 * @attention  Coordonnées de la position de la source lumineuse ，IMP_ISP_EnableTuning Coordonnées de la position de la source lumineuse 
 */
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);

/**
 * @fn int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr)
 *
 *  Coordonnées de la position de la source lumineuse ISP Coordonnées de la position de la source lumineuse AWB Coordonnées de la position de la source lumineuse CWF Coordonnées de la position de la source lumineuse 
 *
 * @param[in] isp_wb_attr CWF Coordonnées de la position de la source lumineuse 
 *
 * @retval 0  Coordonnées de la position de la source lumineuse 
 * @retval  Coordonnées de la position de la source lumineuse 0  Coordonnées de la position de la source lumineuse ， Coordonnées de la position de la source lumineuse 
 *  Coordonnées de la position de la source lumineuse 
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
 * @attention  Coordonnées de la position de la source lumineuse ，IMP_ISP_EnableTuning Coordonnées de la position de la source lumineuse 
 */
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);

/**
 * @fn int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain)
 *
 *  Coordonnées de la position de la source lumineuse sensor Vous pouvez définir le maximum Again . 
 *
 * @param[in] gain sensor Le maximum qui peut être défini again.0 Moyens 1x，32 Moyens 2x， Etc. 
 *
 * @retval 0  Etc. 
 * @retval  Etc. 0  Etc. ， Etc. 
 *
 * @attention  Etc. ，IMP_ISP_EnableTuning Etc. 
 */
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);

/**
 * @fn int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain)
 *
 *  Etc. sensor Etc. Again Etc. 
 *
 * @param[out] gain sensor Etc. again.0 Etc. 1x，32 Etc. 2x， Etc. 
 *
 * @retval 0  Etc. 
 * @retval  Etc. 0  Etc. ， Etc. 
 *
 * @attention  Etc. ，IMP_ISP_EnableTuning Etc. 
 */
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain)
 *
 *  Etc. ISP Etc. Dgain Etc. 
 *
 * @param[in] ISP Dgain  Etc. dgain.0 Etc. 1x，32 Etc. 2x， Etc. 
 *
 * @retval 0  Etc. 
 * @retval  Etc. 0  Etc. ， Etc. 
 *
 * @attention  Etc. ，IMP_ISP_EnableTuning Etc. 
 */
int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain);

/**
 * @fn int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain)
 *
 *  Etc. ISP Définir le maximum Dgain Définir le maximum 
 *
 * @param[out] ISP Dgain  Peut obtenir le plus grand ensemble dgain.0 Peut obtenir le plus grand ensemble 1x，32 Peut obtenir le plus grand ensemble 2x， Peut obtenir le plus grand ensemble 
 *
 * @retval 0  Peut obtenir le plus grand ensemble 
 * @retval  Peut obtenir le plus grand ensemble 0  Peut obtenir le plus grand ensemble ， Peut obtenir le plus grand ensemble 
 *
 * @attention  Peut obtenir le plus grand ensemble ，IMP_ISP_EnableTuning Peut obtenir le plus grand ensemble 
 */
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void))
 *
 *  Réglez la fonction de perte vidéo. Quand il apparaît sensor En cas de problème avec le circuit de connexion ， La fonction de rappel définie sera exécutée. 
 *
 * @param[in] cb  Rappeler. 
 *
 * @retval 0  Rappeler. 
 * @retval  Rappeler. 0  Rappeler. ， Rappeler. 
 *
 * @attention  Rappeler. ，IMP_ISP_EnableTuning Rappeler. 
 */
int IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void));

/**
 * @fn int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength)
 *
 *  Réglez l'intensité de la forte suppression de la lumière. 
 *
 * @param[in] strength  Paramètre d'intensité de suppression de la lumière forte . La plage de valeurs est [ 0-10], 0 Indique que la fonction est désactivée. 
 *
 * @retval 0  Indique que la fonction est désactivée. 
 * @retval  Indique que la fonction est désactivée. 0  Indique que la fonction est désactivée. ， Indique que la fonction est désactivée. 
 *
 * @attention  Indique que la fonction est désactivée. ，IMP_ISP_EnableTuning Indique que la fonction est désactivée. 
 */
int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength);

/**
 * @fn int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio)
 *
 *  Indique que la fonction est désactivée. 3D Intensité de la réduction du bruit. 
 *
 * @param[in] ratio  Rapport d'ajustement d'intensité . Si défini sur 90 Cela signifie qu'il est défini sur la valeur par défaut 90%. Cela signifie qu'il est défini sur la valeur par défaut 50-150].
 *
 * @retval 0  Cela signifie qu'il est défini sur la valeur par défaut 
 * @retval  Cela signifie qu'il est défini sur la valeur par défaut 0  Cela signifie qu'il est défini sur la valeur par défaut ， Cela signifie qu'il est défini sur la valeur par défaut 
 *
 * @attention  Cela signifie qu'il est défini sur la valeur par défaut ，IMP_ISP_EnableTuning Cela signifie qu'il est défini sur la valeur par défaut 
 */
int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio)
 *
 *  Cela signifie qu'il est défini sur la valeur par défaut 2D Cela signifie qu'il est défini sur la valeur par défaut 
 *
 * @param[in] ratio  Cela signifie qu'il est défini sur la valeur par défaut . Cela signifie qu'il est défini sur la valeur par défaut 90 Cela signifie qu'il est défini sur la valeur par défaut 90%. Cela signifie qu'il est défini sur la valeur par défaut 50-150].
 *
 * @retval 0  Cela signifie qu'il est défini sur la valeur par défaut 
 * @retval  Cela signifie qu'il est défini sur la valeur par défaut 0  Cela signifie qu'il est défini sur la valeur par défaut ， Cela signifie qu'il est défini sur la valeur par défaut 
 *
 * @attention  Cela signifie qu'il est défini sur la valeur par défaut ，IMP_ISP_EnableTuning Cela signifie qu'il est défini sur la valeur par défaut 
 */
int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetDPStrength(uint32_t ratio)
 *
 *  Cela signifie qu'il est défini sur la valeur par défaut DPC force. 
 *
 * @param[in] ratio  force. . force. 90 force. 90%. force. 50-150].
 *
 * @retval 0  force. 
 * @retval  force. 0  force. ， force. 
 *
 * @attention  force. ，IMP_ISP_EnableTuning force. 
 */
int IMP_ISP_Tuning_SetDPStrength(uint32_t ratio);

/**
 * ISP ANTIFOG  Mode de fonctionnement. 
 */
typedef enum {
	ANTIFOG_DISABLE,			/**<  Mode de fonctionnement.  */
	ANTIFOG_STRONG,				/**<  Fort  */
	ANTIFOG_MEDIUM,				/**<  Fort  */
	ANTIFOG_WEAK,				/**<  faible  */
}IMPISPAntiFogAttr;

/**
* @fn int IMP_ISP_Tuning_SetAntiFogAttr(IMPISPAntiFogAttr attr)
*
*  faible ANTIFOG Les attributs. 
* @param[in] attr ANTIFOG Paramètre d'attribut 
*
* @retval 0  Paramètre d'attribut 
* @retval  Paramètre d'attribut 0  Paramètre d'attribut ， Paramètre d'attribut 
*
* @attention  Paramètre d'attribut ，IMP_ISP_EnableTuning Paramètre d'attribut 
*/
int IMP_ISP_Tuning_SetAntiFogAttr(IMPISPAntiFogAttr attr);

/**
 * ISP EV  Paramètre d'attribut 
 */
typedef struct {
	uint32_t ev;			/**<  Valeur d'exposition  */
	uint32_t expr_us;		/**<  Délai d'exposition  */
	uint32_t ev_log2;		/**<log Formater le temps d'exposition  */
	uint32_t again;			/**<  Gain analogique  */
	uint32_t dgain;			/**<  Gain numérique  */
	uint32_t gain_log2;		/**< log Gain de format  */
}IMPISPEVAttr;

/**
* @fn int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr)
*
*  Gain de format EV Gain de format 
* @param[out] attr EV Gain de format 
*
* @retval 0  Gain de format 
* @retval  Gain de format 0  Gain de format ， Gain de format 
*
* @attention  Gain de format ，IMP_ISP_EnableTuning Gain de format 
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
