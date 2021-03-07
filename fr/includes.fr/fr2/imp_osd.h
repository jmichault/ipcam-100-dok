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
 * @ingroup lutin
 * @brief Module OSD, peut superposer des images, des bitmaps, des lignes droites et des bo je tes rectangulaires sur le flux vidéo
 *
 * @section Présentation du module osd_summary 1
 * OSD Le nom complet est On-Screen Display . 
 *
 * @section osd_concept 2 concepts associés
 * @subsection Région osd_region 2.1
 * Region Est-ce que la zone superposée ， dans API Abréviation chinoise Rgn . Region Avoir certaines informations sur l'image ， Peut passer OSD Une fois les modules superposés ， Combiné avec l'image d'arrière-plan dans une image. 
 * Pour la superposition d'image ， Peut également être réalisé Alpha effet. @ref osd_region_type . 
 *
 * @subsection osd_region_type 2.1 Type de région
 * Region Il existe plusieurs types ， Elles sont: \n
 * OSD_REG_LINE :ligne droite \n
 * OSD_REG_RECT :Rectangle \n
 * OSD_REG_BITMAP : bitmap \n
 * OSD_REG_COVER : Occlusion \n
 * OSD_REG_PIC :image \n
 * parmi eux ， La différence entre le bitmap et l'image est ， Bitmap n'effectue qu'une couverture monochrome des pixels ， Et l'image est RGBA Image Alpha Recouvrir. 
 *
 * @section Fonction du module osd_fun 3
 * OSD Le module prend en charge les lignes, les bo je tes rectangulaires, la superposition bitmap, l'occlusion rectangulaire et la superposition d'image. 
 * Les lignes, les bo je tes rectangulaires et les bitmaps sont implémentés par logiciel; l'occlusion rectangulaire et la superposition d'image sont implémentées par le matériel. 
 *
 * @section Utilisation du module osd_use 4
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
 * @fn int IMP_OSD_CreateGroup (int grpNum)
 *
 * créer OSD grouper 
 *
 * @param[in] grpNum Numéro de groupe OSD, plage de valeurs: [0, @ref NR_MAX_OSD_GROUPS-1]
 *
 * @retval 0 succès
 * @retval Échec non nul
 *
 * @remarks non.
 *
 * @attention non. 
 */
int IMP_OSD_CreateGroup(int grpNum);

/**
 * @fn int IMP_OSD_DestroyGroup (int grpNum)
 *
 * détruire OSD grouper 
 *
 * @param[in] grpNum OSD No de groupe , Gammes : [0, @ref NR_MAX_OSD_GROUPS - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Lors de l'appel de cette API, le groupe correspondant doit avoir été créé.
 *
 * @attention non. 
 */
int IMP_OSD_DestroyGroup(int grpNum);

/**
 * @fn int IMP_OSD_AttachToGroup (IMPCell * de, IMPCell * à)
 *
 * volonté OSD Groupe ajouté au système 
 *
 * @param[in] depuis l'unité OSD
 * @param[in] vers d'autres unités du système
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Dans la nouvelle version du SDK, il est recommandé d'utiliser Bind pour insérer l'OSD dans le flux de données du système. La méthode Attach n'est plus recommandée, mais l'API est réservée à la compatibilité avec les versions précédentes du logiciel.
 * Pour plus de détails, veuillez consulter @ref bind Exemple de 
 *
 * @attention non. 
 */
int IMP_OSD_AttachToGroup(IMPCell *from, IMPCell *to);

/**
 * @fn IMPRgnHandle IMP_OSD_CreateRgn (IMPOSDRgnAttr * prAttr)
 *
 * créer OSD surface 
 *
 * @param[in] Attributs de la zone OSD prAttr
 *
 * @retval Succès supérieur ou égal à 0
 * @retval Moins de 0 a échoué
 *
 * @remarks non. 
 *
 * @attention non. 
 */
IMPRgnHandle IMP_OSD_CreateRgn(IMPOSDRgnAttr *prAttr);

/**
 * @fn void IMP_OSD_DestroyRgn (poignée IMPRgnHandle)
 *
 * détruire OSD surface 
 *
 * @param[in] Poignée de zone prAttr, valeur de retour de IMP_OSD_CreateRgn
 *
 * @retval non
 *
 * @remarks non. 
 *
 * @attention non. 
 */
void IMP_OSD_DestroyRgn(IMPRgnHandle handle);

/**
 * @fn int IMP_OSD_RegisterRgn (poignée IMPRgnHandle, int grpNum, IMPOSDGrpRgnAttr * pgrAttr)
 *
 * inscrit OSD surface 
 *
 * @param[in] handle de zone, valeur de retour de IMP_OSD_CreateRgn
 * @param[in] grpNum Numéro de groupe OSD
 * @param[in] Attributs d'affichage du groupe OSD pgrAttr
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Lors de l'appel de cette API, le groupe OSD correspondant doit avoir été créé.
 *
 * @attention non. 
 */
int IMP_OSD_RegisterRgn(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_UnRegisterRgn (poignée IMPRgnHandle, int grpNum)
 *
 * Se déconnecter OSD surface 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] grpNum OSD No de groupe 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Lors de l'appel de cette API, il est nécessaire que le groupe OSD correspondant ait été créé et que la zone correspondante ait été enregistrée.
 *
 * @attention non. 
 */
int IMP_OSD_UnRegisterRgn(IMPRgnHandle handle, int grpNum);

/**
 * @fn int IMP_OSD_SetRgnAttr (poignée IMPRgnHandle, IMPOSDRgnAttr * prAttr)
 *
 * Définir les propriétés de la zone 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] prAttr OSD Attributs de zone 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Lors de l'appel de cette API, la zone correspondante doit avoir été créée.
 *
 * @attention non. 
 */
int IMP_OSD_SetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr);

/**
 * @fn int IMP_OSD_GetRgnAttr (poignée IMPRgnHandle, IMPOSDRgnAttr * prAttr)
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
 * @fn int IMP_OSD_UpdateRgnAttrData (poignée IMPRgnHandle, IMPOSDRgnAttrData * prAttrData)
 *
 * Mettre à jour les attributs de données de zone ， Seulement pour OSD_REG_BITMAP avec OSD_REG_PIC Type de zone 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] Attributs de données de la zone OSD prAttrData
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Lors de l'appel de cette API, il est nécessaire que la zone correspondante ait été créée et que l'attribut de zone ait été défini sur OSD_REG_BITMAP ou OSD_REG_PIC.
 *
 * @attention non. 
 */
int IMP_OSD_UpdateRgnAttrData(IMPRgnHandle handle, IMPOSDRgnAttrData *prAttrData);

/**
 * @fn int IMP_OSD_SetGrpRgnAttr (poignée IMPRgnHandle, int grpNum, IMPOSDGrpRgnAttr * pgrAttr)
 *
 * Installation OSD Attributs de zone de groupe 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] grpNum OSD No de groupe 
 * @param[in] Attributs de zone de groupe OSD pgrAttr
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Lors de l'appel de cette API, le groupe OSD correspondant doit avoir été créé et la zone doit avoir été créée et enregistrée.
 *
 * @attention non. 
 */
int IMP_OSD_SetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_GetGrpRgnAttr (poignée IMPRgnHandle, int grpNum, IMPOSDGrpRgnAttr * pgrAttr)
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
 * @fn int IMP_OSD_ShowRgn (poignée IMPRgnHandle, int grpNum, int showFlag)
 *
 * Définir s'il faut afficher la zone de groupe 
 *
 * @param[in] handle Poignée de zone ，IMP_OSD_CreateRgn La valeur de retour 
 * @param[in] grpNum OSD No de groupe 
 * @param[in] Commutateur d'affichage de la zone de groupe OSD showFlag
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
 * @fn int IMP_OSD_Start (int grpNum)
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
 * @fn int IMP_OSD_Stop (int grpNum)
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
