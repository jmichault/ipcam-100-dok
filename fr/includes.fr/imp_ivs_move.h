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

#define IMP_IVS_MOVE_MAX_ROI_CNT		52

#include <imp/imp_ivs.h>

/**
 * @file
 * IMP IVS Module de détection de mouvement 
 */

/**
 * @defgroup MoveDetection
 * @ingroup IMP_IVS
 * @brief Interface de détection de mouvement 
 * @{
 */

/**
 * Structure d'entrée de l'algorithme de détection de mouvement 
 */
typedef struct {
	int sense[IMP_IVS_MOVE_MAX_ROI_CNT]; /**< Sensibilité de la détection de mouvement , La portée normale de la caméra est 0-4， La portée de la caméra panoramique est 0-8 */
	int skipFrameCnt; /*< Nombre de détections toutes les deux images */
	IMPFrameInfo frameInfo; /**< Informations sur la taille du cadre , Juste besoin de configurer width avec height */
	IMPRect roiRect[IMP_IVS_MOVE_MAX_ROI_CNT]; /*< Besoin d'être détecté roi Informations de coordonnées de zone */
	int roiRectCnt; /*< Besoin d'être détecté roi Nombre de régions ， La plage est 0-51， Si 0 : Pas de détection ，1 : Détection roiRect 0
														 surface ，2 , Détection roiRect 0,1 surface ，3 , Détection roiRect 0,1,2 surface ， Etc */
} IMP_IVS_MoveParam;

/*
 * La structure de sortie de l'algorithme de détection de mouvement 
 */
typedef struct {
	int retRoi[IMP_IVS_MOVE_MAX_ROI_CNT];				/*< Résultat du mouvement de détection de zone ， contre roiRect Correspond strictement aux informations de coordonnées ,0: Indique qu'aucun mouvement n'a été détecté ，1 : Indique qu'un mouvement est détecté */
} IMP_IVS_MoveOutput;

/**
 * Créer des ressources d'interface de détection de mouvement 
 *
 * @fn IMPIVSInterface *IMP_IVS_CreateMoveInterface(IMP_IVS_MoveParam *param);
 *
 * @param[in] param Paramètres de structure d'entrée de l'algorithme de détection de mouvement 
 *
 * @retval non- NULL Succès , Renvoie la poignée du pointeur de l'interface de l'algorithme de détection de mouvement 
 * @retval NULL échec 
 *
 * @attention non 
 */
IMPIVSInterface *IMP_IVS_CreateMoveInterface(IMP_IVS_MoveParam *param);

/**
 * Détruire les ressources de l'interface de détection de mouvement 
 *
 * @fn void IMP_IVS_DestroyMoveInterface(IMPIVSInterface *moveInterface);
 *
 * @param[in] moveInterface Poignée de pointeur d'interface d'algorithme de détection de mouvement 
 *
 * @retval Aucune valeur de retour 
 *
 * @attention non 
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
