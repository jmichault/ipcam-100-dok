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
 * @ingroup lutin
 * @brief La source vidéo est la source de données d'image du système IMP. La résolution d'image, le recadrage, la mise à l'échelle et d'autres attributs peuvent être définis, ainsi que la fonction de réduction du bruit d'arrière-plan
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
	FS_EXT_CHANNEL,			/**< Élargir la cha î ne */
} IMPFSChnType;

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
 * @fn int IMP_FrameSource_CreateChn (int chnNum, IMPFSChnAttr * chnAttr)
 *
 * Créer une cha î ne 
 *
 * @param[in] chnNum numéro de canal
 * @param[in] chnAttr Pointeur de structure d'attribut de canal
 *
 * @retval 0 succès
 * @retval Échec différent de zéro, retour du code d'erreur
 *
 * @remark Créez un canal pour fournir une source de données pour le module principal; 
 * Vous pouvez définir les attributs pertinents du canal ， Inclure: largeur de l'image ， Picture height ， Image Format ， La fréquence d'images de sortie du canal , Cache buf numéro ， Attributs de recadrage et de zoom. \n
 * pour T10， rayon 0 [[[ 1 Ne peut être défini que comme canal physique ， aisle 2,3 Peut uniquement être défini comme canal d'extension. 
 *
 * @attention non.
 */
int IMP_FrameSource_CreateChn(int chnNum, IMPFSChnAttr *chn_attr);

/**
 * @fn IMP_FrameSource_DestroyChn (int chnNum)
 *
 * Détruire le canal 
 *
 * @param[in] chnNum Channel number 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Détruire le canal
 *
 * @attention Si le programme a appelé IMP_FrameSource_EnableChn, vous devez appeler IMP_FrameSource_DisableChn avant d'utiliser cette fonction.
 */
int IMP_FrameSource_DestroyChn(int chnNum);

/**
 * @fn int IMP_FrameSource_EnableChn (int chnNum)
 *
 * Activer le canal 
 *
 * @param[in] chnNum Channel number 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark non
 *
 * @attention Avant d'utiliser cette fonction, vous devez vous assurer que le canal activé a été créé.
 */
int IMP_FrameSource_EnableChn(int chnNum);

/**
 * @fn int IMP_FrameSource_DisableChn (int chnNum)
 *
 * Fermer la cha î ne 
 *
 * @param[in] chnNum Channel number 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no 
 *
 * @attention no 
 */
int IMP_FrameSource_DisableChn(int chnNum);

/**
 * @fn int IMP_FrameSource_GetChnAttr (int chnNum, IMPFSChnAttr * chnAttr)
 *
 * Obtenir les propriétés de la cha î ne 
 *
 * @param[in] chnNum Channel number 
 *
 * @param[out] chnAttr Channel attribute structure pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Les attributs pertinents du canal peuvent être obtenus, notamment: la largeur de l'image, la hauteur de l'image, le format de l'image, la fréquence d'images de sortie du canal, le nombre de tampons tampons, les attributs de rognage et de mise à l'échelle.
 *
 * @attention no 
 */
int IMP_FrameSource_GetChnAttr(int chnNum, IMPFSChnAttr *chnAttr);

/**
 * @fn int IMP_FrameSource_SetChnAttr (int chnNum, const IMPFSChnAttr * chnAttr)
 *
 * Définir les propriétés du canal 
 *
 * @param[in] chnNum Channel number 
 *
 * @param[in] chnAttr Channel attribute structure pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark Vous pouvez définir les attributs pertinents du canal, notamment: la largeur de l'image, la hauteur de l'image, le format de l'image, la fréquence d'images de sortie du canal, le numéro de tampon du tampon, les attributs de recadrage et de zoom.
 *
 * @attention no 
 */
int IMP_FrameSource_SetChnAttr(int chnNum, const IMPFSChnAttr *chnAttr);

/**
 * @fn IMP_FrameSource_SetFrameDepth (int chnNum, int depth)
 *
 * Définissez la profondeur maximale de l'image pouvant être obtenue 
 *
 * @param[in] chnNum numéro de canal
 * @param[in] profondeur Définit la valeur de profondeur maximale de l'image pouvant être obtenue
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
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
 * @attention non.
 */
int IMP_FrameSource_SetFrameDepth(int chnNum, int depth);

/**
 * @fn IMP_FrameSource_GetFrameDepth (int chnNum, int * profondeur);
 *
 * Profondeur maximale de l'image acquise 
 *
 * @param[in] chnNum Channel number 
 * @param[out] profondeur La valeur de profondeur maximale de l'image obtenue
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no .
 *
 * @attention no .
 */
int IMP_FrameSource_GetFrameDepth(int chnNum, int *depth);

/**
 * @fn IMP_FrameSource_GetFrame (int chnNum, IMPFrameInfo ** frame);
 *
 * Image acquise 
 *
 * @param[in] chnNum Channel number 
 * @param[out] image capturée par cadre
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark 
 *
 * 1. Cette interface peut obtenir les informations d'image vidéo du canal spécifié. 
 *
 * 2. Cette interface n'est valide qu'après activation du canal. 
 *
 * 3. Prend en charge plusieurs acquisitions, puis libère ， Cependant, il est recommandé de coupler les interfaces d'acquisition et de libération. 
 *
 * 4. Le délai d'expiration par défaut de cette interface est 2s， which is 2s Je n'ai toujours pas l'image à l'intérieur ， Le délai d'expiration revient. 
 *
 * @attention no .
 */
int IMP_FrameSource_GetFrame(int chnNum, IMPFrameInfo **frame);

/**
 * @fn IMP_FrameSource_ReleaseFrame (int chnNum, IMPFrameInfo * frame);
 *
 * Libérer l'image acquise 
 *
 * @param[in] chnNum Channel number 
 * @param[in] le cadre libère l'image acquise
 *
 * @retval 0 success 
 * @retval non- 0 failure ， Return error code 
 *
 * @remark no .
 *
 * @attention no .
 */
int IMP_FrameSource_ReleaseFrame(int chnNum, IMPFrameInfo *frame);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

/**
 * @}
 */

#endif /* __IMP_FRAMESOURCE_H__ */
