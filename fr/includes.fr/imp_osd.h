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
 * @brief OSD Module ， Peut superposer des images, des bitmaps, des lignes droites, des boîtes rectangulaires sur le flux vidéo 
 *
 * @section osd_summary 1  Présentation du module 
 * OSD Le nom complet est On-Screen Display . La fonction du module est de superposer des informations telles que des lignes et des images dans chaque source de film. 
 *
 * @section osd_concept 2  Concepts associés 
 * @subsection osd_region 2.1 Region
 * Region Est-ce que la zone superposée ， dans API Abréviation chinoise Rgn . Chaque Region Avoir certaines informations sur l'image ， Peut passer OSD Une fois les modules superposés ， Combiné avec l'image d'arrière-plan dans une image. 
 *  Pour la superposition d'image ， Peut également être réalisé Alpha effet. Pour une présentation détaillée des différents types de superposition, veuillez consulter @ref osd_region_type . 
 *
 * @subsection osd_region_type 2.1 Region type
 * Region Il existe plusieurs types ， Elles sont: \n
 * OSD_REG_LINE :ligne droite \n
 * OSD_REG_RECT :Rectangle \n
 * OSD_REG_BITMAP : bitmap \n
 * OSD_REG_COVER : Occlusion \n
 * OSD_REG_PIC :image \n
 *  parmi eux ， La différence entre le bitmap et l'image est ， Bitmap n'effectue qu'une couverture monochrome des pixels ， Et l'image est RGBA Image Alpha Recouvrir. 
 *
 * @section osd_fun 3  Fonction du module 
 * OSD Le module prend en charge les lignes, les boîtes rectangulaires, la superposition bitmap, l'occlusion rectangulaire et la superposition d'image. 
 *  Les lignes, les boîtes rectangulaires et les bitmaps sont implémentés par logiciel; l'occlusion rectangulaire et les superpositions d'images sont implémentées par le matériel. 
 *
 * @section osd_use 4  Utilisation du module 
 * OSD L'utilisation de comporte généralement les étapes suivantes 
 * 1.  créer OSD grouper 
 * 2.  Lier OSD Regrouper dans le système 
 * 3.  Regrouper dans le système OSD surface 
 * 4.  inscrit OSD Zone à OSD Dans le groupe 
 * 5.  Installation OSD Attributs de zone de groupe et attributs de zone 
 * 6.  Attributs de zone de groupe et attributs de zone OSD Commutateur de fonction 
 * @{
 */

/**
 *  Valeur de retour d'erreur 
 */
#define INVHANDLE		(-1)

/**
 * OSD  Poignée de zone 
 */
typedef int IMPRgnHandle;

/**
 * OSD Type de couleur ， Le format de couleur est bgra
 */
typedef enum {
	OSD_BLACK	= 0xff000000, /**<  noir  */
	OSD_WHITE	= 0xffffffff, /**<  blanc  */
	OSD_RED		= 0xffff0000, /**<  rouge  */
	OSD_GREEN	= 0xff00ff00, /**<  vert  */
	OSD_BLUE	= 0xff0000ff, /**<  bleu  */
}IMPOsdColour;

/**
 * OSD Type de zone 
 */
typedef enum {
	OSD_REG_INV			= 0, /**<  Type de zone non défini  */
	OSD_REG_LINE		= 1, /**<  ligne  */
	OSD_REG_RECT		= 2, /**<  rectangle  */
	OSD_REG_BITMAP		= 3, /**<  Bitmap  */
	OSD_REG_COVER		= 4, /**<  Occlusion rectangulaire  */
	OSD_REG_PIC			= 5, /**<  image ， Convient pour une utilisation comme Logo Ou horodatage  */
} IMPOsdRgnType;

/**
 * OSD Données de ligne de surface et de rectangle 
 */
typedef struct {
	uint32_t		color;			/**<  Couleur ， Supporte uniquement OSD_WHITE，OSD_BLACK，OSD_RED Trois formats  */
	uint32_t		linewidth;		/**<  Largeur de ligne  */
} lineRectData;

/**
 * OSD Données d'occlusion de zone 
 */
typedef struct {
	uint32_t		color;			/**<  Données d'occlusion de zone ， Données d'occlusion de zone bgra Format de couleur  */
} coverData;


/**
 * OSD Données d'image régionales 
 */
typedef struct {
	void				*pData;			/**<  Pointeur de données d'image  */
} picData;

/**
 * OSD Données d'attribut de zone 
 */
typedef union {
	void				*bitmapData;		/**<  Données de matrice de points  */
	lineRectData			lineRectData;		/**<  Données de ligne et de rectangle  */
	coverData			coverData;		/**<  Données d'occlusion  */
	picData				picData;		/**<  Données d'image  */
} IMPOSDRgnAttrData;

/**
 * OSD Attributs de zone 
 */
typedef struct {
	IMPOsdRgnType		type;			/**< OSD Attributs de zone  */
	IMPRect				rect;			/**<  Données rectangulaires  */
	IMPPixelFormat		fmt;			/**<  Format de point  */
	IMPOSDRgnAttrData	data;			/**< OSD Format de point  */
} IMPOSDRgnAttr;

/**
 * OSD Attributs de zone de groupe 
 */
typedef struct {
	int					show;			/**<  Que ce soit pour montrer  */
	IMPPoint			offPos;			/**<  Afficher les coordonnées de départ  */
	float				scalex;			/**<  Zoom x paramètre  */
	float				scaley;			/**<  paramètre y paramètre  */
	int					gAlphaEn;		/**< Alpha changer  */
	int					fgAlhpa;		/**<  perspective Alpha */
	int					bgAlhpa;		/**<  Contexte Alpha */
	int					layer;			/**<  Afficher la couche  */
} IMPOSDGrpRgnAttr;


/**
 * @fn int IMP_OSD_CreateGroup(int grpNum)
 *
 *  Afficher la couche OSD Afficher la couche 
 *
 * @param[in] grpNum OSD No de groupe , Gammes : [0, @ref NR_MAX_OSD_GROUPS - 1]
 *
 * @retval 0  Succès 
 * @retval  non- 0  échec 
 *
 * @remarks  non. 
 *
 * @attention  non. 
 */
int IMP_OSD_CreateGroup(int grpNum);

/**
 * @fn int IMP_OSD_DestroyGroup(int grpNum)
 *
 *  détruire OSD détruire 
 *
 * @param[in] grpNum OSD détruire , détruire : [0, @ref NR_MAX_OSD_GROUPS - 1]
 *
 * @retval 0  détruire 
 * @retval  détruire 0  détruire 
 *
 * @remarks  Appelle ça API Il est nécessaire que le groupe correspondant ait été créé. 
 *
 * @attention  Il est nécessaire que le groupe correspondant ait été créé. 
 */
int IMP_OSD_DestroyGroup(int grpNum);

/**
 * @fn int IMP_OSD_AttachToGroup(IMPCell *from, IMPCell *to)
 *
 *  volonté OSD Groupe ajouté au système 
 *
 * @param[in] from OSD unité 
 * @param[in] to  Autres unités du système 
 *
 * @retval 0  Autres unités du système 
 * @retval  Autres unités du système 0  Autres unités du système 
 *
 * @remarks  Nouvelle version SDK Recommandé dans Bind Le chemin sera OSD Chaîne au flux de données du système ，Attach N'est plus recommandé ， mais API Garder ， Idéalement compatible avec les versions précédentes du logiciel. 
 *  Pour plus de détails, veuillez consulter @ref bind  Exemple de 
 *
 * @attention  Exemple de 
 */
int IMP_OSD_AttachToGroup(IMPCell *from, IMPCell *to);

/**
 * @fn IMPRgnHandle IMP_OSD_CreateRgn(IMPOSDRgnAttr *prAttr)
 *
 *  Exemple de OSD Exemple de 
 *
 * @param[in] prAttr OSD Exemple de 
 *
 * @retval  supérieur ou égal à 0  supérieur ou égal à 
 * @retval  Moins que 0  Moins que 
 *
 * @remarks  Moins que 
 *
 * @attention  Moins que 
 */
IMPRgnHandle IMP_OSD_CreateRgn(IMPOSDRgnAttr *prAttr);

/**
 * @fn void IMP_OSD_DestroyRgn(IMPRgnHandle handle)
 *
 *  Moins que OSD Moins que 
 *
 * @param[in] prAttr  Moins que ，IMP_OSD_CreateRgn La valeur de retour 
 *
 * @retval  non 
 *
 * @remarks  non 
 *
 * @attention  non 
 */
void IMP_OSD_DestroyRgn(IMPRgnHandle handle);

/**
 * @fn int IMP_OSD_RegisterRgn(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 *  non OSD non 
 *
 * @param[in] handle  non ，IMP_OSD_CreateRgn non 
 * @param[in] grpNum OSD non 
 * @param[in] pgrAttr OSD Attributs d'affichage de groupe 
 *
 * @retval 0  Attributs d'affichage de groupe 
 * @retval  Attributs d'affichage de groupe 0  Attributs d'affichage de groupe 
 *
 * @remarks  Attributs d'affichage de groupe API Lors de la demande du correspondant OSD Le groupe a été créé. 
 *
 * @attention  Le groupe a été créé. 
 */
int IMP_OSD_RegisterRgn(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_UnRegisterRgn(IMPRgnHandle handle, int grpNum)
 *
 *  Se déconnecter OSD Se déconnecter 
 *
 * @param[in] handle  Se déconnecter ，IMP_OSD_CreateRgn Se déconnecter 
 * @param[in] grpNum OSD Se déconnecter 
 *
 * @retval 0  Se déconnecter 
 * @retval  Se déconnecter 0  Se déconnecter 
 *
 * @remarks  Se déconnecter API Se déconnecter OSD Le groupe a été créé , La zone correspondante a été enregistrée. 
 *
 * @attention  La zone correspondante a été enregistrée. 
 */
int IMP_OSD_UnRegisterRgn(IMPRgnHandle handle, int grpNum);

/**
 * @fn int IMP_OSD_SetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr)
 *
 *  Définir les propriétés de la zone 
 *
 * @param[in] handle  Définir les propriétés de la zone ，IMP_OSD_CreateRgn Définir les propriétés de la zone 
 * @param[in] prAttr OSD Définir les propriétés de la zone 
 *
 * @retval 0  Définir les propriétés de la zone 
 * @retval  Définir les propriétés de la zone 0  Définir les propriétés de la zone 
 *
 * @remarks  Définir les propriétés de la zone API Il est nécessaire que la zone correspondante ait été créée. 
 *
 * @attention  Il est nécessaire que la zone correspondante ait été créée. 
 */
int IMP_OSD_SetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr);

/**
 * @fn int IMP_OSD_GetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr)
 *
 *  Obtenir des attributs de zone 
 *
 * @param[in] handle  Obtenir des attributs de zone ，IMP_OSD_CreateRgn Obtenir des attributs de zone 
 * @param[out] prAttr OSD Obtenir des attributs de zone 
 *
 * @retval 0  Obtenir des attributs de zone 
 * @retval  Obtenir des attributs de zone 0  Obtenir des attributs de zone 
 *
 * @remarks  Obtenir des attributs de zone API Obtenir des attributs de zone 
 *
 * @attention  Obtenir des attributs de zone 
 */
int IMP_OSD_GetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr);

/**
 * @fn int IMP_OSD_UpdateRgnAttrData(IMPRgnHandle handle, IMPOSDRgnAttrData *prAttrData)
 *
 *  Mettre à jour les attributs de données de zone ， Seulement pour OSD_REG_BITMAP avec OSD_REG_PIC Type de zone 
 *
 * @param[in] handle  Type de zone ，IMP_OSD_CreateRgn Type de zone 
 * @param[in] prAttrData OSD Attributs de données de zone 
 *
 * @retval 0  Attributs de données de zone 
 * @retval  Attributs de données de zone 0  Attributs de données de zone 
 *
 * @remarks  Attributs de données de zone API Il faut que la zone correspondante ait été créée et que l'attribut de zone ait été défini sur OSD_REG_BITMAP ou OSD_REG_PIC ou 
 *
 * @attention  ou 
 */
int IMP_OSD_UpdateRgnAttrData(IMPRgnHandle handle, IMPOSDRgnAttrData *prAttrData);

/**
 * @fn int IMP_OSD_SetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 *  ou OSD ou 
 *
 * @param[in] handle  ou ，IMP_OSD_CreateRgn ou 
 * @param[in] grpNum OSD ou 
 * @param[in] pgrAttr OSD ou 
 *
 * @retval 0  ou 
 * @retval  ou 0  ou 
 *
 * @remarks  ou API ou OSD ou , La zone a été créée et enregistrée. 
 *
 * @attention  La zone a été créée et enregistrée. 
 */
int IMP_OSD_SetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_GetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 *  Obtenir OSD Obtenir 
 *
 * @param[in] handle  Obtenir ，IMP_OSD_CreateRgn Obtenir 
 * @param[in] grpNum OSD Obtenir 
 * @param[out] pgrAttr OSD Obtenir 
 *
 * @retval 0  Obtenir 
 * @retval  Obtenir 0  Obtenir 
 *
 * @remarks  Obtenir API Obtenir OSD Obtenir , Obtenir 
 *
 * @attention  Obtenir 
 */
int IMP_OSD_GetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_ShowRgn(IMPRgnHandle handle, int grpNum, int showFlag)
 *
 *  Définir s'il faut afficher la zone de groupe 
 *
 * @param[in] handle  Définir s'il faut afficher la zone de groupe ，IMP_OSD_CreateRgn Définir s'il faut afficher la zone de groupe 
 * @param[in] grpNum OSD Définir s'il faut afficher la zone de groupe 
 * @param[in] showFlag OSD Commutateur d'affichage de la zone de groupe 
 *
 * @retval 0  Commutateur d'affichage de la zone de groupe 
 * @retval  Commutateur d'affichage de la zone de groupe 0  Commutateur d'affichage de la zone de groupe 
 *
 * @remarks  Commutateur d'affichage de la zone de groupe API Commutateur d'affichage de la zone de groupe OSD Commutateur d'affichage de la zone de groupe , Commutateur d'affichage de la zone de groupe 
 *
 * @attention  Commutateur d'affichage de la zone de groupe 
 */
int IMP_OSD_ShowRgn(IMPRgnHandle handle, int grpNum, int showFlag);

/**
 * @fn int IMP_OSD_Start(int grpNum)
 *
 *  Installation OSD Affichage de groupe 
 *
 * @param[in] grpNum OSD Affichage de groupe 
 *
 * @retval 0  Affichage de groupe 
 * @retval  Affichage de groupe 0  Affichage de groupe 
 *
 * @remarks  Affichage de groupe API Affichage de groupe OSD Affichage de groupe 
 *
 * @attention  Affichage de groupe 
 */
int IMP_OSD_Start(int grpNum);

/**
 * @fn int IMP_OSD_Stop(int grpNum)
 *
 *  Définir l'arrêt OSD Définir l'arrêt 
 *
 * @param[in] grpNum OSD Définir l'arrêt 
 *
 * @retval 0  Définir l'arrêt 
 * @retval  Définir l'arrêt 0  Définir l'arrêt 
 *
 * @remarks  Définir l'arrêt API Définir l'arrêt OSD Définir l'arrêt 
 *
 * @attention  Définir l'arrêt 
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
