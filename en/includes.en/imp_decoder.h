/*
 * IMP Decoder func header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_DECODER_H__
#define __IMP_DECODER_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP Fichier d'en-tête du décodeur 
 */

/**
 * @defgroup IMP_Decoder
 * @ingroup imp
 * @brief  Module de décodage vidéo ， Actuellement ne prend en charge que JPEG décodage 
 * @{
 */

/**
 *  Définir les propriétés du décodeur 
 */
typedef struct {
	IMPPayloadType		decType;		/**<  Le type de protocole de données d'origine de la trame décodée  */
	uint32_t			maxWidth;		/**<  Largeur maximale du cadre décodé  */
	uint32_t			maxHeight;		/**<  Hauteur maximale du cadre décodé  */
	IMPPixelFormat		pixelFormat;	/**<  Décoder le type de protocole de données de la cible de trame  */
	uint32_t			nrKeepStream;	/**<  Nombre de trames tamponnées du décodeur  */
	uint32_t			frmRateNum;		/**<  Le nombre d'unités de temps en une seconde ,  En unités de temps. Le numérateur de la fréquence d'images  */
	uint32_t			frmRateDen;		/**<  Le nombre d'unités de temps dans une trame ,  En unités de temps. Le dénominateur de la fréquence d'images  */
} IMPDecoderAttr;

/**
 *  Définir le décodage Channel Les attributs 
 */
typedef struct {
	IMPDecoderAttr		decAttr;		/**<  Attributs du décodeur  */
} IMPDecoderCHNAttr;

/**
 *  Définir les attributs de données de trame décodées 
 */
typedef struct {
	int					i_payload;		/**<  Longueur des données de la trame décodée  */
	uint8_t				*p_payload;		/**<  Pointeur de données de la trame décodée  */
	int64_t				timeStamp;		/**<  Horodatage de l'image décodée  */
} IMPDecoderNal;

/**
 *  Définir les attributs du flux de code du décodeur 
 */
typedef struct {
	IMPDecoderNal	decoderNal; /**<  Structure de données de trame décodée  */
} IMPDecoderStream;

/**
 * @fn int IMP_Decoder_CreateChn(int decChn, const IMPDecoderCHNAttr *attr)
 *
 *  Créer un décodage Channel
 *
 * @param[in] decChn  Créer un décodage Channel numéro , Gammes : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] attr  Gammes Channel Pointeur d'attribut 
 *
 * @retval 0  Succès 
 * @retval  non- 0  échec 
 *
 * @remarks  non. 
 * @attention  non. 
 */
int IMP_Decoder_CreateChn(int decChn, const IMPDecoderCHNAttr *attr);

/**
 * @fn int IMP_Decoder_DestroyChn(int decChn)
 *
 *  Détruire le décodage Channel
 *
 * @param[in] decChn  Détruire le décodage Channel Détruire le décodage , Détruire le décodage : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0  Détruire le décodage 
 * @retval  Détruire le décodage 0  Détruire le décodage 
 *
 * @remarks  Détruire le décodage 
 * @attention  Détruire le décodage 
 */
int IMP_Decoder_DestroyChn(int decChn);

/**
 * @fn int IMP_Decoder_StartRecvPic(int decChn)
 *
 *  Activer le décodage Channel Recevoir l'image 
 *
 * @param[in] decChn  Recevoir l'image Channel Recevoir l'image , Recevoir l'image : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0  Recevoir l'image 
 * @retval  Recevoir l'image 0  Recevoir l'image 
 *
 * @remarks  Recevoir l'image Channel Le décodage ne peut démarrer qu'après réception de l'image 
 *
 * @attention  au cas où Channel Non créé ， Manqué 
 */
int IMP_Decoder_StartRecvPic(int decChn);

/**
 * @fn int IMP_Decoder_StopRecvPic(int decChn)
 *
 *  Arrêter le décodage Channel Arrêter le décodage 
 *
 * @param[in] decChn  Arrêter le décodage Channel Arrêter le décodage , Arrêter le décodage : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0  Arrêter le décodage 
 * @retval  Arrêter le décodage 0  Arrêter le décodage 
 *
 * @remarks  Arrêter le décodage Channel Arrêter le décodage 
 *
 * @attention  Arrêter le décodage Channel Arrêter le décodage ， Arrêter le décodage 
 */
int IMP_Decoder_StopRecvPic(int decChn);

/**
 * @fn int IMP_Decoder_SendStreamTimeout(int decChn, IMPDecoderStream *stream, uint32_t timeoutMsec)
 *
 *  Envoyer les données à décoder 
 *
 * @param[in] decChn  Envoyer les données à décoder Channel Envoyer les données à décoder , Envoyer les données à décoder : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] stream  Pointeur de structure de flux de données à décoder 
 * @param[in] timeoutMsec  Délai de décodage   unité ms
 *
 * @retval 0  unité 
 * @retval  unité 0  unité 
 *
 * @remarks  unité 
 *
 * @attention  unité Channel unité ， unité 
 */
int IMP_Decoder_SendStreamTimeout(int decChn, IMPDecoderStream *stream, uint32_t timeoutMsec);

/**
 * @fn int IMP_Decoder_PollingFrame(int decChn, uint32_t timeoutMsec)
 *
 * Polling  Tampon de flux de décodage 
 *
 * @param[in] decChn  Tampon de flux de décodage Channel Tampon de flux de décodage , Tampon de flux de décodage : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] timeoutMsec  temps supplémentaire   temps supplémentaire ms
 *
 * @retval 0  temps supplémentaire 
 * @retval  temps supplémentaire 0  temps supplémentaire 
 *
 * @remarks  temps supplémentaire 
 *
 * @attention  temps supplémentaire Channel temps supplémentaire ， temps supplémentaire 
 */
int IMP_Decoder_PollingFrame(int decChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Decoder_GetFrame(int decChn, IMPFrameInfo **frame)
 *
 *  Obtenir un flux de code décodé 
 *
 * @param[in] decChn  Obtenir un flux de code décodé Channel Obtenir un flux de code décodé , Obtenir un flux de code décodé : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[out] frame  Décodage du pointeur de structure de flux 
 *
 * @retval 0  Décodage du pointeur de structure de flux 
 * @retval  Décodage du pointeur de structure de flux 0  Décodage du pointeur de structure de flux 
 *
 * @remarks  Décodage du pointeur de structure de flux 
 *
 * @attention  Décoder le flux buffer Appliquer en interne par le décodeur ， Cette fonction n'a besoin que de passer le pointeur de structure. 
 */
int IMP_Decoder_GetFrame(int decChn, IMPFrameInfo **frame);

/**
 * @fn int IMP_Decoder_ReleaseFrame(int decChn, IMPFrameInfo *frame)
 *
 *  Libérez le cache du flux de code 
 *
 * @param[in] decChn  Libérez le cache du flux de code Channel Libérez le cache du flux de code , Libérez le cache du flux de code : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] frame  Libérez le cache du flux de code 
 *
 * @retval 0  Libérez le cache du flux de code 
 * @retval  Libérez le cache du flux de code 0  Libérez le cache du flux de code 
 *
 * @remarks  Libérez le cache du flux de code 
 *
 * @attention  Libérez le cache du flux de code 
 */
int IMP_Decoder_ReleaseFrame(int decChn, IMPFrameInfo *frame);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_DECODER_H__ */
