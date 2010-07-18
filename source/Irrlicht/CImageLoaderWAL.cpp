// Copyright (C) 2004 Murphy McCauley
// Copyright (C) 2007-2009 Christian Stehno
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CImageLoaderWAL.h"
#include "CColorConverter.h"
#include "CImage.h"
#include "os.h"
#include "dimension2d.h"
#include "IVideoDriver.h"
#include "IFileSystem.h"
#include "IReadFile.h"
#include "irrString.h"

namespace irr
{
namespace video
{

// old implementation
#if 0

// May or may not be fully implemented
#define TRY_LOADING_PALETTE_FROM_FILE 0

// Default palette for Q2 WALs.

s32 CImageLoaderWAL::DefaultPaletteQ2[256] = {
0x000000L,0x0F0F0FL,0x1F1F1FL,0x2F2F2FL,0x3F3F3FL,0x4B4B4BL,0x5B5B5BL,0x6B6B6BL,0x7B7B7BL,0x8B8B8BL,0x9B9B9BL,
0xABABABL,0xBBBBBBL,0xCBCBCBL,0xDBDBDBL,0xEBEBEBL,0x634B23L,0x5B431FL,0x533F1FL,0x4F3B1BL,0x47371BL,0x3F2F17L,
0x3B2B17L,0x332713L,0x2F2313L,0x2B1F13L,0x271B0FL,0x23170FL,0x1B130BL,0x170F0BL,0x130F07L,0x0F0B07L,0x5F5F6FL,
0x5B5B67L,0x5B535FL,0x574F5BL,0x534B53L,0x4F474BL,0x473F43L,0x3F3B3BL,0x3B3737L,0x332F2FL,0x2F2B2BL,0x272727L,
0x232323L,0x1B1B1BL,0x171717L,0x131313L,0x8F7753L,0x7B6343L,0x735B3BL,0x674F2FL,0xCF974BL,0xA77B3BL,0x8B672FL,
0x6F5327L,0xEB9F27L,0xCB8B23L,0xAF771FL,0x93631BL,0x774F17L,0x5B3B0FL,0x3F270BL,0x231707L,0xA73B2BL,0x9F2F23L,
0x972B1BL,0x8B2713L,0x7F1F0FL,0x73170BL,0x671707L,0x571300L,0x4B0F00L,0x430F00L,0x3B0F00L,0x330B00L,0x2B0B00L,
0x230B00L,0x1B0700L,0x130700L,0x7B5F4BL,0x735743L,0x6B533FL,0x674F3BL,0x5F4737L,0x574333L,0x533F2FL,0x4B372BL,
0x433327L,0x3F2F23L,0x37271BL,0x2F2317L,0x271B13L,0x1F170FL,0x170F0BL,0x0F0B07L,0x6F3B17L,0x5F3717L,0x532F17L,
0x432B17L,0x372313L,0x271B0FL,0x1B130BL,0x0F0B07L,0xB35B4FL,0xBF7B6FL,0xCB9B93L,0xD7BBB7L,0xCBD7DFL,0xB3C7D3L,
0x9FB7C3L,0x87A7B7L,0x7397A7L,0x5B879BL,0x47778BL,0x2F677FL,0x17536FL,0x134B67L,0x0F435BL,0x0B3F53L,0x07374BL,
0x072F3FL,0x072733L,0x001F2BL,0x00171FL,0x000F13L,0x00070BL,0x000000L,0x8B5757L,0x834F4FL,0x7B4747L,0x734343L,
0x6B3B3BL,0x633333L,0x5B2F2FL,0x572B2BL,0x4B2323L,0x3F1F1FL,0x331B1BL,0x2B1313L,0x1F0F0FL,0x130B0BL,0x0B0707L,
0x000000L,0x979F7BL,0x8F9773L,0x878B6BL,0x7F8363L,0x777B5FL,0x737357L,0x6B6B4FL,0x636347L,0x5B5B43L,0x4F4F3BL,
0x434333L,0x37372BL,0x2F2F23L,0x23231BL,0x171713L,0x0F0F0BL,0x9F4B3FL,0x934337L,0x8B3B2FL,0x7F3727L,0x772F23L,
0x6B2B1BL,0x632317L,0x571F13L,0x4F1B0FL,0x43170BL,0x37130BL,0x2B0F07L,0x1F0B07L,0x170700L,0x0B0000L,0x000000L,
0x777BCFL,0x6F73C3L,0x676BB7L,0x6363A7L,0x5B5B9BL,0x53578FL,0x4B4F7FL,0x474773L,0x3F3F67L,0x373757L,0x2F2F4BL,
0x27273FL,0x231F2FL,0x1B1723L,0x130F17L,0x0B0707L,0x9BAB7BL,0x8F9F6FL,0x879763L,0x7B8B57L,0x73834BL,0x677743L,
0x5F6F3BL,0x576733L,0x4B5B27L,0x3F4F1BL,0x374313L,0x2F3B0BL,0x232F07L,0x1B2300L,0x131700L,0x0B0F00L,0x00FF00L,
0x23E70FL,0x3FD31BL,0x53BB27L,0x5FA72FL,0x5F8F33L,0x5F7B33L,0xFFFFFFL,0xFFFFD3L,0xFFFFA7L,0xFFFF7FL,0xFFFF53L,
0xFFFF27L,0xFFEB1FL,0xFFD717L,0xFFBF0FL,0xFFAB07L,0xFF9300L,0xEF7F00L,0xE36B00L,0xD35700L,0xC74700L,0xB73B00L,
0xAB2B00L,0x9B1F00L,0x8F1700L,0x7F0F00L,0x730700L,0x5F0000L,0x470000L,0x2F0000L,0x1B0000L,0xEF0000L,0x3737FFL,
0xFF0000L,0x0000FFL,0x2B2B23L,0x1B1B17L,0x13130FL,0xEB977FL,0xC37353L,0x9F5733L,0x7B3F1BL,0xEBD3C7L,0xC7AB9BL,
0xA78B77L,0x876B57L,0x9F5B53L
};


bool CImageLoaderWAL::isALoadableFileExtension(const io::path& filename) const
{
	return core::hasFileExtension ( filename, "wal" );
}


bool CImageLoaderWAL::isALoadableFileFormat(irr::io::IReadFile* file) const
{
	return (false); // no recognition possible, use a proper file ending
}


IImage* CImageLoaderWAL::loadImage(irr::io::IReadFile* file) const
{
	// Try to get the color palette from elsewhere (usually in a pak along with the WAL).
	// If this fails we use the DefaultPaletteQ2.
	static s32 * palette = 0;
#if TRY_LOADING_PALETTE_FROM_FILE
	s32 loadedPalette[256];
#endif
	if (!palette)
	{
#if TRY_LOADING_PALETTE_FROM_FILE
		IImage * paletteImage;
		// Look in a couple different places...
		paletteImage = createImageFromFile("pics/colormap.pcx");
		if (!paletteImage)
			paletteImage = createImageFromFile("pics/colormap.tga");
		if (!paletteImage)
			paletteImage = createImageFromFile("colormap.pcx");
		if (!paletteImage)
			paletteImage = createImageFromFile("colormap.tga");
		if (paletteImage && (paletteImage->getDimension().Width == 256) ) {
			palette = &loadedPalette;
			for (u32 i = 0; i < 256; ++i) {
				palette[i] = paletteImage->getPixel(i, 0).color;
			}
		} else {
			//FIXME: try reading a simple palette from "wal.pal"
			palette = DefaultPaletteQ2;
		}
		if (paletteImage)
			paletteImage->drop();
#endif
	}
	else
	{
		palette = DefaultPaletteQ2;
	}

	SWALHeader header;

	file->seek(0);
	if (file->read(&header, sizeof(SWALHeader)) != sizeof(SWALHeader) )
		return 0;

	if (file->getSize() < header.MipmapOffset[0])
		return 0;
	file->seek(header.MipmapOffset[0]);

	// read image

	const u32 imageSize = header.ImageHeight * header.ImageWidth;
	if (file->getSize() < (long)(imageSize + header.MipmapOffset[0]))
		return 0;

	u8* data = new u8[imageSize];
	file->read(data, imageSize);

	IImage* image = 0;

	image = new CImage(ECF_A1R5G5B5,
		core::dimension2d<u32>(header.ImageWidth, header.ImageHeight));

	// I wrote an 8 to 32 converter, but this works with released Irrlicht code.
	CColorConverter::convert8BitTo16Bit(data,
		(s16*)image->lock(), header.ImageWidth, header.ImageHeight, palette);
	image->unlock();

	delete [] data;

	return image;
}


IImageLoader* createImageLoaderWAL()
{
	return new irr::video::CImageLoaderWAL();
}

#endif


// Palette quake2 colormap.h, 768 byte, last is transparent
static const u32 colormap_h[256] = {
	0xFF000000,0xFF0F0F0F,0xFF1F1F1F,0xFF2F2F2F,0xFF3F3F3F,0xFF4B4B4B,0xFF5B5B5B,0xFF6B6B6B,
	0xFF7B7B7B,0xFF8B8B8B,0xFF9B9B9B,0xFFABABAB,0xFFBBBBBB,0xFFCBCBCB,0xFFDBDBDB,0xFFEBEBEB,
	0xFF0F0B07,0xFF170F0B,0xFF1F170B,0xFF271B0F,0xFF2F2313,0xFF372B17,0xFF3F2F17,0xFF4B371B,
	0xFF533B1B,0xFF5B431F,0xFF634B1F,0xFF6B531F,0xFF73571F,0xFF7B5F23,0xFF836723,0xFF8F6F23,
	0xFF0B0B0F,0xFF13131B,0xFF1B1B27,0xFF272733,0xFF2F2F3F,0xFF37374B,0xFF3F3F57,0xFF474767,
	0xFF4F4F73,0xFF5B5B7F,0xFF63638B,0xFF6B6B97,0xFF7373A3,0xFF7B7BAF,0xFF8383BB,0xFF8B8BCB,
	0xFF000000,0xFF070700,0xFF0B0B00,0xFF131300,0xFF1B1B00,0xFF232300,0xFF2B2B07,0xFF2F2F07,
	0xFF373707,0xFF3F3F07,0xFF474707,0xFF4B4B0B,0xFF53530B,0xFF5B5B0B,0xFF63630B,0xFF6B6B0F,
	0xFF070000,0xFF0F0000,0xFF170000,0xFF1F0000,0xFF270000,0xFF2F0000,0xFF370000,0xFF3F0000,
	0xFF470000,0xFF4F0000,0xFF570000,0xFF5F0000,0xFF670000,0xFF6F0000,0xFF770000,0xFF7F0000,
	0xFF131300,0xFF1B1B00,0xFF232300,0xFF2F2B00,0xFF372F00,0xFF433700,0xFF4B3B07,0xFF574307,
	0xFF5F4707,0xFF6B4B0B,0xFF77530F,0xFF835713,0xFF8B5B13,0xFF975F1B,0xFFA3631F,0xFFAF6723,
	0xFF231307,0xFF2F170B,0xFF3B1F0F,0xFF4B2313,0xFF572B17,0xFF632F1F,0xFF733723,0xFF7F3B2B,
	0xFF8F4333,0xFF9F4F33,0xFFAF632F,0xFFBF772F,0xFFCF8F2B,0xFFDFAB27,0xFFEFCB1F,0xFFFFF31B,
	0xFF0B0700,0xFF1B1300,0xFF2B230F,0xFF372B13,0xFF47331B,0xFF533723,0xFF633F2B,0xFF6F4733,
	0xFF7F533F,0xFF8B5F47,0xFF9B6B53,0xFFA77B5F,0xFFB7876B,0xFFC3937B,0xFFD3A38B,0xFFE3B397,
	0xFFAB8BA3,0xFF9F7F97,0xFF937387,0xFF8B677B,0xFF7F5B6F,0xFF775363,0xFF6B4B57,0xFF5F3F4B,
	0xFF573743,0xFF4B2F37,0xFF43272F,0xFF371F23,0xFF2B171B,0xFF231313,0xFF170B0B,0xFF0F0707,
	0xFFBB739F,0xFFAF6B8F,0xFFA35F83,0xFF975777,0xFF8B4F6B,0xFF7F4B5F,0xFF734353,0xFF6B3B4B,
	0xFF5F333F,0xFF532B37,0xFF47232B,0xFF3B1F23,0xFF2F171B,0xFF231313,0xFF170B0B,0xFF0F0707,
	0xFFDBC3BB,0xFFCBB3A7,0xFFBFA39B,0xFFAF978B,0xFFA3877B,0xFF977B6F,0xFF876F5F,0xFF7B6353,
	0xFF6B5747,0xFF5F4B3B,0xFF533F33,0xFF433327,0xFF372B1F,0xFF271F17,0xFF1B130F,0xFF0F0B07,
	0xFF6F837B,0xFF677B6F,0xFF5F7367,0xFF576B5F,0xFF4F6357,0xFF475B4F,0xFF3F5347,0xFF374B3F,
	0xFF2F4337,0xFF2B3B2F,0xFF233327,0xFF1F2B1F,0xFF172317,0xFF0F1B13,0xFF0B130B,0xFF070B07,
	0xFFFFF31B,0xFFEFDF17,0xFFDBCB13,0xFFCBB70F,0xFFBBA70F,0xFFAB970B,0xFF9B8307,0xFF8B7307,
	0xFF7B6307,0xFF6B5300,0xFF5B4700,0xFF4B3700,0xFF3B2B00,0xFF2B1F00,0xFF1B0F00,0xFF0B0700,
	0xFF0000FF,0xFF0B0BEF,0xFF1313DF,0xFF1B1BCF,0xFF2323BF,0xFF2B2BAF,0xFF2F2F9F,0xFF2F2F8F,
	0xFF2F2F7F,0xFF2F2F6F,0xFF2F2F5F,0xFF2B2B4F,0xFF23233F,0xFF1B1B2F,0xFF13131F,0xFF0B0B0F,
	0xFF2B0000,0xFF3B0000,0xFF4B0700,0xFF5F0700,0xFF6F0F00,0xFF7F1707,0xFF931F07,0xFFA3270B,
	0xFFB7330F,0xFFC34B1B,0xFFCF632B,0xFFDB7F3B,0xFFE3974F,0xFFE7AB5F,0xFFEFBF77,0xFFF7D38B,
	0xFFA77B3B,0xFFB79B37,0xFFC7C337,0xFFE7E357,0xFF7FBFFF,0xFFABE7FF,0xFFD7FFFF,0xFF670000,
	0xFF8B0000,0xFFB30000,0xFFD70000,0xFFFF0000,0xFFFFF393,0xFFFFF7C7,0xFFFFFFFF,0x009F5B53
};

// Palette quake2 demo pics/colormap.pcx, last is transparent
static const u32 colormap_pcx[256] = {
	0xFF000000,0xFF0F0F0F,0xFF1F1F1F,0xFF2F2F2F,0xFF3F3F3F,0xFF4B4B4B,0xFF5B5B5B,0xFF6B6B6B,
	0xFF7B7B7B,0xFF8B8B8B,0xFF9B9B9B,0xFFABABAB,0xFFBBBBBB,0xFFCBCBCB,0xFFDBDBDB,0xFFEBEBEB,
	0xFF634B23,0xFF5B431F,0xFF533F1F,0xFF4F3B1B,0xFF47371B,0xFF3F2F17,0xFF3B2B17,0xFF332713,
	0xFF2F2313,0xFF2B1F13,0xFF271B0F,0xFF23170F,0xFF1B130B,0xFF170F0B,0xFF130F07,0xFF0F0B07,
	0xFF5F5F6F,0xFF5B5B67,0xFF5B535F,0xFF574F5B,0xFF534B53,0xFF4F474B,0xFF473F43,0xFF3F3B3B,
	0xFF3B3737,0xFF332F2F,0xFF2F2B2B,0xFF272727,0xFF232323,0xFF1B1B1B,0xFF171717,0xFF131313,
	0xFF8F7753,0xFF7B6343,0xFF735B3B,0xFF674F2F,0xFFCF974B,0xFFA77B3B,0xFF8B672F,0xFF6F5327,
	0xFFEB9F27,0xFFCB8B23,0xFFAF771F,0xFF93631B,0xFF774F17,0xFF5B3B0F,0xFF3F270B,0xFF231707,
	0xFFA73B2B,0xFF9F2F23,0xFF972B1B,0xFF8B2713,0xFF7F1F0F,0xFF73170B,0xFF671707,0xFF571300,
	0xFF4B0F00,0xFF430F00,0xFF3B0F00,0xFF330B00,0xFF2B0B00,0xFF230B00,0xFF1B0700,0xFF130700,
	0xFF7B5F4B,0xFF735743,0xFF6B533F,0xFF674F3B,0xFF5F4737,0xFF574333,0xFF533F2F,0xFF4B372B,
	0xFF433327,0xFF3F2F23,0xFF37271B,0xFF2F2317,0xFF271B13,0xFF1F170F,0xFF170F0B,0xFF0F0B07,
	0xFF6F3B17,0xFF5F3717,0xFF532F17,0xFF432B17,0xFF372313,0xFF271B0F,0xFF1B130B,0xFF0F0B07,
	0xFFB35B4F,0xFFBF7B6F,0xFFCB9B93,0xFFD7BBB7,0xFFCBD7DF,0xFFB3C7D3,0xFF9FB7C3,0xFF87A7B7,
	0xFF7397A7,0xFF5B879B,0xFF47778B,0xFF2F677F,0xFF17536F,0xFF134B67,0xFF0F435B,0xFF0B3F53,
	0xFF07374B,0xFF072F3F,0xFF072733,0xFF001F2B,0xFF00171F,0xFF000F13,0xFF00070B,0xFF000000,
	0xFF8B5757,0xFF834F4F,0xFF7B4747,0xFF734343,0xFF6B3B3B,0xFF633333,0xFF5B2F2F,0xFF572B2B,
	0xFF4B2323,0xFF3F1F1F,0xFF331B1B,0xFF2B1313,0xFF1F0F0F,0xFF130B0B,0xFF0B0707,0xFF000000,
	0xFF979F7B,0xFF8F9773,0xFF878B6B,0xFF7F8363,0xFF777B5F,0xFF737357,0xFF6B6B4F,0xFF636347,
	0xFF5B5B43,0xFF4F4F3B,0xFF434333,0xFF37372B,0xFF2F2F23,0xFF23231B,0xFF171713,0xFF0F0F0B,
	0xFF9F4B3F,0xFF934337,0xFF8B3B2F,0xFF7F3727,0xFF772F23,0xFF6B2B1B,0xFF632317,0xFF571F13,
	0xFF4F1B0F,0xFF43170B,0xFF37130B,0xFF2B0F07,0xFF1F0B07,0xFF170700,0xFF0B0000,0xFF000000,
	0xFF777BCF,0xFF6F73C3,0xFF676BB7,0xFF6363A7,0xFF5B5B9B,0xFF53578F,0xFF4B4F7F,0xFF474773,
	0xFF3F3F67,0xFF373757,0xFF2F2F4B,0xFF27273F,0xFF231F2F,0xFF1B1723,0xFF130F17,0xFF0B0707,
	0xFF9BAB7B,0xFF8F9F6F,0xFF879763,0xFF7B8B57,0xFF73834B,0xFF677743,0xFF5F6F3B,0xFF576733,
	0xFF4B5B27,0xFF3F4F1B,0xFF374313,0xFF2F3B0B,0xFF232F07,0xFF1B2300,0xFF131700,0xFF0B0F00,
	0xFF00FF00,0xFF23E70F,0xFF3FD31B,0xFF53BB27,0xFF5FA72F,0xFF5F8F33,0xFF5F7B33,0xFFFFFFFF,
	0xFFFFFFD3,0xFFFFFFA7,0xFFFFFF7F,0xFFFFFF53,0xFFFFFF27,0xFFFFEB1F,0xFFFFD717,0xFFFFBF0F,
	0xFFFFAB07,0xFFFF9300,0xFFEF7F00,0xFFE36B00,0xFFD35700,0xFFC74700,0xFFB73B00,0xFFAB2B00,
	0xFF9B1F00,0xFF8F1700,0xFF7F0F00,0xFF730700,0xFF5F0000,0xFF470000,0xFF2F0000,0xFF1B0000,
	0xFFEF0000,0xFF3737FF,0xFFFF0000,0xFF0000FF,0xFF2B2B23,0xFF1B1B17,0xFF13130F,0xFFEB977F,
	0xFFC37353,0xFF9F5733,0xFF7B3F1B,0xFFEBD3C7,0xFFC7AB9B,0xFFA78B77,0xFF876B57,0x009F5B53
};

#if 0
// palette halflife gfx/palette.lmp only 1 entry difference.. transparent = 0,0,255
static const u32 palette_lmp[256] = {
	0xFF000000,0xFF0F0F0F,0xFF1F1F1F,0xFF2F2F2F,0xFF3F3F3F,0xFF4B4B4B,0xFF5B5B5B,0xFF6B6B6B,
	0xFF7B7B7B,0xFF8B8B8B,0xFF9B9B9B,0xFFABABAB,0xFFBBBBBB,0xFFCBCBCB,0xFFDBDBDB,0xFFEBEBEB,
	0xFF0F0B07,0xFF170F0B,0xFF1F170B,0xFF271B0F,0xFF2F2313,0xFF372B17,0xFF3F2F17,0xFF4B371B,
	0xFF533B1B,0xFF5B431F,0xFF634B1F,0xFF6B531F,0xFF73571F,0xFF7B5F23,0xFF836723,0xFF8F6F23,
	0xFF0B0B0F,0xFF13131B,0xFF1B1B27,0xFF272733,0xFF2F2F3F,0xFF37374B,0xFF3F3F57,0xFF474767,
	0xFF4F4F73,0xFF5B5B7F,0xFF63638B,0xFF6B6B97,0xFF7373A3,0xFF7B7BAF,0xFF8383BB,0xFF8B8BCB,
	0xFF000000,0xFF070700,0xFF0B0B00,0xFF131300,0xFF1B1B00,0xFF232300,0xFF2B2B07,0xFF2F2F07,
	0xFF373707,0xFF3F3F07,0xFF474707,0xFF4B4B0B,0xFF53530B,0xFF5B5B0B,0xFF63630B,0xFF6B6B0F,
	0xFF070000,0xFF0F0000,0xFF170000,0xFF1F0000,0xFF270000,0xFF2F0000,0xFF370000,0xFF3F0000,
	0xFF470000,0xFF4F0000,0xFF570000,0xFF5F0000,0xFF670000,0xFF6F0000,0xFF770000,0xFF7F0000,
	0xFF131300,0xFF1B1B00,0xFF232300,0xFF2F2B00,0xFF372F00,0xFF433700,0xFF4B3B07,0xFF574307,
	0xFF5F4707,0xFF6B4B0B,0xFF77530F,0xFF835713,0xFF8B5B13,0xFF975F1B,0xFFA3631F,0xFFAF6723,
	0xFF231307,0xFF2F170B,0xFF3B1F0F,0xFF4B2313,0xFF572B17,0xFF632F1F,0xFF733723,0xFF7F3B2B,
	0xFF8F4333,0xFF9F4F33,0xFFAF632F,0xFFBF772F,0xFFCF8F2B,0xFFDFAB27,0xFFEFCB1F,0xFFFFF31B,
	0xFF0B0700,0xFF1B1300,0xFF2B230F,0xFF372B13,0xFF47331B,0xFF533723,0xFF633F2B,0xFF6F4733,
	0xFF7F533F,0xFF8B5F47,0xFF9B6B53,0xFFA77B5F,0xFFB7876B,0xFFC3937B,0xFFD3A38B,0xFFE3B397,
	0xFFAB8BA3,0xFF9F7F97,0xFF937387,0xFF8B677B,0xFF7F5B6F,0xFF775363,0xFF6B4B57,0xFF5F3F4B,
	0xFF573743,0xFF4B2F37,0xFF43272F,0xFF371F23,0xFF2B171B,0xFF231313,0xFF170B0B,0xFF0F0707,
	0xFFBB739F,0xFFAF6B8F,0xFFA35F83,0xFF975777,0xFF8B4F6B,0xFF7F4B5F,0xFF734353,0xFF6B3B4B,
	0xFF5F333F,0xFF532B37,0xFF47232B,0xFF3B1F23,0xFF2F171B,0xFF231313,0xFF170B0B,0xFF0F0707,
	0xFFDBC3BB,0xFFCBB3A7,0xFFBFA39B,0xFFAF978B,0xFFA3877B,0xFF977B6F,0xFF876F5F,0xFF7B6353,
	0xFF6B5747,0xFF5F4B3B,0xFF533F33,0xFF433327,0xFF372B1F,0xFF271F17,0xFF1B130F,0xFF0F0B07,
	0xFF6F837B,0xFF677B6F,0xFF5F7367,0xFF576B5F,0xFF4F6357,0xFF475B4F,0xFF3F5347,0xFF374B3F,
	0xFF2F4337,0xFF2B3B2F,0xFF233327,0xFF1F2B1F,0xFF172317,0xFF0F1B13,0xFF0B130B,0xFF070B07,
	0xFFFFF31B,0xFFEFDF17,0xFFDBCB13,0xFFCBB70F,0xFFBBA70F,0xFFAB970B,0xFF9B8307,0xFF8B7307,
	0xFF7B6307,0xFF6B5300,0xFF5B4700,0xFF4B3700,0xFF3B2B00,0xFF2B1F00,0xFF1B0F00,0xFF0B0700,
	0xFF0000FF,0xFF0B0BEF,0xFF1313DF,0xFF1B1BCF,0xFF2323BF,0xFF2B2BAF,0xFF2F2F9F,0xFF2F2F8F,
	0xFF2F2F7F,0xFF2F2F6F,0xFF2F2F5F,0xFF2B2B4F,0xFF23233F,0xFF1B1B2F,0xFF13131F,0xFF0B0B0F,
	0xFF2B0000,0xFF3B0000,0xFF4B0700,0xFF5F0700,0xFF6F0F00,0xFF7F1707,0xFF931F07,0xFFA3270B,
	0xFFB7330F,0xFFC34B1B,0xFFCF632B,0xFFDB7F3B,0xFFE3974F,0xFFE7AB5F,0xFFEFBF77,0xFFF7D38B,
	0xFFA77B3B,0xFFB79B37,0xFFC7C337,0xFFE7E357,0xFF00FF00,0xFFABE7FF,0xFFD7FFFF,0xFF670000,
	0xFF8B0000,0xFFB30000,0xFFD70000,0xFFFF0000,0xFFFFF393,0xFFFFF7C7,0xFFFFFFFF,0xFF9F5B53
};

#endif

bool CImageLoaderLMP::isALoadableFileExtension(const io::path& filename) const
{
	return core::hasFileExtension ( filename, "lmp" );
}


bool CImageLoaderLMP::isALoadableFileFormat(irr::io::IReadFile* file) const
{
	return false;
}

/*!
	Quake1, Quake2, Hallife lmp texture
*/
IImage* CImageLoaderLMP::loadImage(irr::io::IReadFile* file) const
{
	SLMPHeader header;

	file->seek(0);
	file->read(&header, sizeof(header));

	// maybe palette file
	u32 rawtexsize = header.width * header.height;
	if ( rawtexsize + sizeof ( header ) != (u32)file->getSize() )
		return 0;

	u8 *rawtex = new u8 [ rawtexsize ];

	file->read(rawtex, rawtexsize);

	IImage* image = new CImage(ECF_A8R8G8B8, core::dimension2d<u32>(header.width, header.height));

	CColorConverter::convert8BitTo32Bit(rawtex, (u8*)image->lock(), header.width, header.height, (u8*) colormap_h, 0, false);
	image->unlock();

	delete [] rawtex;

	return image;
}


/*!
	Halflife
*/
bool CImageLoaderWAL2::isALoadableFileExtension(const io::path& filename) const
{
	// embedded in Wad(WAD3 format). originally it has no extension
	return core::hasFileExtension ( filename, "wal2" );
}


bool CImageLoaderWAL2::isALoadableFileFormat(irr::io::IReadFile* file) const
{
	return false;
}

/*
	Halflite Texture WAD
*/
IImage* CImageLoaderWAL2::loadImage(irr::io::IReadFile* file) const
{
	miptex_halflife header;

	file->seek(0);
	file->read(&header, sizeof(header));

#ifdef __BIG_ENDIAN__
	header.width = os::Byteswap::byteswap(header.width);
	header.height = os::Byteswap::byteswap(header.height);
#endif

	// palette
	//u32 paletteofs = header.mipmap[0] + ((rawtexsize * 85) >> 6) + 2;
	u32 *pal = new u32 [ 192 + 256 ];
	u8 *s = (u8*) pal;

	file->seek ( file->getSize() - 768 - 2 );
	file->read ( s, 768 );
	u32 i;

	for ( i = 0; i < 256; ++i, s+= 3 )
	{
		pal [ 192 + i ] = 0xFF000000 | s[0] << 16 | s[1] << 8 | s[2];
	}

	ECOLOR_FORMAT format = ECF_R8G8B8;

	// transparency in filename;-) funny. rgb:0x0000FF is colorkey
	if ( file->getFileName().findFirst ( '{' ) >= 0 )
	{
		format = ECF_A8R8G8B8;
		pal [ 192 + 255 ] &= 0x00FFFFFF;
	}

	u32 rawtexsize = header.width * header.height;


	u8 *rawtex = new u8 [ rawtexsize ];

	file->seek ( header.mipmap[0] );
	file->read(rawtex, rawtexsize);

	IImage* image = new CImage(format, core::dimension2d<u32>(header.width, header.height));

	switch ( format )
	{
	case ECF_R8G8B8:
		CColorConverter::convert8BitTo24Bit(rawtex, (u8*)image->lock(), header.width, header.height, (u8*) pal + 768, 0, false);
		break;
	case ECF_A8R8G8B8:
		CColorConverter::convert8BitTo32Bit(rawtex, (u8*)image->lock(), header.width, header.height, (u8*) pal + 768, 0, false);
		break;
	}

	image->unlock();

	delete [] rawtex;
	delete [] pal;

	return image;
}

bool CImageLoaderWAL::isALoadableFileExtension(const io::path& filename) const
{
	return core::hasFileExtension ( filename, "wal" );
}


bool CImageLoaderWAL::isALoadableFileFormat(irr::io::IReadFile* file) const
{
	return false;
}


/*!
	quake2
*/
IImage* CImageLoaderWAL::loadImage(irr::io::IReadFile* file) const
{
	miptex_quake2 header;

	file->seek(0);
	file->read(&header, sizeof(header));

#ifdef __BIG_ENDIAN__
	header.width = os::Byteswap::byteswap(header.width);
	header.height = os::Byteswap::byteswap(header.height);
#endif

	u32 rawtexsize = header.width * header.height;

	u8 *rawtex = new u8 [ rawtexsize ];

	file->seek ( header.mipmap[0] );
	file->read(rawtex, rawtexsize);

	IImage* image = new CImage(ECF_A8R8G8B8, core::dimension2d<u32>(header.width, header.height));

	CColorConverter::convert8BitTo32Bit(rawtex, (u8*)image->lock(), header.width, header.height, (u8*) colormap_pcx, 0, false);
	image->unlock();

	delete [] rawtex;

	return image;
}



IImageLoader* createImageLoaderHalfLife()
{
	return new irr::video::CImageLoaderWAL2();
}

IImageLoader* createImageLoaderWAL()
{
	return new irr::video::CImageLoaderWAL();
}

IImageLoader* createImageLoaderLMP()
{
	return new irr::video::CImageLoaderLMP();
}

}
}


