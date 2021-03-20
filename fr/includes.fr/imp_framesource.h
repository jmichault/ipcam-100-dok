/*
 * IMP FrameSource header file.
 *
 * Copyright (C) 2015 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_FRAMESOURCE_H__
#define __IMP_FRAMESOURCE_H__

#include "imp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * FrameSource Fichier d'en-tête du module 
 */

/**
 * @defgroup IMP_FrameSource
 * @ingroup imp
 * @brief Source vidéo ， Oui IMP Source de données d'image du système ， Vous pouvez définir la résolution de l'image, le recadrage, le zoom et d'autres attributs ， Et la fonction de réduction du bruit d'arrière-plan 
 *
 * FrameSource Est un concept lié au flux de données ， La résolution de l'image peut être définie ， Format etc. ， Et fournissez l'image originale à l'arrière-plan. 
 *
 * FrameSource La structure est la suivante: 
 * @image html FrameSource.png
 * Comme le montre la figure ，FrameSource Il y a trois sorties ， Les trois sorties peuvent être utilisées pour l'encodage ， parmi eux: 
 * * Channel 0 Généralement sous forme de flux vidéo haute définition 
 * * Channel 1 Généralement en tant que flux vidéo de définition standard ， ou IVS Seule source de données algorithmique 
 * * Channel 2 Est d'élargir le canal ， Utilisation dans des applications spéciales ， Généralement déconseillé 
 *
 * FrameSource Les étapes d'initialisation sont les suivantes (prenez deux sorties comme exemple): 
 * @code
 * IMPFSChnAttr fs_chn_attr;
 * fs_chn_attr.pixFmt = PIX_FMT_NV12;
 * fs_chn_attr.outFrmRateNum = SENSOR_FRAME_RATE;
 * fs_chn_attr.outFrmRateDen = 1;
 * fs_chn_attr.nrVBs = 3;
 * fs_chn_attr.type = FS_PHY_CHANNEL;
 *
 * fs_chn_attr.crop.enable = 1;
 * fs_chn_attr.crop.top = 0;
 * fs_chn_attr.crop.left = 0;
 * fs_chn_attr.crop.width = 960;
 * fs_chn_attr.crop.height = 640;
 *
 * fs_chn_attr.scaler.enable = 1;
 * fs_chn_attr.scaler.outwidth = 320;
 * fs_chn_attr.scaler.outheight = 240;
 *
 * ret = IMP_FrameSource_CreateChn(0, &fs_chn_attr); //step.1 créer Channel 0
 * if (ret < 0) {
 * printf("FrameSource_CreateChn(0) error\n");
 * goto createchn_err;
 * }
 *
 * ret = IMP_FrameSource_EnableChn(0); //step.2 Enable Channel 0，channel 0 Lancer la sortie de l'image 
 * if (ret < 0) {
 * printf("EnableChn(0) error\n";
 * return enablechn_err;
 * }
 *
 * // Jusque là ，FrameSource Commencez par l'arrière Group Transférer des données 
 *
 * ret = IMP_FrameSource_DisableChn(0); //step.3 Disable channel 0，channel 0 Arrêter la sortie des images 
 * if (ret < 0) {
 * printf("FrameSource_DisableChn(0) error\n");
 * return disablechn_err;
 * }
 *
 * ret = IMP_FrameSource_DestroyChn(0); //step.4 détruire channel 0
 * if (ret < 0) {
 * printf("FrameSource_DestroyChn error\n");
 * return destorychn_err;
 * }
 * @endcode
 * Pour plus de méthodes d'utilisation, veuillez vous référer à Samples
 * @{
 */

/**
* Structure de personnalisation des canaux 
*/
typedef struct {
	int enable;		/**< Activer la fonction de recadrage */
	int left;		/**< Recadrer le point de départ à gauche */
	int top;		/**< Point de départ */
	int width;		/**< Largeur de recadrage de l'image */
	int height;		/**< Hauteur de recadrage de l'image */
} IMPFSChnCrop;

/**
* Structure de zoom de canal 
*/
typedef struct {
	int enable;		/**< Activer la fonction de zoom */
	int outwidth;	/**< Largeur de l'image après le zoom */
	int outheight;	/**< Hauteur de l'image après le zoom */
} IMPFSChnScaler;

typedef enum {
	FS_PHY_CHANNEL,			/**< Canal physique */
	FS_EXT_CHANNEL,			/**< Élargir la cha je ne */
} IMPFSChnType;

/**
* rayon FIFO Types de 
*/
typedef enum {
	FIFO_CACHE_PRIORITY = 0,	/**< FIFO Cache prioritaire ， Puis sortez les données */
	FIFO_DATA_PRIORITY,			/**< FIFO Données de sortie prioritaires ， Puis cache */
} IMPFSChnFifoType;

/**
* rayon FIFO Structure d'attribut 
*/
typedef struct {
	int maxdepth;				/**< FIFO Profondeur maximale */
	IMPFSChnFifoType type;			/**< rayon FIFO Types de */
} IMPFSChnFifoAttr;

/**
 * Structure d'attribut de canal 
 */
typedef struct {
	int picWidth;				/**< Largeur de l'image */
	int picHeight;				/**< Hauteur de l'image */
	IMPPixelFormat pixFmt;		/**< Format d'image */
	IMPFSChnCrop crop;			/**< Attributs de recadrage d'image */
	IMPFSChnScaler scaler;		/**< Attribut de zoom d'image */
	int outFrmRateNum;			/**< Le numérateur de la fréquence d'images de sortie du canal */
	int outFrmRateDen;			/**< Dénominateur de la fréquence d'images de sortie du canal */
	int nrVBs;					/**< Video buffer Quantité */
	IMPFSChnType type;			/**< Type de canal */
} IMPFSChnAttr;

/**
 * @fn int IMP_FrameSource_CreateChn(int chnNum, IMPFSChnAttr *chnAttr)
 *
 * Créer une cha je ne 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[in] chnAttr Pointeur de structure d'attribut de canal 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Créer une cha je ne ， Fournir des sources de données pour les modules back-end ; \n
 * Vous pouvez définir les attributs pertinents du canal ， Inclure: largeur de l'image ， Hauteur de l'image ， Format d'image ， La fréquence d'images de sortie du canal , Cache buf numéro ， Attributs de recadrage et de zoom. \n
 * pour T10， rayon 0 [[[ 1 Ne peut être défini que comme canal physique ， rayon 2,3 Peut uniquement être défini comme canal d'extension. 
 *
 * @attention non. 
 */
int IMP_FrameSource_CreateChn(int chnNum, IMPFSChnAttr *chn_attr);

/**
 * @fn IMP_FrameSource_DestroyChn(int chnNum)
 *
 * Détruire le canal 
 *
 * @param[in] chnNum Le numéro de canal 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Détruire le canal 
 *
 * @attention Si le programme a appelé IMP_FrameSource_EnableChn， Doit appeler IMP_FrameSource_DisableChn après ， Utilisez à nouveau cette fonction. 
 */
int IMP_FrameSource_DestroyChn(int chnNum);

/**
 * @fn int IMP_FrameSource_EnableChn(int chnNum)
 *
 * Activer le canal 
 *
 * @param[in] chnNum Le numéro de canal 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non 
 *
 * @attention Avant d'utiliser cette fonction ， Il faut s'assurer que le canal activé a été créé .
 */
int IMP_FrameSource_EnableChn(int chnNum);

/**
 * @fn int IMP_FrameSource_DisableChn(int chnNum)
 *
 * Fermer la cha je ne 
 *
 * @param[in] chnNum Le numéro de canal 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non 
 *
 * @attention non 
 */
int IMP_FrameSource_DisableChn(int chnNum);

/**
 * @fn int IMP_FrameSource_GetChnAttr(int chnNum, IMPFSChnAttr *chnAttr)
 *
 * Obtenir les propriétés de la cha je ne 
 *
 * @param[in] chnNum Le numéro de canal 
 *
 * @param[out] chnAttr Pointeur de structure d'attribut de canal 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Obtenez les attributs pertinents de la cha je ne ， Inclure: largeur de l'image ， Hauteur de l'image ， Format d'image ， La fréquence d'images de sortie du canal , Cache buf numéro ， Propriétés de recadrage et de zoom .
 *
 * @attention non 
 */
int IMP_FrameSource_GetChnAttr(int chnNum, IMPFSChnAttr *chnAttr);

/**
 * @fn int IMP_FrameSource_SetChnAttr(int chnNum, const IMPFSChnAttr *chnAttr)
 *
 * Définir les propriétés du canal 
 *
 * @param[in] chnNum Le numéro de canal 
 *
 * @param[in] chnAttr Pointeur de structure d'attribut de canal 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark Vous pouvez définir les attributs pertinents du canal ， Inclure: largeur de l'image ， Hauteur de l'image ， Format d'image ， La fréquence d'images de sortie du canal , Cache buf numéro ， Propriétés de recadrage et de zoom .
 *
 * @attention non 
 */
int IMP_FrameSource_SetChnAttr(int chnNum, const IMPFSChnAttr *chnAttr);

/**
 * @fn IMP_FrameSource_SetFrameDepth(int chnNum, int depth)
 *
 * Définissez la profondeur maximale de l'image pouvant être obtenue 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[in] depth Définissez la valeur de profondeur maximale de l'image pouvant être obtenue 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark
 *
 * 1. Cette interface est utilisée pour définir le nombre d'images vidéo mises en mémoire tampon dans un canal. ， L'utilisateur peut obtenir un certain nombre de données d'image en continu. 
 *
 * 2. Si spécifié depth pour 0， Indique que le système n'a pas besoin de mettre en cache les images pour ce canal ， Par conséquent, l'utilisateur ne peut pas obtenir les données d'image du canal. ， lequel est depth La valeur par défaut est 0 . 
 *
 * 3. Le système mettra automatiquement à jour les données d'image les plus anciennes ， Pour s'assurer qu'une fois que les utilisateurs commencent à ， Vous pouvez obtenir l'image la plus récente. 
 *
 * 4. Le système arrête automatiquement de mettre en cache les nouvelles images car il ne peut pas obtenir d'images ， L'utilisateur ne peut pas non plus obtenir de nouvelles images. 
 *
 * 5. Le système mettra automatiquement à jour les données d'image les plus anciennes que l'utilisateur n'a pas encore acquises ， Assurez-vous que la file d'attente d'images mises en cache est la dernière image. ， L'image résultante peut ne pas être continue. 
 *
 * 6. Cette fonction peut appeler la localisation ， Il n'y a aucune exigence. 
 *
 * @attention non .
 */
int IMP_FrameSource_SetFrameDepth(int chnNum, int depth);

/**
 * @fn IMP_FrameSource_GetFrameDepth(int chnNum, int *depth);
 *
 * Profondeur maximale de l'image acquise 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[out] depth La valeur de profondeur maximale de l'image acquise 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non .
 *
 * @attention non .
 */
int IMP_FrameSource_GetFrameDepth(int chnNum, int *depth);

/**
 * @fn IMP_FrameSource_GetFrame(int chnNum, IMPFrameInfo **frame);
 *
 * Image acquise 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[out] frame Image acquise 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark
 *
 * 1. Cette interface peut obtenir les informations d'image vidéo du canal spécifié. 
 *
 * 2. Cette interface n'est valide qu'après activation du canal. 
 *
 * 3. Prend en charge plusieurs acquisitions, puis libère ， Cependant, il est recommandé que l'interface d'acquisition et de libération soit associée pour l'utilisation. 
 *
 * 4. Le délai d'expiration par défaut de cette interface est 2s， lequel est 2s Je n'ai toujours pas l'image à l'intérieur ， Le délai d'expiration revient. 
 *
 * @attention non .
 */
int IMP_FrameSource_GetFrame(int chnNum, IMPFrameInfo **frame);

/**
 * @fn IMP_FrameSource_GetTimedFrame(int chnNum, IMPFrameTimestamp *framets, int block, void *framedata, IMPFrameInfo *frame);
 *
 * Obtenir l'image à l'heure spécifiée 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[in] framets Informations sur l'heure 
 * @param[in] block Propriétés de blocage 
 * @param[in] framedata Copiez le pointeur mémoire de l'image 
 * @param[in] frame Obtenir des informations sur l'image 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark
 *
 * 1. Cette interface peut obtenir les informations d'image vidéo du canal spécifié à l'heure spécifiée. 
 *
 * 2. Cette interface n'est valide qu'après activation du canal. 
 *
 * 3. Cette interface doit d'abord être configurée IMP_FrameSource_SetMaxDelay avec IMP_FrameSource_SetDelay . 
 *
 * @attention non .
 */
int IMP_FrameSource_GetTimedFrame(int chnNum, IMPFrameTimestamp *framets, int block, void *framedata, IMPFrameInfo *frame);

/**
 * @fn IMP_FrameSource_ReleaseFrame(int chnNum, IMPFrameInfo *frame);
 *
 * Libérer l'image acquise 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[in] frame Libérer l'image acquise 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non .
 *
 * @attention non .
 */
int IMP_FrameSource_ReleaseFrame(int chnNum, IMPFrameInfo *frame);

/**
 * @fn IMP_FrameSource_SnapFrame(int chnNum, IMPPixelFormat fmt, int width, int height, void *framedata, IMPFrameInfo *frame);
 *
 * Obtenir une image 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[in] fmt Format d'image 
 * @param[in] width Largeur de l'image 
 * @param[in] height Hauteur de l'image 
 * @param[in] framedata Copiez le pointeur mémoire de l'image 
 * @param[in] frame Obtenir des informations sur l'image 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark
 *
 * 1. Cette interface peut obtenir une trame d'images dans un format et une taille spécifiés; le format actuel prend en charge NV12，YUYV422 ; La taille est la même que la résolution du canal; pas besoin d'appeler IMP_FrameSource_SetFrameDepth interface .
 *
 * 2. Cette interface n'est valide qu'après activation du canal. 
 *
 *
 * @attention non .
 */
int IMP_FrameSource_SnapFrame(int chnNum, IMPPixelFormat fmt, int width, int height, void *framedata, IMPFrameInfo *frame);

/**
 * @fn IMP_FrameSource_SetMaxDelay(int chnNum, int maxcnt);
 *
 * Définir le numéro de trame de retard maximum 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[in] maxcnt Délai maximum ， Cadre de l'unité 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non .
 *
 * @attention Lors de son utilisation, vous devez utiliser la fonction IMP_FrameSource_CreateChn contre IMP_FrameSource_EnableChn Appeler entre .
 */
int IMP_FrameSource_SetMaxDelay(int chnNum, int maxcnt);

/**
 * @fn IMP_FrameSource_GetMaxDelay(int chnNum, int *maxcnt);
 *
 * Obtenez le nombre maximum d'images retardées 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[out] maxcnt Délai maximum ， Cadre de l'unité 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non .
 *
 * @attention Lors de son utilisation, vous devez utiliser la fonction IMP_FrameSource_CreateChn après .
 */
int IMP_FrameSource_GetMaxDelay(int chnNum, int *maxcnt);

/**
 * @fn IMP_FrameSource_SetDelay(int chnNum, int cnt);
 *
 * Définir le nombre d'images retardées 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[in] cnt retard ， Cadre de l'unité 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non .
 *
 * @attention Lors de son utilisation, vous devez utiliser la fonction IMP_FrameSource_SetMaxDelay Appeler après .
 */
int IMP_FrameSource_SetDelay(int chnNum, int cnt);

/**
 * @fn IMP_FrameSource_GetDelay(int chnNum, int *cnt);
 *
 * Obtenez le nombre d'images retardées 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[out] cnt retard ， Cadre de l'unité 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non .
 *
 * @attention Lors de son utilisation, vous devez utiliser la fonction IMP_FrameSource_CreateChn après .
 */
int IMP_FrameSource_GetDelay(int chnNum, int *cnt);

/**
 * @fn IMP_FrameSource_SetChnFifoAttr(int chnNum, IMPFSChnFifoAttr *attr);
 *
 * Définir la mémoire tampon maximale du canal FIFO Les attributs 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[in] attr	FIFO Les attributs ， comprendre FIFO Profondeur maximale ， Cadre de l'unité FIFO Types de .
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non .
 *
 * @attention Lors de son utilisation, vous devez utiliser la fonction IMP_FrameSource_CreateChn contre IMP_FrameSource_EnableChn Appeler entre .
 */
int IMP_FrameSource_SetChnFifoAttr(int chnNum, IMPFSChnFifoAttr *attr);

/**
 * @fn IMP_FrameSource_GetChnFifoAttr(int chnNum, IMPFSChnFifoAttr *attr);
 *
 * Obtenir le tampon maximal du canal FIFO Les attributs 
 *
 * @param[in] chnNum Le numéro de canal 
 * @param[out] attr	FIFO Les attributs .
 *
 * @retval 0 Succès 
 * @retval non- 0 échec ， Renvoyer le code d'erreur 
 *
 * @remark non .
 *
 * @attention Lors de son utilisation, vous devez utiliser la fonction IMP_FrameSource_CreateChn après .
 */
int IMP_FrameSource_GetChnFifoAttr(int chnNum, IMPFSChnFifoAttr *attr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

/**
 * @}
 */

#endif /* __IMP_FRAMESOURCE_H__ */
