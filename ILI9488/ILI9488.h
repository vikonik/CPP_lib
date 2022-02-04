/*
 * ILI9488.h
 *
 *  Created on: Apr 29, 2021
 *      Author: hydra
 */

#ifndef ILI9488_H_
#define ILI9488_H_
#include "MDR1986VE1T.h"                // Device header
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT

#include <math.h>
#include "port.h"
#include "delay.h"
#include "DefaultFonts.h"
#include "GraphicObj.h"

#define PORTRAIT 0
#define LANDSCAPE 1

#define ILI9488_TFTWIDTH  480
#define ILI9488_TFTHEIGHT 320

#define ILI9488_NOP     0x00
#define ILI9488_SWRESET 0x01
#define ILI9488_RDDID   0x04
#define ILI9488_RDDST   0x09

#define ILI9488_SLPIN   0x10
#define ILI9488_SLPOUT  0x11
#define ILI9488_PTLON   0x12
#define ILI9488_NORON   0x13

#define ILI9488_RDMODE  0x0A
#define ILI9488_RDMADCTL  0x0B
#define ILI9488_RDPIXFMT  0x0C
#define ILI9488_RDIMGFMT  0x0D
#define ILI9488_RDSELFDIAG  0x0F

#define ILI9488_INVOFF  0x20
#define ILI9488_INVON   0x21
#define ILI9488_GAMMASET 0x26
#define ILI9488_DISPOFF 0x28
#define ILI9488_DISPON  0x29

#define ILI9488_CASET   0x2A
#define ILI9488_PASET   0x2B
#define ILI9488_RAMWR   0x2C
#define ILI9488_RAMRD   0x2E

#define ILI9488_PTLAR   0x30
#define ILI9488_MADCTL  0x36
#define ILI9488_PIXFMT  0x3A

#define ILI9488_FRMCTR1 0xB1
#define ILI9488_FRMCTR2 0xB2
#define ILI9488_FRMCTR3 0xB3
#define ILI9488_INVCTR  0xB4
#define ILI9488_DFUNCTR 0xB6

#define ILI9488_PWCTR1  0xC0
#define ILI9488_PWCTR2  0xC1
#define ILI9488_PWCTR3  0xC2
#define ILI9488_PWCTR4  0xC3
#define ILI9488_PWCTR5  0xC4
#define ILI9488_VMCTR1  0xC5
#define ILI9488_VMCTR2  0xC7

#define ILI9488_RDID1   0xDA
#define ILI9488_RDID2   0xDB
#define ILI9488_RDID3   0xDC
#define ILI9488_RDID4   0xDD

#define ILI9488_GMCTRP1 0xE0
#define ILI9488_GMCTRN1 0xE1
/*
#define ILI9488_PWCTR6  0xFC

*/

// Color definitions
#define ILI9488_BLACK      			0x0000      /*   0,   0,   0 */
#define ILI9488_NAVY						0x000F      /*   0,   0, 128 */
#define ILI9488_DARKGREEN   		0x03E0      /*   0, 128,   0 */
#define ILI9488_DARKCYAN    		0x03EF      /*   0, 128, 128 */
#define ILI9488_MAROON      		0x7800      /* 128,   0,   0 */
#define ILI9488_PURPLE      		0x780F      /* 128,   0, 128 */
#define ILI9488_OLIVE       		0x7BE0      /* 128, 128,   0 */
#define ILI9488_LIGHTGREY   		0xC618      /* 192, 192, 192 */
#define ILI9488_DARKGREY    		0x7BEF      /* 128, 128, 128 */
#define ILI9488_BLUE        		0x001F      /*   0,   0, 255 */
#define ILI9488_GREEN       		0x07E0      /*   0, 255,   0 */
#define ILI9488_CYAN        		0x07FF      /*   0, 255, 255 */
#define ILI9488_RED         		0xF800      /* 255,   0,   0 */
#define ILI9488_MAGENTA     		0xF81F      /* 255,   0, 255 */
#define ILI9488_YELLOW      		0xFFE0      /* 255, 255,   0 */
#define ILI9488_WHITE       		0xFFFF      /* 255, 255, 255 */
#define ILI9488_ORANGE      		0xFD20      /* 255, 165,   0 */
#define ILI9488_GREENYELLOW 		0xAFE5      /* 173, 255,  47 */
#define ILI9488_PINK        		0xF81F

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

//*********************************
// COLORS
//*********************************
// VGA color palette
#define VGA_BLACK		0x0000
#define VGA_WHITE		0xFFFF
#define VGA_RED			0xF800
#define VGA_GREEN		0x0400
#define VGA_BLUE		0x001F
#define VGA_SILVER		0xC618
#define VGA_GRAY		0x8410
#define VGA_MAROON		0x8000
#define VGA_YELLOW		0xFFE0
#define VGA_OLIVE		0x8400
#define VGA_LIME		0x07E0
#define VGA_AQUA		0x07FF
#define VGA_TEAL		0x0410
#define VGA_NAVY		0x0010
#define VGA_FUCHSIA		0xF81F
#define VGA_PURPLE		0x8010
#define VGA_TRANSPARENT	0xFFFFFFFF

#define FON_COLOR 0xA7DF
#define _swap_int16_t(a, b) \
	{int16_t t = a; \
	a = b;   \
	b = t; \
  }

#define SEND_CMD 					pTFT_RS_Y->setLow()
#define SEND_DATA 				pTFT_RS_Y->setHigh()	
#define	SELECT_DISPLAY		pTFT_CS_X->setLow()
#define	DESELECT_DISPLAY	pTFT_CS_X->setHigh()	
/* GENERAL CONFIGURATIONS */

#define _DEGUG_MODE 1
#define SINGLE_IO_MODE 1
#define PORT_MASK (uint8_t)0x7F8
	#define fontbyte(x) cfont.font[x]  
	struct _current_font
{
	const uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
};
	
class ILI9488 : public PortMapIO, public DELAY
{
	public:
		ILI9488 ();
		//ILI9488(PortmapIO CS, PortmapIO DC, PortmapIO RST,PortmapSPI spi,PortmapUART uart);
//		ILI9488(PortmapIO *CS, PortmapIO *DC, PortmapIO *RST,PortmapSPI *spi);
//		ILI9488(PortmapIO *CS, PortmapIO *DC, PortmapIO *RST,PortmapIO *SCK, PortmapIO *MOSI);
		ILI9488(PortMapIO *bit_0, PortMapIO *bit_1,PortMapIO *bit_2,PortMapIO *bit_3,PortMapIO *bit_4,
						PortMapIO *bit_5,PortMapIO *bit_6,PortMapIO *bit_7,PortMapIO *pTFT_RST,PortMapIO *pTFT_CS_X,
						PortMapIO *pTFT_RS_Y,PortMapIO *pTFT_RD,PortMapIO *pTFT_WR, MDR_PORT_TypeDef *dataPort);
void testPin();
		void begin(void);
void setOrientation(uint8_t orientation);
void readPixelFormat(void);
		void hardReset(void);
    void clrXY();
void setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

		void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
		void setScrollArea(uint16_t topFixedArea, uint16_t bottomFixedArea);
		void scroll(uint16_t pixels);
		void setColor(uint16_t color);	
		void setColor(uint8_t r,uint8_t g, uint8_t b );	
    uint16_t getColor(void){return this->color565;}
    void setBackColor(uint8_t r, uint8_t g, uint8_t b);
    void setBackColor(uint32_t color);
		void pushColor(uint16_t color);
		void pushColors(uint16_t *data, uint8_t len, uint8_t first);
		void drawImage(const uint8_t* img, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void drawImageScale(uint8_t scale, const uint8_t* img, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

		void fillScreen(uint16_t color);
    void setPixel();
    void setPixel(uint16_t color);
		void drawPixel(int16_t x, int16_t y);	//Для вывода предустановленного цвета
		void drawPixel(int16_t x, int16_t y, uint16_t color);
		void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
		void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
		void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,uint16_t color);
		void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,uint16_t color);
		void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
		void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
		void drawCircle(int x, int y, int radius);
		void fillCircle(int x, int y, int radius);
		void setRotation(uint8_t r);
		void invertDisplay(uint8_t  i);
		uint16_t setColor565(uint8_t r, uint8_t g, uint8_t b);
		void spiwrite(uint8_t data);
		void writecommand(uint8_t c);
		void writeColor565(void);
		void write16BitColor(uint16_t color);
		void writedata(uint8_t d);
uint8_t readData(void);//чтение дисплея(не написано)
		void testLines(uint8_t color);
		void sendasIO(uint8_t *d);


void setFont(const uint8_t* font);
const uint8_t* getFont();
uint8_t getFontXsize();
uint8_t getFontYsize();
void	print(char *st, int size, int x, int y, int deg=0);
void	_print(char *st, int x, int y, int deg=0);

    void printChar(uint8_t c, int x, int y);
void printChar_x2(uint8_t c, int x, int y);

uint16_t getBackColor(){return backColor565;}

		int16_t _width;
		int16_t _height;
		_current_font	cfont;
	private:
		uint8_t  tabcolor;
		uint8_t mySPCR;
		MDR_PORT_TypeDef *dataPort;
		PortMapIO *bit_0; 
		PortMapIO *bit_1;
		PortMapIO *bit_2;
		PortMapIO *bit_3;
		PortMapIO *bit_4;
		PortMapIO *bit_5;
		PortMapIO *bit_6;
		PortMapIO *bit_7;
		PortMapIO *pTFT_RST;//Сброс
		PortMapIO *pTFT_CS_X;//Выбор устройства
		PortMapIO *pTFT_RS_Y;//Команда/данные
		PortMapIO *pTFT_RD;//Записать
		PortMapIO *pTFT_WR;//Прочитать
	
		//PortmapUART _uart;
		//Adafruit fields
		int16_t WIDTH;
		int16_t HEIGHT;

		int16_t cursor_x;
		int16_t cursor_y;
		uint16_t textcolor;
		uint16_t textbgcolor;
		uint8_t textsize_x;
		uint8_t textsize_y;
		uint8_t rotation;
		 

		 uint8_t colorH;
		 uint8_t colorL;
		 uint16_t color565;

		 uint16_t backColor565;
		 uint8_t backColorH;
		 uint8_t backColorL;
     bool _transparent;

		 uint16_t			disp_x_size, disp_y_size;
     uint8_t			orient;
     uint8_t ch;

};

#endif /* ILI9488_H_ */
