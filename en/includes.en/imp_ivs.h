/*
 * IMP IVS header file.
 *
 * Copyright (C) 2015 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_IVS_H__
#define __IMP_IVS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#include <imp/imp_common.h>

/**
 * @file
 * IMP IVS Module 
 */

#define IMP_IVS_DEFAULT_TIMEOUTMS		(-1)

/**
 * @defgroup IMP_IVS
 * @ingroup imp
 * @brief IVS Interface universelle d'analyse intelligente API
 *
 * @section concept 1  Concepts associés 
 * IMP IVS  par IVS Interface universelle API Appel instancié IMPIVSInterface Pour intégrer des algorithmes d'analyse intelligents dans SDK Analyse entrante SDK milieu frame image. 
 *
 * @subsection IMPIVSInterface 1.1 IMPIVSInterface
 * IMPIVSInterface  Interface d'algorithme général ， L'algorithme spécifique implémente cette interface et la transmet à IMP IVS Atteindre à SDK Le but de l'exécution d'algorithmes spécifiques dans. \n
 *  Une channel Il n'y a et il n'y a qu'un transporteur pour une seule instance d'algorithme ， L'implémentation spécifique de l'interface de l'algorithme général doit être transmise au channel Capacité à SDK Exécutez l'algorithme dans. 	\n
 * IMPIVSInterface  membre param Fonction membre init Paramètres.  \n
 * IMP_IVS Sera passé à la fonction membre ProcessAsync Paramétrique frame Verrou externe ，ProcessAsync Doit être épuisé frame Appeler après IMP_IVS_ReleaseData libéré frame， Afin d'éviter une impasse. 
 *
 * @section ivs_usage 2  Instructions 
 *  Prenons l'exemple de l'algorithme de détection de mouvement ， Voir l'implémentation spécifique de la fonction sample-move_c.c déposer \n
 * step.1  Initialiser le système ， Vous pouvez appeler directement l'exemple sample_system_init() fonction. \n
 *  L'application entière ne peut initialiser le système qu'une seule fois ， Si initialisé avant ， Il n'est pas nécessaire de réinitialiser à nouveau. \n
 * step.2  initialisation framesource \n
 *  Si l'algorithme utilisé framesource Chaîne créée ， Utilisez simplement le canal créé directement. \n
 *  Utilisez simplement le canal créé directement. framesource Chaîne non créée ， Vous pouvez appeler le sample_framesource_init(IVS_FS_CHN, &fs_chn_attr) Créez-le. \n
 * step.3  créer ivs Groupe de canaux d'algorithme spécifique. \n
 *  Plusieurs algorithmes peuvent partager un groupe de canaux ， Vous pouvez également utiliser des groupes de canaux séparément ， Pièces spécifiques sample_ivs_move_init() \n
 * @code
 * int sample_ivs_move_init(int grp_num)
 * {
 *  	int ret = 0;
 *
 *		ret = IMP_IVS_CreateGroup(grp_num);
 *		if (ret < 0) {
 *			IMP_LOG_ERR(TAG, "IMP_IVS_CreateGroup(%d) failed\n", grp_num);
 *			return -1;
 *		}
 *		return 0;
 * }
 * @endcode
 * step.4  Lier le groupe de canaux de l'algorithme et framesource Groupe de canaux 
 * @code
 *	IMPCell framesource_cell = {DEV_ID_FS, IVS_FS_CHN, 0};
 *	IMPCell ivs_cell = {DEV_ID_IVS, 0, 0};
 *	ret = IMP_System_Bind(&framesource_cell, &ivs_cell);
 *	if (ret < 0) {
 *		IMP_LOG_ERR(TAG, "Bind FrameSource channel%d and ivs0 failed\n", IVS_FS_CHN);
 *		return -1;
 *	}
 * @endcode
 * step.5  Commencez framesource Et algorithme. Il est recommandé que le numéro de canal de l'algorithme soit le même ， Pour qu'il puisse correspondre directement à quel algorithme fonctionne actuellement. 
 * @code
 *	IMP_FrameSource_SetFrameDepth(0, 0);
 *	ret = sample_framesource_streamon(IVS_FS_CHN);
 *	if (ret < 0) {
 *		IMP_LOG_ERR(TAG, "ImpStreamOn failed\n");
 *		return -1;
 *	}
 *	ret = sample_ivs_move_start(0, 0, &inteface);
 *	if (ret < 0) {
 *		IMP_LOG_ERR(TAG, "sample_ivs_move_start(0, 0) failed\n");
 *		return -1;
 *	}
 * @endcode
 *
 * step.6  Obtenir les résultats de l'algorithme  \n
 * Polling Les résultats, les résultats d'acquisition et les résultats de diffusion doivent correspondre strictement ， Pas d'interruption ;
 *  seul Polling Le résultat est renvoyé correctement ， Les résultats obtenus seront mis à jour ， Sinon, les résultats obtenus sont imprévisibles. 
 * @code
 *	for (i = 0; i < NR_FRAMES_TO_IVS; i++) {
 *		ret = IMP_IVS_PollingResult(0, IMP_IVS_DEFAULT_TIMEOUTMS);
 *		if (ret < 0) {
 *			IMP_LOG_ERR(TAG, "IMP_IVS_PollingResult(%d, %d) failed\n", 0, IMP_IVS_DEFAULT_TIMEOUTMS);
 *			return -1;
 *		}
 *		ret = IMP_IVS_GetResult(0, (void **)&result);
 *		if (ret < 0) {
 *			IMP_LOG_ERR(TAG, "IMP_IVS_GetResult(%d) failed\n", 0);
 *			return -1;
 *		}
 *		IMP_LOG_INFO(TAG, "frame[%d], result->ret=%d\n", i, result->ret);
 *
 *		ret = IMP_IVS_ReleaseResult(0, (void *)result);
 *		if (ret < 0) {
 *			IMP_LOG_ERR(TAG, "IMP_IVS_ReleaseResult(%d) failed\n", 0);
 *			return -1;
 *		}
 *	}
 * @endcode
 * step.7  Libérer les ressources 
 * @code
 *  sample_ivs_move_stop(0, inteface);
 *  sample_framesource_streamoff(1);
 *  IMP_System_UnBind(&framesource_cell, &ivs_cell);
 *  sample_ivs_move_exit(0);
 *  sample_framesource_exit(IVS_FS_CHN);
 *  sample_system_exit();
 * @endcode
 * @{
 */

/**
 * ivs  Interface commune 
 */
typedef struct {
	void  *param;                             /**<  Paramètres d'entrée  */
	int   paramSize;                          /**<  Taille de l'espace des paramètres  */
	IMPPixelFormat pixfmt;                    /**<  L'algorithme nécessite un format de données  */
	int  (*init)(void *param);                /**<  Fonction d'initialisation  */
	void (*exit)(void);                       /**<  Fonction de déconnexion  */
	int  (*PreprocessSync)(IMPFrameInfo *frame);/**<  Fonction de prétraitement ， valeur de retour: 0->frame Pas free,1->frame Déjà free;-1-> Erreur ,frame Erreur free */
	int  (*ProcessAsync)(IMPFrameInfo *frame);/**<  Fonction de traitement , Doit s'assurer que chaque frame Dans free statut , valeur de retour :0-> Le test réel revient normalement ,1-> La détection de saut de trame revient normalement ,-1-> La détection de saut de trame revient normalement  */
	int  (*GetResult)(void **result);         /**<  Obtenir des ressources sur les résultats  */
	int  (*ReleaseResult)(void *result);      /**<  Libérer les ressources de résultats  */
	int	 (*GetParam)(void *param);            /**<  Obtenir les paramètres de l'algorithme  */
	int	 (*SetParam)(void *param);            /**<  Définir les paramètres de l'algorithme  */
	int	 (*FlushFrame)(void);                 /**<  Libération par l'extérieur ProcessAsync Tous mis en cache après l'entrée dans l'algorithme frame */
} IMPIVSInterface;

/**
 *  Créer un groupe de canaux 
 *
 * @fn int IMP_IVS_CreateGroup(int GrpNum);
 *
 * @param[in] GrpNum IVS Numéro de groupe de canaux correspondant à la fonction 
 *
 * @retval 0  Succès 
 * @retval -1  échec 
 *
 * @remark  non 
 *
 * @attention  non 
 */
int IMP_IVS_CreateGroup(int GrpNum);

/**
 *  Détruire le groupe de canaux 
 *
 * @fn int IMP_IVS_DestroyGroup(int GrpNum);
 *
 * @param[in] GrpNum IVS Détruire le groupe de canaux 
 *
 * @retval 0  Détruire le groupe de canaux 
 * @retval -1  Détruire le groupe de canaux 
 *
 * @remark  Détruire le groupe de canaux 
 *
 * @attention  Détruire le groupe de canaux 
 */
int IMP_IVS_DestroyGroup(int GrpNum);
/**
 *  Détruire le groupe de canaux IVS Fonction canal correspondant 
 *
 * @fn int IMP_IVS_CreateChn(int ChnNum, IMPIVSInterface *handler);
 *
 * @param[in] ChnNum  Le numéro de canal 
 *
 * @param[in] handler IVS Poignée de fonction 
 *
 * @retval 0  Poignée de fonction 
 * @retval -1  Poignée de fonction 
 *
 * @remark  Poignée de fonction .
 *
 * @attention  Poignée de fonction 
 */
int IMP_IVS_CreateChn(int ChnNum, IMPIVSInterface *handler);

/**
 *  détruire IVS Le canal correspondant à la poignée de fonction 
 *
 * @fn int IMP_IVS_DestroyChn(int ChnNum);
 *
 * @param[in] ChnNum  Le canal correspondant à la poignée de fonction 
 *
 * @retval 0  Le canal correspondant à la poignée de fonction 
 * @retval -1  Le canal correspondant à la poignée de fonction 
 *
 * @remark  Le canal correspondant à la poignée de fonction 
 *
 * @attention  Le canal correspondant à la poignée de fonction 
 */
int IMP_IVS_DestroyChn(int ChnNum);

/**
 *  Enregistrer la chaîne dans le groupe de chaînes 
 *
 * @fn int IMP_IVS_RegisterChn(int GrpNum, int ChnNum);
 *
 * @param[in] GrpNum IVS Enregistrer la chaîne dans le groupe de chaînes 
 *
 * @param[in] ChnNum IVS Numéro de canal correspondant à la fonction 
 *
 * @retval 0  Numéro de canal correspondant à la fonction 
 * @retval -1  Numéro de canal correspondant à la fonction 
 *
 * @remark  Sera numéroté Chnnum Le canal enregistré sous le numéro est Grpnum Groupe de canaux 
 *
 * @attention  Groupe de canaux 
 */
int IMP_IVS_RegisterChn(int GrpNum, int ChnNum);

/**
 *  Annuler la chaîne du groupe de chaînes 
 *
 * @fn int IMP_IVS_UnRegisterChn(int ChnNum);
 *
 * @param[in] ChnNum IVS Annuler la chaîne du groupe de chaînes 
 *
 * @retval 0  Annuler la chaîne du groupe de chaînes 
 * @retval -1  Annuler la chaîne du groupe de chaînes 
 *
 * @remark  Le nombre mineur est Grpnum Le numéro de déconnexion dans le groupe de canaux est Chnnum rayon 
 *
 * @attention  rayon 
 */
int IMP_IVS_UnRegisterChn(int ChnNum);

/**
 *  La chaîne commence à recevoir des images 
 *
 * @fn int IMP_IVS_StartRecvPic(int ChnNum);
 *
 * @param[in] ChnNum  La chaîne commence à recevoir des images 
 *
 * @retval 0  La chaîne commence à recevoir des images 
 * @retval -1  La chaîne commence à recevoir des images 
 *
 * @remark  Le numéro de canal est Chnnum de IVS Le canal de fonction commence à recevoir des images pour une analyse intelligente 
 *
 * @attention  Le canal de fonction commence à recevoir des images pour une analyse intelligente 
 */
int IMP_IVS_StartRecvPic(int ChnNum);

/**
 *  La chaîne cesse de recevoir des images 
 *
 * @fn int IMP_IVS_StopRecvPic(int ChnNum);
 *
 * @param[in] ChnNum  La chaîne cesse de recevoir des images 
 *
 * @retval 0  La chaîne cesse de recevoir des images 
 * @retval -1  La chaîne cesse de recevoir des images 
 *
 * @remark  La chaîne cesse de recevoir des images Chnnum La chaîne cesse de recevoir des images IVS Le canal de fonction cesse de recevoir des images ， Suspendre l'analyse intelligente 
 *
 * @attention  Suspendre l'analyse intelligente 
 */
int IMP_IVS_StopRecvPic(int ChnNum);

/**
 *  Blocage pour déterminer s'il peut être obtenu IVS Résultat d'analyse intelligent calculé par fonction 
 *
 * @fn int IMP_IVS_PollingResult(int ChnNum, int timeoutMs);
 *
 * @param[in] ChnNum IVS Résultat d'analyse intelligent calculé par fonction 
 *
 * @param[in] timeout  Temps d'attente maximum ， unité ms; IMP_IVS_DEFAULT_TIMEOUTMS: Temps d'attente par défaut dans la bibliothèque ,0: N'attends pas ,>0: Temps d'attente défini par l'utilisateur 
 *
 * @retval 0  Temps d'attente défini par l'utilisateur 
 * @retval -1  Temps d'attente défini par l'utilisateur 
 *
 * @remark  Seuls les paramètres lors de la création du canal IMPIVSInterface Structure ProcessAsync Retour du membre de fonction 0 Temps ， Autrement dit, lorsque le test réel revient normalement ， ce Polling La fonction renvoie le succès 
 *
 * @attention  La fonction renvoie le succès 
 */
int IMP_IVS_PollingResult(int ChnNum, int timeoutMs);

/**
 *  obtenir IVS Résultat d'analyse intelligent calculé par fonction 
 *
 * @fn int IMP_IVS_GetResult(int ChnNum, void **result);
 *
 * @param[in] ChnNum IVS Résultat d'analyse intelligent calculé par fonction 
 *
 * @param[in] result IVS Le résultat de sortie du numéro de canal correspondant à la fonction ， Renvoie le pointeur de résultat de l'algorithme d'analyse intelligente correspondant à ce canal ， Les clients externes n'ont pas besoin d'allouer d'espace. 
 *
 * @retval 0  Les clients externes n'ont pas besoin d'allouer d'espace. 
 * @retval -1  Les clients externes n'ont pas besoin d'allouer d'espace. 
 *
 * @remark  Selon différents IVS Canal lié fonctionnellement , Sortir le résultat correspondant .
 *
 * @attention  Sortir le résultat correspondant 
 */
int IMP_IVS_GetResult(int ChnNum, void **result);

/**
 *  Sortir le résultat correspondant IVS Ressource de résultat calculée par fonction 
 *
 * @fn int IMP_IVS_ReleaseResult(int ChnNum, void *result);
 *
 * @param[in] GrpNum  Numéro de groupe de canaux 
 *
 * @param[in] ChnNum IVS Numéro de groupe de canaux 
 *
 * @param[in] result IVS Numéro de groupe de canaux 
 *
 * @retval 0  Numéro de groupe de canaux 
 * @retval -1  Numéro de groupe de canaux 
 *
 * @remark  Numéro de groupe de canaux IVS Numéro de groupe de canaux , Libérer ses ressources de résultat de sortie .
 *
 * @attention  Libérer ses ressources de résultat de sortie 
 */
int IMP_IVS_ReleaseResult(int ChnNum, void *result);

/**
 *  Relâchez à Datacallback Paramètres frame
 *
 * @fn int IMP_IVS_ReleaseData(void *vaddr);
 *
 * @param[in] vaddr  Adresse virtuelle de l'espace libéré 
 *
 * @retval 0  Adresse virtuelle de l'espace libéré 
 * @retval -1  Adresse virtuelle de l'espace libéré 
 *
 * @remark  Doit utiliser cette fonction pour libérer la passe à Datacallback Doit utiliser cette fonction pour libérer la passe à frame paramètre ， Sinon, cela entraînera certainement une impasse. 
 * @remark  Cette interface est réservée aux fournisseurs d'algorithmes ， Les clients n'ont pas besoin de prêter attention à l'utilisation d'algorithmes. 
 *
 * @attention  Les clients n'ont pas besoin de prêter attention à l'utilisation d'algorithmes. 
 */
int IMP_IVS_ReleaseData(void *vaddr);

/**
 *  Obtenir les paramètres d'algorithme de canal 
 *
 * @fn int IMP_IVS_GetParam(int chnNum, void *param);
 *
 * @param[in] ChnNum IVS Obtenir les paramètres d'algorithme de canal 
 * @param[in] param  Pointeur d'adresse virtuelle de paramètre d'algorithme 
 *
 * @retval 0  Pointeur d'adresse virtuelle de paramètre d'algorithme 
 * @retval -1  Pointeur d'adresse virtuelle de paramètre d'algorithme 
 *
 * @attention  Pointeur d'adresse virtuelle de paramètre d'algorithme 
 */
int IMP_IVS_GetParam(int chnNum, void *param);

/**
 *  Définir les paramètres de l'algorithme de canal 
 *
 * @fn int IMP_IVS_SetParam(int chnNum, void *param);
 *
 * @param[in] ChnNum IVS Définir les paramètres de l'algorithme de canal 
 * @param[in] param  Définir les paramètres de l'algorithme de canal 
 *
 * @retval 0  Définir les paramètres de l'algorithme de canal 
 * @retval -1  Définir les paramètres de l'algorithme de canal 
 *
 * @attention  Définir les paramètres de l'algorithme de canal 
 */
int IMP_IVS_SetParam(int chnNum, void *param);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_IVS_H__ */
