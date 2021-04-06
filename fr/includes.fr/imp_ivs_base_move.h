/*
 * IMP IVS Move func header file.
 *
 * Copyright (C) 2016 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_IVS_BASE_MOVE_H__
#define __IMP_IVS_BASE_MOVE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define IMP_IVS_MOVE_MAX_ROI_CNT		16

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
 * Structure d'entrée de l'algorithme de détection de mouvement de base 
 */
typedef struct {
	int skipFrameCnt; /*< Nombre de détections toutes les deux images */
	int referenceNum; /*< Spécifiez la position par rapport à l'image actuelle -referenceNum Cadre de référence */
	int sadMode; /*< SAD mode ,0 Moyens 8*8*/
	int sense; /*< Sensibilité ,0-3, Plus la valeur est élevée, plus la sensibilité est grande */
	IMPFrameInfo frameInfo; /**< Informations sur la taille du cadre , Juste besoin de configurer width avec height */

} IMP_IVS_BaseMoveParam;

/*
 * Structure de sortie de l'algorithme de détection de mouvement de base 
 */
typedef struct {
	int ret;
	uint8_t* data;
	int datalen;
} IMP_IVS_BaseMoveOutput;

/**
 * Créer des ressources d'interface de détection de mouvement 
 *
 * @fn IMPIVSInterface *IMP_IVS_CreateBaseMoveInterface(IMP_IVS_BaseMoveParam *param);
 *
 * @param[in] param Paramètres de structure d'entrée de l'algorithme de détection de mouvement 
 *
 * @retval non- NULL Succès , Renvoie la poignée du pointeur de l'interface de l'algorithme de détection de mouvement 
 * @retval NULL échec 
 *
 * @attention non 
 */
IMPIVSInterface *IMP_IVS_CreateBaseMoveInterface(IMP_IVS_BaseMoveParam *param);

/**
 * Détruire les ressources de l'interface de détection de mouvement 
 *
 * @fn void IMP_IVS_DestroyBaseMoveInterface(IMPIVSInterface *moveInterface);
 *
 * @param[in] moveInterface Poignée de pointeur d'interface d'algorithme de détection de mouvement 
 *
 * @retval Aucune valeur de retour 
 *
 * @attention non 
 */
void IMP_IVS_DestroyBaseMoveInterface(IMPIVSInterface *moveInterface);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __IMP_IVS_MOVE_H__ */
