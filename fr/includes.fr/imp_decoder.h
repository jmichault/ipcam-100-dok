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
 * @brief Module de décodage vidéo ， Actuellement ne prend en charge que JPEG décodage 
 * @{
 */

/**
 * Définir les propriétés du décodeur 
 */
typedef struct {
	IMPPayloadType		decType;		/**< Le type de protocole de données d'origine de la trame décodée */
	uint32_t			maxWidth;		/**< Largeur maximale du cadre décodé */
	uint32_t			maxHeight;		/**< Hauteur maximale du cadre décodé */
	IMPPixelFormat		pixelFormat;	/**< Décoder le type de protocole de données de la cible de trame */
	uint32_t			nrKeepStream;	/**< Nombre de trames tamponnées du décodeur */
	uint32_t			frmRateNum;		/**< Le nombre d'unités de temps en une seconde , En unités de temps. */
	uint32_t			frmRateDen;		/**< Le nombre d'unités de temps dans une trame , En unités de temps. */
} IMPDecoderAttr;

/**
 * Définir le décodage Channel Les attributs 
 */
typedef struct {
	IMPDecoderAttr		decAttr;		/**< Attributs du décodeur */
} IMPDecoderCHNAttr;

/**
 * Définir les attributs de données de trame décodées 
 */
typedef struct {
	int					i_payload;		/**< Longueur des données de la trame décodée */
	uint8_t				*p_payload;		/**< Pointeur de données de la trame décodée */
	int64_t				timeStamp;		/**< Horodatage de l'image décodée */
} IMPDecoderNal;

/**
 * Définir les attributs du flux de code du décodeur 
 */
typedef struct {
	IMPDecoderNal	decoderNal; /**< Structure de données de trame décodée */
} IMPDecoderStream;

/**
 * @fn int IMP_Decoder_CreateChn(int decChn, const IMPDecoderCHNAttr *attr)
 *
 * Créer un décodage Channel
 *
 * @param[in] decChn décodage Channel numéro , Gammes : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] attr décodage Channel Pointeur d'attribut 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks non. 
 * @attention non. 
 */
int IMP_Decoder_CreateChn(int decChn, const IMPDecoderCHNAttr *attr);

/**
 * @fn int IMP_Decoder_DestroyChn(int decChn)
 *
 * Détruire le décodage Channel
 *
 * @param[in] decChn décodage Channel numéro , Gammes : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks non. 
 * @attention non. 
 */
int IMP_Decoder_DestroyChn(int decChn);

/**
 * @fn int IMP_Decoder_StartRecvPic(int decChn)
 *
 * Activer le décodage Channel Recevoir l'image 
 *
 * @param[in] decChn décodage Channel numéro , Gammes : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Activer le décodage Channel Le décodage ne peut démarrer qu'après réception de l'image 
 *
 * @attention au cas où Channel Non créé ， Manqué 
 */
int IMP_Decoder_StartRecvPic(int decChn);

/**
 * @fn int IMP_Decoder_StopRecvPic(int decChn)
 *
 * Arrêter le décodage Channel Recevoir l'image 
 *
 * @param[in] decChn décodage Channel numéro , Gammes : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks Arrêter le décodage Channel Recevoir l'image 
 *
 * @attention au cas où Channel Non créé ， Manqué 
 */
int IMP_Decoder_StopRecvPic(int decChn);

/**
 * @fn int IMP_Decoder_SendStreamTimeout(int decChn, IMPDecoderStream *stream, uint32_t timeoutMsec)
 *
 * Envoyer les données à décoder 
 *
 * @param[in] decChn décodage Channel numéro , Gammes : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] stream Pointeur de structure de flux de données à décoder 
 * @param[in] timeoutMsec Délai de décodage unité ms
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks non. 
 *
 * @attention au cas où Channel Non créé ， Manqué 
 */
int IMP_Decoder_SendStreamTimeout(int decChn, IMPDecoderStream *stream, uint32_t timeoutMsec);

/**
 * @fn int IMP_Decoder_PollingFrame(int decChn, uint32_t timeoutMsec)
 *
 * Polling Tampon de flux de décodage 
 *
 * @param[in] decChn décodage Channel numéro , Gammes : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] timeoutMsec temps supplémentaire unité ms
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks non. 
 *
 * @attention au cas où Channel Non créé ， Manqué 
 */
int IMP_Decoder_PollingFrame(int decChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Decoder_GetFrame(int decChn, IMPFrameInfo **frame)
 *
 * Obtenir un flux de code décodé 
 *
 * @param[in] decChn décodage Channel numéro , Gammes : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[out] frame Décodage du pointeur de structure de flux 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks non. 
 *
 * @attention Décoder le flux buffer Appliquer en interne par le décodeur ， Cette fonction n'a besoin que de passer le pointeur de structure. 
 */
int IMP_Decoder_GetFrame(int decChn, IMPFrameInfo **frame);

/**
 * @fn int IMP_Decoder_ReleaseFrame(int decChn, IMPFrameInfo *frame)
 *
 * Libérez le cache du flux de code 
 *
 * @param[in] decChn décodage Channel numéro , Gammes : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] frame Décodage du pointeur de structure de flux 
 *
 * @retval 0 Succès 
 * @retval non- 0 échec 
 *
 * @remarks non. 
 *
 * @attention non. 
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
