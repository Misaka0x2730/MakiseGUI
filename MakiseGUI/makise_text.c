#include "makise_text.h"

static void _makise_draw_char(MakiseBuffer *b, uint16_t ind, uint16_t x, uint16_t y, const MakiseFont *font, uint32_t c, uint16_t width)
{
    uint32_t bitCounter, rawIndex, colIndex;
    const uint8_t * ptrByte;
    
    ptrByte = &font->table[font->char_index[ind]];
    for(rawIndex = 0; rawIndex < font->height; rawIndex++)
    {
	bitCounter = 0;
	for(colIndex = 0; colIndex < width; colIndex++)
	{

	    if (bitCounter > 7)
	    {
		bitCounter = 0;
		ptrByte++;
	    }
	    if(*ptrByte & (1<<bitCounter))
	    {
		makise_pset(b, x+colIndex - 1, y+rawIndex - 1, c);
	    }
	    bitCounter++;
	}
	ptrByte++;
    }
}

void makise_d_char(MakiseBuffer *b, uint16_t ch, uint16_t x, uint16_t y, const MakiseFont *font, uint32_t c)
{
    uint32_t width;

    ch = (uint8_t)ch - font->offset;
    
    // Symbol width
    if (ch > font->num_char) ch = 0;
    width = font->width ? font->width : font->char_width[ch];
	
    // Draw Char
    _makise_draw_char(b, ch, x, y, font, c, width);
}
void makise_d_string(MakiseBuffer *b, char *s, uint16_t x, uint16_t y, const MakiseFont *font, uint32_t c)
{
    uint32_t width, l = strlen(s) , i = 0;
    uint32_t ch, xt = x, yt = y;

    while (i < l) {
	ch = s[i];
	ch = (uint8_t)ch - font->offset;

	// Symbol width
	if (ch > font->num_char) ch = 0;
	width = font->width ? font->width : font->char_width[ch];
	
	// Draw Char
	_makise_draw_char(b, ch, xt, yt, font, c, width);
	xt += width + font->space_char;
	i++;
    }
}