/*
 * IMP IVS Move func header file.
 *
 * Copyright (C) 2016 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_IVS_MOVE_H__
#define __IMP_IVS_MOVE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define IMP_IVS_MOVE_MAX_ROI_CNT		4

#include <imp/imp_ivs.h>

/**
 * @file
 * IMP IVS  Module de détection de mouvement 
 */

/**
 * @defgroup MoveDetection
 * @ingroup IMP_IVS
 * @brief  Interface de détection de mouvement 
 * @{
 */

/**
 *  Structure d'entrée de l'algorithme de détection de mouvement 
 */
typedef struct {
	int             sense[IMP_IVS_MOVE_MAX_ROI_CNT];   /**<  Sensibilité de la détection de mouvement ， La plage est 0-4 */
	int             skipFrameCnt;                      /*<  Nombre de détections toutes les deux images  */
	IMPFrameInfo    frameInfo;                         /**<  Informations sur la taille du cadre , Juste besoin de configurer width avec height */
	IMPRect         roiRect[IMP_IVS_MOVE_MAX_ROI_CNT]; /*<  Besoin d'être détecté roi Informations de coordonnées de zone  */
	int             roiRectCnt;                        /*<  Informations de coordonnées de zone roi Nombre de régions ， Nombre de régions 0-4， Si 0 : Pas de détection ，1 : Détection roiRect 0
														  surface ，2 , Détection roiRect 0,1 , Détection ，3 , Détection roiRect 0,1,2 , Détection ， Etc  */
} IMP_IVS_MoveParam;
// I suppose it has something to do with this sequence of bytes which is located in appfs/etc/sensor/jxf22move.txt:
	// 50 50 14 26 05 2b 3c 96 28 73 14 32 0f 28

/*
 *  La structure de sortie de l'algorithme de détection de mouvement 
 */
typedef struct {
	int retRoi[IMP_IVS_MOVE_MAX_ROI_CNT];				/*<  Résultat du mouvement de détection de zone ， contre roiRect Correspond strictement aux informations de coordonnées  */
} IMP_IVS_MoveOutput;

/**
 *  Créer des ressources d'interface de détection de mouvement 
 *
 * @fn IMPIVSInterface *IMP_IVS_CreateMoveInterface(IMP_IVS_MoveParam *param);
 *
 * @param[in] param  Paramètres de structure d'entrée de l'algorithme de détection de mouvement 
 *
 * @retval  non- NULL  Succès , Renvoie la poignée du pointeur de l'interface de l'algorithme de détection de mouvement 
 * @retval NULL  échec 
 *
 * @attention  non 
 */
IMPIVSInterface *IMP_IVS_CreateMoveInterface(IMP_IVS_MoveParam *param);

/**
 *  Détruire les ressources de l'interface de détection de mouvement 
 *
 * @fn void IMP_IVS_DestroyMoveInterface(IMPIVSInterface *moveInterface);
 *
 * @param[in] moveInterface  Poignée de pointeur d'interface d'algorithme de détection de mouvement 
 *
 * @retval  Aucune valeur de retour 
 *
 * @attention  Aucune valeur de retour 
 */
void IMP_IVS_DestroyMoveInterface(IMPIVSInterface *moveInterface);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __IMP_IVS_MOVE_H__ */
