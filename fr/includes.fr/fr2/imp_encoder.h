/*
 * IMP Encoder func header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_ENCODER_H__
#define __IMP_ENCODER_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file 
 * IMP Fichier d'en-tête de codage vidéo 
 */

/**
 * @defgroup IMP_Encoder
 * @ingroup lutin
 * @brief Module d'encodage vidéo (H264, JPEG), y compris la gestion des canaux d'encodage, les réglages des paramètres d'encodage et d'autres fonctions
 * @section structure du module enc_struct 1
 * Encoder La structure interne du module est la suivante: 
 * @image html encoder_struct.jpg
 * Comme le montre la figure ， Le module de codage se compose de plusieurs Group Composition (en T15 Soutenir deux Group ) ， Chaque Group Codé par Channel composition. 
 * Chaque code Channel Avec un tampon de flux de code de sortie ， Ce tampon se compose de plusieurs buffer composition. 
 * @section enc_channel 2 Canal de codage
 * Un code Channel Peut compléter le codage d'un protocole. Group Peut en ajouter un H264 codage Channel Avec un JPEG codage Channel . 
 * @section enc_rc 3 Contrôle de débit
 * @subsection enc_cbr 3.1 CBR
 * CBR ( Constent Bit Rate ) Débit constant ， C'est-à-dire que le taux de codage est constant pendant le temps de statistiques de taux. 
 * À H.264 Codage comme exemple ， L'utilisateur peut définir maxQp，minQp，bitrate Attendre. 
 * maxQp，minQp Utilisé pour contrôler la plage de qualité de l'image ， bitrate Il est utilisé pour bloquer le débit de code moyen pendant le temps statistique. 
 * Lorsque le débit de code est supérieur au débit de code constant ， image QP Will progressivement maxQp Ajustement ， Lorsque le taux de codage est bien inférieur au taux constant ， image QP Will progressivement minQp Ajustement. 
 * Lorsque l'image QP atteindre maxQp Temps ，QP Serré au maximum ，bitrate L'effet de serrage n'est pas valide ， Le taux de codage peut dépasser bitrate . 
 * Lorsque l'image QP atteindre minQp Temps ，QP Serré au minimum ， A ce moment, le taux de code de l'encodage a atteint la valeur maximale ， Et la qualité d'image est la meilleure. 
 * @subsection enc_FixQP 3.2 FixQP
 * Fix Qp fixé Qp évaluer. ， Encoder tous les macroblocs de l'image Qp Même valeur ， Utiliser des images définies par l'utilisateur Qp évaluer. 
 * @{
 */

/**
 * Code de définition Channel Mode contrôleur de débit 
 */
typedef enum {
	ENC_RC_MODE_H264FIXQP = 0,	/**< H.264 Fixqp Mode (support) */
	ENC_RC_MODE_H264CBR = 1,	/**< H.264 CBR Mode (support) */
	ENC_RC_MODE_H264ABR = 2,	/**< H.264 ABR mode */
	ENC_RC_MODE_H264VBR = 3,	/**< H.264 VBR mode */
	ENC_RC_MODE_H264INV = 4,	/**< H.264 INV mode */
} IMPEncoderRcMode;

/**
 * Code de définition channel Structure de fréquence d'images ,frmRateNum avec frmRateDen Après avoir été divisé par le plus grand diviseur commun, le plus petit multiple commun entre les deux ne peut pas dépasser 64， Il est préférable d'être divisible par le plus grand diviseur commun avant de définir 
 */
typedef struct {
	uint32_t	frmRateNum;				/**< Le nombre d'unités de temps en une seconde , En unités de temps. */
	uint32_t	frmRateDen;				/**< Le nombre d'unités de temps dans une trame , En unités de temps. */
} IMPEncoderFrmRate;

/**
 * définition H.264 codage Channel Fixqp Structure de la propriété 
 */
typedef struct {
	uint32_t			maxGop;			/**< H.264 gop évaluer ， Doit être un multiple entier de la fréquence d'images */
	IMPEncoderFrmRate	outFrmRate;		/**< codage Channel La fréquence d'images de sortie (la fréquence d'images de sortie ne peut pas être supérieure à la fréquence d'images d'entrée) */
	uint32_t			qp;				/**< Niveau du cadre Qp évaluer */
} IMPEncoderAttrH264FixQP;

/**
 * définition H.264 codage Channel CBR Structure de la propriété 
 */
typedef struct {
	uint32_t			maxGop;			/**< H.264 gop évaluer ， Doit être un multiple entier de la fréquence d'images */
	IMPEncoderFrmRate	outFrmRate;		/**< codage Channel La fréquence d'images de sortie (la fréquence d'images de sortie ne peut pas être supérieure à la fréquence d'images d'entrée) */
	uint32_t			maxQp;			/**< L'encodeur prend en charge la plus grande image QP */
	uint32_t			minQp;			/**< L'encodeur prend en charge la plus petite image QP */
	uint32_t			outBitRate;		/**< Débit binaire de sortie du codeur , À kbps En tant qu'unité */
	uint32_t			maxFPS;			/**< Fréquence d'images maximale */
	uint32_t			minFPS;			/**< Fréquence d'images minimale */
	int					IBiasLvl;		/**< I Poids du cadre ， Etre prêt (-3~3)，7 Niveaux */
	uint32_t			FrmQPStep;		/**< Intertrame QP Changer l'étape */
	uint32_t			GOPQPStep;		/**< GOP compris entre QP Changer l'étape */
	bool				AdaptiveMode;	/**< Mode adaptatif */
	bool				GOPRelation;	/**< GOP Est-ce lié */
} IMPEncoderAttrH264CBR;

/**
 * définition H.264 codage Channel VBR Structure de la propriété 
 */
typedef struct {
	uint32_t			maxGop;			/**< H.264 gop évaluer ， Doit être un multiple entier de la fréquence d'images */
	IMPEncoderFrmRate	outFrmRate;		/**< codage Channel La fréquence d'images de sortie (la fréquence d'images de sortie ne peut pas être supérieure à la fréquence d'images d'entrée) */
	uint32_t			maxQp;			/**< L'encodeur prend en charge la plus grande image QP */
	uint32_t			minQp;			/**< L'encodeur prend en charge la plus petite image QP */
	uint32_t			staticTime;		/**< Temps de statistiques de débit binaire , En secondes */
	uint32_t			maxBitRate;		/**< Débit binaire maximal de la sortie du codeur , À kbps En tant qu'unité */
	uint32_t			changePos;		/**< VBR Commencez à vous ajuster Qp Le rapport entre le débit de code à ce moment et le débit de code maximal , Gammes :[50, 100] */
	uint32_t			FrmQPStep;		/**< Intertrame QP Changer l'étape */
	uint32_t			GOPQPStep;		/**< GOP compris entre QP Changer l'étape */
} IMPEncoderAttrH264VBR;

/**
 * définition H.264 codage Channel Propriétés de dématriçage 
 */
typedef struct {
	bool				enable;			/**< Activer ou non la fonction de dématriçage */
	bool				isAutoMode;		/**< Activer le mode de dématriçage automatique ， 0: Manuel ，1 :automatique */
	int					demaskCnt;		/**< Paramètre de temps de maintien du dématriçage */
	int					demaskThresd;	/**< Seuil de dématriçage */
} IMPEncoderAttrH264Demask;

/**
 * définition H.264 codage Channel Propriétés de débruitage , Ne peut pas être modifié une fois activé , Mais le type de débruitage peut être changé dynamiquement ;
 */
typedef struct {
	bool				enable;			/**< Activer ou non la fonction de débruitage , 0: ignorer ,1: Réduction du bruit en fonction du type de trame actuel , Perte maximale d'informations ,2: presse I Débruitage du cadre ， Perte d'informations modérée */
	int					dnType;			/**< Type de débruitage ,0: ignorer ， Pas de réduction du bruit ,1: utilisation IP Réduction du bruit du type de cadre ,2: utilisation I Réduction du bruit du type de cadre */
	int					dnIQp;			/**< Débruitage I Paramètre de quantification de trame */
	int					dnPQp;			/**< Débruitage P Paramètre de quantification de trame */
} IMPEncoderAttrH264Denoise;

/**
 * définition H.264 codage Channel Mode d'utilisation du cadre d'entrée 
 */
typedef enum {
	ENC_FRM_BYPASS	= 0,		/**< Mode d'utilisation complet séquentiel - Mode par défaut */
	ENC_FRM_REUSED	= 1,		/**< Réutiliser le mode de trame */
	ENC_FRM_SKIP	= 2,		/**< Mode drop frame */
} EncFrmUsedMode;

/**
 * définition H.264 codage Channel Attributs du mode d'utilisation du cadre d'entrée 
 */
typedef struct {
	bool				enable;			/**< Activer ou non le mode d'utilisation du cadre d'entrée */
	EncFrmUsedMode		frmUsedMode;	/**< Mode d'utilisation du cadre d'entrée */
	uint32_t			frmUsedTimes;	/**< Intervalle d'image utilisé à chaque fois en mode image répétée ou en mode image perdue */
} IMPEncoderAttrH264FrmUsed;

typedef enum {
	IMP_H264_STYPE_N11			= 0,	/**< 1 Référence d'image à double saut (instance unique) */
	IMP_H264_STYPE_N1X			= 1,	/**< 1 Référence d'image à double saut (multi-instance) */
	IMP_H264_STYPE_N2X			= 2,	/**< 2 Référence de cadre à double saut */
	IMP_H264_STYPE_N4X			= 3,	/**< 4 Référence de cadre à double saut */
	IMP_H264_STYPE_HN1_FALSE	= 4,	/**< Mode de saut d'image avancé: N,1,HI_FALSE */
	IMP_H264_STYPE_HN1_TRUE		= 5,	/**< Mode de saut d'image avancé: NN,1,HI_TURE */
	IMP_H264_STYPE_H1M_TRUE		= 6,	/**< Mode de saut d'image avancé: N1,M,HI_TRUE */
} IMPH264SkipType;

typedef enum {
	IMP_H264_FS_IDR		= 0,	/**< Images clés en mode de saut d'image avancé */
	IMP_H264_FS_BASE	= 1,	/**< Image de référence en mode de saut d'image avancé */
	IMP_H264_FS_ENHANCE	= 2,	/**< Cadre amélioré en mode de saut de cadre avancé */
} IMPH264RefType;

/**
 * définition H264 Structure de type de saut de trame avancée 
 */
typedef struct {
	IMPH264SkipType	h264SkipType;	/**< Type de saut de trame */
	int				m;				/**< Intervalle d'image amélioré */
	int				n;				/**< Intervalle de trame de référence */
} IMPEncoderAttrH264HSkip;

/**
 * définition H264 Structure de type de saut de cadre avancé vierge 
 */
typedef struct {
	int				i_skip_distance;	/**< Nombre d'images vierges consécutives */
} IMPEncoderAttrH264BSkip;


/**
 * Code de définition Channel Propriétés du contrôleur de taux 
 */
typedef struct {
	IMPEncoderRcMode rcMode;						/**< RC mode */
	union {
		IMPEncoderAttrH264FixQP	 attrH264FixQp;		/**< H.264 Codage de protocole Channel Fixqp Attributs de mode */
		IMPEncoderAttrH264CBR	 attrH264Cbr;		/**< H.264 Codage de protocole Channel Cbr Attributs de mode */
		IMPEncoderAttrH264VBR	 attrH264Vbr;		/**< H.264 Codage de protocole Channel Vbr Attributs de mode */
	};
	IMPEncoderAttrH264FrmUsed	attrH264FrmUsed;	/**< Attributs du mode d'utilisation du cadre d'entrée */
	IMPEncoderAttrH264Demask	attrH264Demask;		/**< Propriétés de dématriçage */
	IMPEncoderAttrH264Denoise	attrH264Denoise;	/**< Propriétés de débruitage */
	IMPEncoderAttrH264HSkip		attrH264HSkip;		/**< H264 Propriétés avancées de saut de trame */
	IMPEncoderAttrH264BSkip		attrH264BSkip;		/**< H264 Attribut de cadre de saut vide */
} IMPEncoderRcAttr;

/**
 * H264 Flux NALU Types de 
 */
typedef enum {
	IMP_NAL_UNKNOWN		= 0,	/**< non spécifié */
	IMP_NAL_SLICE		= 1,	/**< Un non IDR Bande de codage d'image */
	IMP_NAL_SLICE_DPA	= 2,	/**< Bloc de segmentation de données de bande codé A */
	IMP_NAL_SLICE_DPB	= 3,	/**< Bloc de segmentation de données de bande codé B */
	IMP_NAL_SLICE_DPC	= 4,	/**< Bloc de segmentation de données de bande codé C */
	IMP_NAL_SLICE_IDR	= 5,	/**< IDR Bande de codage d'image */
	IMP_NAL_SEI			= 6,	/**< Informations sur les améliorations auxiliaires (SEI) */
	IMP_NAL_SPS			= 7,	/**< Jeu de paramètres de séquence */
	IMP_NAL_PPS			= 8,	/**< Jeu de paramètres d'image */
	IMP_NAL_AUD			= 9,	/**< Séparateur d'unité d'accès */
	IMP_NAL_FILLER		= 12,	/**< Entrée de données */
} IMPEncoderH264NaluType;

/**
 * Définir le type de flux de code 
 */
typedef union {
	IMPEncoderH264NaluType		h264Type;		/**< H264E NALU Type de paquet de flux */
} IMPEncoderDataType;

/**
 * Définir la structure du paquet de flux de code de trame 
 */
typedef struct {
	uint32_t	phyAddr;						/**< Adresse physique du paquet de flux */
	uint32_t	virAddr;						/**< Adresse virtuelle du paquet de flux */
	uint32_t	length;							/**< Longueur du paquet de flux */

	int64_t		timestamp;						/**< Horodatage ， unité us */
	bool		frameEnd;						/**< Indicateur de fin de trame */

	IMPEncoderDataType	dataType;				/**< Type de flux */
} IMPEncoderPack;

/**
 * Définir la structure du type de flux de trames 
 */
typedef struct {
	IMPEncoderPack	*pack;				/**< Structure des paquets de flux de trames */
	uint32_t	packCount;				/**< Le nombre de tous les paquets dans une trame de flux */
	uint32_t	seq;					/**< Numéro de série du flux ， Obtenez le numéro d'image par image ， Obtenez le numéro de série du colis par colis */
	union {
		IMPH264RefType h264RefType;
	};
} IMPEncoderStream;

/**
 * Définir les propriétés de découpage de l'encodeur ， Commencez par recadrer l'image entrée dans l'encodeur ， Comparer avec la taille du canal d'encodage avant la mise à l'échelle 
 */
typedef struct {
 bool		enable;		/**< Que ce soit pour couper , Gammes :[FALSE, TRUE],TRUE: Activer le découpage ,FALSE: Désactiver le découpage */
 uint32_t	x;			/**< Zone recadrée , Coin supérieur gauche x coordonner */
 uint32_t	y;			/**< Zone recadrée , Coin supérieur gauche y coordonner */
 uint32_t	w;			/**< Zone recadrée , largeur */
 uint32_t	h;			/**< Zone recadrée , haut */
} IMPEncoderCropCfg;

/**
 * Définir l'encodeur pour insérer les attributs de données utilisateur , Seulement pour H264
 */
typedef struct {
	uint32_t			maxUserDataCnt;		/**< Nombre maximum d'utilisateurs pour insérer l'espace du cache de données , gamme: 0-2 */
	uint32_t			maxUserDataSize;	/**< Taille maximale de l'espace du cache de données d'insertion par l'utilisateur , gamme: 16-1024 */
} IMPEncoderUserDataCfg;

/**
 * Définir la structure des attributs du codeur 
 */
typedef struct {
	IMPPayloadType			enType;			/**< Type de protocole de codage */
	uint32_t				bufSize;		/**< Configuration buffer Taille ， Gammes : Pas moins que le produit de la largeur et de la hauteur de l'image 1.5 Fois. ， Réglez ce paramètre sur 0，IMP La taille est automatiquement calculée en interne */
	uint32_t				profile;		/**< Niveau de codage , 0: baseline; 1:MP; 2:HP */
	uint32_t				picWidth;		/**< Largeur de l'image codée */
	uint32_t				picHeight;		/**< Hauteur de l'image codée */
	IMPEncoderCropCfg		crop;			/**< Propriétés de recadrage de l'encodeur */
	IMPEncoderUserDataCfg	userData;		/**< Insérer des attributs de données utilisateur , Seulement pour H264 */
} IMPEncoderAttr;

/**
 * Code de définition Channel Structure d'attribut 
 */
typedef struct {
	IMPEncoderAttr		encAttr;	/**< Structure d'attribut du codeur */
	IMPEncoderRcAttr	rcAttr;			/**< Structure d'attribut du contrôleur de débit */
} IMPEncoderCHNAttr;

/**
 * Code de définition Channel Structure de l'État 
 */
typedef struct {
	bool		registered;				/**< Inscrivez-vous à Group Signe ， Gammes :{TRUE, FALSE}，TRUE: inscrit ，FALSE: non enregistré */
	uint32_t	leftPics;				/**< Nombre d'images à encoder */
	uint32_t	leftStreamBytes;		/**< Flux buffer Restant byte numéro */
	uint32_t	leftStreamFrames;		/**< Flux buffer Images restantes */
	uint32_t	curPacks;				/**< Le nombre de paquets de flux dans la trame actuelle */
	uint32_t	work_done;				/**< État de fonctionnement du programme de canal ，0 :fonctionnement ，1， Ne pas courrir */
} IMPEncoderCHNStat;

/**
 * Définir la couleur en gris (C2G) paramètre 
 */
typedef struct {
 bool	enable;			/**< Activer ou désactiver la fonction de couleur à gris */
} IMPEncoderColor2GreyCfg;

/**
 * Définir les paramètres EnableIDR paramètre 
 */
typedef struct {
 bool	enable;			/**< Définir ou non EnableIDR */
} IMPEncoderEnIDRCfg;

/**
 * Définir les paramètres gopsize paramètre 
 */
typedef struct {
	int		gopsize;			/**< IDR paramètre */
} IMPEncoderGOPSizeCfg;

/**
 * Définir les paramètres ROI paramètre 
 */
typedef struct {
	uint32_t	u32Index;	/**< ROI Valeur d'index de zone ， Etre prêt 0-7 */
	bool		bEnable;	/**< Activer ou non cette zone ROI Fonctionnalités */
	bool		bRelatedQp;		/**< 0 :absolu ROI，1 :relativement ROI */
	int			s32Qp;		/**< ROI Aire relative ou absolue qp évaluer */
	IMPRect		rect;		/**< Propriétés des coordonnées de zone */
} IMPEncoderROICfg;

/**
 * @fn int IMP_Encoder_CreateGroup (int encGroup)
 *
 * Créer du code Group
 *
 * @param[in] encGroup Numéro de groupe, plage de valeurs: [0, @ref NR_MAX_ENC_GROUPS-1]
 *
 * @retval 0 succès
 * @retval Échec non nul
 *
 * @remarks Un groupe ne prend en charge qu'une seule résolution et différentes résolutions doivent démarrer un nouveau groupe. 
 *
 * @attention Si le groupe spécifié existe déjà, retourne un échec
 */
int IMP_Encoder_CreateGroup(int encGroup);

/**
 * @fn int IMP_Encoder_DestroyGroup (int encGroup)
 *
 * Détruisez le code Grouop.
 *
 * @param[in] encGroup Group numéro , Gammes :[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Lors de la destruction du groupe, vous devez vous assurer que le groupe est vide, c'est-à-dire qu'aucun canal n'est enregistré dans le groupe ou enregistré dans le groupe
 * de Channel Annulé ， Sinon, il retourne échoué 
 *
 * @attention Détruire le groupe inexistant, puis renvoyer l'échec
 */
int IMP_Encoder_DestroyGroup(int encGroup);

/**
 * @fn int IMP_Encoder_CreateChn (int encChn, const IMPEncoderCHNAttr * attr)
 *
 * Créer du code Channel
 *
 * @param[in] encChn code le numéro de canal, plage de valeurs: [0, @ref NR_MAX_ENC_CHN-1]
 * @param[in] attr encoding Pointeur d'attribut de canal
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'attribut de canal d'encodage se compose de deux parties, l'attribut d'encodeur et l'attribut de contrôle de débit
 * @remarks Les attributs du codeur doivent d'abord sélectionner le protocole de codage, puis attribuer des valeurs aux attributs correspondant à chaque protocole
 */
int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr);

/**
 * @fn int IMP_Encoder_DestroyChn (int encChn)
 *
 * Détruisez le code Channel
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @attention Détruire le canal qui n'existe pas, puis renvoyer l'échec
 * @attention Avant de détruire, il faut s'assurer que le canal n'a pas été enregistré du groupe, sinon il renverra un échec
 */
int IMP_Encoder_DestroyChn(int encChn);

/**
 * @fn int IMP_Encoder_GetChnAttr (int encChn, IMPEncoderCHNAttr * const attr)
 *
 * Obtenez le code Channel Attribut de 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr encoding Attributs de canal
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 */
int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr * const attr);

/**
 * @fn int IMP_Encoder_RegisterChn (int encGroup, int encChn)
 *
 * Code d'enregistrement Channel À Group
 *
 * @param[in] EncGroup encoding Numéro de groupe, plage de valeurs: [0, @ref NR_MAX_ENC_GROUPS-1]
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @attention Enregistrer un canal qui n'existe pas, puis renvoyer un échec
 * @attention Enregistrez le canal dans un groupe inexistant, sinon il renverra un échec
 * @attention Le même canal codé ne peut être enregistré que dans un seul groupe. Si le canal est déjà enregistré dans un certain groupe, il retournera un échec.
 * @attention Si un groupe a été enregistré, ce groupe ne peut pas être enregistré par d'autres canaux, sauf si la relation d'enregistrement précédente est annulée
 */

int IMP_Encoder_RegisterChn(int encGroup, int encChn);
/**
 * @fn int IMP_Encoder_UnRegisterChn (int encChn)
 *
 * Code anti-enregistrement Channel À Group
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Une fois le canal désenregistré, le canal d'encodage sera réinitialisé et le tampon de flux de code dans le canal d'encodage sera effacé, si l'utilisateur utilise toujours
 * Streams non diffusés à temps buffer， Ne sera pas garanti buffer Exactitude des données ， L'utilisateur peut utiliser IMP_Encoder_Query Interface à interroger 
 * code Channel Flux buffer statut ， Flux de confirmation buffer Désenregistrer après le flux de code dans Channel
 *
 * @attention Annuler l'enregistrement du canal non créé, puis renvoyer l'échec
 * @attention Annuler l'enregistrement du canal non enregistré, puis renvoyer l'échec
 * @attention Si le canal d'encodage n'arrête pas de recevoir l'encodage d'image, il renvoie un échec
 */
int IMP_Encoder_UnRegisterChn(int encChn);

/**
 * @fn int IMP_Encoder_StartRecvPic (int encChn)
 *
 * Activer l'encodage Channel Recevoir l'image 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Le canal d'encodage ne peut commencer l'encodage qu'après avoir reçu des images
 *
 * @attention Si le canal n'est pas créé, il renvoie un échec
 * @attention Si le canal n'est pas enregistré dans le groupe, il renvoie un échec
 */
int IMP_Encoder_StartRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_StopRecvPic (int encChn)
 *
 * Arrêter le codage Channel Recevoir l'image 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Cette interface ne détermine pas si la réception est actuellement arrêtée, c'est-à-dire qu'elle autorise l'arrêt répété de la réception sans renvoyer d'erreur
 * @remarks L'appel de cette interface arrête seulement de recevoir le codage de données d'origine, le tampon de flux de code ne sera pas éliminé
 *
 * @attention au cas o ù Channel Non créé ， Manqué 
 * @attention au cas o ù Channel Non enregistré pour Group， Manqué 
 */
int IMP_Encoder_StopRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_Query (int encChn, IMPEncoderCHNStat * stat)
 *
 * Code de requête Channel statut 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] codage statistique État de la voie
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks non
 *
 * @attention non 
 */
int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat);

/**
 * @fn int IMP_Encoder_GetStream (int encChn, IMPEncoderStream * stream, bool blockFlag)
 *
 * Obtenez le flux codé 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pointeur de structure de flux de flux
 * @param[in] Si blockFlag est obtenu en mode bloquant, 0: non bloquant, 1: bloquant
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Obtenez les données d'une image de flux à la fois
 * @remarks Si l'utilisateur n'obtient pas le flux de code pendant une longue période, le tampon de flux de code sera plein. 
 * L'image reçue est perdue , Jusqu'à ce que l'utilisateur reçoive le flux de code , Il y a donc suffisamment de tampon de flux de code à utiliser pour l'encodage , Commencez simplement à coder. 
 * L'appel d'interface pour obtenir le flux de code et l'appel d'interface pour libérer le flux de code apparaissent par paires , Et publiez le flux dès que possible , Empêcher l'acquisition du flux de code en raison du mode utilisateur , Rel une chez pas 
 * Flux de code causé dans le temps buffer complet , Arrêtez de coder. 
 * @remarks Pour un flux de type H264, une trame de flux peut être obtenue avec succès en un seul appel, et cette trame de flux peut contenir plusieurs paquets.
 * @remarks Pour un flux de type JPEG, une trame de flux est obtenue avec succès en un seul appel. Cette trame de flux ne contient qu'un seul paquet, et cette trame contient les informations complètes du fichier image JPEG.
 *
 * Exemple: 
 * @code 
 * int ret;
 * ret = IMP_Encoder_PollingStream(ENC_H264_CHANNEL, 1000); //Polling Flux Buffer， En attente de disponibilité 
 * if (ret < 0) {
 * printf("Polling stream timeout\n");
 * return -1;
 * }
 *
 * IMPEncoderStream stream;
 * ret = IMP_Encoder_GetStream(ENC_H264_CHANNEL, &stream, 1); // Obtenez un flux d'images ， Méthode de blocage 
 * if (ret < 0) {
 * printf("Get Stream failed\n");
 * return -1;
 * }
 *
 * int i, nr_pack = stream.packCount;
 * for (i = 0; i < nr_pack; i++) { // Enregistrez chaque paquet de cette trame de flux de code 
 * ret = write(stream_fd, (void *)stream.pack[i].virAddr,
 * stream.pack[i].length);
 * if (ret != stream.pack[i].length) {
 * printf("stream write error:%s\n", strerror(errno));
 * return -1;
 * }
 * }
 * @endcode 
 *
 * @attention Si pstStream est NULL, il renvoie un échec;
 * @attention Si le canal n'est pas créé, il renvoie un échec;
 */
int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag);

/**
 * @fn int IMP_Encoder_ReleaseStream (int encChn, IMPEncoderStream * stream)
 *
 * Libérez le cache du flux de code 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream Pointeur de structure de flux 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Cette interface doit être associée à IMP_Encoder_GetStream, 
 * Après avoir obtenu le flux de code, l'utilisateur doit libérer le cache de flux de code obtenu à temps ， Sinon, cela peut provoquer un flux de bits buffer complet ， Affecte l'encodage de l'encodeur. \n
 * Et l'utilisateur doit appuyer sur 
 * Libérez le cache de flux de code qui a été acquis dans l'ordre de libération; 
 * @remarks Une fois que le canal de codage est désenregistré, tous les paquets de flux de code non libérés sont invalides, et cette partie du tampon de flux de code non valide ne peut pas être utilisée ou libérée.
 *
 * @attention au cas o ù pstStream pour NULL, Puis renvoyez l'échec; 
 * @attention au cas o ù Channel Non créé ， Puis renvoyez l'échec; 
 * @attention La libération du flux de code non valide renverra un échec.
 */
int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream);

/**
 * @fn int IMP_Encoder_PollingStream (int encChn, uint32_t timeoutMsec)
 *
 * Polling Tampon de flux 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] timeoutMsec timeout timeout, unité: millisecondes
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Vous pouvez utiliser cette API pour interroger avant d'obtenir le flux de code, et la fonction retourne lorsque le tampon de flux de code n'est pas vide ou lorsqu'il expire.
 *
 * @attention non 
 */
int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Encoder_SetMaxStreamCnt (int encChn, int nrMaxStream)
 *
 * Définir le cache du flux de code Buffer Nombre 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] nrMaxStream bit stream Numéro de tampon, plage de valeurs: [1, @ref NR_MAX_ENC_CHN_STREAM]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Étant donné que le nombre de tampons de flux de code est fixe lors de la création du canal, cette API doit être appelée avant la création du canal.
 * @remarks Si vous n'appelez pas cette API pour définir le nombre de tampons de flux avant la création du canal, le nombre par défaut de canaux H264 est 5 et le nombre par défaut de canaux JPEG est 1.
 *
 * @attention non 
 */
int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream);

/**
 * @fn int IMP_Encoder_GetMaxStreamCnt (int encChn, int * nrMaxStream)
 *
 * Obtenir le flux de code Buffer numéro 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] Flux de code nrMaxStream Pointeur de variable de numéro de tampon
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks non 
 *
 * @attention non 
 */
int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream);

/**
 * @fn int IMP_Encoder_RequestIDR (int encChn)
 *
 * demander IDR Cadre 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Après avoir appelé cette API, le codage de trame IDR sera appliqué dans la trame de codage la plus récente.
 *
 * @attention non 
 */
int IMP_Encoder_RequestIDR(int encChn);

/**
 * @fn int IMP_Encoder_FlushStream (int encChn)
 *
 * Brosser l'ancien flux de code restant dans l'encodeur ， et IDR Encodage de début de trame 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appeler ça API Arrière ， S'appliquera dans la trame d'encodage la plus proche IDR Encodage de trame. 
 *
 * @attention non 
 */
int IMP_Encoder_FlushStream(int encChn);

/**
 * @fn int IMP_Encoder_SetChnColor2Grey (int encChn, const IMPEncoderColor2GreyCfg * pstColor2Grey).
 *
 * Réglez la couleur sur la fonction grise 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] Paramètres de la fonction pstColor2Grey couleur à gris
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelez cette API pour définir la fonction de couleur à gris du canal, qui prendra effet dans la prochaine trame IDR ou P.
 * Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention non 
 */
int IMP_Encoder_SetChnColor2Grey(int encChn, const IMPEncoderColor2GreyCfg *pstColor2Grey);

/**
 * @fn int IMP_Encoder_GetChnColor2Grey (int encChn, IMPEncoderColor2GreyCfg * pstColor2Grey).
 *
 * Obtenir la couleur des attributs de fonction gris 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstColor2Grey Paramètres de la fonction de la couleur au gris 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API obtiendra les propriétés de la fonction de couleur à gris du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention Cette fonction n'a aucune signification pour les canaux JPEG.
 */
int IMP_Encoder_GetChnColor2Grey(int encChn, IMPEncoderColor2GreyCfg *pstColor2Grey);

/**
 * @fn int IMP_Encoder_SetChnRcAttr (int encChn, const IMPEncoderRcAttr * pstRcCfg).
 *
 * Définir les propriétés du contrôle de débit 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] Paramètre d'attribut de contrôle de débit pstRcCfg
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API définira les propriétés de contrôle de débit du canal et le prochain IDR prendra effet. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention Actuellement, le contrôle de débit prend en charge ENC_RC_MODE_H264FIXQP et ENC_RC_MODE_H264CBR.
 * ENC_RC_MODE_H264FIXQP Configuration du support qp，ENC_RC_MODE_H264CBR Configuration du support outBitRate . 
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_SetChnRcAttr(int encChn, const IMPEncoderRcAttr *pstRcCfg);

/**
 * @fn int IMP_Encoder_GetChnRcAttr (int encChn, IMPEncoderRcAttr * pstRcCfg).
 *
 * Obtenir les propriétés du contrôle de débit 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstRcCfg Paramètres d'attribut de contrôle de débit 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API obtiendra les propriétés de contrôle de débit du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_GetChnRcAttr(int encChn, IMPEncoderRcAttr *pstRcCfg);

/**
 * @fn int IMP_Encoder_SetChnFrmRate (int encChn, const IMPEncoderFrmRate * pstFps)
 *
 * Définir dynamiquement les propriétés du contrôle de la fréquence d'images 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] Paramètre d'attribut de contrôle de fréquence d'images pstFpsCfg
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API réinitialisera l'attribut de fréquence d'images de l'encodeur. L'attribut de fréquence d'images prendra effet dans le prochain GOP avec un délai maximal de 1 seconde. L'appel de cette API nécessite que le canal existe déjà.
 * @remarks Si vous appelez la fonction IMP_FrameSource_SetChnFPS () pour modifier dynamiquement la fréquence d'images du système, vous devez appeler cette fonction pour modifier la fréquence d'images de l'encodeur afin de terminer la configuration des paramètres correcte.
 *
 * @attention non.
 */
int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_GetChnFrmRate (int encChn, IMPEncoderFrmRate * pstFps)
 *
 * Obtenir les propriétés du contrôle de la fréquence d'images 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg Paramètres d'attribut de contrôle de la fréquence d'images 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API obtiendra les propriétés de contrôle de la fréquence d'images du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_SetChnROI (int encChn, const IMPEncoderROICfg * pstVencRoiCfg)
 *
 * Configurer la cha je ne ROI Les attributs 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] Paramètres d'attribut pstFpsCfg ROI
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API définira l'attribut ROI du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention non. 
 */
int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROICfg *pstVencRoiCfg);

/**
 * @fn int IMP_Encoder_GetChnROI (int encChn, IMPEncoderROICfg * pstVencRoiCfg)
 *
 * Obtenir la cha je ne ROI Les attributs 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg ROI Paramètre d'attribut 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API obtiendra l'attribut ROI du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROICfg *pstVencRoiCfg);

/**
 * @fn int IMP_Encoder_GetGOPSize (int encChn, IMPEncoderGOPSizeCfg * pstGOPSizeCfg)
 *
 * Obtenir la cha je ne GOP Les attributs 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] Paramètre d'attribut pstGOPSizeCfg GOPSize
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API obtiendra la propriété GOPSize du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetGOPSize (int encChn, const IMPEncoderGOPSizeCfg * pstGOPSizeCfg)
 *
 * Configurer la cha je ne GOP Les attributs 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] Paramètre d'attribut pstGOPSizeCfg GOP
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API définira la propriété GOPSize du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention non. 
 */
int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetChnH264Demask (int encChn, const IMPEncoderAttrH264Demask * pdemaskAttr)
 *
 * Définir les propriétés de dématriçage des canaux 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] Paramètre d'attribut pdemaskAttr Demosaic
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API définira la propriété de dématriçage du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention non. 
 */
int IMP_Encoder_SetChnH264Demask(int encChn, const IMPEncoderAttrH264Demask *pdemaskAttr);

/**
 * @fn int IMP_Encoder_GetChnH264Demask (int encChn, IMPEncoderAttrH264Demask * pdemaskAttr)
 *
 * Obtenir les propriétés de dématriçage des canaux 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdemaskAttr Paramètres de propriété de dématriçage 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API permet d'obtenir les propriétés de dématriçage du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention non. 
 */
int IMP_Encoder_GetChnH264Demask(int encChn, IMPEncoderAttrH264Demask *pdemaskAttr);

/**
 * @fn int IMP_Encoder_SetChnH264FrmUsedMode (int encChn, const IMPEncoderAttrH264FrmUsed * pfrmUsedAttr)
 *
 * Définir l'attribut du mode d'utilisation de la trame d'entrée du canal 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] Paramètre d'attribut de mode d'utilisation du cadre d'entrée pfrmUsedAttr
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API définira les propriétés du mode d'utilisation du cadre d'entrée du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention non. 
 */
int IMP_Encoder_SetChnH264FrmUsedMode(int encChn, const IMPEncoderAttrH264FrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_GetChnH264FrmUsedMode (int encChn, IMPEncoderAttrH264FrmUsed * pfrmUsedAttr)
 *
 * Obtenir l'attribut du mode d'utilisation de la trame d'entrée du canal 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr Paramètre d'attribut du mode d'utilisation du cadre d'entrée 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API obtiendra les propriétés du mode d'utilisation du cadre d'entrée du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention non. 
 */
int IMP_Encoder_GetChnH264FrmUsedMode(int encChn, IMPEncoderAttrH264FrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_SetChnH264Denoise (int encChn, const IMPEncoderAttrH264Denoise * pdenoiseAttr)
 *
 * Définir les propriétés de réduction du bruit de canal 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] Paramètres d'attribut de débruitage pdenoiseAttr
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API définira les propriétés de réduction du bruit du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention non. 
 */
int IMP_Encoder_SetChnH264Denoise(int encChn, const IMPEncoderAttrH264Denoise *pdenoiseAttr);

/**
 * @fn int IMP_Encoder_GetChnH264Denoise (int encChn, IMPEncoderAttrH264Denoise * pdenoiseAttr)
 *
 * Obtenir les propriétés de débruitage du canal 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdenoiseAttr Paramètres d'attribut de débruitage 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API obtiendra les propriétés de réduction du bruit du canal. L'appel de cette API nécessite que le canal existe déjà.
 *
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_GetChnH264Denoise(int encChn, IMPEncoderAttrH264Denoise *pdenoiseAttr);

/**
 * @fn int IMP_Encoder_InsertUserData (int encChn, void * userData, uint32_t userDataLen)
 *
 * Insérer les données utilisateur 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pointeur de données utilisateur userData
 * @param[in] userDataLen Longueur des données utilisateur, plage de valeurs: (0, 1024), en octets
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks L'appel de cette API nécessite que le canal existe déjà
 * @remarks Si le canal n'est pas créé, il renvoie un échec
 * @remarks Si userData est vide ou userDataLen vaut 0, renvoie un échec
 * @remarks Insérer les données utilisateur, prend uniquement en charge le protocole de codage H.264
 * @remarks Le canal de protocole H.264 alloue au plus 2 espaces mémoire pour la mise en mémoire tampon des données utilisateur, et la taille de chaque donnée utilisateur ne dépasse pas 1 Ko.
 * Si les données insérées par l'utilisateur sont redondantes 2 Pièce , Ou l'élément de données utilisateur inséré est supérieur à 1k byte Temps , Cette interface renverra une erreur. 
 * @remarks Chaque élément de données utilisateur est inséré sous la forme d'un paquet SEI avant le dernier paquet de flux de code image. 
 * H.264 L'espace mémoire pour la mise en mémoire tampon de cette donnée utilisateur dans le canal est effacé , Utilisé pour stocker de nouvelles données utilisateur 
 *
 * @attention non. 
 */
int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen);

/**
 * @fn int IMP_Encoder_SetFisheyeEnableStatus (int encChn, int activer)
 *
 * Installation Ingenic L'état activé de l'algorithme de correction fisheye fourni 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] activer 0: désactiver (par défaut), 1: activer
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Étant donné que l'état d'activation de l'algorithme de correction fisheye est fixé lors de la création du canal, cette API doit être appelée avant la création du canal.
 * @remarks Si cette API n'est pas appelée pour définir l'état d'activation de l'algorithme de correction fisheye fourni par Ingenic avant la création du canal, elle est désactivée par défaut, c'est-à-dire que l'algorithme de correction fisheye fourni par Ingenic ne peut pas être utilisé.
 * @remarks Cette API n'est disponible que pour H264
 *
 * @attention non 
 */
int IMP_Encoder_SetFisheyeEnableStatus(int encChn, int enable);

/**
 * @fn int IMP_Encoder_GetFisheyeEnableStatus (int encChn, int * enable)
 *
 * Obtenir Ingenic L'état activé de l'algorithme de correction fisheye fourni 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] enable renvoie l'état activé de l'algorithme de correction fisheye fourni par Ingenic, 0: non activé, 1: activé
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks ce API s'applique uniquement à H264
 *
 * @attention non 
 */
int IMP_Encoder_GetFisheyeEnableStatus(int encChn, int *enable);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_ENCODER_H__ */
