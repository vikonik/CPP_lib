/*
 * ILI9488.cpp
 *
 *  Created on: Apr 29, 2021
 *      Author: hydra
 */

#include "ILI9488.h"
#include "delay.h"
#include "math.h"

/*ILI9488::ILI9488(PortmapIO CS, PortmapIO DC, PortmapIO RST,PortmapSPI spi,PortmapUART uart)
{
	_cs=CS;
	_dc=DC;
	_rst = RST;
	_spi=spi;
	_uart=uart;

}*/
ILI9488::ILI9488(PortMapIO *bit_0, PortMapIO *bit_1,PortMapIO *bit_2,PortMapIO *bit_3,PortMapIO *bit_4,
						PortMapIO *bit_5,PortMapIO *bit_6,PortMapIO *bit_7,
						PortMapIO *pTFT_RST,PortMapIO *pTFT_CS_X,
						PortMapIO *pTFT_RS_Y,PortMapIO *pTFT_RD,PortMapIO *pTFT_WR)
						:	 bit_0(bit_0), bit_1(bit_1), bit_2(bit_2), bit_3(bit_3), bit_4(bit_4),
						 bit_5(bit_5), bit_6(bit_6), bit_7(bit_7), pTFT_RST(pTFT_RST),pTFT_CS_X(pTFT_CS_X),
						 pTFT_RS_Y(pTFT_RS_Y), pTFT_RD(pTFT_RD),pTFT_WR(pTFT_WR)			
						{
pTFT_RST->setPinAsOutput();
pTFT_CS_X->setPinAsOutput();
pTFT_RS_Y->setPinAsOutput();
pTFT_RD->setPinAsOutput();
pTFT_WR->setPinAsOutput();	
							
pTFT_RST->setHigh();
pTFT_CS_X->setHigh();
pTFT_RS_Y->setHigh();
pTFT_RD->setHigh();
pTFT_WR->setHigh();
							
			hardReset();
							
bit_0->setPinAsOutput();
bit_1->setPinAsOutput();
bit_2->setPinAsOutput();
bit_3->setPinAsOutput();
bit_4->setPinAsOutput();
bit_5->setPinAsOutput();
bit_6->setPinAsOutput();
bit_7->setPinAsOutput();							


bit_0->setHigh();
bit_1->setHigh();
bit_2->setHigh();
bit_3->setHigh();
bit_4->setHigh();
bit_5->setHigh();
bit_6->setHigh();
bit_7->setHigh();
						
};
		

				
template <class T> void swap (T& a, T& b)
{
T c(a); a=b; b=c;
}					


/**/
void ILI9488::begin(void)
{

	_width=ILI9488_TFTWIDTH;
	_height=ILI9488_TFTHEIGHT;


	SELECT_DISPLAY;
	writecommand(0xE0);
	writedata(0x00);
	writedata(0x03);
	writedata(0x09);
	writedata(0x08);
	writedata(0x16);
	writedata(0x0A);
	writedata(0x3F);
	writedata(0x78);
	writedata(0x4C);
	writedata(0x09);
	writedata(0x0A);
	writedata(0x08);
	writedata(0x16);
	writedata(0x1A);
	writedata(0x0F);
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0XE1);
	writedata(0x00);
	writedata(0x16);
	writedata(0x19);
	writedata(0x03);
	writedata(0x0F);
	writedata(0x05);
	writedata(0x32);
	writedata(0x45);
	writedata(0x46);
	writedata(0x04);
	writedata(0x0E);
	writedata(0x0D);
	writedata(0x35);
	writedata(0x37);
	writedata(0x0F);
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0XC0);      //Power Control 1
	writedata(0x17);    //Vreg1out
	writedata(0x15);    //Verg2out
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0xC1);      //Power Control 2
	writedata(0x41);    //VGH,VGL
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0xC5);      //Power Control 3
	writedata(0x00);
	writedata(0x12);    //Vcom
	writedata(0x80);
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0x36);      //Memory Access
	writedata(0x48);
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0x3A);      // Interface Pixel Format
	writedata(0x55); 	  //16 bit	565
//	writedata(0x66); 	  //18 bit
//	writedata(0x77); 	  //24 bit
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0xB0);      // Interface Mode Control
	writedata(0x80);     			 //SDO NOT USE
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0xB1);      //Frame rate
	writedata(0xA0);    //60Hz
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0xB4);      //Display Inversion Control
	writedata(0x02);    //2-dot
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0XB6); //Display Function Control  RGB/MCU Interface Control
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writedata(0x02);    //MCU
	writedata(0x02);    //Source,Gate scan dieection
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0XE9);      // Set Image Functio
	writedata(0x00);    // Disable 24 bit data
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(0xF7);      // Adjust Control
	writedata(0xA9);
	writedata(0x51);
	writedata(0x2C);
	writedata(0x82);    // D7 stream, loose
DESELECT_DISPLAY;

SELECT_DISPLAY;
	writecommand(ILI9488_SLPOUT);    //Exit Sleep
DESELECT_DISPLAY;

this->delay_ms(120);

SELECT_DISPLAY;
	writecommand(ILI9488_DISPON);    //Display on
DESELECT_DISPLAY;

}

/*
Аппаратный сброс
*/
void ILI9488::hardReset(void){
	pTFT_RST->setHigh();//Устанавливаетсмя при тнициализации, потом всегда "1"
	this->delay_ms(10);
	pTFT_RST->setLow();
	this->delay_ms(10);	
	pTFT_RST->setHigh();
	this->delay_ms(10);
}

/**/
void ILI9488::clrXY()
{
	if (orient==PORTRAIT)
		setXY(0,0,disp_x_size,disp_y_size);
	else
		setXY(0,0,disp_y_size,disp_x_size);
}

/**/
void ILI9488::setXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	if (orient==LANDSCAPE)
	{
		swap(x1, y1);
		swap(x2, y2);
		y1=disp_y_size-y1;
		y2=disp_y_size-y2;
		swap(y1, y2);
	}


	SELECT_DISPLAY;
	writecommand(0x2a); // Column addr set
	writedata(x1>>8);
	writedata(x1);
	writedata(x2>>8);
	writedata(x2);
	DESELECT_DISPLAY;

	SELECT_DISPLAY;
	writecommand(0x2b); 
	writedata(y1>>8);
	writedata(y1);
	writedata(y2>>8);
	writedata(y2);
	writedata(0x2c); 
	DESELECT_DISPLAY;	
}
/*
Устанавливаем координаты рабочей области
*/
void ILI9488::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	SELECT_DISPLAY;
	writecommand(ILI9488_CASET); // Column addr set
	writedata(x0 >> 8);
	writedata(x0 & 0xFF);     // XSTART
	writedata(x1 >> 8);
	writedata(x1 & 0xFF);     // XEND
	DESELECT_DISPLAY;
	SELECT_DISPLAY;
	writecommand(ILI9488_PASET); // Row addr set
	writedata(y0 >> 8);
	writedata(y0 & 0xff);     // YSTART
	writedata(y1 >> 8);
	writedata(y1 & 0xff);     // YEND
	DESELECT_DISPLAY;
	
	SELECT_DISPLAY;
	writecommand(ILI9488_RAMWR); // write to RAM
	DESELECT_DISPLAY;
}
/*

*/
void ILI9488::setScrollArea(uint16_t topFixedArea, uint16_t bottomFixedArea)
{
	SELECT_DISPLAY;
	writecommand(0x33); // Vertical scroll definition
	writedata(topFixedArea >> 8);
	writedata(topFixedArea);
	writedata((_height - topFixedArea - bottomFixedArea) >> 8);
	writedata(_height - topFixedArea - bottomFixedArea);
	writedata(bottomFixedArea >> 8);
	writedata(bottomFixedArea);
	DESELECT_DISPLAY;
}

/**/
void ILI9488::scroll(uint16_t pixels)
{
	SELECT_DISPLAY;
	writecommand(0x37); // Vertical scrolling start address
	writedata(pixels >> 8);
	writedata(pixels);
	DESELECT_DISPLAY;
}

/*
Предустановка цвета
*/
void ILI9488::setColor(uint16_t color){
	this->color565 = color;
	this->colorL = color565 & 0x31;
	this->colorH = color565 / 8;	
}	

/*
Устанавливаем цвет в формате RGB565
на вход red, green, blue
*/
void ILI9488::setColor(uint8_t r,uint8_t g, uint8_t b ){
	this->color565 = setColor565(r,g,b);
	this->colorL = color565 & 0x31;
	this->colorH = color565 / 8;
}	


/**/
void ILI9488::setBackColor(uint8_t r, uint8_t g, uint8_t b)
{
	backColorH=((r&248)|g>>5);
	backColorL=((g&28)<<3|b>>3);
	_transparent=false;
}


/**/
void ILI9488::setBackColor(uint32_t color)
{
	if (color == VGA_TRANSPARENT)
		_transparent = true;
	else
	{
		backColorH = uint8_t(color>>8);
		backColorL = uint8_t(color & 0xFF);
		_transparent=false;
	}
}
/**/
void ILI9488::drawImage(const uint8_t* img, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{

	if ((x >= _width) || (y >= _height))
		return;
	if ((x + w - 1) >= _width)
		w = _width - x;
	if ((y + h - 1) >= _height)
		h = _height - y;
	setAddrWindow(x, y, x + w - 1, y + h - 1);
SEND_DATA;
SELECT_DISPLAY;

	
//	uint8_t linebuff[w * 3 + 1];
//	uint32_t count = 0;
//	for (uint16_t i = 0; i < h; i++) {
//		uint16_t pixcount = 0;
//		for (uint16_t o = 0; o < w; o++) {
//			uint8_t b1 = img[count];
//			count++;
//			uint8_t b2 = img[count];
//			count++;
//			uint16_t color = b1 << 8 | b2;
//			linebuff[pixcount] = (((color & 0xF800) >> 11) * 255) / 31;
//			pixcount++;
//			linebuff[pixcount] = (((color & 0x07E0) >> 5) * 255)	/ 63;
//			pixcount++;
//			linebuff[pixcount] = ((color & 0x001F) * 255) / 31;
//			pixcount++;
//		}
////		HAL_SPI_Transmit(_spi->getHandler(), linebuff, w * 3, 100);

//	}

DESELECT_DISPLAY;
}

/*
Заливаем весь дисплей цветом color
*/
void ILI9488::fillScreen(uint16_t color)
{
	fillRect(0, 0,  _width, _height, color);
}
/**/
void ILI9488::setPixel(){
	sendasIO(&colorH);
	sendasIO(&colorL);
}

/**/
void ILI9488::setPixel(uint16_t color){
uint8_t tmp = (color>>8);
	sendasIO(&tmp);
tmp = (color & 0xFF);
	sendasIO(&tmp);
}
/*
Печатаем предустановленными цветом
*/
void ILI9488::drawPixel(int16_t x, int16_t y){
	setAddrWindow(x, y, x + 1, y + 1);
	SEND_DATA;
	SELECT_DISPLAY;
  setPixel();
	DESELECT_DISPLAY;
}

/*
Печатаем цветом color
*/
void ILI9488::drawPixel(int16_t x, int16_t y, uint16_t color)
{
if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
return;
setColor(color);
setAddrWindow(x, y, x + 1, y + 1);
SEND_DATA;
SELECT_DISPLAY;
writeColor565();
DESELECT_DISPLAY;

}

/*

*/
void ILI9488::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{

	if ((x >= _width) || (y >= _height))
		return;

	if ((y + h - 1) >= _height)
		h = _height - y;

	setAddrWindow(x, y, x, y + h - 1);
SEND_DATA;
SELECT_DISPLAY;

	while (h--) {
		writeColor565();
	}
DESELECT_DISPLAY;

}

/**/
void ILI9488::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{

//	if ((x >= _width) || (y >= _height))
//		return;
//	if ((x + w - 1) >= _width)
//		w = _width - x;
//	setAddrWindow(x, y, x + w - 1, y);
//	_dc->setHigh();
//	_cs->setLow();
//	while (w--)
//	{
//		write16BitColor(color);
//	}
//	_cs->setHigh();
}

/**/
void ILI9488:: drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,uint16_t color)
{
	setColor(color);
	 if (x0 == x1) {
	    if (y0 > y1)
	      _swap_int16_t(y0, y1);
	    drawFastVLine(x0, y0, y1 - y0 + 1, color);
	  } else if (y0 == y1) {
	    if (x0 > x1)
	      _swap_int16_t(x0, x1);
	    drawFastHLine(x0, y0, x1 - x0 + 1, color);
	  } else {

	    writeLine(x0, y0, x1, y1, color);

	  }

}

/**/
void ILI9488::writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,uint16_t color) {
setColor(color);
  int16_t steep = abs((float)(y1 - y0)) > abs((float)(x1 - x0));
	
  if (steep) {
    _swap_int16_t(x0, y0);
    _swap_int16_t(x1, y1);
  }

  if (x0 > x1) {
    _swap_int16_t(x0, x1);
    _swap_int16_t(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs((float)(y1 - y0));

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0 <= x1; x0++) {
    if (steep) {
      drawPixel(y0, x0);
    } else {
      drawPixel(x0, y0);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
void ILI9488::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	
	if ((x >= _width) || (y >= _height))
		return;
	if ((x + w - 1) >= _width)
		w = _width - x;
	if ((y + h - 1) >= _height)
		h = _height - y;
	
	setColor(color);
	setAddrWindow(x, y, x + w - 1, y + h - 1);

SEND_DATA;
SELECT_DISPLAY;

	for (y = h; y > 0; y--) {
		for (x = w; x > 0; x--) {
			writeColor565();
		}
	}
DESELECT_DISPLAY;
	

//Не понятно зачем это надо
//	_dc->setHigh();
//		_cs->setLow();

//		for (y = h; y > 0; y--) {
//			for (x = w; x > 0; x--) {

//				write16BitColor(ILI9488_DARKGREY);
//			}
//		}

//		_cs->setHigh();

}
void ILI9488::setRotation(uint8_t r)
{

//	writecommand(ILI9488_MADCTL);
//	rotation = r % 4; // can't be higher than 3
//	switch (rotation) {
//	case 0:
//		writedata(MADCTL_MX | MADCTL_BGR);
//		_width = ILI9488_TFTWIDTH;
//		_height = ILI9488_TFTHEIGHT;
//		break;
//	case 1:
//		writedata(MADCTL_MV | MADCTL_BGR);
//		_width = ILI9488_TFTHEIGHT;
//		_height = ILI9488_TFTWIDTH;
//		break;
//	case 2:
//		writedata(MADCTL_MY | MADCTL_BGR);
//		_width = ILI9488_TFTWIDTH;
//		_height = ILI9488_TFTHEIGHT;
//		break;
//	case 3:
//		writedata(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
//		_width = ILI9488_TFTHEIGHT;
//		_height = ILI9488_TFTWIDTH;
//		break;
//	}

}
void ILI9488::invertDisplay(uint8_t i)
{

//	  writecommand(i ? ILI9488_INVON : ILI9488_INVOFF);

}

/*

*/
uint16_t ILI9488::setColor565(uint8_t r, uint8_t g, uint8_t b)
{
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


void ILI9488::spiwrite(uint8_t data)
{
//	uint8_t d=data;
//	_spi->send(&d);

}
void ILI9488::writecommand(uint8_t c)
{
//	uint8_t d=c;
	SEND_CMD;
	if(SINGLE_IO_MODE)
		sendasIO(&c);
//	else
//		_spi->send(&d);
//	//HAL_SPI_Transmit(_spi.getHandler(), &d,1,100);

}

/*
выводит на дисплей пиксель в формате RGB565
*/
void ILI9488::writeColor565(void){
	if(SINGLE_IO_MODE){
		sendasIO(&colorH);
		sendasIO(&colorL);
	}
}
/**/
//void ILI9488::write16BitColor(uint16_t color)
//{

//	  uint8_t r = (color & 0xF800) >> 11;
//	  uint8_t g = (color & 0x07E0) >> 5;
//	  uint8_t b = color & 0x001F;

//	  r = (r * 255) / 31;
//	  g = (g * 255) / 63;
//	  b = (b * 255) / 31;
//	  if(SINGLE_IO_MODE)
//	  {
//		  sendasIO(&r);
//		  sendasIO(&g);
//		  sendasIO(&b);
//	  }
////	  else{
////	  _spi->send(&r);
////	  _spi->send(&g);
////	  _spi->send(&b);
////	  }

//}


void ILI9488::writedata(uint8_t d)
{

	
	//	uint8_t tmp=d;
SEND_DATA;
	if(SINGLE_IO_MODE)
		sendasIO(&d);
//	else
//	_spi->send(&tmp);

}
void ILI9488::testLines(uint8_t color)
{

//	unsigned long start, t;
//	int x1, y1, x2, y2, w = _width, h = _height;
//	fillScreen(ILI9488_BLACK);

//	x1 = y1 = 0;
//	y2 = h - 1;

//	for (x2 = 0; x2 < w; x2 += 6)
//		drawLine(x1, y1, x2, y2, color);
//	x2 = w - 1;
//	for (y2 = 0; y2 < h; y2 += 6)
//		drawLine(x1, y1, x2, y2, color);
//	fillScreen(ILI9488_BLACK);

//	x1 = w - 1;
//	y1 = 0;
//	y2 = h - 1;

//	for (x2 = 0; x2 < w; x2 += 6)
//		drawLine(x1, y1, x2, y2, color);
//	x2 = 0;
//	for (y2 = 0; y2 < h; y2 += 6)
//		drawLine(x1, y1, x2, y2, color);

//	fillScreen(ILI9488_BLACK);

//	x1 = 0;
//	y1 = h - 1;
//	y2 = 0;

//	for (x2 = 0; x2 < w; x2 += 6)
//		drawLine(x1, y1, x2, y2, color);
//	x2 = w - 1;
//	for (y2 = 0; y2 < h; y2 += 6)
//		drawLine(x1, y1, x2, y2, color);

//	fillScreen(ILI9488_BLACK);

//	x1 = w - 1;
//	y1 = h - 1;
//	y2 = 0;

//	for (x2 = 0; x2 < w; x2 += 6)
//		drawLine(x1, y1, x2, y2, color);
//	x2 = 0;
//	for (y2 = 0; y2 < h; y2 += 6)
//		drawLine(x1, y1, x2, y2, color);
}

/*
Пишем данные в порт
*/
void ILI9488::sendasIO(uint8_t *d)
{
	uint16_t portTemp = *d;
	dataPort->CLRTX |= PORT_MASK;
	dataPort->SETTX |= portTemp * 8; //Используем умножение для сдвига в лево на 3 разряда
	pTFT_WR->setLow();
	pTFT_WR->setHigh();	
}


void ILI9488::setFont(uint8_t* font)
{
	cfont.font      = font;
	cfont.x_size    = fontbyte(0);
	cfont.y_size    = fontbyte(1);
	cfont.offset    = fontbyte(2);
	cfont.numchars  = fontbyte(3);
}

uint8_t* ILI9488::getFont()
{
	return cfont.font;
}

uint8_t ILI9488::getFontXsize()
{
	return cfont.x_size;
}

uint8_t ILI9488::getFontYsize()
{
	return cfont.y_size;
}

/**/
void ILI9488::printChar(uint8_t c, int x, int y)
{
	uint8_t i,ch;
	uint16_t j;
	uint16_t temp; 

SELECT_DISPLAY;
  
	if (!_transparent)
	{
		if (orient==PORTRAIT)
		{
			setXY(x,y,x+cfont.x_size-1,y+cfont.y_size-1);
	  
			temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
			for(j=0;j<((cfont.x_size/8)*cfont.y_size);j++)
			{
				ch=*(&cfont.font[temp]);
				for(i=0;i<8;i++)
				{   
					if((ch&(1<<(7-i)))!=0)   
					{
						setPixel(color565);
					} 
					else
					{
						setPixel(color565);
					}   
				}
				temp++;
			}
		}
		else
		{
			temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;

			for(j=0;j<((cfont.x_size/8)*cfont.y_size);j+=(cfont.x_size/8))
			{
				setXY(x,y+(j/(cfont.x_size/8)),x+cfont.x_size-1,y+(j/(cfont.x_size/8)));
				for (int zz=(cfont.x_size/8)-1; zz>=0; zz--)
				{
					ch=*(&cfont.font[temp+zz]);
					for(i=0;i<8;i++)
					{   
						if((ch&(1<<i))!=0)   
						{
							setPixel(color565);
						} 
						else
						{
							setPixel(color565);
						}   
					}
				}
				temp+=(cfont.x_size/8);
			}
		}
	}
	else
	{
		temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
		for(j=0;j<cfont.y_size;j++) 
		{
			for (int zz=0; zz<(cfont.x_size/8); zz++)
			{
				ch=*(&cfont.font[temp+zz]); 
				for(i=0;i<8;i++)
				{   
				
					if((ch&(1<<(7-i)))!=0)   
					{
						setXY(x+i+(zz*8),y+j,x+i+(zz*8)+1,y+j+1);
						setPixel(color565);
					} 
				}
			}
			temp+=(cfont.x_size/8);
		}
	}

DESELECT_DISPLAY;
	clrXY();


}

