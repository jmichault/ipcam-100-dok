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
 * @ingroup lutin
 * @brief Module de décodage vidéo, ne prend actuellement en charge que le décodage JPEG
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
 * @fn int IMP_Decoder_CreateChn (int decChn, const IMPDecoderCHNAttr * attr)
 *
 * Créer un décodage Channel
 *
 * @param[in] decChn decode Numéro de canal, plage de valeurs: [0, @ref NR_MAX_DEC_CHN-1]
 * @param[in] attr décoder le pointeur d'attribut de canal
 *
 * @retval 0 succès
 * @retval Échec non nul
 *
 * @remarks non.
 * @attention no. 
 */
int IMP_Decoder_CreateChn(int decChn, const IMPDecoderCHNAttr *attr);

/**
 * @fn int IMP_Decoder_DestroyChn (int decChn)
 *
 * Détruire le décodage Channel
 *
 * @param[in] decChn decoding Channel number , Ranges : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks no. 
 * @attention no. 
 */
int IMP_Decoder_DestroyChn(int decChn);

/**
 * @fn int IMP_Decoder_StartRecvPic (int decChn)
 *
 * Activer le décodage Channel Recevoir l'image 
 *
 * @param[in] decChn decoding Channel number , Ranges : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Le décodage ne peut démarrer qu'après l'ouverture du canal de décodage pour recevoir l'image
 *
 * @attention Si le canal n'est pas créé, il renvoie un échec
 */
int IMP_Decoder_StartRecvPic(int decChn);

/**
 * @fn int IMP_Decoder_StopRecvPic (int decChn)
 *
 * Arrêter le décodage Channel Receive image 
 *
 * @param[in] decChn decoding Channel number , Ranges : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Arrêter le décodage de l'image de réception du canal
 *
 * @attention in case Channel Not created ， Failed 
 */
int IMP_Decoder_StopRecvPic(int decChn);

/**
 * @fn int IMP_Decoder_SendStreamTimeout (int decChn, IMPDecoderStream * stream, uint32_t timeoutMsec)
 *
 * Envoyer les données à décoder 
 *
 * @param[in] decChn decoding Channel number , Ranges : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] pointeur de flux vers la structure du flux de données à décoder
 * @param[in] timeout Msec Timeout de décodage unité de temps ms
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks no. 
 *
 * @attention in case Channel Not created ， Failed 
 */
int IMP_Decoder_SendStreamTimeout(int decChn, IMPDecoderStream *stream, uint32_t timeoutMsec);

/**
 * @fn int IMP_Decoder_PollingFrame (int decChn, uint32_t timeoutMsec)
 *
 * Polling Tampon de flux de décodage 
 *
 * @param[in] decChn decoding Channel number , Ranges : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] timeout Msec timeout unité de temps ms
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks no. 
 *
 * @attention in case Channel Not created ， Failed 
 */
int IMP_Decoder_PollingFrame(int decChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Decoder_GetFrame (int decChn, IMPFrameInfo ** frame)
 *
 * Obtenir un flux de code décodé 
 *
 * @param[in] decChn decoding Channel number , Ranges : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[out] frame Pointeur de structure de flux de décodage
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks no. 
 *
 * @attention Le tampon de flux de code de décodage est demandé en interne par le décodeur, et cette fonction n'a besoin que de passer le pointeur de structure.
 */
int IMP_Decoder_GetFrame(int decChn, IMPFrameInfo **frame);

/**
 * @fn int IMP_Decoder_ReleaseFrame (int decChn, IMPFrameInfo * frame)
 *
 * Libérez le cache du flux de code 
 *
 * @param[in] decChn decoding Channel number , Ranges : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] frame Decoding stream structure pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks no. 
 *
 * @attention no. 
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
