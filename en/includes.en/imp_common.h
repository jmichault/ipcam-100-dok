/*
 * IMP common data structure header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_COMMON_H__
#define __IMP_COMMON_H__

#include <stdint.h>
#include <pthread.h>
#include <linux/videodev2.h>
#include <stdio.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * SDK-T15 Common data structure header file 
 */

/**
 * IMP  equipment ID Enumeration definition .
 */
typedef enum {
	DEV_ID_FS,			/**<  Video source  */
	DEV_ID_ENC,			/**<  Encoder  */
	DEV_ID_DEC,			/**<  decoder  */
	DEV_ID_IVS,			/**<  algorithm  */
	DEV_ID_OSD,			/**<  Image overlay  */
	DEV_ID_FG1DIRECT,		/**< FB FG1Direct */
	DEV_ID_RESERVED_START,
	DEV_ID_RESERVED_END = 23,
	NR_MAX_DEVICES,
} IMPDeviceID;

/**
 * IMPCell Image overlay .
 */
typedef struct {
	IMPDeviceID	deviceID;		/**<  Image overlay ID */
	int			groupID;		/**<  group ID */
	int			outputID;		/**<  Output ID */
} IMPCell;

/**
 * IMP Frame image information definition .
 */
typedef struct {
	int index;			/**<  Frame number  */
	int pool_idx;		/**<  Where the frame is Pool of ID */

	uint32_t width;			/**<  Frame width  */
	uint32_t height;			/**<  Frame height  */
	uint32_t pixfmt;			/**<  Frame image format  */
	uint32_t size;			/**<  The size of the space occupied by the frame  */

	uint32_t phyAddr;	/**<  Physical address of the frame  */
	uint32_t virAddr;	/**<  Virtual address of the frame  */

	int64_t timeStamp;	/**<  Timestamp of frame  */
	uint32_t priv[0];	/*  Private data  */
} IMPFrameInfo;

/**
 *  Encoding and decoding protocol type 
 */
typedef enum {
	PT_JPEG,					/**< JPEG Image protocol type  */
	PT_H264,					/**< H264 Video protocol type  */
} IMPPayloadType;

/**
 * IMP Image format definition .
 */
typedef enum {
	PIX_FMT_YUV420P,   /**< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples) */
	PIX_FMT_YUYV422,   /**< packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr */
	PIX_FMT_UYVY422,   /**< packed YUV 4:2:2, 16bpp, Cb Y0 Cr Y1 */
	PIX_FMT_YUV422P,   /**< planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples) */
	PIX_FMT_YUV444P,   /**< planar YUV 4:4:4, 24bpp, (1 Cr & Cb sample per 1x1 Y samples) */
	PIX_FMT_YUV410P,   /**< planar YUV 4:1:0,  9bpp, (1 Cr & Cb sample per 4x4 Y samples) */
	PIX_FMT_YUV411P,   /**< planar YUV 4:1:1, 12bpp, (1 Cr & Cb sample per 4x1 Y samples) */
	PIX_FMT_GRAY8,     /**<	   Y	    ,  8bpp */
	PIX_FMT_MONOWHITE, /**<	   Y	    ,  1bpp, 0 is white, 1 is black, in each byte pixels are ordered from the msb to the lsb */
	PIX_FMT_MONOBLACK, /**<	   Y	    ,  1bpp, 0 is black, 1 is white, in each byte pixels are ordered from the msb to the lsb */

	PIX_FMT_NV12,      /**< planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V) */
	PIX_FMT_NV21,      /**< as above, but U and V bytes are swapped */

	PIX_FMT_RGB24,     /**< packed RGB 8:8:8, 24bpp, RGBRGB... */
	PIX_FMT_BGR24,     /**< packed RGB 8:8:8, 24bpp, BGRBGR... */

	PIX_FMT_ARGB,      /**< packed ARGB 8:8:8:8, 32bpp, ARGBARGB... */
	PIX_FMT_RGBA,	   /**< packed RGBA 8:8:8:8, 32bpp, RGBARGBA... */
	PIX_FMT_ABGR,	   /**< packed ABGR 8:8:8:8, 32bpp, ABGRABGR... */
	PIX_FMT_BGRA,	   /**< packed BGRA 8:8:8:8, 32bpp, BGRABGRA... */

	PIX_FMT_RGB565BE,  /**< packed RGB 5:6:5, 16bpp, (msb)	  5R 6G 5B(lsb), big-endian */
	PIX_FMT_RGB565LE,  /**< packed RGB 5:6:5, 16bpp, (msb)	  5R 6G 5B(lsb), little-endian */
	PIX_FMT_RGB555BE,  /**< packed RGB 5:5:5, 16bpp, (msb)1A 5R 5G 5B(lsb), big-endian, most significant bit to 0 */
	PIX_FMT_RGB555LE,  /**< packed RGB 5:5:5, 16bpp, (msb)1A 5R 5G 5B(lsb), little-endian, most significant bit to 0 */

	PIX_FMT_BGR565BE,  /**< packed BGR 5:6:5, 16bpp, (msb)	 5B 6G 5R(lsb), big-endian */
	PIX_FMT_BGR565LE,  /**< packed BGR 5:6:5, 16bpp, (msb)	 5B 6G 5R(lsb), little-endian */
	PIX_FMT_BGR555BE,  /**< packed BGR 5:5:5, 16bpp, (msb)1A 5B 5G 5R(lsb), big-endian, most significant bit to 1 */
	PIX_FMT_BGR555LE,  /**< packed BGR 5:5:5, 16bpp, (msb)1A 5B 5G 5R(lsb), little-endian, most significant bit to 1 */

	PIX_FMT_0RGB,      /**< packed RGB 8:8:8, 32bpp, 0RGB0RGB... */
	PIX_FMT_RGB0,	   /**< packed RGB 8:8:8, 32bpp, RGB0RGB0... */
	PIX_FMT_0BGR,	   /**< packed BGR 8:8:8, 32bpp, 0BGR0BGR... */
	PIX_FMT_BGR0,	   /**< packed BGR 8:8:8, 32bpp, BGR0BGR0... */

	PIX_FMT_BAYER_BGGR8,    /**< bayer, BGBG..(odd line), GRGR..(even line), 8-bit samples */
	PIX_FMT_BAYER_RGGB8,    /**< bayer, RGRG..(odd line), GBGB..(even line), 8-bit samples */
	PIX_FMT_BAYER_GBRG8,    /**< bayer, GBGB..(odd line), RGRG..(even line), 8-bit samples */
	PIX_FMT_BAYER_GRBG8,    /**< bayer, GRGR..(odd line), BGBG..(even line), 8-bit samples */

	PIX_FMT_RAW,

	PIX_FMT_NB,        /**< number of pixel formats. */
} IMPPixelFormat;

/**
 * IMP Point coordinate information .
 */
typedef struct {
	int		x;			/**< Abscissa   */
	int		y;			/**< Y-axis   */
} IMPPoint;

/**
 * IMP  Rectangular area information .
 *
 *  As shown below ， when p0(100,100) As a starting point ， To make width with height for 100 Time ， then p1 then (199,199)
 * width = abs(p1.x-p0.x)+1   height = abs(p1.y-p0.y)+1   The number of points equals the distance +1
 * p0(100,100) _____100______
 *            |              |
 *            |              |
 *         100|              |
 *            |              |
 *            |______________|
 *                           p1(199,199)
 *
 */
typedef struct {
	IMPPoint		p0;		/**< Coordinate information of the upper left corner point   */
	IMPPoint		p1;		/**< Coordinate information of the lower right corner point   */
} IMPRect;

static inline int calc_pic_size(int width, int height, IMPPixelFormat imp_pixfmt)
{
	int bpp1 = 0, bpp2 = 1,size;

#define BPP(FMT, A, B) case FMT: bpp1 = A;bpp2 = B;break
	switch (imp_pixfmt) {
		BPP(PIX_FMT_NV12, 3, 2);
		BPP(PIX_FMT_YUYV422, 2, 1);
		BPP(PIX_FMT_UYVY422, 2, 1);
		BPP(PIX_FMT_RGB565BE, 2, 1);
	default: break;
	}
#undef BPP
	size = width * height * bpp1 / bpp2;

	return size;
}

static inline const char *fmt_to_string(IMPPixelFormat imp_pixfmt)
{
	static const char *nv12 = "nv12";
	static const char *yuyv422 = "yuyv422";

	switch (imp_pixfmt) {
	case PIX_FMT_NV12:
		return nv12;
	case PIX_FMT_YUYV422:
		return yuyv422;
	default:
		break;
	}
	return NULL;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_COMMON_H__ */
