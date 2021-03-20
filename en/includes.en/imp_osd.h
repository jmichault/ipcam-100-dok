/*
 * IMP OSD header file.
 *
 * Copyright (C) 2015 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_OSD_H__
#define __IMP_OSD_H__

#include "imp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */
/**
 * @file
 * IMP OSD Module header file 
 */


/**
 * @defgroup IMP_OSD
 * @ingroup imp
 * @brief OSD Module ， Can superimpose pictures, bitmaps, straight lines, and rectangular frames on the video stream 
 *
 * @section osd_summary 1 Module introduction 
 * OSD The full name is On-Screen Display . 
 *
 * @section osd_concept 2 Related concepts 
 * @subsection osd_region 2.1 Region
 * Region Is the superimposed area ， in API Chinese abbreviation Rgn . Region Have certain image information ， Can pass OSD After the modules are superimposed ， Combined with the background image into a picture. 
 * For picture overlay ， Can also be achieved Alpha effect. @ref osd_region_type . 
 *
 * @subsection osd_region_type 2.1 Region type
 * Region There are several types ， They are: \n
 * OSD_REG_LINE :straight line \n
 * OSD_REG_RECT :Rectangle \n
 * OSD_REG_BITMAP :bitmap \n
 * OSD_REG_COVER : Occlusion \n
 * OSD_REG_PIC :image \n
 * among them ， The difference between bitmap and picture is ， Bitmap only performs monochrome coverage of pixels ， And the picture is RGBA Image Alpha Overlay. 
 *
 * @section osd_fun 3 Module function 
 * OSD The module supports lines, rectangular boxes, bitmap overlay, rectangular occlusion, and image overlay. 
 * Lines, rectangular boxes and bitmaps are implemented by software; rectangular occlusion and image overlays are implemented by hardware. 
 *
 * @section osd_use 4 Module usage 
 * OSD The use of generally has the following steps 
 * 1. create OSD group 
 * 2. Bind OSD Group into the system 
 * 3. create OSD area 
 * 4. registered OSD Area to OSD In the group 
 * 5. Set up OSD Group area attributes and area attributes 
 * 6. Set up OSD Function switch 
 * @{
 */

/**
 * Error return value 
 */
#define INVHANDLE		(-1)

/**
 * OSD Area handle 
 */
typedef int IMPRgnHandle;

/**
 * OSD Color type ， The color format is bgra
 */
typedef enum {
	OSD_BLACK	= 0xff000000, /**< black */
	OSD_WHITE	= 0xffffffff, /**< white */
	OSD_RED		= 0xffff0000, /**< red */
	OSD_GREEN	= 0xff00ff00, /**< green */
	OSD_BLUE	= 0xff0000ff, /**< blue */
}IMPOsdColour;

/**
 * OSD Area type 
 */
typedef enum {
	OSD_REG_INV			= 0, /**< Undefined area type */
	OSD_REG_LINE		= 1, /**< line */
	OSD_REG_RECT		= 2, /**< rectangle */
	OSD_REG_BITMAP		= 3, /**< Bitmap */
	OSD_REG_COVER		= 4, /**< Rectangular occlusion */
	OSD_REG_PIC			= 5, /**< image ， Suitable for use as Logo Or timestamp */
} IMPOsdRgnType;

/**
 * OSD Area line and rectangle data 
 */
typedef struct {
	uint32_t		color;			/**< colour ， Only supports OSD_WHITE，OSD_BLACK，OSD_RED Three formats */
	uint32_t		linewidth;		/**< Line width */
} lineRectData;

/**
 * OSD Area occlusion data 
 */
typedef struct {
	uint32_t		color;			/**< colour ， Only supports bgra Color format */
} coverData;


/**
 * OSD Regional image data 
 */
typedef struct {
	void				*pData;			/**< Picture data pointer */
} picData;

/**
 * OSD Area attribute data 
 */
typedef union {
	void				*bitmapData;		/**< Dot matrix data */
	lineRectData			lineRectData;		/**< Line and rectangle data */
	coverData			coverData;		/**< Occlusion data */
	picData				picData;		/**< Picture data */
} IMPOSDRgnAttrData;

/**
 * OSD Area attributes 
 */
typedef struct {
	IMPOsdRgnType		type;			/**< OSD Area type */
	IMPRect				rect;			/**< Rectangular data */
	IMPPixelFormat		fmt;			/**< Point format */
	IMPOSDRgnAttrData	data;			/**< OSD Area attribute data */
} IMPOSDRgnAttr;

/**
 * OSD Zone effective timestamp 
 */
typedef struct {
	uint64_t ts;						/**< Timestamp */
	uint64_t minus;						/**< Lower limit */
	uint64_t plus;						/**< Upper limit */
} IMPOSDRgnTimestamp;

/**
 * OSD Group area attributes 
 */
typedef struct {
	int					show;			/**< Whether to show */
	IMPPoint			offPos;			/**< Show starting coordinates */
	float				scalex;			/**< Zoom x parameter */
	float				scaley;			/**< Zoom y parameter */
	int					gAlphaEn;		/**< Alpha switch */
	int					fgAlhpa;		/**< prospect Alpha */
	int					bgAlhpa;		/**< background Alpha */
	int					layer;			/**< Display layer */
} IMPOSDGrpRgnAttr;


/**
 * @fn int IMP_OSD_CreateGroup(int grpNum)
 *
 * create OSD group 
 *
 * @param[in] grpNum OSD Group No , Ranges : [0, @ref NR_MAX_OSD_GROUPS - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks no. 
 *
 * @attention no. 
 */
int IMP_OSD_CreateGroup(int grpNum);

/**
 * @fn int IMP_OSD_DestroyGroup(int grpNum)
 *
 * destroy OSD group 
 *
 * @param[in] grpNum OSD Group No , Ranges : [0, @ref NR_MAX_OSD_GROUPS - 1]
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API It is required that the corresponding group has been created. 
 *
 * @attention no. 
 */
int IMP_OSD_DestroyGroup(int grpNum);

/**
 * @fn int IMP_OSD_AttachToGroup(IMPCell *from, IMPCell *to)
 *
 * will OSD Group added to the system 
 *
 * @param[in] from OSD unit 
 * @param[in] to Other units in the system 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks New version SDK Recommended in Bind The way will OSD String to the data stream of the system ，Attach Is no longer recommended ， but API Keep ， Conveniently compatible with previous versions of software. 
 * For details, please refer to @ref bind Example of 
 *
 * @attention no. 
 */
int IMP_OSD_AttachToGroup(IMPCell *from, IMPCell *to);

/**
 * @fn IMPRgnHandle IMP_OSD_CreateRgn(IMPOSDRgnAttr *prAttr)
 *
 * create OSD area 
 *
 * @param[in] prAttr OSD Area attributes 
 *
 * @retval greater or equal to 0 success 
 * @retval Less than 0 failure 
 *
 * @remarks no. 
 *
 * @attention no. 
 */
IMPRgnHandle IMP_OSD_CreateRgn(IMPOSDRgnAttr *prAttr);

/**
 * @fn void IMP_OSD_DestroyRgn(IMPRgnHandle handle)
 *
 * destroy OSD area 
 *
 * @param[in] prAttr Area handle ，IMP_OSD_CreateRgn The return value 
 *
 * @retval no 
 *
 * @remarks no. 
 *
 * @attention no. 
 */
void IMP_OSD_DestroyRgn(IMPRgnHandle handle);

/**
 * @fn int IMP_OSD_RegisterRgn(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 * registered OSD area 
 *
 * @param[in] handle Area handle ，IMP_OSD_CreateRgn The return value 
 * @param[in] grpNum OSD Group No 
 * @param[in] pgrAttr OSD Group display attributes 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API When requesting the corresponding OSD The group has been created. 
 *
 * @attention no. 
 */
int IMP_OSD_RegisterRgn(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_UnRegisterRgn(IMPRgnHandle handle, int grpNum)
 *
 * Logout OSD area 
 *
 * @param[in] handle Area handle ，IMP_OSD_CreateRgn The return value 
 * @param[in] grpNum OSD Group No 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API When requesting the corresponding OSD Group has been created , The corresponding area has been registered. 
 *
 * @attention no. 
 */
int IMP_OSD_UnRegisterRgn(IMPRgnHandle handle, int grpNum);

/**
 * @fn int IMP_OSD_SetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr)
 *
 * Set area properties 
 *
 * @param[in] handle Area handle ，IMP_OSD_CreateRgn The return value 
 * @param[in] prAttr OSD Area attributes 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API It is required that the corresponding area has been created. 
 *
 * @attention no. 
 */
int IMP_OSD_SetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr);

/**
 * @fn int IMP_OSD_SetRgnAttrWithTimestamp(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr, IMPOSDRgnTimestamp *prTs)
 *
 * Set regional attributes and effective time 
 *
 * @param[in] handle Area handle ，IMP_OSD_CreateRgn The return value 
 * @param[in] prAttr OSD Area attributes 
 * @param[in] prTs Effective time 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API It is required that the corresponding area has been created. 
 *
 * @attention no. 
 */
int IMP_OSD_SetRgnAttrWithTimestamp(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr, IMPOSDRgnTimestamp *prTs);

/**
 * @fn int IMP_OSD_GetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr)
 *
 * Get area attributes 
 *
 * @param[in] handle Area handle ，IMP_OSD_CreateRgn The return value 
 * @param[out] prAttr OSD Area attributes 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API It is required that the corresponding area has been created. 
 *
 * @attention no. 
 */
int IMP_OSD_GetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr);

/**
 * @fn int IMP_OSD_UpdateRgnAttrData(IMPRgnHandle handle, IMPOSDRgnAttrData *prAttrData)
 *
 * Update area data attributes ， Only for OSD_REG_BITMAP with OSD_REG_PIC Area type 
 *
 * @param[in] handle Area handle ，IMP_OSD_CreateRgn The return value 
 * @param[in] prAttrData OSD Area data attributes 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API It requires that the corresponding area has been created and the area attribute has been set to OSD_REG_BITMAP or OSD_REG_PIC . 
 *
 * @attention no. 
 */
int IMP_OSD_UpdateRgnAttrData(IMPRgnHandle handle, IMPOSDRgnAttrData *prAttrData);

/**
 * @fn int IMP_OSD_SetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 * Set up OSD Group area attributes 
 *
 * @param[in] handle Area handle ，IMP_OSD_CreateRgn The return value 
 * @param[in] grpNum OSD Group No 
 * @param[in] pgrAttr OSD Group area attributes 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API When requesting the corresponding OSD Group has been created , The zone has been created and registered. 
 *
 * @attention no. 
 */
int IMP_OSD_SetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_GetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 * Obtain OSD Group area attributes 
 *
 * @param[in] handle Area handle ，IMP_OSD_CreateRgn The return value 
 * @param[in] grpNum OSD Group No 
 * @param[out] pgrAttr OSD Group area attributes 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API When requesting the corresponding OSD Group has been created , The zone has been created and registered. 
 *
 * @attention no. 
 */
int IMP_OSD_GetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_ShowRgn(IMPRgnHandle handle, int grpNum, int showFlag)
 *
 * Set whether to display the group area 
 *
 * @param[in] handle Area handle ，IMP_OSD_CreateRgn The return value 
 * @param[in] grpNum OSD Group No 
 * @param[in] showFlag OSD Group area display switch 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API When requesting the corresponding OSD Group has been created , The zone has been created and registered. 
 *
 * @attention no. 
 */
int IMP_OSD_ShowRgn(IMPRgnHandle handle, int grpNum, int showFlag);

/**
 * @fn int IMP_OSD_Start(int grpNum)
 *
 * Set up OSD Group display 
 *
 * @param[in] grpNum OSD Group No 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API When requesting the corresponding OSD The group has been created. 
 *
 * @attention no. 
 */
int IMP_OSD_Start(int grpNum);

/**
 * @fn int IMP_OSD_Stop(int grpNum)
 *
 * Set stop OSD Group display 
 *
 * @param[in] grpNum OSD Group No 
 *
 * @retval 0 success 
 * @retval non- 0 failure 
 *
 * @remarks Call this API When requesting the corresponding OSD The group has been created. 
 *
 * @attention no. 
 */
int IMP_OSD_Stop(int grpNum);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_OSD_H__ */
