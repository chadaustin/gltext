lib_LTLIBRARIES = libgltext.la

include_HEADERS = \
	gltext.h

libgltext_la_SOURCES = \
	gltext.cpp \
	AbstractRenderer.cpp \
	AbstractRenderer.h \
	BitmapRenderer.cpp \
	BitmapRenderer.h \
	FTFont.cpp \
	FTFont.h \
	FTGlyph.cpp \
	FTGlyph.h \
	GLGlyph.h \
	GLPixelGlyph.cpp \
	GLPixelGlyph.h \
	GLTextureGlyph.cpp \
	GLTextureGlyph.h \
	GlyphCache.h \
	OpenGL.h \
	PixmapRenderer.cpp \
	PixmapRenderer.h \
	TextureRenderer.cpp \
	TextureRenderer.h

libgltext_la_LDFLAGS = \
	-release $(VERSION)

ligltext_la_CFLAGS = \
	-Wall -Wno-non-virtual-dtor
