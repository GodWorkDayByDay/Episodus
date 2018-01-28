/*
GOCR API Copyright (C) 2001 Bruno Barberi Gnecco <brunobg@sourceforge.net>

This program is free software; you can redistribute it and/or
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#ifndef _GOCR_IMAGE_H

#ifndef _GOCR_MODULE_H
#endif.

#ifdef __cplusplus
#endif

/*! \file gocr_image.h
  \author Bruno Barberi Gnecco <brunobg@sourceforge.net>
*/

/** @name Image
/*@{*/
/**
  \brief Black pixel value.
  \sa gocr_Pixel.
*/
#define GOCR_BLACK			0

/**
  \sa gocr_Pixel.
*/
#define GOCR_WHITE			1

/**
*/
enum gocr_imagetype {
	GOCR_NONE, 			/**< No type. */
	GOCR_BW, 			/**< Black and white. */
	GOCR_GRAY, 			/**< Grayscale. */
	GOCR_COLOR,			/**< Color. */
	GOCR_OTHER 			/**< Other (user-defined). */
};

/**
*/
typedef enum gocr_imagetype gocr_ImageType;

/**

 Long description.
*/
	unsigned char	value : 1;	/**< pixel value. */
	unsigned char	mark1 : 1;	/**< user defined marker 1. */
	unsigned char	mark2 : 1;	/**< user defined marker 2. */
	unsigned char	mark3 : 1;	/**< user defined marker 3. */
	unsigned char	isblock : 1;	/**< is part of a block? */
	unsigned char	ischar : 1;	/**< is part of a character? */
	unsigned char	private1 : 1;	/**< reserved, used internally (find.c). */
	unsigned char	private2 : 1;	/**< reserved, used internally */
};

/**
*/
typedef struct gocr_pixelbw gocr_PixelBW;

struct gocr_pixelgray {
	unsigned char	mark1 : 1;	/**< user defined marker 1. */
	unsigned char	mark2 : 1;	/**< user defined marker 2. */
	unsigned char	mark3 : 1;	/**< user defined marker 3. */
	unsigned char	isblock : 1;	/**< is part of a block? */
	unsigned char	ischar : 1;	/**< is part of a character? */
	unsigned char	private1 : 1;	/**< reserved, used internally (find.c). */
	unsigned char	private2 : 1;	/**< reserved, used internally */

	unsigned char 	value;
typedef struct gocr_pixelgray gocr_PixelGray;

struct gocr_pixelcolor {
	unsigned char	mark1 : 1;	/**< user defined marker 1. */
	unsigned char	mark2 : 1;	/**< user defined marker 2. */
	unsigned char	mark3 : 1;	/**< user defined marker 3. */
	unsigned char	isblock : 1;	/**< is part of a block? */
	unsigned char	ischar : 1;	/**< is part of a character? */
	unsigned char	private1 : 1;	/**< reserved, used internally (find.c). */
	unsigned char	private2 : 1;	/**< reserved, used internally */

	unsigned char 	value[3];
typedef struct gocr_pixelcolor gocr_PixelColor;

/**

 It should work with any pixel data structure.
struct gocr_pixel {
	unsigned char	pad : 1;	/**< pad bit. */
	unsigned char	mark1 : 1;	/**< user defined marker 1. */
	unsigned char	mark2 : 1;	/**< user defined marker 2. */
	unsigned char	mark3 : 1;	/**< user defined marker 3. */
	unsigned char	isblock : 1;	/**< is part of a block? */
	unsigned char	ischar : 1;	/**< is part of a character? */
	unsigned char	private1 : 1;	/**< reserved, used internally (find.c). */
	unsigned char	private2 : 1;	/**< reserved, used internally */

	char		value/*[0]*/;
typedef struct gocr_pixel gocr_Pixel;

/**

 Long description.
struct gocr_image {
	char		*filename;	/**< file name; may be NULL. */
	int		width, height;	/**< size. */
	gocr_ImageType	type;		/**< image type. */

	union {
		gocr_PixelBW	**bw;	/**< bw pixel */
		gocr_PixelGray	**gray; /**< gray pixel */
		gocr_PixelColor	**color;/**< color pixel */
	} data;

/* you are unlikely to change these below. Future: hide them */
	int		threshold;	/**< image threshold, for gray->bw conversion. */
	int		sons;		/**< number of shared images */
	struct gocr_image *parent;	/**< if shared, the parent */
};

/**
*/
typedef struct gocr_image gocr_Image;

int datamalloc(gocr_Image * image);
/* image.c */
extern int gocr_imageWrite ( gocr_Image *image, char *filename );
extern int gocr_mainImageWriteWithData ( char *filename );

/* pixel.c */
extern /* inline */ int gocr_pixelSetMark1 ( gocr_Image *image, int x, int y, char value );
extern /* inline */ int gocr_pixelGetMark2 ( gocr_Image *image, int x, int y );
extern /* inline */ int gocr_pixelSetMark2 ( gocr_Image *image, int x, int y, char value );
extern /* inline */ int gocr_pixelGetMark3 ( gocr_Image *image, int x, int y );
extern /* inline */ int gocr_pixelSetMark3 ( gocr_Image *image, int x, int y, char value );

// #define gocr_isblock(image, x, y) \
// #define gocr_ischar(image, x, y) \
//  ((gocr_Pixel *)((image)->data.pix[y]+(x)*_gocr_imagePixelSize(image)))->ischar

extern void gocr_imagePixelSetBW ( gocr_Image *image, int x, int y,
extern unsigned char gocr_imagePixelGetBW ( gocr_Image *image, int x, int y );
extern void gocr_imagePixelSetGray ( gocr_Image *image, int x, int y,
		unsigned char data );
extern unsigned char gocr_imagePixelGetGray ( gocr_Image *image, int x, int y );
extern void gocr_imagePixelSetColor ( gocr_Image *image, int x, int y,
		unsigned char data[3] );
extern unsigned char *gocr_imagePixelGetColor ( gocr_Image *image, int x, int y );

/*@}*/
#ifdef _GOCR_INTERNAL_H /*ok, this #ifdef sucks, but is a quick hack */
extern int 	_gocr_imageLoad		( const char *filename, void *data );
extern int 	_gocr_thresholdGrayToBW ( gocr_Image *image );

#define _gocr_private1(image, x, y) \

#define _gocr_private2(image, x, y) \

#define _gocr_maskGet(img, x, y) \

#define _gocr_maskSet(img, x, y, v) \

#endif
/**
  This variable holds the image being processed right now, and can be freely
  accessed by the programmer.
  \sa gocr_imageLoad, gocr_imageClose, gocr_Image.
*/
extern gocr_Image	*currentimage;

#define gocr_isblock(image, x, y) \

#define gocr_ischar(image, x, y) \

extern void NSgocr_isblock(gocr_Image *image, int x, int y, char value);
#ifdef __cplusplus
#endif


#endif