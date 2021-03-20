/*
 * Audio utils header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_AUDIO_H__
#define __IMP_AUDIO_H__

#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP Audio input and output header files 
 */

/**
 * @defgroup IMP_Audio
 * @ingroup imp
 * @brief Audio module ， Including recording and playback, audio codec, volume and gain settings, echo cancellation, automatic gain and other functions 
 *
 * @section audio_summary 1 Overview 
 * Audio function includes audio input , Audio output , Echo cancellation , Audio encoding and audio decoding 5 Modules . \n
 * Among them, the audio input and audio output have the concept of equipment and channels . One of the MIC We think it is a Device, And one MIC There can be multiple Channel enter . \n
 * The same one SPK We think it's an announcement Device, And one SPK There can also be multiple Channel Output . \n
 * Audio of the current version API One Device Only supports one Channel. \n
 * Echo cancellation is located in the audio input interface , Specific instructions are reflected in the function description . \n
 * Audio encoding current audio API Medium support PT_G711A [[[ PT_G711U with PT_G726 Format audio encoding , If you need to add a new encoding method , Need to register the encoder . \n
 * Audio decoding current audio API Medium support PT_G711A [[[ PT_G711U with PT_G726 Format audio decoding , If you need to add a new decoding method , Need to register decoder . \n
 * @section audio_function_description 2 Function description 
 * The following is a specific description of each module 
 * @subsection audio_in 2.1 Audio input 
 * Audio input Device ID Correspondence , 0: Corresponding number MIC 1: Corresponding simulation MIC \n
 * Audio input Channel current API Only supports 1 Channels . \n
 * Audio input volume setting , The range of volume is [-30 ~ 120]. -30 Stands for mute ,120 Means to amplify the sound 30dB, Step size 0.5dB. among them 60 Is a critical point for volume setting ，\n
 * The software does not increase or decrease the volume at this value ， When the volume value is less than 60 Time ， Every drop 1， Volume down 0.5dB ; When the volume value is greater than 60 Time ， Increase 1， Volume increase 0.5dB . 
 * @subsection audio_out 2.2 Audio output 
 * Audio output Device ID Correspondence , 0: Corresponding to the default SPK 1: Corresponding to other SPK \n
 * Audio output Channel current API Only supports 1 Channels . \n
 * Audio output volume setting , The range of volume is [-30 ~ 120]. -30 Stands for mute ,120 Means to amplify the sound 30dB, Step size 0.5dB. among them 60 Is a critical point for volume setting ，\n
 * The software does not increase or decrease the volume at this value ， When the volume value is less than 60 Time ， Every drop 1， Volume down 0.5dB ; When the volume value is greater than 60 Time ， Increase 1， Volume increase 0.5dB. \n
 * @subsection audio_aec 2.3 Echo cancellation 
 * Echo cancellation is a function of the audio input interface , Therefore, the audio input device and channel must be enabled before enabling echo cancellation . \n
 * Echo cancellation currently supports audio sampling rate 8K with 16K， The number of data samples in one frame is 10ms Integer multiples of audio data (such as: 8K Sampling Rate ， The data sent is: 8000 × 2 / 100 = 160byte Integer multiples of). \n
 * Echo cancellation for different devices ， Different packages ， Echo cancellation will have different effects . \n
 * Echo cancellation currently does not support adaptive ， So there are separate echo cancellation parameters for different devices , \n
 * The parameter file for echo cancellation is located in /etc/webrtc_profile.ini Configuration file . \n
 * The configuration file format is as follows ( The three main parameters that need to be debugged are listed below ): \n
 * [Set_Far_Frame] \n
 * Frame_V=0.3 \n
 * [Set_Near_Frame] \n
 * Frame_V=0.1 \n
 * delay_ms=150 \n
 *
 * The first label [Set_Far_Frame] The content in represents the remote parameter , which is SPK End playback data parameters . \n
 * Fram_V Represents the audio amplitude ratio , Adjust this parameter to adjust the amplitude of the playback data ( This amplitude is only used for echo cancellation ). \n
 * The first label [Set_Near_Frame] The content in represents the near-end parameter , which is MIC End recording data parameters . \n
 * Fram_V Represents the audio amplitude ratio , Adjust this parameter to adjust the amplitude of the recorded data ( This amplitude is only used for echo cancellation ). \n
 * delay_ms Due to the delay of software and hardware , And SPK versus MIC Is placed at a certain distance ,SPK The playback data will be MIC sampling , and so SPK Data in MIC There will be a certain delay in the data . \n
 * This time represents the time difference between the playback data and the recording data . \n

 * @subsection audio_enc 2.4 Audio coding 
 * Audio encoding current audio API stand by PT_G711A [[[ PT_G711U with PT_G726 Format audio encoding , If you need to add a new encoding method , Need to call IMP_AENC_RegisterEncoder Interface to register encoder .
 * @subsection audio_dec 2.5 Audio decoding 
 * Audio decoding current audio API stand by PT_G711A [[[ PT_G711U with PT_G726 Format audio decoding , If you need to add a new decoding method , Need to call IMP_ADEC_RegisterDecoder Interface to register decoder .
 * @{
 */

/**
 * Maximum number of audio frame buffers 
 */
#define MAX_AUDIO_FRAME_NUM 50

/**
 * Audio stream blocking type 
 */
typedef enum {
	BLOCK = 0,				/**< block */
	NOBLOCK = 1,			/**< Non-blocking */
} IMPBlock;

/**
 * Audio sampling rate definition .
 */
typedef enum {
	AUDIO_SAMPLE_RATE_8000	= 8000,		/**< 8KHz Sampling Rate */
	AUDIO_SAMPLE_RATE_16000 = 16000,	/**< 16KHz Sampling Rate */
	AUDIO_SAMPLE_RATE_24000 = 24000,	/**< 24KHz Sampling Rate */
	AUDIO_SAMPLE_RATE_44100 = 44100,	/**< 44.1KHz Sampling Rate */
	AUDIO_SAMPLE_RATE_48000 = 48000,	/**< 48KHz Sampling Rate */
	AUDIO_SAMPLE_RATE_96000 = 96000,	/**< 96KHz Sampling Rate */
} IMPAudioSampleRate;

/**
 * Audio sampling accuracy definition .
 */
typedef enum {
	AUDIO_BIT_WIDTH_16 = 16,		/**< 16bit Sampling accuracy */
} IMPAudioBitWidth;

/**
 * Audio channel mode definition .
 */
typedef enum {
	AUDIO_SOUND_MODE_MONO	= 1,	/**< Mono */
	AUDIO_SOUND_MODE_STEREO = 2,	/**< Two-channel */
} IMPAudioSoundMode;

/**
 * Define audio payload type enumeration .
 */
typedef enum {
	PT_PCM		= 0,
	PT_G711A	= 1,
	PT_G711U	= 2,
	PT_G726 	= 3,
	PT_AEC		= 4,
	PT_ADPCM	= 5,
	PT_MAX		= 6,
} IMPAudioPalyloadType;

/**
 * Define the decoding method .
 */
typedef enum {
	ADEC_MODE_PACK = 0,	/**< Pack Way to decode */
	ADEC_MODE_STREAM = 1,	/**< Stream Way to decode */
} IMPAudioDecMode;

/**
 * Audio input and output device properties .
 */
typedef struct {
	IMPAudioSampleRate samplerate;		/**< Audio sampling rate */
	IMPAudioBitWidth bitwidth;			/**< Audio sampling accuracy */
	IMPAudioSoundMode soundmode;		/**< Audio channel mode */
	int frmNum;							/**< Number of buffered frames , Ranges :[2, MAX_AUDIO_FRAME_NUM] */
	int numPerFrm;						/**< Number of sampling points per frame */
	int chnCnt;							/**< Number of channels supported */
} IMPAudioIOAttr;

/**
 * Audio frame structure .
 */
typedef struct {
	IMPAudioBitWidth bitwidth;			/**< Audio sampling accuracy */
	IMPAudioSoundMode soundmode;		/**< Audio channel mode */
	uint32_t *virAddr;					/**< Audio frame data virtual address */
	uint32_t phyAddr;					/**< Audio frame data physical address */
	int64_t timeStamp;					/**< Audio frame data timestamp */
	int seq;							/**< Audio frame number */
	int len;							/**< Audio frame length */
} IMPAudioFrame;

/**
 * Audio channel parameter structure .
 */
typedef struct {
	int usrFrmDepth;					/**< Audio frame buffer depth */
	int Rev;							/**< Keep */
} IMPAudioIChnParam;

/**
 * Data buffer status structure of audio output channel .
 */
typedef struct {
	int chnTotalNum;				/**< The total number of buffer blocks of the output channel */
	int chnFreeNum;					/**< Number of free cache blocks */
	int chnBusyNum;					/**< Number of cache blocks occupied */
} IMPAudioOChnState;

/**
 * Define audio stream structure .
 */
typedef struct {
	uint8_t *stream;				/**< Data stream pointer */
	uint32_t phyAddr;				/**< Data stream physical address */
	int len;						/**< Audio stream length */
	int64_t timeStamp;				/**< Timestamp */
	int seq;						/**< Audio stream serial number */
} IMPAudioStream;

/**
 * Define the audio coding channel attribute structure .
 */
typedef struct {
	IMPAudioPalyloadType type;				/**< Audio payload data type */
	int bufSize;							/**< buf size ， In frames ，[2 ~ MAX_AUDIO_FRAME_NUM] */
	uint32_t *value;						/**< Protocol attribute pointer */
} IMPAudioEncChnAttr;

/**
 * Define encoder attribute structure .
 */
typedef struct {
	IMPAudioPalyloadType type;		/**< Encoding protocol type */
	int maxFrmLen;					/**< Maximum stream length */
	char name[16];					/**< Encoder name */
	int (*openEncoder)(void *encoderAttr, void
			*encoder);
	int (*encoderFrm)(void *encoder, IMPAudioFrame
			*data, unsigned char *outbuf,int *outLen);
	int (*closeEncoder)(void *encoder);
} IMPAudioEncEncoder;

/**
 * Define the decoding channel attribute structure .
 */
typedef struct {
	IMPAudioPalyloadType type;			/**< Audio decoding protocol type */
	int bufSize;						/**< Audio decoding buffer size */
	IMPAudioDecMode mode;				/**< Decoding method */
	void *value;						/**< Specific protocol attribute pointer */
} IMPAudioDecChnAttr;

/**
 * Define decoder attribute structure .
 */
typedef struct {
	IMPAudioPalyloadType type;		/**< Audio decoding protocol type */
	char name[16];					/**< Audio decoder name */
	int (*openDecoder)(void *decoderAttr, void
			*decoder);
	int (*decodeFrm)(void *decoder, unsigned char
			*inbuf,int inLen, unsigned short *outbuf,int
			*outLen,int *chns);
	int (*getFrmInfo)(void *decoder, void *info);
	int (*closeDecoder)(void *decoder);
} IMPAudioDecDecoder;

/**
 * definition AGC Gain structure .
 */
typedef struct {
	int TargetLevelDbfs;	/**< Gain level , The value is [0, 31], This refers to the target volume level , the unit is db, Negative . The smaller the value , Louder . */
	int CompressionGaindB;	/**< Set the maximum gain value ,[0, 90],0 Means no gain , Higher value , Higher gain . */
} IMPAudioAgcConfig;

/**
 * Define noise suppression level .
 */
enum Level_ns {
	NS_LOW,			/**< Low-level noise suppression */
	NS_MODERATE,	/**< Mid-level noise suppression */
	NS_HIGH,		/**< High-level noise suppression */
	NS_VERYHIGH		/**< The highest level of noise suppression */
};

/**
 * @fn int IMP_AI_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr)
 *
 * Set audio input device properties .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] attr Audio device attribute pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Sample code 
 * @code
 * int devID = 1;
 * IMPAudioIOAttr attr;
 * attr.samplerate = AUDIO_SAMPLE_RATE_8000;
 * attr.bitwidth = AUDIO_BIT_WIDTH_16;
 * attr.soundmode = AUDIO_SOUND_MODE_MONO;
 * attr.frmNum = 20;
 * attr.numPerFrm = 400;
 * attr.chnCnt = 1;
 * ret = IMP_AI_SetPubAttr(devID, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Set Audio in %d attr err: %d\n", devID, ret);
 *		return ret;
 * }
 * @endcode
 *
 * @attention Need to be in IMP_AI_Enable Call before .
 */
int IMP_AI_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AI_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr)
 *
 * Get audio input device properties .
 *
 * @param[in] audioDevId Audio device number .
 * @param[out] attr Audio device attribute pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AI_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AI_Enable(int audioDevId)
 *
 * Enable audio input device .
 *
 * @param[in] audioDevId Audio device number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention Must be called before calling this function IMP_AI_SetPubAttr().
 */
int IMP_AI_Enable(int audioDevId);

/**
 * @fn int IMP_AI_Disable(int audioDevId)
 *
 * Disable audio input device .
 *
 * @param[in] audioDevId Audio device number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention versus IMP_AI_Enable Supporting the use of , Must be executed before the system sleeps IMP_AI_Disable.
 */
int IMP_AI_Disable(int audioDevId);

/**
 * @fn int IMP_AI_EnableChn(int audioDevId, int aiChn)
 *
 * Enable audio input channel .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aiChn Audio input channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention Must be enabled first device.
 */
int IMP_AI_EnableChn(int audioDevId, int aiChn);

/**
 * @fn int IMP_AI_DisableChn(int audioDevId, int aiChn)
 *
 * Disable audio input channel .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aiChn Audio input channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention versus IMP_AI_EnableChn Supporting the use of .
 */
int IMP_AI_DisableChn(int audioDevId, int aiChn);

/**
 * @fn int IMP_AI_PollingFrame(int audioDevId, int aiChn, unsigned int timeout_ms)
 *
 * Polling Audio stream buffer .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aiChn Audio input channel number .
 * @param[in] timeout_ms Polling overtime time .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention In use IMP_AI_GetFrame Use this interface before ， When the interface is successfully called, it means audio 
 *			 Data is ready ， can use IMP_AI_GetFrame Get audio data .
 */
int IMP_AI_PollingFrame(int audioDevId, int aiChn, unsigned int timeout_ms);

/**
 * @fn int IMP_AI_GetFrame(int audioDevId, int aiChn, IMPAudioFrame *frm, IMPBlock block)
 *
 * Get audio frame .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aiChn Audio input channel number .
 * @param[out] frm Audio frame structure pointer .
 * @param[in] block block / Non-blocking flag .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Sample code 
 * @code
 * IMPAudioFrame frm;
 * // Get audio frame 
 * ret = IMP_AI_GetFrame(devID, chnID, &frm, BLOCK);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Get Frame Data error\n");
 *		return ret;
 * }
 *
 * fwrite(frm.virAddr, 1, frm.len, record_file); // Use audio frame data 
 *
 * // Release audio frame 
 * ret = IMP_AI_ReleaseFrame(devID, chnID, &frm);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio release frame data error\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention no .
 */
int IMP_AI_GetFrame(int audioDevId, int aiChn, IMPAudioFrame *frm, IMPBlock block);

/**
 * @fn int IMP_AI_ReleaseFrame(int audioDevId, int aiChn, IMPAudioFrame *frm)
 *
 * Release audio frame .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aiChn Audio input channel number .
 * @param[in] frm Audio frame structure pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention versus IMP_AI_GetFrame Supporting the use of .
 */
int IMP_AI_ReleaseFrame(int audioDevId, int aiChn, IMPAudioFrame *frm);

/**
 * @fn int IMP_AI_SetChnParam(int audioDevId, int aiChn, IMPAudioIChnParam *chnParam)
 *
 * Set audio input channel parameters .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aiChn Audio input channel number .
 * @param[in] chnParam Audio channel parameters .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Sample code 
 * @code
 * int chnID = 0;
 * IMPAudioIChnParam chnParam;
 * chnParam.usrFrmDepth = 20;	// the range of valid value is [2, MAX_AUDIO_FRAME_NUM].
 * ret = IMP_AI_SetChnParam(devID, chnID, &chnParam);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "set ai %d channel %d attr err: %d\n", devID, chnID, ret);
 *		return ret;
 * }
 * @endcode
 *
 * @attention in IMP_AI_EnableChn Call before .
 */
int IMP_AI_SetChnParam(int audioDevId, int aiChn, IMPAudioIChnParam *chnParam);

/**
 * @fn int IMP_AI_GetChnParam(int audioDevId, int aiChn, IMPAudioIChnParam *chnParam)
 *
 * Get audio input channel parameters .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aiChn Audio input channel number .
 * @param[out] chnParam Audio channel parameters .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AI_GetChnParam(int audioDevId, int aiChn, IMPAudioIChnParam *chnParam);

/**
 * @fn int IMP_AI_EnableAec(int aiDevId, int aiChn, int aoDevId, int aoChn)
 *
 * Enable the echo cancellation function of the specified audio input and audio output .
 *
 * @param[in] aiDevId Audio input device number that needs echo cancellation .
 * @param[in] aiChn Audio input channel number that needs echo cancellation .
 * @param[in] aoDevId Audio output device number that needs echo cancellation .
 * @param[in] aoChn Audio output channel number that needs echo cancellation .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Echo cancellation for different devices ， Different packages ， Echo cancellation will have different effects .
 * @remarks Echo cancellation currently does not support adaptive ， So there are separate echo cancellation parameters for different devices ,
 * @remarks Just enabling the function is not necessarily good. 
 * @remarks The parameter file for echo cancellation is located in /etc/webrtc_profile.ini Configuration file .
 * @remarks The configuration file format is as follows ( The three main parameters that need to be debugged are listed below ):
 * @remarks [Set_Far_Frame]
 * @remarks Frame_V=0.3
 * @remarks [Set_Near_Frame]
 * @remarks Frame_V=0.1
 * @remarks delay_ms=150
 *
 * @remarks The first label [Set_Far_Frame] The content in represents the remote parameter , which is SPK End playback data parameters .
 * @remarks Fram_V Represents the audio amplitude ratio , Adjust this parameter to adjust the amplitude of the playback data ( This amplitude is only used for echo cancellation ).
 * @remarks The first label [Set_Near_Frame] The content in represents the near-end parameter , which is MIC End recording data parameters .
 * @remarks Fram_V Represents the audio amplitude ratio , Adjust this parameter to adjust the amplitude of the recorded data ( This amplitude is only used for echo cancellation ).
 * @remarks delay_ms Due to the delay of software and hardware , And SPK versus MIC Is placed at a certain distance ,SPK The playback data will be MIC sampling , and so SPK Data in MIC There will be a certain delay in the data .
 * @remarks This time represents the time difference between the playback data and the recording data .
 *
 * @attention Actually the interface will only check aiDevId with aiChn. But it is best to call after the two channels are enabled at the same time . \n
 * While closing the audio input channel , The echo cancellation function is turned off at the same time . If you need to use it again, you need to open it again .
 */
int IMP_AI_EnableAec(int aiDevId, int aiChn, int aoDevId, int aoChn);

/**
 * @fn int IMP_AI_DisableAec(int aiDevId, int aiChn)
 *
 * Disable echo cancellation .
 *
 * @param[in] aiDevId Audio input device number .
 * @param[in] aiChn Audio input channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AI_DisableAec(int aiDevId, int aiChn);

/**
 * @fn int IMP_AI_EnableNs(IMPAudioIOAttr *attr, int mode)
 *
 * Enable the noise suppression function of the specified audio input .
 *
 * @param[in] attr Audio attributes that require noise suppression .
 * @param[in] mode Noise suppression level 0 ~ 3, See Level_ns.
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Noise suppressed mode The parameter indicates the level of noise suppression , Range is [0 ~ 3], The higher the level , The cleaner the noise suppression .
 * @remarks however , The cleaner the noise suppression, the more sound details will be lost , So there is a contradiction here , Need to be in 
 * @remarks Make trade-offs when using .
 *
 * @attention Echo cancellation includes noise suppression , If echo cancellation is enabled , No need to do noise suppression .
 */
int IMP_AI_EnableNs(IMPAudioIOAttr *attr, int mode);

/**
 * @fn int IMP_AI_DisableNs(void)
 *
 * Disable noise suppression .
 *
 * @param no .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AI_DisableNs(void);

/**
 * @fn int IMP_AI_EnableAgc(IMPAudioIOAttr *attr, IMPAudioAgcConfig agcConfig)
 *
 * Enable the automatic gain function of audio input .
 *
 * @param[in] attr Audio attributes that require automatic gain .
 * @param[in] agcConfig Parameter configuration of automatic gain , Configure magnification .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks requires attention agcConfig Configuration ,AGC The magnification mainly has the parameter configuration , See for specific gains IMPAudioAgcConfig Description .
 * @remarks have to be aware of is ,AGC Can amplify the gain of the sound , But if the gain parameter is not suitable , It will cause the sound to break, etc. , Please adjust yourself when you use it .
 *
 * @attention Echo cancellation includes AGC Features , If echo cancellation is enabled , No need to do automatic gain .
 */
int IMP_AI_EnableAgc(IMPAudioIOAttr *attr, IMPAudioAgcConfig agcConfig);

/**
 * @fn int IMP_AI_DisableAgc(void)
 *
 * Disable AI Automatic gain function .
 *
 * @param no .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AI_DisableAgc(void);

/**
 * @fn int IMP_AO_EnableAgc(IMPAudioIOAttr *attr, IMPAudioAgcConfig agcConfig)
 *
 * Enable the automatic gain function of audio output .
 *
 * @param[in] attr Audio attributes that require automatic gain .
 * @param[in] agcConfig Parameter configuration of automatic gain , Configure magnification .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks requires attention agcConfig Configuration ,AGC The magnification mainly has the parameter configuration , See for specific gains IMPAudioAgcConfig Description .
 * @remarks have to be aware of is ,AGC Can amplify the gain of the sound , But if the gain parameter is not suitable , It will cause the sound to break, etc. , Please adjust yourself when you use it .
 *
 * @attention Echo cancellation includes AGC Features , If echo cancellation is enabled , No need to do automatic gain .
 */
int IMP_AO_EnableAgc(IMPAudioIOAttr *attr, IMPAudioAgcConfig agcConfig);

/**
 * @fn int IMP_AO_DisableAgc(void)
 *
 * Disable AO Automatic gain function .
 *
 * @param no .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AO_DisableAgc(void);

/**
 * @fn int IMP_AI_EnableHpf(IMPAudioIOAttr *attr)
 *
 * Enable high-pass filtering of audio input .
 *
 * @param[in] attr Audio attributes that require high-pass filtering .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention Echo cancellation includes HPF Features , If echo cancellation is enabled , No need to do HPF.
 */
int IMP_AI_EnableHpf(IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AI_DisableHpf(void)
 *
 * Disable AI High pass filter function .
 *
 * @param no .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AI_DisableHpf(void);

/**
 * @fn int IMP_AO_EnableHpf(IMPAudioIOAttr *attr)
 *
 * Enable high-pass filtering of audio output .
 *
 * @param[in] attr Audio attributes that require high-pass filtering .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention Echo cancellation includes HPF Features , If echo cancellation is enabled , No need to do HPF.
 */
int IMP_AO_EnableHpf(IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AO_DisableHpf(void)
 *
 * Disable AO High pass filter function .
 *
 * @param no .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AO_DisableHpf(void);

/**
 * @fn int IMP_AO_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr)
 *
 * Set audio input and output device properties .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] attr Audio output device attribute pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AO_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AO_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr)
 *
 * Get audio input and output device properties .
 *
 * @param[in] audioDevId Audio device number .
 * @param[out] attr Audio output device attribute pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AO_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

/**
 * @fn int IMP_AO_Enable(int audioDevId)
 *
 * Enable audio output device .
 *
 * @param[in] audioDevId Audio device number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention Must be called before enabling IMP_AO_SetPubAttr.
 */
int IMP_AO_Enable(int audioDevId);

/**
 * @fn int IMP_AO_Disable(int audioDevId)
 *
 * Disable audio output device .
 *
 * @param[in] audioDevId Audio device number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AO_Disable(int audioDevId);

/**
 * @fn int IMP_AO_EnableChn(int audioDevId, int aoChn)
 *
 * Enable audio output channel .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aoChn Audio output channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AO_EnableChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_DisableChn(int audioDevId, int aoChn)
 *
 * Disable audio output channel .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aoChn Audio output channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AO_DisableChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_SendFrame(int audioDevId, int aoChn, IMPAudioFrame *data, IMPBlock block)
 *
 * Send audio output frame .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aoChn Audio output channel number .
 * @param[in] data Audio frame structure pointer .
 * @param[in] block block / Non-blocking flag .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Sample code 
 * @code
 * while(1) {
 *		size = fread(buf, 1, IMP_AUDIO_BUF_SIZE, play_file);
 *		if(size < IMP_AUDIO_BUF_SIZE)
 *			break;
 *
 *		IMPAudioFrame frm;
 *		frm.virAddr = (uint32_t *)buf;
 *		frm.len = size;
 *		ret = IMP_AO_SendFrame(devID, chnID, &frm, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "send Frame Data error\n");
 *			return ret;
 *		}
 * }
 * @endcode
 *
 * @attention no .
 */
int IMP_AO_SendFrame(int audioDevId, int aoChn, IMPAudioFrame *data, IMPBlock block);

/**
 * @fn int IMP_AO_PauseChn(int audioDevId, int aoChn)
 *
 * Pause audio output channel .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aoChn Audio output channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AO_PauseChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_ResumeChn(int audioDevId, int aoChn)
 *
 * Restore audio output channel .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aoChn Audio output channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AO_ResumeChn(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_ClearChnBuf(int audioDevId, int aoChn)
 *
 * Clear the current audio data buffer in the audio output channel .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aoChn Audio output channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AO_ClearChnBuf(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_QueryChnStat(int audioDevId, int aoChn, IMPAudioOChnState *status)
 *
 * Query the current audio data buffer status in the audio output channel .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aoChn Audio output channel number .
 * @param[out] status Cache state structure pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
int IMP_AO_QueryChnStat(int audioDevId, int aoChn, IMPAudioOChnState *status);

/**
 * @fn int IMP_AENC_CreateChn(int aeChn, IMPAudioEncChnAttr *attr)
 *
 * Create audio encoding channel .
 *
 * @param[in] aeChn Channel number .
 * @param[in] attr Audio encoding channel attribute pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Sample code 
 * @code
 * int AeChn = 0;
 * IMPAudioEncChnAttr attr;
 * attr.type = PT_G711A;
 * attr.bufSize = 20;
 * ret = IMP_AENC_CreateChn(AeChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio encode create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention Currently SDK stand by PT_G711A [[[ PT_G711U with PT_G726 coding . \n
 * So use SDK Encoding in , only need to attr.type = PT_G711A Can . \n
 * How to use a custom encoder , You need to register the encoder , The sample code is explained in the registration interface .
 */
 int IMP_AENC_CreateChn(int aeChn, IMPAudioEncChnAttr *attr);

/**
 * @fn int IMP_AENC_DestroyChn(int aeChn)
 *
 * Destroy the audio encoding channel .
 *
 * @param[in] aeChn Channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention versus IMP_AENC_CreateChn Supporting the use of .
 */
 int IMP_AENC_DestroyChn(int aeChn);

/**
 * @fn int IMP_AENC_SendFrame(int aeChn, IMPAudioFrame *frm)
 *
 * Send audio encoded audio frames .
 *
 * @param[in] aeChn Channel number .
 * @param[in] frm Audio frame structure pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Sample code 
 * @code
 * while(1) {
 *		// Read a frame of data 
 *		ret = fread(buf_pcm, 1, IMP_AUDIO_BUF_SIZE, file_pcm);
 *		if(ret < IMP_AUDIO_BUF_SIZE)
 *			break;
 *
 *		// coding 
 *		IMPAudioFrame frm;
 *		frm.virAddr = (uint32_t *)buf_pcm;
 *		frm.len = ret;
 *		ret = IMP_AENC_SendFrame(AeChn, &frm);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode send frame failed\n");
 *			return ret;
 *		}
 *
 *		// Get code stream 
 *		IMPAudioStream stream;
 *		ret = IMP_AENC_GetStream(AeChn, &stream, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode get stream failed\n");
 *			return ret;
 *		}
 *
 *		// Use code stream 
 *		fwrite(stream.stream, 1, stream.len, file_g711);
 *
 *		// Release code stream 
 *		ret = IMP_AENC_ReleaseStream(AeChn, &stream);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode release stream failed\n");
 *			return ret;
 *		}
 * }
 * @endcode
 *
 * @attention no .
 */
 int IMP_AENC_SendFrame(int aeChn, IMPAudioFrame *frm);

/**
 * @fn int IMP_AENC_PollingStream(int AeChn, unsigned int timeout_ms)
 *
 * Polling Encoded audio stream buffer .
 *
 * @param[in] AeChn Audio encoding input channel number .
 * @param[in] timeout_ms Polling overtime time .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention In use IMP_AENC_GetStream Use this interface before ， When the interface is successfully called, it means audio 
 *			 The encoded data is ready ， can use IMP_AENC_GetStream Get the encoded data .
 */
int IMP_AENC_PollingStream(int AeChn, unsigned int timeout_ms);

/**
 * @fn int IMP_AENC_GetStream(int aeChn, IMPAudioStream *stream ,IMPBlock block)
 *
 * Get the code stream after encoding .
 *
 * @param[in] aeChn Channel number .
 * @param[in] stream Get audio stream .
 * @param[in] block block / Non-blocking flag .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks See sample code IMP_AENC_SendFrame Function description .
 *
 * @attention no .
 */
 int IMP_AENC_GetStream(int aeChn, IMPAudioStream *stream ,IMPBlock block);

/**
 * @fn int IMP_AENC_ReleaseStream(int aeChn,IMPAudioStream *stream)
 *
 * Release the code stream obtained from the audio encoding channel .
 *
 * @param[in] aeChn Channel number .
 * @param[in] stream Get audio stream pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks See sample code IMP_AENC_SendFrame Function description .
 *
 * @attention no .
 */
 int IMP_AENC_ReleaseStream(int aeChn,IMPAudioStream *stream);

/**
 * @fn int IMP_AENC_RegisterEncoder(int *handle, IMPAudioEncEncoder *encoder)
 *
 * Register encoder .
 *
 * @param[in] ps32handle Register handle .
 * @param[in] encoder Encoder attribute structure .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Sample code 
 * @code
 * int handle_g711a = 0;
 * IMPAudioEncEncoder my_encoder;
 * my_encoder.maxFrmLen = 1024;
 * sprintf(my_encoder.name, "%s", "MY_G711A");
 * my_encoder.openEncoder = NULL; // Encoder callback function 
 * my_encoder.encoderFrm = MY_G711A_Encode_Frm; // Encoder callback function 
 * my_encoder.closeEncoder = NULL; // Encoder callback function 
 *
 * ret = IMP_AENC_RegisterEncoder(&handle_g711a, &my_encoder);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "IMP_AENC_RegisterEncoder failed\n");
 *		return ret;
 * }
 *
 * // Use encoder 
 * int AeChn = 0;
 * IMPAudioEncChnAttr attr;
 * attr.type = handle_g711a; // Encoder type Equal to the return of successful registration handle_g711a The value of .
 * attr.bufSize = 20;
 * ret = IMP_AENC_CreateChn(AeChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "imp audio encode create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention How to use and use after registration SDK The same as the built-in encoder .
 */
 int IMP_AENC_RegisterEncoder(int *handle, IMPAudioEncEncoder *encoder);

/**
 * @fn int IMP_AENC_ReleaseEncoder(int *handle)
 *
 * Log out of encoder .
 *
 * @param[in] ps32handle Register handle ( Handle obtained when registering the encoder ).
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
 int IMP_AENC_ReleaseEncoder(int *handle);

/**
 * @fn int IMP_ADEC_CreateChn(int adChn, IMPAudioDecChnAttr *attr)
 *
 * Create audio decoding channel .
 *
 * @param[in] adChn Channel number .
 * @param[in] attr Channel attribute pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Sample code 
 * @code
 * int adChn = 0;
 * IMPAudioDecChnAttr attr;
 * attr.type = PT_G711A;
 * attr.bufSize = 20;
 * attr.mode = ADEC_MODE_PACK;
 * ret = IMP_ADEC_CreateChn(adChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "imp audio decoder create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention no .
 */
 int IMP_ADEC_CreateChn(int adChn, IMPAudioDecChnAttr *attr);

/**
 * @fn int IMP_ADEC_DestroyChn(int adChn)
 *
 * Destroy audio decoding channel .
 *
 * @param[in] adChn Channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
 int IMP_ADEC_DestroyChn(int adChn);

/**
 * @fn int IMP_ADEC_SendStream(int adChn, IMPAudioStream *stream, IMPBlock block)
 *
 * Send audio code stream to audio decoding channel .
 *
 * @param[in] adChn Channel number .
 * @param[in] stream Audio stream .
 * @param[in] block block / Non-blocking flag .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Sample code 
 * @code
 * while(1) {
 *		// Get the data that needs to be decoded 
 *		ret = fread(buf_g711, 1, IMP_AUDIO_BUF_SIZE/2, file_g711);
 *		if(ret < IMP_AUDIO_BUF_SIZE/2)
 *			break;
 *
 *		// Send decoded data 
 *		IMPAudioStream stream_in;
 *		stream_in.stream = (uint8_t *)buf_g711;
 *		stream_in.len = ret;
 *		ret = IMP_ADEC_SendStream(adChn, &stream_in, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode send frame failed\n");
 *			return ret;
 *		}
 *
 *		// Get the decoded data 
 *		IMPAudioStream stream_out;
 *		ret = IMP_ADEC_GetStream(adChn, &stream_out, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio decoder get stream failed\n");
 *			return ret;
 *		}
 *
 *		// Use decoded data 
 *		fwrite(stream_out.stream, 1, stream_out.len, file_pcm);
 *
 *		// Release the decoded data 
 *		ret = IMP_ADEC_ReleaseStream(adChn, &stream_out);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio decoder release stream failed\n");
 *			return ret;
 *		}
 * }
 * @endcode
 *
 * @attention no .
 */
 int IMP_ADEC_SendStream(int adChn, IMPAudioStream *stream, IMPBlock block);

/**
 * @fn int IMP_ADEC_PollingStream(int AdChn, unsigned int timeout_ms)
 *
 * Polling Decode audio stream buffer .
 *
 * @param[in] AdChn Audio decoding input channel number .
 * @param[in] timeout_ms Polling overtime time .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention In use IMP_ADEC_GetStream Use this interface before ， When the interface is successfully called, it means audio 
 *			 The decoded data is ready ， can use IMP_ADEC_GetStream Get the decoded data .
 */
int IMP_ADEC_PollingStream(int AdChn, unsigned int timeout_ms);

/**
 * @fn int IMP_ADEC_GetStream(int adChn, IMPAudioStream *stream ,IMPBlock block)
 *
 * Get the decoded code stream .
 *
 * @param[in] adChn Channel number .
 * @param[in] stream Get decoded code stream .
 * @param[in] block block / Non-blocking flag .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks See sample code IMP_ADEC_SendStream Function description .
 *
 * @attention no .
 */
int IMP_ADEC_GetStream(int adChn, IMPAudioStream *stream ,IMPBlock block);

/**
 * @fn int IMP_ADEC_ReleaseStream(int adChn,IMPAudioStream *stream)
 *
 * Release the code stream obtained from the audio decoding channel .
 *
 * @param[in] adChn Channel number .
 * @param[in] stream Audio stream pointer .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks See sample code IMP_ADEC_SendStream Function description .
 *
 * @attention no .
 */
int IMP_ADEC_ReleaseStream(int adChn,IMPAudioStream *stream);

/**
 * @fn int IMP_ADEC_ClearChnBuf(int adChn)
 *
 * Clear the current audio data buffer in the audio decoding channel .
 *
 * @param[in] adChn Channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
 int IMP_ADEC_ClearChnBuf(int adChn);

/**
 * @fn int IMP_ADEC_RegisterDecoder(int *handle, IMPAudioDecDecoder *decoder)
 *
 * Register the decoder .
 *
 * @param[in] ps32handle Register handle .
 * @param[in] decoder Decoder attribute structure .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Sample code 
 * @code
 * int handle_g711a = 0;
 * IMPAudioDecDecoder my_decoder;
 * sprintf(my_decoder.name, "%s", "MY_G711A");
 * my_decoder.openDecoder = NULL; // Decoder callback function 
 * my_decoder.decodeFrm = MY_G711A_Decode_Frm; // Decoder callback function 
 * my_decoder.getFrmInfo = NULL; // Decoder callback function 
 * my_decoder.closeDecoder = NULL; // Decoder callback function 
 *
 * // Register the decoder 
 * ret = IMP_ADEC_RegisterDecoder(&handle_g711a, &my_decoder);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "IMP_ADEC_RegisterDecoder failed\n");
 *		return ret;
 * }
 *
 * // Use decoder 
 * int adChn = 0;
 * IMPAudioDecChnAttr attr;
 * attr.type = handle_g711a; // decoding type Equal to that returned by the decoder registration handle_g711a.
 * attr.bufSize = 20;
 * attr.mode = ADEC_MODE_PACK;
 * // Create a decoding channel 
 * ret = IMP_ADEC_CreateChn(adChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "imp audio decoder create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention How to use and use after registration SDK The same as the built-in decoder .
 */
 int IMP_ADEC_RegisterDecoder(int *handle, IMPAudioDecDecoder *decoder);

/**
 * @fn int IMP_ADEC_ReleaseDecoder(int *handle)
 *
 * Unregister decoder .
 *
 * @param[in] ps32handle Register handle ( Handle obtained when registering the decoder ).
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
 int IMP_ADEC_ReleaseDecoder(int *handle);

/**
 * ACODEC Configuration .
 */
/**
 * @fn int IMP_AI_SetVol(int audioDevId, int aiChn, int aiVol)
 *
 * Set audio input volume .
 *
 * @param[in] aiDevId Audio input device number .
 * @param[in] aiChn Audio input channel number .
 * @param[in] aiVol Audio input volume .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks The range of volume is [-30 ~ 120]. -30 Stands for mute ,120 Means to amplify the sound 30dB, Step size 0.5dB.
 * @remarks among them 60 Is a critical point for volume setting ， The software does not increase or decrease the volume at this value ， When the volume value is less than 60 Time ， Every drop 1， Volume down 0.5dB ; When the volume value is greater than 60 Time ， Increase 1， Volume increase 0.5dB . 
 *
 * Sample code 
 * @code
 * int volume = 60;
 * ret = IMP_AI_SetVol(devID, chnID, volume);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Record set volume failed\n");
 *		return ret;
 * }
 * @endcode
 * @attention If you enter aiVol exceeded [-30 ~ 120] The scope of , Less than -30 Will take -30, more than the 120 Take 120.
 */
 int IMP_AI_SetVol(int audioDevId, int aiChn, int aiVol);

/**
 * @fn int IMP_AI_GetVol(int audioDevId, int aiChn, int *vol)
 *
 * Get audio input volume .
 *
 * @param[in] aiDevId Audio input device number .
 * @param[in] aiChn Audio input channel number .
 * @param[out] vol Audio input channel volume .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
 int IMP_AI_GetVol(int audioDevId, int aiChn, int *vol);

/**
 * @fn int IMP_AI_SetVolMute(int audioDevId, int aiChn, int mute)
 *
 * Set audio input mute .
 *
 * @param[in] aiDevId Audio input device number .
 * @param[in] aiChn Audio input channel number .
 * @param[out] mute Audio input mute sign , mute = 0: Mute off , mute = 1: Turn on mute .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Call this interface to mute immediately .
 *
 * @attention no .
 */
 int IMP_AI_SetVolMute(int audioDevId, int aiChn, int mute);

/**
 * @fn int IMP_AO_SetVol(int audioDevId, int aoChn, int aoVol)
 *
 * Set audio output channel volume .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aoChn Audio output channel number .
 * @param[in] aoVol Audio output volume .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks The range of volume is [-30 ~ 120]. -30 Stands for mute ,120 Means to amplify the sound 30dB, Step size 0.5dB.
 * @remarks among them 60 Is a critical point for volume setting ， The software does not increase or decrease the volume at this value ， When the volume value is less than 60 Time ， Every drop 1， Volume down 0.5dB ; When the volume value is greater than 60 Time ， Increase 1， Volume increase 0.5dB . 
 *
 * @attention If you enter aoVol exceeded [-30 ~ 120] The scope of , Less than -30 Will take -30, more than the 120 Take 120.
 */
 int IMP_AO_SetVol(int audioDevId, int aoChn, int aoVol);

/**
 * @fn int IMP_AO_GetVol(int audioDevId, int aoChn, int *vol)
 *
 * Get audio output channel volume .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aoChn Audio output channel number .
 * @param[out] aoVol Audio output volume .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
 int IMP_AO_GetVol(int audioDevId, int aoChn, int *vol);

/**
 * @fn int IMP_AO_SetVolMute(int audioDevId, int aoChn, int mute)
 *
 * Set audio output mute .
 *
 * @param[in] audioDevId Audio output device number .
 * @param[in] aoChn Audio output channel number .
 * @param[out] mute Audio output mute sign , mute = 0: Mute off , mute = 1: Turn on mute .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Call this interface to mute immediately .
 *
 * @attention no .
 */
 int IMP_AO_SetVolMute(int audioDevId, int aoChn, int mute);

/**
 * @fn int IMP_AI_SetGain(int audioDevId, int aiChn, int aiGain)
 *
 * Set audio input gain .
 *
 * @param[in] audioDevId Audio input device number .
 * @param[in] aiChn Audio input channel number .
 * @param[out] aiGain Audio input gain , range [0 ~ 31].
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention aiGain The range is [0 ~ 31], If the value entered is less than 0, then aiGain The value will be \n
 * set as 0. If the value is greater than 31,aiGain Will be set to 10.
 *
 */
 int IMP_AI_SetGain(int audioDevId, int aiChn, int aiGain);

/**
 * @fn int IMP_AI_GetGain(int audioDevId, int aiChn, int *aiGain)
 *
 * Obtain AI Gain value .
 *
 * @param[in] audioDevId Audio input device number .
 * @param[in] aiChn Audio input channel number .
 * @param[out] aiGain Audio input gain .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
 int IMP_AI_GetGain(int audioDevId, int aiChn, int *aiGain);

/**
 * @fn int IMP_AO_SetGain(int audioDevId, int aoChn, int aoGain)
 *
 * Set audio output gain .
 *
 * @param[in] audioDevId Audio output device number .
 * @param[in] aoChn Audio output channel number .
 * @param[out] aoGain Audio output gain , range [0 ~ 0xcb].
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention aoGain The range is [0 ~ 31], If the value entered is less than 0, then aoGain The value will be \n
 * set as 0. If the value is greater than 31,aoGain Will be set to 31.
 *
 */
 int IMP_AO_SetGain(int audioDevId, int aoChn, int aoGain);

/**
 * @fn int IMP_AO_GetGain(int audioDevId, int aoChn, int *aoGain)
 *
 * Get audio output gain .
 *
 * @param[in] audioDevId Audio output device number .
 * @param[in] aoChn Audio output channel number .
 * @param[out] aoGain Audio output gain .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 *
 * @attention no .
 */
 int IMP_AO_GetGain(int audioDevId, int aoChn, int *aoGain);

/**
 * @fn int IMP_AO_Soft_Mute(int audioDevId, int aoChn)
 *
 * Output soft mute control .
 *
 * @param[in] audioDevId Audio output device number .
 * @param[in] aoChn Audio output channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Calling this interface will not immediately mute ， Will slowly lower the volume from the normal playback state ， Until it's really silent .
 *
 * @attention no .
 */
 int IMP_AO_Soft_Mute(int audioDevId, int aoChn);

/**
 * @fn int IMP_AO_Soft_UNMute(int audioDevId, int aoChn)
 *
 * Output soft unmute control .
 *
 * @param[in] audioDevId Audio output device number .
 * @param[in] aoChn Audio output channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Calling this interface will not immediately restore the current volume ， Will slowly increase the volume from the mute state ， Until the volume reaches the set volume .
 *
 * @attention no .
 */
 int IMP_AO_Soft_UNMute(int audioDevId, int aoChn);

/**
 * @fn int IMP_AI_GetFrameAndRef(int audioDevId, int aiChn, IMPAudioFrame *frm, IMPAudioFrame *ref, IMPBlock block)
 *
 * Get audio frame and output reference frame .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aiChn Audio input channel number .
 * @param[out] frm Audio frame structure pointer .
 * @param[out] ref Reference frame structure pointer .
 * @param[in] block block / Non-blocking flag .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks Sample code 
 * @code
 * IMPAudioFrame frm;
 * IMPAudioFrame ref;
 * // Get audio frame and output reference frame 
 * ret = IMP_AI_GetFrameAndRef(devID, chnID, &frm, &ref, BLOCK);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Get Frame Data error\n");
 *		return ret;
 * }
 *
 * fwrite(frm.virAddr, 1, frm.len, record_file); // Use audio frame data 
 * fwrite(ref.virAddr, 1, ref.len, ref_file); // Use audio reference frames 
 *
 * // Release audio frame 
 * ret = IMP_AI_ReleaseFrame(devID, chnID, &frm);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio release frame data error\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention no .
 */
 int IMP_AI_GetFrameAndRef(int audioDevId, int aiChn, IMPAudioFrame *frm, IMPAudioFrame *ref, IMPBlock block);

/**
 * @fn int IMP_AI_EnableAecRefFrame(int audioDevId, int aiChn, int audioAoDevId, int aoChn)
 *
 * Open to get reference frame .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aiChn Audio input channel number .
 * @param[in] audioAoDevId Audio output device number .
 * @param[in] aoChn Audio output channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks transfer IMP_AI_GetFrameAndRef Call this interface before .
 * @attention no .
 */
 int IMP_AI_EnableAecRefFrame(int audioDevId, int aiChn, int audioAoDevId, int aoChn);

/**
 * @fn int IMP_AI_DisableAecRefFrame(int audioDevId, int aiChn, int audioAoDevId, int aoChn)
 *
 * Close Get Reference Frame .
 *
 * @param[in] audioDevId Audio device number .
 * @param[in] aiChn Audio input channel number .
 * @param[in] audioAoDevId Audio output device number .
 * @param[in] aoChn Audio output channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 * @attention no .
 */
 int IMP_AI_DisableAecRefFrame(int audioDevId, int aiChn, int audioAoDevId, int aoChn);

/**
 * @fn int IMP_AO_CacheSwitch(int audioDevId, int aoChn, int cache_en)
 * Turn off the audio playback caching mechanism 
 * @param[in] audioDevId Audio device number .
 * @param[in] aoChn Audio output channel number .
 * @param[in] cache_en Caching mechanism on switch 
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 * @attention no .
 */
 int IMP_AO_CacheSwitch(int audioDevId, int aoChn, int cache_en);

/**
 * @fn int IMP_AO_FlushChnBuf(int audioDevId, int aoChn);
 * Wait for the last piece of audio data to be played ;
 * @param[in] audioDevId Audio device number .
 * @param[in] aoChn Audio output channel number .
 *
 * @retval 0 success .
 * @retval non- 0 failure .
 *
 * @remarks no .
 * @attention no .
 */
 int IMP_AO_FlushChnBuf(int audioDevId, int aoChn);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_AUDIO_H__ */
