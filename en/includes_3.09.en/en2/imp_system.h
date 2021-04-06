/*
 * IMP System header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_SYSTEM_H__
#define __IMP_SYSTEM_H__

#include "imp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file 
 * IMP Fichier d'en-tête du module système 
 */

/**
 * @defgroup imp IMP (Plateforme Média Ingenic)
 */

/**
 * @defgroup IMP_System
 * @ingroup lutin
 * @brief Module de contrôle du système, y compris les fonctions de base d'IMP et les fonctions associées liées entre les modules
 * @section concepts liés au concept 1
 * Le contrôle du système réalise principalement la connexion de divers modules ， Définissez la fonction du flux de données. 
 *
 * @subsection appareil 1.1 Appareil
 * Device C'est une collection qui complète une certaine fonction (de classe). FrameSource Terminer la sortie des données de la source vidéo ，Encoder Remplissez la fonction de codage vidéo ou de codage d'image. FrameSource avec Encoder Seulement Device le concept de. \n
 * Device Juste un concept de collection ， Ce n'est pas un n œ ud de flux de données spécifique. 
 *
 * @subsection groupe 1.2 Groupe
 * Group C'est la plus petite unité d'entrée de données. Device Il peut y avoir plusieurs Group， Chaque Group Une seule entrée de données peut être reçue. Group Peut avoir plusieurs sorties ( @ref output ). \n
 * Group C'est aussi un conteneur pour des « fonctions » spécifiques ， Tu peux voir @ref channel Une partie de l'explication. 
 *
 * @subsection sortie 1.3 Sortie
 * Output Est un Group La plus petite unité de sortie de données pour un canal. Group There can be multiple Output， Each Output Un seul canal de données peut être émis. 
 *
 * @subsection cellule 1.4 Cellule
 * Cell Se réfère à contient Device [[[ Group [[[ Output Collecte d'informations. @ref IMPCell La structure des données est présentée. \n
 * Cell Principalement utilisé Bind ( @ref bind ). Device [[[ Group [[[ Output Définition ，Output En tant que n œ ud de sortie de données ， et Group En tant que n œ ud d'entrée de données. \n
 * dans Bind Noeud de sortie des données de temps Cell Index à la sortie Output， N œ ud de saisie de données Cell Index à saisir Group (Par conséquent, en tant qu'entrée de données Cell，Output Est une valeur dénuée de sens). 
 *
 * @subsection canal 1.5 canal
 * Channel Fait généralement référence à une seule unité fonctionnelle ，Channel in Create Temps ( Instancier ) Lorsque la fonction spécifique est attribuée. \n
 * Par exemple: \n
 * * pour Encoder， Une Channel Complétez le chemin H264 Code ou JPEG Fonction de codage ， Fonction de codage spécifique ( Types de ， paramètre ) Spécifié lors de la création du canal 
 * * for IVS， One Channel Compléter la fonction d'un algorithme spécifique ， Les paramètres de type d'algorithme spécifiques sont spécifiés lors de la création du canal 
 * * for OSD， Avoir le même Channel Concepts similaires Region， One Region Est une zone de superposition spécifique ， Peut être PIC( image )，COVER( Occlure ) Attendre 
 * * for FrameSource， One Channel Sortie d'une image originale ，FrameSource de Channel Est en fait Group
 *
 * Channel En tant qu'unité fonctionnelle ， ont généralement besoin Register À Group dans (FrameSource sauf )， Pour recevoir les données. Channel Inscrivez-vous à Group Milieu et arrière ， Aura Group Données saisies. \n
 * différent Device of Group peut Register of Channel Les chiffres sont également différents. 
 *
 * @section liaison de module 2 (Bind)
 * Deux Group après Bind Après connexion ， la source Group Les données seront automatiquement envoyées à la destination Group . \n
 * en raison de Group Est la plus petite unité d'entrée de données ，Output Est la plus petite unité de sortie de données ， donc IMP_System_Bind(IMPCell *srcCell, IMPCell *dstCell) Des deux paramètres srcCell of deviceID, groupID, outputID C'est vaild 
 * and dstCell seul deviceID with groupID efficace ，outputID Comme la saisie de données n'a pas de sens. \n
 * L'image ci-dessous est un simple Bind exemple de. 
 * @image html system_bind0.jpg
 * Dans l'image ci-dessus ， Atteint FrameSource Une sortie Bind To Encoder un des Group . 
 * in Encoder Group in Register J'en ai deux Channel， therefore Encoder Group Ont H264 with JPEG Deux sorties. 
 * Code de référence: 
 * @code 
 * IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};			//FrameSource deviceID:DEV_ID_FS groupID:0 outputID:0
 * IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0};		//ENC deviceID:DEV_ID_ENC groupID:0 outputID:0, Ici enc_grp0 Le troisième paramètre n'a pas de sens. 
 * int ret = IMP_System_Bind(&fs_chn0, &enc_grp0);
 * if (ret < 0)
 * printf("Bind FrameSource Channel0 and Encoder Group0 failed\n");
 * @endcode 
 * Bind Concaténer le flux de données du système ， Selon les différentes exigences fonctionnelles du produit ，Bind La stratégie peut également être différente. 
 *
 * Ce qui suit est une application de produit de flux de code à double canal typique Bind Diagramme schématique: 
 *
 * @image html typique_application.png
 *
 * Dans l'image ci-dessus ，FrameSource Il y a deux sorties ， Respectivement sont Channel0 Intégrer (1280x720) with Channel1 Flux esclave (640x360) . \n
 * * Intégrer: FrameSource of Channel0 Bind OSD Group.0，OSD Group.0 Bind Encoder Group.0 . 
 * * OSD Group.0 Enregistré deux Region， Utilisé pour afficher respectivement les informations d'horodatage et de cha î ne 
 * * Encoder Group.0 Registered two Channel， Séparément H264 Encodage et JPEG codage. JPEG Si la taille d'image du canal d'encodage n'est pas égale au réglage d'entrée ( FrameSource of Channel0 ) ， Ensuite, il zoomera (Software at T10)， Atteindre l'objectif de capturer n'importe quelle résolution 
 * * À partir du flux de code: FrameSource of Channel1 Bind IVS Group.0，IVS Group.0 Bind OSD Group.1，OSD Group.1 Bind Encoder Group.1 . 
 * * IVS Group.0 Enregistré un Channel， Utilisé pour la détection de mouvement 
 * * OSD Group.1 Registered two Region， Used to display timestamp and string information respectively 
 * * Encoder Group.1 Registered one Channel， monter H264 codage 
 * * Un point à noter ici est ，IVS Bind in OSD antérieur à ， En raison de OSD L'horodatage peut provoquer IVS Mauvaise appréciation de la détection de mouvement 
 *
 * Reference Code: \n
 * Flux de données du flux principal Bind : 
 * @code 
 * IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};
 * IMPCell osd_grp0 = {DEV_ID_OSD, 0, 0};
 * IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0};
 * int ret = IMP_System_Bind(&fs_chn0, &osd_grp0);
 * if (ret < 0)
 * printf("Bind FrameSource Channel0 and OSD Group0 failed\n");
 *
 * int ret = IMP_System_Bind(&osd_grp0, &enc_grp0);
 * if (ret < 0)
 * printf("Bind OSD Group0 and Encoder Group0 failed\n");
 * @endcode 
 * Flux de données du flux de code Bind : 
 * @code 
 * IMPCell fs_chn1_output0 = {DEV_ID_FS, 1, 0};
 * IMPCell ivs_grp0 = {DEV_ID_IVS, 0, 0};
 * IMPCell osd_grp1 = {DEV_ID_OSD, 1, 0};
 * IMPCell enc_grp1 = {DEV_ID_ENC, 1, 0};
 *
 * int ret = IMP_System_Bind(&fs_chn1_output0, &ivs_grp0);
 * if (ret < 0)
 * printf("Bind FrameSource Channel1 and IVS Group0 failed\n");
 *
 * int ret = IMP_System_Bind(&ivs_grp0, &osd_grp1);
 * if (ret < 0)
 * printf("Bind IVS Group0 and OSD Group1 failed\n");
 *
 * int ret = IMP_System_Bind(&osd_grp1, &enc_grp1);
 * if (ret < 0)
 * printf("Bind OSD Group1 and Encoder Group1 failed\n");
 *
 * @endcode 
 *
 * @attention Il est recommandé que toutes les opérations Bind soient effectuées lors de l'initialisation du système.
 * @attention Les opérations Bind et UnBind ne peuvent pas être appelées dynamiquement une fois FrameSource activé. UnBind ne peut être effectué qu'après avoir désactivé FrameSource.
 * @attention DestroyGroup ne peut être exécuté qu'après UnBind.
 *
 * Bind Peut être une structure arborescente ， La figure suivante est un exemple: 
 * @image html different_output.png
 * In the picture above ，FrameSource of Channel 1(Group.1) Backend respectivement Bind Got two Group， Séparément de Output.0 with Output.1 Des données de sortie. Bind L'avantage est ，IVS Group Avec OSD Group.1 Travaillez en parallèle. 
 * @attention La méthode Bind de cet exemple peut affecter la détection de mouvement ordinaire, donc cette méthode n'est pas recommandée pour la détection de mouvement ordinaire.
 *
 * @{
 */

/**
 * IMP Définition du numéro de version du système .
 */
typedef struct {
	char aVersion[64];	/**< IMP Numéro de version du système */
} IMPVersion;

/**
 * @fn int IMP_System_Init (vide)
 *
 * IMP initialisation du système .
 *
 * @param non.
 *
 * @retval 0 succès.
 * @retval Échec non nul.
 *
 * @remarks Après cet appel d'API, la structure de données de base sera initialisée, mais l'unité matérielle ne sera pas initialisée.
 *
 * @attention Cette interface doit être appelée pour l'initialisation avant toute opération d'IMP.
 */
int IMP_System_Init(void);

/**
 * @fn int IMP_System_Exit (void)
 *
 * IMP Désinitialisation du système .
 *
 * @param no .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Une fois cette fonction appelée, toute la mémoire et les poignées d'IMP seront libérées et l'unité matérielle sera fermée.
 *
 * @attention Après avoir appelé cette API, si vous souhaitez utiliser à nouveau IMP, vous devez réinitialiser le système IMP.
 */
int IMP_System_Exit(void);

/**
 * @fn int64_t IMP_System_GetTimeStamp (vide)
 *
 * obtenir IMP Horodatage du système ， L'unité est en microsecondes. 
 *
 * @param non.
 *
 * @retval Heure (usec)
 *
 * @remarks L'horodatage est automatiquement initialisé après l'initialisation du système. 
 *
 * @attention no. 
 */
int64_t IMP_System_GetTimeStamp(void);

/**
 * @fn int IMP_System_RebaseTimeStamp (bases int64_t)
 *
 * Installation IMP System timestamp ， The unit is microseconds. 
 *
 * @param[in] temps de base des basets.
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no. 
 *
 * @attention no. 
 */
int IMP_System_RebaseTimeStamp(int64_t basets);

/**
 * @fn uint32_t IMP_System_ReadReg32 (uint32_t u32Addr)
 *
 * Lire 32 La valeur du registre de bits. 
 *
 * @param[in] L'adresse physique du registre regAddr.
 *
 * @retval La valeur du registre (32 bits)
 *
 * @remarks no. 
 *
 * @attention no. 
 */
uint32_t IMP_System_ReadReg32(uint32_t regAddr);

/**
 * @fn void IMP_System_WriteReg32 (uint32_t regAddr, valeur uint32_t)
 *
 * à 32 Écrivez la valeur dans le registre de bits. 
 *
 * @param[in] regAddr The physical address of the register. 
 * @param[in] valeur La valeur à écrire.
 *
 * @retval non
 *
 * @remarks no. 
 *
 * @attention Veuillez faire attention d'appeler cette API avant de ne pas être clair sur la signification du registre, sinon cela peut provoquer des erreurs système.
 */
void IMP_System_WriteReg32(uint32_t regAddr, uint32_t value);

/**
 * @fn int IMP_System_GetVersion (IMPVersion * pstVersion)
 *
 * Obtenir IMP System version number .
 *
 * @param[out] pstVersion Pointeur de structure du numéro de version du système IMP.
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_System_GetVersion(IMPVersion *pstVersion);

/**
 * @fn const char * IMP_System_GetCPUInfo (void)
 *
 * Obtain CPU Informations sur le modèle .
 *
 * @param no .
 *
 * @retval Cha î ne de modèle de processeur.
 *
 * @remarks La valeur de retour est une cha î ne du type de modèle de CPU. Par exemple, pour T10, il existe T10 et T10-Lite.
 *
 * @attention no .
 */
const char* IMP_System_GetCPUInfo(void);

/**
 * @fn int IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell)
 *
 * Source de liaison Cell Et but Cell.
 *
 * @param[in] Pointeur de cellule source srcCell.
 * @param[in] dstCell Le pointeur de cellule de destination.
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Selon les concepts de périphérique, de groupe et de sortie, chaque périphérique peut avoir plusieurs groupes et chaque groupe peut avoir plusieurs sorties.
 * Group Comme Device Interface d'entrée ， and Output As Device Interface de sortie . Ainsi, la liaison produit en fait Device De 
 * UNE Output Connectez-vous à l'entrée Device Une partie de Group sur .
 * @remarks Une fois la relation de liaison réussie, les données générées par la cellule source (sortie) seront automatiquement transmises à la cellule de destination (groupe).
 *
 * @attention no. 
 */
int IMP_System_Bind(IMPCell *srcCell, IMPCell *dstCell);

/**
 * @fn int IMP_System_UnBind (IMPCell * srcCell, IMPCell * dstCell)
 *
 * De-source Cell And purpose Cell Obligatoire .
 *
 * @param[in] srcCell source Cell pointer .
 * @param[in] dstCell purpose Cell pointer .
 *
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no. 
 */
int IMP_System_UnBind(IMPCell *srcCell, IMPCell *dstCell);

/**
 * @fn int IMP_System_GetBindbyDest (IMPCell * dstCell, IMPCell * srcCell)
 *
 * Soyez lié dans le but Cell Source de Cell informations .
 *
 * @param[in] dstCell purpose Cell pointer .
 * @param[out] srcCell source Cell pointer .
 *
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no. 
 */
int IMP_System_GetBindbyDest(IMPCell *dstCell, IMPCell *srcCell);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_SYSTEM_H__ */
