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
 * IMP Fichiers d'en-tête d'entrée et de sortie audio 
 */

/**
 * @defgroup IMP_Audio
 * @ingroup lutin
 * @brief Module audio, comprenant l'enregistrement et la lecture, le codec audio, les paramètres de volume et de gain, l'annulation d'écho, le gain automatique et d'autres fonctions
 *
 * @section Présentation de l'audio_summary 1
 * La fonction audio comprend une entrée audio , Sortie audio , Annulation d'écho , Encodage audio et décodage audio 5 Modules . \n
 * Parmi eux, l'entrée audio et la sortie audio ont le concept d'équipement et de canaux . L'un des MIC Nous pensons que c'est un Device, Et une MIC Il peut y avoir plusieurs Channel Entrer . \n
 * Le même SPK Nous pensons que c'est une annonce Device, SPK Il peut également y avoir plusieurs Channel Production . \n
 * Audio de la version actuelle API Une Device Prend en charge un seul Channel. \n
 * L'annulation de l'écho est située dans l'interface d'entrée audio , Des instructions spécifiques sont reflétées dans la description de la fonction . \n
 * Codage audio audio actuel API Support moyen PT_G711A [[[ PT_G711U avec PT_G726 Formater l'encodage audio , Si vous devez ajouter une nouvelle méthode d'encodage , Besoin d'enregistrer l'encodeur . \n
 * Décodage audio audio actuel API PT_G711A PT_G711U PT_G726 Formater le décodage audio , Si vous devez ajouter une nouvelle méthode de décodage , Besoin d'enregistrer le décodeur . \n
 * @section audio_function_description 2 Description de la fonction
 * Ce qui suit est une description spécifique de chaque module 
 * @subsection entrée audio audio_in 2.1
 * Entrée audio Device ID Correspondance , 0: Numéro correspondant MIC 1: Simulation correspondante MIC \n
 * Channel actuel API Supporte uniquement 1 Canaux . \n
 * Réglage du volume d'entrée audio , La plage de volume est [-30 ~ 120]. -30 Signifie muet ,120 Moyens d'amplifier le son 30dB, Taille de pas 0.5dB. parmi eux 60 Est un point critique pour le réglage du volume ，\n
 * Le logiciel n'augmente ni ne diminue le volume à cette valeur ， Lorsque la valeur du volume est inférieure à 60 Temps ， Chaque goutte 1， Baisser le volume 0.5dB ; Lorsque la valeur du volume est supérieure à 60 ， Augmenter 1， Augmentation de volume 0.5dB . 
 * @subsection audio_out 2.2 Sortie audio
 * Device ID , 0: Correspondant à la valeur par défaut SPK 1: Correspondant à d'autres SPK \n
 * Channel API 1 . \n
 * Réglage du volume de sortie audio , [-30 ~ 120]. -30 ,120 30dB, 0.5dB. 60 ，\n
 * ， 60 ， 1， 0.5dB 60 ， 1， 0.5dB. \n
 * @subsection audio_aec 2.3 Annulation de l'écho
 * L'annulation de l'écho est une fonction de l'interface d'entrée audio , Par conséquent, le périphérique d'entrée audio et le canal doivent être activés avant d'activer l'annulation d'écho . \n
 * L'annulation de l'écho prend actuellement en charge le taux d'échantillonnage audio 8K 16K， Le nombre d'échantillons de données dans une trame est 10ms Multiples entiers de données audio (tels que: 8K Taux d'échantillonnage ， Les données envoyées sont: 8000 × 2 / 100 = 160byte Multiples entiers de). \n
 * Annulation d'écho pour différents appareils ， Différents forfaits ， L'annulation de l'écho aura des effets différents . \n
 * L'annulation d'écho ne prend actuellement pas en charge la fonction adaptative ， Il existe donc des paramètres d'annulation d'écho distincts pour différents appareils , \n
 * Le fichier de paramètres pour l'annulation d'écho se trouve dans /etc/webrtc_profile.ini Fichier de configuration . \n
 * Le format du fichier de configuration est le suivant ( Les trois principaux paramètres à déboguer sont répertoriés ci-dessous ): \n
 * [Set_Far_Frame] \n
 * Frame_V=0.3 \n
 * [Set_Near_Frame] \n
 * Frame_V=0.1 \n
 * delay_ms=150 \n
 *
 * Le premier label [Set_Far_Frame] Le contenu de représente le paramètre distant , lequel est SPK Terminer les paramètres de données de lecture . \n
 * Fram_V Représente le rapport d'amplitude audio , Ajustez ce paramètre pour ajuster l'amplitude des données de lecture ( Cette amplitude n'est utilisée que pour l'annulation d'écho ). \n
 * [Set_Near_Frame] Le contenu dans représente le paramètre proche , MIC Terminer l'enregistrement des paramètres de données . \n
 * Fram_V , Ajustez ce paramètre pour ajuster l'amplitude des données enregistrées ( ). \n
 * delay_ms En raison du retard du logiciel et du matériel , Et SPK contre MIC Est placé à une certaine distance ,SPK Les données de lecture seront MIC échantillonnage , et donc SPK Données en MIC Il y aura un certain retard dans les données . \n
 * Cette heure représente la différence de temps entre les données de lecture et les données d'enregistrement . \n

 * @subsection encodage audio audio_enc 2.4
 * Codage audio audio actuel API Etre prêt PT_G711A PT_G711U PT_G726 , Si vous devez ajouter une nouvelle méthode d'encodage , Besoin d'appeler IMP_AENC_RegisterEncoder Interface pour enregistrer le codeur .
 * @subsection décodage audio audio_dec 2.5
 * Décodage audio audio actuel API PT_G711A PT_G711U PT_G726 , Si vous devez ajouter une nouvelle méthode de décodage , IMP_ADEC_RegisterDecoder Interface pour enregistrer le décodeur .
 * @{
 */

/**
 * Nombre maximum de tampons de trame audio 
 */
#define MAX_AUDIO_FRAME_NUM 50

/**
 * Type de blocage du flux audio 
 */
typedef enum {
	BLOCK = 0,				/**< bloquer */
	NOBLOCK = 1,			/**< Non bloquant */
} IMPBlock;

/**
 * Définition du taux d'échantillonnage audio .
 */
typedef enum {
	AUDIO_SAMPLE_RATE_8000	= 8000,		/**< 8KHz */
	AUDIO_SAMPLE_RATE_16000 = 16000,	/**< 16KHz */
	AUDIO_SAMPLE_RATE_44100 = 44100,	/**< 44.1KHz */
	AUDIO_SAMPLE_RATE_48000 = 48000,	/**< 48KHz */
	AUDIO_SAMPLE_RATE_96000 = 96000,	/**< 96KHz */
} IMPAudioSampleRate;

/**
 * Définition de la précision d'échantillonnage audio .
 */
typedef enum {
	AUDIO_BIT_WIDTH_16 = 16,		/**< 16bit Précision d'échantillonnage */
} IMPAudioBitWidth;

/**
 * Définition du mode de canal audio .
 */
typedef enum {
	AUDIO_SOUND_MODE_MONO	= 1,	/**< Mono */
	AUDIO_SOUND_MODE_STEREO = 2,	/**< Deux canaux */
} IMPAudioSoundMode;

/**
 * Définir l'énumération du type de charge utile audio .
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
 * Définir la méthode de décodage .
 */
typedef enum {
	ADEC_MODE_PACK = 0,	/**< Pack Façon de décoder */
	ADEC_MODE_STREAM = 1,	/**< Stream */
} IMPAudioDecMode;

/**
 * Propriétés du périphérique d'entrée et de sortie audio .
 */
typedef struct {
	IMPAudioSampleRate samplerate;		/**< Taux d'échantillonnage audio */
	IMPAudioBitWidth bitwidth;			/**< Précision d'échantillonnage audio */
	IMPAudioSoundMode soundmode;		/**< Mode canal audio */
	int frmNum;							/**< Nombre de trames tamponnées , Gammes :[2, MAX_AUDIO_FRAME_NUM] */
	int numPerFrm;						/**< Nombre de points d'échantillonnage par trame */
	int chnCnt;							/**< Nombre de canaux pris en charge */
} IMPAudioIOAttr;

/**
 * Structure de trame audio .
 */
typedef struct {
	IMPAudioBitWidth bitwidth;			/**< */
	IMPAudioSoundMode soundmode;		/**< */
	uint32_t *virAddr;					/**< Adresse virtuelle des données de trame audio */
	uint32_t phyAddr;					/**< Adresse physique des données de trame audio */
	int64_t timeStamp;					/**< Horodatage des données de trame audio */
	int seq;							/**< Numéro de trame audio */
	int len;							/**< Longueur de la trame audio */
} IMPAudioFrame;

/**
 * Structure des paramètres du canal audio .
 */
typedef struct {
	int usrFrmDepth;					/**< Profondeur de la mémoire tampon d'image audio */
	int Rev;							/**< Garder */
} IMPAudioIChnParam;

/**
 * Structure de l'état du tampon de données du canal de sortie audio .
 */
typedef struct {
	int chnTotalNum;				/**< Le nombre total de blocs tampons du canal de sortie */
	int chnFreeNum;					/**< Nombre de blocs de cache gratuits */
	int chnBusyNum;					/**< Nombre de blocs de cache occupés */
} IMPAudioOChnState;

/**
 * Définir la structure du flux audio .
 */
typedef struct {
	uint8_t *stream;				/**< Pointeur de flux de données */
	uint32_t phyAddr;				/**< Adresse physique du flux de données */
	int len;						/**< Longueur du flux audio */
	int64_t timeStamp;				/**< Horodatage */
	int seq;						/**< Numéro de série du flux audio */
} IMPAudioStream;

/**
 * Définir la structure d'attribut du canal de codage audio .
 */
typedef struct {
	IMPAudioPalyloadType type;				/**< Type de données de charge utile audio */
	int bufSize;							/**< buf Taille ， Dans les cadres ，[2 ~ MAX_AUDIO_FRAME_NUM] */
	uint32_t *value;						/**< Pointeur d'attribut de protocole */
} IMPAudioEncChnAttr;

/**
 * Définir la structure des attributs du codeur .
 */
typedef struct {
	IMPAudioPalyloadType type;		/**< Type de protocole de codage */
	int maxFrmLen;					/**< Longueur maximale du flux */
	char name[16];					/**< Nom du codeur */
	int (*openEncoder)(void *encoderAttr, void
			*encoder);
	int (*encoderFrm)(void *encoder, IMPAudioFrame
			*data, unsigned char *outbuf,int *outLen);
	int (*closeEncoder)(void *encoder);
} IMPAudioEncEncoder;

/**
 * Définir la structure d'attribut du canal de décodage .
 */
typedef struct {
	IMPAudioPalyloadType type;			/**< Type de protocole de décodage audio */
	int bufSize;						/**< Taille du tampon de décodage audio */
	IMPAudioDecMode mode;				/**< Méthode de décodage */
	void *value;						/**< Pointeur d'attribut de protocole spécifique */
} IMPAudioDecChnAttr;

/**
 * Définir la structure des attributs du décodeur .
 */
typedef struct {
	IMPAudioPalyloadType type;		/**< */
	char name[16];					/**< Nom du décodeur audio */
	int (*openDecoder)(void *decoderAttr, void
			*decoder);
	int (*decodeFrm)(void *decoder, unsigned char
			*inbuf,int inLen, unsigned short *outbuf,int
			*outLen,int *chns);
	int (*getFrmInfo)(void *decoder, void *info);
	int (*closeDecoder)(void *decoder);
} IMPAudioDecDecoder;

/**
 * définition AGC Structure de gain .
 */
typedef struct {
	int TargetLevelDbfs;	/**< Niveau de gain , La valeur est [0, 31], Cela fait référence au niveau de volume cible , l'unité est db, Négatif . Plus la valeur est petite , Plus fort . */
	int CompressionGaindB;	/**< Définir la valeur de gain maximum ,[0, 90],0 Signifie pas de gain , Valeur plus élevée , Gain plus élevé . */
} IMPAudioAgcConfig;

/**
 * Définir le niveau de suppression du bruit .
 */
enum Level_ns {
	NS_LOW,			/**< Suppression du bruit de bas niveau */
	NS_MODERATE,	/**< Suppression du bruit de niveau moyen */
	NS_HIGH,		/**< Suppression du bruit de haut niveau */
	NS_VERYHIGH		/**< Le plus haut niveau de suppression du bruit */
};

/**
 * @fn int IMP_AI_SetPubAttr (int audioDevId, IMPAudioIOAttr * attr)
 *
 * Définir les propriétés du périphérique d'entrée audio .
 *
 * @param[in] Numéro de périphérique audio audioDevId.
 * @param[in] attr Pointeur d'attribut de périphérique audio.
 *
 * @retval 0 succès.
 * @retval Échec non nul.
 *
 * @remarks Exemple de code
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
 * @attention Doit être appelé avant IMP_AI_Enable.
 */
int IMP_AI_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AI_GetPubAttr (int audioDevId, IMPAudioIOAttr * attr)
 *
 * Obtenir les propriétés du périphérique d'entrée audio .
 *
 * @param[in] audioDevId Numéro du périphérique audio .
 * @param[out] attr Pointeur d'attribut de périphérique audio .
 *
 * @retval 0 Succès .
 * @retval non- 0 échec .
 *
 * @remarks non.
 *
 * @attention non .
 */
int IMP_AI_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AI_Enable (int audioDevId)
 *
 * Activer le périphérique d'entrée audio .
 *
 * @param[in] audioDevId .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention IMP_AI_SetPubAttr () doit être appelé avant d'appeler cette fonction.
 */
int IMP_AI_Enable(int audioDevId);

/**
 * @fn int IMP_AI_Disable (int audioDevId)
 *
 * Désactiver le périphérique d'entrée audio .
 *
 * @param[in] audioDevId .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention Utilisé conjointement avec IMP_AI_Enable, IMP_AI_Disable doit être exécuté avant que le système ne se mette en veille.
 */
int IMP_AI_Disable(int audioDevId);

/**
 * @fn int IMP_AI_EnableChn (int audioDevId, int aiChn)
 *
 * Activer le canal d'entrée audio .
 *
 * @param[in] audioDevId .
 * @param[in] aiChn Numéro de canal d'entrée audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention L'appareil doit d'abord être activé.
 */
int IMP_AI_EnableChn(int audioDevId, int aiChn);

/**
 * @fn int IMP_AI_DisableChn (int audioDevId, int aiChn)
 *
 * Désactiver le canal d'entrée audio .
 *
 * @param[in] audioDevId .
 * @param[in] aiChn Numéro de canal d'entrée audio .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention Utilisé en conjonction avec IMP_AI_EnableChn.
 */
int IMP_AI_DisableChn(int audioDevId, int aiChn);

/**
 * @fn int IMP_AI_PollingFrame (int audioDevId, int aiChn, non signé int timeout_ms)
 *
 * Polling Tampon de flux audio .
 *
 * @param[in] audioDevId .
 * @param[in] aiChn .
 * @param[in] timeout_ms Délai d'expiration de l'interrogation.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention Utilisez cette interface avant d'utiliser IMP_AI_GetFrame, lorsque l'interface est appelée avec succès, cela signifie audio
 *			 Les données sont prêtes ， peut utiliser IMP_AI_GetFrame Obtenez des données audio .
 */
int IMP_AI_PollingFrame(int audioDevId, int aiChn, unsigned int timeout_ms);

/**
 * @fn int IMP_AI_GetFrame (int audioDevId, int aiChn, IMPAudioFrame * frm, bloc IMPBlock)
 *
 * Obtenir une image audio .
 *
 * @param[in] audioDevId .
 * @param[in] aiChn .
 * @param[out] frm Pointeur de structure de trame audio.
 * @param[in] Identification bloquante / non bloquante de bloc.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks Exemple de code 
 * @code 
 * IMPAudioFrame frm;
 * // 
 * ret = IMP_AI_GetFrame(devID, chnID, &frm, BLOCK);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Get Frame Data error\n");
 *		return ret;
 * }
 *
 * fwrite(frm.virAddr, 1, frm.len, record_file); // Utiliser les données de trame audio 
 *
 * // Libérer le cadre audio 
 * ret = IMP_AI_ReleaseFrame(devID, chnID, &frm);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio release frame data error\n");
 *		return ret;
 * }
 * @endcode 
 *
 * @attention .
 */
int IMP_AI_GetFrame(int audioDevId, int aiChn, IMPAudioFrame *frm, IMPBlock block);

/**
 * @fn int IMP_AI_ReleaseFrame (int audioDevId, int aiChn, IMPAudioFrame * frm)
 *
 * .
 *
 * @param[in] audioDevId .
 * @param[in] aiChn .
 * @param[in] frm Pointeur de structure de trame audio .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention Utilisé en conjonction avec IMP_AI_GetFrame.
 */
int IMP_AI_ReleaseFrame(int audioDevId, int aiChn, IMPAudioFrame *frm);

/**
 * @fn int IMP_AI_SetChnParam (int audioDevId, int aiChn, IMPAudioIChnParam * chnParam)
 *
 * Définir les paramètres du canal d'entrée audio .
 *
 * @param[in] audioDevId .
 * @param[in] aiChn .
 * @param[in] chnParam Paramètres du canal audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks 
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
 * @attention Appelé avant IMP_AI_EnableChn.
 */
int IMP_AI_SetChnParam(int audioDevId, int aiChn, IMPAudioIChnParam *chnParam);

/**
 * @fn int IMP_AI_GetChnParam (int audioDevId, int aiChn, IMPAudioIChnParam * chnParam)
 *
 * Obtenir les paramètres du canal d'entrée audio .
 *
 * @param[in] audioDevId .
 * @param[in] aiChn .
 * @param[out] chnParam Paramètres du canal audio .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AI_GetChnParam(int audioDevId, int aiChn, IMPAudioIChnParam *chnParam);

/**
 * @fn int IMP_AI_EnableAec (int aiDevId, int aiChn, int aoDevId, int aoChn)
 *
 * Activer la fonction d'annulation d'écho de l'entrée audio et de la sortie audio spécifiées .
 *
 * @param[in] aiDevId Le numéro du périphérique d'entrée audio qui nécessite une annulation d'écho.
 * @param[in] aiChn Le numéro du canal d'entrée audio pour l'annulation de l'écho.
 * @param[in] aoDevId Le numéro du périphérique de sortie audio qui nécessite une annulation d'écho.
 * @param[in] aoChn Le numéro du canal de sortie audio pour l'annulation de l'écho.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks L'annulation d'écho aura des effets différents pour différents appareils et différents packages.
 * @remarks L'annulation d'écho ne prend actuellement pas en charge adaptative, il existe donc des paramètres d'annulation d'écho distincts pour différents appareils,
 * @remarks Le simple fait d'activer la fonction n'est pas nécessairement bon.
 * @remarks Le fichier de paramètres d'annulation d'écho se trouve dans le fichier de configuration /etc/webrtc_profile.ini.
 * @remarks Le format du fichier de configuration est le suivant (les trois principaux paramètres à déboguer sont répertoriés ci-dessous):
 * @remarks [Set_Far_Frame]
 * @remarks Frame_V = 0,3
 * @remarks [Set_Near_Frame]
 * @remarks Frame_V = 0,1
 * @remarks delay_ms = 150
 *
 * @remarks Le contenu de la première étiquette [Set_Far_Frame] représente les paramètres distants, c'est-à-dire les paramètres de données de fin de lecture SPK.
 * @remarks Fram_V représente le rapport d'amplitude audio. Le réglage de ce paramètre peut ajuster l'amplitude des données de lecture (cette amplitude n'est utilisée que pour l'annulation de l'écho).
 * @remarks Le contenu de la première étiquette [Set_Near_Frame] représente le paramètre d'extrémité proche, c'est-à-dire le paramètre de données d'enregistrement de l'extrémité MIC.
 * @remarks Fram_V représente le rapport d'amplitude audio. Le réglage de ce paramètre permet d'ajuster l'amplitude des données d'enregistrement (cette amplitude n'est utilisée que pour l'annulation de l'écho).
 * @remarks delay_ms En raison du retard du logiciel et du matériel, et il y a une certaine distance entre SPK et MIC, les données de lecture SPK seront à nouveau échantillonnées par MIC, il y aura donc un certain retard dans les données SPK reflétées dans les données MIC.
 * @remarks Cette heure représente la différence de temps entre les données de lecture et les données d'enregistrement.
 *
 * @attention En fait, l'interface ne vérifiera que aiDevId et aiChn. Mais il est préférable de l'appeler une fois que les deux canaux sont activés en même temps. 
 * Lors de la fermeture du canal d'entrée audio , La fonction d'annulation d'écho est désactivée en même temps . Si vous devez l'utiliser à nouveau, vous devez l'ouvrir à nouveau .
 */
int IMP_AI_EnableAec(int aiDevId, int aiChn, int aoDevId, int aoChn);

/**
 * @fn int IMP_AI_DisableAec (int aiDevId, int aiChn)
 *
 * Désactiver l'annulation d'écho .
 *
 * @param[in] aiDevId Numéro de périphérique d'entrée audio.
 * @param[in] aiChn .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AI_DisableAec(int aiDevId, int aiChn);

/**
 * @fn int IMP_AI_EnableNs (IMPAudioIOAttr * attr, mode int)
 *
 * Activer la fonction de suppression du bruit de l'entrée audio spécifiée .
 *
 * @param[in] attr Attributs audio nécessitant une suppression du bruit.
 * @param[in] mode Niveau de suppression du bruit 0 ~ 3, voir Level_ns.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks Le paramètre de mode de suppression du bruit indique le niveau de suppression du bruit et la plage est (0 ~ 3). Plus le niveau est élevé, plus la suppression du bruit est nette.
 * @remarks Cependant, plus la suppression du bruit est propre, plus les détails sonores seront perdus, il y a donc une contradiction ici.
 * @remarks Faites des compromis lors de l'utilisation.
 *
 * @attention L'annulation de l'écho inclut la suppression du bruit. Si l'annulation de l'écho est activée, la suppression du bruit n'est pas nécessaire.
 */
int IMP_AI_EnableNs(IMPAudioIOAttr *attr, int mode);

/**
 * @fn int IMP_AI_DisableNs (void)
 *
 * Désactiver la suppression du bruit .
 *
 * @param .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AI_DisableNs(void);

/**
 * @fn int IMP_AI_EnableAgc (IMPAudioIOAttr * attr, IMPAudioAgcConfig agcConfig)
 *
 * Activer la fonction de gain automatique de l'entrée audio .
 *
 * @param[in] attr nécessite des attributs audio pour le gain automatique.
 * @param[in] configuration du paramètre agcConfig du gain automatique, configurez le facteur d'agrandissement.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks Il faut faire attention à la configuration de agcConfig, le facteur d'amplification d'AGC a principalement cette configuration de paramètre, et le gain spécifique voit la description de IMPAudioAgcConfig.
 * @remarks Il convient de noter que l'AGC peut amplifier le gain du son, mais si les paramètres de gain ne sont pas appropriés, cela provoquera une rupture du son, etc., veuillez l'ajuster vous-même lors d'une utilisation spécifique.
 *
 * @attention L'annulation d'écho inclut la fonction AGC, si vous activez l'annulation d'écho, vous n'avez pas besoin de faire un gain automatique.
 */
int IMP_AI_EnableAgc(IMPAudioIOAttr *attr, IMPAudioAgcConfig agcConfig);

/**
 * @fn int IMP_AI_DisableAgc (vide)
 *
 * Désactiver AI Fonction de gain automatique .
 *
 * @param .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AI_DisableAgc(void);

/**
 * @fn int IMP_AO_EnableAgc (IMPAudioIOAttr * attr, IMPAudioAgcConfig agcConfig)
 *
 * Activer la fonction de gain automatique de la sortie audio .
 *
 * @param[in] attr Attributs audio nécessitant un gain automatique .
 * @param[in] agcConfig Configuration des paramètres du gain automatique , Configurer le grossissement .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks nécessite de l'attention agcConfig Configuration ,AGC Le grossissement a principalement la configuration des paramètres , Voir pour des gains spécifiques IMPAudioAgcConfig Description .
 * @remarks doit être conscient de ,AGC Peut amplifier le gain du son , Mais si le paramètre de gain ne convient pas , Cela provoquera la rupture du son, etc. , Veuillez vous ajuster lorsque vous l'utilisez .
 *
 * @attention L'annulation de l'écho comprend AGC Fonctionnalités , Si l'annulation d'écho est activée , Pas besoin de faire de gain automatique .
 */
int IMP_AO_EnableAgc(IMPAudioIOAttr *attr, IMPAudioAgcConfig agcConfig);

/**
 * @fn int IMP_AO_DisableAgc (vide)
 *
 * AO .
 *
 * @param .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AO_DisableAgc(void);

/**
 * @fn int IMP_AI_EnableHpf (IMPAudioIOAttr * attr)
 *
 * Activer le filtrage passe-haut de l'entrée audio .
 *
 * @param[in] attr Attributs audio qui doivent être filtrés passe-haut.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention L'annulation d'écho inclut la fonction HPF, si vous activez l'annulation d'écho, vous n'avez pas besoin de faire HPF.
 */
int IMP_AI_EnableHpf(IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AI_DisableHpf (vide)
 *
 * AI Fonction de filtre passe-haut .
 *
 * @param .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AI_DisableHpf(void);

/**
 * @fn int IMP_AO_EnableHpf (IMPAudioIOAttr * attr)
 *
 * Activer le filtrage passe-haut de la sortie audio .
 *
 * @param[in] attr Attributs audio nécessitant un filtrage passe-haut .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention HPF , , Pas besoin de faire HPF.
 */
int IMP_AO_EnableHpf(IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AO_DisableHpf (vide)
 *
 * AO .
 *
 * @param .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AO_DisableHpf(void);

/**
 * @fn int IMP_AO_SetPubAttr (int audioDevId, IMPAudioIOAttr * attr)
 *
 * Définir les propriétés du périphérique d'entrée et de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[in] attr Pointeur des attributs du périphérique de sortie audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AO_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AO_GetPubAttr (int audioDevId, IMPAudioIOAttr * attr)
 *
 * Obtenir les propriétés du périphérique d'entrée et de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[out] attr Pointeur d'attribut du périphérique de sortie audio .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AO_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AO_Enable (int audioDevId)
 *
 * Activer le périphérique de sortie audio .
 *
 * @param[in] audioDevId .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention IMP_AO_SetPubAttr doit être appelé avant l'activation.
 */
int IMP_AO_Enable(int audioDevId);

/**
 * @fn int IMP_AO_Disable (int audioDevId)
 *
 * Désactiver le périphérique de sortie audio .
 *
 * @param[in] audioDevId .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AO_Disable(int audioDevId);

/**
 * @fn int IMP_AO_EnableChn (int audioDevId, int aoChn)
 *
 * Activer le canal de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[in] aoChn Numéro du canal de sortie audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AO_EnableChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_DisableChn (int audioDevId, int aoChn)
 *
 * Désactiver le canal de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[in] aoChn Numéro de canal de sortie audio .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AO_DisableChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_SendFrame (int audioDevId, int aoChn, IMPAudioFrame * données, bloc IMPBlock)
 *
 * Envoyer une trame de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[in] aoChn .
 * @param[in] pointeur de données vers la structure de la trame audio.
 * @param[in] block bloquer / Drapeau non bloquant .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks 
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
 * @attention .
 */
int IMP_AO_SendFrame(int audioDevId, int aoChn, IMPAudioFrame *data, IMPBlock block);

/**
 * @fn int IMP_AO_PauseChn (int audioDevId, int aoChn)
 *
 * Suspendre le canal de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[in] aoChn .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AO_PauseChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_ResumeChn (int audioDevId, int aoChn)
 *
 * Restaurer le canal de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[in] aoChn .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AO_ResumeChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_ClearChnBuf (int audioDevId, int aoChn)
 *
 * Effacer le tampon de données audio actuel dans le canal de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[in] aoChn .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AO_ClearChnBuf(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_QueryChnStat (int audioDevId, int aoChn, IMPAudioOChnState * statut)
 *
 * Interroger l'état actuel du tampon de données audio dans le canal de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[in] aoChn .
 * @param[out] status Pointeur de structure d'état du cache.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
int IMP_AO_QueryChnStat(int audioDevId, int aoChn, IMPAudioOChnState *status);

/**
 * @fn int IMP_AENC_CreateChn (int aeChn, IMPAudioEncChnAttr * attr)
 *
 * Créer un canal d'encodage audio .
 *
 * @param[in] numéro de canal aeChn.
 * @param[in] attr Pointeur d'attribut de canal de codage audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks 
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
 * @attention Le SDK prend actuellement en charge le codage PT_G711A, PT_G711U et PT_G726. 
 * Alors utilisez SDK Encodage en , juste besoin de attr.type = PT_G711A Peut . \n
 * Comment utiliser un encodeur personnalisé , Vous devez enregistrer l'encodeur , L'exemple de code est expliqué dans l'interface d'inscription .
 */
 int IMP_AENC_CreateChn(int aeChn, IMPAudioEncChnAttr *attr);

/**
 * @fn int IMP_AENC_DestroyChn (int aeChn)
 *
 * Détruire le canal d'encodage audio .
 *
 * @param[in] aeChn Le numéro de canal .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention Utilisé avec IMP_AENC_CreateChn.
 */
 int IMP_AENC_DestroyChn(int aeChn);

/**
 * @fn int IMP_AENC_SendFrame (int aeChn, IMPAudioFrame * frm)
 *
 * Envoyer des trames audio encodées audio .
 *
 * @param[in] aeChn .
 * @param[in] frm .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks 
 * @code 
 * while(1) {
 *		// Lire une trame de données 
 *		ret = fread(buf_pcm, 1, IMP_AUDIO_BUF_SIZE, file_pcm);
 *		if(ret < IMP_AUDIO_BUF_SIZE)
 *			break;
 *
 *		// codage 
 *		IMPAudioFrame frm;
 *		frm.virAddr = (uint32_t *)buf_pcm;
 *		frm.len = ret;
 *		ret = IMP_AENC_SendFrame(AeChn, &frm);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode send frame failed\n");
 *			return ret;
 *		}
 *
 *		// Obtenir le flux de code 
 *		IMPAudioStream stream;
 *		ret = IMP_AENC_GetStream(AeChn, &stream, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode get stream failed\n");
 *			return ret;
 *		}
 *
 *		// Utiliser le flux de code 
 *		fwrite(stream.stream, 1, stream.len, file_g711);
 *
 *		// Diffuser le flux de code 
 *		ret = IMP_AENC_ReleaseStream(AeChn, &stream);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode release stream failed\n");
 *			return ret;
 *		}
 * }
 * @endcode 
 *
 * @attention .
 */
 int IMP_AENC_SendFrame(int aeChn, IMPAudioFrame *frm);

/**
 * @fn int IMP_AENC_PollingStream (int AeChn, int timeout_ms non signé)
 *
 * Polling Tampon de flux audio codé .
 *
 * @param[in] Numéro de canal d'entrée d'encodage audio AeChn.
 * @param[in] timeout_ms Polling temps supplémentaire .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention Utilisez cette interface avant d'utiliser IMP_AENC_GetStream, lorsque l'interface est appelée avec succès, cela signifie audio
 *			 Les données encodées sont prêtes ， IMP_AENC_GetStream Obtenez les données encodées .
 */
int IMP_AENC_PollingStream(int AeChn, unsigned int timeout_ms);

/**
 * @fn int IMP_AENC_GetStream (int aeChn, IMPAudioStream * flux, bloc IMPBlock)
 *
 * Obtenez le flux de code après l'encodage .
 *
 * @param[in] aeChn .
 * @param[in] stream Obtenez le flux de code audio.
 * @param[in] block / .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks Consultez la description de la fonction IMP_AENC_SendFrame pour l'exemple de code.
 *
 * @attention .
 */
 int IMP_AENC_GetStream(int aeChn, IMPAudioStream *stream ,IMPBlock block);

/**
 * @fn int IMP_AENC_ReleaseStream (int aeChn, IMPAudioStream * flux)
 *
 * Libérez le flux de code obtenu à partir du canal de codage audio .
 *
 * @param[in] aeChn .
 * @param[in] stream Récupère le pointeur du flux audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks Voir un exemple de code IMP_AENC_SendFrame Description de la fonction .
 *
 * @attention .
 */
 int IMP_AENC_ReleaseStream(int aeChn,IMPAudioStream *stream);

/**
 * @fn int IMP_AENC_RegisterEncoder (int * handle, IMPAudioEncEncoder * encoder)
 *
 * Enregistrer l'encodeur .
 *
 * @param[in] poignée d'enregistrement ps32handle.
 * @param[in] encoder Structure d'attributs d'encodeur.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks 
 * @code 
 * int handle_g711a = 0;
 * IMPAudioEncEncoder my_encoder;
 * my_encoder.maxFrmLen = 1024;
 * sprintf(my_encoder.name, "%s", "MY_G711A");
 * my_encoder.openEncoder = NULL; // Fonction de rappel de l'encodeur 
 * my_encoder.encoderFrm = MY_G711A_Encode_Frm; // 
 * my_encoder.closeEncoder = NULL; // 
 *
 * ret = IMP_AENC_RegisterEncoder(&handle_g711a, &my_encoder);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "IMP_AENC_RegisterEncoder failed\n");
 *		return ret;
 * }
 *
 * // Utiliser l'encodeur 
 * int AeChn = 0;
 * IMPAudioEncChnAttr attr;
 * attr.type = handle_g711a; // Encodeur type gal au retour d'une inscription réussie handle_g711a La valeur de .
 * attr.bufSize = 20;
 * ret = IMP_AENC_CreateChn(AeChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "imp audio encode create channel failed\n");
 *		return ret;
 * }
 * @endcode 
 *
 * @attention Après l'enregistrement, la méthode d'utilisation est la même que l'utilisation de l'encodeur intégré du SDK.
 */
 int IMP_AENC_RegisterEncoder(int *handle, IMPAudioEncEncoder *encoder);

/**
 * @fn int IMP_AENC_ReleaseEncoder (int * handle)
 *
 * Déconnectez-vous de l'encodeur .
 *
 * @param[in] ps32handle registration handle (le handle obtenu lors de l'enregistrement de l'encodeur).
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
 int IMP_AENC_ReleaseEncoder(int *handle);

/**
 * @fn int IMP_ADEC_CreateChn (int adChn, IMPAudioDecChnAttr * attr)
 *
 * Créer un canal de décodage audio .
 *
 * @param[in] numéro de canal adChn.
 * @param[in] attr Pointeur d'attribut de canal.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks 
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
 * @attention .
 */
 int IMP_ADEC_CreateChn(int adChn, IMPAudioDecChnAttr *attr);

/**
 * @fn int IMP_ADEC_DestroyChn (int adChn)
 *
 * Détruire le canal de décodage audio .
 *
 * @param[in] adChn .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
 int IMP_ADEC_DestroyChn(int adChn);

/**
 * @fn int IMP_ADEC_SendStream (int adChn, IMPAudioStream * flux, bloc IMPBlock)
 *
 * Envoyer le flux de code audio au canal de décodage audio .
 *
 * @param[in] adChn .
 * @param[in] stream Flux de code audio.
 * @param[in] block / .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks 
 * @code 
 * while(1) {
 *		// Obtenez les données à décoder 
 *		ret = fread(buf_g711, 1, IMP_AUDIO_BUF_SIZE/2, file_g711);
 *		if(ret < IMP_AUDIO_BUF_SIZE/2)
 *			break;
 *
 *		// Envoyer des données décodées 
 *		IMPAudioStream stream_in;
 *		stream_in.stream = (uint8_t *)buf_g711;
 *		stream_in.len = ret;
 *		ret = IMP_ADEC_SendStream(adChn, &stream_in, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode send frame failed\n");
 *			return ret;
 *		}
 *
 *		// Obtenez les données décodées 
 *		IMPAudioStream stream_out;
 *		ret = IMP_ADEC_GetStream(adChn, &stream_out, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio decoder get stream failed\n");
 *			return ret;
 *		}
 *
 *		// Utiliser des données décodées 
 *		fwrite(stream_out.stream, 1, stream_out.len, file_pcm);
 *
 *		// Libérez les données décodées 
 *		ret = IMP_ADEC_ReleaseStream(adChn, &stream_out);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio decoder release stream failed\n");
 *			return ret;
 *		}
 * }
 * @endcode 
 *
 * @attention .
 */
 int IMP_ADEC_SendStream(int adChn, IMPAudioStream *stream, IMPBlock block);

/**
 * @fn int IMP_ADEC_PollingStream (int AdChn, int timeout_ms non signé)
 *
 * Polling Décoder le tampon de flux audio .
 *
 * @param[in] Numéro de canal d'entrée de décodage audio AdChn.
 * @param[in] timeout_ms Polling .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention Utilisez cette interface avant d'utiliser IMP_ADEC_GetStream, lorsque l'interface est appelée avec succès, cela signifie audio
 *			 Les données décodées sont prêtes ， IMP_ADEC_GetStream Obtenez les données décodées .
 */
int IMP_ADEC_PollingStream(int AdChn, unsigned int timeout_ms);

/**
 * @fn int IMP_ADEC_GetStream (int adChn, IMPAudioStream * flux, bloc IMPBlock)
 *
 * Obtenez le flux de code décodé .
 *
 * @param[in] adChn .
 * @param[in] stream Récupère le flux de code décodé.
 * @param[in] block / .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks Voir la description de la fonction IMP_ADEC_SendStream pour l'exemple de code.
 *
 * @attention .
 */
int IMP_ADEC_GetStream(int adChn, IMPAudioStream *stream ,IMPBlock block);

/**
 * @fn int IMP_ADEC_ReleaseStream (int adChn, IMPAudioStream * flux)
 *
 * Libérez le flux de code obtenu à partir du canal de décodage audio .
 *
 * @param[in] adChn .
 * @param[in] pointeur de flux de flux de code audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks IMP_ADEC_SendStream .
 *
 * @attention .
 */
int IMP_ADEC_ReleaseStream(int adChn,IMPAudioStream *stream);

/**
 * @fn int IMP_ADEC_ClearChnBuf (int adChn)
 *
 * Effacer le tampon de données audio actuel dans le canal de décodage audio .
 *
 * @param[in] adChn .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
 int IMP_ADEC_ClearChnBuf(int adChn);

/**
 * @fn int IMP_ADEC_RegisterDecoder (int * handle, IMPAudioDecDecoder * décodeur)
 *
 * Enregistrer le décodeur .
 *
 * @param[in] ps32handle Enregistrer la poignée .
 * @param[in] décodeur Structure d'attribut du décodeur.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks 
 * @code 
 * int handle_g711a = 0;
 * IMPAudioDecDecoder my_decoder;
 * sprintf(my_decoder.name, "%s", "MY_G711A");
 * my_decoder.openDecoder = NULL; // Fonction de rappel du décodeur 
 * my_decoder.decodeFrm = MY_G711A_Decode_Frm; // 
 * my_decoder.getFrmInfo = NULL; // 
 * my_decoder.closeDecoder = NULL; // 
 *
 * // 
 * ret = IMP_ADEC_RegisterDecoder(&handle_g711a, &my_decoder);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "IMP_ADEC_RegisterDecoder failed\n");
 *		return ret;
 * }
 *
 * // Utiliser le décodeur 
 * int adChn = 0;
 * IMPAudioDecChnAttr attr;
 * attr.type = handle_g711a; // décodage type gal à celui renvoyé par l'enregistrement du décodeur handle_g711a.
 * attr.bufSize = 20;
 * attr.mode = ADEC_MODE_PACK;
 * // Créer un canal de décodage 
 * ret = IMP_ADEC_CreateChn(adChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "imp audio decoder create channel failed\n");
 *		return ret;
 * }
 * @endcode 
 *
 * @attention Après l'enregistrement, la méthode d'utilisation est la même que l'utilisation du décodeur intégré du SDK.
 */
 int IMP_ADEC_RegisterDecoder(int *handle, IMPAudioDecDecoder *decoder);

/**
 * @fn int IMP_ADEC_ReleaseDecoder (int * handle)
 *
 * Désenregistrer le décodeur .
 *
 * @param[in] ps32handle registration handle (handle obtenu lors de l'enregistrement du décodeur).
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
 int IMP_ADEC_ReleaseDecoder(int *handle);

/**
 * ACODEC Configuration .
 */
/**
 * @fn int IMP_AI_SetVol (int audioDevId, int aiChn, int aiVol)
 *
 * Régler le volume d'entrée audio .
 *
 * @param[in] aiDevId Numéro de périphérique d'entrée audio .
 * @param[in] aiChn .
 * @param[in] aiVol Niveau de volume d'entrée audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks La plage de valeurs du volume est [-30 ~ 120]. -30 signifie muet et 120 signifie amplifier le son de 30 dB par pas de 0,5 dB.
 * @remarks Parmi eux, 60 est un point critique pour le réglage du volume. UNE cette valeur, le logiciel n'augmente ni ne diminue le volume. Lorsque la valeur de volume est inférieure à 60, le volume diminue de 0,5 dB pour chaque diminution; lorsque la valeur de volume est supérieur à 60, l'augmentation de 1, le volume est augmenté de 0,5 dB.
 *
 * Exemple de code 
 * @code 
 * int volume = 60;
 * ret = IMP_AI_SetVol(devID, chnID, volume);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Record set volume failed\n");
 *		return ret;
 * }
 * @endcode 
 * @attention Si l'entrée aiVol dépasse la plage de [-30 ~ 120], la valeur inférieure à -30 sera -30 et la valeur supérieure à 120 sera 120.
 */
 int IMP_AI_SetVol(int audioDevId, int aiChn, int aiVol);

/**
 * @fn int IMP_AI_GetVol (int audioDevId, int aiChn, int * vol)
 *
 * Obtenez le volume d'entrée audio .
 *
 * @param[in] aiDevId .
 * @param[in] aiChn .
 * @param[out] vol Volume du canal d'entrée audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
 int IMP_AI_GetVol(int audioDevId, int aiChn, int *vol);

/**
 * @fn int IMP_AI_SetVolMute (int audioDevId, int aiChn, int muet)
 *
 * Régler la sourdine de l'entrée audio .
 *
 * @param[in] aiDevId .
 * @param[in] aiChn .
 * @param[out] mute Indicateur de mute de l'entrée audio, mute = 0: désactiver le mute, mute = 1: activer le mute.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks Appelez cette interface pour couper immédiatement le son.
 *
 * @attention .
 */
 int IMP_AI_SetVolMute(int audioDevId, int aiChn, int mute);

/**
 * @fn int IMP_AO_SetVol (int audioDevId, int aoChn, int aoVol)
 *
 * Régler le volume du canal de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[in] aoChn .
 * @param[in] aoVol Volume de sortie audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks La plage de volume est [-30 ~ 120]. -30 Signifie muet ,120 Moyens d'amplifier le son 30dB, Taille de pas 0.5dB.
 * @remarks parmi eux 60 Est un point critique pour le réglage du volume ， Le logiciel n'augmente ni ne diminue le volume à cette valeur ， Lorsque la valeur du volume est inférieure à 60 Temps ， Chaque goutte 1， Baisser le volume 0.5dB ; Lorsque la valeur du volume est supérieure à 60 ， Augmenter 1， Augmentation de volume 0.5dB . 
 *
 * @attention Si l'aoVol entré dépasse la plage de [-30 ~ 120], la valeur inférieure à -30 sera -30 et la valeur supérieure à 120 sera 120.
 */
 int IMP_AO_SetVol(int audioDevId, int aoChn, int aoVol);

/**
 * @fn int IMP_AO_GetVol (int audioDevId, int aoChn, int * vol)
 *
 * Obtenir le volume du canal de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[in] aoChn .
 * @param[out] aoVol Volume de sortie audio .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
 int IMP_AO_GetVol(int audioDevId, int aoChn, int *vol);

/**
 * @fn int IMP_AO_SetVolMute (int audioDevId, int aoChn, int mute)
 *
 * Régler la sourdine de la sortie audio .
 *
 * @param[in] audioDevId Numéro du périphérique de sortie audio.
 * @param[in] aoChn .
 * @param[out] mute sortie audio mute flag, mute = 0: désactiver le mute, mute = 1: activer le mute.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks Appelez cette interface pour couper le son immédiatement .
 *
 * @attention .
 */
 int IMP_AO_SetVolMute(int audioDevId, int aoChn, int mute);

/**
 * @fn int IMP_AI_SetGain (int audioDevId, int aiChn, int aiGain)
 *
 * Régler le gain d'entrée audio .
 *
 * @param[in] audioDevId Numéro de périphérique d'entrée audio.
 * @param[in] aiChn .
 * @param[out] aiGain gain d'entrée audio, plage [0 ~ 31].
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention La plage de aiGain est [0 ~ 31], si la valeur d'entrée est inférieure à 0, la valeur de aiGain sera 
 * définir comme 0. Si la valeur est supérieure à 31,aiGain Sera réglé sur 10.
 *
 */
 int IMP_AI_SetGain(int audioDevId, int aiChn, int aiGain);

/**
 * @fn int IMP_AI_GetGain (int audioDevId, int aiChn, int * aiGain)
 *
 * Obtenir AI Gagner de la valeur .
 *
 * @param[in] audioDevId .
 * @param[in] aiChn .
 * @param[out] aiGain Gain d'entrée audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
 int IMP_AI_GetGain(int audioDevId, int aiChn, int *aiGain);

/**
 * @fn int IMP_AO_SetGain (int audioDevId, int aoChn, int aoGain)
 *
 * Régler le gain de sortie audio .
 *
 * @param[in] audioDevId Numéro du périphérique de sortie audio .
 * @param[in] aoChn .
 * @param[out] Gain de sortie audio aoGain, plage [0 ~ 0xcb].
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention La plage de aoGain est [0 ~ 31], si la valeur d'entrée est inférieure à 0, la valeur de aoGain sera 
 * 0. 31,aoGain 31.
 *
 */
 int IMP_AO_SetGain(int audioDevId, int aoChn, int aoGain);

/**
 * @fn int IMP_AO_GetGain (int audioDevId, int aoChn, int * aoGain)
 *
 * Obtenez le gain de sortie audio .
 *
 * @param[in] audioDevId .
 * @param[in] aoChn .
 * @param[out] aoGain gain de sortie audio.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 *
 * @attention .
 */
 int IMP_AO_GetGain(int audioDevId, int aoChn, int *aoGain);

/**
 * @fn int IMP_AO_Soft_Mute (int audioDevId, int aoChn)
 *
 * Commande de sourdine douce de sortie .
 *
 * @param[in] audioDevId .
 * @param[in] aoChn .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks L'appel de cette interface ne coupera pas immédiatement le son, mais réduira lentement le volume à partir de l'état de lecture normal jusqu'à ce qu'il soit vraiment coupé.
 *
 * @attention .
 */
 int IMP_AO_Soft_Mute(int audioDevId, int aoChn);

/**
 * @fn int imp_AO_soft_UN mute (int audio Devi, int AOC peut aussi)
 *
 * Contrôle de mise en sourdine douce de sortie.
 *
 * @param[in] audioDevId.
 * @param[in] aoChn.
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks L'appel de cette interface ne restaurera pas immédiatement le volume actuel, mais augmentera lentement le volume à partir de l'état muet jusqu'à ce que le volume atteigne le volume défini.
 *
 * @attention .
 */
 int IMP_AO_Soft_UNMute(int audioDevId, int aoChn);

/**
 * @fn int IMP_AI_GetFrameAndRef (int audioDevId, int aiChn, IMPAudioFrame * frm, IMPAudioFrame * ref, bloc IMPBlock)
 *
 * Obtenir une image audio et une image de référence de sortie .
 *
 * @param[in] audioDevId .
 * @param[in] aiChn .
 * @param[out] frm .
 * @param[out] ref fait référence au pointeur de la structure du cadre.
 * @param[in] block / .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks 
 * @code 
 * IMPAudioFrame frm;
 * IMPAudioFrame ref;
 * // 
 * ret = IMP_AI_GetFrameAndRef(devID, chnID, &frm, &ref, BLOCK);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Get Frame Data error\n");
 *		return ret;
 * }
 *
 * fwrite(frm.virAddr, 1, frm.len, record_file); // 
 * fwrite(ref.virAddr, 1, ref.len, ref_file); // Utiliser des cadres de référence audio 
 *
 * // 
 * ret = IMP_AI_ReleaseFrame(devID, chnID, &frm);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio release frame data error\n");
 *		return ret;
 * }
 * @endcode 
 *
 * @attention .
 */
 int IMP_AI_GetFrameAndRef(int audioDevId, int aiChn, IMPAudioFrame *frm, IMPAudioFrame *ref, IMPBlock block);

/**
 * @fn int IMP_AI_EnableAecRefFrame (int audioDevId, int aiChn, int audioAoDevId, int aoChn)
 *
 * Ouvrir pour obtenir le cadre de référence .
 *
 * @param[in] audioDevId .
 * @param[in] aiChn .
 * @param[in] audioAoDevId Numéro du périphérique de sortie audio.
 * @param[in] aoChn .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks Appelez cette interface avant d'appeler IMP_AI_GetFrameAndRef.
 * @attention .
 */
 int IMP_AI_EnableAecRefFrame(int audioDevId, int aiChn, int audioAoDevId, int aoChn);

/**
 * @fn int IMP_AI_DisableAecRefFrame (int audioDevId, int aiChn, int audioAoDevId, int aoChn)
 *
 * Fermer Obtenir le cadre de référence .
 *
 * @param[in] audioDevId .
 * @param[in] aiChn .
 * @param[in] audioAoDevId .
 * @param[in] aoChn .
 *
 * @retval 0 .
 * @retval 0 .
 *
 * @remarks .
 * @attention .
 */
 int IMP_AI_DisableAecRefFrame(int audioDevId, int aiChn, int audioAoDevId, int aoChn);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_AUDIO_H__ */
