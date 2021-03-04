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
 * @brief OSD Module ， Can superimpose pictures, bitmaps, straight lines, rectangular boxes on the video stream 
 *
 * @section osd_summary 1  Module introduction 
 * OSD The full name is On-Screen Display . The function of the module is to superimpose information such as lines and pictures in each film source. 
 *
 * @section osd_concept 2  Related concepts 
 * @subsection osd_region 2.1 Region
 * Region Is the superimposed area ， in API Chinese abbreviation Rgn . Each Region Have certain image information ， Can pass OSD After the modules are superimposed ， Combined with the background image into a picture. 
 *  For picture overlay ， Can also be achieved Alpha effect. For detailed introduction of various overlay types, please refer to @ref osd_region_type . 
 *
 * @subsection osd_region_type 2.1 Region type
 * Region There are several types ， They are: \n
 * OSD_REG_LINE :straight line \n
 * OSD_REG_RECT :Rectangle \n
 * OSD_REG_BITMAP :bitmap \n
 * OSD_REG_COVER : Occlusion \n
 * OSD_REG_PIC :image \n
 *  among them ， The difference between bitmap and picture is ， Bitmap only performs monochrome coverage of pixels ， And the picture is RGBA Image Alpha Overlay. 
 *
 * @section osd_fun 3  Module function 
 * OSD The module supports lines, rectangular boxes, bitmap overlay, rectangular occlusion, and image overlay. 
 *  Lines, rectangular boxes and bitmaps are implemented by software; rectangular occlusion and image overlays are implemented by hardware. 
 *
 * @section osd_use 4  Module usage 
 * OSD The use of generally has the following steps 
 * 1.  create OSD group 
 * 2.  Bind OSD Group into the system 
 * 3.  Group into the system OSD area 
 * 4.  registered OSD Area to OSD In the group 
 * 5.  Set up OSD Group area attributes and area attributes 
 * 6.  Group area attributes and area attributes OSD Function switch 
 * @{
 */

/**
 *  Error return value 
 */
#define INVHANDLE		(-1)

/**
 * OSD  Area handle 
 */
typedef int IMPRgnHandle;

/**
 * OSD Color type ， The color format is bgra
 */
typedef enum {
	OSD_BLACK	= 0xff000000, /**<  black  */
	OSD_WHITE	= 0xffffffff, /**<  white  */
	OSD_RED		= 0xffff0000, /**<  red  */
	OSD_GREEN	= 0xff00ff00, /**<  green  */
	OSD_BLUE	= 0xff0000ff, /**<  blue  */
}IMPOsdColour;

/**
 * OSD Area type 
 */
typedef enum {
	OSD_REG_INV			= 0, /**<  Undefined area type  */
	OSD_REG_LINE		= 1, /**<  line  */
	OSD_REG_RECT		= 2, /**<  rectangle  */
	OSD_REG_BITMAP		= 3, /**<  Bitmap  */
	OSD_REG_COVER		= 4, /**<  Rectangular occlusion  */
	OSD_REG_PIC			= 5, /**<  image ， Suitable for use as Logo Or timestamp  */
} IMPOsdRgnType;

/**
 * OSD Area line and rectangle data 
 */
typedef struct {
	uint32_t		color;			/**<  colour ， Only supports OSD_WHITE，OSD_BLACK，OSD_RED Three formats  */
	uint32_t		linewidth;		/**<  Line width  */
} lineRectData;

/**
 * OSD Area occlusion data 
 */
typedef struct {
	uint32_t		color;			/**<  Area occlusion data ， Area occlusion data bgra Color format  */
} coverData;


/**
 * OSD Regional image data 
 */
typedef struct {
	void				*pData;			/**<  Picture data pointer  */
} picData;

/**
 * OSD Area attribute data 
 */
typedef union {
	void				*bitmapData;		/**<  Dot matrix data  */
	lineRectData			lineRectData;		/**<  Line and rectangle data  */
	coverData			coverData;		/**<  Occlusion data  */
	picData				picData;		/**<  Picture data  */
} IMPOSDRgnAttrData;

/**
 * OSD Area attributes 
 */
typedef struct {
	IMPOsdRgnType		type;			/**< OSD Area attributes  */
	IMPRect				rect;			/**<  Rectangular data  */
	IMPPixelFormat		fmt;			/**<  Point format  */
	IMPOSDRgnAttrData	data;			/**< OSD Point format  */
} IMPOSDRgnAttr;

/**
 * OSD Group area attributes 
 */
typedef struct {
	int					show;			/**<  Whether to show  */
	IMPPoint			offPos;			/**<  Show starting coordinates  */
	float				scalex;			/**<  Zoom x parameter  */
	float				scaley;			/**<  parameter y parameter  */
	int					gAlphaEn;		/**< Alpha switch  */
	int					fgAlhpa;		/**<  prospect Alpha */
	int					bgAlhpa;		/**<  background Alpha */
	int					layer;			/**<  Display layer  */
} IMPOSDGrpRgnAttr;


/**
 * @fn int IMP_OSD_CreateGroup(int grpNum)
 *
 *  Display layer OSD Display layer 
 *
 * @param[in] grpNum OSD Group No , Ranges : [0, @ref NR_MAX_OSD_GROUPS - 1]
 *
 * @retval 0  success 
 * @retval  non- 0  failure 
 *
 * @remarks  no. 
 *
 * @attention  no. 
 */
int IMP_OSD_CreateGroup(int grpNum);

/**
 * @fn int IMP_OSD_DestroyGroup(int grpNum)
 *
 *  destroy OSD destroy 
 *
 * @param[in] grpNum OSD destroy , destroy : [0, @ref NR_MAX_OSD_GROUPS - 1]
 *
 * @retval 0  destroy 
 * @retval  destroy 0  destroy 
 *
 * @remarks  Call this API It is required that the corresponding group has been created. 
 *
 * @attention  It is required that the corresponding group has been created. 
 */
int IMP_OSD_DestroyGroup(int grpNum);

/**
 * @fn int IMP_OSD_AttachToGroup(IMPCell *from, IMPCell *to)
 *
 *  will OSD Group added to the system 
 *
 * @param[in] from OSD unit 
 * @param[in] to  Other units in the system 
 *
 * @retval 0  Other units in the system 
 * @retval  Other units in the system 0  Other units in the system 
 *
 * @remarks  New version SDK Recommended in Bind The way will OSD String to the data stream of the system ，Attach Is no longer recommended ， but API Keep ， Conveniently compatible with previous versions of software. 
 *  For details, please refer to @ref bind  Example of 
 *
 * @attention  Example of 
 */
int IMP_OSD_AttachToGroup(IMPCell *from, IMPCell *to);

/**
 * @fn IMPRgnHandle IMP_OSD_CreateRgn(IMPOSDRgnAttr *prAttr)
 *
 *  Example of OSD Example of 
 *
 * @param[in] prAttr OSD Example of 
 *
 * @retval  greater or equal to 0  greater or equal to 
 * @retval  Less than 0  Less than 
 *
 * @remarks  Less than 
 *
 * @attention  Less than 
 */
IMPRgnHandle IMP_OSD_CreateRgn(IMPOSDRgnAttr *prAttr);

/**
 * @fn void IMP_OSD_DestroyRgn(IMPRgnHandle handle)
 *
 *  Less than OSD Less than 
 *
 * @param[in] prAttr  Less than ，IMP_OSD_CreateRgn The return value 
 *
 * @retval  no 
 *
 * @remarks  no 
 *
 * @attention  no 
 */
void IMP_OSD_DestroyRgn(IMPRgnHandle handle);

/**
 * @fn int IMP_OSD_RegisterRgn(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 *  no OSD no 
 *
 * @param[in] handle  no ，IMP_OSD_CreateRgn no 
 * @param[in] grpNum OSD no 
 * @param[in] pgrAttr OSD Group display attributes 
 *
 * @retval 0  Group display attributes 
 * @retval  Group display attributes 0  Group display attributes 
 *
 * @remarks  Group display attributes API When requesting the corresponding OSD The group has been created. 
 *
 * @attention  The group has been created. 
 */
int IMP_OSD_RegisterRgn(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_UnRegisterRgn(IMPRgnHandle handle, int grpNum)
 *
 *  Logout OSD Logout 
 *
 * @param[in] handle  Logout ，IMP_OSD_CreateRgn Logout 
 * @param[in] grpNum OSD Logout 
 *
 * @retval 0  Logout 
 * @retval  Logout 0  Logout 
 *
 * @remarks  Logout API Logout OSD Group has been created , The corresponding area has been registered. 
 *
 * @attention  The corresponding area has been registered. 
 */
int IMP_OSD_UnRegisterRgn(IMPRgnHandle handle, int grpNum);

/**
 * @fn int IMP_OSD_SetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr)
 *
 *  Set area properties 
 *
 * @param[in] handle  Set area properties ，IMP_OSD_CreateRgn Set area properties 
 * @param[in] prAttr OSD Set area properties 
 *
 * @retval 0  Set area properties 
 * @retval  Set area properties 0  Set area properties 
 *
 * @remarks  Set area properties API It is required that the corresponding area has been created. 
 *
 * @attention  It is required that the corresponding area has been created. 
 */
int IMP_OSD_SetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr);

/**
 * @fn int IMP_OSD_GetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr)
 *
 *  Get area attributes 
 *
 * @param[in] handle  Get area attributes ，IMP_OSD_CreateRgn Get area attributes 
 * @param[out] prAttr OSD Get area attributes 
 *
 * @retval 0  Get area attributes 
 * @retval  Get area attributes 0  Get area attributes 
 *
 * @remarks  Get area attributes API Get area attributes 
 *
 * @attention  Get area attributes 
 */
int IMP_OSD_GetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr);

/**
 * @fn int IMP_OSD_UpdateRgnAttrData(IMPRgnHandle handle, IMPOSDRgnAttrData *prAttrData)
 *
 *  Update area data attributes ， Only for OSD_REG_BITMAP with OSD_REG_PIC Type of area 
 *
 * @param[in] handle  Type of area ，IMP_OSD_CreateRgn Type of area 
 * @param[in] prAttrData OSD Area data attributes 
 *
 * @retval 0  Area data attributes 
 * @retval  Area data attributes 0  Area data attributes 
 *
 * @remarks  Area data attributes API It requires that the corresponding area has been created and the area attribute has been set to OSD_REG_BITMAP or OSD_REG_PIC or 
 *
 * @attention  or 
 */
int IMP_OSD_UpdateRgnAttrData(IMPRgnHandle handle, IMPOSDRgnAttrData *prAttrData);

/**
 * @fn int IMP_OSD_SetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 *  or OSD or 
 *
 * @param[in] handle  or ，IMP_OSD_CreateRgn or 
 * @param[in] grpNum OSD or 
 * @param[in] pgrAttr OSD or 
 *
 * @retval 0  or 
 * @retval  or 0  or 
 *
 * @remarks  or API or OSD or , The zone has been created and registered. 
 *
 * @attention  The zone has been created and registered. 
 */
int IMP_OSD_SetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_GetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr)
 *
 *  Obtain OSD Obtain 
 *
 * @param[in] handle  Obtain ，IMP_OSD_CreateRgn Obtain 
 * @param[in] grpNum OSD Obtain 
 * @param[out] pgrAttr OSD Obtain 
 *
 * @retval 0  Obtain 
 * @retval  Obtain 0  Obtain 
 *
 * @remarks  Obtain API Obtain OSD Obtain , Obtain 
 *
 * @attention  Obtain 
 */
int IMP_OSD_GetGrpRgnAttr(IMPRgnHandle handle, int grpNum, IMPOSDGrpRgnAttr *pgrAttr);

/**
 * @fn int IMP_OSD_ShowRgn(IMPRgnHandle handle, int grpNum, int showFlag)
 *
 *  Set whether to display the group area 
 *
 * @param[in] handle  Set whether to display the group area ，IMP_OSD_CreateRgn Set whether to display the group area 
 * @param[in] grpNum OSD Set whether to display the group area 
 * @param[in] showFlag OSD Group area display switch 
 *
 * @retval 0  Group area display switch 
 * @retval  Group area display switch 0  Group area display switch 
 *
 * @remarks  Group area display switch API Group area display switch OSD Group area display switch , Group area display switch 
 *
 * @attention  Group area display switch 
 */
int IMP_OSD_ShowRgn(IMPRgnHandle handle, int grpNum, int showFlag);

/**
 * @fn int IMP_OSD_Start(int grpNum)
 *
 *  Set up OSD Group display 
 *
 * @param[in] grpNum OSD Group display 
 *
 * @retval 0  Group display 
 * @retval  Group display 0  Group display 
 *
 * @remarks  Group display API Group display OSD Group display 
 *
 * @attention  Group display 
 */
int IMP_OSD_Start(int grpNum);

/**
 * @fn int IMP_OSD_Stop(int grpNum)
 *
 *  Set stop OSD Set stop 
 *
 * @param[in] grpNum OSD Set stop 
 *
 * @retval 0  Set stop 
 * @retval  Set stop 0  Set stop 
 *
 * @remarks  Set stop API Set stop OSD Set stop 
 *
 * @attention  Set stop 
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
