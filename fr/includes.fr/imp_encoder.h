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
 * @brief  Encodage vidéo ( H264, JPEG ) Module ， Contient la gestion des canaux d'encodage ， Réglage des paramètres d'encodage et autres fonctions 
 * @section enc_struct 1  Structure du module 
 * Encoder La structure interne du module est la suivante: 
 * @image html encoder_struct.jpg
 *  Comme le montre la figure ， Le module de codage se compose de plusieurs Group Composition (en T15 Soutenir deux Group ) ， Chaque Group Codé par Channel composition. 
 *  Chaque code Channel Avec un tampon de flux de code de sortie ， Ce tampon se compose de plusieurs buffer Ce tampon se compose de plusieurs 
 * @section enc_channel 2  codage Channel
 *  Un code Channel Peut compléter le codage d'un protocole. Chaque Group Peut en ajouter un H264 Peut en ajouter un Channel Avec un JPEG Avec un Channel . 
 * @section enc_rc 3  Contrôle de taux 
 * @subsection enc_cbr 3.1 CBR
 * CBR ( Constent Bit Rate ) Débit constant ， C'est-à-dire que le taux de codage est constant pendant le temps de statistiques de taux. 
 *  À H.264  Codage comme exemple ， L'utilisateur peut définir maxQp，minQp，bitrate Attendre. 
 * maxQp，minQp  Utilisé pour contrôler la plage de qualité de l'image ， bitrate  Il est utilisé pour bloquer le débit de code moyen pendant le temps statistique. 
 *  Lorsque le débit de code est supérieur au débit de code constant ， image QP  Will progressivement maxQp  Ajustement ， Lorsque le taux de codage est bien inférieur au taux constant ， Lorsque le taux de codage est bien inférieur au taux constant QP  Lorsque le taux de codage est bien inférieur au taux constant minQp  Ajustement. 
 *  Lorsque l'image QP  atteindre maxQp  Temps ，QP  Serré au maximum ，bitrate  L'effet de serrage n'est pas valide ， Le taux de codage peut dépasser bitrate Le taux de codage peut dépasser 
 *  Le taux de codage peut dépasser QP  Le taux de codage peut dépasser minQp  Le taux de codage peut dépasser ，QP  Serré au minimum ， A ce moment, le taux de code de l'encodage a atteint la valeur maximale ， Et la qualité d'image est la meilleure. 
 * @subsection enc_FixQP 3.2 FixQP
 * Fix Qp  fixé Qp  évaluer. Pendant le temps de statistiques de débit binaire ， Encoder tous les macroblocs de l'image Qp  Même valeur ， Utiliser des images définies par l'utilisateur Qp évaluer. 
 * @{
 */

/**
 *  Code de définition Channel Mode contrôleur de débit 
 */
typedef enum {
	ENC_RC_MODE_H264FIXQP               = 0,	/**< H.264 Fixqp  Mode (support)  */
	ENC_RC_MODE_H264CBR                 = 1,	/**< H.264 CBR  Mode (support)  */
	ENC_RC_MODE_H264ABR                 = 2,	/**< H.264 ABR  mode  */
	ENC_RC_MODE_H264VBR                 = 3,	/**< H.264 VBR  mode  */
	ENC_RC_MODE_H264INV                 = 4,	/**< H.264 INV  mode  */
} IMPEncoderRcMode;

/**
 *  mode channel Structure de fréquence d'images ,frmRateNum avec frmRateDen Après avoir été divisé par le plus grand diviseur commun, le plus petit multiple commun entre les deux ne peut pas dépasser 64， Il est préférable d'être divisible par le plus grand diviseur commun avant de définir 
 */
typedef struct {
	uint32_t	frmRateNum;				/**<  Le nombre d'unités de temps en une seconde ,  En unités de temps. Le numérateur de la fréquence d'images  */
	uint32_t	frmRateDen;				/**<  Le nombre d'unités de temps dans une trame ,  En unités de temps. Le dénominateur de la fréquence d'images  */
} IMPEncoderFrmRate;

/**
 *  définition H.264 définition Channel Fixqp Structure de la propriété 
 */
typedef struct {
	uint32_t			maxGop;			/**< H.264 gop évaluer ， Doit être un multiple entier de la fréquence d'images  */
	IMPEncoderFrmRate	outFrmRate;		/**<  Doit être un multiple entier de la fréquence d'images Channel La fréquence d'images de sortie (la fréquence d'images de sortie ne peut pas être supérieure à la fréquence d'images d'entrée) */
	uint32_t			qp;				/**<  Niveau du cadre Qp Niveau du cadre  */
} IMPEncoderAttrH264FixQP;

/**
 *  Niveau du cadre H.264 Niveau du cadre Channel CBR Niveau du cadre 
 */
typedef struct {
	uint32_t			maxGop;			/**< H.264 gop Niveau du cadre ， Niveau du cadre  */
	IMPEncoderFrmRate	outFrmRate;		/**<  Niveau du cadre Channel Niveau du cadre */
	uint32_t			maxQp;			/**<  L'encodeur prend en charge la plus grande image QP */
	uint32_t			minQp;			/**<  L'encodeur prend en charge la plus petite image QP */
	uint32_t			outBitRate;		/**<  Débit binaire de sortie du codeur , Débit binaire de sortie du codeur kbps En tant qu'unité  */
	uint32_t			maxFPS;			/**<  Fréquence d'images maximale  */
	uint32_t			minFPS;			/**<  Fréquence d'images minimale  */
	int					IBiasLvl;		/**< I Poids du cadre ， Etre prêt (-3~3)，7  Niveaux  */
	uint32_t			FrmQPStep;		/**<  Intertrame QP Changer l'étape  */
	uint32_t			GOPQPStep;		/**< GOP compris entre QP compris entre  */
	bool				AdaptiveMode;	/**<  Mode adaptatif */
	bool				GOPRelation;	/**< GOP Est-ce lié  */
} IMPEncoderAttrH264CBR;

/**
 *  Est-ce lié H.264 Est-ce lié Channel VBR Est-ce lié 
 */
typedef struct {
	uint32_t			maxGop;			/**< H.264 gop Est-ce lié ， Est-ce lié  */
	IMPEncoderFrmRate	outFrmRate;		/**<  Est-ce lié Channel Est-ce lié */
	uint32_t			maxQp;			/**<  Est-ce lié QP */
	uint32_t			minQp;			/**<  Est-ce lié QP */
	uint32_t			staticTime;		/**<  Temps de statistiques de débit binaire , En secondes  */
	uint32_t			maxBitRate;		/**<  Débit binaire maximal de la sortie du codeur , Débit binaire maximal de la sortie du codeur kbps Débit binaire maximal de la sortie du codeur  */
	uint32_t			changePos;		/**< VBR  Commencez à vous ajuster  Qp  Le rapport entre le débit de code à ce moment et le débit de code maximal , Gammes :[50, 100] */
	uint32_t			FrmQPStep;		/**<  Gammes QP Gammes  */
	uint32_t			GOPQPStep;		/**< GOP Gammes QP Gammes  */
} IMPEncoderAttrH264VBR;

/**
 *  Gammes H.264 Gammes Channel Propriétés de dématriçage 
 */
typedef struct {
	bool				enable;			/**<  Activer ou non la fonction de dématriçage  */
	bool				isAutoMode;		/**<  Activer le mode de dématriçage automatique ， 0: Manuel ，1 :automatique  */
	int					demaskCnt;		/**<  Paramètre de temps de maintien du dématriçage  */
	int					demaskThresd;	/**<  Seuil de dématriçage  */
} IMPEncoderAttrH264Demask;

/**
 *  Seuil de dématriçage H.264 Seuil de dématriçage Channel Propriétés de débruitage , Ne peut pas être modifié une fois activé , Mais le type de débruitage peut être changé dynamiquement ;
 */
typedef struct {
	bool				enable;			/**<  Activer ou non la fonction de débruitage , 0: ignorer ,1: Réduction du bruit en fonction du type de trame actuel , Perte maximale d'informations ,2: presse I Débruitage du cadre ， Perte d'informations modérée  */
	int					dnType;			/**<  Type de débruitage ,0: Type de débruitage ， Pas de réduction du bruit ,1: utilisation IP Réduction du bruit du type de cadre ,2: Réduction du bruit du type de cadre I Réduction du bruit du type de cadre  */
	int					dnIQp;			/**<  Débruitage I Paramètre de quantification de trame  */
	int					dnPQp;			/**<  Paramètre de quantification de trame P Paramètre de quantification de trame  */
} IMPEncoderAttrH264Denoise;

/**
 *  Paramètre de quantification de trame H.264 Paramètre de quantification de trame Channel Mode d'utilisation du cadre d'entrée 
 */
typedef enum {
	ENC_FRM_BYPASS	= 0,		/**<  Mode d'utilisation complet séquentiel - Mode par défaut  */
	ENC_FRM_REUSED	= 1,		/**<  Réutiliser le mode de trame  */
	ENC_FRM_SKIP	= 2,		/**<  Mode drop frame  */
} EncFrmUsedMode;

/**
 *  Mode drop frame H.264 Mode drop frame Channel Attributs du mode d'utilisation du cadre d'entrée 
 */
typedef struct {
	bool				enable;			/**<  Activer ou non le mode d'utilisation du cadre d'entrée  */
	EncFrmUsedMode		frmUsedMode;	/**<  Activer ou non le mode d'utilisation du cadre d'entrée  */
	uint32_t			frmUsedTimes;	/**<  Intervalle d'image utilisé à chaque fois en mode image répétée ou en mode image perdue  */
} IMPEncoderAttrH264FrmUsed;

typedef enum {
	IMP_H264_STYPE_N11			= 0,	/**< 1 Référence d'image à double saut (instance unique)  */
	IMP_H264_STYPE_N1X			= 1,	/**< 1 Référence d'image à double saut (multi-instance)  */
	IMP_H264_STYPE_N2X			= 2,	/**< 2 Référence de cadre à double saut  */
	IMP_H264_STYPE_N4X			= 3,	/**< 4 Référence de cadre à double saut  */
	IMP_H264_STYPE_HN1_FALSE	= 4,	/**<  Mode de saut de trame avancé: N,1,HI_FALSE */
	IMP_H264_STYPE_HN1_TRUE		= 5,	/**<  Mode de saut de trame avancé: NN,1,HI_TURE */
	IMP_H264_STYPE_H1M_TRUE		= 6,	/**<  Mode de saut de trame avancé: N1,M,HI_TRUE */
} IMPH264SkipType;

typedef enum {
	IMP_H264_FS_IDR		= 0,	/**<  Images clés en mode de saut d'image avancé  */
	IMP_H264_FS_BASE	= 1,	/**<  Image de référence en mode de saut d'image avancé  */
	IMP_H264_FS_ENHANCE	= 2,	/**<  Cadre amélioré en mode de saut de cadre avancé  */
} IMPH264RefType;

/**
 *  Cadre amélioré en mode de saut de cadre avancé H264 Structure de type de saut de trame avancée 
 */
typedef struct {
	IMPH264SkipType	h264SkipType;	/**<  Type de saut de trame  */
	int				m;				/**<  Intervalle d'image amélioré  */
	int				n;				/**<  Intervalle de trame de référence  */
} IMPEncoderAttrH264HSkip;

/**
 *  Intervalle de trame de référence H264 Structure de type de saut de cadre avancé vierge 
 */
typedef struct {
	int				i_skip_distance;	/**<  Nombre d'images vierges consécutives  */
} IMPEncoderAttrH264BSkip;


/**
 *  Nombre d'images vierges consécutives Channel Propriétés du contrôleur de taux 
 */
typedef struct {
	IMPEncoderRcMode rcMode;						/**< RC  Propriétés du contrôleur de taux  */
	union {
		IMPEncoderAttrH264FixQP	 attrH264FixQp;		/**< H.264  Codage de protocole Channel Fixqp  Attributs de mode  */
		IMPEncoderAttrH264CBR	 attrH264Cbr;		/**< H.264  Attributs de mode Channel Cbr  Attributs de mode  */
		IMPEncoderAttrH264VBR	 attrH264Vbr;		/**< H.264  Attributs de mode Channel Vbr  Attributs de mode  */
	};
	IMPEncoderAttrH264FrmUsed	attrH264FrmUsed;	/**<  Attributs de mode  */
	IMPEncoderAttrH264Demask	attrH264Demask;		/**<  Attributs de mode  */
	IMPEncoderAttrH264Denoise	attrH264Denoise;	/**<  Attributs de mode  */
	IMPEncoderAttrH264HSkip		attrH264HSkip;		/**< H264 Propriétés avancées de saut de trame  */
	IMPEncoderAttrH264BSkip		attrH264BSkip;		/**< H264 Attribut de cadre de saut vide  */
} IMPEncoderRcAttr;

/**
 * H264 Flux NALU Types de 
 */
typedef enum {
	IMP_NAL_UNKNOWN		= 0,	/**<  non spécifié  */
	IMP_NAL_SLICE		= 1,	/**<  Un non IDR Bande de codage d'image   */
	IMP_NAL_SLICE_DPA	= 2,	/**<  Bloc de segmentation de données de bande codé A */
	IMP_NAL_SLICE_DPB	= 3,	/**<  Bloc de segmentation de données de bande codé B */
	IMP_NAL_SLICE_DPC	= 4,	/**<  Bloc de segmentation de données de bande codé C */
	IMP_NAL_SLICE_IDR	= 5,	/**< IDR Bloc de segmentation de données de bande codé  */
	IMP_NAL_SEI			= 6,	/**<  Informations sur les améliorations auxiliaires  (SEI) */
	IMP_NAL_SPS			= 7,	/**<  Jeu de paramètres de séquence  */
	IMP_NAL_PPS			= 8,	/**<  Jeu de paramètres d'image  */
	IMP_NAL_AUD			= 9,	/**<  Séparateur d'unité d'accès  */
	IMP_NAL_FILLER		= 12,	/**<  Entrée de données  */
} IMPEncoderH264NaluType;

/**
 *  Définir le type de flux de code 
 */
typedef union {
	IMPEncoderH264NaluType		h264Type;		/**< H264E NALU  Type de paquet de flux  */
} IMPEncoderDataType;

/**
 *  Définir la structure du paquet de flux de code de trame 
 */
typedef struct {
	uint32_t	phyAddr;						/**<  Adresse physique du paquet de flux  */
	uint32_t	virAddr;						/**<  Adresse virtuelle du paquet de flux  */
	uint32_t	length;							/**<  Longueur du paquet de flux  */

	int64_t		timestamp;						/**<  Horodatage ， unité us */
	bool		frameEnd;						/**<  Indicateur de fin de trame  */

	IMPEncoderDataType	dataType;				/**<  Type de flux  */
} IMPEncoderPack;

/**
 *  Définir la structure du type de flux de trames 
 */
typedef struct {
	IMPEncoderPack	*pack;				/**<  Structure des paquets de flux de trames  */
	uint32_t	packCount;				/**<  Le nombre de tous les paquets dans une trame de flux de code  */
	uint32_t	seq;					/**<  Numéro de série du flux ， Obtenez le numéro d'image par image ， Obtenez le numéro de série du colis par colis  */
	union {
		IMPH264RefType h264RefType;
	};
} IMPEncoderStream;

/**
 *  Définir les propriétés de découpage de l'encodeur ， Commencez par recadrer l'image entrée dans l'encodeur ， Comparer avec la taille du canal d'encodage avant la mise à l'échelle 
 */
typedef struct {
    bool		enable;		/**<  Que ce soit pour couper , Que ce soit pour couper :[FALSE, TRUE],TRUE: Activer le découpage ,FALSE: Désactiver le découpage  */
    uint32_t	x;			/**<  Zone recadrée , Coin supérieur gauche x coordonner  */
    uint32_t	y;			/**<  coordonner , coordonner y coordonner  */
    uint32_t	w;			/**<  coordonner , largeur  */
    uint32_t	h;			/**<  largeur , haut  */
} IMPEncoderCropCfg;

/**
 *  Définir l'encodeur pour insérer les attributs de données utilisateur , Seulement pour H264
 */
typedef struct {
	uint32_t			maxUserDataCnt;		/**<  Nombre maximum d'utilisateurs pour insérer l'espace du cache de données , gamme: 0-2 */
	uint32_t			maxUserDataSize;	/**<  Taille maximale de l'espace du cache de données d'insertion par l'utilisateur , Taille maximale de l'espace du cache de données d'insertion par l'utilisateur 16-1024 */
} IMPEncoderUserDataCfg;

/**
 *  Définir la structure des attributs du codeur 
 */
typedef struct {
	IMPPayloadType			enType;			/**<  Type de protocole de codage  */
	uint32_t				bufSize;		/**<  Configuration  buffer  Taille ， Taille : Pas moins que le produit de la largeur et de la hauteur de l'image 1.5 Fois. Lors de la définition des propriétés de codage de canal ， Réglez ce paramètre sur 0，IMP La taille est automatiquement calculée en interne  */
	uint32_t				profile;		/**<  Niveau de codage , 0: baseline; 1:MP; 2:HP */
	uint32_t				picWidth;		/**<  Largeur de l'image codée  */
	uint32_t				picHeight;		/**<  Hauteur de l'image codée  */
	IMPEncoderCropCfg		crop;			/**<  Propriétés de recadrage de l'encodeur  */
	IMPEncoderUserDataCfg	userData;		/**<  Insérer des attributs de données utilisateur , Insérer des attributs de données utilisateur H264 */
} IMPEncoderAttr;

/**
 *  Insérer des attributs de données utilisateur Channel Structure d'attribut 
 */
typedef struct {
	IMPEncoderAttr		encAttr;	/**<  Structure d'attribut du codeur  */
	IMPEncoderRcAttr	rcAttr;			/**<  Structure d'attribut du contrôleur de débit  */
} IMPEncoderCHNAttr;

/**
 *  Structure d'attribut du contrôleur de débit Channel Structure de l'État 
 */
typedef struct {
	bool		registered;				/**<  Inscrivez-vous à Group Signe ， Signe :{TRUE, FALSE}，TRUE: inscrit ，FALSE: non enregistré  */
	uint32_t	leftPics;				/**<  Nombre d'images à encoder  */
	uint32_t	leftStreamBytes;		/**<  Nombre d'images à encoder buffer Restant byte numéro  */
	uint32_t	leftStreamFrames;		/**<  numéro buffer Images restantes  */
	uint32_t	curPacks;				/**<  Le nombre de paquets de flux dans la trame actuelle  */
	uint32_t	work_done;				/**<  État de fonctionnement du programme de canal ，0 :fonctionnement ，1， Ne pas courrir  */
} IMPEncoderCHNStat;

/**
 *  Définir la couleur en gris (C2G) paramètre 
 */
typedef struct {
    bool	enable;			/**<  Activer ou désactiver la fonction de couleur à gris  */
} IMPEncoderColor2GreyCfg;

/**
 *  Définir les paramètres EnableIDR Définir les paramètres 
 */
typedef struct {
    bool	enable;			/**<  Définir ou non EnableIDR */
} IMPEncoderEnIDRCfg;

/**
 *  Définir ou non gopsize Définir ou non 
 */
typedef struct {
	int		gopsize;			/**< IDR Définir ou non  */
} IMPEncoderGOPSizeCfg;

/**
 *  Définir ou non ROI Définir ou non 
 */
typedef struct {
	uint32_t	u32Index;	/**< ROI Valeur d'index de zone ， Valeur d'index de zone 0-7 */
	bool		bEnable;	/**<  Activer ou non cette zone ROI Fonctionnalités  */
	bool		bRelatedQp;		/**< 0 :absolu ROI，1 :relativement ROI */
	int			s32Qp;		/**< ROI Aire relative ou absolue qp Aire relative ou absolue  */
	IMPRect		rect;		/**<  Propriétés des coordonnées de zone  */
} IMPEncoderROICfg;

/**
 * @fn int IMP_Encoder_CreateGroup(int encGroup)
 *
 *  Créer du code Group
 *
 * @param[in] encGroup Group numéro , numéro :[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0  Succès 
 * @retval  non- 0  échec 
 *
 * @remarks  Tout le Group Prend en charge une seule résolution ， Différentes résolutions doivent recommencer Group . Tout le Group Soutenez tout le chemin en même temps H264 Et tout le chemin JPEG Se casser 
 *
 * @attention  Si spécifié Group existe déjà ， Manqué 
 */
int IMP_Encoder_CreateGroup(int encGroup);

/**
 * @fn int IMP_Encoder_DestroyGroup(int encGroup)
 *
 *  Détruisez le code Grouop.
 *
 * @param[in] encGroup Group Détruisez le code , Détruisez le code :[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0  Détruisez le code 
 * @retval  Détruisez le code 0  Détruisez le code 
 *
 * @remarks  détruire Group détruire ， Doit garantir Group Est vide ， C'est-à-dire sans aucun Channel dans Group Inscrivez-vous ， Ou inscrivez-vous à Group dans 
 *  de Channel Annulé ， Sinon, il retourne échoué 
 *
 * @attention  Détruire inexistant Group， Détruire inexistant 
 */
int IMP_Encoder_DestroyGroup(int encGroup);

/**
 * @fn int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr)
 *
 *  Détruire inexistant Channel
 *
 * @param[in] encChn  Détruire inexistant Channel Détruire inexistant , Détruire inexistant : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr  Détruire inexistant Channel Pointeur d'attribut 
 *
 * @retval 0  Pointeur d'attribut 
 * @retval  Pointeur d'attribut 0  Pointeur d'attribut 
 *
 * @remarks  Pointeur d'attribut Channel L'attribut se compose de deux parties ， Attributs d'encodeur et attributs de contrôle de débit 
 * @remarks  Les propriétés du codeur doivent d'abord sélectionner le protocole de codage ， Attribuez ensuite des valeurs aux attributs correspondant aux différents protocoles 
 */
int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr);

/**
 * @fn int IMP_Encoder_DestroyChn(int encChn)
 *
 *  Attribuez ensuite des valeurs aux attributs correspondant aux différents protocoles Channel
 *
 * @param[in] encChn  Attribuez ensuite des valeurs aux attributs correspondant aux différents protocoles Channel Attribuez ensuite des valeurs aux attributs correspondant aux différents protocoles , Attribuez ensuite des valeurs aux attributs correspondant aux différents protocoles : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  Attribuez ensuite des valeurs aux attributs correspondant aux différents protocoles 
 * @retval  Attribuez ensuite des valeurs aux attributs correspondant aux différents protocoles 0  Attribuez ensuite des valeurs aux attributs correspondant aux différents protocoles 
 *
 * @attention  Attribuez ensuite des valeurs aux attributs correspondant aux différents protocoles Channel， Attribuez ensuite des valeurs aux attributs correspondant aux différents protocoles 
 * @attention  Doit garantir avant la destruction Channel Ont été de Group Anti-enregistrement ， Anti-enregistrement 
 */
int IMP_Encoder_DestroyChn(int encChn);

/**
 * @fn int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr * const attr)
 *
 *  Obtenez le code Channel Attribut de 
 *
 * @param[in] encChn  Attribut de Channel Attribut de , Attribut de : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr  Attribut de Channel Les attributs 
 *
 * @retval 0  Les attributs 
 * @retval  Les attributs 0  Les attributs 
 */
int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr * const attr);

/**
 * @fn int IMP_Encoder_RegisterChn(int encGroup, int encChn)
 *
 *  Code d'enregistrement Channel À Group
 *
 * @param[in] encGroup  À Group À , À : [0, @ref NR_MAX_ENC_GROUPS - 1]
 * @param[in] encChn  À Channel À , À : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  À 
 * @retval  À 0  À 
 *
 * @attention  L'enregistrement n'existe pas Channel， L'enregistrement n'existe pas 
 * @attention  L'enregistrement n'existe pas Channel À inexistant Group， À inexistant 
 * @attention  Même code Channel Un seul peut être enregistré Group， Si la Channel Déjà inscrit à un Group， Déjà inscrit à un 
 * @attention  Si un Group Déjà enregistré ， Ensuite ceci Group Je ne peux pas être l'autre Channel Je ne peux pas être l'autre ， Sauf si la relation d'enregistrement précédente est annulée 
 */

int IMP_Encoder_RegisterChn(int encGroup, int encChn);
/**
 * @fn int IMP_Encoder_UnRegisterChn(int encChn)
 *
 *  Code anti-enregistrement Channel Code anti-enregistrement Group
 *
 * @param[in] encChn  Code anti-enregistrement Channel Code anti-enregistrement , Code anti-enregistrement : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  Code anti-enregistrement 
 * @retval  Code anti-enregistrement 0  Code anti-enregistrement 
 *
 * @remarks Channel Après la déconnexion ， Après la déconnexion Channel Sera réinitialisé ， Sera réinitialisé Channel Flux buffer Sera vidé ， Si l'utilisateur utilise toujours 
 *  Streams non diffusés à temps buffer， Ne sera pas garanti buffer Exactitude des données ， L'utilisateur peut utiliser IMP_Encoder_Query Interface à interroger 
 *  code Channel code buffer statut ， Flux de confirmation buffer Se désinscrire après avoir intégré le flux de code Channel
 *
 * @attention  Déconnexion non créée Channel， Déconnexion non créée 
 * @attention  Non enregistré Channel， Non enregistré 
 * @attention  Si code Channel N'arrête pas de recevoir le codage de l'image ， N'arrête pas de recevoir le codage de l'image 
 */
int IMP_Encoder_UnRegisterChn(int encChn);

/**
 * @fn int IMP_Encoder_StartRecvPic(int encChn)
 *
 *  Activer l'encodage Channel Recevoir l'image 
 *
 * @param[in] encChn  Recevoir l'image Channel Recevoir l'image , Recevoir l'image : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  Recevoir l'image 
 * @retval  Recevoir l'image 0  Recevoir l'image 
 *
 * @remarks  Recevoir l'image Channel L'encodage ne peut démarrer qu'après réception de l'image 
 *
 * @attention  au cas où Channel Non créé ， Non créé 
 * @attention  Non créé Channel Non enregistré pour Group， Non enregistré pour 
 */
int IMP_Encoder_StartRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_StopRecvPic(int encChn)
 *
 *  Arrêter le codage Channel Arrêter le codage 
 *
 * @param[in] encChn  Arrêter le codage Channel Arrêter le codage , Arrêter le codage : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  Arrêter le codage 
 * @retval  Arrêter le codage 0  Arrêter le codage 
 *
 * @remarks  Cette interface ne détermine pas s'il faut arrêter de recevoir actuellement ， Autrement dit, il est permis d'arrêter de recevoir à plusieurs reprises sans renvoyer une erreur 
 * @remarks  L'appel de cette interface arrête uniquement de recevoir le codage des données d'origine ， L'appel de cette interface arrête uniquement de recevoir le codage des données d'origine buffer Ne sera pas éliminé 
 *
 * @attention  Ne sera pas éliminé Channel Ne sera pas éliminé ， Ne sera pas éliminé 
 * @attention  Ne sera pas éliminé Channel Ne sera pas éliminé Group， Ne sera pas éliminé 
 */
int IMP_Encoder_StopRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat)
 *
 *  Code de requête Channel Code de requête 
 *
 * @param[in] encChn  Code de requête Channel Code de requête , Code de requête : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] stat  Code de requête Channel Code de requête 
 *
 * @retval 0  Code de requête 
 * @retval  Code de requête 0  Code de requête 
 *
 * @remarks  non 
 *
 * @attention  non 
 */
int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat);

/**
 * @fn int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag)
 *
 *  Obtenez le flux codé 
 *
 * @param[in] encChn  Obtenez le flux codé Channel Obtenez le flux codé , Obtenez le flux codé : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream  Pointeur de structure de flux 
 * @param[in] blockFlag  Utiliser ou non la méthode de blocage pour obtenir ，0 : Non bloquant ，1 :bloquer 
 *
 * @retval 0  :bloquer 
 * @retval  :bloquer 0  :bloquer 
 *
 * @remarks  Obtenez les données d'une image de flux à la fois 
 * @remarks  Si l'utilisateur n'obtient pas le flux de code pendant une longue période , Le tampon de flux sera plein. Un code Channel Si le tampon de flux est plein , Sera après 
 *  L'image reçue est perdue , Jusqu'à ce que l'utilisateur reçoive le flux de code , Il y a donc suffisamment de tampon de flux de code à utiliser pour l'encodage , Commencez simplement à coder. Suggérer des utilisateurs 
 *  L'appel d'interface pour obtenir le flux de code et l'appel d'interface pour libérer le flux de code apparaissent par paires , Et publiez le flux dès que possible , Empêcher le flux de code d'être acquis en raison du mode utilisateur , Relâchez pas 
 *  Flux de code causé dans le temps  buffer  complet , Arrêtez de coder. 
 * @remarks  pour H264 Type de flux ， Obtenez une image de flux de code avec succès en un seul appel ， Cette trame de flux de code peut contenir plusieurs paquets. 
 * @remarks  Cette trame de flux de code peut contenir plusieurs paquets. JPEG Cette trame de flux de code peut contenir plusieurs paquets. ， Cette trame de flux de code peut contenir plusieurs paquets. ， Cette trame de flux de code ne contient qu'un seul paquet ， Ce cadre contient JPEG Les informations complètes du fichier image. 
 *
 *  Exemple: 
 * @code
 * int ret;
 * ret = IMP_Encoder_PollingStream(ENC_H264_CHANNEL, 1000); //Polling Exemple: Buffer， En attente de disponibilité 
 * if (ret < 0) {
 *     printf("Polling stream timeout\n");
 *     return -1;
 * }
 *
 * IMPEncoderStream stream;
 * ret = IMP_Encoder_GetStream(ENC_H264_CHANNEL, &stream, 1); // Obtenez un flux d'images ， Méthode de blocage 
 * if (ret < 0) {
 *     printf("Get Stream failed\n");
 *     return -1;
 * }
 *
 * int i, nr_pack = stream.packCount;
 * for (i = 0; i < nr_pack; i++) { // Enregistrez chaque paquet de cette trame de flux de code 
 *     ret = write(stream_fd, (void *)stream.pack[i].virAddr,
 *                stream.pack[i].length);
 *     if (ret != stream.pack[i].length) {
 *         printf("stream write error:%s\n", strerror(errno));
 *         return -1;
 *     }
 * }
 * @endcode
 *
 * @attention  Enregistrez chaque paquet de cette trame de flux de code pstStream pour NULL, Puis renvoyez l'échec; 
 * @attention  Puis renvoyez l'échec; Channel Puis renvoyez l'échec; ， Puis renvoyez l'échec; 
 */
int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag);

/**
 * @fn int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream)
 *
 *  Libérez le cache du flux de code 
 *
 * @param[in] encChn  Libérez le cache du flux de code Channel Libérez le cache du flux de code , Libérez le cache du flux de code : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream  Libérez le cache du flux de code 
 *
 * @retval 0  Libérez le cache du flux de code 
 * @retval  Libérez le cache du flux de code 0  Libérez le cache du flux de code 
 *
 * @remarks  Cette interface doit être IMP_Encoder_GetStream Jumeler et utiliser ，\n
 *  Après avoir obtenu le flux de code, l'utilisateur doit libérer le cache de flux de code obtenu à temps ， Sinon, cela peut provoquer un flux de bits buffer Sinon, cela peut provoquer un flux de bits ， Affecte l'encodage de l'encodeur. \n
 *  Et l'utilisateur doit appuyer sur 
 *  Libérez le cache de flux de code qui a été acquis dans l'ordre de libération; 
 * @remarks  Codage Channel Après la désinscription ， Tous les paquets de flux non publiés ne sont pas valides ， Ce tampon de flux de code non valide ne peut plus être utilisé ou libéré. 
 *
 * @attention  Ce tampon de flux de code non valide ne peut plus être utilisé ou libéré. pstStream Ce tampon de flux de code non valide ne peut plus être utilisé ou libéré. NULL, Ce tampon de flux de code non valide ne peut plus être utilisé ou libéré. 
 * @attention  Ce tampon de flux de code non valide ne peut plus être utilisé ou libéré. Channel Ce tampon de flux de code non valide ne peut plus être utilisé ou libéré. ， Ce tampon de flux de code non valide ne peut plus être utilisé ou libéré. 
 * @attention  La libération du flux de code non valide renverra un échec. 
 */
int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream);

/**
 * @fn int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec)
 *
 * Polling Tampon de flux 
 *
 * @param[in] encChn  Tampon de flux Channel Tampon de flux , Tampon de flux : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] timeoutMsec  temps supplémentaire ， Unité: millisecondes 
 *
 * @retval 0  Unité: millisecondes 
 * @retval  Unité: millisecondes 0  Unité: millisecondes 
 *
 * @remarks  Vous pouvez l'utiliser avant d'obtenir le flux de code API monter Polling， La fonction retourne lorsque le tampon de flux de code n'est pas vide ou lorsqu'il expire. 
 *
 * @attention  La fonction retourne lorsque le tampon de flux de code n'est pas vide ou lorsqu'il expire. 
 */
int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream)
 *
 *  Définir le cache du flux de code Buffer Nombre 
 *
 * @param[in] encChn  Nombre Channel Nombre , Nombre : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] nrMaxStream  Nombre Buffer Nombre , Nombre : [1, @ref NR_MAX_ENC_CHN_STREAM]
 *
 * @retval 0  Nombre 
 * @retval  Nombre 0  Nombre 
 *
 * @remarks  En raison de la mise en cache du flux Buffer Le numéro est fixe lors de la création du canal ， Par conséquent API Il doit être appelé avant la création du canal. 
 * @remarks  S'il n'est pas appelé avant la création du canal API S'il n'est pas appelé avant la création du canal Buffer S'il n'est pas appelé avant la création du canal ， alors H264 Le nombre de canaux par défaut est 5，JPEG Le nombre de canaux par défaut est 1 Le nombre de canaux par défaut est 
 *
 * @attention  Le nombre de canaux par défaut est 
 */
int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream);

/**
 * @fn int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream)
 *
 *  Obtenir le flux de code Buffer Obtenir le flux de code 
 *
 * @param[in] encChn  Obtenir le flux de code Channel Obtenir le flux de code , Obtenir le flux de code : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] nrMaxStream  Obtenir le flux de code Buffer Pointeur variable 
 *
 * @retval 0  Pointeur variable 
 * @retval  Pointeur variable 0  Pointeur variable 
 *
 * @remarks  Pointeur variable 
 *
 * @attention  Pointeur variable 
 */
int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream);

/**
 * @fn int IMP_Encoder_RequestIDR(int encChn)
 *
 *  demander IDR Cadre 
 *
 * @param[in] encChn  Cadre Channel Cadre , Cadre : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  Cadre 
 * @retval  Cadre 0  Cadre 
 *
 * @remarks  Appeler ça API Arrière ， S'appliquera dans la trame d'encodage la plus proche IDR Encodage de trame. 
 *
 * @attention  Encodage de trame. 
 */
int IMP_Encoder_RequestIDR(int encChn);

/**
 * @fn int IMP_Encoder_FlushStream(int encChn)
 *
 *  Brosser l'ancien flux de code restant dans l'encodeur ， et IDR Codage de début de trame 
 *
 * @param[in] encChn  Codage de début de trame Channel Codage de début de trame , Codage de début de trame : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  Codage de début de trame 
 * @retval  Codage de début de trame 0  Codage de début de trame 
 *
 * @remarks  Codage de début de trame API Codage de début de trame ， Codage de début de trame IDR Codage de début de trame 
 *
 * @attention  Codage de début de trame 
 */
int IMP_Encoder_FlushStream(int encChn);

/**
 * @fn int IMP_Encoder_SetChnColor2Grey(int encChn, const IMPEncoderColor2GreyCfg *pstColor2Grey).
 *
 *  Réglez la couleur sur la fonction grise 
 *
 * @param[in] encChn  Réglez la couleur sur la fonction grise Channel Réglez la couleur sur la fonction grise , Réglez la couleur sur la fonction grise : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstColor2Grey  Paramètres de la fonction de la couleur au gris 
 *
 * @retval 0  Paramètres de la fonction de la couleur au gris 
 * @retval  Paramètres de la fonction de la couleur au gris 0  Paramètres de la fonction de la couleur au gris 
 *
 * @remarks  Appelle ça API Réglez la couleur sur la fonction grise du canal ， Sur le prochain IDR ou P Le cadre prend effet. 
 *  Le cadre prend effet. API Besoin d'un canal existe déjà. 
 *
 * @attention  Besoin d'un canal existe déjà. 
 */
int IMP_Encoder_SetChnColor2Grey(int encChn, const IMPEncoderColor2GreyCfg *pstColor2Grey);

/**
 * @fn int IMP_Encoder_GetChnColor2Grey(int encChn, IMPEncoderColor2GreyCfg *pstColor2Grey).
 *
 *  Obtenir la couleur des attributs de fonction gris 
 *
 * @param[in] encChn  Obtenir la couleur des attributs de fonction gris Channel Obtenir la couleur des attributs de fonction gris , Obtenir la couleur des attributs de fonction gris : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstColor2Grey  Obtenir la couleur des attributs de fonction gris 
 *
 * @retval 0  Obtenir la couleur des attributs de fonction gris 
 * @retval  Obtenir la couleur des attributs de fonction gris 0  Obtenir la couleur des attributs de fonction gris 
 *
 * @remarks  Obtenir la couleur des attributs de fonction gris API Obtiendra les attributs de fonction de couleur à gris du canal ， Obtiendra les attributs de fonction de couleur à gris du canal API Obtiendra les attributs de fonction de couleur à gris du canal 
 *
 * @attention  Cette fonction JPEG La chaîne n'a pas de sens. 
 */
int IMP_Encoder_GetChnColor2Grey(int encChn, IMPEncoderColor2GreyCfg *pstColor2Grey);

/**
 * @fn int IMP_Encoder_SetChnRcAttr(int encChn, const IMPEncoderRcAttr *pstRcCfg).
 *
 *  Définir les propriétés du contrôle de débit 
 *
 * @param[in] encChn  Définir les propriétés du contrôle de débit Channel Définir les propriétés du contrôle de débit , Définir les propriétés du contrôle de débit : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstRcCfg  Paramètres d'attribut de contrôle de débit 
 *
 * @retval 0  Paramètres d'attribut de contrôle de débit 
 * @retval  Paramètres d'attribut de contrôle de débit 0  Paramètres d'attribut de contrôle de débit 
 *
 * @remarks  Paramètres d'attribut de contrôle de débit API Définira les propriétés de contrôle de débit du canal ， Suivant IDR Prendre effet , Prendre effet API Prendre effet 
 *
 * @attention  Actuellement ， Prise en charge du contrôle de taux ENC_RC_MODE_H264FIXQP contre ENC_RC_MODE_H264CBR contre 
 * ENC_RC_MODE_H264FIXQP Configuration du support qp，ENC_RC_MODE_H264CBR Configuration du support outBitRate Configuration du support 
 * @attention  Configuration du support JPEG Configuration du support 
 */
int IMP_Encoder_SetChnRcAttr(int encChn, const IMPEncoderRcAttr *pstRcCfg);

/**
 * @fn int IMP_Encoder_GetChnRcAttr(int encChn, IMPEncoderRcAttr *pstRcCfg).
 *
 *  Obtenir les propriétés du contrôle de débit 
 *
 * @param[in] encChn  Obtenir les propriétés du contrôle de débit Channel Obtenir les propriétés du contrôle de débit , Obtenir les propriétés du contrôle de débit : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstRcCfg  Obtenir les propriétés du contrôle de débit 
 *
 * @retval 0  Obtenir les propriétés du contrôle de débit 
 * @retval  Obtenir les propriétés du contrôle de débit 0  Obtenir les propriétés du contrôle de débit 
 *
 * @remarks  Obtenir les propriétés du contrôle de débit API Obtiendra les propriétés de contrôle de débit du canal ， Obtiendra les propriétés de contrôle de débit du canal API Obtiendra les propriétés de contrôle de débit du canal 
 *
 * @attention  Obtiendra les propriétés de contrôle de débit du canal JPEG Obtiendra les propriétés de contrôle de débit du canal 
 */
int IMP_Encoder_GetChnRcAttr(int encChn, IMPEncoderRcAttr *pstRcCfg);

/**
 * @fn int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps)
 *
 *  Définir dynamiquement les propriétés du contrôle de la fréquence d'images 
 *
 * @param[in] encChn  Définir dynamiquement les propriétés du contrôle de la fréquence d'images Channel Définir dynamiquement les propriétés du contrôle de la fréquence d'images , Définir dynamiquement les propriétés du contrôle de la fréquence d'images : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg  Paramètres d'attribut de contrôle de la fréquence d'images 
 *
 * @retval 0  Paramètres d'attribut de contrôle de la fréquence d'images 
 * @retval  Paramètres d'attribut de contrôle de la fréquence d'images 0  Paramètres d'attribut de contrôle de la fréquence d'images 
 *
 * @remarks  Paramètres d'attribut de contrôle de la fréquence d'images API Réinitialise les propriétés de fréquence d'images de l'encodeur ， L'attribut de fréquence d'images est le suivant GOP L'attribut de fréquence d'images est le suivant ， Délai maximum 1 Prenez effet en quelques secondes ， Prenez effet en quelques secondes API Prenez effet en quelques secondes 
 * @remarks  Si vous appelez IMP_FrameSource_SetChnFPS() La fonction modifie dynamiquement la fréquence d'images du système ， Ensuite, vous devez appeler cette fonction pour modifier la fréquence d'images de l'encodeur ， Terminez la configuration correcte des paramètres. 
 *
 * @attention  non. 
 */
int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps)
 *
 *  Obtenir les propriétés du contrôle de la fréquence d'images 
 *
 * @param[in] encChn  Obtenir les propriétés du contrôle de la fréquence d'images Channel Obtenir les propriétés du contrôle de la fréquence d'images , Obtenir les propriétés du contrôle de la fréquence d'images : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg  Obtenir les propriétés du contrôle de la fréquence d'images 
 *
 * @retval 0  Obtenir les propriétés du contrôle de la fréquence d'images 
 * @retval  Obtenir les propriétés du contrôle de la fréquence d'images 0  Obtenir les propriétés du contrôle de la fréquence d'images 
 *
 * @remarks  Obtenir les propriétés du contrôle de la fréquence d'images API Obtiendra les propriétés de contrôle de la fréquence d'images du canal ， Obtiendra les propriétés de contrôle de la fréquence d'images du canal API Obtiendra les propriétés de contrôle de la fréquence d'images du canal 
 *
 * @attention  Obtiendra les propriétés de contrôle de la fréquence d'images du canal JPEG Obtiendra les propriétés de contrôle de la fréquence d'images du canal 
 */
int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROICfg *pstVencRoiCfg)
 *
 *  Configurer la chaîne ROI Configurer la chaîne 
 *
 * @param[in] encChn  Configurer la chaîne Channel Configurer la chaîne , Configurer la chaîne : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg ROI Paramètre d'attribut 
 *
 * @retval 0  Paramètre d'attribut 
 * @retval  Paramètre d'attribut 0  Paramètre d'attribut 
 *
 * @remarks  Paramètre d'attribut API Configurera la chaîne ROI Configurera la chaîne ， Configurera la chaîne API Configurera la chaîne 
 *
 * @attention  Configurera la chaîne 
 */
int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROICfg *pstVencRoiCfg);

/**
 * @fn int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROICfg *pstVencRoiCfg)
 *
 *  Obtenir la chaîne ROI Obtenir la chaîne 
 *
 * @param[in] encChn  Obtenir la chaîne Channel Obtenir la chaîne , Obtenir la chaîne : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg ROI Obtenir la chaîne 
 *
 * @retval 0  Obtenir la chaîne 
 * @retval  Obtenir la chaîne 0  Obtenir la chaîne 
 *
 * @remarks  Obtenir la chaîne API Obtiendra la chaîne ROI Obtiendra la chaîne ， Obtiendra la chaîne API Obtiendra la chaîne 
 *
 * @attention  Obtiendra la chaîne JPEG Obtiendra la chaîne 
 */
int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROICfg *pstVencRoiCfg);

/**
 * @fn int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 *  Obtiendra la chaîne GOP Obtiendra la chaîne 
 *
 * @param[in] encChn  Obtiendra la chaîne Channel Obtiendra la chaîne , Obtiendra la chaîne : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstGOPSizeCfg GOPSize Obtiendra la chaîne 
 *
 * @retval 0  Obtiendra la chaîne 
 * @retval  Obtiendra la chaîne 0  Obtiendra la chaîne 
 *
 * @remarks  Obtiendra la chaîne API Obtiendra la chaîne GOPSize Obtiendra la chaîne ， Obtiendra la chaîne API Obtiendra la chaîne 
 *
 * @attention  Obtiendra la chaîne JPEG Obtiendra la chaîne 
 */
int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 *  Obtiendra la chaîne GOP Obtiendra la chaîne 
 *
 * @param[in] encChn  Obtiendra la chaîne Channel Obtiendra la chaîne , Obtiendra la chaîne : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstGOPSizeCfg GOP Obtiendra la chaîne 
 *
 * @retval 0  Obtiendra la chaîne 
 * @retval  Obtiendra la chaîne 0  Obtiendra la chaîne 
 *
 * @remarks  Obtiendra la chaîne API Obtiendra la chaîne GOPSize Obtiendra la chaîne ， Obtiendra la chaîne API Obtiendra la chaîne 
 *
 * @attention  Obtiendra la chaîne 
 */
int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetChnH264Demask(int encChn, const IMPEncoderAttrH264Demask *pdemaskAttr)
 *
 *  Définir les propriétés de dématriçage des canaux 
 *
 * @param[in] encChn  Définir les propriétés de dématriçage des canaux Channel Définir les propriétés de dématriçage des canaux , Définir les propriétés de dématriçage des canaux : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdemaskAttr  Paramètres de propriété de dématriçage 
 *
 * @retval 0  Paramètres de propriété de dématriçage 
 * @retval  Paramètres de propriété de dématriçage 0  Paramètres de propriété de dématriçage 
 *
 * @remarks  Paramètres de propriété de dématriçage API Définira les propriétés de dématriçage du canal ， Définira les propriétés de dématriçage du canal API Définira les propriétés de dématriçage du canal 
 *
 * @attention  Définira les propriétés de dématriçage du canal 
 */
int IMP_Encoder_SetChnH264Demask(int encChn, const IMPEncoderAttrH264Demask *pdemaskAttr);

/**
 * @fn int IMP_Encoder_GetChnH264Demask(int encChn, IMPEncoderAttrH264Demask *pdemaskAttr)
 *
 *  Obtenir les propriétés de dématriçage des canaux 
 *
 * @param[in] encChn  Obtenir les propriétés de dématriçage des canaux Channel Obtenir les propriétés de dématriçage des canaux , Obtenir les propriétés de dématriçage des canaux : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdemaskAttr  Obtenir les propriétés de dématriçage des canaux 
 *
 * @retval 0  Obtenir les propriétés de dématriçage des canaux 
 * @retval  Obtenir les propriétés de dématriçage des canaux 0  Obtenir les propriétés de dématriçage des canaux 
 *
 * @remarks  Obtenir les propriétés de dématriçage des canaux API Obtiendra les propriétés de dématriçage du canal ， Obtiendra les propriétés de dématriçage du canal API Obtiendra les propriétés de dématriçage du canal 
 *
 * @attention  Obtiendra les propriétés de dématriçage du canal 
 */
int IMP_Encoder_GetChnH264Demask(int encChn, IMPEncoderAttrH264Demask *pdemaskAttr);

/**
 * @fn int IMP_Encoder_SetChnH264FrmUsedMode(int encChn, const IMPEncoderAttrH264FrmUsed *pfrmUsedAttr)
 *
 *  Définir l'attribut du mode d'utilisation de la trame d'entrée du canal 
 *
 * @param[in] encChn  Définir l'attribut du mode d'utilisation de la trame d'entrée du canal Channel Définir l'attribut du mode d'utilisation de la trame d'entrée du canal , Définir l'attribut du mode d'utilisation de la trame d'entrée du canal : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr  Paramètre d'attribut du mode d'utilisation du cadre d'entrée 
 *
 * @retval 0  Paramètre d'attribut du mode d'utilisation du cadre d'entrée 
 * @retval  Paramètre d'attribut du mode d'utilisation du cadre d'entrée 0  Paramètre d'attribut du mode d'utilisation du cadre d'entrée 
 *
 * @remarks  Paramètre d'attribut du mode d'utilisation du cadre d'entrée API Définira l'attribut de mode d'utilisation de la trame d'entrée du canal ， Définira l'attribut de mode d'utilisation de la trame d'entrée du canal API Définira l'attribut de mode d'utilisation de la trame d'entrée du canal 
 *
 * @attention  Définira l'attribut de mode d'utilisation de la trame d'entrée du canal 
 */
int IMP_Encoder_SetChnH264FrmUsedMode(int encChn, const IMPEncoderAttrH264FrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_GetChnH264FrmUsedMode(int encChn, IMPEncoderAttrH264FrmUsed *pfrmUsedAttr)
 *
 *  Obtenir l'attribut du mode d'utilisation de la trame d'entrée du canal 
 *
 * @param[in] encChn  Obtenir l'attribut du mode d'utilisation de la trame d'entrée du canal Channel Obtenir l'attribut du mode d'utilisation de la trame d'entrée du canal , Obtenir l'attribut du mode d'utilisation de la trame d'entrée du canal : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr  Obtenir l'attribut du mode d'utilisation de la trame d'entrée du canal 
 *
 * @retval 0  Obtenir l'attribut du mode d'utilisation de la trame d'entrée du canal 
 * @retval  Obtenir l'attribut du mode d'utilisation de la trame d'entrée du canal 0  Obtenir l'attribut du mode d'utilisation de la trame d'entrée du canal 
 *
 * @remarks  Obtenir l'attribut du mode d'utilisation de la trame d'entrée du canal API Obtiendra l'attribut de mode d'utilisation de la trame d'entrée du canal ， Obtiendra l'attribut de mode d'utilisation de la trame d'entrée du canal API Obtiendra l'attribut de mode d'utilisation de la trame d'entrée du canal 
 *
 * @attention  Obtiendra l'attribut de mode d'utilisation de la trame d'entrée du canal 
 */
int IMP_Encoder_GetChnH264FrmUsedMode(int encChn, IMPEncoderAttrH264FrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_SetChnH264Denoise(int encChn, const IMPEncoderAttrH264Denoise *pdenoiseAttr)
 *
 *  Définir les propriétés de réduction du bruit de canal 
 *
 * @param[in] encChn  Définir les propriétés de réduction du bruit de canal Channel Définir les propriétés de réduction du bruit de canal , Définir les propriétés de réduction du bruit de canal : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdenoiseAttr  Paramètres d'attribut de débruitage 
 *
 * @retval 0  Paramètres d'attribut de débruitage 
 * @retval  Paramètres d'attribut de débruitage 0  Paramètres d'attribut de débruitage 
 *
 * @remarks  Paramètres d'attribut de débruitage API Définira les propriétés de débruitage du canal ， Définira les propriétés de débruitage du canal API Définira les propriétés de débruitage du canal 
 *
 * @attention  Définira les propriétés de débruitage du canal 
 */
int IMP_Encoder_SetChnH264Denoise(int encChn, const IMPEncoderAttrH264Denoise *pdenoiseAttr);

/**
 * @fn int IMP_Encoder_GetChnH264Denoise(int encChn, IMPEncoderAttrH264Denoise *pdenoiseAttr)
 *
 *  Obtenir les propriétés de débruitage du canal 
 *
 * @param[in] encChn  Obtenir les propriétés de débruitage du canal Channel Obtenir les propriétés de débruitage du canal , Obtenir les propriétés de débruitage du canal : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdenoiseAttr  Obtenir les propriétés de débruitage du canal 
 *
 * @retval 0  Obtenir les propriétés de débruitage du canal 
 * @retval  Obtenir les propriétés de débruitage du canal 0  Obtenir les propriétés de débruitage du canal 
 *
 * @remarks  Obtenir les propriétés de débruitage du canal API Obtiendra les propriétés de débruitage du canal ， Obtiendra les propriétés de débruitage du canal API Obtiendra les propriétés de débruitage du canal 
 *
 * @attention  Obtiendra les propriétés de débruitage du canal JPEG Obtiendra les propriétés de débruitage du canal 
 */
int IMP_Encoder_GetChnH264Denoise(int encChn, IMPEncoderAttrH264Denoise *pdenoiseAttr);

/**
 * @fn int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen)
 *
 *  Insérer les données utilisateur 
 *
 * @param[in] encChn  Insérer les données utilisateur Channel Insérer les données utilisateur , Insérer les données utilisateur : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] userData  Pointeur de données utilisateur 
 * @param[in] userDataLen  Longueur des données utilisateur ,  Longueur des données utilisateur :(0, 1024], Longueur des données utilisateur  byte  Longueur des données utilisateur 
 *
 * @retval 0  Longueur des données utilisateur 
 * @retval  Longueur des données utilisateur 0  Longueur des données utilisateur 
 *
 * @remarks  Longueur des données utilisateur API Le canal requis existe déjà 
 * @remarks  Si le canal n'est pas créé , Si le canal n'est pas créé 
 * @remarks  Si le canal n'est pas créé userData Vide ou userDataLen Vide ou 0, Vide ou 
 * @remarks  Vide ou , Supporte uniquement H.264 Protocole d'encodage 
 * @remarks H.264 Les canaux de protocole sont alloués au plus 2 L'espace mémoire de bloc est utilisé pour mettre en cache les données utilisateur , Et la taille de chaque élément de données utilisateur ne dépasse pas 1k byte Et la taille de chaque élément de données utilisateur ne dépasse pas 
 *  Si les données insérées par l'utilisateur sont redondantes 2 Pièce , Ou l'élément de données utilisateur inséré est supérieur à 1k byte  Ou l'élément de données utilisateur inséré est supérieur à , Cette interface renverra une erreur. 
 * @remarks  Chaque élément de données utilisateur est SEI Le format du package est inséré avant le dernier package de flux d'images. Après qu'un certain paquet de données utilisateur est encodé et envoyé ,
 * H.264  L'espace mémoire pour la mise en mémoire tampon de cette donnée utilisateur dans le canal est effacé , Utilisé pour stocker de nouvelles données utilisateur 
 *
 * @attention  Utilisé pour stocker de nouvelles données utilisateur 
 */
int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen);

/**
 * @fn int IMP_Encoder_SetFisheyeEnableStatus(int encChn, int enable)
 *
 *  Installation Ingenic L'état activé de l'algorithme de correction fisheye fourni 
 *
 * @param[in] encChn  L'état activé de l'algorithme de correction fisheye fourni Channel L'état activé de l'algorithme de correction fisheye fourni , L'état activé de l'algorithme de correction fisheye fourni : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] enable 0: Désactiver ( défaut ),1: Permettre 
 *
 * @retval 0  Permettre 
 * @retval  Permettre 0  Permettre 
 *
 * @remarks  Étant donné que l'état d'activation de l'algorithme de correction fisheye est fixé lors de la création du canal ， Étant donné que l'état d'activation de l'algorithme de correction fisheye est fixé lors de la création du canal API Étant donné que l'état d'activation de l'algorithme de correction fisheye est fixé lors de la création du canal 
 * @remarks  Étant donné que l'état d'activation de l'algorithme de correction fisheye est fixé lors de la création du canal API Étant donné que l'état d'activation de l'algorithme de correction fisheye est fixé lors de la création du canal Ingenic Étant donné que l'état d'activation de l'algorithme de correction fisheye est fixé lors de la création du canal , N'est pas activé par défaut ， Autrement dit, l'algorithme de correction fisheye fourni par Ingenics ne peut pas être utilisé. 
 * @remarks  ce API s'applique uniquement à H264
 *
 * @attention  s'applique uniquement à 
 */
int IMP_Encoder_SetFisheyeEnableStatus(int encChn, int enable);

/**
 * @fn int IMP_Encoder_GetFisheyeEnableStatus(int encChn, int *enable)
 *
 *  Obtenir Ingenic Obtenir 
 *
 * @param[in] encChn  Obtenir Channel Obtenir , Obtenir : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] enable  Retour au set Ingenic Retour au set ,0: Pas activé ,1: Activé 
 *
 * @retval 0  Activé 
 * @retval  Activé 0  Activé 
 *
 * @remarks  Activé API Activé H264
 *
 * @attention  Activé 
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
