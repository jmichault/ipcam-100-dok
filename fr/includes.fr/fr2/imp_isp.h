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
* Le type de bus de contrôle de la caméra est I2C Temps ， Structure des paramètres à configurer 
*/
typedef struct {
	char type[20];		/**< I2C Nom de l'appareil ， Doit être conduit avec la caméra struct i2c_device_id dans name Les variables sont cohérentes */
	int addr;		/**< I2C adresse */
	int i2c_adapter_id;	/**< I2C Manette */
} IMPI2CInfo;
/**
* Le type de bus de contrôle de la caméra est SPI Temps ， Structure des paramètres à configurer 
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
 * fermer ISP Module 
 *
 * @param non 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Module ISP, le module ISP ne fonctionne plus.
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que toutes les fonctions de débogage FrameSource et d'effets ont été fermées et que tous les capteurs ont été désinstallés.
 */
int IMP_ISP_Close(void);

/**
 * @fn int IMP_ISP_AddSensor (IMPSensorInfo * pinfo)
 *
 * ajoute un sensor， Habitué ISP Le module fournit la source de données 
 *
 * @param[in] pinfo Besoin d'ajouter un pointeur d'informations sur le capteur
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
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
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
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
 * @param non 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
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
 * @param non 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
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
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Vous pouvez régler directement la valeur d'un registre de capteur.
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que la caméra a été activée.
 */
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value);

/**
 * @fn int IMP_ISP_GetSensorRegister (uint32_t reg, uint32_t * valeur)
 *
 * Obtenir sensor La valeur d'un registre 
 *
 * @param[in] reg Adresse d'inscription 
 *
 * @param[in] pointeur de valeur pour enregistrer la valeur
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Vous pouvez obtenir directement la valeur d'un registre de capteur.
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
	IMPISP_TUNING_OPS_TYPE_BUTT,			/**< Utilisé pour juger de la validité des paramètres ， La taille du paramètre doit être inférieure à cette valeur */
} IMPISPTuningOpsType;

/**
 * @fn int IMP_ISP_EnableTuning (void)
 *
 * Permettre ISP Fonction de débogage d'effet 
 *
 * @param non 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que IMP_ISP_EnableSensor est exécuté et renvoie correctement.
 */
int IMP_ISP_EnableTuning(void);

/**
 * @fn int IMP_ISP_DisableTuning (void)
 *
 * Désactiver ISP Fonction de débogage d'effet 
 *
 * @param non 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
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
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
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
 * @fn int IMP_ISP_Tuning_SetAntiFlickerAttr (IMPISPAntiflickerAttr attr)
 *
 * Installation ISP Propriétés anti-flash 
 *
 * @param[in] attr définir la valeur du paramètre
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que la fonction de débogage d'effet ISP a été activée.
 */
int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);

/**
 * @fn int IMP_ISP_Tuning_GetAntiFlickerAttr (IMPISPAntiflickerAttr * pattr)
 *
 * obtenir ISP Propriétés anti-flash 
 *
 * @param[in] pattr Récupère le pointeur de valeur de paramètre
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
} IMPISPDrcMode;

/**
 * ISP Paramètres d'attribut du module de compression de plage dynamique. 
 */
typedef struct {
	IMPISPDrcMode mode;				/**< ISP Sélection du mode de fonctionnement du module de compression de plage dynamique */
	unsigned char drc_strength;			/**< Valeur cible définie en mode manuel ， La plage de valeurs est [0, 0xff] */
	unsigned char slop_max;				/**< Paramètres de contrôle de la force ， La plage de valeurs est [0, oxff] */
	unsigned char slop_min;				/**< Paramètres de contrôle de la force ， La plage de valeurs est [0, oxff] */
	unsigned short black_level;			/**< DRC Valeur de pixel minimale améliorée ， La plage de valeurs est [0, oxfff] */
	unsigned short white_level;			/**< DRC Valeur de pixel maximale améliorée ， La plage de valeurs est [0, oxfff] */
} IMPISPDrcAttr;

/**
 * @fn int IMP_ISP_Tuning_SetRawDRC (IMPISPDrcAttr * pinfo)
 *
 * Installation ISP RAW Figure paramètres du module de compression de plage dynamique 
 *
 * @param[in] pointeur de paramètre de plage dynamique pinfo
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Définissez le type d'opération et l'intensité de la compression de la plage dynamique des images RVB RAW, ainsi que les valeurs de pixels maximales et minimales qui doivent être améliorées.
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetRawDRC(IMPISPDrcAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetRawDRC (IMPISPDrcAttr * pinfo)
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
	IMPISPTemperMode type;					/**< Type d'opération de la fonction de réduction du bruit dans le domaine temporel ， Désactiver ， Automatique ou manuel */
	unsigned char temper_strength;				/**< Intensité de la réduction du bruit dans le domaine temporel ， Le mode manuel est efficace ， La plage de valeurs est [0, 0xff] */
} IMPISPTemperDenoiseAttr;


/**
 * @fn int IMP_ISP_Tuning_SetSinterDnsAttr (IMPISPSinterDenoiseAttr * pinfo)
 *
 * Installation ISP Paramètres du module de réduction du bruit spatial 
 *
 * @param[in] pointeur de paramètre de réduction du bruit dans le domaine temporel pinfo
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
 * @fn int IMP_ISP_Tuning_GetSinterDnsAttr (IMPISPSinterDenoiseAttr * pinfo)
 *
 * Obtenir ISP Paramètres du module de réduction du bruit spatial 
 *
 * @param[in] pointeur de paramètre de réduction du bruit de l'espace pinfo
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
* @fn int IMP_ISP_Tuning_SetTemperDnsCtl (IMPISPTemperDenoiseAttr * pinfo);
*
* Installation ISP Mode du module de réduction du bruit dans le domaine temporel 
*
* @param[in] pinfo Pointeur de paramètre de réduction du bruit dans le domaine temporel 
*
* @retval 0 Succès 
* @retval non- 0 échec ， Renvoyer le code d'erreur 
*
* @remark Définissez les paramètres de mode du module de réduction du bruit dans le domaine temporel, le mode automatique par défaut.
*
* @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
*/
int IMP_ISP_Tuning_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
#endif
/**
 * @fn int IMP_ISP_Tuning_SetTemperDnsAttr (IMPISPTemperDenoiseAttr * pinfo)
 *
 * Installation ISP Paramètres du module de réduction du bruit dans le domaine temporel 
 *
 * @param[in] pinfo Pointeur de paramètre de réduction du bruit dans le domaine temporel 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Définissez les paramètres de correction du module de réduction du bruit dans le domaine temporel, et le module est activé par défaut; comme le module nécessite de la mémoire supplémentaire, veuillez éteindre le module si vous n'en avez pas besoin. Une fois la mémoire désactivée, il sera être rel une chée et ne peut plus être remise sous tension.
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_GetTemperDnsAttr (IMPISPTemperDenoiseAttr * pinfo)
 *
 * Obtenir ISP Paramètres du module de réduction du bruit dans le domaine temporel 
 *
 * @param[in] pinfo Pointeur de paramètre du module de réduction du bruit dans le domaine temporel
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Obtenez les paramètres de correction du module de réduction du bruit dans le domaine temporel.
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);

/**
 * @fn int IMP_ISP_Tuning_SetWDRAttr (mode IMPISPTuningOpsMode)
 *
 * Installation ISP Si le module dynamique large est activé 
 *
 * @param[in] paramètres du module dynamique à l'échelle du mode
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Définissez les paramètres d'étalonnage du module dynamique large, le module est activé par défaut; parce que le module nécessite de la mémoire supplémentaire, veuillez éteindre le module si vous n'en avez pas besoin. Une fois que vous éteignez la mémoire, elle sera libérée et ne pourra plus être rallumé.
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetWDRAttr (IMPISPTuningOpsMode * pmode)
 *
 * Obtenir ISP État actuel du module dynamique large 
 *
 * @param[in] pointeur de paramètre de module dynamique large pmode
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
 * @fn int IMP_ISP_Tuning_SetSceneMode (mode IMPISPSceneMode)
 *
 * Installation ISP Mode scène d'effets complet 
 *
 * @param[in] mode Paramètre de mode de scène d'effet
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetSceneMode (IMPISPSceneMode * pmode)
 *
 * Obtenir ISP Mode scène d'effets complet 
 *
 * @param[in] pointeur de paramètre de mode scène d'effet pmode
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
 * @fn int IMP_ISP_Tuning_SetColorfxMode (mode IMPISPColorfxMode)
 *
 * Installation ISP Mode couleur multi-effets 
 *
 * @param[in] paramètre de mode couleur
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetColorfxMode (IMPISPColorfxMode * pmode)
 *
 * Obtenir ISP Mode couleur multi-effets 
 *
 * @param[in] pointeur de paramètre de mode couleur pmode
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_GetColorfxMode(IMPISPColorfxMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetBrightness (caractère non signé brillant)
 *
 * Installation ISP Luminosité d'image complète 
 *
 * @param[in] Paramètre de luminosité de l'image lumineuse
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128, plus de 128 augmente la luminosité, moins de 128 diminue la luminosité.
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetBrightness(unsigned char bright);

/**
 * @fn int IMP_ISP_Tuning_GetBrightness (caractère non signé * pbright)
 *
 * Obtenir ISP Luminosité d'image complète 
 *
 * @param[in] Pointeur de paramètre de luminosité de l'image lumineuse
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
 * @fn int IMP_ISP_Tuning_SetContrast (contraste de caractères non signé)
 *
 * Installation ISP Contraste d'image complet 
 *
 * @param[in] contraste paramètre de contraste de l'image
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128, plus de 128 augmente le contraste, moins de 128 réduit le contraste.
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetContrast(unsigned char contrast);

/**
 * @fn int IMP_ISP_Tuning_GetContrast (caractère non signé * pcontrast)
 *
 * Obtenir ISP Contraste d'image complet 
 *
 * @param[in] pointeur de paramètre de contraste de l'image de contraste
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
 * @fn int IMP_ISP_Tuning_SetSharpness (netteté des caractères non signés)
 *
 * Installation ISP Netteté d'image complète 
 *
 * @param[in] netteté image valeur du paramètre de netteté
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128, plus de 128 augmente la netteté, moins de 128 diminue la netteté.
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness);

/**
 * @fn int IMP_ISP_Tuning_GetSharpness (caractère non signé * psharpness)
 *
 * Obtenir ISP Netteté d'image complète 
 *
 * @param[in] pointeur de paramètre de netteté de l'image de netteté
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
 * @fn int IMP_ISP_Tuning_SetSaturation (caractère non signé sat)
 *
 * Installation ISP Saturation complète de l'image avec effet 
 *
 * @param[in] saturation de l'image valeur du paramètre de saturation
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark La valeur par défaut est 128, plus de 128 augmente la saturation, moins de 128 diminue la saturation.
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetSaturation(unsigned char sat);

/**
 * @fn int IMP_ISP_Tuning_GetSaturation (caractère non signé * psat)
 *
 * Obtenir ISP Saturation complète de l'image avec effet 
 *
 * @param[in] pointeur de paramètre de saturation d'image sat
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
 * @fn int IMP_ISP_Tuning_SetISPProcess (mode IMPISPTuningOpsMode)
 *
 * contourne ISP Manipulation des modules ， Sortie directe sensor image 
 *
 * @param[in] mode s'il faut contourner les paramètres de traitement du module ISP
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Si cette fonction est activée, l'image sortie par le capteur sera sortie directement sans aucun traitement par le module ISP.
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
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
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SetFWFreeze(IMPISPTuningOpsMode mode);


/**
 * @fn int IMP_ISP_Tuning_SaveAllParam (char * chemin)
 *
 * sauvegarder ISP Tous les paramètres de débogage du module 
 *
 * @param[in] pointeur de paramètre de chemin de chemin
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Enregistrez tous les paramètres du FAI pour le débogage.
 *
 * @attention Avant d'utiliser cette fonction ， Doit garantir ISP La fonction de débogage des effets a été activée .
 */
int IMP_ISP_Tuning_SaveAllParam(char *path);

/**
 * @fn int IMP_ISP_Tuning_SetISPBypass (activation IMPISPTuningOpsMode)
 *
 * ISP Si le module bypass
 *
 * @param[in] activer s'il faut contourner le mode de sortie
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non 
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que le module ISP est fermé.
 */
int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable);

/**
 * @fn int IMP_ISP_Tuning_GetTotalGain (uint32_t * gain)
 *
 * Obtenir ISP La valeur de gain globale de l'image de sortie 
 *
 * @param[in] gain est un pointeur pour obtenir le paramètre de valeur de gain, son format de stockage de données est [24,8], le haut 24 bits est un entier et le bas 8 bits est un décimal.
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
 * @fn int IMP_ISP_Tuning_SetISPHflip (mode IMPISPTuningOpsMode)
 *
 * @param[in] mode s'il faut activer l'effet miroir
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction, IMP_ISP_EnableTuning a été appelé.
 */
int IMP_ISP_Tuning_SetISPHflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPHflip (IMPISPTuningOpsMode * pmode)
 *
 * Obtenir ISP L'état de fonctionnement de la fonction d'effet de miroir d'image 
 *
 * @param[in] pointeur de paramètre d'opération pmode
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetISPHflip(IMPISPTuningOpsMode *pmode);

/**
 * @fn int IMP_ISP_Tuning_SetISPVflip (mode IMPISPTuningOpsMode)
 *
 * Installation ISP Si la fonction d'effet inverse de l'image vers le haut et vers le bas est activée 
 *
 * @param[in] mode s'il faut activer l'inversion de l'image vers le haut et vers le bas
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode);

/**
 * @fn int IMP_ISP_Tuning_GetISPVflip (IMPISPTuningOpsMode * pmode)
 *
 * Obtenir ISP L'état de fonctionnement de l'image de haut en bas de la fonction d'effet inverse 
 *
 * @param[in] pmode Pointeur de paramètre d'opération 
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
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
 * Installation ISP Mode de fonctionnement ， Mode normal ou mode de vision nocturne; le mode par défaut est le mode normal. 
 *
 * @param[in] paramètre de mode de fonctionnement de mode
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
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
 * @fn int IMP_ISP_Tuning_GetISPRunningMode (IMPISPRunningMode * pmode)
 *
 * Obtenir ISP Mode de fonctionnement ， Mode normal ou mode de vision nocturne. 
 *
 * @param[in] pointeur de paramètre d'opération pmode
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
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
 * @fn int IMP_ISP_Tuning_SetAeStrategy (stratégie IMPISPAeStrategy)
 *
 * Installation ISP Mode de fonctionnement ， Configuration de la stratégie d'exposition automatique ， Mode normal ou mode de priorité d'exposition; le mode par défaut est le mode normal. 
 *
 * @param[in] stratégie Paramètres de stratégie d'exposition automatique
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
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
* @fn int IMP_ISP_Tuning_GetAeStrategy (IMPISPAeStrategy * pstrategy)
*
* Obtenir ISP Configuration de la stratégie d'exposition automatique ， Mode normal ou mode de priorité d'exposition. 
* @param[in] Pointeur de paramètre de stratégie d'exposition automatique pstrategy
*
* @retval 0 succès 
* @retval non-0 échec ， Renvoyer le code d'erreur 
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
* @fn int IMP_ISP_Tuning_SetGamma (IMPISPGamma * gamma)
*
* Installation GAMMA paramètre .
* @param[in] paramètre gamma gamma
*
* @retval 0 succès 
* @retval non-0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_GetGamma (IMPISPGamma * gamma)
*
* Obtenir GAMMA paramètre .
* @param[out] gamma gamma paramètre 
*
* @retval 0 succès 
* @retval non-0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma);

/**
* @fn int IMP_ISP_Tuning_SetAeComp (int comp)
*
* Installation AE se réconcilier. AE Les paramètres de compensation peuvent ajuster l'image AE target， La plage de réglage recommandée est [90-150].
* @param[in] comp Paramètres de compensation AE
*
* @retval 0 succès 
* @retval non-0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
*/
int IMP_ISP_Tuning_SetAeComp(int comp);

/**
* @fn int IMP_ISP_Tuning_GetAeComp (int * comp)
*
* Obtenir AE se réconcilier. 
* @param[out] comp AE Paramètre de compensation 
*
* @retval 0 succès 
* @retval non-0 échec ， Renvoyer le code d'erreur 
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
 * @fn int IMP_ISP_Tuning_SetExpr (IMPISPExpr * expr)
 *
 * Installation AE paramètre. 
 *
 * @param[in] paramètre expr AE.
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr);

/**
 * @fn int IMP_ISP_Tuning_GetExpr (IMPISPExpr * expr)
 *
 * Obtenir AE paramètre. 
 *
 * @param[out] expr AE paramètre. 
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
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
 * @fn int IMP_ISP_Tuning_AE_GetROI (IMPISPAERoi * isp_ae_roi)
 *
 * Obtenir AE Zone de statistiques. 
 *
 * @param[out] isp_ae_roi AE Paramètres de la zone statistique rectangulaire.
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);

/**
 * @fn int IMP_ISP_Tuning_AE_SetROI (IMPISPAERoi * isp_ae_roi)
 *
 * Installation AE Zone de statistiques. 
 *
 * @param[in] isp_ae_roi AE Paramètres de zone statistique rectangulaire. 
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
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
 * @fn int IMP_ISP_Tuning_SetWB (IMPISPWB * wb)
 *
 * Définissez les paramètres de la fonction de balance des blancs. ， Le mode manuel est principalement défini par rgain [[[ bgain atteindre. 
 *
 * @param[in] wb Jeu de paramètres de balance des blancs.
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_GetWB (IMPISPWB * wb)
 *
 * Obtenez le réglage de la fonction de balance des blancs. 
 *
 * @param[out] wb Paramètre de balance des blancs obtenu.
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetWB(IMPISPWB *wb);

/**
 * @fn IMP_ISP_Tuning_GetWB_Statis (IMPISPWB * wb)
 *
 * Obtenez des statistiques de balance des blancs. 
 *
 * @param[out] wb Statistiques de balance des blancs obtenues.
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);

/**
 * @fn int IMP_ISP_Tuning_Awb_GetCwfShift (IMPISPWB * isp_wb_attr)
 *
 * Obtenir ISP dans AWB de CWF La position de la source lumineuse 
 *
 * @param[out] isp_wb_attr Coordonnées de la position de la source lumineuse CWF
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);

/**
 * @fn int IMP_ISP_Tuning_Awb_SetCwfShift (IMPISPWB * isp_wb_attr)
 *
 * Installation ISP dans AWB de CWF La position de la source lumineuse 
 *
 * @param[in] isp_wb_attr CWF Coordonnées de la position de la source lumineuse 
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
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
 * @fn int IMP_ISP_Tuning_SetMaxAgain (gain uint32_t)
 *
 * Installation sensor Vous pouvez définir le maximum Again . 
 *
 * @param[in] Le maximum que le capteur de gain peut régler est de nouveau: 0 signifie 1x, 32 signifie 2x, et ainsi de suite.
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);

/**
 * @fn int IMP_ISP_Tuning_GetMaxAgain (uint32_t * gain)
 *
 * Obtenir sensor Vous pouvez définir le maximum Again . 
 *
 * @param[out] gain sensor Le maximum qui peut être défini again.0 Moyens 1x，32 Moyens 2x， Etc. 
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetMaxDgain (gain uint32_t)
 *
 * Installation ISP Le maximum qui peut être défini Dgain . 
 *
 * @param[in] Le gain maximal qui peut être défini par le FAI Dgain.0 signifie 1x, 32 signifie 2x, et ainsi de suite.
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain);

/**
 * @fn int IMP_ISP_Tuning_GetMaxDgain (uint32_t * gain)
 *
 * Obtenir ISP Définir le maximum Dgain . 
 *
 * @param[out] ISP Dgain peut obtenir le gain maximum défini.0 signifie 1x, 32 signifie 2x, et ainsi de suite.
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);

/**
 * @fn int IMP_ISP_Tuning_SetVideoDrop (void (* cb) (void))
 *
 * Réglez la fonction de perte vidéo. sensor En cas de problème avec la ligne de connexion à la carte mère ， La fonction de rappel définie sera exécutée. 
 *
 * @param[in] fonction de rappel cb.
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void));

/**
 * @fn int IMP_ISP_Tuning_SetHiLightDepress (force uint32_t)
 *
 * Réglez l'intensité de la forte suppression de la lumière. 
 *
 * @param[in] force Le paramètre d'intensité de suppression de la lumière forte La plage de valeurs est [0-10], 0 signifie que la fonction est désactivée.
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength);

/**
 * @fn int IMP_ISP_Tuning_SetTemperStrength (rapport uint32_t)
 *
 * Installation 3D Intensité de la réduction du bruit. 
 *
 * @param[in] ratio: Le rapport de réglage de l'intensité. S'il est réglé sur 90, cela signifie qu'il est réglé sur 90% de la valeur par défaut. La plage de valeurs est [50-150].
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetSinterStrength (rapport uint32_t)
 *
 * Installation 2D Intensité de la réduction du bruit. 
 *
 * @param[in] ratio Rapport d'ajustement d'intensité . Si défini sur 90 Moyens définis sur la valeur par défaut 90%. La plage de valeurs est [ 50-150].
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
 *
 * @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
 */
int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio);

/**
 * @fn int IMP_ISP_Tuning_SetDPStrength (rapport uint32_t)
 *
 * Installation DPC force. 
 *
 * @param[in] ratio Rapport d'ajustement d'intensité . Si défini sur 90 Moyens définis sur la valeur par défaut 90%. La plage de valeurs est [ 50-150].
 *
 * @retval 0 succès 
 * @retval non-0 échec ， Renvoyer le code d'erreur 
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
* @fn int IMP_ISP_Tuning_SetAntiFogAttr (IMPISPAntiFogAttr attr)
*
* Installation ANTIFOG Les attributs. 
* @param[in] attr Paramètres d'attribut ANTIFOG
*
* @retval 0 succès 
* @retval non-0 échec ， Renvoyer le code d'erreur 
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
* @fn int IMP_ISP_Tuning_GetEVAttr (IMPISPEVAttr * attr)
*
* Obtenir EV Les attributs. 
* @param[out] attr Paramètres d'attribut EV
*
* @retval 0 succès 
* @retval non-0 échec ， Renvoyer le code d'erreur 
*
* @attention Avant d'utiliser cette fonction ，IMP_ISP_EnableTuning A été appelé. 
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
