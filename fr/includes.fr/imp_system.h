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
 * @defgroup imp IMP(Ingenic Media Platform)
 */

/**
 * @defgroup IMP_System
 * @ingroup imp
 * @brief  Module de contrôle du système ， comprendre IMP Fonctions de base et fonctions associées liées entre les modules 
 * @section concept 1  Concepts associés 
 *  Le contrôle du système réalise principalement la connexion de divers modules ， Définissez la fonction du flux de données. Voici quelques concepts importants: 
 *
 * @subsection device 1.1 Device
 * Device C'est une collection qui complète une certaine fonction (de classe). Tel que FrameSource Terminer la sortie des données de la source vidéo ，Encoder Remplissez la fonction de codage vidéo ou de codage d'image. ici FrameSource avec Encoder Seulement Device le concept de. \n
 * Device Juste un concept de collection ， Ce n'est pas un nœud de flux de données spécifique. 
 *
 * @subsection group 1.2 Group
 * Group C'est la plus petite unité d'entrée de données. Une Device Il peut y avoir plusieurs Group， Chaque Group Une seule entrée de données peut être reçue. Group Peut avoir plusieurs sorties ( @ref output  ). \n
 * Group C'est aussi un conteneur pour des «fonctions» spécifiques ， Tu peux voir @ref channel  Une partie de l'explication. 
 *
 * @subsection output 1.3 Output
 * Output Est un Group La plus petite unité de sortie de données pour un canal. Une Group La plus petite unité de sortie de données pour un canal. Une Output， La plus petite unité de sortie de données pour un canal. Une Output Un seul canal de données peut être émis. 
 *
 * @subsection cell 1.4 Cell
 * Cell Se réfère à contient Device [[[ Group [[[ Output Collecte d'informations. À @ref IMPCell La structure des données est présentée. \n
 * Cell Principalement utilisé Bind ( @ref bind ). selon Device ). selon Group ). selon Output Définition ，Output En tant que nœud de sortie de données ， et Group En tant que nœud d'entrée de données. \n
 *  dans Bind Noeud de sortie des données de temps Cell Index à la sortie Output， Nœud de saisie de données Cell Index à saisir Group (Par conséquent, en tant qu'entrée de données Cell，Output Est une valeur dénuée de sens). 
 *
 * @subsection channel 1.5 Channel
 * Channel Fait généralement référence à une seule unité fonctionnelle ，Channel Fait généralement référence à une seule unité fonctionnelle Create Temps ( Instancier ) Lorsque la fonction spécifique est attribuée. \n
 *  Par exemple: \n
 * *  pour Encoder， Une Channel Complétez le chemin H264 Code ou JPEG Fonction de codage ， Fonction de codage spécifique ( Types de ， paramètre ) Spécifié lors de la création du canal 
 * *  Spécifié lors de la création du canal IVS， Spécifié lors de la création du canal Channel Compléter la fonction d'un algorithme spécifique ， Les paramètres de type d'algorithme spécifiques sont spécifiés lors de la création du canal 
 * *  Les paramètres de type d'algorithme spécifiques sont spécifiés lors de la création du canal OSD， Avoir le même Channel Concepts similaires Region， Concepts similaires Region Est une zone de chevauchement spécifique ， Peut être PIC( image )，COVER( Occlure ) Attendre 
 * *  Attendre FrameSource， Attendre Channel Sortie d'une image originale ，FrameSource de Channel Est en fait Group
 *
 * Channel En tant qu'unité fonctionnelle ， ont généralement besoin Register À Group dans (FrameSource sauf )， Pour recevoir les données. Channel Inscrivez-vous à Group Milieu et arrière ， Aura Group Données saisies. \n
 *  différent Device différent Group peut Register peut Channel Les chiffres sont également différents. 
 *
 * @section bind 2  Liaison de module ( Bind ) 
 *  Deux Group après Bind Après connexion ， la source Group Les données seront automatiquement envoyées à la destination Group . \n
 *  en raison de Group Est la plus petite unité d'entrée de données ，Output Est la plus petite unité de sortie de données ， donc IMP_System_Bind(IMPCell *srcCell, IMPCell *dstCell) Des deux paramètres srcCell Des deux paramètres deviceID, groupID, outputID C'est vaild 
 *  C'est vaild dstCell seul deviceID seul groupID efficace ，outputID Comme la saisie de données n'a pas de sens. \n
 *  L'image ci-dessous est un simple Bind exemple de. 
 * @image html system_bind0.jpg
 *  Dans l'image ci-dessus ， Atteint FrameSource Une sortie Bind Une sortie Encoder un des Group un des 
 *  un des Encoder Group un des Register J'en ai deux Channel， J'en ai deux Encoder Group Ont H264 Ont JPEG Deux sorties. 
 *  Code de référence: 
 * @code
 * IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};			//FrameSource deviceID:DEV_ID_FS groupID:0 outputID:0
 * IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0};		//ENC deviceID:DEV_ID_ENC groupID:0 outputID:0,  Ici enc_grp0 Le troisième paramètre n'a pas de sens. 
 * int ret = IMP_System_Bind(&fs_chn0, &enc_grp0);
 * if (ret < 0)
 *     printf("Bind FrameSource Channel0 and Encoder Group0 failed\n");
 * @endcode
 * Bind Concaténer le flux de données du système ， Selon les différentes exigences fonctionnelles du produit ，Bind La stratégie peut également être différente. 
 *
 *  Ce qui suit est une application de produit de flux de code à double canal typique Bind Diagramme schématique: 
 *
 * @image html typical_application.png
 *
 *  Dans l'image ci-dessus ，FrameSource Il y a deux sorties ， Respectivement sont Channel0 Intégrer (1280x720) Intégrer Channel1 Flux esclave (640x360) Flux esclave \n
 * *  Intégrer: FrameSource Intégrer: Channel0 Bind OSD Group.0，OSD Group.0 Bind Encoder Group.0 . parmi eux: 
 *   * OSD Group.0  Enregistré deux Region， Utilisé pour afficher respectivement les informations d'horodatage et de chaîne 
 *   * Encoder Group.0  Utilisé pour afficher respectivement les informations d'horodatage et de chaîne Channel， Séparément H264 Encodage et JPEG codage. parmi eux JPEG Si la taille d'image du canal d'encodage n'est pas égale au réglage d'entrée ( FrameSource Si la taille d'image du canal d'encodage n'est pas égale au réglage d'entrée ( Channel0 Si la taille d'image du canal d'encodage n'est pas égale au réglage d'entrée ( ， Ensuite, il zoomera (Software at T10)， Atteindre l'objectif de capturer n'importe quelle résolution 
 * *  À partir du flux de code: FrameSource À partir du flux de code: Channel1 Bind IVS Group.0，IVS Group.0 Bind OSD Group.1，OSD Group.1 Bind Encoder Group.1 À partir du flux de code: 
 *   * IVS Group.0  Enregistré un Channel， Utilisé pour la détection de mouvement 
 *   * OSD Group.1  Utilisé pour la détection de mouvement Region， Utilisé pour la détection de mouvement 
 *   * Encoder Group.1  Utilisé pour la détection de mouvement Channel， monter H264 codage 
 *   *  Un point à noter ici est ，IVS Bind  Un point à noter ici est  OSD antérieur à ， En raison de OSD L'horodatage peut provoquer IVS Mauvaise appréciation de la détection de mouvement 
 *
 *  Mauvaise appréciation de la détection de mouvement \n
 *  Flux de données du flux principal Bind : 
 * @code
 * IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};
 * IMPCell osd_grp0 = {DEV_ID_OSD, 0, 0};
 * IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0};
 * int ret = IMP_System_Bind(&fs_chn0, &osd_grp0);
 * if (ret < 0)
 *     printf("Bind FrameSource Channel0 and OSD Group0 failed\n");
 *
 * int ret = IMP_System_Bind(&osd_grp0, &enc_grp0);
 * if (ret < 0)
 *     printf("Bind OSD Group0 and Encoder Group0 failed\n");
 * @endcode
 *  Flux de données du flux de code Bind Flux de données du flux de code 
 * @code
 * IMPCell fs_chn1_output0 = {DEV_ID_FS, 1, 0};
 * IMPCell ivs_grp0 = {DEV_ID_IVS, 0, 0};
 * IMPCell osd_grp1 = {DEV_ID_OSD, 1, 0};
 * IMPCell enc_grp1 = {DEV_ID_ENC, 1, 0};
 *
 * int ret = IMP_System_Bind(&fs_chn1_output0, &ivs_grp0);
 * if (ret < 0)
 *     printf("Bind FrameSource Channel1 and IVS Group0 failed\n");
 *
 * int ret = IMP_System_Bind(&ivs_grp0, &osd_grp1);
 * if (ret < 0)
 *     printf("Bind IVS Group0 and OSD Group1 failed\n");
 *
 * int ret = IMP_System_Bind(&osd_grp1, &enc_grp1);
 * if (ret < 0)
 *     printf("Bind OSD Group1 and Encoder Group1 failed\n");
 *
 * @endcode
 *
 * @attention  Suggérer tout Bind L'opération est effectuée lorsque le système est initialisé. 
 * @attention  L'opération est effectuée lorsque le système est initialisé. FrameSource Après avoir activé Bind Après avoir activé UnBind L'opération ne peut pas être appelée dynamiquement ， avoir besoin Disable FrameSource Peut être fait plus tard UnBind Peut être fait plus tard 
 * @attention DestroyGroup En être UnBind Cela ne peut être fait qu'après. 
 *
 * Bind Peut être une structure arborescente ， La figure suivante est un exemple: 
 * @image html different_output.png
 *  La figure suivante est un exemple: ，FrameSource La figure suivante est un exemple: Channel 1(Group.1) Backend respectivement Bind Backend respectivement Group， Séparément de Output.0 Séparément de  Output.1 Des données de sortie. Dans ce cas Bind L'avantage est ，IVS Group Avec OSD Group.1 Travaillez en parallèle. 
 * @attention  Dans cet exemple Bind Les moyens peuvent affecter la détection de mouvement ordinaire ， Par conséquent, cette méthode n'est pas recommandée pour la détection de mouvement normale. 
 *
 * @{
 */

/**
 * IMP Définition du numéro de version du système .
 */
typedef struct {
	char aVersion[64];	/**< IMP Numéro de version du système  */
} IMPVersion;

/**
 * @fn int IMP_System_Init(void)
 *
 * IMP initialisation du système .
 *
 * @param  non .
 *
 * @retval 0  Succès .
 * @retval  non- 0  échec .
 *
 * @remarks  ce API Après l'appel, la structure de données de base sera initialisée ， Mais n'initialise pas l'unité matérielle .
 *
 * @attention  Mais n'initialise pas l'unité matérielle IMP Vous devez appeler cette interface pour l'initialiser avant toute opération de .
 */
int IMP_System_Init(void);

/**
 * @fn int IMP_System_Exit(void)
 *
 * IMP Désinitialisation du système .
 *
 * @param  Désinitialisation du système .
 *
 * @retval 0  Désinitialisation du système .
 * @retval  Désinitialisation du système 0  Désinitialisation du système .
 *
 * @remarks  Cette fonction sera libérée après l'appel IMP Toute la mémoire et les poignées ， Et fermez l'unité matérielle .
 *
 * @attention  Appeler ça API Arrière ， Pour utiliser à nouveau IMP Vous devez le refaire IMP Vous devez le refaire .
 */
int IMP_System_Exit(void);

/**
 * @fn int64_t IMP_System_GetTimeStamp(void)
 *
 *  obtenir IMP Horodatage du système ， L'unité est en microsecondes. 
 *
 * @param  non. 
 *
 * @retval  temps (usec)
 *
 * @remarks  L'horodatage est automatiquement initialisé après l'initialisation du système. L'horodatage devient invalide après la désinitialisation du système. 
 *
 * @attention  L'horodatage est automatiquement initialisé après l'initialisation du système. L'horodatage devient invalide après la désinitialisation du système. 
 */
int64_t IMP_System_GetTimeStamp(void);

/**
 * @fn int IMP_System_RebaseTimeStamp(int64_t basets)
 *
 *  Installation IMP Installation ， Installation 
 *
 * @param[in] basets  Temps de base. 
 *
 * @retval 0  Temps de base. .
 * @retval  Temps de base. 0  Temps de base. .
 *
 * @remarks  Temps de base. 
 *
 * @attention  Temps de base. 
 */
int IMP_System_RebaseTimeStamp(int64_t basets);

/**
 * @fn uint32_t IMP_System_ReadReg32(uint32_t u32Addr)
 *
 *  Lire 32 La valeur du registre de bits. 
 *
 * @param[in] regAddr  L'adresse physique du registre. 
 *
 * @retval  La valeur du registre ( 32 Bit) 
 *
 * @remarks  Bit) 
 *
 * @attention  Bit) 
 */
uint32_t IMP_System_ReadReg32(uint32_t regAddr);

/**
 * @fn void IMP_System_WriteReg32(uint32_t regAddr, uint32_t value)
 *
 *  à 32 Écrivez la valeur dans le registre de bits. 
 *
 * @param[in] regAddr  Écrivez la valeur dans le registre de bits. 
 * @param[in] value  La valeur à écrire. 
 *
 * @retval  La valeur à écrire. 
 *
 * @remarks  La valeur à écrire. 
 *
 * @attention  Veuillez faire attention d'appeler ceci avant que vous ne soyez pas clair sur la signification du registre API， Sinon, des erreurs système peuvent survenir. 
 */
void IMP_System_WriteReg32(uint32_t regAddr, uint32_t value);

/**
 * @fn int IMP_System_GetVersion(IMPVersion *pstVersion)
 *
 *  Obtenir IMP Obtenir .
 *
 * @param[out] pstVersion IMP Pointeur de structure du numéro de version du système .
 *
 * @retval 0  Pointeur de structure du numéro de version du système .
 * @retval  Pointeur de structure du numéro de version du système 0  Pointeur de structure du numéro de version du système .
 *
 * @remarks  Pointeur de structure du numéro de version du système .
 *
 * @attention  Pointeur de structure du numéro de version du système .
 */
int IMP_System_GetVersion(IMPVersion *pstVersion);

/**
 * @fn const char* IMP_System_GetCPUInfo(void)
 *
 *  Pointeur de structure du numéro de version du système CPU Informations sur le modèle .
 *
 * @param  Informations sur le modèle .
 *
 * @retval CPU Chaîne de modèle .
 *
 * @remarks  La valeur de retour est CPU Chaîne de type de modèle , Par exemple pour T10 Dire , Dire "T10" et "T10-Lite".
 *
 * @attention  et .
 */
const char* IMP_System_GetCPUInfo(void);

/**
 * @fn int IMP_System_Bind(IMPCell *srcCell, IMPCell *dstCell)
 *
 *  Source de liaison Cell Et but Cell.
 *
 * @param[in] srcCell  Et but Cell aiguille .
 * @param[in] dstCell  but Cell but .
 *
 * @retval 0  but .
 * @retval  but 0  but .
 *
 * @remarks  selon Device selon Group selon Output le concept de ， le concept de Device Il peut y avoir plus d'un Group， Il peut y avoir plus d'un Group Il peut y avoir plus d'un Output，
 * Group Comme Device Interface d'entrée ， Interface d'entrée Output Interface d'entrée Device Interface de sortie . Ainsi, la liaison produit en fait Device De 
 *  UNE Output Connectez-vous à l'entrée Device Une partie de Group sur .
 * @remarks  Une fois la relation de liaison réussie ， Une fois la relation de liaison réussie Cell(Output) Les données générées seront automatiquement transmises à la destination Cell(Group).
 *
 * @attention  Les données générées seront automatiquement transmises à la destination 
 */
int IMP_System_Bind(IMPCell *srcCell, IMPCell *dstCell);

/**
 * @fn int IMP_System_UnBind(IMPCell *srcCell, IMPCell *dstCell)
 *
 *  De-source Cell De-source Cell Obligatoire .
 *
 * @param[in] srcCell  Obligatoire Cell Obligatoire .
 * @param[in] dstCell  Obligatoire Cell Obligatoire .
 *
 *
 * @retval 0  Obligatoire .
 * @retval  Obligatoire 0  Obligatoire .
 *
 * @remarks  Obligatoire .
 *
 * @attention  Obligatoire 
 */
int IMP_System_UnBind(IMPCell *srcCell, IMPCell *dstCell);

/**
 * @fn int IMP_System_GetBindbyDest(IMPCell *dstCell, IMPCell *srcCell)
 *
 *  Soyez lié dans le but Cell Source de Cell informations .
 *
 * @param[in] dstCell  informations Cell informations .
 * @param[out] srcCell  informations Cell informations .
 *
 *
 * @retval 0  informations .
 * @retval  informations 0  informations .
 *
 * @remarks  informations .
 *
 * @attention  informations 
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
