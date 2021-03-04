/*
 * Audio utils header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_AUDIO_H__
#define __IMP_AUDIO_H__

#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP  Fichiers d'en-tête d'entrée et de sortie audio 
 */

/**
 * @defgroup IMP_Audio
 * @ingroup imp
 * @brief  Module audio ， Y compris l'enregistrement et la lecture, le codec audio, les paramètres de volume et de gain, l'annulation d'écho, le gain automatique et d'autres fonctions 
 *
 * @section audio_summary 1  Aperçu 
 *  La fonction audio comprend une entrée audio , Sortie audio , Annulation d'écho , Encodage audio et décodage audio 5 Modules . \n
 *  Parmi eux, l'entrée audio et la sortie audio ont le concept d'équipement et de canaux . L'un des MIC Nous pensons que c'est un Device, Et une MIC Il peut y avoir plusieurs Channel Entrer . \n
 *  Le même SPK Nous pensons que c'est une annonce Device, Nous pensons que c'est une annonce SPK Il peut également y avoir plusieurs Channel Production . \n
 *  Audio de la version actuelle API Une Device Prend en charge un seul Channel. \n
 *  L'annulation de l'écho est située dans l'interface d'entrée audio , Des instructions spécifiques sont reflétées dans la description de la fonction . \n
 *  Codage audio audio actuel API Support moyen PT_G711A [[[ PT_G711U avec PT_G726 Formater l'encodage audio , Si vous devez ajouter une nouvelle méthode d'encodage , Besoin d'enregistrer l'encodeur . \n
 *  Décodage audio audio actuel API Décodage audio audio actuel PT_G711A Décodage audio audio actuel PT_G711U Décodage audio audio actuel PT_G726 Formater le décodage audio , Si vous devez ajouter une nouvelle méthode de décodage , Besoin d'enregistrer le décodeur . \n
 * @section audio_function_description 2  Description de la fonction 
 *  Ce qui suit est une description spécifique de chaque module 
 * @subsection audio_in 2.1  Entrée audio 
 *  Entrée audio Device ID  Correspondance , 0:  Numéro correspondant MIC  1:  Simulation correspondante MIC \n
 *  Simulation correspondante Channel actuel API Supporte uniquement 1 Chaînes . \n
 *  Réglage du volume d'entrée audio , La plage de volume est [-30 ~ 120]. -30 Signifie muet ,120 Moyens d'amplifier le son 30dB, Taille de pas 0.5dB. parmi eux 60 Est un point critique pour le réglage du volume ，\n
 *  Le logiciel n'augmente ni ne diminue le volume à cette valeur ， Lorsque la valeur du volume est inférieure à 60 Temps ， Chaque goutte 1， Baisser le volume 0.5dB ; Lorsque la valeur du volume est supérieure à 60 ; Lorsque la valeur du volume est supérieure à ， Augmenter 1， Augmentation de volume 0.5dB . 
 * @subsection audio_out 2.2  . 
 *  . Device ID  . , 0:  Correspondant à la valeur par défaut SPK 1:  Correspond à d'autres SPK \n
 *  Correspond à d'autres Channel Correspond à d'autres API Correspond à d'autres 1 Correspond à d'autres . \n
 *  Réglage du volume de sortie audio , Réglage du volume de sortie audio [-30 ~ 120]. -30 Réglage du volume de sortie audio ,120 Réglage du volume de sortie audio 30dB, Réglage du volume de sortie audio 0.5dB. Réglage du volume de sortie audio 60 Réglage du volume de sortie audio ，\n
 *  Réglage du volume de sortie audio ， Réglage du volume de sortie audio 60 Réglage du volume de sortie audio ， Réglage du volume de sortie audio 1， Réglage du volume de sortie audio 0.5dB Réglage du volume de sortie audio 60 Réglage du volume de sortie audio ， Réglage du volume de sortie audio 1， Réglage du volume de sortie audio 0.5dB. \n
 * @subsection audio_aec 2.3  Réglage du volume de sortie audio 
 *  L'annulation de l'écho est une fonction de l'interface d'entrée audio , Par conséquent, le périphérique d'entrée audio et le canal doivent être activés avant d'activer l'annulation d'écho . \n
 *  L'annulation de l'écho prend actuellement en charge le taux d'échantillonnage audio 8K L'annulation de l'écho prend actuellement en charge le taux d'échantillonnage audio 16K， Le nombre d'échantillons de données dans une trame est 10ms Multiples entiers de données audio (tels que: 8K Taux d'échantillonnage ，  Les données envoyées sont: 8000  ×  2 / 100 = 160byte Multiples entiers de). \n
 *  Annulation d'écho pour différents appareils ， Différents forfaits ， L'annulation de l'écho aura des effets différents . \n
 *  L'annulation d'écho ne prend actuellement pas en charge la fonction adaptative ， Il existe donc des paramètres d'annulation d'écho distincts pour différents appareils , \n
 *  Le fichier de paramètres pour l'annulation d'écho se trouve dans /etc/webrtc_profile.ini  Fichier de configuration . \n
 *  Le format du fichier de configuration est le suivant ( Les trois principaux paramètres à déboguer sont répertoriés ci-dessous ): \n
 * [Set_Far_Frame] \n
 * Frame_V=0.3 \n
 * [Set_Near_Frame] \n
 * Frame_V=0.1 \n
 * delay_ms=150 \n
 *
 *  Le premier label [Set_Far_Frame] Le contenu de représente le paramètre distant , lequel est SPK Terminer les paramètres de données de lecture . \n
 * Fram_V  Représente le rapport d'amplitude audio , Ajustez ce paramètre pour ajuster l'amplitude des données de lecture ( Cette amplitude n'est utilisée que pour l'annulation d'écho ). \n
 *  Cette amplitude n'est utilisée que pour l'annulation d'écho [Set_Near_Frame] Le contenu dans représente le paramètre proche , Le contenu dans représente le paramètre proche MIC Terminer l'enregistrement des paramètres de données . \n
 * Fram_V  Terminer l'enregistrement des paramètres de données , Ajustez ce paramètre pour ajuster l'amplitude des données enregistrées ( Ajustez ce paramètre pour ajuster l'amplitude des données enregistrées ). \n
 * delay_ms  En raison du retard du logiciel et du matériel , Et SPK contre MIC Est placé à une certaine distance ,SPK Les données de lecture seront MIC échantillonnage , et donc SPK Données en MIC Il y aura un certain retard dans les données . \n
 *  Cette heure représente la différence de temps entre les données de lecture et les données d'enregistrement . \n

 * @subsection audio_enc 2.4  Codage audio 
 *  Codage audio audio actuel API Etre prêt PT_G711A Etre prêt PT_G711U Etre prêt PT_G726 Etre prêt , Si vous devez ajouter une nouvelle méthode d'encodage , Besoin d'appeler IMP_AENC_RegisterEncoder Interface pour enregistrer le codeur .
 * @subsection audio_dec 2.5  Décodage audio 
 *  Décodage audio audio actuel API Décodage audio audio actuel PT_G711A Décodage audio audio actuel PT_G711U Décodage audio audio actuel PT_G726 Décodage audio audio actuel , Si vous devez ajouter une nouvelle méthode de décodage , Si vous devez ajouter une nouvelle méthode de décodage IMP_ADEC_RegisterDecoder Interface pour enregistrer le décodeur .
 * @{
 */

/**
 *  Nombre maximum de tampons de trame audio 
 */
#define MAX_AUDIO_FRAME_NUM 50

/**
 *  Type de blocage du flux audio 
 */
typedef enum {
	BLOCK = 0,				/**<  bloquer  */
	NOBLOCK = 1,			/**<  Non bloquant  */
} IMPBlock;

/**
 *  Définition du taux d'échantillonnage audio .
 */
typedef enum {
	AUDIO_SAMPLE_RATE_8000	= 8000,		/**< 8KHz Définition du taux d'échantillonnage audio  */
	AUDIO_SAMPLE_RATE_16000 = 16000,	/**< 16KHz Définition du taux d'échantillonnage audio  */
	AUDIO_SAMPLE_RATE_44100 = 44100,	/**< 44.1KHz Définition du taux d'échantillonnage audio  */
	AUDIO_SAMPLE_RATE_48000 = 48000,	/**< 48KHz Définition du taux d'échantillonnage audio  */
	AUDIO_SAMPLE_RATE_96000 = 96000,	/**< 96KHz Définition du taux d'échantillonnage audio  */
} IMPAudioSampleRate;

/**
 *  Définition de la précision d'échantillonnage audio .
 */
typedef enum {
	AUDIO_BIT_WIDTH_16 = 16,		/**< 16bit Précision d'échantillonnage  */
} IMPAudioBitWidth;

/**
 *  Définition du mode de canal audio .
 */
typedef enum {
	AUDIO_SOUND_MODE_MONO	= 1,	/**<  Mono  */
	AUDIO_SOUND_MODE_STEREO = 2,	/**<  Deux canaux  */
} IMPAudioSoundMode;

/**
 *  Définir l'énumération du type de charge utile audio .
 */
typedef enum {
	PT_PCM		= 0,
	PT_G711A	= 1,
	PT_G711U	= 2,
	PT_G726 	= 3,
	PT_AEC		= 4,
	PT_ADPCM	= 5,
	PT_MAX		= 6,
} IMPAudioPalyloadType;

/**
 *  Définir la méthode de décodage .
 */
typedef enum {
	ADEC_MODE_PACK   = 0,	/**< Pack  Façon de décoder  */
	ADEC_MODE_STREAM = 1,	/**< Stream  Façon de décoder  */
} IMPAudioDecMode;

/**
 *  Propriétés du périphérique d'entrée et de sortie audio .
 */
typedef struct {
	IMPAudioSampleRate samplerate;		/**<  Taux d'échantillonnage audio  */
	IMPAudioBitWidth bitwidth;			/**<  Précision d'échantillonnage audio  */
	IMPAudioSoundMode soundmode;		/**<  Mode canal audio  */
	int frmNum;							/**<  Nombre de trames tamponnées ,  Gammes :[2, MAX_AUDIO_FRAME_NUM] */
	int numPerFrm;						/**<  Nombre de points d'échantillonnage par trame  */
	int chnCnt;							/**<  Nombre de canaux pris en charge  */
} IMPAudioIOAttr;

/**
 *  Structure de trame audio .
 */
typedef struct {
	IMPAudioBitWidth bitwidth;			/**<  Structure de trame audio  */
	IMPAudioSoundMode soundmode;		/**<  Structure de trame audio  */
	uint32_t *virAddr;					/**<  Adresse virtuelle des données de trame audio  */
	uint32_t phyAddr;					/**<  Adresse physique des données de trame audio  */
	int64_t timeStamp;					/**<  Horodatage des données de trame audio  */
	int seq;							/**<  Numéro de trame audio  */
	int len;							/**<  Longueur de la trame audio  */
} IMPAudioFrame;

/**
 *  Structure des paramètres du canal audio .
 */
typedef struct {
	int usrFrmDepth;					/**<  Profondeur de la mémoire tampon d'image audio  */
	int Rev;							/**<  Garder  */
} IMPAudioIChnParam;

/**
 *  Structure de l'état du tampon de données du canal de sortie audio .
 */
typedef struct {
	int chnTotalNum;				/**<  Le nombre total de blocs tampons du canal de sortie  */
	int chnFreeNum;					/**<  Nombre de blocs de cache gratuits  */
	int chnBusyNum;					/**<  Nombre de blocs de cache occupés  */
} IMPAudioOChnState;

/**
 *  Définir la structure du flux audio .
 */
typedef struct {
	uint8_t *stream;				/**<  Pointeur de flux de données  */
	uint32_t phyAddr;				/**<  Adresse physique du flux de données  */
	int len;						/**<  Longueur du flux audio  */
	int64_t timeStamp;				/**<  Horodatage  */
	int seq;						/**<  Numéro de série du flux audio  */
} IMPAudioStream;

/**
 *  Définir la structure d'attribut du canal de codage audio .
 */
typedef struct {
	IMPAudioPalyloadType type;				/**<  Type de données de charge utile audio  */
	int bufSize;							/**<  buf  Taille ， Dans les cadres ，[2 ~ MAX_AUDIO_FRAME_NUM] */
	uint32_t *value;						/**<  Pointeur d'attribut de protocole  */
} IMPAudioEncChnAttr;

/**
 *  Définir la structure des attributs du codeur .
 */
typedef struct {
	IMPAudioPalyloadType type;		/**<  Type de protocole de codage  */
	int maxFrmLen;					/**<  Longueur maximale du flux  */
	char name[16];					/**<  Nom du codeur  */
	int (*openEncoder)(void *encoderAttr, void
			*encoder);
	int (*encoderFrm)(void *encoder, IMPAudioFrame
			*data, unsigned char *outbuf,int *outLen);
	int (*closeEncoder)(void *encoder);
} IMPAudioEncEncoder;

/**
 *  Définir la structure d'attribut du canal de décodage .
 */
typedef struct {
	IMPAudioPalyloadType type;			/**<  Type de protocole de décodage audio  */
	int bufSize;						/**<  Taille du tampon de décodage audio  */
	IMPAudioDecMode mode;				/**<  Méthode de décodage  */
	void *value;						/**<  Pointeur d'attribut de protocole spécifique  */
} IMPAudioDecChnAttr;

/**
 *  Définir la structure des attributs du décodeur .
 */
typedef struct {
	IMPAudioPalyloadType type;		/**<  Définir la structure des attributs du décodeur  */
	char name[16];					/**<  Nom du décodeur audio  */
	int (*openDecoder)(void *decoderAttr, void
			*decoder);
	int (*decodeFrm)(void *decoder, unsigned char
			*inbuf,int inLen, unsigned short *outbuf,int
			*outLen,int *chns);
	int (*getFrmInfo)(void *decoder, void *info);
	int (*closeDecoder)(void *decoder);
} IMPAudioDecDecoder;

/**
 *  définition AGC Structure de gain .
 */
typedef struct {
	int TargetLevelDbfs;	/**<  Niveau de gain , La valeur est [0, 31],  Cela fait référence au niveau de volume cible , l'unité est db, Négatif . Plus la valeur est petite , Plus fort . */
	int CompressionGaindB;	/**<  Définir la valeur de gain maximum ,[0, 90],0 Signifie pas de gain , Valeur plus élevée , Gain plus élevé . */
} IMPAudioAgcConfig;

/**
 *  Définir le niveau de suppression du bruit .
 */
enum Level_ns {
	NS_LOW,			/**<  Suppression du bruit de bas niveau  */
	NS_MODERATE,	/**<  Suppression du bruit de niveau moyen  */
	NS_HIGH,		/**<  Suppression du bruit de haut niveau  */
	NS_VERYHIGH		/**<  Le plus haut niveau de suppression du bruit  */
};

/**
 * @fn int IMP_AI_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr)
 *
 *  Définir les propriétés du périphérique d'entrée audio .
 *
 * @param[in] audioDevId  Numéro du périphérique audio .
 * @param[in] attr  Pointeur d'attribut de périphérique audio .
 *
 * @retval 0  Succès .
 * @retval  non- 0  échec .
 *
 * @remarks  Exemple de code 
 * @code
 * int devID = 1;
 * IMPAudioIOAttr attr;
 * attr.samplerate = AUDIO_SAMPLE_RATE_8000;
 * attr.bitwidth = AUDIO_BIT_WIDTH_16;
 * attr.soundmode = AUDIO_SOUND_MODE_MONO;
 * attr.frmNum = 20;
 * attr.numPerFrm = 400;
 * attr.chnCnt = 1;
 * ret = IMP_AI_SetPubAttr(devID, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Set Audio in %d attr err: %d\n", devID, ret);
 *		return ret;
 * }
 * @endcode
 *
 * @attention  Besoin d'être dans IMP_AI_Enable Appelez avant .
 */
int IMP_AI_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AI_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr)
 *
 *  Obtenir les propriétés du périphérique d'entrée audio .
 *
 * @param[in] audioDevId  Obtenir les propriétés du périphérique d'entrée audio .
 * @param[out] attr  Obtenir les propriétés du périphérique d'entrée audio .
 *
 * @retval 0  Obtenir les propriétés du périphérique d'entrée audio .
 * @retval  Obtenir les propriétés du périphérique d'entrée audio 0  Obtenir les propriétés du périphérique d'entrée audio .
 *
 * @remarks  non .
 *
 * @attention  non .
 */
int IMP_AI_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AI_Enable(int audioDevId)
 *
 *  Activer le périphérique d'entrée audio .
 *
 * @param[in] audioDevId  Activer le périphérique d'entrée audio .
 *
 * @retval 0  Activer le périphérique d'entrée audio .
 * @retval  Activer le périphérique d'entrée audio 0  Activer le périphérique d'entrée audio .
 *
 * @remarks  Activer le périphérique d'entrée audio .
 *
 * @attention  Doit être appelé avant d'appeler cette fonction  IMP_AI_SetPubAttr().
 */
int IMP_AI_Enable(int audioDevId);

/**
 * @fn int IMP_AI_Disable(int audioDevId)
 *
 *  Désactiver le périphérique d'entrée audio .
 *
 * @param[in] audioDevId  Désactiver le périphérique d'entrée audio .
 *
 * @retval 0  Désactiver le périphérique d'entrée audio .
 * @retval  Désactiver le périphérique d'entrée audio 0  Désactiver le périphérique d'entrée audio .
 *
 * @remarks  Désactiver le périphérique d'entrée audio .
 *
 * @attention  Désactiver le périphérique d'entrée audio IMP_AI_Enable Soutenir l'utilisation de , Doit être exécuté avant que le système ne se mette en veille IMP_AI_Disable.
 */
int IMP_AI_Disable(int audioDevId);

/**
 * @fn int IMP_AI_EnableChn(int audioDevId, int aiChn)
 *
 *  Activer le canal d'entrée audio .
 *
 * @param[in] audioDevId  Activer le canal d'entrée audio .
 * @param[in] aiChn  Numéro de canal d'entrée audio .
 *
 * @retval 0  Numéro de canal d'entrée audio .
 * @retval  Numéro de canal d'entrée audio 0  Numéro de canal d'entrée audio .
 *
 * @remarks  Numéro de canal d'entrée audio .
 *
 * @attention  Doit être activé en premier device.
 */
int IMP_AI_EnableChn(int audioDevId, int aiChn);

/**
 * @fn int IMP_AI_DisableChn(int audioDevId, int aiChn)
 *
 *  Désactiver le canal d'entrée audio .
 *
 * @param[in] audioDevId  Désactiver le canal d'entrée audio .
 * @param[in] aiChn  Désactiver le canal d'entrée audio .
 *
 * @retval 0  Désactiver le canal d'entrée audio .
 * @retval  Désactiver le canal d'entrée audio 0  Désactiver le canal d'entrée audio .
 *
 * @remarks  Désactiver le canal d'entrée audio .
 *
 * @attention  Désactiver le canal d'entrée audio IMP_AI_EnableChn Désactiver le canal d'entrée audio .
 */
int IMP_AI_DisableChn(int audioDevId, int aiChn);

/**
 * @fn int IMP_AI_PollingFrame(int audioDevId, int aiChn, unsigned int timeout_ms)
 *
 * Polling Tampon de flux audio .
 *
 * @param[in] audioDevId  Tampon de flux audio .
 * @param[in] aiChn  Tampon de flux audio .
 * @param[in] timeout_ms Polling temps supplémentaire .
 *
 * @retval 0  temps supplémentaire .
 * @retval  temps supplémentaire 0  temps supplémentaire .
 *
 * @remarks  temps supplémentaire .
 *
 * @attention  Utilisé IMP_AI_GetFrame L'interface était utilisée avant ， Lorsque l'interface est appelée avec succès, cela signifie audio 
 *			   Les données sont prêtes ， peut utiliser IMP_AI_GetFrame Obtenez des données audio .
 */
int IMP_AI_PollingFrame(int audioDevId, int aiChn, unsigned int timeout_ms);

/**
 * @fn int IMP_AI_GetFrame(int audioDevId, int aiChn, IMPAudioFrame *frm, IMPBlock block)
 *
 *  Obtenir une image audio .
 *
 * @param[in] audioDevId  Obtenir une image audio .
 * @param[in] aiChn  Obtenir une image audio .
 * @param[out] frm  Pointeur de structure de trame audio .
 * @param[in] block  Pointeur de structure de trame audio / Drapeau non bloquant .
 *
 * @retval 0  Drapeau non bloquant .
 * @retval  Drapeau non bloquant 0  Drapeau non bloquant .
 *
 * @remarks  Drapeau non bloquant 
 * @code
 * IMPAudioFrame frm;
 * //  Drapeau non bloquant 
 * ret = IMP_AI_GetFrame(devID, chnID, &frm, BLOCK);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Get Frame Data error\n");
 *		return ret;
 * }
 *
 * fwrite(frm.virAddr, 1, frm.len, record_file); //  Utiliser les données de trame audio 
 *
 * //  Libérer le cadre audio 
 * ret = IMP_AI_ReleaseFrame(devID, chnID, &frm);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio release frame data error\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention  Libérer le cadre audio .
 */
int IMP_AI_GetFrame(int audioDevId, int aiChn, IMPAudioFrame *frm, IMPBlock block);

/**
 * @fn int IMP_AI_ReleaseFrame(int audioDevId, int aiChn, IMPAudioFrame *frm)
 *
 *  Libérer le cadre audio .
 *
 * @param[in] audioDevId  Libérer le cadre audio .
 * @param[in] aiChn  Libérer le cadre audio .
 * @param[in] frm  Libérer le cadre audio .
 *
 * @retval 0  Libérer le cadre audio .
 * @retval  Libérer le cadre audio 0  Libérer le cadre audio .
 *
 * @remarks  Libérer le cadre audio .
 *
 * @attention  Libérer le cadre audio IMP_AI_GetFrame Libérer le cadre audio .
 */
int IMP_AI_ReleaseFrame(int audioDevId, int aiChn, IMPAudioFrame *frm);

/**
 * @fn int IMP_AI_SetChnParam(int audioDevId, int aiChn, IMPAudioIChnParam *chnParam)
 *
 *  Définir les paramètres du canal d'entrée audio .
 *
 * @param[in] audioDevId  Définir les paramètres du canal d'entrée audio .
 * @param[in] aiChn  Définir les paramètres du canal d'entrée audio .
 * @param[in] chnParam  Paramètres du canal audio .
 *
 * @retval 0  Paramètres du canal audio .
 * @retval  Paramètres du canal audio 0  Paramètres du canal audio .
 *
 * @remarks  Paramètres du canal audio 
 * @code
 * int chnID = 0;
 * IMPAudioIChnParam chnParam;
 * chnParam.usrFrmDepth = 20;	// the range of valid value is [2, MAX_AUDIO_FRAME_NUM].
 * ret = IMP_AI_SetChnParam(devID, chnID, &chnParam);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "set ai %d channel %d attr err: %d\n", devID, chnID, ret);
 *		return ret;
 * }
 * @endcode
 *
 * @attention  dans IMP_AI_EnableChn dans .
 */
int IMP_AI_SetChnParam(int audioDevId, int aiChn, IMPAudioIChnParam *chnParam);

/**
 * @fn int IMP_AI_GetChnParam(int audioDevId, int aiChn, IMPAudioIChnParam *chnParam)
 *
 *  Obtenir les paramètres du canal d'entrée audio .
 *
 * @param[in] audioDevId  Obtenir les paramètres du canal d'entrée audio .
 * @param[in] aiChn  Obtenir les paramètres du canal d'entrée audio .
 * @param[out] chnParam  Obtenir les paramètres du canal d'entrée audio .
 *
 * @retval 0  Obtenir les paramètres du canal d'entrée audio .
 * @retval  Obtenir les paramètres du canal d'entrée audio 0  Obtenir les paramètres du canal d'entrée audio .
 *
 * @remarks  Obtenir les paramètres du canal d'entrée audio .
 *
 * @attention  Obtenir les paramètres du canal d'entrée audio .
 */
int IMP_AI_GetChnParam(int audioDevId, int aiChn, IMPAudioIChnParam *chnParam);

/**
 * @fn int IMP_AI_EnableAec(int aiDevId, int aiChn, int aoDevId, int aoChn)
 *
 *  Activer la fonction d'annulation d'écho de l'entrée audio et de la sortie audio spécifiées .
 *
 * @param[in] aiDevId  Numéro de périphérique d'entrée audio nécessitant une annulation d'écho .
 * @param[in] aiChn  Numéro de canal d'entrée audio nécessitant une annulation d'écho .
 * @param[in] aoDevId  Numéro du périphérique de sortie audio nécessitant une annulation d'écho .
 * @param[in] aoChn  Numéro de canal de sortie audio nécessitant une annulation d'écho .
 *
 * @retval 0  Numéro de canal de sortie audio nécessitant une annulation d'écho .
 * @retval  Numéro de canal de sortie audio nécessitant une annulation d'écho 0  Numéro de canal de sortie audio nécessitant une annulation d'écho .
 *
 * @remarks  Numéro de canal de sortie audio nécessitant une annulation d'écho ， Numéro de canal de sortie audio nécessitant une annulation d'écho ， Numéro de canal de sortie audio nécessitant une annulation d'écho .
 * @remarks  Numéro de canal de sortie audio nécessitant une annulation d'écho ， Numéro de canal de sortie audio nécessitant une annulation d'écho ,
 * @remarks  Le simple fait d'activer la fonction n'est pas nécessairement bon. 
 * @remarks  Le simple fait d'activer la fonction n'est pas nécessairement bon. /etc/webrtc_profile.ini  Le simple fait d'activer la fonction n'est pas nécessairement bon. .
 * @remarks  Le simple fait d'activer la fonction n'est pas nécessairement bon. ( Le simple fait d'activer la fonction n'est pas nécessairement bon. ):
 * @remarks [Set_Far_Frame]
 * @remarks Frame_V=0.3
 * @remarks [Set_Near_Frame]
 * @remarks Frame_V=0.1
 * @remarks delay_ms=150
 *
 * @remarks  Le simple fait d'activer la fonction n'est pas nécessairement bon. [Set_Far_Frame] Le simple fait d'activer la fonction n'est pas nécessairement bon. , Le simple fait d'activer la fonction n'est pas nécessairement bon. SPK Le simple fait d'activer la fonction n'est pas nécessairement bon. .
 * @remarks Fram_V  Le simple fait d'activer la fonction n'est pas nécessairement bon. , Le simple fait d'activer la fonction n'est pas nécessairement bon. ( Le simple fait d'activer la fonction n'est pas nécessairement bon. ).
 * @remarks  Le simple fait d'activer la fonction n'est pas nécessairement bon. [Set_Near_Frame] Le simple fait d'activer la fonction n'est pas nécessairement bon. , Le simple fait d'activer la fonction n'est pas nécessairement bon. MIC Le simple fait d'activer la fonction n'est pas nécessairement bon. .
 * @remarks Fram_V  Le simple fait d'activer la fonction n'est pas nécessairement bon. , Le simple fait d'activer la fonction n'est pas nécessairement bon. ( Le simple fait d'activer la fonction n'est pas nécessairement bon. ).
 * @remarks delay_ms  Le simple fait d'activer la fonction n'est pas nécessairement bon. , Le simple fait d'activer la fonction n'est pas nécessairement bon. SPK Le simple fait d'activer la fonction n'est pas nécessairement bon. MIC Le simple fait d'activer la fonction n'est pas nécessairement bon. ,SPK Le simple fait d'activer la fonction n'est pas nécessairement bon. MIC Le simple fait d'activer la fonction n'est pas nécessairement bon. , Le simple fait d'activer la fonction n'est pas nécessairement bon. SPK Le simple fait d'activer la fonction n'est pas nécessairement bon. MIC Le simple fait d'activer la fonction n'est pas nécessairement bon. .
 * @remarks  Le simple fait d'activer la fonction n'est pas nécessairement bon. .
 *
 * @attention  En fait, l'interface ne vérifiera que aiDevId En fait, l'interface ne vérifiera que aiChn. Mais il est préférable d'appeler une fois que les deux canaux sont activés en même temps . \n
 *  Lors de la fermeture du canal d'entrée audio , La fonction d'annulation d'écho est désactivée en même temps . Si vous devez l'utiliser à nouveau, vous devez l'ouvrir à nouveau .
 */
int IMP_AI_EnableAec(int aiDevId, int aiChn, int aoDevId, int aoChn);

/**
 * @fn int IMP_AI_DisableAec(int aiDevId, int aiChn)
 *
 *  Désactiver l'annulation d'écho .
 *
 * @param[in] aiDevId  Numéro de périphérique d'entrée audio .
 * @param[in] aiChn  Numéro de périphérique d'entrée audio .
 *
 * @retval 0  Numéro de périphérique d'entrée audio .
 * @retval  Numéro de périphérique d'entrée audio 0  Numéro de périphérique d'entrée audio .
 *
 * @remarks  Numéro de périphérique d'entrée audio .
 *
 * @attention  Numéro de périphérique d'entrée audio .
 */
int IMP_AI_DisableAec(int aiDevId, int aiChn);

/**
 * @fn int IMP_AI_EnableNs(IMPAudioIOAttr *attr, int mode)
 *
 *  Activer la fonction de suppression du bruit de l'entrée audio spécifiée .
 *
 * @param[in] attr  Attributs audio nécessitant une suppression du bruit .
 * @param[in] mode  Niveau de suppression du bruit 0  Niveau de suppression du bruit  3, Voir  Level_ns.
 *
 * @retval 0  Voir .
 * @retval  Voir 0  Voir .
 *
 * @remarks  Bruit supprimé mode Le paramètre indique le niveau de suppression du bruit , La plage est [0 ~ 3], Plus le niveau est élevé , Le plus propre la suppression du bruit .
 * @remarks  toutefois , Plus la suppression du bruit est propre, plus les détails sonores seront perdus , Il y a donc une contradiction ici , Il y a donc une contradiction ici 
 * @remarks  Faites des compromis lors de l'utilisation .
 *
 * @attention  L'annulation de l'écho inclut la suppression du bruit , Si l'annulation d'écho est activée , Pas besoin de supprimer le bruit .
 */
int IMP_AI_EnableNs(IMPAudioIOAttr *attr, int mode);

/**
 * @fn int IMP_AI_DisableNs(void)
 *
 *  Désactiver la suppression du bruit .
 *
 * @param  Désactiver la suppression du bruit .
 *
 * @retval 0  Désactiver la suppression du bruit .
 * @retval  Désactiver la suppression du bruit 0  Désactiver la suppression du bruit .
 *
 * @remarks  Désactiver la suppression du bruit .
 *
 * @attention  Désactiver la suppression du bruit .
 */
int IMP_AI_DisableNs(void);

/**
 * @fn int IMP_AI_EnableAgc(IMPAudioIOAttr *attr, IMPAudioAgcConfig agcConfig)
 *
 *  Activer la fonction de gain automatique de l'entrée audio .
 *
 * @param[in] attr  Attributs audio nécessitant un gain automatique .
 * @param[in] agcConfig  Configuration des paramètres du gain automatique , Configurer le grossissement .
 *
 * @retval 0  Configurer le grossissement .
 * @retval  Configurer le grossissement 0  Configurer le grossissement .
 *
 * @remarks  nécessite de l'attention agcConfig Configuration ,AGC Le grossissement a principalement la configuration des paramètres , Voir pour des gains spécifiques IMPAudioAgcConfig Description .
 * @remarks  doit être conscient de ,AGC Peut amplifier le gain du son , Mais si le paramètre de gain ne convient pas , Cela provoquera la rupture du son, etc. , Veuillez vous ajuster lorsque vous l'utilisez .
 *
 * @attention  L'annulation de l'écho comprend  AGC  Fonctionnalités , Fonctionnalités , Pas besoin de faire de gain automatique .
 */
int IMP_AI_EnableAgc(IMPAudioIOAttr *attr, IMPAudioAgcConfig agcConfig);

/**
 * @fn int IMP_AI_DisableAgc(void)
 *
 *  Désactiver AI Fonction de gain automatique .
 *
 * @param  Fonction de gain automatique .
 *
 * @retval 0  Fonction de gain automatique .
 * @retval  Fonction de gain automatique 0  Fonction de gain automatique .
 *
 * @remarks  Fonction de gain automatique .
 *
 * @attention  Fonction de gain automatique .
 */
int IMP_AI_DisableAgc(void);

/**
 * @fn int IMP_AO_EnableAgc(IMPAudioIOAttr *attr, IMPAudioAgcConfig agcConfig)
 *
 *  Activer la fonction de gain automatique de la sortie audio .
 *
 * @param[in] attr  Activer la fonction de gain automatique de la sortie audio .
 * @param[in] agcConfig  Activer la fonction de gain automatique de la sortie audio , Activer la fonction de gain automatique de la sortie audio .
 *
 * @retval 0  Activer la fonction de gain automatique de la sortie audio .
 * @retval  Activer la fonction de gain automatique de la sortie audio 0  Activer la fonction de gain automatique de la sortie audio .
 *
 * @remarks  Activer la fonction de gain automatique de la sortie audio agcConfig Activer la fonction de gain automatique de la sortie audio ,AGC Activer la fonction de gain automatique de la sortie audio , Activer la fonction de gain automatique de la sortie audio IMPAudioAgcConfig Activer la fonction de gain automatique de la sortie audio .
 * @remarks  Activer la fonction de gain automatique de la sortie audio ,AGC Activer la fonction de gain automatique de la sortie audio , Activer la fonction de gain automatique de la sortie audio , Activer la fonction de gain automatique de la sortie audio , Activer la fonction de gain automatique de la sortie audio .
 *
 * @attention  Activer la fonction de gain automatique de la sortie audio  AGC  Activer la fonction de gain automatique de la sortie audio , Activer la fonction de gain automatique de la sortie audio , Activer la fonction de gain automatique de la sortie audio .
 */
int IMP_AO_EnableAgc(IMPAudioIOAttr *attr, IMPAudioAgcConfig agcConfig);

/**
 * @fn int IMP_AO_DisableAgc(void)
 *
 *  Activer la fonction de gain automatique de la sortie audio AO Activer la fonction de gain automatique de la sortie audio .
 *
 * @param  Activer la fonction de gain automatique de la sortie audio .
 *
 * @retval 0  Activer la fonction de gain automatique de la sortie audio .
 * @retval  Activer la fonction de gain automatique de la sortie audio 0  Activer la fonction de gain automatique de la sortie audio .
 *
 * @remarks  Activer la fonction de gain automatique de la sortie audio .
 *
 * @attention  Activer la fonction de gain automatique de la sortie audio .
 */
int IMP_AO_DisableAgc(void);

/**
 * @fn int IMP_AI_EnableHpf(IMPAudioIOAttr *attr)
 *
 *  Activer le filtrage passe-haut de l'entrée audio .
 *
 * @param[in] attr  Attributs audio nécessitant un filtrage passe-haut .
 *
 * @retval 0  Attributs audio nécessitant un filtrage passe-haut .
 * @retval  Attributs audio nécessitant un filtrage passe-haut 0  Attributs audio nécessitant un filtrage passe-haut .
 *
 * @remarks  Attributs audio nécessitant un filtrage passe-haut .
 *
 * @attention  Attributs audio nécessitant un filtrage passe-haut  HPF  Attributs audio nécessitant un filtrage passe-haut , Attributs audio nécessitant un filtrage passe-haut , Pas besoin de faire  HPF.
 */
int IMP_AI_EnableHpf(IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AI_DisableHpf(void)
 *
 *  Pas besoin de faire AI Fonction de filtre passe-haut .
 *
 * @param  Fonction de filtre passe-haut .
 *
 * @retval 0  Fonction de filtre passe-haut .
 * @retval  Fonction de filtre passe-haut 0  Fonction de filtre passe-haut .
 *
 * @remarks  Fonction de filtre passe-haut .
 *
 * @attention  Fonction de filtre passe-haut .
 */
int IMP_AI_DisableHpf(void);

/**
 * @fn int IMP_AO_EnableHpf(IMPAudioIOAttr *attr)
 *
 *  Activer le filtrage passe-haut de la sortie audio .
 *
 * @param[in] attr  Activer le filtrage passe-haut de la sortie audio .
 *
 * @retval 0  Activer le filtrage passe-haut de la sortie audio .
 * @retval  Activer le filtrage passe-haut de la sortie audio 0  Activer le filtrage passe-haut de la sortie audio .
 *
 * @remarks  Activer le filtrage passe-haut de la sortie audio .
 *
 * @attention  Activer le filtrage passe-haut de la sortie audio  HPF  Activer le filtrage passe-haut de la sortie audio , Activer le filtrage passe-haut de la sortie audio , Activer le filtrage passe-haut de la sortie audio  HPF.
 */
int IMP_AO_EnableHpf(IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AO_DisableHpf(void)
 *
 *  Activer le filtrage passe-haut de la sortie audio AO Activer le filtrage passe-haut de la sortie audio .
 *
 * @param  Activer le filtrage passe-haut de la sortie audio .
 *
 * @retval 0  Activer le filtrage passe-haut de la sortie audio .
 * @retval  Activer le filtrage passe-haut de la sortie audio 0  Activer le filtrage passe-haut de la sortie audio .
 *
 * @remarks  Activer le filtrage passe-haut de la sortie audio .
 *
 * @attention  Activer le filtrage passe-haut de la sortie audio .
 */
int IMP_AO_DisableHpf(void);

/**
 * @fn int IMP_AO_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr)
 *
 *  Définir les propriétés du périphérique d'entrée et de sortie audio .
 *
 * @param[in] audioDevId  Définir les propriétés du périphérique d'entrée et de sortie audio .
 * @param[in] attr  Pointeur d'attribut du périphérique de sortie audio .
 *
 * @retval 0  Pointeur d'attribut du périphérique de sortie audio .
 * @retval  Pointeur d'attribut du périphérique de sortie audio 0  Pointeur d'attribut du périphérique de sortie audio .
 *
 * @remarks  Pointeur d'attribut du périphérique de sortie audio .
 *
 * @attention  Pointeur d'attribut du périphérique de sortie audio .
 */
int IMP_AO_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AO_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr)
 *
 *  Obtenir les propriétés du périphérique d'entrée et de sortie audio .
 *
 * @param[in] audioDevId  Obtenir les propriétés du périphérique d'entrée et de sortie audio .
 * @param[out] attr  Obtenir les propriétés du périphérique d'entrée et de sortie audio .
 *
 * @retval 0  Obtenir les propriétés du périphérique d'entrée et de sortie audio .
 * @retval  Obtenir les propriétés du périphérique d'entrée et de sortie audio 0  Obtenir les propriétés du périphérique d'entrée et de sortie audio .
 *
 * @remarks  Obtenir les propriétés du périphérique d'entrée et de sortie audio .
 *
 * @attention  Obtenir les propriétés du périphérique d'entrée et de sortie audio .
 */
int IMP_AO_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AO_Enable(int audioDevId)
 *
 *  Activer le périphérique de sortie audio .
 *
 * @param[in] audioDevId  Activer le périphérique de sortie audio .
 *
 * @retval 0  Activer le périphérique de sortie audio .
 * @retval  Activer le périphérique de sortie audio 0  Activer le périphérique de sortie audio .
 *
 * @remarks  Activer le périphérique de sortie audio .
 *
 * @attention  Doit être appelé avant l'activation IMP_AO_SetPubAttr.
 */
int IMP_AO_Enable(int audioDevId);

/**
 * @fn int IMP_AO_Disable(int audioDevId)
 *
 *  Désactiver le périphérique de sortie audio .
 *
 * @param[in] audioDevId  Désactiver le périphérique de sortie audio .
 *
 * @retval 0  Désactiver le périphérique de sortie audio .
 * @retval  Désactiver le périphérique de sortie audio 0  Désactiver le périphérique de sortie audio .
 *
 * @remarks  Désactiver le périphérique de sortie audio .
 *
 * @attention  Désactiver le périphérique de sortie audio .
 */
int IMP_AO_Disable(int audioDevId);

/**
 * @fn int IMP_AO_EnableChn(int audioDevId, int aoChn)
 *
 *  Activer le canal de sortie audio .
 *
 * @param[in] audioDevId  Activer le canal de sortie audio .
 * @param[in] aoChn  Numéro de canal de sortie audio .
 *
 * @retval 0  Numéro de canal de sortie audio .
 * @retval  Numéro de canal de sortie audio 0  Numéro de canal de sortie audio .
 *
 * @remarks  Numéro de canal de sortie audio .
 *
 * @attention  Numéro de canal de sortie audio .
 */
int IMP_AO_EnableChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_DisableChn(int audioDevId, int aoChn)
 *
 *  Désactiver le canal de sortie audio .
 *
 * @param[in] audioDevId  Désactiver le canal de sortie audio .
 * @param[in] aoChn  Désactiver le canal de sortie audio .
 *
 * @retval 0  Désactiver le canal de sortie audio .
 * @retval  Désactiver le canal de sortie audio 0  Désactiver le canal de sortie audio .
 *
 * @remarks  Désactiver le canal de sortie audio .
 *
 * @attention  Désactiver le canal de sortie audio .
 */
int IMP_AO_DisableChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_SendFrame(int audioDevId, int aoChn, IMPAudioFrame *data, IMPBlock block)
 *
 *  Envoyer une trame de sortie audio .
 *
 * @param[in] audioDevId  Envoyer une trame de sortie audio .
 * @param[in] aoChn  Envoyer une trame de sortie audio .
 * @param[in] data  Envoyer une trame de sortie audio .
 * @param[in] block  Envoyer une trame de sortie audio / Envoyer une trame de sortie audio .
 *
 * @retval 0  Envoyer une trame de sortie audio .
 * @retval  Envoyer une trame de sortie audio 0  Envoyer une trame de sortie audio .
 *
 * @remarks  Envoyer une trame de sortie audio 
 * @code
 * while(1) {
 *		size = fread(buf, 1, IMP_AUDIO_BUF_SIZE, play_file);
 *		if(size < IMP_AUDIO_BUF_SIZE)
 *			break;
 *
 *		IMPAudioFrame frm;
 *		frm.virAddr = (uint32_t *)buf;
 *		frm.len = size;
 *		ret = IMP_AO_SendFrame(devID, chnID, &frm, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "send Frame Data error\n");
 *			return ret;
 *		}
 * }
 * @endcode
 *
 * @attention  Envoyer une trame de sortie audio .
 */
int IMP_AO_SendFrame(int audioDevId, int aoChn, IMPAudioFrame *data, IMPBlock block);

/**
 * @fn int IMP_AO_PauseChn(int audioDevId, int aoChn)
 *
 *  Suspendre le canal de sortie audio .
 *
 * @param[in] audioDevId  Suspendre le canal de sortie audio .
 * @param[in] aoChn  Suspendre le canal de sortie audio .
 *
 * @retval 0  Suspendre le canal de sortie audio .
 * @retval  Suspendre le canal de sortie audio 0  Suspendre le canal de sortie audio .
 *
 * @remarks  Suspendre le canal de sortie audio .
 *
 * @attention  Suspendre le canal de sortie audio .
 */
int IMP_AO_PauseChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_ResumeChn(int audioDevId, int aoChn)
 *
 *  Restaurer le canal de sortie audio .
 *
 * @param[in] audioDevId  Restaurer le canal de sortie audio .
 * @param[in] aoChn  Restaurer le canal de sortie audio .
 *
 * @retval 0  Restaurer le canal de sortie audio .
 * @retval  Restaurer le canal de sortie audio 0  Restaurer le canal de sortie audio .
 *
 * @remarks  Restaurer le canal de sortie audio .
 *
 * @attention  Restaurer le canal de sortie audio .
 */
int IMP_AO_ResumeChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_ClearChnBuf(int audioDevId, int aoChn)
 *
 *  Effacer le tampon de données audio actuel dans le canal de sortie audio .
 *
 * @param[in] audioDevId  Effacer le tampon de données audio actuel dans le canal de sortie audio .
 * @param[in] aoChn  Effacer le tampon de données audio actuel dans le canal de sortie audio .
 *
 * @retval 0  Effacer le tampon de données audio actuel dans le canal de sortie audio .
 * @retval  Effacer le tampon de données audio actuel dans le canal de sortie audio 0  Effacer le tampon de données audio actuel dans le canal de sortie audio .
 *
 * @remarks  Effacer le tampon de données audio actuel dans le canal de sortie audio .
 *
 * @attention  Effacer le tampon de données audio actuel dans le canal de sortie audio .
 */
int IMP_AO_ClearChnBuf(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_QueryChnStat(int audioDevId, int aoChn, IMPAudioOChnState *status)
 *
 *  Interroger l'état actuel du tampon de données audio dans le canal de sortie audio .
 *
 * @param[in] audioDevId  Interroger l'état actuel du tampon de données audio dans le canal de sortie audio .
 * @param[in] aoChn  Interroger l'état actuel du tampon de données audio dans le canal de sortie audio .
 * @param[out] status  Pointeur de structure d'état du cache .
 *
 * @retval 0  Pointeur de structure d'état du cache .
 * @retval  Pointeur de structure d'état du cache 0  Pointeur de structure d'état du cache .
 *
 * @remarks  Pointeur de structure d'état du cache .
 *
 * @attention  Pointeur de structure d'état du cache .
 */
int IMP_AO_QueryChnStat(int audioDevId, int aoChn, IMPAudioOChnState *status);

/**
 * @fn int IMP_AENC_CreateChn(int aeChn, IMPAudioEncChnAttr *attr)
 *
 *  Créer un canal d'encodage audio .
 *
 * @param[in] aeChn  Le numéro de canal .
 * @param[in] attr  Pointeur d'attribut de canal de codage audio .
 *
 * @retval 0  Pointeur d'attribut de canal de codage audio .
 * @retval  Pointeur d'attribut de canal de codage audio 0  Pointeur d'attribut de canal de codage audio .
 *
 * @remarks  Pointeur d'attribut de canal de codage audio 
 * @code
 * int AeChn = 0;
 * IMPAudioEncChnAttr attr;
 * attr.type = PT_G711A;
 * attr.bufSize = 20;
 * ret = IMP_AENC_CreateChn(AeChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio encode create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention  Actuellement SDK Actuellement PT_G711A Actuellement PT_G711U Actuellement PT_G726 codage . \n
 *  Alors utilisez SDK Encodage en , juste besoin de attr.type = PT_G711A Peut . \n
 *  Comment utiliser un encodeur personnalisé , Vous devez enregistrer l'encodeur , L'exemple de code est expliqué dans l'interface d'inscription .
 */
 int IMP_AENC_CreateChn(int aeChn, IMPAudioEncChnAttr *attr);

/**
 * @fn int IMP_AENC_DestroyChn(int aeChn)
 *
 *  Détruire le canal d'encodage audio .
 *
 * @param[in] aeChn  Détruire le canal d'encodage audio .
 *
 * @retval 0  Détruire le canal d'encodage audio .
 * @retval  Détruire le canal d'encodage audio 0  Détruire le canal d'encodage audio .
 *
 * @remarks  Détruire le canal d'encodage audio .
 *
 * @attention  Détruire le canal d'encodage audio IMP_AENC_CreateChn Détruire le canal d'encodage audio .
 */
 int IMP_AENC_DestroyChn(int aeChn);

/**
 * @fn int IMP_AENC_SendFrame(int aeChn, IMPAudioFrame *frm)
 *
 *  Envoyer des trames audio encodées audio .
 *
 * @param[in] aeChn  Envoyer des trames audio encodées audio .
 * @param[in] frm  Envoyer des trames audio encodées audio .
 *
 * @retval 0  Envoyer des trames audio encodées audio .
 * @retval  Envoyer des trames audio encodées audio 0  Envoyer des trames audio encodées audio .
 *
 * @remarks  Envoyer des trames audio encodées audio 
 * @code
 * while(1) {
 *		//  Lire une trame de données 
 *		ret = fread(buf_pcm, 1, IMP_AUDIO_BUF_SIZE, file_pcm);
 *		if(ret < IMP_AUDIO_BUF_SIZE)
 *			break;
 *
 *		//  Lire une trame de données 
 *		IMPAudioFrame frm;
 *		frm.virAddr = (uint32_t *)buf_pcm;
 *		frm.len = ret;
 *		ret = IMP_AENC_SendFrame(AeChn, &frm);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode send frame failed\n");
 *			return ret;
 *		}
 *
 *		//  Obtenir le flux de code 
 *		IMPAudioStream stream;
 *		ret = IMP_AENC_GetStream(AeChn, &stream, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode get stream failed\n");
 *			return ret;
 *		}
 *
 *		//  Utiliser le flux de code 
 *		fwrite(stream.stream, 1, stream.len, file_g711);
 *
 *		//  Diffuser le flux de code 
 *		ret = IMP_AENC_ReleaseStream(AeChn, &stream);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode release stream failed\n");
 *			return ret;
 *		}
 * }
 * @endcode
 *
 * @attention  Diffuser le flux de code .
 */
 int IMP_AENC_SendFrame(int aeChn, IMPAudioFrame *frm);

/**
 * @fn int IMP_AENC_PollingStream(int AeChn, unsigned int timeout_ms)
 *
 * Polling Tampon de flux audio codé .
 *
 * @param[in] AeChn  Numéro de canal d'entrée de codage audio .
 * @param[in] timeout_ms Polling Numéro de canal d'entrée de codage audio .
 *
 * @retval 0  Numéro de canal d'entrée de codage audio .
 * @retval  Numéro de canal d'entrée de codage audio 0  Numéro de canal d'entrée de codage audio .
 *
 * @remarks  Numéro de canal d'entrée de codage audio .
 *
 * @attention  Numéro de canal d'entrée de codage audio IMP_AENC_GetStream Numéro de canal d'entrée de codage audio ， Numéro de canal d'entrée de codage audio 
 *			   Les données encodées sont prêtes ， Les données encodées sont prêtes IMP_AENC_GetStream Obtenez les données encodées .
 */
int IMP_AENC_PollingStream(int AeChn, unsigned int timeout_ms);

/**
 * @fn int IMP_AENC_GetStream(int aeChn, IMPAudioStream *stream ,IMPBlock block)
 *
 *  Obtenez le flux de code après l'encodage .
 *
 * @param[in] aeChn  Obtenez le flux de code après l'encodage .
 * @param[in] stream  Obtenir un flux audio .
 * @param[in] block  Obtenir un flux audio / Obtenir un flux audio .
 *
 * @retval 0  Obtenir un flux audio .
 * @retval  Obtenir un flux audio 0  Obtenir un flux audio .
 *
 * @remarks  Voir un exemple de code IMP_AENC_SendFrame Description de la fonction .
 *
 * @attention  Description de la fonction .
 */
 int IMP_AENC_GetStream(int aeChn, IMPAudioStream *stream ,IMPBlock block);

/**
 * @fn int IMP_AENC_ReleaseStream(int aeChn,IMPAudioStream *stream)
 *
 *  Libérez le flux de code obtenu à partir du canal de codage audio .
 *
 * @param[in] aeChn  Libérez le flux de code obtenu à partir du canal de codage audio .
 * @param[in] stream  Obtenir un pointeur de flux audio .
 *
 * @retval 0  Obtenir un pointeur de flux audio .
 * @retval  Obtenir un pointeur de flux audio 0  Obtenir un pointeur de flux audio .
 *
 * @remarks  Obtenir un pointeur de flux audio IMP_AENC_SendFrame Obtenir un pointeur de flux audio .
 *
 * @attention  Obtenir un pointeur de flux audio .
 */
 int IMP_AENC_ReleaseStream(int aeChn,IMPAudioStream *stream);

/**
 * @fn int IMP_AENC_RegisterEncoder(int *handle, IMPAudioEncEncoder *encoder)
 *
 *  Enregistrer l'encodeur .
 *
 * @param[in] ps32handle  Enregistrer la poignée .
 * @param[in] encoder  Structure d'attribut du codeur .
 *
 * @retval 0  Structure d'attribut du codeur .
 * @retval  Structure d'attribut du codeur 0  Structure d'attribut du codeur .
 *
 * @remarks  Structure d'attribut du codeur 
 * @code
 * int handle_g711a = 0;
 * IMPAudioEncEncoder my_encoder;
 * my_encoder.maxFrmLen = 1024;
 * sprintf(my_encoder.name, "%s", "MY_G711A");
 * my_encoder.openEncoder = NULL; //  Fonction de rappel de l'encodeur 
 * my_encoder.encoderFrm = MY_G711A_Encode_Frm; //  Fonction de rappel de l'encodeur 
 * my_encoder.closeEncoder = NULL; //  Fonction de rappel de l'encodeur 
 *
 * ret = IMP_AENC_RegisterEncoder(&handle_g711a, &my_encoder);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "IMP_AENC_RegisterEncoder failed\n");
 *		return ret;
 * }
 *
 * //  Utiliser l'encodeur 
 * int AeChn = 0;
 * IMPAudioEncChnAttr attr;
 * attr.type = handle_g711a; //  Encodeur type Égal au retour d'une inscription réussie handle_g711a La valeur de .
 * attr.bufSize = 20;
 * ret = IMP_AENC_CreateChn(AeChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "imp audio encode create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention  Comment utiliser et utiliser après l'enregistrement SDK Identique à l'encodeur intégré .
 */
 int IMP_AENC_RegisterEncoder(int *handle, IMPAudioEncEncoder *encoder);

/**
 * @fn int IMP_AENC_ReleaseEncoder(int *handle)
 *
 *  Déconnectez-vous de l'encodeur .
 *
 * @param[in] ps32handle  Déconnectez-vous de l'encodeur ( Handle obtenu lors de l'enregistrement du codeur ).
 *
 * @retval 0  Handle obtenu lors de l'enregistrement du codeur .
 * @retval  Handle obtenu lors de l'enregistrement du codeur 0  Handle obtenu lors de l'enregistrement du codeur .
 *
 * @remarks  Handle obtenu lors de l'enregistrement du codeur .
 *
 * @attention  Handle obtenu lors de l'enregistrement du codeur .
 */
 int IMP_AENC_ReleaseEncoder(int *handle);

/**
 * @fn int IMP_ADEC_CreateChn(int adChn, IMPAudioDecChnAttr *attr)
 *
 *  Créer un canal de décodage audio .
 *
 * @param[in] adChn  Créer un canal de décodage audio .
 * @param[in] attr  Pointeur d'attribut de canal .
 *
 * @retval 0  Pointeur d'attribut de canal .
 * @retval  Pointeur d'attribut de canal 0  Pointeur d'attribut de canal .
 *
 * @remarks  Pointeur d'attribut de canal 
 * @code
 * int adChn = 0;
 * IMPAudioDecChnAttr attr;
 * attr.type = PT_G711A;
 * attr.bufSize = 20;
 * attr.mode = ADEC_MODE_PACK;
 * ret = IMP_ADEC_CreateChn(adChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "imp audio decoder create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention  Pointeur d'attribut de canal .
 */
 int IMP_ADEC_CreateChn(int adChn, IMPAudioDecChnAttr *attr);

/**
 * @fn int IMP_ADEC_DestroyChn(int adChn)
 *
 *  Détruire le canal de décodage audio .
 *
 * @param[in] adChn  Détruire le canal de décodage audio .
 *
 * @retval 0  Détruire le canal de décodage audio .
 * @retval  Détruire le canal de décodage audio 0  Détruire le canal de décodage audio .
 *
 * @remarks  Détruire le canal de décodage audio .
 *
 * @attention  Détruire le canal de décodage audio .
 */
 int IMP_ADEC_DestroyChn(int adChn);

/**
 * @fn int IMP_ADEC_SendStream(int adChn, IMPAudioStream *stream, IMPBlock block)
 *
 *  Envoyer le flux de code audio au canal de décodage audio .
 *
 * @param[in] adChn  Envoyer le flux de code audio au canal de décodage audio .
 * @param[in] stream  Flux audio .
 * @param[in] block  Flux audio / Flux audio .
 *
 * @retval 0  Flux audio .
 * @retval  Flux audio 0  Flux audio .
 *
 * @remarks  Flux audio 
 * @code
 * while(1) {
 *		//  Obtenez les données à décoder 
 *		ret = fread(buf_g711, 1, IMP_AUDIO_BUF_SIZE/2, file_g711);
 *		if(ret < IMP_AUDIO_BUF_SIZE/2)
 *			break;
 *
 *		//  Envoyer des données décodées 
 *		IMPAudioStream stream_in;
 *		stream_in.stream = (uint8_t *)buf_g711;
 *		stream_in.len = ret;
 *		ret = IMP_ADEC_SendStream(adChn, &stream_in, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode send frame failed\n");
 *			return ret;
 *		}
 *
 *		//  Obtenez les données décodées 
 *		IMPAudioStream stream_out;
 *		ret = IMP_ADEC_GetStream(adChn, &stream_out, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio decoder get stream failed\n");
 *			return ret;
 *		}
 *
 *		//  Utiliser des données décodées 
 *		fwrite(stream_out.stream, 1, stream_out.len, file_pcm);
 *
 *		//  Libérez les données décodées 
 *		ret = IMP_ADEC_ReleaseStream(adChn, &stream_out);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio decoder release stream failed\n");
 *			return ret;
 *		}
 * }
 * @endcode
 *
 * @attention  Libérez les données décodées .
 */
 int IMP_ADEC_SendStream(int adChn, IMPAudioStream *stream, IMPBlock block);

/**
 * @fn int IMP_ADEC_PollingStream(int AdChn, unsigned int timeout_ms)
 *
 * Polling Décoder le tampon de flux audio .
 *
 * @param[in] AdChn  Numéro de canal d'entrée de décodage audio .
 * @param[in] timeout_ms Polling Numéro de canal d'entrée de décodage audio .
 *
 * @retval 0  Numéro de canal d'entrée de décodage audio .
 * @retval  Numéro de canal d'entrée de décodage audio 0  Numéro de canal d'entrée de décodage audio .
 *
 * @remarks  Numéro de canal d'entrée de décodage audio .
 *
 * @attention  Numéro de canal d'entrée de décodage audio IMP_ADEC_GetStream Numéro de canal d'entrée de décodage audio ， Numéro de canal d'entrée de décodage audio 
 *			   Les données décodées sont prêtes ， Les données décodées sont prêtes IMP_ADEC_GetStream Obtenez les données décodées .
 */
int IMP_ADEC_PollingStream(int AdChn, unsigned int timeout_ms);

/**
 * @fn int IMP_ADEC_GetStream(int adChn, IMPAudioStream *stream ,IMPBlock block)
 *
 *  Obtenez le flux de code décodé .
 *
 * @param[in] adChn  Obtenez le flux de code décodé .
 * @param[in] stream  Obtenir un flux de code décodé .
 * @param[in] block  Obtenir un flux de code décodé / Obtenir un flux de code décodé .
 *
 * @retval 0  Obtenir un flux de code décodé .
 * @retval  Obtenir un flux de code décodé 0  Obtenir un flux de code décodé .
 *
 * @remarks  Obtenir un flux de code décodé IMP_ADEC_SendStream Obtenir un flux de code décodé .
 *
 * @attention  Obtenir un flux de code décodé .
 */
int IMP_ADEC_GetStream(int adChn, IMPAudioStream *stream ,IMPBlock block);

/**
 * @fn int IMP_ADEC_ReleaseStream(int adChn,IMPAudioStream *stream)
 *
 *  Libérez le flux de code obtenu à partir du canal de décodage audio .
 *
 * @param[in] adChn  Libérez le flux de code obtenu à partir du canal de décodage audio .
 * @param[in] stream  Pointeur de flux audio .
 *
 * @retval 0  Pointeur de flux audio .
 * @retval  Pointeur de flux audio 0  Pointeur de flux audio .
 *
 * @remarks  Pointeur de flux audio IMP_ADEC_SendStream Pointeur de flux audio .
 *
 * @attention  Pointeur de flux audio .
 */
int IMP_ADEC_ReleaseStream(int adChn,IMPAudioStream *stream);

/**
 * @fn int IMP_ADEC_ClearChnBuf(int adChn)
 *
 *  Effacer le tampon de données audio actuel dans le canal de décodage audio .
 *
 * @param[in] adChn  Effacer le tampon de données audio actuel dans le canal de décodage audio .
 *
 * @retval 0  Effacer le tampon de données audio actuel dans le canal de décodage audio .
 * @retval  Effacer le tampon de données audio actuel dans le canal de décodage audio 0  Effacer le tampon de données audio actuel dans le canal de décodage audio .
 *
 * @remarks  Effacer le tampon de données audio actuel dans le canal de décodage audio .
 *
 * @attention  Effacer le tampon de données audio actuel dans le canal de décodage audio .
 */
 int IMP_ADEC_ClearChnBuf(int adChn);

/**
 * @fn int IMP_ADEC_RegisterDecoder(int *handle, IMPAudioDecDecoder *decoder)
 *
 *  Enregistrer le décodeur .
 *
 * @param[in] ps32handle  Enregistrer le décodeur .
 * @param[in] decoder  Structure d'attribut du décodeur .
 *
 * @retval 0  Structure d'attribut du décodeur .
 * @retval  Structure d'attribut du décodeur 0  Structure d'attribut du décodeur .
 *
 * @remarks  Structure d'attribut du décodeur 
 * @code
 * int handle_g711a = 0;
 * IMPAudioDecDecoder my_decoder;
 * sprintf(my_decoder.name, "%s", "MY_G711A");
 * my_decoder.openDecoder = NULL; //  Fonction de rappel du décodeur 
 * my_decoder.decodeFrm = MY_G711A_Decode_Frm; //  Fonction de rappel du décodeur 
 * my_decoder.getFrmInfo = NULL; //  Fonction de rappel du décodeur 
 * my_decoder.closeDecoder = NULL; //  Fonction de rappel du décodeur 
 *
 * //  Fonction de rappel du décodeur 
 * ret = IMP_ADEC_RegisterDecoder(&handle_g711a, &my_decoder);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "IMP_ADEC_RegisterDecoder failed\n");
 *		return ret;
 * }
 *
 * //  Utiliser le décodeur 
 * int adChn = 0;
 * IMPAudioDecChnAttr attr;
 * attr.type = handle_g711a; //  décodage type Égal à celui renvoyé par l'enregistrement du décodeur handle_g711a.
 * attr.bufSize = 20;
 * attr.mode = ADEC_MODE_PACK;
 * //  Créer un canal de décodage 
 * ret = IMP_ADEC_CreateChn(adChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "imp audio decoder create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention  Créer un canal de décodage SDK Identique au décodeur intégré .
 */
 int IMP_ADEC_RegisterDecoder(int *handle, IMPAudioDecDecoder *decoder);

/**
 * @fn int IMP_ADEC_ReleaseDecoder(int *handle)
 *
 *  Désenregistrer le décodeur .
 *
 * @param[in] ps32handle  Désenregistrer le décodeur ( Handle obtenu lors de l'enregistrement du décodeur ).
 *
 * @retval 0  Handle obtenu lors de l'enregistrement du décodeur .
 * @retval  Handle obtenu lors de l'enregistrement du décodeur 0  Handle obtenu lors de l'enregistrement du décodeur .
 *
 * @remarks  Handle obtenu lors de l'enregistrement du décodeur .
 *
 * @attention  Handle obtenu lors de l'enregistrement du décodeur .
 */
 int IMP_ADEC_ReleaseDecoder(int *handle);

/**
 * ACODEC Configuration .
 */
/**
 * @fn int IMP_AI_SetVol(int audioDevId, int aiChn, int aiVol)
 *
 *  Régler le volume d'entrée audio .
 *
 * @param[in] aiDevId  Régler le volume d'entrée audio .
 * @param[in] aiChn  Régler le volume d'entrée audio .
 * @param[in] aiVol  Volume d'entrée audio .
 *
 * @retval 0  Volume d'entrée audio .
 * @retval  Volume d'entrée audio 0  Volume d'entrée audio .
 *
 * @remarks  Volume d'entrée audio [-30 ~ 120]. -30 Volume d'entrée audio ,120 Volume d'entrée audio 30dB, Volume d'entrée audio 0.5dB.
 * @remarks  Volume d'entrée audio 60 Volume d'entrée audio ， Volume d'entrée audio ， Volume d'entrée audio 60 Volume d'entrée audio ， Volume d'entrée audio 1， Volume d'entrée audio 0.5dB Volume d'entrée audio 60 Volume d'entrée audio ， Volume d'entrée audio 1， Volume d'entrée audio 0.5dB Volume d'entrée audio 
 *
 *  Volume d'entrée audio 
 * @code
 * int volume = 60;
 * ret = IMP_AI_SetVol(devID, chnID, volume);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Record set volume failed\n");
 *		return ret;
 * }
 * @endcode
 * @attention  Si vous entrez aiVol dépassé [-30 ~ 120] La portée de , Moins que -30 Prendra -30, plus que le 120 Prendre 120.
 */
 int IMP_AI_SetVol(int audioDevId, int aiChn, int aiVol);

/**
 * @fn int IMP_AI_GetVol(int audioDevId, int aiChn, int *vol)
 *
 *  Obtenez le volume d'entrée audio .
 *
 * @param[in] aiDevId  Obtenez le volume d'entrée audio .
 * @param[in] aiChn  Obtenez le volume d'entrée audio .
 * @param[out] vol  Volume du canal d'entrée audio .
 *
 * @retval 0  Volume du canal d'entrée audio .
 * @retval  Volume du canal d'entrée audio 0  Volume du canal d'entrée audio .
 *
 * @remarks  Volume du canal d'entrée audio .
 *
 * @attention  Volume du canal d'entrée audio .
 */
 int IMP_AI_GetVol(int audioDevId, int aiChn, int *vol);

/**
 * @fn int IMP_AI_SetVolMute(int audioDevId, int aiChn, int mute)
 *
 *  Régler le son de l'entrée audio .
 *
 * @param[in] aiDevId  Régler le son de l'entrée audio .
 * @param[in] aiChn  Régler le son de l'entrée audio .
 * @param[out] mute  Signe de sourdine d'entrée audio , mute = 0: Couper le son , mute = 1: Activer le son .
 *
 * @retval 0  Activer le son .
 * @retval  Activer le son 0  Activer le son .
 *
 * @remarks  Appelez cette interface pour couper le son immédiatement .
 *
 * @attention  Appelez cette interface pour couper le son immédiatement .
 */
 int IMP_AI_SetVolMute(int audioDevId, int aiChn, int mute);

/**
 * @fn int IMP_AO_SetVol(int audioDevId, int aoChn, int aoVol)
 *
 *  Régler le volume du canal de sortie audio .
 *
 * @param[in] audioDevId  Régler le volume du canal de sortie audio .
 * @param[in] aoChn  Régler le volume du canal de sortie audio .
 * @param[in] aoVol  Volume de sortie audio .
 *
 * @retval 0  Volume de sortie audio .
 * @retval  Volume de sortie audio 0  Volume de sortie audio .
 *
 * @remarks  Volume de sortie audio [-30 ~ 120]. -30 Volume de sortie audio ,120 Volume de sortie audio 30dB, Volume de sortie audio 0.5dB.
 * @remarks  Volume de sortie audio 60 Volume de sortie audio ， Volume de sortie audio ， Volume de sortie audio 60 Volume de sortie audio ， Volume de sortie audio 1， Volume de sortie audio 0.5dB Volume de sortie audio 60 Volume de sortie audio ， Volume de sortie audio 1， Volume de sortie audio 0.5dB Volume de sortie audio 
 *
 * @attention  Volume de sortie audio aoVol Volume de sortie audio [-30 ~ 120] Volume de sortie audio , Volume de sortie audio -30 Volume de sortie audio -30, Volume de sortie audio 120 Volume de sortie audio 120.
 */
 int IMP_AO_SetVol(int audioDevId, int aoChn, int aoVol);

/**
 * @fn int IMP_AO_GetVol(int audioDevId, int aoChn, int *vol)
 *
 *  Obtenir le volume du canal de sortie audio .
 *
 * @param[in] audioDevId  Obtenir le volume du canal de sortie audio .
 * @param[in] aoChn  Obtenir le volume du canal de sortie audio .
 * @param[out] aoVol  Obtenir le volume du canal de sortie audio .
 *
 * @retval 0  Obtenir le volume du canal de sortie audio .
 * @retval  Obtenir le volume du canal de sortie audio 0  Obtenir le volume du canal de sortie audio .
 *
 * @remarks  Obtenir le volume du canal de sortie audio .
 *
 * @attention  Obtenir le volume du canal de sortie audio .
 */
 int IMP_AO_GetVol(int audioDevId, int aoChn, int *vol);

/**
 * @fn int IMP_AO_SetVolMute(int audioDevId, int aoChn, int mute)
 *
 *  Régler la sortie audio mute .
 *
 * @param[in] audioDevId  Numéro du périphérique de sortie audio .
 * @param[in] aoChn  Numéro du périphérique de sortie audio .
 * @param[out] mute  Signe de sourdine de sortie audio , mute = 0: Signe de sourdine de sortie audio , mute = 1: Signe de sourdine de sortie audio .
 *
 * @retval 0  Signe de sourdine de sortie audio .
 * @retval  Signe de sourdine de sortie audio 0  Signe de sourdine de sortie audio .
 *
 * @remarks  Signe de sourdine de sortie audio .
 *
 * @attention  Signe de sourdine de sortie audio .
 */
 int IMP_AO_SetVolMute(int audioDevId, int aoChn, int mute);

/**
 * @fn int IMP_AI_SetGain(int audioDevId, int aiChn, int aiGain)
 *
 *  Régler le gain d'entrée audio .
 *
 * @param[in] audioDevId  Régler le gain d'entrée audio .
 * @param[in] aiChn  Régler le gain d'entrée audio .
 * @param[out] aiGain  Gain d'entrée audio , gamme [0 ~ 31].
 *
 * @retval 0  gamme .
 * @retval  gamme 0  gamme .
 *
 * @remarks  gamme .
 *
 * @attention aiGain La gamme est [0 ~ 31], Si la valeur saisie est inférieure à 0, alors aiGain La valeur sera \n
 *  définir comme 0. Si la valeur est supérieure à 31,aiGain Sera réglé sur 10.
 *
 */
 int IMP_AI_SetGain(int audioDevId, int aiChn, int aiGain);

/**
 * @fn int IMP_AI_GetGain(int audioDevId, int aiChn, int *aiGain)
 *
 *  Obtenir AI Gagner de la valeur .
 *
 * @param[in] audioDevId  Gagner de la valeur .
 * @param[in] aiChn  Gagner de la valeur .
 * @param[out] aiGain  Gagner de la valeur .
 *
 * @retval 0  Gagner de la valeur .
 * @retval  Gagner de la valeur 0  Gagner de la valeur .
 *
 * @remarks  Gagner de la valeur .
 *
 * @attention  Gagner de la valeur .
 */
 int IMP_AI_GetGain(int audioDevId, int aiChn, int *aiGain);

/**
 * @fn int IMP_AO_SetGain(int audioDevId, int aoChn, int aoGain)
 *
 *  Régler le gain de sortie audio .
 *
 * @param[in] audioDevId  Régler le gain de sortie audio .
 * @param[in] aoChn  Régler le gain de sortie audio .
 * @param[out] aoGain  Gain de sortie audio , Gain de sortie audio [0 ~ 0xcb].
 *
 * @retval 0  Gain de sortie audio .
 * @retval  Gain de sortie audio 0  Gain de sortie audio .
 *
 * @remarks  Gain de sortie audio .
 *
 * @attention aoGain Gain de sortie audio [0 ~ 31], Gain de sortie audio 0, Gain de sortie audio aoGain Gain de sortie audio \n
 *  Gain de sortie audio 0. Gain de sortie audio 31,aoGain Gain de sortie audio 31.
 *
 */
 int IMP_AO_SetGain(int audioDevId, int aoChn, int aoGain);

/**
 * @fn int IMP_AO_GetGain(int audioDevId, int aoChn, int *aoGain)
 *
 *  Obtenez le gain de sortie audio .
 *
 * @param[in] audioDevId  Obtenez le gain de sortie audio .
 * @param[in] aoChn  Obtenez le gain de sortie audio .
 * @param[out] aoGain  Obtenez le gain de sortie audio .
 *
 * @retval 0  Obtenez le gain de sortie audio .
 * @retval  Obtenez le gain de sortie audio 0  Obtenez le gain de sortie audio .
 *
 * @remarks  Obtenez le gain de sortie audio .
 *
 * @attention  Obtenez le gain de sortie audio .
 */
 int IMP_AO_GetGain(int audioDevId, int aoChn, int *aoGain);

/**
 * @fn int IMP_AO_Soft_Mute(int audioDevId, int aoChn)
 *
 *  Contrôle de la sortie silencieuse .
 *
 * @param[in] audioDevId  Contrôle de la sortie silencieuse .
 * @param[in] aoChn  Contrôle de la sortie silencieuse .
 *
 * @retval 0  Contrôle de la sortie silencieuse .
 * @retval  Contrôle de la sortie silencieuse 0  Contrôle de la sortie silencieuse .
 *
 * @remarks  L'appel de cette interface ne coupera pas immédiatement le son ， Réduira lentement le volume à partir de l'état de lecture normal ， Jusqu'à ce que ce soit vraiment silencieux .
 *
 * @attention  Jusqu'à ce que ce soit vraiment silencieux .
 */
 int IMP_AO_Soft_Mute(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_Soft_UNMute(int audioDevId, int aoChn)
 *
 *  Contrôle de la mise en sourdine douce de la sortie .
 *
 * @param[in] audioDevId  Contrôle de la mise en sourdine douce de la sortie .
 * @param[in] aoChn  Contrôle de la mise en sourdine douce de la sortie .
 *
 * @retval 0  Contrôle de la mise en sourdine douce de la sortie .
 * @retval  Contrôle de la mise en sourdine douce de la sortie 0  Contrôle de la mise en sourdine douce de la sortie .
 *
 * @remarks  L'appel de cette interface ne restaure pas immédiatement le volume actuel ， Augmentera lentement le volume à partir de l'état muet ， Jusqu'à ce que le volume atteigne le volume réglé .
 *
 * @attention  Jusqu'à ce que le volume atteigne le volume réglé .
 */
 int IMP_AO_Soft_UNMute(int audioDevId, int aoChn);

/**
 * @fn int IMP_AI_GetFrameAndRef(int audioDevId, int aiChn, IMPAudioFrame *frm, IMPAudioFrame *ref, IMPBlock block)
 *
 *  Obtenir une image audio et une image de référence de sortie .
 *
 * @param[in] audioDevId  Obtenir une image audio et une image de référence de sortie .
 * @param[in] aiChn  Obtenir une image audio et une image de référence de sortie .
 * @param[out] frm  Obtenir une image audio et une image de référence de sortie .
 * @param[out] ref  Pointeur de structure du cadre de référence .
 * @param[in] block  Pointeur de structure du cadre de référence / Pointeur de structure du cadre de référence .
 *
 * @retval 0  Pointeur de structure du cadre de référence .
 * @retval  Pointeur de structure du cadre de référence 0  Pointeur de structure du cadre de référence .
 *
 * @remarks  Pointeur de structure du cadre de référence 
 * @code
 * IMPAudioFrame frm;
 * IMPAudioFrame ref;
 * //  Pointeur de structure du cadre de référence 
 * ret = IMP_AI_GetFrameAndRef(devID, chnID, &frm, &ref, BLOCK);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Get Frame Data error\n");
 *		return ret;
 * }
 *
 * fwrite(frm.virAddr, 1, frm.len, record_file); //  Pointeur de structure du cadre de référence 
 * fwrite(ref.virAddr, 1, ref.len, ref_file); //  Utiliser des cadres de référence audio 
 *
 * //  Utiliser des cadres de référence audio 
 * ret = IMP_AI_ReleaseFrame(devID, chnID, &frm);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio release frame data error\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention  Utiliser des cadres de référence audio .
 */
 int IMP_AI_GetFrameAndRef(int audioDevId, int aiChn, IMPAudioFrame *frm, IMPAudioFrame *ref, IMPBlock block);

/**
 * @fn int IMP_AI_EnableAecRefFrame(int audioDevId, int aiChn, int audioAoDevId, int aoChn)
 *
 *  Ouvrir pour obtenir le cadre de référence .
 *
 * @param[in] audioDevId  Ouvrir pour obtenir le cadre de référence .
 * @param[in] aiChn  Ouvrir pour obtenir le cadre de référence .
 * @param[in] audioAoDevId  Ouvrir pour obtenir le cadre de référence .
 * @param[in] aoChn  Ouvrir pour obtenir le cadre de référence .
 *
 * @retval 0  Ouvrir pour obtenir le cadre de référence .
 * @retval  Ouvrir pour obtenir le cadre de référence 0  Ouvrir pour obtenir le cadre de référence .
 *
 * @remarks  transfert IMP_AI_GetFrameAndRef Appelez cette interface avant .
 * @attention  Appelez cette interface avant .
 */
 int IMP_AI_EnableAecRefFrame(int audioDevId, int aiChn, int audioAoDevId, int aoChn);

/**
 * @fn int IMP_AI_DisableAecRefFrame(int audioDevId, int aiChn, int audioAoDevId, int aoChn)
 *
 *  Fermer Obtenir le cadre de référence .
 *
 * @param[in] audioDevId  Fermer Obtenir le cadre de référence .
 * @param[in] aiChn  Fermer Obtenir le cadre de référence .
 * @param[in] audioAoDevId  Fermer Obtenir le cadre de référence .
 * @param[in] aoChn  Fermer Obtenir le cadre de référence .
 *
 * @retval 0  Fermer Obtenir le cadre de référence .
 * @retval  Fermer Obtenir le cadre de référence 0  Fermer Obtenir le cadre de référence .
 *
 * @remarks  Fermer Obtenir le cadre de référence .
 * @attention  Fermer Obtenir le cadre de référence .
 */
 int IMP_AI_DisableAecRefFrame(int audioDevId, int aiChn, int audioAoDevId, int aoChn);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_AUDIO_H__ */
