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
 * IMP Decoder header file 
 */

/**
 * @defgroup IMP_Decoder
 * @ingroup imp
 * @brief  Video decoding module ， Currently only supports JPEG decoding 
 * @{
 */

/**
 *  Define decoder properties 
 */
typedef struct {
	IMPPayloadType		decType;		/**<  The original data protocol type of the decoded frame  */
	uint32_t			maxWidth;		/**<  Maximum width of decoded frame  */
	uint32_t			maxHeight;		/**<  Maximum height of decoded frame  */
	IMPPixelFormat		pixelFormat;	/**<  Decode frame target data protocol type  */
	uint32_t			nrKeepStream;	/**<  Number of decoder buffered frames  */
	uint32_t			frmRateNum;		/**<  The number of time units in one second ,  In units of time. The numerator of the frame rate  */
	uint32_t			frmRateDen;		/**<  The number of time units in a frame ,  In units of time. The denominator of the frame rate  */
} IMPDecoderAttr;

/**
 *  Define decoding Channel Attributes 
 */
typedef struct {
	IMPDecoderAttr		decAttr;		/**<  Decoder attributes  */
} IMPDecoderCHNAttr;

/**
 *  Define decoded frame data attributes 
 */
typedef struct {
	int					i_payload;		/**<  Data length of the decoded frame  */
	uint8_t				*p_payload;		/**<  Data pointer of decoded frame  */
	int64_t				timeStamp;		/**<  Timestamp of decoded frame  */
} IMPDecoderNal;

/**
 *  Define decoder code stream attributes 
 */
typedef struct {
	IMPDecoderNal	decoderNal; /**<  Decoded frame data structure  */
} IMPDecoderStream;

/**
 * @fn int IMP_Decoder_CreateChn(int decChn, const IMPDecoderCHNAttr *attr)
 *
 *  Create decoding Channel
 *
 * @param[in] decChn  Create decoding Channel number , Ranges : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] attr  Ranges Channel Attribute pointer 
 *
 * @retval 0  success 
 * @retval  non- 0  failure 
 *
 * @remarks  no. 
 * @attention  no. 
 */
int IMP_Decoder_CreateChn(int decChn, const IMPDecoderCHNAttr *attr);

/**
 * @fn int IMP_Decoder_DestroyChn(int decChn)
 *
 *  Destroy decoding Channel
 *
 * @param[in] decChn  Destroy decoding Channel Destroy decoding , Destroy decoding : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0  Destroy decoding 
 * @retval  Destroy decoding 0  Destroy decoding 
 *
 * @remarks  Destroy decoding 
 * @attention  Destroy decoding 
 */
int IMP_Decoder_DestroyChn(int decChn);

/**
 * @fn int IMP_Decoder_StartRecvPic(int decChn)
 *
 *  Turn on decoding Channel Receive image 
 *
 * @param[in] decChn  Receive image Channel Receive image , Receive image : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0  Receive image 
 * @retval  Receive image 0  Receive image 
 *
 * @remarks  Receive image Channel Decoding can only start after receiving images 
 *
 * @attention  in case Channel Not created ， Failed 
 */
int IMP_Decoder_StartRecvPic(int decChn);

/**
 * @fn int IMP_Decoder_StopRecvPic(int decChn)
 *
 *  Stop decoding Channel Stop decoding 
 *
 * @param[in] decChn  Stop decoding Channel Stop decoding , Stop decoding : [0, @ref NR_MAX_DEC_CHN - 1]
 *
 * @retval 0  Stop decoding 
 * @retval  Stop decoding 0  Stop decoding 
 *
 * @remarks  Stop decoding Channel Stop decoding 
 *
 * @attention  Stop decoding Channel Stop decoding ， Stop decoding 
 */
int IMP_Decoder_StopRecvPic(int decChn);

/**
 * @fn int IMP_Decoder_SendStreamTimeout(int decChn, IMPDecoderStream *stream, uint32_t timeoutMsec)
 *
 *  Send the data to be decoded 
 *
 * @param[in] decChn  Send the data to be decoded Channel Send the data to be decoded , Send the data to be decoded : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] stream  Data stream structure pointer to be decoded 
 * @param[in] timeoutMsec  Decoding timeout   unit ms
 *
 * @retval 0  unit 
 * @retval  unit 0  unit 
 *
 * @remarks  unit 
 *
 * @attention  unit Channel unit ， unit 
 */
int IMP_Decoder_SendStreamTimeout(int decChn, IMPDecoderStream *stream, uint32_t timeoutMsec);

/**
 * @fn int IMP_Decoder_PollingFrame(int decChn, uint32_t timeoutMsec)
 *
 * Polling  Decoding stream buffer 
 *
 * @param[in] decChn  Decoding stream buffer Channel Decoding stream buffer , Decoding stream buffer : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] timeoutMsec  overtime time   overtime time ms
 *
 * @retval 0  overtime time 
 * @retval  overtime time 0  overtime time 
 *
 * @remarks  overtime time 
 *
 * @attention  overtime time Channel overtime time ， overtime time 
 */
int IMP_Decoder_PollingFrame(int decChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Decoder_GetFrame(int decChn, IMPFrameInfo **frame)
 *
 *  Get decoded code stream 
 *
 * @param[in] decChn  Get decoded code stream Channel Get decoded code stream , Get decoded code stream : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[out] frame  Decoding stream structure pointer 
 *
 * @retval 0  Decoding stream structure pointer 
 * @retval  Decoding stream structure pointer 0  Decoding stream structure pointer 
 *
 * @remarks  Decoding stream structure pointer 
 *
 * @attention  Decode stream buffer Apply internally by the decoder ， This function only needs to pass in the structure pointer. 
 */
int IMP_Decoder_GetFrame(int decChn, IMPFrameInfo **frame);

/**
 * @fn int IMP_Decoder_ReleaseFrame(int decChn, IMPFrameInfo *frame)
 *
 *  Release the code stream cache 
 *
 * @param[in] decChn  Release the code stream cache Channel Release the code stream cache , Release the code stream cache : [0, @ref NR_MAX_DEC_CHN - 1]
 * @param[in] frame  Release the code stream cache 
 *
 * @retval 0  Release the code stream cache 
 * @retval  Release the code stream cache 0  Release the code stream cache 
 *
 * @remarks  Release the code stream cache 
 *
 * @attention  Release the code stream cache 
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
