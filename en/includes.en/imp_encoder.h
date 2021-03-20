/*
 * IMP Encoder func header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_ENCODER_H__
#define __IMP_ENCODER_H__

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
 * IMP Video encoding header file 
 */

/**
 * @defgroup IMP_Encoder
 * @ingroup imp
 * @brief Video encoding ( H264, JPEG ) Module ， Contains encoding channel management ， Encoding parameter setting and other functions 
 * @section enc_struct 1 Module structure 
 * Encoder The internal structure of the module is as follows: 
 * @image html encoder_struct.jpg
 * As shown in FIG ， The coding module consists of several Group Composition (in T15 Support two Group ) ， Each Group Coded by Channel composition. 
 * Each code Channel With an output code stream buffer ， This buffer consists of multiple buffer composition. 
 * @section enc_channel 2 coding Channel
 * A code Channel Can complete the coding of a protocol. Group Can add one H264 coding Channel With a JPEG coding Channel . 
 * @section enc_rc 3 Rate control 
 * @subsection enc_cbr 3.1 CBR
 * CBR ( Constent Bit Rate ) Constant bit rate ， That is, the code rate is constant during the code rate statistics time. 
 * To H.264 Coding as an example ， User can set maxQp，minQp，bitrate Wait. 
 * maxQp，minQp Used to control the quality range of the image ， bitrate It is used to clamp the average code rate during the statistical time. 
 * When the code rate is greater than the constant code rate ， image QP Will gradually maxQp Adjustment ， When the encoding rate is much less than the constant rate ， image QP Will gradually minQp Adjustment. 
 * When the image QP achieve maxQp Time ，QP Clamped to maximum ，bitrate Clamping effect is invalid ， Encoding rate may exceed bitrate . 
 * When the image QP achieve minQp Time ，QP Clamped to minimum ， At this time, the code rate of the encoding has reached the maximum value ， And the image quality is the best. 
 * @subsection enc_FixQP 3.2 FixQP
 * Fix Qp fixed Qp value. ， Encode all macroblocks of the image Qp Same value ， Use user-defined images Qp value. 
 * @{
 */

/**
 * Definition code Channel Rate controller mode 
 */
typedef enum {
	ENC_RC_MODE_FIXQP = 0,	/**< Fixqp mode */
	ENC_RC_MODE_CBR = 1,	/**< CBR mode */
	ENC_RC_MODE_VBR = 2,	/**< VBR mode */
	ENC_RC_MODE_SMART = 3,	/**< Smart mode */
	ENC_RC_MODE_INV = 4,	/**< INV mode */
} IMPEncoderRcMode;

/**
 * Definition code channel Frame rate structure ,frmRateNum with frmRateDen After being divided by the greatest common divisor, the least common multiple between the two cannot exceed 64， It is best to be divisible by the greatest common divisor before setting 
 */
typedef struct {
	uint32_t	frmRateNum;				/**< The number of time units in one second , In units of time. */
	uint32_t	frmRateDen;				/**< The number of time units in a frame , In units of time. */
} IMPEncoderFrmRate;

/**
 * definition H.264 coding Channel Fixqp Property structure 
 */
typedef struct {
	uint32_t			qp;				/**< Frame level Qp value */
} IMPEncoderAttrH264FixQP;

/**
 * definition H.264 coding Channel CBR Property structure 
 */
typedef struct {
	uint32_t			maxQp;			/**< Encoder supports the largest image QP */
	uint32_t			minQp;			/**< Encoder supports the smallest image QP */
	uint32_t			outBitRate;		/**< Encoder output bit rate , To kbps As a unit */
	int					iBiasLvl;		/**< Adjustment I frame QP To adjust I The image quality of the frame and its code stream size , range :[-3,3] */
	uint32_t			frmQPStep;		/**< Interframe QP Change step */
	uint32_t			gopQPStep;		/**< GOP between QP Change step */
	bool				adaptiveMode;	/**< Adaptive mode */
	bool				gopRelation;	/**< GOP Is it related */
} IMPEncoderAttrH264CBR;

/**
 * definition H.264 coding Channel VBR Property structure 
 */
typedef struct {
	uint32_t			maxQp;			/**< Encoder supports the largest image QP */
	uint32_t			minQp;			/**< Encoder supports the smallest image QP */
	uint32_t			staticTime;		/**< Bit rate statistics time , In seconds */
	uint32_t			maxBitRate;		/**< Encoder output maximum bit rate , To kbps As a unit */
 int32_t iBiasLvl; /**< Adjustment I frame QP To adjust I The image quality of the frame and its code stream size , range :[-3,3] */
	uint32_t			changePos;		/**< VBR Start to adjust Qp The ratio of the code rate at the time to the maximum code rate , Ranges :[50, 100] */
 uint32_t qualityLvl; /**< Minimum video quality , range [0-7], The lower the value, the higher the image quality , But the larger the code stream , minBitRate = maxBitRate * quality[qualityLvl], among them quality[] = {0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1} */
	uint32_t			frmQPStep;		/**< Interframe QP Change step */
	uint32_t			gopQPStep;		/**< GOP between QP Change step */
	bool				gopRelation;	/**< gop Is it related */
} IMPEncoderAttrH264VBR;

/**
 * definition H.264 coding Channel Smart Property structure 
 */
typedef struct {
	uint32_t			maxQp;			/**< Encoder supports the largest image QP */
	uint32_t			minQp;			/**< Encoder supports the smallest image QP */
	uint32_t			staticTime;		/**< Bit rate statistics time , In seconds */
	uint32_t			maxBitRate;		/**< Encoder output maximum bit rate , To kbps As a unit */
 int32_t iBiasLvl; /**< Adjustment I frame QP To adjust I The image quality of the frame and its code stream size , range :[-3,3] */
	uint32_t			changePos;		/**< Start to adjust Qp The ratio of the code rate at the time to the maximum code rate , Ranges :[50, 100] */
 uint32_t qualityLvl; /**< Minimum video quality , range [0-7], The lower the value, the higher the image quality , But the larger the code stream . minBitRate = maxBitRate * quality[qualityLvl], among them quality[] = {0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1} */
	uint32_t			frmQPStep;		/**< Interframe QP Change step */
	uint32_t			gopQPStep;		/**< gop between QP Change step */
	bool				gopRelation;	/**< gop Is it related */
} IMPEncoderAttrH264Smart;

/**
 * definition H.264 coding Channel Demosaicing properties 
 */
typedef struct {
	bool				enable;			/**< Whether to enable the demosaicing function */
	bool				isAutoMode;		/**< Turn on automatic demosaicing mode ， 0: Manual ，1 :automatic */
	int					demaskCnt;		/**< Demosaicing hold time parameter */
	int					demaskThresd;	/**< Demosaicing threshold */
} IMPEncoderAttrDemask;

/**
 * definition H.264 coding Channel Denoising properties , Can not be changed once enabled , But the denoising type can be changed dynamically ;
 */
typedef struct {
	bool				enable;			/**< Whether to enable the denoising function , 0: ignore ,1: Denoise according to the current frame type , Maximum loss of information ,2: press I Frame denoising ， Moderate information loss */
	int					dnType;			/**< Denoising type ,0: ignore ， No noise reduction ,1: use IP Frame type noise reduction ,2: use I Frame type noise reduction */
	int					dnIQp;			/**< Denoising I Frame quantization parameter */
	int					dnPQp;			/**< Denoising P Frame quantization parameter */
} IMPEncoderAttrDenoise;

/**
 * definition H.264 coding Channel Input frame usage mode 
 */
typedef enum {
	ENC_FRM_BYPASS	= 0,		/**< Sequential full usage mode - Default mode */
	ENC_FRM_REUSED	= 1,		/**< Reuse frame mode */
	ENC_FRM_SKIP	= 2,		/**< Drop frame mode */
} EncFrmUsedMode;

/**
 * definition H.264 coding Channel Input frame usage mode attributes 
 */
typedef struct {
	bool				enable;			/**< Whether to enable the input frame usage mode */
	EncFrmUsedMode		frmUsedMode;	/**< Input frame usage mode */
	uint32_t			frmUsedTimes;	/**< Frame interval used each time in repeated frame or dropped frame mode */
} IMPEncoderAttrFrmUsed;

typedef enum {
	IMP_Encoder_STYPE_N1X			= 0,	/**< 1 Double skip frame reference */
	IMP_Encoder_STYPE_N2X			= 1,	/**< 2 Double skip frame reference */
	IMP_Encoder_STYPE_N4X			= 2,	/**< 4 Double skip frame reference */
	IMP_Encoder_STYPE_HN1_FALSE	 = 3,	/**< Advanced frame skip mode: N1 Open frame skipping */
	IMP_Encoder_STYPE_HN1_TRUE		= 4,	/**< Advanced frame skip mode: N1 Closed frame skipping */
	IMP_Encoder_STYPE_H1M_FALSE	 = 5,	/**< Advanced frame skip mode: 1M Open frame skipping */
	IMP_Encoder_STYPE_H1M_TRUE		= 6,	/**< Advanced frame skip mode: 1M Closed frame skipping */
} IMPSkipType;

typedef enum {
	IMP_Encoder_FSTYPE_IDR		= 0,	/**< Key frames in advanced frame skipping mode */
	IMP_Encoder_FSTYPE_LBASE	= 1,	/**< Long-term basic frame in advanced frame skipping mode */
	IMP_Encoder_FSTYPE_SBASE	= 2,	/**< Short-term basic frame in advanced frame skipping mode */
	IMP_Encoder_FSTYPE_ENHANCE	= 3,	/**< Enhanced frame in advanced frame skipping mode */
} IMPRefType;

/**
 * definition H264 Advanced frame skipping type structure 
 */
typedef struct {
	IMPSkipType	 skipType;	/**< Frame skipping type */
	int				m;				/**< Enhanced frame interval */
	int				n;				/**< Reference frame interval */
	int				maxSameSceneCnt;/**< Occupied by the same scene gop Maximum number , Only for H1M Skip Type valid , If set to not greater than 0, then m Value does not work */
	int				bEnableScenecut;/**< Whether to enable scene switching , Only for H1M Skip Type valid */
	int				bBlackEnhance;	/**< Whether to make the enhanced frame output as a null stream */
} IMPEncoderAttrHSkip;

/**
 * definition H264 Advanced frame skip type initialization structure 
 */
typedef struct {
	IMPEncoderAttrHSkip	hSkipAttr;	/**< Advanced frame skipping properties */
	IMPSkipType			maxHSkipType;/**< Maximum frame skipping type to be used */
} IMPEncoderAttrInitHSkip;

/**
 * Definition code Channel Rate controller rate control mode attributes 
 */
typedef struct {
	IMPEncoderRcMode rcMode;						/**< RC mode */
	union {
		IMPEncoderAttrH264FixQP	 attrH264FixQp;		/**< H.264 Protocol encoding Channel Fixqp Mode attributes */
		IMPEncoderAttrH264CBR	 attrH264Cbr;		/**< H.264 Protocol encoding Channel Cbr Mode attributes */
		IMPEncoderAttrH264VBR	 attrH264Vbr;		/**< H.264 Protocol encoding Channel Vbr Mode attributes */
		IMPEncoderAttrH264Smart	 attrH264Smart;		/**< H.264 Protocol encoding Channel Smart Mode attributes */
	};
} IMPEncoderAttrRcMode;

/**
 * Definition code Channel Rate controller properties 
 */
typedef struct {
 IMPEncoderFrmRate	 outFrmRate;		/**< coding Channel The output frame rate (the output frame rate cannot be greater than the input frame rate) */
 uint32_t			 maxGop;			/**< gop value ， Must be an integer multiple of the frame rate */
 IMPEncoderAttrRcMode attrRcMode; /**< Rate control mode attributes */
	IMPEncoderAttrFrmUsed	 attrFrmUsed;	/**< Input frame usage mode attributes */
	IMPEncoderAttrDemask	 attrDemask;		/**< Demosaicing properties */
	IMPEncoderAttrDenoise	 attrDenoise;	/**< Denoising properties */
	IMPEncoderAttrInitHSkip	 attrHSkip;		/**< Advanced frame skipping initialization properties */
} IMPEncoderRcAttr;

/**
 * H264 Stream NALU Types of 
 */
typedef enum {
	IMP_H264_NAL_UNKNOWN		= 0,	/**< not specified */
	IMP_H264_NAL_SLICE		 = 1,	/**< A non IDR Image coding strip */
	IMP_H264_NAL_SLICE_DPA	 = 2,	/**< Encoded strip data segmentation block A */
	IMP_H264_NAL_SLICE_DPB	 = 3,	/**< Encoded strip data segmentation block B */
	IMP_H264_NAL_SLICE_DPC	 = 4,	/**< Encoded strip data segmentation block C */
	IMP_H264_NAL_SLICE_IDR	 = 5,	/**< IDR Image coding strip */
	IMP_H264_NAL_SEI			= 6,	/**< Auxiliary enhancement information (SEI) */
	IMP_H264_NAL_SPS			= 7,	/**< Sequence parameter set */
	IMP_H264_NAL_PPS			= 8,	/**< Image parameter set */
	IMP_H264_NAL_AUD			= 9,	/**< Access unit separator */
	IMP_H264_NAL_FILLER		 = 12,	/**< Data input */
} IMPEncoderH264NaluType;

/**
 * Define code stream type 
 */
typedef union {
	IMPEncoderH264NaluType		h264Type;		/**< H264E NALU Stream packet type */
} IMPEncoderDataType;

/**
 * Define the frame code stream packet structure 
 */
typedef struct {
	uint32_t	phyAddr;						/**< Stream packet physical address */
	uint32_t	virAddr;						/**< Stream packet virtual address */
	uint32_t	length;							/**< Stream packet length */

	int64_t		timestamp;						/**< Timestamp ， unit us */
	bool		frameEnd;						/**< End of frame indicator */

	IMPEncoderDataType	dataType;				/**< Stream type */
} IMPEncoderPack;

/**
 * Define the frame stream type structure 
 */
typedef struct {
	IMPEncoderPack	*pack;				/**< Frame stream packet structure */
	uint32_t	packCount;				/**< The number of all packets in one frame of code stream */
	uint32_t	seq;					/**< Stream serial number ， Get the frame number by frame ， Get the package serial number by package */
	union {
		IMPRefType refType;
	};
} IMPEncoderStream;

/**
 * Define encoder clipping properties ， First crop the image input to the encoder ， Compare with the size of the encoding channel before scaling 
 */
typedef struct {
 bool		enable;		/**< Whether to cut , Ranges :[FALSE, TRUE],TRUE: Enable clipping ,FALSE: Disable clipping */
 uint32_t	x;			/**< Cropped area , Upper left corner x coordinate */
 uint32_t	y;			/**< Cropped area , Upper left corner y coordinate */
 uint32_t	w;			/**< Cropped area , width */
 uint32_t	h;			/**< Cropped area , high */
} IMPEncoderCropCfg;

/**
 * Define the encoder to insert user data attributes , Only for H264
 */
typedef struct {
	uint32_t			maxUserDataCnt;		/**< Maximum number of users to insert data cache space , range: 0-2 */
	uint32_t			maxUserDataSize;	/**< Maximum user insert data cache space size , range: 16-1024 */
} IMPEncoderUserDataCfg;

/**
 * Define encoder attribute structure 
 */
typedef struct {
	IMPPayloadType			enType;			/**< Encoding protocol type */
	uint32_t				bufSize;		/**< Configuration buffer size ， Ranges : Not less than the product of image width and height 1.5 Times. ， Set this parameter to 0，IMP The size is automatically calculated internally */
	uint32_t				profile;		/**< Coding level , 0: baseline; 1:MP; 2:HP */
	uint32_t				picWidth;		/**< Encoded image width */
	uint32_t				picHeight;		/**< Encoded image height */
	IMPEncoderCropCfg		crop;			/**< Encoder cropping properties */
	IMPEncoderUserDataCfg	userData;		/**< Insert user data attributes , Only for H264 */
} IMPEncoderAttr;

/**
 * Definition code Channel Attribute structure 
 */
typedef struct {
	IMPEncoderAttr		encAttr;	/**< Encoder attribute structure */
	IMPEncoderRcAttr	rcAttr;			/**< Rate controller attribute structure */
uint32_t xW;
uint32_t xH;
} IMPEncoderCHNAttr;

/**
 * Definition code Channel State structure 
 */
typedef struct {
	bool		registered;				/**< Register to Group Sign ， Ranges :{TRUE, FALSE}，TRUE: registered ，FALSE: unregistered */
	uint32_t	leftPics;				/**< Number of images to be encoded */
	uint32_t	leftStreamBytes;		/**< Stream buffer Remaining byte number */
	uint32_t	leftStreamFrames;		/**< Stream buffer Remaining frames */
	uint32_t	curPacks;				/**< The number of stream packets in the current frame */
	uint32_t	work_done;				/**< Channel program running status ，0 :running ，1， Not running */
} IMPEncoderCHNStat;

/**
 * Define color to gray (C2G) parameter 
 */
typedef struct {
 bool	enable;			/**< Turn on or off the color to gray function */
} IMPEncoderColor2GreyCfg;

/**
 * Define settings EnableIDR parameter 
 */
typedef struct {
 bool	enable;			/**< Whether to set EnableIDR */
} IMPEncoderEnIDRCfg;

/**
 * Define settings gopsize parameter 
 */
typedef struct {
	int		gopsize;			/**< IDR parameter */
} IMPEncoderGOPSizeCfg;

/**
 * Define settings ROI parameter 
 */
typedef struct {
	uint32_t	u32Index;	/**< ROI Area index value ， stand by 0-7 */
	bool		bEnable;	/**< Whether to enable this area ROI Features */
	bool		bRelatedQp;		/**< 0 :absolute ROI，1 :relatively ROI */
	int			s32Qp;		/**< ROI Relative or absolute area qp value */
	IMPRect		rect;		/**< Area coordinate properties */
} IMPEncoderROICfg;

/**
 * Define the super frame processing mode in rate control 
 */
typedef enum {
 IMP_RC_SUPERFRM_NONE = 0, /**< No special strategy , stand by */
 IMP_RC_SUPERFRM_DISCARD = 1, /**< Discard jumbo frames , not support , It is up to the caller to decide whether to discard */
 IMP_RC_SUPERFRM_REENCODE = 2, /**< Remake oversized frames , stand by */
 IMP_RC_SUPERFRM_BUTT = 3,
} IMPEncoderSuperFrmMode;

/**
 * Rate control priority enumeration 
 */
typedef enum {
 IMP_RC_PRIORITY_RDO = 0, /**< Target bit rate and quality balance */
 IMP_RC_PRIORITY_BITRATE_FIRST = 1, /**< Target bit rate priority */
 IMP_RC_PRIORITY_FRAMEBITS_FIRST = 2, /**< Jumbo frame threshold priority */
 IMP_RC_PRIORITY_BUTT = 3,
} IMPEncoderRcPriority;

/**
 * Jumbo frame processing strategy parameters 
 */
typedef struct {
 IMPEncoderSuperFrmMode superFrmMode; /**< Jumbo frame processing mode , The default is SUPERFRM_REENCODE */
 uint32_t superIFrmBitsThr; /**< I Frame oversize threshold , The default is w*h*3/2*8/ratio, ratio: The main resolution is 6, The sub-resolution is 3 */
 uint32_t superPFrmBitsThr; /**< P Frame oversize threshold , The default is I Frame oversize threshold divided by 1.4 */
 uint32_t superBFrmBitsThr; /**< B Frame oversize threshold , The default is P Frame oversize threshold divided by 1.3, Not currently supported B frame */
 IMPEncoderRcPriority rcPriority; /**< Rate control priority , The default is IMP_RC_PRIORITY_RDO */
} IMPEncoderSuperFrmCfg;

/**
 * definition H.264 Protocol encoding channel transformation, quantization structure 
 */
typedef struct {
 uint32_t intraTransMode; /**< Transformation mode of inter prediction 0: stand by 4x4,8x8 Transform , high profile stand by ; 1:4x4 Transform , baseline, main, high profile Both support ; 2: 8x8 Transform , high profile stand by ; Currently only supports configuration 1 */
 uint32_t interTransMode; /**< Transformation mode of inter prediction 0: stand by 4x4,8x8 Transform , high profile stand by ; 1:4x4 Transform , baseline, main, high profile Both support ; 2: 8x8 Transform , high profile stand by ; Currently only supports configuration 1 */
 bool bScalingListValid; /**< interScalingList8x8 [[[ intraScalingList8x8 Is it valid? , Only in high profile Make sense ; 0: invalid , 1: effective ; Only supports configuration 0 */
 uint8_t interScalingList8X8[64]; /**< Inter prediction 8x8 Quantization table , in high profile under , Users can use their own quantization table , Keep , Not in use ; Ranges :[1, 255] */
 uint8_t intraScalingList8X8[64]; /**< Intra prediction 8x8 Quantization table , in high profile under , Users can use their own quantization table , Keep , Not in use ; Ranges :[1, 255] */
 int chroma_qp_index_offset; /**< For specific meaning, please refer to H.264 protocol , The system default is 0; Ranges :[-12, 12] */
} IMPEncoderH264TransCfg;

/*
 MPEncoderJpegeQl* definition JPEG Coding quantization table parameter structure 
 */
typedef struct {
 bool user_ql_en;/**< 0: Use default quantization table ; 1: Use user quantization table */
 uint8_t qmem_table[256];/**< User-defined quantization table */
} IMPEncoderJpegeQl;
/**
 * @fn int IMP_Encoder_CreateGroup(int encGroup)
 *
 * Create code Group
 *
 * @param[in] encGroup Group number , Ranges :[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks All the way Group Only supports one resolution ， Different resolutions need to start new Group . Group Support all the way at the same time H264 And all the way JPEG Snap 
 *
 * @attention If specified Group already exists ， Failed 
 */
int IMP_Encoder_CreateGroup(int encGroup);

/**
 * @fn int IMP_Encoder_DestroyGroup(int encGroup)
 *
 * Destroy the code Grouop.
 *
 * @param[in] encGroup Group number , Ranges :[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks destroy Group Time ， Must guarantee Group Is empty ， I.e. without any Channel in Group Register in ， Or register to Group in 
 * of Channel Deregistered ， Otherwise it returns failed 
 *
 * @attention Destroy non-existent Group， Failed 
 */
int IMP_Encoder_DestroyGroup(int encGroup);

/**
 * @fn int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr)
 *
 * Create code Channel
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr coding Channel Attribute pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks coding Channel The attribute consists of two parts ， Encoder attributes and rate control attributes 
 * @remarks Encoder properties first need to select the encoding protocol ， Then assign values ​​ to the attributes corresponding to various protocols 
 */
int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr);

/**
 * @fn int IMP_Encoder_DestroyChn(int encChn)
 *
 * Destroy the code Channel
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @attention Destroy non-existent Channel， Failed 
 * @attention Must guarantee before destruction Channel Have been from Group Anti-registration ， Otherwise it returns failed 
 */
int IMP_Encoder_DestroyChn(int encChn);

/**
 * @fn int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr * const attr)
 *
 * Get the code Channel Attribute of 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr coding Channel Attributes 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 */
int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr * const attr);

/**
 * @fn int IMP_Encoder_RegisterChn(int encGroup, int encChn)
 *
 * Registration code Channel To Group
 *
 * @param[in] encGroup coding Group number , Ranges : [0, @ref NR_MAX_ENC_GROUPS - 1]
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @attention Registration does not exist Channel， Failed 
 * @attention registered Channel To non-existent Group， Otherwise it returns failed 
 * @attention Same code Channel Only one can be registered Group， If the Channel Already registered to a Group， Failed 
 * @attention If one Group Already registered ， Then this Group Can't be the other Channel registered ， Unless the previous registration relationship is cancelled 
 */

int IMP_Encoder_RegisterChn(int encGroup, int encChn);
/**
 * @fn int IMP_Encoder_UnRegisterChn(int encChn)
 *
 * Anti-registration code Channel To Group
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Channel After logout ， coding Channel Will be reset ， coding Channel Stream buffer Will be emptied ， If the user is still using 
 * Streams not released in time buffer， Will not be guaranteed buffer Correctness of data ， User can use IMP_Encoder_Query Interface to query 
 * code Channel Stream buffer status ， Confirmation stream buffer Unregister after taking the code stream in Channel
 *
 * @attention Logout uncreated Channel， Failed 
 * @attention Unregistered Channel， Failed 
 * @attention If code Channel Does not stop receiving image encoding ， Failed 
 */
int IMP_Encoder_UnRegisterChn(int encChn);

/**
 * @fn int IMP_Encoder_StartRecvPic(int encChn)
 *
 * Turn on encoding Channel Receive image 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Turn on encoding Channel Encoding can only start after receiving the image 
 *
 * @attention in case Channel Not created ， Failed 
 * @attention in case Channel Not registered to Group， Failed 
 */
int IMP_Encoder_StartRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_StopRecvPic(int encChn)
 *
 * Stop coding Channel Receive image 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks This interface does not determine whether to stop receiving currently ， That is, it is allowed to stop receiving repeatedly without returning an error 
 * @remarks Calling this interface only stops receiving the original data encoding ， Stream buffer Will not be eliminated 
 *
 * @attention in case Channel Not created ， Failed 
 * @attention in case Channel Not registered to Group， Failed 
 */
int IMP_Encoder_StopRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat)
 *
 * Query code Channel status 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] stat coding Channel status 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks no 
 *
 * @attention no 
 */
int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat);

/**
 * @fn int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag)
 *
 * Get the coded stream 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream Stream structure pointer 
 * @param[in] blockFlag Whether to use blocking method to obtain ，0 : Non-blocking ，1 :block 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Get data of one frame of stream at a time 
 * @remarks If the user does not get the code stream for a long time , The stream buffer will be full. Channel If the stream buffer is full , Will be after 
 * The received image is lost , Until the user gets the code stream , So there is enough code stream buffer to be used for encoding , Just start coding. 
 * The interface call to get the code stream and the interface call to release the code stream appear in pairs , And release the stream as soon as possible , Prevent the code stream from being acquired due to user mode , Release not 
 * Code stream caused in time buffer full , Stop coding. 
 * @remarks for H264 Type stream ， Get one frame of code stream successfully in one call ， This frame of code stream may contain multiple packets. 
 * @remarks for JPEG Type stream ， Get one frame of code stream successfully in one call ， This frame of code stream only contains one packet ， This frame contains JPEG The complete information of the picture file. 
 *
 * Example: 
 * @code
 * int ret;
 * ret = IMP_Encoder_PollingStream(ENC_H264_CHANNEL, 1000); //Polling Stream Buffer， Waiting for availability 
 * if (ret < 0) {
 * printf("Polling stream timeout\n");
 * return -1;
 * }
 *
 * IMPEncoderStream stream;
 * ret = IMP_Encoder_GetStream(ENC_H264_CHANNEL, &stream, 1); // Get a frame stream ， Blocking method 
 * if (ret < 0) {
 * printf("Get Stream failed\n");
 * return -1;
 * }
 *
 * int i, nr_pack = stream.packCount;
 * for (i = 0; i < nr_pack; i++) { // Save each packet of this frame of code stream 
 * ret = write(stream_fd, (void *)stream.pack[i].virAddr,
 * stream.pack[i].length);
 * if (ret != stream.pack[i].length) {
 * printf("stream write error:%s\n", strerror(errno));
 * return -1;
 * }
 * }
 * @endcode
 *
 * @attention in case pstStream for NULL, Then return failure; 
 * @attention in case Channel Not created ， Then return failure; 
 */
int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag);

/**
 * @fn int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream)
 *
 * Release the code stream cache 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream Stream structure pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks This interface should be IMP_Encoder_GetStream Pair up and use ，\n
 * After obtaining the code stream, the user must release the obtained code stream buffer in time ， Otherwise it may cause bit stream buffer full ， Affect the encoder encoding. \n
 * And the user must press 
 * Release the code stream cache that has been acquired in the order of release; 
 * @remarks Coding Channel After deregistration ， All unreleased stream packets are invalid ， This invalid code stream buffer can no longer be used or released. 
 *
 * @attention in case pstStream for NULL, Then return failure; 
 * @attention in case Channel Not created ， Then return failure; 
 * @attention Releasing the invalid code stream will return failure. 
 */
int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream);

/**
 * @fn int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec)
 *
 * Polling Stream buffer 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] timeoutMsec overtime time ， Unit: milliseconds 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks You can use this before getting the code stream API get on Polling， The function returns when the code stream buffer is not empty or when it times out. 
 *
 * @attention no 
 */
int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream)
 *
 * Set code stream cache Buffer Number 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] nrMaxStream Stream Buffer number , Ranges : [1, @ref NR_MAX_ENC_CHN_STREAM]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Due to stream caching Buffer The number is fixed when the channel is created ， Therefore API It needs to be called before the channel is created. 
 * @remarks If this is not called before the channel is created API Set code stream cache Buffer Number ， then H264 The default number of channels is 5，JPEG The default number of channels is 1 . 
 *
 * @attention no 
 */
int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream);

/**
 * @fn int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream)
 *
 * Get code stream Buffer number 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] nrMaxStream Stream Buffer Number variable pointer 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks no 
 *
 * @attention no 
 */
int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream);

/**
 * @fn int IMP_Encoder_RequestIDR(int encChn)
 *
 * request IDR frame 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Calling this API Rear ， Will apply in the nearest encoding frame IDR Frame encoding. 
 *
 * @attention no 
 */
int IMP_Encoder_RequestIDR(int encChn);

/**
 * @fn int IMP_Encoder_FlushStream(int encChn)
 *
 * Brush out the old code stream remaining in the encoder ， and IDR Frame start coding 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Calling this API Rear ， Will apply in the nearest encoding frame IDR Frame encoding. 
 *
 * @attention no 
 */
int IMP_Encoder_FlushStream(int encChn);

/**
 * @fn int IMP_Encoder_SetChnColor2Grey(int encChn, const IMPEncoderColor2GreyCfg *pstColor2Grey).
 *
 * Set color to gray function 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstColor2Grey Parameters of the color to gray function 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Set the color to gray function of the channel ， On the next IDR or P The frame takes effect. 
 * Call this API Need channel already exists. 
 *
 * @attention no 
 */
int IMP_Encoder_SetChnColor2Grey(int encChn, const IMPEncoderColor2GreyCfg *pstColor2Grey);

/**
 * @fn int IMP_Encoder_GetChnColor2Grey(int encChn, IMPEncoderColor2GreyCfg *pstColor2Grey).
 *
 * Get color to gray function attributes 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstColor2Grey Parameters of the color to gray function 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will get the channel ’ s color-to-gray function attributes ， Call this API Need channel already exists. 
 *
 * @attention This function JPEG The channel is meaningless. 
 */
int IMP_Encoder_GetChnColor2Grey(int encChn, IMPEncoderColor2GreyCfg *pstColor2Grey);

/**
 * @fn int IMP_Encoder_SetChnAttrRcMode(int encChn, const IMPEncoderAttrRcMode *pstRcModeCfg).
 *
 * Set rate control mode properties 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstRcCfg Rate control mode attribute parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will set the channel's rate control mode attributes ， Next IDR Take effect , Call this API Need channel already exists. 
 *
 * @attention Currently ， Rate control mode support ENC_RC_MODE_FIXQP, ENC_RC_MODE_CBR, ENC_RC_MODE_VBR versus ENC_RC_MODE_SMART
 * @attention This function JPEG The channel is meaningless. 
 */
int IMP_Encoder_SetChnAttrRcMode(int encChn, const IMPEncoderAttrRcMode *pstRcModeCfg);

/**
 * @fn int IMP_Encoder_GetChnAttrRcMode(int encChn, IMPEncoderAttrRcMode *pstRcModeCfg).
 *
 * Get rate control mode attributes 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstRcCfg Rate control mode attribute parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Get the rate control mode attributes of the channel ， Call this API Need channel already exists. 
 *
 * @attention This function JPEG The channel is meaningless. 
 */
int IMP_Encoder_GetChnAttrRcMode(int encChn, IMPEncoderAttrRcMode *pstRcModeCfg);

/**
 * @fn int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps)
 *
 * Dynamically set frame rate control properties 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg Frame rate control attribute parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will reset the encoder frame rate properties ， The frame rate attribute is next GOP Take effect ， Maximum delay 1 Take effect in seconds ， Call this API Need channel already exists. 
 * @remarks If you call IMP_FrameSource_SetChnFPS() Function dynamically changes the system frame rate ， Then you need to call this function to modify the encoder frame rate ， Complete the correct parameter configuration. 
 *
 * @attention no. 
 */
int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps)
 *
 * Get frame rate control properties 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg Frame rate control attribute parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will get the frame rate control properties of the channel ， Call this API Need channel already exists. 
 *
 * @attention This function JPEG The channel is meaningless. 
 */
int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROICfg *pstVencRoiCfg)
 *
 * Set up the channel ROI Attributes 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg ROI Attribute parameter 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will set up the channel ROI Attributes ， Call this API Need channel already exists. 
 *
 * @attention no. 
 */
int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROICfg *pstVencRoiCfg);

/**
 * @fn int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROICfg *pstVencRoiCfg)
 *
 * Get channel ROI Attributes 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg ROI Attribute parameter 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will get the channel ROI Attributes ， Call this API Need channel already exists. 
 *
 * @attention This function JPEG The channel is meaningless. 
 */
int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROICfg *pstVencRoiCfg);

/**
 * @fn int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 * Get channel GOP Attributes 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstGOPSizeCfg GOPSize Attribute parameter 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will get the channel GOPSize Attributes ， Call this API Need channel already exists. 
 *
 * @attention This function JPEG The channel is meaningless. 
 */
int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 * Set up the channel GOP Attributes 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstGOPSizeCfg GOP Attribute parameter 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will set up the channel GOPSize Attributes ， Call this API Need channel already exists. 
 *
 * @attention no. 
 */
int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetChnDemask(int encChn, const IMPEncoderAttrDemask *pdemaskAttr)
 *
 * Set channel demosaicing properties 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdemaskAttr Demosaicing property parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will set the demosaicing properties of the channel ， Call this API Need channel already exists. 
 *
 * @attention no. 
 */
int IMP_Encoder_SetChnDemask(int encChn, const IMPEncoderAttrDemask *pdemaskAttr);

/**
 * @fn int IMP_Encoder_GetChnDemask(int encChn, IMPEncoderAttrDemask *pdemaskAttr)
 *
 * Get channel demosaicing properties 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdemaskAttr Demosaicing property parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will get the demosaicing properties of the channel ， Call this API Need channel already exists. 
 *
 * @attention no. 
 */
int IMP_Encoder_GetChnDemask(int encChn, IMPEncoderAttrDemask *pdemaskAttr);

/**
 * @fn int IMP_Encoder_SetChnFrmUsedMode(int encChn, const IMPEncoderAttrFrmUsed *pfrmUsedAttr)
 *
 * Set the channel input frame usage mode attribute 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr Input frame usage mode attribute parameter 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will set the input frame usage mode attribute of the channel ， Call this API Need channel already exists. 
 *
 * @attention no. 
 */
int IMP_Encoder_SetChnFrmUsedMode(int encChn, const IMPEncoderAttrFrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_GetChnFrmUsedMode(int encChn, IMPEncoderAttrFrmUsed *pfrmUsedAttr)
 *
 * Get the attribute of the channel input frame usage mode 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr Input frame usage mode attribute parameter 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will get the input frame usage mode attribute of the channel ， Call this API Need channel already exists. 
 *
 * @attention no. 
 */
int IMP_Encoder_GetChnFrmUsedMode(int encChn, IMPEncoderAttrFrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_SetChnDenoise(int encChn, const IMPEncoderAttrDenoise *pdenoiseAttr)
 *
 * Set channel denoising properties 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pdenoiseAttr Denoising attribute parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will set the denoising properties of the channel ， Call this API Need channel already exists. 
 *
 * @attention no. 
 */
int IMP_Encoder_SetChnDenoise(int encChn, const IMPEncoderAttrDenoise *pdenoiseAttr);

/**
 * @fn int IMP_Encoder_GetChnDenoise(int encChn, IMPEncoderAttrDenoise *pdenoiseAttr)
 *
 * Get channel denoising properties 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdenoiseAttr Denoising attribute parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will get the denoising properties of the channel ， Call this API Need channel already exists. 
 *
 * @attention This function JPEG The channel is meaningless. 
 */
int IMP_Encoder_GetChnDenoise(int encChn, IMPEncoderAttrDenoise *pdenoiseAttr);

/**
 * @fn int IMP_Encoder_SetChnHSkip(int encChn, const IMPEncoderAttrHSkip *phSkipAttr)
 *
 * Set the advanced frame skipping properties of the channel 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] phSkipAttr Advanced frame skipping attribute parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API The advanced frame skipping properties of the channel will be set ， Call this API Need channel already exists. 
 * @remarks If the advanced frame skipping type set when creating the channel is IMP_Encoder_STYPE_N1X To IMP_Encoder_STYPE_N2X one of the ,
 * this API The frame skipping type can only be set to IMP_Encoder_STYPE_N1X or IMP_Encoder_STYPE_N2X Any one of 
 * @remarks If the advanced frame skipping type set when creating the channel is IMP_Encoder_STYPE_N4X To IMP_Encoder_STYPE_H1M_TRUE one of the ，
 * It can be set to any advanced frame skipping type 
 *
 * @attention no. 
 */
int IMP_Encoder_SetChnHSkip(int encChn, const IMPEncoderAttrHSkip *phSkipAttr);

/**
 * @fn int IMP_Encoder_GetChnHSkip(int encChn, IMPEncoderAttrHSkip *phSkipAttr)
 *
 * Get the advanced frame skipping properties of the channel 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] phSkipAttr Advanced frame skipping attribute parameters 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Get the advanced frame skipping properties of the channel ， Call this API Need channel already exists. 
 */
int IMP_Encoder_GetChnHSkip(int encChn, IMPEncoderAttrHSkip *phSkipAttr);

/**
 * @fn int IMP_Encoder_SetChnHSkipBlackEnhance(int encChn, const int bBlackEnhance)
 *
 * Setting the channel advanced frame skipping bBlackEnhance Attributes 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] bBlackEnhance Logical value ， correspond IMPEncoderAttrHSkip in bBlackEnhance value 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Will set the channel advanced frame skipping bBlackEnhance Attributes ， Call this API Need channel already exists. 
 *
 * @attention no. 
 */
int IMP_Encoder_SetChnHSkipBlackEnhance(int encChn, const int bBlackEnhance);

/**
 * @fn int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen)
 *
 * Insert user data 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] userData User data pointer 
 * @param[in] userDataLen User data length , Ranges :(0, 1024], To byte As a unit 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API Need channel already exists 
 * @remarks If the channel is not created , Failed 
 * @remarks in case userData Empty or userDataLen for 0, Failed 
 * @remarks Insert user data , Only supports H.264 Encoding protocol 
 * @remarks H.264 Maximum allocation of protocol channels 2 Block memory space is used to cache user data , And the size of each piece of user data does not exceed 1k byte . 
 * If the data inserted by the user is redundant 2 Piece , Or the inserted piece of user data is greater than 1k byte Time , This interface will return an error. 
 * @remarks Each piece of user data is SEI The package format is inserted before the latest image stream package. ,
 * H.264 The memory space for buffering this piece of user data in the channel is cleared , Used to store new user data 
 *
 * @attention no. 
 */
int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen);

/**
 * @fn int IMP_Encoder_SetFisheyeEnableStatus(int encChn, int enable)
 *
 * Set up Ingenic The enabled state of the provided fisheye correction algorithm 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] enable 0: Disable ( default ),1: Enable 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Since the enable state of the fisheye correction algorithm is fixed when the channel is created ， Therefore API It needs to be called before the channel is created. 
 * @remarks If this is not called before the channel is created API Set up Ingenic The enabled state of the provided fisheye correction algorithm , Is not enabled by default ， That is, the fisheye correction algorithm provided by Ingenics cannot be used. 
 * @remarks this API only apply to H264
 *
 * @attention no 
 */
int IMP_Encoder_SetFisheyeEnableStatus(int encChn, int enable);

/**
 * @fn int IMP_Encoder_GetFisheyeEnableStatus(int encChn, int *enable)
 *
 * Obtain Ingenic The enabled state of the provided fisheye correction algorithm 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] enable Back to set Ingenic The enabled state of the provided fisheye correction algorithm ,0: Not enabled ,1: Enabled 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks this API only apply to H264
 *
 * @attention no 
 */
int IMP_Encoder_GetFisheyeEnableStatus(int encChn, int *enable);

/**
 * @fn int IMP_Encoder_SetChangeRef(int encChn, int bEnable)
 *
 * Whether the setting is allowed to change BASE Status of frame reference mode 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] enable 0 : No change allowed ，1， Allow change ( default )
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks this API Must be called after the encoding channel is created ， After setting, the encoding of the next frame will take effect. 
 * @remarks this API only apply to H264 SMART Encoding 
 *
 * @attention no 
 */
int IMP_Encoder_SetChangeRef(int encChn, int bEnable);

/**
 * @fn int IMP_Encoder_GetChangeRef(int encChn, int *bEnable)
 *
 * Get permission to change BASE Status of frame reference mode 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] enable Return whether to allow changes BASE Status of frame reference mode ，0 : No change allowed ，1， Allow change 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks this API only apply to H264
 *
 * @attention no 
 */
int IMP_Encoder_GetChangeRef(int encChn, int *bEnable);

/**
 * @fn int IMP_Encoder_SetMbRC(int encChn, int bEnable)
 *
 * Set whether to open the macro block level qp control 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] bEnable 0: Not open ( default ), 1: Turn on 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks this API Must be called after the encoding channel is created ， After setting, the encoding of the next frame will take effect. 
 *
 * @attention no 
 */
int IMP_Encoder_SetMbRC(int encChn, int bEnable);

/**
 * @fn int IMP_Encoder_GetMbRC(int encChn, int *bEnable)
 *
 * Get whether to open the macro block level qp State of control 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] bEnable Return whether to open the macro block level qp State of control , 0: Not open , 1: Turn on 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks this API only apply to H264
 *
 * @attention no 
 */
int IMP_Encoder_GetMbRC(int encChn, int *bEnable);

/**
 * @fn int IMP_Encoder_SetSuperFrameCfg(int encChn, const IMPEncoderSuperFrmCfg *pstSuperFrmParam)
 *
 * Set encoding jumbo frame configuration 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstSuperFrmParam Encoding jumbo frame configuration 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks If the channel is not created , Failed 
 * @remarks this API only apply to H264
 *
 * @attention no 
 */
int IMP_Encoder_SetSuperFrameCfg(int encChn, const IMPEncoderSuperFrmCfg *pstSuperFrmParam);

/**
 * @fn int IMP_Encoder_GetSuperFrameCfg(int encChn, IMPEncoderSuperFrmCfg *pstSuperFrmParam)
 *
 * Get the encoding jumbo frame configuration 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstSuperFrmParam Back to encoding jumbo frame configuration 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks If the channel is not created , Failed 
 * @remarks this API only apply to H264
 *
 * @attention no 
 */
int IMP_Encoder_GetSuperFrameCfg(int encChn, IMPEncoderSuperFrmCfg *pstSuperFrmParam);

/**
 * @fn int IMP_Encoder_SetH264TransCfg(int encChn, const IMPEncoderH264TransCfg *pstH264TransCfg)
 *
 * Set up H.264 The transformation and quantization properties of the protocol encoding channel 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstH264TransCfg H.264 Transformation and quantization properties of protocol encoding channel 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks If the channel is not created , Failed 
 * @remarks this API only apply to H264
 * @remarks It is recommended to create a code channel after that ，startRecvPic Before calling , First when setting GetH264TransCfg， after that SetH264TransCfg
 *
 * @attention no 
 */
int IMP_Encoder_SetH264TransCfg(int encChn, const IMPEncoderH264TransCfg *pstH264TransCfg);

/**
 * @fn int IMP_Encoder_GetH264TransCfg(int encChn, IMPEncoderH264TransCfg *pstH264TransCfg)
 *
 * Obtain H.264 Transformation and quantization properties of protocol encoding channel 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstH264TransCfg return H.264 Transformation and quantization properties of protocol encoding channel 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks If the channel is not created , Failed 
 * @remarks this API only apply to H264
 *
 * @attention no 
 */
int IMP_Encoder_GetH264TransCfg(int encChn, IMPEncoderH264TransCfg *pstH264TransCfg);

/**
 * @fn int IMP_Encoder_SetJpegeQl(int encChn, const IMPEncoderJpegeQl *pstJpegeQl)
 *
 * Set up JPEG Quantization table configuration parameters of the protocol encoding channel 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstJpegeQl JPEG Quantization table configuration parameters of the protocol encoding channel , before 128 Fill in the quantization table ， Rear 128 Bytes to fill 0
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks If the channel is not created , Failed 
 * @remarks this API only apply to JPEG
 *
 * @attention no 
 */
int IMP_Encoder_SetJpegeQl(int encChn, const IMPEncoderJpegeQl *pstJpegeQl);

/**
 * @fn int IMP_Encoder_GetJpegeQl(int encChn, IMPEncoderJpegeQl *pstJpegeQl)
 *
 * Obtain JPEG Quantization table configuration parameters of the protocol encoding channel 
 *
 * @param[in] encChn coding Channel number , Ranges : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstJpegeQl return JPEG Quantization table configuration parameters of the protocol encoding channel 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks If the channel is not created , Failed 
 * @remarks this API only apply to JPEG
 *
 * @attention no 
 */
int IMP_Encoder_GetJpegeQl(int encChn, IMPEncoderJpegeQl *pstJpegeQl);


/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_ENCODER_H__ */
