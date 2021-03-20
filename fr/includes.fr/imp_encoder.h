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
 * @ingroup imp
 * @brief Encodage vidéo ( H264, JPEG ) Module ， Contient la gestion des canaux d'encodage ， Réglage des paramètres d'encodage et autres fonctions 
 * @section enc_struct 1 Structure du module 
 * Encoder La structure interne du module est la suivante: 
 * @image html encoder_struct.jpg
 * Comme le montre la figure ， Le module de codage se compose de plusieurs Group Composition (en T15 Soutenir deux Group ) ， Chaque Group Codé par Channel composition. 
 * Chaque code Channel Avec un tampon de flux de code de sortie ， Ce tampon se compose de plusieurs buffer composition. 
 * @section enc_channel 2 codage Channel
 * Un code Channel Peut compléter le codage d'un protocole. Group Peut en ajouter un H264 codage Channel Avec un JPEG codage Channel . 
 * @section enc_rc 3 Contrôle de taux 
 * @subsection enc_cbr 3.1 CBR
 * CBR ( Constent Bit Rate ) Débit constant ， C'est-à-dire que le débit de code est constant pendant la durée des statistiques de débit de code. 
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
	ENC_RC_MODE_FIXQP = 0,	/**< Fixqp mode */
	ENC_RC_MODE_CBR = 1,	/**< CBR mode */
	ENC_RC_MODE_VBR = 2,	/**< VBR mode */
	ENC_RC_MODE_SMART = 3,	/**< Smart mode */
	ENC_RC_MODE_INV = 4,	/**< INV mode */
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
	uint32_t			qp;				/**< Niveau du cadre Qp évaluer */
} IMPEncoderAttrH264FixQP;

/**
 * définition H.264 codage Channel CBR Structure de la propriété 
 */
typedef struct {
	uint32_t			maxQp;			/**< L'encodeur prend en charge la plus grande image QP */
	uint32_t			minQp;			/**< L'encodeur prend en charge la plus petite image QP */
	uint32_t			outBitRate;		/**< Débit binaire de sortie du codeur , À kbps En tant qu'unité */
	int					iBiasLvl;		/**< Ajustement I Cadre QP Ajuster I La qualité d'image de la trame et sa taille de flux binaire , gamme :[-3,3] */
	uint32_t			frmQPStep;		/**< Intertrame QP Changer l'étape */
	uint32_t			gopQPStep;		/**< GOP compris entre QP Changer l'étape */
	bool				adaptiveMode;	/**< Mode adaptatif */
	bool				gopRelation;	/**< GOP Est-ce lié */
} IMPEncoderAttrH264CBR;

/**
 * définition H.264 codage Channel VBR Structure de la propriété 
 */
typedef struct {
	uint32_t			maxQp;			/**< L'encodeur prend en charge la plus grande image QP */
	uint32_t			minQp;			/**< L'encodeur prend en charge la plus petite image QP */
	uint32_t			staticTime;		/**< Temps de statistiques de débit binaire , En secondes */
	uint32_t			maxBitRate;		/**< Débit binaire maximal de la sortie du codeur , À kbps En tant qu'unité */
 int32_t iBiasLvl; /**< Ajustement I Cadre QP Ajuster I La qualité d'image de la trame et sa taille de flux binaire , gamme :[-3,3] */
	uint32_t			changePos;		/**< VBR Commencez à vous ajuster Qp Le rapport entre le débit de code à ce moment et le débit de code maximal , Gammes :[50, 100] */
 uint32_t qualityLvl; /**< Qualité vidéo minimale , gamme [0-7], Plus la valeur est basse, plus la qualité d'image est élevée , Mais plus le flux de code est volumineux , minBitRate = maxBitRate * quality[qualityLvl], parmi eux quality[] = {0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1} */
	uint32_t			frmQPStep;		/**< Intertrame QP Changer l'étape */
	uint32_t			gopQPStep;		/**< GOP compris entre QP Changer l'étape */
	bool				gopRelation;	/**< gop Est-ce lié */
} IMPEncoderAttrH264VBR;

/**
 * définition H.264 codage Channel Smart Structure de la propriété 
 */
typedef struct {
	uint32_t			maxQp;			/**< L'encodeur prend en charge la plus grande image QP */
	uint32_t			minQp;			/**< L'encodeur prend en charge la plus petite image QP */
	uint32_t			staticTime;		/**< Temps de statistiques de débit binaire , En secondes */
	uint32_t			maxBitRate;		/**< Débit binaire maximal de la sortie du codeur , À kbps En tant qu'unité */
 int32_t iBiasLvl; /**< Ajustement I Cadre QP Ajuster I La qualité d'image de la trame et sa taille de flux binaire , gamme :[-3,3] */
	uint32_t			changePos;		/**< Commencez à vous ajuster Qp Le rapport entre le débit de code à ce moment et le débit de code maximal , Gammes :[50, 100] */
 uint32_t qualityLvl; /**< Qualité vidéo minimale , gamme [0-7], Plus la valeur est basse, plus la qualité d'image est élevée , Mais plus le flux de code est volumineux . minBitRate = maxBitRate * quality[qualityLvl], parmi eux quality[] = {0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1} */
	uint32_t			frmQPStep;		/**< Intertrame QP Changer l'étape */
	uint32_t			gopQPStep;		/**< gop compris entre QP Changer l'étape */
	bool				gopRelation;	/**< gop Est-ce lié */
} IMPEncoderAttrH264Smart;

/**
 * définition H.264 codage Channel Propriétés de dématriçage 
 */
typedef struct {
	bool				enable;			/**< Activer ou non la fonction de dématriçage */
	bool				isAutoMode;		/**< Activer le mode de dématriçage automatique ， 0: Manuel ，1 :automatique */
	int					demaskCnt;		/**< Paramètre de temps de maintien du dématriçage */
	int					demaskThresd;	/**< Seuil de dématriçage */
} IMPEncoderAttrDemask;

/**
 * définition H.264 codage Channel Propriétés de débruitage , Ne peut pas être modifié une fois activé , Mais le type de débruitage peut être changé dynamiquement ;
 */
typedef struct {
	bool				enable;			/**< Activer ou non la fonction de débruitage , 0: ignorer ,1: Réduction du bruit en fonction du type de trame actuel , Perte maximale d'informations ,2: presse I Débruitage du cadre ， Perte d'informations modérée */
	int					dnType;			/**< Type de débruitage ,0: ignorer ， Pas de réduction du bruit ,1: utilisation IP Réduction du bruit du type de cadre ,2: utilisation I Réduction du bruit du type de cadre */
	int					dnIQp;			/**< Débruitage I Paramètre de quantification de trame */
	int					dnPQp;			/**< Débruitage P Paramètre de quantification de trame */
} IMPEncoderAttrDenoise;

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
} IMPEncoderAttrFrmUsed;

typedef enum {
	IMP_Encoder_STYPE_N1X			= 0,	/**< 1 Référence de cadre à double saut */
	IMP_Encoder_STYPE_N2X			= 1,	/**< 2 Référence de cadre à double saut */
	IMP_Encoder_STYPE_N4X			= 2,	/**< 4 Référence de cadre à double saut */
	IMP_Encoder_STYPE_HN1_FALSE	 = 3,	/**< Mode de saut de trame avancé: N1 Saut de cadre ouvert */
	IMP_Encoder_STYPE_HN1_TRUE		= 4,	/**< Mode de saut de trame avancé: N1 Saut de cadre fermé */
	IMP_Encoder_STYPE_H1M_FALSE	 = 5,	/**< Mode de saut de trame avancé: 1M Saut de cadre ouvert */
	IMP_Encoder_STYPE_H1M_TRUE		= 6,	/**< Mode de saut de trame avancé: 1M Saut de cadre fermé */
} IMPSkipType;

typedef enum {
	IMP_Encoder_FSTYPE_IDR		= 0,	/**< Images clés en mode de saut d'image avancé */
	IMP_Encoder_FSTYPE_LBASE	= 1,	/**< Cadre de base à long terme en mode de saut de cadre avancé */
	IMP_Encoder_FSTYPE_SBASE	= 2,	/**< Cadre de base à court terme en mode de saut de cadre avancé */
	IMP_Encoder_FSTYPE_ENHANCE	= 3,	/**< Cadre amélioré en mode de saut de cadre avancé */
} IMPRefType;

/**
 * définition H264 Structure de type de saut de trame avancée 
 */
typedef struct {
	IMPSkipType	 skipType;	/**< Type de saut de trame */
	int				m;				/**< Intervalle d'image amélioré */
	int				n;				/**< Intervalle de trame de référence */
	int				maxSameSceneCnt;/**< Occupé par la même scène gop Nombre maximum , Seulement pour H1M Skip Type valide , Si la valeur n'est pas supérieure à 0, alors m La valeur ne fonctionne pas */
	int				bEnableScenecut;/**< Activer ou non la commutation de scène , Seulement pour H1M Skip Type valide */
	int				bBlackEnhance;	/**< Indique si la sortie d'image améliorée doit être effectuée sous la forme d'un flux nul */
} IMPEncoderAttrHSkip;

/**
 * définition H264 Structure d'initialisation avancée du type de saut de trame 
 */
typedef struct {
	IMPEncoderAttrHSkip	hSkipAttr;	/**< Propriétés avancées de saut de trame */
	IMPSkipType			maxHSkipType;/**< Type de saut de trame maximum à utiliser */
} IMPEncoderAttrInitHSkip;

/**
 * Code de définition Channel Attributs du mode de contrôle du débit du contrôleur de débit 
 */
typedef struct {
	IMPEncoderRcMode rcMode;						/**< RC mode */
	union {
		IMPEncoderAttrH264FixQP	 attrH264FixQp;		/**< H.264 Codage de protocole Channel Fixqp Attributs de mode */
		IMPEncoderAttrH264CBR	 attrH264Cbr;		/**< H.264 Codage de protocole Channel Cbr Attributs de mode */
		IMPEncoderAttrH264VBR	 attrH264Vbr;		/**< H.264 Codage de protocole Channel Vbr Attributs de mode */
		IMPEncoderAttrH264Smart	 attrH264Smart;		/**< H.264 Codage de protocole Channel Smart Attributs de mode */
	};
} IMPEncoderAttrRcMode;

/**
 * Code de définition Channel Propriétés du contrôleur de taux 
 */
typedef struct {
 IMPEncoderFrmRate	 outFrmRate;		/**< codage Channel La fréquence d'images de sortie (la fréquence d'images de sortie ne peut pas être supérieure à la fréquence d'images d'entrée) */
 uint32_t			 maxGop;			/**< gop évaluer ， Doit être un multiple entier de la fréquence d'images */
 IMPEncoderAttrRcMode attrRcMode; /**< Attributs du mode de contrôle de débit */
	IMPEncoderAttrFrmUsed	 attrFrmUsed;	/**< Attributs du mode d'utilisation du cadre d'entrée */
	IMPEncoderAttrDemask	 attrDemask;		/**< Propriétés de dématriçage */
	IMPEncoderAttrDenoise	 attrDenoise;	/**< Propriétés de débruitage */
	IMPEncoderAttrInitHSkip	 attrHSkip;		/**< Propriétés d'initialisation avancées de saut de trame */
} IMPEncoderRcAttr;

/**
 * H264 Flux NALU Types de 
 */
typedef enum {
	IMP_H264_NAL_UNKNOWN		= 0,	/**< non spécifié */
	IMP_H264_NAL_SLICE		 = 1,	/**< Un non IDR Bande de codage d'image */
	IMP_H264_NAL_SLICE_DPA	 = 2,	/**< Bloc de segmentation de données de bande codé A */
	IMP_H264_NAL_SLICE_DPB	 = 3,	/**< Bloc de segmentation de données de bande codé B */
	IMP_H264_NAL_SLICE_DPC	 = 4,	/**< Bloc de segmentation de données de bande codé C */
	IMP_H264_NAL_SLICE_IDR	 = 5,	/**< IDR Bande de codage d'image */
	IMP_H264_NAL_SEI			= 6,	/**< Informations sur les améliorations auxiliaires (SEI) */
	IMP_H264_NAL_SPS			= 7,	/**< Jeu de paramètres de séquence */
	IMP_H264_NAL_PPS			= 8,	/**< Jeu de paramètres d'image */
	IMP_H264_NAL_AUD			= 9,	/**< Séparateur d'unité d'accès */
	IMP_H264_NAL_FILLER		 = 12,	/**< Entrée de données */
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
		IMPRefType refType;
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
uint32_t xW;
uint32_t xH;
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
 * Définir le mode de traitement des super trames dans le contrôle de débit 
 */
typedef enum {
 IMP_RC_SUPERFRM_NONE = 0, /**< Pas de stratégie particulière , Etre prêt */
 IMP_RC_SUPERFRM_DISCARD = 1, /**< Jeter les cadres jumbo , pas de support , Il appartient à l'appelant de décider de rejeter ou non */
 IMP_RC_SUPERFRM_REENCODE = 2, /**< Refaire des cadres surdimensionnés , Etre prêt */
 IMP_RC_SUPERFRM_BUTT = 3,
} IMPEncoderSuperFrmMode;

/**
 * Énumération des priorités de contrôle de débit 
 */
typedef enum {
 IMP_RC_PRIORITY_RDO = 0, /**< Débit binaire cible et équilibre de qualité */
 IMP_RC_PRIORITY_BITRATE_FIRST = 1, /**< Priorité du débit binaire cible */
 IMP_RC_PRIORITY_FRAMEBITS_FIRST = 2, /**< Priorité de seuil de trame Jumbo */
 IMP_RC_PRIORITY_BUTT = 3,
} IMPEncoderRcPriority;

/**
 * Paramètres de stratégie de traitement des trames Jumbo 
 */
typedef struct {
 IMPEncoderSuperFrmMode superFrmMode; /**< Mode de traitement des trames Jumbo , La valeur par défaut est SUPERFRM_REENCODE */
 uint32_t superIFrmBitsThr; /**< I Seuil de surdimensionnement du cadre , La valeur par défaut est w*h*3/2*8/ratio, ratio: La principale résolution est 6, La sous-résolution est 3 */
 uint32_t superPFrmBitsThr; /**< P Seuil de surdimensionnement du cadre , La valeur par défaut est I Seuil de surdimensionnement du cadre divisé par 1.4 */
 uint32_t superBFrmBitsThr; /**< B Seuil de surdimensionnement du cadre , La valeur par défaut est P Seuil de surdimensionnement du cadre divisé par 1.3, Pas actuellement pris en charge B Cadre */
 IMPEncoderRcPriority rcPriority; /**< Priorité de contrôle de débit , La valeur par défaut est IMP_RC_PRIORITY_RDO */
} IMPEncoderSuperFrmCfg;

/**
 * définition H.264 Transformation de canal de codage de protocole, structure de quantification 
 */
typedef struct {
 uint32_t intraTransMode; /**< Mode de transformation de l'interprédiction 0: Etre prêt 4x4,8x8 Transformer , high profile Etre prêt ; 1:4x4 Transformer , baseline, main, high profile Les deux soutiennent ; 2: 8x8 Transformer , high profile Etre prêt ; Actuellement, ne prend en charge que la configuration 1 */
 uint32_t interTransMode; /**< Mode de transformation de l'interprédiction 0: Etre prêt 4x4,8x8 Transformer , high profile Etre prêt ; 1:4x4 Transformer , baseline, main, high profile Les deux soutiennent ; 2: 8x8 Transformer , high profile Etre prêt ; Actuellement, ne prend en charge que la configuration 1 */
 bool bScalingListValid; /**< interScalingList8x8 [[[ intraScalingList8x8 Est-ce valable? , Seulement dans high profile Avoir du sens ; 0: invalide , 1: efficace ; Prend uniquement en charge la configuration 0 */
 uint8_t interScalingList8X8[64]; /**< Prédiction inter 8x8 Table de quantification , dans high profile sous , Les utilisateurs peuvent utiliser leur propre table de quantification , Garder , Hors service ; Gammes :[1, 255] */
 uint8_t intraScalingList8X8[64]; /**< Prédiction intra 8x8 Table de quantification , dans high profile sous , Les utilisateurs peuvent utiliser leur propre table de quantification , Garder , Hors service ; Gammes :[1, 255] */
 int chroma_qp_index_offset; /**< Pour une signification spécifique, veuillez vous référer à H.264 protocole , La valeur par défaut du système est 0; Gammes :[-12, 12] */
} IMPEncoderH264TransCfg;

/*
 MPEncoderJpegeQl* définition JPEG Codage de la structure des paramètres de la table de quantification 
 */
typedef struct {
 bool user_ql_en;/**< 0: Utiliser la table de quantification par défaut ; 1: Utiliser la table de quantification utilisateur */
 uint8_t qmem_table[256];/**< Table de quantification définie par l'utilisateur */
} IMPEncoderJpegeQl;
/**
 * @fn int IMP_Encoder_CreateGroup(int encGroup)
 *
 * Créer du code Group
 *
 * @param[in] encGroup Group numéro , Gammes :[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Tout le Group Prend en charge une seule résolution ， Différentes résolutions doivent recommencer Group . Group Soutenez tout le chemin en même temps H264 Et tout le chemin JPEG Se casser 
 *
 * @attention Si spécifié Group existe déjà ， Manqué 
 */
int IMP_Encoder_CreateGroup(int encGroup);

/**
 * @fn int IMP_Encoder_DestroyGroup(int encGroup)
 *
 * Détruisez le code Grouop.
 *
 * @param[in] encGroup Group numéro , Gammes :[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks détruire Group Temps ， Doit garantir Group Est vide ， C'est-à-dire sans aucun Channel dans Group Inscrivez-vous ， Ou inscrivez-vous à Group dans 
 * de Channel Annulé ， Sinon, il retourne échoué 
 *
 * @attention Détruire inexistant Group， Manqué 
 */
int IMP_Encoder_DestroyGroup(int encGroup);

/**
 * @fn int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr)
 *
 * Créer du code Channel
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr codage Channel Pointeur d'attribut 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks codage Channel L'attribut se compose de deux parties ， Attributs d'encodeur et attributs de contrôle de débit 
 * @remarks Les propriétés du codeur doivent d'abord sélectionner le protocole de codage ， Attribuez ensuite des valeurs aux attributs correspondant aux différents protocoles 
 */
int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr);

/**
 * @fn int IMP_Encoder_DestroyChn(int encChn)
 *
 * Détruisez le code Channel
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @attention Détruire inexistant Channel， Manqué 
 * @attention Doit garantir avant la destruction Channel Ont été de Group Anti-enregistrement ， Sinon, il retourne échoué 
 */
int IMP_Encoder_DestroyChn(int encChn);

/**
 * @fn int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr * const attr)
 *
 * Obtenez le code Channel Attribut de 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr codage Channel Les attributs 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 */
int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr * const attr);

/**
 * @fn int IMP_Encoder_RegisterChn(int encGroup, int encChn)
 *
 * Code d'enregistrement Channel À Group
 *
 * @param[in] encGroup codage Group numéro , Gammes : [0, @ref NR_MAX_ENC_GROUPS - 1]
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @attention L'enregistrement n'existe pas Channel， Manqué 
 * @attention inscrit Channel À inexistant Group， Sinon, il retourne échoué 
 * @attention Même code Channel Un seul peut être enregistré Group， Si la Channel Déjà inscrit à un Group， Manqué 
 * @attention Si un Group Déjà enregistré ， Ensuite ceci Group Ça ne peut plus être Channel inscrit ， Sauf si la relation d'enregistrement précédente est annulée 
 */

int IMP_Encoder_RegisterChn(int encGroup, int encChn);
/**
 * @fn int IMP_Encoder_UnRegisterChn(int encChn)
 *
 * Code anti-enregistrement Channel À Group
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Channel Après la déconnexion ， codage Channel Sera réinitialisé ， codage Channel Flux buffer Sera vidé ， Si l'utilisateur utilise toujours 
 * Streams non diffusés à temps buffer， Ne sera pas garanti buffer Exactitude des données ， L'utilisateur peut utiliser IMP_Encoder_Query Interface à interroger 
 * code Channel Flux buffer statut ， Flux de confirmation buffer Désenregistrer après le flux de code dans Channel
 *
 * @attention Déconnexion non créée Channel， Manqué 
 * @attention Non enregistré Channel， Manqué 
 * @attention Si code Channel N'arrête pas de recevoir le codage d'image ， Manqué 
 */
int IMP_Encoder_UnRegisterChn(int encChn);

/**
 * @fn int IMP_Encoder_StartRecvPic(int encChn)
 *
 * Activer l'encodage Channel Recevoir l'image 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Activer l'encodage Channel L'encodage ne peut démarrer qu'après réception de l'image 
 *
 * @attention au cas où Channel Non créé ， Manqué 
 * @attention au cas où Channel Non enregistré pour Group， Manqué 
 */
int IMP_Encoder_StartRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_StopRecvPic(int encChn)
 *
 * Arrêter le codage Channel Recevoir l'image 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Cette interface ne détermine pas s'il faut arrêter de recevoir actuellement ， Autrement dit, il est permis d'arrêter de recevoir à plusieurs reprises sans renvoyer une erreur 
 * @remarks L'appel de cette interface arrête uniquement de recevoir le codage des données d'origine ， Flux buffer Ne sera pas éliminé 
 *
 * @attention au cas où Channel Non créé ， Manqué 
 * @attention au cas où Channel Non enregistré pour Group， Manqué 
 */
int IMP_Encoder_StopRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat)
 *
 * Code de requête Channel statut 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] stat codage Channel statut 
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
 * @fn int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag)
 *
 * Obtenez le flux codé 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream Pointeur de structure de flux 
 * @param[in] blockFlag Utiliser ou non la méthode de blocage pour obtenir ，0 : Non bloquant ，1 :bloquer 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Obtenez les données d'une image de flux à la fois 
 * @remarks Si l'utilisateur n'obtient pas le flux de code pendant une longue période , Le tampon de flux sera plein. Channel Si le tampon de flux est plein , Sera après 
 * L'image reçue est perdue , Jusqu'à ce que l'utilisateur reçoive le flux de code , Il y a donc suffisamment de tampon de flux de code à utiliser pour l'encodage , Commencez simplement à coder. 
 * L'appel d'interface pour obtenir le flux de code et l'appel d'interface pour libérer le flux de code apparaissent par paires , Et publiez le flux dès que possible , Empêcher l'acquisition du flux de code en raison du mode utilisateur , Rel une chez pas 
 * Flux de code causé dans le temps buffer complet , Arrêtez de coder. 
 * @remarks pour H264 Type de flux ， Obtenez une image de flux de code avec succès en un seul appel ， Cette trame de flux de code peut contenir plusieurs paquets. 
 * @remarks pour JPEG Type de flux ， Obtenez une image de flux de code avec succès en un seul appel ， Cette trame de flux de code ne contient qu'un seul paquet ， Ce cadre contient JPEG Les informations complètes du fichier image. 
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
 * @attention au cas où pstStream pour NULL, Puis renvoyez l'échec; 
 * @attention au cas où Channel Non créé ， Puis renvoyez l'échec; 
 */
int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag);

/**
 * @fn int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream)
 *
 * Libérez le cache du flux de code 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream Pointeur de structure de flux 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Cette interface doit être IMP_Encoder_GetStream Jumeler et utiliser ，\n
 * Après avoir obtenu le flux de code, l'utilisateur doit libérer le cache de flux de code obtenu à temps ， Sinon, cela peut provoquer un flux de bits buffer complet ， Affecte l'encodage de l'encodeur. \n
 * Et l'utilisateur doit appuyer sur 
 * Libérez le cache de flux de code qui a été acquis dans l'ordre de libération; 
 * @remarks Codage Channel Après la désinscription ， Tous les paquets de flux non publiés ne sont pas valides ， Ce tampon de flux de code non valide ne peut plus être utilisé ou libéré. 
 *
 * @attention au cas où pstStream pour NULL, Puis renvoyez l'échec; 
 * @attention au cas où Channel Non créé ， Puis renvoyez l'échec; 
 * @attention La libération du flux de code non valide renverra un échec. 
 */
int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream);

/**
 * @fn int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec)
 *
 * Polling Tampon de flux 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] timeoutMsec temps supplémentaire ， Unité: millisecondes 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Vous pouvez l'utiliser avant d'obtenir le flux de code API monter Polling， La fonction retourne lorsque le tampon de flux de code n'est pas vide ou lorsqu'il expire. 
 *
 * @attention non 
 */
int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream)
 *
 * Définir le cache du flux de code Buffer Nombre 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] nrMaxStream Flux Buffer numéro , Gammes : [1, @ref NR_MAX_ENC_CHN_STREAM]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks En raison de la mise en cache du flux Buffer Le numéro est fixe lors de la création du canal ， Par conséquent API Il doit être appelé avant la création du canal. 
 * @remarks S'il n'est pas appelé avant la création du canal API Définir le cache du flux de code Buffer Nombre ， alors H264 Le nombre de canaux par défaut est 5，JPEG Le nombre de canaux par défaut est 1 . 
 *
 * @attention non 
 */
int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream);

/**
 * @fn int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream)
 *
 * Obtenir le flux de code Buffer numéro 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] nrMaxStream Flux Buffer Pointeur variable 
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
 * @fn int IMP_Encoder_RequestIDR(int encChn)
 *
 * demander IDR Cadre 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appeler ça API Arrière ， S'appliquera dans la trame d'encodage la plus récente IDR Encodage de trame. 
 *
 * @attention non 
 */
int IMP_Encoder_RequestIDR(int encChn);

/**
 * @fn int IMP_Encoder_FlushStream(int encChn)
 *
 * Brosser l'ancien flux de code restant dans l'encodeur ， et IDR Encodage de début de trame 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appeler ça API Arrière ， S'appliquera dans la trame d'encodage la plus récente IDR Encodage de trame. 
 *
 * @attention non 
 */
int IMP_Encoder_FlushStream(int encChn);

/**
 * @fn int IMP_Encoder_SetChnColor2Grey(int encChn, const IMPEncoderColor2GreyCfg *pstColor2Grey).
 *
 * Réglez la couleur sur la fonction grise 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstColor2Grey Paramètres de la fonction de la couleur au gris 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Réglez la couleur sur la fonction grise du canal ， Sur le prochain IDR ou P Le cadre prend effet. 
 * Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention non 
 */
int IMP_Encoder_SetChnColor2Grey(int encChn, const IMPEncoderColor2GreyCfg *pstColor2Grey);

/**
 * @fn int IMP_Encoder_GetChnColor2Grey(int encChn, IMPEncoderColor2GreyCfg *pstColor2Grey).
 *
 * Obtenir la couleur des attributs de fonction gris 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstColor2Grey Paramètres de la fonction de la couleur au gris 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Obtiendra les attributs de fonction de couleur à gris du canal ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_GetChnColor2Grey(int encChn, IMPEncoderColor2GreyCfg *pstColor2Grey);

/**
 * @fn int IMP_Encoder_SetChnAttrRcMode(int encChn, const IMPEncoderAttrRcMode *pstRcModeCfg).
 *
 * Définir les propriétés du mode de contrôle de débit 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstRcCfg Paramètres d'attribut du mode de contrôle de débit 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Définira les attributs du mode de contrôle de débit du canal ， Suivant IDR Prendre effet , Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention Actuellement ， Prise en charge du mode de contrôle de débit ENC_RC_MODE_FIXQP, ENC_RC_MODE_CBR, ENC_RC_MODE_VBR contre ENC_RC_MODE_SMART
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_SetChnAttrRcMode(int encChn, const IMPEncoderAttrRcMode *pstRcModeCfg);

/**
 * @fn int IMP_Encoder_GetChnAttrRcMode(int encChn, IMPEncoderAttrRcMode *pstRcModeCfg).
 *
 * Obtenir les attributs du mode de contrôle de débit 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstRcCfg Paramètres d'attribut du mode de contrôle de débit 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Obtenir les attributs du mode de contrôle de débit du canal ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_GetChnAttrRcMode(int encChn, IMPEncoderAttrRcMode *pstRcModeCfg);

/**
 * @fn int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps)
 *
 * Définir dynamiquement les propriétés du contrôle de la fréquence d'images 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg Paramètres d'attribut de contrôle de la fréquence d'images 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Réinitialise les propriétés de fréquence d'images de l'encodeur ， L'attribut de fréquence d'images est le suivant GOP Prendre effet ， Délai maximum 1 Prenez effet en quelques secondes ， Appelle ça API Besoin d'un canal existe déjà. 
 * @remarks Si vous appelez IMP_FrameSource_SetChnFPS() La fonction modifie dynamiquement la fréquence d'images du système ， Ensuite, vous devez appeler cette fonction pour modifier la fréquence d'images de l'encodeur ， Terminez la configuration correcte des paramètres. 
 *
 * @attention non. 
 */
int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps)
 *
 * Obtenir les propriétés du contrôle de la fréquence d'images 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg Paramètres d'attribut de contrôle de la fréquence d'images 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Obtiendra les propriétés de contrôle de la fréquence d'images du canal ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROICfg *pstVencRoiCfg)
 *
 * Configurer la cha je ne ROI Les attributs 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg ROI Paramètre d'attribut 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Configurera la cha je ne ROI Les attributs ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention non. 
 */
int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROICfg *pstVencRoiCfg);

/**
 * @fn int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROICfg *pstVencRoiCfg)
 *
 * Obtenir la cha je ne ROI Les attributs 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg ROI Paramètre d'attribut 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Obtiendra la cha je ne ROI Les attributs ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROICfg *pstVencRoiCfg);

/**
 * @fn int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 * Obtenir la cha je ne GOP Les attributs 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstGOPSizeCfg GOPSize Paramètre d'attribut 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Obtiendra la cha je ne GOPSize Les attributs ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 * Configurer la cha je ne GOP Les attributs 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstGOPSizeCfg GOP Paramètre d'attribut 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Configurera la cha je ne GOPSize Les attributs ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention non. 
 */
int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetChnDemask(int encChn, const IMPEncoderAttrDemask *pdemaskAttr)
 *
 * Définir les propriétés de dématriçage des canaux 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdemaskAttr Paramètres de propriété de dématriçage 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Définira les propriétés de dématriçage du canal ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention non. 
 */
int IMP_Encoder_SetChnDemask(int encChn, const IMPEncoderAttrDemask *pdemaskAttr);

/**
 * @fn int IMP_Encoder_GetChnDemask(int encChn, IMPEncoderAttrDemask *pdemaskAttr)
 *
 * Obtenir les propriétés de dématriçage des canaux 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdemaskAttr Paramètres de propriété de dématriçage 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Obtiendra les propriétés de dématriçage du canal ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention non. 
 */
int IMP_Encoder_GetChnDemask(int encChn, IMPEncoderAttrDemask *pdemaskAttr);

/**
 * @fn int IMP_Encoder_SetChnFrmUsedMode(int encChn, const IMPEncoderAttrFrmUsed *pfrmUsedAttr)
 *
 * Définir l'attribut du mode d'utilisation du cadre d'entrée du canal 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr Paramètre d'attribut du mode d'utilisation du cadre d'entrée 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Définira l'attribut de mode d'utilisation de la trame d'entrée du canal ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention non. 
 */
int IMP_Encoder_SetChnFrmUsedMode(int encChn, const IMPEncoderAttrFrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_GetChnFrmUsedMode(int encChn, IMPEncoderAttrFrmUsed *pfrmUsedAttr)
 *
 * Obtenir l'attribut du mode d'utilisation de la trame d'entrée du canal 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr Paramètre d'attribut du mode d'utilisation du cadre d'entrée 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Obtiendra l'attribut de mode d'utilisation de la trame d'entrée du canal ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention non. 
 */
int IMP_Encoder_GetChnFrmUsedMode(int encChn, IMPEncoderAttrFrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_SetChnDenoise(int encChn, const IMPEncoderAttrDenoise *pdenoiseAttr)
 *
 * Définir les propriétés de réduction du bruit de canal 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pdenoiseAttr Paramètres d'attribut de débruitage 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Définira les propriétés de débruitage du canal ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention non. 
 */
int IMP_Encoder_SetChnDenoise(int encChn, const IMPEncoderAttrDenoise *pdenoiseAttr);

/**
 * @fn int IMP_Encoder_GetChnDenoise(int encChn, IMPEncoderAttrDenoise *pdenoiseAttr)
 *
 * Obtenir les propriétés de débruitage du canal 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdenoiseAttr Paramètres d'attribut de débruitage 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Obtiendra les propriétés de débruitage du canal ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention Cette fonction JPEG La cha je ne n'a pas de sens. 
 */
int IMP_Encoder_GetChnDenoise(int encChn, IMPEncoderAttrDenoise *pdenoiseAttr);

/**
 * @fn int IMP_Encoder_SetChnHSkip(int encChn, const IMPEncoderAttrHSkip *phSkipAttr)
 *
 * Définir les propriétés avancées de saut de trame du canal 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] phSkipAttr Paramètres d'attribut de saut de trame avancés 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Les propriétés avancées de saut de trame du canal seront définies ， Appelle ça API Besoin d'un canal existe déjà. 
 * @remarks Si le type de saut de trame avancé défini lors de la création du canal est IMP_Encoder_STYPE_N1X À IMP_Encoder_STYPE_N2X l'un des ,
 * ce API Le type de saut de trame ne peut être défini que sur IMP_Encoder_STYPE_N1X ou IMP_Encoder_STYPE_N2X N'importe lequel des 
 * @remarks Si le type de saut de trame avancé défini lors de la création du canal est IMP_Encoder_STYPE_N4X À IMP_Encoder_STYPE_H1M_TRUE l'un des ，
 * Il peut être défini sur n'importe quel type de saut de trame avancé 
 *
 * @attention non. 
 */
int IMP_Encoder_SetChnHSkip(int encChn, const IMPEncoderAttrHSkip *phSkipAttr);

/**
 * @fn int IMP_Encoder_GetChnHSkip(int encChn, IMPEncoderAttrHSkip *phSkipAttr)
 *
 * Obtenez les propriétés avancées de saut de trame du canal 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] phSkipAttr Paramètres d'attribut de saut de trame avancés 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Obtenez les propriétés avancées de saut de trame du canal ， Appelle ça API Besoin d'un canal existe déjà. 
 */
int IMP_Encoder_GetChnHSkip(int encChn, IMPEncoderAttrHSkip *phSkipAttr);

/**
 * @fn int IMP_Encoder_SetChnHSkipBlackEnhance(int encChn, const int bBlackEnhance)
 *
 * Réglage du saut de trame avancé du canal bBlackEnhance Les attributs 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] bBlackEnhance Valeur logique ， correspondre IMPEncoderAttrHSkip dans bBlackEnhance évaluer 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Définira le saut de trame avancé du canal bBlackEnhance Les attributs ， Appelle ça API Besoin d'un canal existe déjà. 
 *
 * @attention non. 
 */
int IMP_Encoder_SetChnHSkipBlackEnhance(int encChn, const int bBlackEnhance);

/**
 * @fn int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen)
 *
 * Insérer les données utilisateur 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] userData Pointeur de données utilisateur 
 * @param[in] userDataLen Longueur des données utilisateur , Gammes :(0, 1024], À byte En tant qu'unité 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Le canal requis existe déjà 
 * @remarks Si le canal n'est pas créé , Manqué 
 * @remarks au cas où userData Vide ou userDataLen pour 0, Manqué 
 * @remarks Insérer les données utilisateur , Supporte uniquement H.264 Protocole d'encodage 
 * @remarks H.264 Attribution maximale des canaux de protocole 2 L'espace mémoire de bloc est utilisé pour mettre en cache les données utilisateur , Et la taille de chaque élément de données utilisateur ne dépasse pas 1k byte . 
 * Si les données insérées par l'utilisateur sont redondantes 2 Pièce , Ou l'élément de données utilisateur inséré est supérieur à 1k byte Temps , Cette interface renverra une erreur. 
 * @remarks Chaque élément de données utilisateur est SEI Le format du package est inséré avant le dernier package de flux d'images. ,
 * H.264 L'espace mémoire pour la mise en mémoire tampon de cette donnée utilisateur dans le canal est effacé , Utilisé pour stocker de nouvelles données utilisateur 
 *
 * @attention non. 
 */
int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen);

/**
 * @fn int IMP_Encoder_SetFisheyeEnableStatus(int encChn, int enable)
 *
 * Installation Ingenic L'état activé de l'algorithme de correction fisheye fourni 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] enable 0: Désactiver ( défaut ),1: Permettre 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Étant donné que l'état d'activation de l'algorithme de correction fisheye est fixé lors de la création du canal ， Par conséquent API Il doit être appelé avant la création du canal. 
 * @remarks S'il n'est pas appelé avant la création du canal API Installation Ingenic L'état activé de l'algorithme de correction fisheye fourni , N'est pas activé par défaut ， Autrement dit, l'algorithme de correction fisheye fourni par Ingenics ne peut pas être utilisé. 
 * @remarks ce API s'applique uniquement à H264
 *
 * @attention non 
 */
int IMP_Encoder_SetFisheyeEnableStatus(int encChn, int enable);

/**
 * @fn int IMP_Encoder_GetFisheyeEnableStatus(int encChn, int *enable)
 *
 * Obtenir Ingenic L'état activé de l'algorithme de correction fisheye fourni 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] enable Retour au set Ingenic L'état activé de l'algorithme de correction fisheye fourni ,0: Pas activé ,1: Activé 
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
 * @fn int IMP_Encoder_SetChangeRef(int encChn, int bEnable)
 *
 * Si le paramètre est autorisé à changer BASE État du mode de référence de trame 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] enable 0 : Aucun changement autorisé ，1， Autoriser le changement ( défaut )
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks ce API Doit être appelé après la création du canal d'encodage ， Après le réglage, l'encodage de l'image suivante prendra effet. 
 * @remarks ce API s'applique uniquement à H264 SMART Codage 
 *
 * @attention non 
 */
int IMP_Encoder_SetChangeRef(int encChn, int bEnable);

/**
 * @fn int IMP_Encoder_GetChangeRef(int encChn, int *bEnable)
 *
 * Obtenir la permission de changer BASE État du mode de référence de trame 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] enable Retourner s'il faut autoriser les modifications BASE État du mode de référence de trame ，0 : Aucun changement autorisé ，1， Autoriser le changement 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks ce API s'applique uniquement à H264
 *
 * @attention non 
 */
int IMP_Encoder_GetChangeRef(int encChn, int *bEnable);

/**
 * @fn int IMP_Encoder_SetMbRC(int encChn, int bEnable)
 *
 * Définir s'il faut ouvrir le niveau de bloc de macro qp contrôler 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] bEnable 0: Pas ouverte ( défaut ), 1: Allumer 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks ce API Doit être appelé après la création du canal d'encodage ， Après le réglage, l'encodage de l'image suivante prendra effet. 
 *
 * @attention non 
 */
int IMP_Encoder_SetMbRC(int encChn, int bEnable);

/**
 * @fn int IMP_Encoder_GetMbRC(int encChn, int *bEnable)
 *
 * Obtenir s'il faut ouvrir le niveau de bloc de macro qp État de contrôle 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] bEnable Retourne s'il faut ouvrir le niveau du bloc macro qp État de contrôle , 0: Pas ouverte , 1: Allumer 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks ce API s'applique uniquement à H264
 *
 * @attention non 
 */
int IMP_Encoder_GetMbRC(int encChn, int *bEnable);

/**
 * @fn int IMP_Encoder_SetSuperFrameCfg(int encChn, const IMPEncoderSuperFrmCfg *pstSuperFrmParam)
 *
 * Définir la configuration de trame jumbo d'encodage 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstSuperFrmParam Encodage de la configuration de trame jumbo 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Si le canal n'est pas créé , Manqué 
 * @remarks ce API s'applique uniquement à H264
 *
 * @attention non 
 */
int IMP_Encoder_SetSuperFrameCfg(int encChn, const IMPEncoderSuperFrmCfg *pstSuperFrmParam);

/**
 * @fn int IMP_Encoder_GetSuperFrameCfg(int encChn, IMPEncoderSuperFrmCfg *pstSuperFrmParam)
 *
 * Obtenez la configuration de trame jumbo d'encodage 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstSuperFrmParam Retour à l'encodage de la configuration des trames jumbo 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Si le canal n'est pas créé , Manqué 
 * @remarks ce API s'applique uniquement à H264
 *
 * @attention non 
 */
int IMP_Encoder_GetSuperFrameCfg(int encChn, IMPEncoderSuperFrmCfg *pstSuperFrmParam);

/**
 * @fn int IMP_Encoder_SetH264TransCfg(int encChn, const IMPEncoderH264TransCfg *pstH264TransCfg)
 *
 * Installation H.264 Les propriétés de transformation et de quantification du canal de codage du protocole 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstH264TransCfg H.264 Propriétés de transformation et de quantification du canal de codage de protocole 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Si le canal n'est pas créé , Manqué 
 * @remarks ce API s'applique uniquement à H264
 * @remarks Il est recommandé de créer un code channel après ，startRecvPic Avant d'appeler , Premier lors du réglage GetH264TransCfg， après SetH264TransCfg
 *
 * @attention non 
 */
int IMP_Encoder_SetH264TransCfg(int encChn, const IMPEncoderH264TransCfg *pstH264TransCfg);

/**
 * @fn int IMP_Encoder_GetH264TransCfg(int encChn, IMPEncoderH264TransCfg *pstH264TransCfg)
 *
 * Obtenir H.264 Propriétés de transformation et de quantification du canal de codage de protocole 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstH264TransCfg revenir H.264 Propriétés de transformation et de quantification du canal de codage de protocole 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Si le canal n'est pas créé , Manqué 
 * @remarks ce API s'applique uniquement à H264
 *
 * @attention non 
 */
int IMP_Encoder_GetH264TransCfg(int encChn, IMPEncoderH264TransCfg *pstH264TransCfg);

/**
 * @fn int IMP_Encoder_SetJpegeQl(int encChn, const IMPEncoderJpegeQl *pstJpegeQl)
 *
 * Installation JPEG Paramètres de configuration de la table de quantification du canal de codage du protocole 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstJpegeQl JPEG Paramètres de configuration de la table de quantification du canal de codage du protocole , avant que 128 Remplissez le tableau de quantification ， Arrière 128 Octets à remplir 0
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Si le canal n'est pas créé , Manqué 
 * @remarks ce API s'applique uniquement à JPEG
 *
 * @attention non 
 */
int IMP_Encoder_SetJpegeQl(int encChn, const IMPEncoderJpegeQl *pstJpegeQl);

/**
 * @fn int IMP_Encoder_GetJpegeQl(int encChn, IMPEncoderJpegeQl *pstJpegeQl)
 *
 * Obtenir JPEG Paramètres de configuration de la table de quantification du canal de codage du protocole 
 *
 * @param[in] encChn codage Channel numéro , Gammes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstJpegeQl revenir JPEG Paramètres de configuration de la table de quantification du canal de codage du protocole 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Si le canal n'est pas créé , Manqué 
 * @remarks ce API s'applique uniquement à JPEG
 *
 * @attention non 
 */
int IMP_Encoder_GetJpegeQl(int encChn, IMPEncoderJpegeQl *pstJpegeQl);


/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_ENCODER_H__ */
