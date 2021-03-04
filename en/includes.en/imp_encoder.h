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
 * @brief  Video encoding ( H264, JPEG ) Module ， Contains encoding channel management ， Encoding parameter setting and other functions 
 * @section enc_struct 1  Module structure 
 * Encoder The internal structure of the module is as follows: 
 * @image html encoder_struct.jpg
 *  As shown in FIG ， The coding module consists of several Group Composition (in T15 Support two Group ) ， Each Group Coded by Channel composition. 
 *  Each code Channel With an output code stream buffer ， This buffer consists of multiple buffer This buffer consists of multiple 
 * @section enc_channel 2  coding Channel
 *  A code Channel Can complete the coding of a protocol. Each Group Can add one H264 Can add one Channel With a JPEG With a Channel . 
 * @section enc_rc 3  Rate control 
 * @subsection enc_cbr 3.1 CBR
 * CBR ( Constent Bit Rate ) Constant bit rate ， That is, the code rate is constant during the code rate statistics time. 
 *  To H.264  Coding as an example ， User can set maxQp，minQp，bitrate Wait. 
 * maxQp，minQp  Used to control the quality range of the image ， bitrate  It is used to clamp the average code rate during the statistical time. 
 *  When the code rate is greater than the constant code rate ， image QP  Will gradually maxQp  Adjustment ， When the encoding rate is much less than the constant rate ， When the encoding rate is much less than the constant rate QP  When the encoding rate is much less than the constant rate minQp  Adjustment. 
 *  When the image QP  achieve maxQp  Time ，QP  Clamped to maximum ，bitrate  Clamping effect is invalid ， Encoding rate may exceed bitrate Encoding rate may exceed 
 *  Encoding rate may exceed QP  Encoding rate may exceed minQp  Encoding rate may exceed ，QP  Clamped to minimum ， At this time, the code rate of the encoding has reached the maximum value ， And the image quality is the best. 
 * @subsection enc_FixQP 3.2 FixQP
 * Fix Qp  fixed Qp  value. During the bit rate statistics time ， Encode all macroblocks of the image Qp  Same value ， Use user-defined images Qp value. 
 * @{
 */

/**
 *  Define code Channel Rate controller mode 
 */
typedef enum {
	ENC_RC_MODE_H264FIXQP               = 0,	/**< H.264 Fixqp  Mode (support)  */
	ENC_RC_MODE_H264CBR                 = 1,	/**< H.264 CBR  Mode (support)  */
	ENC_RC_MODE_H264ABR                 = 2,	/**< H.264 ABR  mode  */
	ENC_RC_MODE_H264VBR                 = 3,	/**< H.264 VBR  mode  */
	ENC_RC_MODE_H264INV                 = 4,	/**< H.264 INV  mode  */
} IMPEncoderRcMode;

/**
 *  mode channel Frame rate structure ,frmRateNum with frmRateDen After being divided by the greatest common divisor, the least common multiple between the two cannot exceed 64， It is best to be divisible by the greatest common divisor before setting 
 */
typedef struct {
	uint32_t	frmRateNum;				/**<  The number of time units in one second ,  In units of time. The numerator of the frame rate  */
	uint32_t	frmRateDen;				/**<  The number of time units in a frame ,  In units of time. The denominator of the frame rate  */
} IMPEncoderFrmRate;

/**
 *  definition H.264 definition Channel Fixqp Property structure 
 */
typedef struct {
	uint32_t			maxGop;			/**< H.264 gop value ， Must be an integer multiple of the frame rate  */
	IMPEncoderFrmRate	outFrmRate;		/**<  Must be an integer multiple of the frame rate Channel The output frame rate (the output frame rate cannot be greater than the input frame rate) */
	uint32_t			qp;				/**<  Frame level Qp Frame level  */
} IMPEncoderAttrH264FixQP;

/**
 *  Frame level H.264 Frame level Channel CBR Frame level 
 */
typedef struct {
	uint32_t			maxGop;			/**< H.264 gop Frame level ， Frame level  */
	IMPEncoderFrmRate	outFrmRate;		/**<  Frame level Channel Frame level */
	uint32_t			maxQp;			/**<  Encoder supports the largest image QP */
	uint32_t			minQp;			/**<  Encoder supports the smallest image QP */
	uint32_t			outBitRate;		/**<  Encoder output bit rate , Encoder output bit rate kbps As a unit  */
	uint32_t			maxFPS;			/**<  Maximum frame rate  */
	uint32_t			minFPS;			/**<  Minimum frame rate  */
	int					IBiasLvl;		/**< I Frame weight ， stand by (-3~3)，7  Levels  */
	uint32_t			FrmQPStep;		/**<  Interframe QP Change step  */
	uint32_t			GOPQPStep;		/**< GOP between QP between  */
	bool				AdaptiveMode;	/**<  Adaptive mode */
	bool				GOPRelation;	/**< GOP Is it related  */
} IMPEncoderAttrH264CBR;

/**
 *  Is it related H.264 Is it related Channel VBR Is it related 
 */
typedef struct {
	uint32_t			maxGop;			/**< H.264 gop Is it related ， Is it related  */
	IMPEncoderFrmRate	outFrmRate;		/**<  Is it related Channel Is it related */
	uint32_t			maxQp;			/**<  Is it related QP */
	uint32_t			minQp;			/**<  Is it related QP */
	uint32_t			staticTime;		/**<  Bit rate statistics time , In seconds  */
	uint32_t			maxBitRate;		/**<  Encoder output maximum bit rate , Encoder output maximum bit rate kbps Encoder output maximum bit rate  */
	uint32_t			changePos;		/**< VBR  Start to adjust  Qp  The ratio of the code rate at the time to the maximum code rate , Ranges :[50, 100] */
	uint32_t			FrmQPStep;		/**<  Ranges QP Ranges  */
	uint32_t			GOPQPStep;		/**< GOP Ranges QP Ranges  */
} IMPEncoderAttrH264VBR;

/**
 *  Ranges H.264 Ranges Channel Demosaicing properties 
 */
typedef struct {
	bool				enable;			/**<  Whether to enable the demosaicing function  */
	bool				isAutoMode;		/**<  Turn on automatic demosaicing mode ， 0: Manual ，1 :automatic  */
	int					demaskCnt;		/**<  Demosaicing hold time parameter  */
	int					demaskThresd;	/**<  Demosaicing threshold  */
} IMPEncoderAttrH264Demask;

/**
 *  Demosaicing threshold H.264 Demosaicing threshold Channel Denoising properties , Cannot be changed once enabled , But the denoising type can be changed dynamically ;
 */
typedef struct {
	bool				enable;			/**<  Whether to enable the denoising function , 0: ignore ,1: Denoise according to the current frame type , Maximum loss of information ,2: press I Frame denoising ， Moderate information loss  */
	int					dnType;			/**<  Denoising type ,0: Denoising type ， No noise reduction ,1: use IP Frame type noise reduction ,2: Frame type noise reduction I Frame type noise reduction  */
	int					dnIQp;			/**<  Denoising I Frame quantization parameter  */
	int					dnPQp;			/**<  Frame quantization parameter P Frame quantization parameter  */
} IMPEncoderAttrH264Denoise;

/**
 *  Frame quantization parameter H.264 Frame quantization parameter Channel Input frame usage mode 
 */
typedef enum {
	ENC_FRM_BYPASS	= 0,		/**<  Sequential full usage mode - Default mode  */
	ENC_FRM_REUSED	= 1,		/**<  Reuse frame mode  */
	ENC_FRM_SKIP	= 2,		/**<  Drop frame mode  */
} EncFrmUsedMode;

/**
 *  Drop frame mode H.264 Drop frame mode Channel Input frame usage mode attributes 
 */
typedef struct {
	bool				enable;			/**<  Whether to enable the input frame usage mode  */
	EncFrmUsedMode		frmUsedMode;	/**<  Whether to enable the input frame usage mode  */
	uint32_t			frmUsedTimes;	/**<  Frame interval used each time in repeated frame or dropped frame mode  */
} IMPEncoderAttrH264FrmUsed;

typedef enum {
	IMP_H264_STYPE_N11			= 0,	/**< 1 Double skip frame reference (single instance)  */
	IMP_H264_STYPE_N1X			= 1,	/**< 1 Double skip frame reference (multi-instance)  */
	IMP_H264_STYPE_N2X			= 2,	/**< 2 Double skip frame reference  */
	IMP_H264_STYPE_N4X			= 3,	/**< 4 Double skip frame reference  */
	IMP_H264_STYPE_HN1_FALSE	= 4,	/**<  Advanced frame skip mode: N,1,HI_FALSE */
	IMP_H264_STYPE_HN1_TRUE		= 5,	/**<  Advanced frame skip mode: NN,1,HI_TURE */
	IMP_H264_STYPE_H1M_TRUE		= 6,	/**<  Advanced frame skip mode: N1,M,HI_TRUE */
} IMPH264SkipType;

typedef enum {
	IMP_H264_FS_IDR		= 0,	/**<  Key frames in advanced frame skipping mode  */
	IMP_H264_FS_BASE	= 1,	/**<  Reference frame in advanced frame skipping mode  */
	IMP_H264_FS_ENHANCE	= 2,	/**<  Enhanced frame in advanced frame skipping mode  */
} IMPH264RefType;

/**
 *  Enhanced frame in advanced frame skipping mode H264 Advanced frame skipping type structure 
 */
typedef struct {
	IMPH264SkipType	h264SkipType;	/**<  Frame skipping type  */
	int				m;				/**<  Enhanced frame interval  */
	int				n;				/**<  Reference frame interval  */
} IMPEncoderAttrH264HSkip;

/**
 *  Reference frame interval H264 Blank advanced frame skip type structure 
 */
typedef struct {
	int				i_skip_distance;	/**<  Number of consecutive blank frames  */
} IMPEncoderAttrH264BSkip;


/**
 *  Number of consecutive blank frames Channel Rate controller properties 
 */
typedef struct {
	IMPEncoderRcMode rcMode;						/**< RC  Rate controller properties  */
	union {
		IMPEncoderAttrH264FixQP	 attrH264FixQp;		/**< H.264  Protocol encoding Channel Fixqp  Mode attributes  */
		IMPEncoderAttrH264CBR	 attrH264Cbr;		/**< H.264  Mode attributes Channel Cbr  Mode attributes  */
		IMPEncoderAttrH264VBR	 attrH264Vbr;		/**< H.264  Mode attributes Channel Vbr  Mode attributes  */
	};
	IMPEncoderAttrH264FrmUsed	attrH264FrmUsed;	/**<  Mode attributes  */
	IMPEncoderAttrH264Demask	attrH264Demask;		/**<  Mode attributes  */
	IMPEncoderAttrH264Denoise	attrH264Denoise;	/**<  Mode attributes  */
	IMPEncoderAttrH264HSkip		attrH264HSkip;		/**< H264 Advanced frame skipping properties  */
	IMPEncoderAttrH264BSkip		attrH264BSkip;		/**< H264 Blank skip frame attribute  */
} IMPEncoderRcAttr;

/**
 * H264 Stream NALU Types of 
 */
typedef enum {
	IMP_NAL_UNKNOWN		= 0,	/**<  not specified  */
	IMP_NAL_SLICE		= 1,	/**<  A non IDR Image coding strip   */
	IMP_NAL_SLICE_DPA	= 2,	/**<  Encoded strip data segmentation block A */
	IMP_NAL_SLICE_DPB	= 3,	/**<  Encoded strip data segmentation block B */
	IMP_NAL_SLICE_DPC	= 4,	/**<  Encoded strip data segmentation block C */
	IMP_NAL_SLICE_IDR	= 5,	/**< IDR Encoded strip data segmentation block  */
	IMP_NAL_SEI			= 6,	/**<  Auxiliary enhancement information  (SEI) */
	IMP_NAL_SPS			= 7,	/**<  Sequence parameter set  */
	IMP_NAL_PPS			= 8,	/**<  Image parameter set  */
	IMP_NAL_AUD			= 9,	/**<  Access unit separator  */
	IMP_NAL_FILLER		= 12,	/**<  Data input  */
} IMPEncoderH264NaluType;

/**
 *  Define code stream type 
 */
typedef union {
	IMPEncoderH264NaluType		h264Type;		/**< H264E NALU  Stream packet type  */
} IMPEncoderDataType;

/**
 *  Define the frame code stream packet structure 
 */
typedef struct {
	uint32_t	phyAddr;						/**<  Stream packet physical address  */
	uint32_t	virAddr;						/**<  Stream packet virtual address  */
	uint32_t	length;							/**<  Stream packet length  */

	int64_t		timestamp;						/**<  Timestamp ， unit us */
	bool		frameEnd;						/**<  End of frame indicator  */

	IMPEncoderDataType	dataType;				/**<  Stream type  */
} IMPEncoderPack;

/**
 *  Define the frame stream type structure 
 */
typedef struct {
	IMPEncoderPack	*pack;				/**<  Frame stream packet structure  */
	uint32_t	packCount;				/**<  The number of all packets in one frame of stream  */
	uint32_t	seq;					/**<  Stream serial number ， Get the frame number by frame ， Get the package serial number by package  */
	union {
		IMPH264RefType h264RefType;
	};
} IMPEncoderStream;

/**
 *  Define encoder clipping properties ， First crop the image input to the encoder ， Compare with the size of the encoding channel before scaling 
 */
typedef struct {
    bool		enable;		/**<  Whether to cut , Whether to cut :[FALSE, TRUE],TRUE: Enable clipping ,FALSE: Disable clipping  */
    uint32_t	x;			/**<  Cropped area , Upper left corner x coordinate  */
    uint32_t	y;			/**<  coordinate , coordinate y coordinate  */
    uint32_t	w;			/**<  coordinate , width  */
    uint32_t	h;			/**<  width , high  */
} IMPEncoderCropCfg;

/**
 *  Define the encoder to insert user data attributes , Only for H264
 */
typedef struct {
	uint32_t			maxUserDataCnt;		/**<  Maximum number of users inserting data cache space , range: 0-2 */
	uint32_t			maxUserDataSize;	/**<  Maximum user insert data cache space size , Maximum user insert data cache space size 16-1024 */
} IMPEncoderUserDataCfg;

/**
 *  Define encoder attribute structure 
 */
typedef struct {
	IMPPayloadType			enType;			/**<  Encoding protocol type  */
	uint32_t				bufSize;		/**<  Configuration  buffer  size ， size : Not less than the product of image width and height 1.5 Times. When setting channel encoding properties ， Set this parameter to 0，IMP The size is automatically calculated internally  */
	uint32_t				profile;		/**<  Coding level , 0: baseline; 1:MP; 2:HP */
	uint32_t				picWidth;		/**<  Encoded image width  */
	uint32_t				picHeight;		/**<  Encoded image height  */
	IMPEncoderCropCfg		crop;			/**<  Encoder cropping properties  */
	IMPEncoderUserDataCfg	userData;		/**<  Insert user data attributes , Insert user data attributes H264 */
} IMPEncoderAttr;

/**
 *  Insert user data attributes Channel Attribute structure 
 */
typedef struct {
	IMPEncoderAttr		encAttr;	/**<  Encoder attribute structure  */
	IMPEncoderRcAttr	rcAttr;			/**<  Rate controller attribute structure  */
} IMPEncoderCHNAttr;

/**
 *  Rate controller attribute structure Channel State structure 
 */
typedef struct {
	bool		registered;				/**<  Register to Group Sign ， Sign :{TRUE, FALSE}，TRUE: registered ，FALSE: unregistered  */
	uint32_t	leftPics;				/**<  Number of images to be encoded  */
	uint32_t	leftStreamBytes;		/**<  Number of images to be encoded buffer Remaining byte number  */
	uint32_t	leftStreamFrames;		/**<  number buffer Remaining frames  */
	uint32_t	curPacks;				/**<  The number of stream packets in the current frame  */
	uint32_t	work_done;				/**<  Channel program running status ，0 :running ，1， Not running  */
} IMPEncoderCHNStat;

/**
 *  Define color to gray (C2G) parameter 
 */
typedef struct {
    bool	enable;			/**<  Turn on or off the color to gray function  */
} IMPEncoderColor2GreyCfg;

/**
 *  Define settings EnableIDR Define settings 
 */
typedef struct {
    bool	enable;			/**<  Whether to set EnableIDR */
} IMPEncoderEnIDRCfg;

/**
 *  Whether to set gopsize Whether to set 
 */
typedef struct {
	int		gopsize;			/**< IDR Whether to set  */
} IMPEncoderGOPSizeCfg;

/**
 *  Whether to set ROI Whether to set 
 */
typedef struct {
	uint32_t	u32Index;	/**< ROI Area index value ， Area index value 0-7 */
	bool		bEnable;	/**<  Whether to enable this area ROI Features  */
	bool		bRelatedQp;		/**< 0 :absolute ROI，1 :relatively ROI */
	int			s32Qp;		/**< ROI Relative or absolute area qp Relative or absolute area  */
	IMPRect		rect;		/**<  Area coordinate properties  */
} IMPEncoderROICfg;

/**
 * @fn int IMP_Encoder_CreateGroup(int encGroup)
 *
 *  Create code Group
 *
 * @param[in] encGroup Group number , number :[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0  success 
 * @retval  non- 0  failure 
 *
 * @remarks  All the way Group Only supports one resolution ， Different resolutions need to start new Group . All the way Group Support all the way at the same time H264 And all the way JPEG Snap 
 *
 * @attention  If specified Group already exists ， Failed 
 */
int IMP_Encoder_CreateGroup(int encGroup);

/**
 * @fn int IMP_Encoder_DestroyGroup(int encGroup)
 *
 *  Destroy the code Grouop.
 *
 * @param[in] encGroup Group Destroy the code , Destroy the code :[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0  Destroy the code 
 * @retval  Destroy the code 0  Destroy the code 
 *
 * @remarks  destroy Group destroy ， Must guarantee Group Is empty ， I.e. without any Channel in Group Register in ， Or register to Group in 
 *  of Channel Deregistered ， Otherwise it returns failed 
 *
 * @attention  Destroy non-existent Group， Destroy non-existent 
 */
int IMP_Encoder_DestroyGroup(int encGroup);

/**
 * @fn int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr)
 *
 *  Destroy non-existent Channel
 *
 * @param[in] encChn  Destroy non-existent Channel Destroy non-existent , Destroy non-existent : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr  Destroy non-existent Channel Attribute pointer 
 *
 * @retval 0  Attribute pointer 
 * @retval  Attribute pointer 0  Attribute pointer 
 *
 * @remarks  Attribute pointer Channel The attribute consists of two parts ， Encoder attributes and rate control attributes 
 * @remarks  Encoder properties first need to select the encoding protocol ， Then assign values ​​to the attributes corresponding to various protocols 
 */
int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr);

/**
 * @fn int IMP_Encoder_DestroyChn(int encChn)
 *
 *  Then assign values ​​to the attributes corresponding to various protocols Channel
 *
 * @param[in] encChn  Then assign values ​​to the attributes corresponding to various protocols Channel Then assign values ​​to the attributes corresponding to various protocols , Then assign values ​​to the attributes corresponding to various protocols : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  Then assign values ​​to the attributes corresponding to various protocols 
 * @retval  Then assign values ​​to the attributes corresponding to various protocols 0  Then assign values ​​to the attributes corresponding to various protocols 
 *
 * @attention  Then assign values ​​to the attributes corresponding to various protocols Channel， Then assign values ​​to the attributes corresponding to various protocols 
 * @attention  Must guarantee before destruction Channel Have been from Group Anti-registration ， Anti-registration 
 */
int IMP_Encoder_DestroyChn(int encChn);

/**
 * @fn int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr * const attr)
 *
 *  Get the code Channel Attribute of 
 *
 * @param[in] encChn  Attribute of Channel Attribute of , Attribute of : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr  Attribute of Channel Attributes 
 *
 * @retval 0  Attributes 
 * @retval  Attributes 0  Attributes 
 */
int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr * const attr);

/**
 * @fn int IMP_Encoder_RegisterChn(int encGroup, int encChn)
 *
 *  Registration code Channel To Group
 *
 * @param[in] encGroup  To Group To , To : [0, @ref NR_MAX_ENC_GROUPS - 1]
 * @param[in] encChn  To Channel To , To : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  To 
 * @retval  To 0  To 
 *
 * @attention  Registration does not exist Channel， Registration does not exist 
 * @attention  Registration does not exist Channel To non-existent Group， To non-existent 
 * @attention  Same code Channel Only one can be registered Group， If the Channel Already registered to a Group， Already registered to a 
 * @attention  If one Group Already registered ， Then this Group Can't be the other Channel Can't be the other ， Unless the previous registration relationship is cancelled 
 */

int IMP_Encoder_RegisterChn(int encGroup, int encChn);
/**
 * @fn int IMP_Encoder_UnRegisterChn(int encChn)
 *
 *  Anti-registration code Channel Anti-registration code Group
 *
 * @param[in] encChn  Anti-registration code Channel Anti-registration code , Anti-registration code : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  Anti-registration code 
 * @retval  Anti-registration code 0  Anti-registration code 
 *
 * @remarks Channel After logout ， After logout Channel Will be reset ， Will be reset Channel Stream buffer Will be emptied ， If the user is still using 
 *  Streams not released in time buffer， Will not be guaranteed buffer Correctness of data ， User can use IMP_Encoder_Query Interface to query 
 *  code Channel code buffer status ， Confirmation code stream buffer Unregister after taking the code stream in Channel
 *
 * @attention  Logout uncreated Channel， Logout uncreated 
 * @attention  Unregistered Channel， Unregistered 
 * @attention  If code Channel Does not stop receiving image encoding ， Does not stop receiving image encoding 
 */
int IMP_Encoder_UnRegisterChn(int encChn);

/**
 * @fn int IMP_Encoder_StartRecvPic(int encChn)
 *
 *  Turn on encoding Channel Receive image 
 *
 * @param[in] encChn  Receive image Channel Receive image , Receive image : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  Receive image 
 * @retval  Receive image 0  Receive image 
 *
 * @remarks  Receive image Channel Encoding can only start after receiving the image 
 *
 * @attention  in case Channel Not created ， Not created 
 * @attention  Not created Channel Not registered to Group， Not registered to 
 */
int IMP_Encoder_StartRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_StopRecvPic(int encChn)
 *
 *  Stop coding Channel Stop coding 
 *
 * @param[in] encChn  Stop coding Channel Stop coding , Stop coding : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  Stop coding 
 * @retval  Stop coding 0  Stop coding 
 *
 * @remarks  This interface does not determine whether to stop receiving currently ， That is, it is allowed to stop receiving repeatedly without returning an error 
 * @remarks  Calling this interface only stops receiving the original data encoding ， Calling this interface only stops receiving the original data encoding buffer Will not be eliminated 
 *
 * @attention  Will not be eliminated Channel Will not be eliminated ， Will not be eliminated 
 * @attention  Will not be eliminated Channel Will not be eliminated Group， Will not be eliminated 
 */
int IMP_Encoder_StopRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat)
 *
 *  Query code Channel Query code 
 *
 * @param[in] encChn  Query code Channel Query code , Query code : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] stat  Query code Channel Query code 
 *
 * @retval 0  Query code 
 * @retval  Query code 0  Query code 
 *
 * @remarks  no 
 *
 * @attention  no 
 */
int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat);

/**
 * @fn int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag)
 *
 *  Get the coded stream 
 *
 * @param[in] encChn  Get the coded stream Channel Get the coded stream , Get the coded stream : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream  Stream structure pointer 
 * @param[in] blockFlag  Whether to use blocking method to obtain ，0 : Non-blocking ，1 :block 
 *
 * @retval 0  :block 
 * @retval  :block 0  :block 
 *
 * @remarks  Get data of one frame of stream at a time 
 * @remarks  If the user does not get the code stream for a long time , The stream buffer will be full. A code Channel If the stream buffer is full , Will be after 
 *  The received image is lost , Until the user gets the code stream , So there is enough code stream buffer to be used for encoding , Just start coding. Suggest users 
 *  The interface call to get the code stream and the interface call to release the code stream appear in pairs , And release the stream as soon as possible , Prevent the code stream from being acquired due to user mode , Release not 
 *  Code stream caused in time  buffer  full , Stop coding. 
 * @remarks  for H264 Type stream ， Get one frame of code stream successfully in one call ， This frame of code stream may contain multiple packets. 
 * @remarks  This frame of code stream may contain multiple packets. JPEG This frame of code stream may contain multiple packets. ， This frame of code stream may contain multiple packets. ， This frame of code stream only contains one packet ， This frame contains JPEG The complete information of the picture file. 
 *
 *  Example: 
 * @code
 * int ret;
 * ret = IMP_Encoder_PollingStream(ENC_H264_CHANNEL, 1000); //Polling Example: Buffer， Waiting for availability 
 * if (ret < 0) {
 *     printf("Polling stream timeout\n");
 *     return -1;
 * }
 *
 * IMPEncoderStream stream;
 * ret = IMP_Encoder_GetStream(ENC_H264_CHANNEL, &stream, 1); // Get a frame stream ， Blocking method 
 * if (ret < 0) {
 *     printf("Get Stream failed\n");
 *     return -1;
 * }
 *
 * int i, nr_pack = stream.packCount;
 * for (i = 0; i < nr_pack; i++) { // Save each packet of this frame of code stream 
 *     ret = write(stream_fd, (void *)stream.pack[i].virAddr,
 *                stream.pack[i].length);
 *     if (ret != stream.pack[i].length) {
 *         printf("stream write error:%s\n", strerror(errno));
 *         return -1;
 *     }
 * }
 * @endcode
 *
 * @attention  Save each packet of this frame of code stream pstStream for NULL, Then return failure; 
 * @attention  Then return failure; Channel Then return failure; ， Then return failure; 
 */
int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag);

/**
 * @fn int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream)
 *
 *  Release the code stream cache 
 *
 * @param[in] encChn  Release the code stream cache Channel Release the code stream cache , Release the code stream cache : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream  Release the code stream cache 
 *
 * @retval 0  Release the code stream cache 
 * @retval  Release the code stream cache 0  Release the code stream cache 
 *
 * @remarks  This interface should be IMP_Encoder_GetStream Pair up and use ，\n
 *  After obtaining the code stream, the user must release the obtained code stream buffer in time ， Otherwise it may cause bit stream buffer Otherwise it may cause bit stream ， Affect the encoder encoding. \n
 *  And the user must press 
 *  Release the code stream cache that has been acquired in the order of release; 
 * @remarks  Coding Channel After deregistration ， All unreleased stream packets are invalid ， This invalid code stream buffer can no longer be used or released. 
 *
 * @attention  This invalid code stream buffer can no longer be used or released. pstStream This invalid code stream buffer can no longer be used or released. NULL, This invalid code stream buffer can no longer be used or released. 
 * @attention  This invalid code stream buffer can no longer be used or released. Channel This invalid code stream buffer can no longer be used or released. ， This invalid code stream buffer can no longer be used or released. 
 * @attention  Releasing the invalid code stream will return failure. 
 */
int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream);

/**
 * @fn int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec)
 *
 * Polling Stream buffer 
 *
 * @param[in] encChn  Stream buffer Channel Stream buffer , Stream buffer : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] timeoutMsec  overtime time ， Unit: milliseconds 
 *
 * @retval 0  Unit: milliseconds 
 * @retval  Unit: milliseconds 0  Unit: milliseconds 
 *
 * @remarks  You can use this before getting the code stream API get on Polling， The function returns when the code stream buffer is not empty or when it times out. 
 *
 * @attention  The function returns when the code stream buffer is not empty or when it times out. 
 */
int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream)
 *
 *  Set code stream cache Buffer Number 
 *
 * @param[in] encChn  Number Channel Number , Number : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] nrMaxStream  Number Buffer Number , Number : [1, @ref NR_MAX_ENC_CHN_STREAM]
 *
 * @retval 0  Number 
 * @retval  Number 0  Number 
 *
 * @remarks  Due to stream caching Buffer The number is fixed when the channel is created ， Therefore API It needs to be called before the channel is created. 
 * @remarks  If this is not called before the channel is created API If this is not called before the channel is created Buffer If this is not called before the channel is created ， then H264 The default number of channels is 5，JPEG The default number of channels is 1 The default number of channels is 
 *
 * @attention  The default number of channels is 
 */
int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream);

/**
 * @fn int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream)
 *
 *  Get code stream Buffer Get code stream 
 *
 * @param[in] encChn  Get code stream Channel Get code stream , Get code stream : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] nrMaxStream  Get code stream Buffer Number variable pointer 
 *
 * @retval 0  Number variable pointer 
 * @retval  Number variable pointer 0  Number variable pointer 
 *
 * @remarks  Number variable pointer 
 *
 * @attention  Number variable pointer 
 */
int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream);

/**
 * @fn int IMP_Encoder_RequestIDR(int encChn)
 *
 *  request IDR frame 
 *
 * @param[in] encChn  frame Channel frame , frame : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  frame 
 * @retval  frame 0  frame 
 *
 * @remarks  Calling this API Rear ， Will apply in the most recent encoding frame IDR Frame encoding. 
 *
 * @attention  Frame encoding. 
 */
int IMP_Encoder_RequestIDR(int encChn);

/**
 * @fn int IMP_Encoder_FlushStream(int encChn)
 *
 *  Brush out the old code stream remaining in the encoder ， and IDR Frame start encoding 
 *
 * @param[in] encChn  Frame start encoding Channel Frame start encoding , Frame start encoding : [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0  Frame start encoding 
 * @retval  Frame start encoding 0  Frame start encoding 
 *
 * @remarks  Frame start encoding API Frame start encoding ， Frame start encoding IDR Frame start encoding 
 *
 * @attention  Frame start encoding 
 */
int IMP_Encoder_FlushStream(int encChn);

/**
 * @fn int IMP_Encoder_SetChnColor2Grey(int encChn, const IMPEncoderColor2GreyCfg *pstColor2Grey).
 *
 *  Set color to gray function 
 *
 * @param[in] encChn  Set color to gray function Channel Set color to gray function , Set color to gray function : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstColor2Grey  Parameters of the color to gray function 
 *
 * @retval 0  Parameters of the color to gray function 
 * @retval  Parameters of the color to gray function 0  Parameters of the color to gray function 
 *
 * @remarks  Call this API Set the color to gray function of the channel ， On the next IDR or P The frame takes effect. 
 *  The frame takes effect. API Need channel already exists. 
 *
 * @attention  Need channel already exists. 
 */
int IMP_Encoder_SetChnColor2Grey(int encChn, const IMPEncoderColor2GreyCfg *pstColor2Grey);

/**
 * @fn int IMP_Encoder_GetChnColor2Grey(int encChn, IMPEncoderColor2GreyCfg *pstColor2Grey).
 *
 *  Get color to gray function attributes 
 *
 * @param[in] encChn  Get color to gray function attributes Channel Get color to gray function attributes , Get color to gray function attributes : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstColor2Grey  Get color to gray function attributes 
 *
 * @retval 0  Get color to gray function attributes 
 * @retval  Get color to gray function attributes 0  Get color to gray function attributes 
 *
 * @remarks  Get color to gray function attributes API Will get the channel’s color-to-gray function attributes ， Will get the channel’s color-to-gray function attributes API Will get the channel’s color-to-gray function attributes 
 *
 * @attention  This function JPEG The channel is meaningless. 
 */
int IMP_Encoder_GetChnColor2Grey(int encChn, IMPEncoderColor2GreyCfg *pstColor2Grey);

/**
 * @fn int IMP_Encoder_SetChnRcAttr(int encChn, const IMPEncoderRcAttr *pstRcCfg).
 *
 *  Set rate control properties 
 *
 * @param[in] encChn  Set rate control properties Channel Set rate control properties , Set rate control properties : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstRcCfg  Rate control attribute parameters 
 *
 * @retval 0  Rate control attribute parameters 
 * @retval  Rate control attribute parameters 0  Rate control attribute parameters 
 *
 * @remarks  Rate control attribute parameters API Will set the rate control properties of the channel ， Next IDR Take effect , Take effect API Take effect 
 *
 * @attention  Currently ， Rate control support ENC_RC_MODE_H264FIXQP versus ENC_RC_MODE_H264CBR versus 
 * ENC_RC_MODE_H264FIXQP Support configuration qp，ENC_RC_MODE_H264CBR Support configuration outBitRate Support configuration 
 * @attention  Support configuration JPEG Support configuration 
 */
int IMP_Encoder_SetChnRcAttr(int encChn, const IMPEncoderRcAttr *pstRcCfg);

/**
 * @fn int IMP_Encoder_GetChnRcAttr(int encChn, IMPEncoderRcAttr *pstRcCfg).
 *
 *  Get rate control properties 
 *
 * @param[in] encChn  Get rate control properties Channel Get rate control properties , Get rate control properties : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstRcCfg  Get rate control properties 
 *
 * @retval 0  Get rate control properties 
 * @retval  Get rate control properties 0  Get rate control properties 
 *
 * @remarks  Get rate control properties API Will get the rate control properties of the channel ， Will get the rate control properties of the channel API Will get the rate control properties of the channel 
 *
 * @attention  Will get the rate control properties of the channel JPEG Will get the rate control properties of the channel 
 */
int IMP_Encoder_GetChnRcAttr(int encChn, IMPEncoderRcAttr *pstRcCfg);

/**
 * @fn int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps)
 *
 *  Dynamically set frame rate control properties 
 *
 * @param[in] encChn  Dynamically set frame rate control properties Channel Dynamically set frame rate control properties , Dynamically set frame rate control properties : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg  Frame rate control attribute parameters 
 *
 * @retval 0  Frame rate control attribute parameters 
 * @retval  Frame rate control attribute parameters 0  Frame rate control attribute parameters 
 *
 * @remarks  Frame rate control attribute parameters API Will reset the encoder frame rate properties ， The frame rate attribute is next GOP The frame rate attribute is next ， Maximum delay 1 Take effect in seconds ， Take effect in seconds API Take effect in seconds 
 * @remarks  If you call IMP_FrameSource_SetChnFPS() Function dynamically changes the system frame rate ， Then you need to call this function to modify the encoder frame rate ， Complete the correct parameter configuration. 
 *
 * @attention  no. 
 */
int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps)
 *
 *  Get frame rate control properties 
 *
 * @param[in] encChn  Get frame rate control properties Channel Get frame rate control properties , Get frame rate control properties : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg  Get frame rate control properties 
 *
 * @retval 0  Get frame rate control properties 
 * @retval  Get frame rate control properties 0  Get frame rate control properties 
 *
 * @remarks  Get frame rate control properties API Will get the frame rate control properties of the channel ， Will get the frame rate control properties of the channel API Will get the frame rate control properties of the channel 
 *
 * @attention  Will get the frame rate control properties of the channel JPEG Will get the frame rate control properties of the channel 
 */
int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROICfg *pstVencRoiCfg)
 *
 *  Set up the channel ROI Set up the channel 
 *
 * @param[in] encChn  Set up the channel Channel Set up the channel , Set up the channel : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg ROI Attribute parameter 
 *
 * @retval 0  Attribute parameter 
 * @retval  Attribute parameter 0  Attribute parameter 
 *
 * @remarks  Attribute parameter API Will set up the channel ROI Will set up the channel ， Will set up the channel API Will set up the channel 
 *
 * @attention  Will set up the channel 
 */
int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROICfg *pstVencRoiCfg);

/**
 * @fn int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROICfg *pstVencRoiCfg)
 *
 *  Get channel ROI Get channel 
 *
 * @param[in] encChn  Get channel Channel Get channel , Get channel : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg ROI Get channel 
 *
 * @retval 0  Get channel 
 * @retval  Get channel 0  Get channel 
 *
 * @remarks  Get channel API Will get the channel ROI Will get the channel ， Will get the channel API Will get the channel 
 *
 * @attention  Will get the channel JPEG Will get the channel 
 */
int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROICfg *pstVencRoiCfg);

/**
 * @fn int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 *  Will get the channel GOP Will get the channel 
 *
 * @param[in] encChn  Will get the channel Channel Will get the channel , Will get the channel : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstGOPSizeCfg GOPSize Will get the channel 
 *
 * @retval 0  Will get the channel 
 * @retval  Will get the channel 0  Will get the channel 
 *
 * @remarks  Will get the channel API Will get the channel GOPSize Will get the channel ， Will get the channel API Will get the channel 
 *
 * @attention  Will get the channel JPEG Will get the channel 
 */
int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 *  Will get the channel GOP Will get the channel 
 *
 * @param[in] encChn  Will get the channel Channel Will get the channel , Will get the channel : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstGOPSizeCfg GOP Will get the channel 
 *
 * @retval 0  Will get the channel 
 * @retval  Will get the channel 0  Will get the channel 
 *
 * @remarks  Will get the channel API Will get the channel GOPSize Will get the channel ， Will get the channel API Will get the channel 
 *
 * @attention  Will get the channel 
 */
int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetChnH264Demask(int encChn, const IMPEncoderAttrH264Demask *pdemaskAttr)
 *
 *  Set channel demosaicing properties 
 *
 * @param[in] encChn  Set channel demosaicing properties Channel Set channel demosaicing properties , Set channel demosaicing properties : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdemaskAttr  Demosaicing property parameters 
 *
 * @retval 0  Demosaicing property parameters 
 * @retval  Demosaicing property parameters 0  Demosaicing property parameters 
 *
 * @remarks  Demosaicing property parameters API Will set the demosaicing properties of the channel ， Will set the demosaicing properties of the channel API Will set the demosaicing properties of the channel 
 *
 * @attention  Will set the demosaicing properties of the channel 
 */
int IMP_Encoder_SetChnH264Demask(int encChn, const IMPEncoderAttrH264Demask *pdemaskAttr);

/**
 * @fn int IMP_Encoder_GetChnH264Demask(int encChn, IMPEncoderAttrH264Demask *pdemaskAttr)
 *
 *  Get channel demosaicing properties 
 *
 * @param[in] encChn  Get channel demosaicing properties Channel Get channel demosaicing properties , Get channel demosaicing properties : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdemaskAttr  Get channel demosaicing properties 
 *
 * @retval 0  Get channel demosaicing properties 
 * @retval  Get channel demosaicing properties 0  Get channel demosaicing properties 
 *
 * @remarks  Get channel demosaicing properties API Will get the demosaicing properties of the channel ， Will get the demosaicing properties of the channel API Will get the demosaicing properties of the channel 
 *
 * @attention  Will get the demosaicing properties of the channel 
 */
int IMP_Encoder_GetChnH264Demask(int encChn, IMPEncoderAttrH264Demask *pdemaskAttr);

/**
 * @fn int IMP_Encoder_SetChnH264FrmUsedMode(int encChn, const IMPEncoderAttrH264FrmUsed *pfrmUsedAttr)
 *
 *  Set the channel input frame usage mode attribute 
 *
 * @param[in] encChn  Set the channel input frame usage mode attribute Channel Set the channel input frame usage mode attribute , Set the channel input frame usage mode attribute : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr  Input frame usage mode attribute parameter 
 *
 * @retval 0  Input frame usage mode attribute parameter 
 * @retval  Input frame usage mode attribute parameter 0  Input frame usage mode attribute parameter 
 *
 * @remarks  Input frame usage mode attribute parameter API Will set the input frame usage mode attribute of the channel ， Will set the input frame usage mode attribute of the channel API Will set the input frame usage mode attribute of the channel 
 *
 * @attention  Will set the input frame usage mode attribute of the channel 
 */
int IMP_Encoder_SetChnH264FrmUsedMode(int encChn, const IMPEncoderAttrH264FrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_GetChnH264FrmUsedMode(int encChn, IMPEncoderAttrH264FrmUsed *pfrmUsedAttr)
 *
 *  Get the attribute of the channel input frame usage mode 
 *
 * @param[in] encChn  Get the attribute of the channel input frame usage mode Channel Get the attribute of the channel input frame usage mode , Get the attribute of the channel input frame usage mode : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr  Get the attribute of the channel input frame usage mode 
 *
 * @retval 0  Get the attribute of the channel input frame usage mode 
 * @retval  Get the attribute of the channel input frame usage mode 0  Get the attribute of the channel input frame usage mode 
 *
 * @remarks  Get the attribute of the channel input frame usage mode API Will get the input frame usage mode attribute of the channel ， Will get the input frame usage mode attribute of the channel API Will get the input frame usage mode attribute of the channel 
 *
 * @attention  Will get the input frame usage mode attribute of the channel 
 */
int IMP_Encoder_GetChnH264FrmUsedMode(int encChn, IMPEncoderAttrH264FrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_SetChnH264Denoise(int encChn, const IMPEncoderAttrH264Denoise *pdenoiseAttr)
 *
 *  Set channel denoising properties 
 *
 * @param[in] encChn  Set channel denoising properties Channel Set channel denoising properties , Set channel denoising properties : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdenoiseAttr  Denoising attribute parameters 
 *
 * @retval 0  Denoising attribute parameters 
 * @retval  Denoising attribute parameters 0  Denoising attribute parameters 
 *
 * @remarks  Denoising attribute parameters API Will set the denoising properties of the channel ， Will set the denoising properties of the channel API Will set the denoising properties of the channel 
 *
 * @attention  Will set the denoising properties of the channel 
 */
int IMP_Encoder_SetChnH264Denoise(int encChn, const IMPEncoderAttrH264Denoise *pdenoiseAttr);

/**
 * @fn int IMP_Encoder_GetChnH264Denoise(int encChn, IMPEncoderAttrH264Denoise *pdenoiseAttr)
 *
 *  Get channel denoising properties 
 *
 * @param[in] encChn  Get channel denoising properties Channel Get channel denoising properties , Get channel denoising properties : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pdenoiseAttr  Get channel denoising properties 
 *
 * @retval 0  Get channel denoising properties 
 * @retval  Get channel denoising properties 0  Get channel denoising properties 
 *
 * @remarks  Get channel denoising properties API Will get the denoising properties of the channel ， Will get the denoising properties of the channel API Will get the denoising properties of the channel 
 *
 * @attention  Will get the denoising properties of the channel JPEG Will get the denoising properties of the channel 
 */
int IMP_Encoder_GetChnH264Denoise(int encChn, IMPEncoderAttrH264Denoise *pdenoiseAttr);

/**
 * @fn int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen)
 *
 *  Insert user data 
 *
 * @param[in] encChn  Insert user data Channel Insert user data , Insert user data : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] userData  User data pointer 
 * @param[in] userDataLen  User data length ,  User data length :(0, 1024], User data length  byte  User data length 
 *
 * @retval 0  User data length 
 * @retval  User data length 0  User data length 
 *
 * @remarks  User data length API Need channel already exists 
 * @remarks  If the channel is not created , If the channel is not created 
 * @remarks  If the channel is not created userData Empty or userDataLen Empty or 0, Empty or 
 * @remarks  Empty or , Only supports H.264 Encoding protocol 
 * @remarks H.264 Protocol channels are allocated at most 2 Block memory space is used to cache user data , And the size of each piece of user data does not exceed 1k byte And the size of each piece of user data does not exceed 
 *  If the data inserted by the user is redundant 2 Piece , Or the inserted piece of user data is greater than 1k byte  Or the inserted piece of user data is greater than , This interface will return an error. 
 * @remarks  Each piece of user data is SEI The packet format is inserted before the latest image stream packet. After a certain user data packet is encoded and sent ,
 * H.264  The memory space for buffering this piece of user data in the channel is cleared , Used to store new user data 
 *
 * @attention  Used to store new user data 
 */
int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen);

/**
 * @fn int IMP_Encoder_SetFisheyeEnableStatus(int encChn, int enable)
 *
 *  Set up Ingenic The enabled state of the provided fisheye correction algorithm 
 *
 * @param[in] encChn  The enabled state of the provided fisheye correction algorithm Channel The enabled state of the provided fisheye correction algorithm , The enabled state of the provided fisheye correction algorithm : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] enable 0: Disable ( default ),1: Enable 
 *
 * @retval 0  Enable 
 * @retval  Enable 0  Enable 
 *
 * @remarks  Since the enable state of the fisheye correction algorithm is fixed when the channel is created ， Since the enable state of the fisheye correction algorithm is fixed when the channel is created API Since the enable state of the fisheye correction algorithm is fixed when the channel is created 
 * @remarks  Since the enable state of the fisheye correction algorithm is fixed when the channel is created API Since the enable state of the fisheye correction algorithm is fixed when the channel is created Ingenic Since the enable state of the fisheye correction algorithm is fixed when the channel is created , Is not enabled by default ， That is, the fisheye correction algorithm provided by Ingenics cannot be used. 
 * @remarks  this API only apply to H264
 *
 * @attention  only apply to 
 */
int IMP_Encoder_SetFisheyeEnableStatus(int encChn, int enable);

/**
 * @fn int IMP_Encoder_GetFisheyeEnableStatus(int encChn, int *enable)
 *
 *  Obtain Ingenic Obtain 
 *
 * @param[in] encChn  Obtain Channel Obtain , Obtain : [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] enable  Back to set Ingenic Back to set ,0: Not enabled ,1: Enabled 
 *
 * @retval 0  Enabled 
 * @retval  Enabled 0  Enabled 
 *
 * @remarks  Enabled API Enabled H264
 *
 * @attention  Enabled 
 */
int IMP_Encoder_GetFisheyeEnableStatus(int encChn, int *enable);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_ENCODER_H__ */
