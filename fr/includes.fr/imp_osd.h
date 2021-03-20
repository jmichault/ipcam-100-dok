/*
 * IMP OSD header file.
 *
 * Copyright (C) 2015 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_OSD_H__
#define __IMP_OSD_H__

#include "imp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */
/**
 * @file
 * IMP OSD Fichier d'en-tête du module 
 */


/**
 * @defgroup IMP_OSD
 * @ingroup imp
 * @brief OSD Module ， Peut superposer des images, des bitmaps, des lignes droites et des cadres rectangulaires sur le flux vidéo 
 *
 * @section osd_summary 1 Présentation du module 
 * OSD Le nom complet est On-Screen Display . 
 *
 * @section osd_concept 2 Concepts associés 
 * @subsection osd_region 2.1 Region
 * Region Est-ce que la zone superposée ， dans API Abréviation chinoise Rgn . Region Avoir certaines informations sur l'image ， Peut passer OSD Une fois les modules superposés ， Combiné avec l'image d'arrière-plan dans une image. 
 * Pour la superposition d'image ， Peut également être réalisé Alpha effet. @ref osd_region_type . 
 *
 * @subsection osd_region_type 2.1 Region type
 * Region Il existe plusieurs types ， Elles sont: \n
 * OSD_REG_LINE :ligne droite \n
 * OSD_REG_RECT :Rectangle \n
 * OSD_REG_BITMAP : bitmap \n
 * OSD_REG_COVER : Occlusion \n
 * OSD_REG_PIC :image \n
 * parmi eux ， La différence entre le bitmap et l'image est ， Bitmap n'effectue qu'une couverture monochrome des pixels ， Et l'image est RGBA Image Alpha Recouvrir. 
 *
 * @section osd_fun 3 Fonction du module 
 * OSD Le module prend en charge les lignes, les bo je tes rectangulaires, la superposition bitmap, l'occlusion rectangulaire et la superposition d'image. 
 * Les lignes, les bo je tes rectangulaires et les bitmaps sont implémentés par logiciel; l'occlusion rectangulaire et les superpositions d'images sont implémentées par le matériel. 
 *
 * @section osd_use 4 Utilisation du module 
 * OSD L'utilisation de comporte généralement les étapes suivantes 
 * 1. créer OSD grouper 
 * 2. Lier OSD Regrouper dans le système 
 * 3. créer OSD surface 
 * 4. inscrit OSD Zone à OSD Dans le groupe 
 * 5. Installation OSD Attributs de zone de groupe et attributs de zone 
 * 6. Installation OSD Commutateur de fonction 
 * @{
 */

/**
 * Valeur de retour d'erreur 
 */
#define INVHANDLE		(-1)

/**
 * OSD Poignée de zone 
 */
typedef int IMPRgnHandle;

/**
 * OSD Type de couleur ， Le format de couleur est bgra
 */
typedef enum {
	OSD_BLACK	= 0xff000000, /**< noir */
	OSD_WHITE	= 0xffffffff, /**< blanc */
	OSD_RED		= 0xffff0000, /**< rouge */
	OSD_GREEN	= 0xff00ff00, /**< vert */
	OSD_BLUE	= 0xff0000ff, /**< bleu */
}IMPOsdColour;

/**
 * OSD Type de zone 
 */
typedef enum {
	OSD_REG_INV			= 0, /**< Type de zone non défini */
	OSD_REG_LINE		= 1, /**< ligne */
	OSD_REG_RECT		= 2, /**< rectangle */
	OSD_REG_BITMAP		= 3, /**< Bitmap */
	OSD_REG_COVER		= 4, /**< Occlusion rectangulaire */
	OSD_REG_PIC			= 5, /**< image ， Convient pour une utilisation comme Logo Ou horodatage */
} IMPOsdRgnType;

/**
 * OSD Données de ligne de surface et de rectangle 
 */
typedef struct {
	uint32_t		color;			/**< Couleur ， Supporte uniquement OSD_WHITE，OSD_BLACK，OSD_RED Trois formats */
	uint32_t		linewidth;		/**< Largeur de ligne */
} lineRectData;

/**
 * OSD Données d'occlusion de zone 
 */
typedef struct {
	uint32_t		color;			/**< Couleur ， Supporte uniquement bgra Format de couleur */
} coverData;


/**
 * OSD Données d'image régionales 
 */
typedef struct {
	void				*pData;			/**< Pointeur de données d'image */
} picData;

/**
 * OSD Données d'attribut de zone 
 */
typedef union {
	void				*bitmapData;		/**< Données de matrice de points */
	lineRectData			lineRectData;		/**< Données de ligne et de rectangle */
	coverData			coverData;		/**< Données d'occlusion */
	picData				picData;		/**< Données d'image */
} IMPOSDRgnAttrData;

/**
 * OSD Attributs de zone 
 */
typedef struct {
	IMPOsdRgnType		type;			/**< OSD Type de zone */
	IMPRect				rect;			/**< Données rectangulaires */
	IMPPixelFormat		fmt;			/**< Format de point */
	IMPOSDRgnAttrData	data;			/**< OSD Données d'attribut de zone */
} IMPOSDRgnAttr;

/**
 * OSD Horodatage effectif de la zone 
 */
typedef struct {
	uint64_t ts;						/**< Horodatage */
	uint64_t minus;						/**< Limite inférieure */
	uint64_t plus;						/**< Limite supérieure */
} IMPOSDRgnTimestamp;

/**
 * OSD Attributs de zone de groupe 
 */
typedef struct {
	int					show;			/**< Que ce soit pour montrer */
	IMPPoint			offPos;			/**< Afficher les coordonnées de départ */
	float				scalex;			/**< Zoom x paramètre */
	float				scaley;			/**< Zoom y paramètre */
	int					gAlphaEn;		/**< Alpha changer */
	int					fgAlhpa;		/**< perspective Alpha */
	int					bgAlhpa;		/**< Contexte Alpha */
	int					layer;			/**< Afficher la couche */
} IMPOSDGrpRgnAttr;


/**
 * @fn int IMP_OSD_CreateGroup(int grpNum)
 *
 * créer OSD grouper 
 *
 * @param[in] grpNum OSD No de groupe , Gammes : [0, @ref NR_MAX_OSD_GROUPS - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks non. 
 *
 * @attention non. 
 */
int IMP_OSD_CreateGroup(int grpNum);

/**
 * @fn int IMP_OSD_DestroyGroup(int grpNum)
 *
 * détruire OSD grouper 
 *
 * @param[in] grpNum OSD No de groupe , Gammes : [0, @ref NR_MAX_OSD_GROUPS - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Il est nécessaire que le groupe correspondant ait été créé. 
 *
 * @attention non. 
 */
int IMP_OSD_DestroyGroup(int grpNum);

/**
 * @fn int IMP_OSD_AttachToGroup(IMPCell *from, IMPCell *to)
 *
 * volonté OSD Groupe ajouté au système 
 *
 * @param[in] from OSD unité 
 * @param[in] to Autres unités du système 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Nouvelle version SDK Recommandé dans Bind Le chemin sera OSD Cha je ne au flux de données du système ，Attach N'est plus recommandé ， mais API Garder ， Idéalement compatible avec les versions précédentes du logiciel. 
 * Pour plus de détails, veuillez consulter @ref bind Exemple de 
 *
 * @attention non. 
 */
int IMP_OSD_AttachToGroup(IMPCell *from, IMPCell *to);

/**
 * @fn IMPRgnHandle IMP_OSD_CreateRgn(IMPOSDRgnAttr *prAttr)
 *
 * créer OSD surface 
 *
 * @param[in] prAttr OSD Attributs de zone 
 *
 * @retval supérieur ou égal à 0 Succès 
 * @retval Moins que 0 échec 
 *
 * @remarks non. 
 *
 * @attention non. 
 */
IMPRgnHandle IMP_OSD_CreateRgn(IMPOSDRgnAttr *prAttr);

/**
 * @fn void IMP_OSD_DestroyRgn(IMPRgnHandle handle)
 *
 * détruire OSD surface 
 *
 * @param[in] prAttr Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 *
 * @retval non 
 *
 * @remarks non. 
 *
 * @attention non. 
 */
void IMP_OSD_DestroyRgn(IMPRgnHandle handle);

/**
 * @fn int IMP_OSD_RegisterRgn(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 * inscrit OSD surface 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] grpNum OSD No de groupe 
 * @param[in] pgrAttr OSD Attributs d'affichage de groupe 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Lors de la demande du correspondant OSD Le groupe a été créé. 
 *
 * @attention non. 
 */
int IMP_OSD_RegisterRgn(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_UnRegisterRgn(IMPRgnHandle handle, int grpNum)
 *
 * Se déconnecter OSD surface 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] grpNum OSD No de groupe 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Lors de la demande du correspondant OSD Le groupe a été créé , La zone correspondante a été enregistrée. 
 *
 * @attention non. 
 */
int IMP_OSD_UnRegisterRgn(IMPRgnHandle handle, int grpNum);

/**
 * @fn int IMP_OSD_SetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr)
 *
 * Définir les propriétés de la zone 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] prAttr OSD Attributs de zone 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Il est nécessaire que la zone correspondante ait été créée. 
 *
 * @attention non. 
 */
int IMP_OSD_SetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr);

/**
 * @fn int IMP_OSD_SetRgnAttrWithTimestamp(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr, IMPOSDRgnTimestamp *prTs)
 *
 * Définir les attributs régionaux et l'heure effective 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] prAttr OSD Attributs de zone 
 * @param[in] prTs Temps effectif 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Il est nécessaire que la zone correspondante ait été créée. 
 *
 * @attention non. 
 */
int IMP_OSD_SetRgnAttrWithTimestamp(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr, IMPOSDRgnTimestamp *prTs);

/**
 * @fn int IMP_OSD_GetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr)
 *
 * Obtenir des attributs de zone 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[out] prAttr OSD Attributs de zone 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Il est nécessaire que la zone correspondante ait été créée. 
 *
 * @attention non. 
 */
int IMP_OSD_GetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr);

/**
 * @fn int IMP_OSD_UpdateRgnAttrData(IMPRgnHandle handle, IMPOSDRgnAttrData *prAttrData)
 *
 * Mettre à jour les attributs de données de zone ， Seulement pour OSD_REG_BITMAP avec OSD_REG_PIC Type de zone 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] prAttrData OSD Attributs de données de zone 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Il faut que la zone correspondante ait été créée et que l'attribut de zone ait été défini sur OSD_REG_BITMAP ou OSD_REG_PIC . 
 *
 * @attention non. 
 */
int IMP_OSD_UpdateRgnAttrData(IMPRgnHandle handle, IMPOSDRgnAttrData *prAttrData);

/**
 * @fn int IMP_OSD_SetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 * Installation OSD Attributs de zone de groupe 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] grpNum OSD No de groupe 
 * @param[in] pgrAttr OSD Attributs de zone de groupe 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Lors de la demande du correspondant OSD Le groupe a été créé , La zone a été créée et enregistrée. 
 *
 * @attention non. 
 */
int IMP_OSD_SetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_GetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 * Obtenir OSD Attributs de zone de groupe 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] grpNum OSD No de groupe 
 * @param[out] pgrAttr OSD Attributs de zone de groupe 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Lors de la demande du correspondant OSD Le groupe a été créé , La zone a été créée et enregistrée. 
 *
 * @attention non. 
 */
int IMP_OSD_GetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_ShowRgn(IMPRgnHandle handle, int grpNum, int showFlag)
 *
 * Définir s'il faut afficher la zone de groupe 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] grpNum OSD No de groupe 
 * @param[in] showFlag OSD Commutateur d'affichage de la zone de groupe 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Lors de la demande du correspondant OSD Le groupe a été créé , La zone a été créée et enregistrée. 
 *
 * @attention non. 
 */
int IMP_OSD_ShowRgn(IMPRgnHandle handle, int grpNum, int showFlag);

/**
 * @fn int IMP_OSD_Start(int grpNum)
 *
 * Installation OSD Affichage de groupe 
 *
 * @param[in] grpNum OSD No de groupe 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Lors de la demande du correspondant OSD Le groupe a été créé. 
 *
 * @attention non. 
 */
int IMP_OSD_Start(int grpNum);

/**
 * @fn int IMP_OSD_Stop(int grpNum)
 *
 * Définir l'arrêt OSD Affichage de groupe 
 *
 * @param[in] grpNum OSD No de groupe 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Appelle ça API Lors de la demande du correspondant OSD Le groupe a été créé. 
 *
 * @attention non. 
 */
int IMP_OSD_Stop(int grpNum);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_OSD_H__ */
