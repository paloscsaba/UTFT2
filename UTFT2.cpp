

#include "UTFT2.h"

#define DUETT 1
	

void UTFT2::LCD_Writ_Bus(char VH,char VL)
{   
	REG_PIOC_CODR=0xFF3FC;
	REG_PIOC_SODR=(VL<<2) & 0x3FC;
	REG_PIOC_SODR=(VH<<12) & 0xFF000;
	REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
}


void UTFT2::_fast_fill_16(int ch, int cl, long pix)
{
	long blocks;

    REG_PIOC_CODR=0xFF3FC;
	REG_PIOC_SODR=(cl<<2) & 0x3FC;
	REG_PIOC_SODR=(ch<<12) & 0xFF000;

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
	}
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16)+1; i++)
		{
			REG_PIOB_CODR=0x00200000;REG_PIOB_SODR=0x00200000;
		}
}


UTFT2::UTFT2()
{
}

UTFT2::UTFT2(byte model, int RS, int WR, int CS, int RST, int SER)
{ 
	disp_x_size =			239;
	disp_y_size =			319;
}

void UTFT2::LCD_Write_COM(char VL)  
{   
		REG_PIOB_CODR=0x00004000;
		LCD_Writ_Bus(0x00,VL);

}

void UTFT2::LCD_Write_DATA(char VH,char VL)
{
		REG_PIOB_SODR=0x00004000;
		LCD_Writ_Bus(VH,VL);
}

void UTFT2::LCD_Write_DATA(char VL)
{
		REG_PIOB_SODR=0x00004000;
		LCD_Writ_Bus(0x00,VL);

}

void UTFT2::InitLCD(byte orientation)
{
	orient=orientation;

	REG_PIOB_PER=0x00200000;  // Enable WR pin (B.21) 
	REG_PIOB_OER=0x00200000;  // Set WR pin (B.21) as output
	
	REG_PIOB_PER=0x00004000;  // Enable RS pin (B.14) 
	REG_PIOB_OER=0x00004000;  // Set RS pin (B.14) as output
	
	REG_PIOA_PER=0x00008000;  // Enable REST pin (A.15) 
	REG_PIOA_OER=0x00008000;  // Set REST pin (A.15) as output
	
	REG_PIOC_PER=0x000FF3FC;  // Enable DB0 to DB7 (C.2 to C.9) and DB8 to DB15 (C.12 to C.19) 
	REG_PIOC_OER=0x000FF3FC;  // Set DB0 to DB7 (C.2 to C.9) and DB8 to DB15 (C.12 to C.19) as output


	REG_PIOA_SODR=0x00008000;
	delay(5); 
	REG_PIOA_CODR=0x00008000;
	delay(15);
	REG_PIOA_SODR=0x00008000;
	delay(15);

	
    LCD_Write_COM(0xCB);  
    LCD_Write_DATA(0x39); 
    LCD_Write_DATA(0x2C); 
    LCD_Write_DATA(0x00); 
    LCD_Write_DATA(0x34); 
    LCD_Write_DATA(0x02); 

    LCD_Write_COM(0xCF);  
    LCD_Write_DATA(0x00); 
    LCD_Write_DATA(0XC1); 
    LCD_Write_DATA(0X30); 

    LCD_Write_COM(0xE8);  
    LCD_Write_DATA(0x85); 
    LCD_Write_DATA(0x00); 
    LCD_Write_DATA(0x78); 

    LCD_Write_COM(0xEA);  
    LCD_Write_DATA(0x00); 
    LCD_Write_DATA(0x00); 
 
    LCD_Write_COM(0xED);  
    LCD_Write_DATA(0x64); 
    LCD_Write_DATA(0x03); 
    LCD_Write_DATA(0X12); 
    LCD_Write_DATA(0X81); 

    LCD_Write_COM(0xF7);  
    LCD_Write_DATA(0x20); 
  
    LCD_Write_COM(0xC0);    //Power control 
    LCD_Write_DATA(0x23);   //VRH[5:0] 
 
    LCD_Write_COM(0xC1);    //Power control 
    LCD_Write_DATA(0x10);   //SAP[2:0];BT[3:0] 

    LCD_Write_COM(0xC5);    //VCM control 
    LCD_Write_DATA(0x3e);   //Contrast
    LCD_Write_DATA(0x28); 
 
    LCD_Write_COM(0xC7);    //VCM control2 
    LCD_Write_DATA(0x86);   //--
 
    LCD_Write_COM(0x36);    // Memory Access Control 
    LCD_Write_DATA(0x48);   

    LCD_Write_COM(0x3A);    
    LCD_Write_DATA(0x55); 

    LCD_Write_COM(0xB1);    
    LCD_Write_DATA(0x00);  
    LCD_Write_DATA(0x18); 
 
    LCD_Write_COM(0xB6);    // Display Function Control 
    LCD_Write_DATA(0x08); 
    LCD_Write_DATA(0x82);
    LCD_Write_DATA(0x27);  

    LCD_Write_COM(0x11);    //Exit Sleep 
    delay(120); 
				
    LCD_Write_COM(0x29);    //Display on 
    LCD_Write_COM(0x2c); 


	setColor(255, 255, 255);
	setBackColor(0, 0, 0);
	cfont.font=0;
	_transparent = false;
}

void UTFT2::setXY(word x1, word y1, word x2, word y2)
{
	if (orient==LANDSCAPE)
	{
		swap(word, x1, y1);
		swap(word, x2, y2)
		y1=disp_y_size-y1;
		y2=disp_y_size-y2;
		swap(word, y1, y2)
	}

	LCD_Write_COM(0x2a); 
	LCD_Write_DATA(x1>>8);
	LCD_Write_DATA(x1);
	LCD_Write_DATA(x2>>8);
	LCD_Write_DATA(x2);
	LCD_Write_COM(0x2b); 
	LCD_Write_DATA(y1>>8);
	LCD_Write_DATA(y1);
	LCD_Write_DATA(y2>>8);
	LCD_Write_DATA(y2);
	LCD_Write_COM(0x2c); 
}

void UTFT2::clrXY()
{
	if (orient==PORTRAIT)
		setXY(0,0,disp_x_size,disp_y_size);
	else
		setXY(0,0,disp_y_size,disp_x_size);
}

void UTFT2::drawRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	drawHLine(x1, y1, x2-x1);
	drawHLine(x1, y2, x2-x1);
	drawVLine(x1, y1, y2-y1);
	drawVLine(x2, y1, y2-y1);
}

void UTFT2::drawRoundRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		drawPixel(x1+1,y1+1);
		drawPixel(x2-1,y1+1);
		drawPixel(x1+1,y2-1);
		drawPixel(x2-1,y2-1);
		drawHLine(x1+2, y1, x2-x1-4);
		drawHLine(x1+2, y2, x2-x1-4);
		drawVLine(x1, y1+2, y2-y1-4);
		drawVLine(x2, y1+2, y2-y1-4);
	}
}

void UTFT2::fillRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}
	
	setXY(x1, y1, x2, y2);
	REG_PIOB_SODR=0x00004000;
	_fast_fill_16(fch,fcl,((long(x2-x1)+1)*(long(y2-y1)+1)));
	
}

void UTFT2::fillRoundRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	if ((x2-x1)>4 && (y2-y1)>4)
	{
		for (int i=0; i<((y2-y1)/2)+1; i++)
		{
			switch(i)
			{
			case 0:
				drawHLine(x1+2, y1+i, x2-x1-4);
				drawHLine(x1+2, y2-i, x2-x1-4);
				break;
			case 1:
				drawHLine(x1+1, y1+i, x2-x1-2);
				drawHLine(x1+1, y2-i, x2-x1-2);
				break;
			default:
				drawHLine(x1, y1+i, x2-x1);
				drawHLine(x1, y2-i, x2-x1);
			}
		}
	}
}

void UTFT2::drawCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
 
		setXY(x, y + radius, x, y + radius);
	LCD_Write_DATA(fch,fcl);
	setXY(x, y - radius, x, y - radius);
	LCD_Write_DATA(fch,fcl);
	setXY(x + radius, y, x + radius, y);
	LCD_Write_DATA(fch,fcl);
	setXY(x - radius, y, x - radius, y);
	LCD_Write_DATA(fch,fcl);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		setXY(x + x1, y + y1, x + x1, y + y1);
		LCD_Write_DATA(fch,fcl);
		setXY(x - x1, y + y1, x - x1, y + y1);
		LCD_Write_DATA(fch,fcl);
		setXY(x + x1, y - y1, x + x1, y - y1);
		LCD_Write_DATA(fch,fcl);
		setXY(x - x1, y - y1, x - x1, y - y1);
		LCD_Write_DATA(fch,fcl);
		setXY(x + y1, y + x1, x + y1, y + x1);
		LCD_Write_DATA(fch,fcl);
		setXY(x - y1, y + x1, x - y1, y + x1);
		LCD_Write_DATA(fch,fcl);
		setXY(x + y1, y - x1, x + y1, y - x1);
		LCD_Write_DATA(fch,fcl);
		setXY(x - y1, y - x1, x - y1, y - x1);
		LCD_Write_DATA(fch,fcl);
	}

	clrXY();
}

void UTFT2::fillCircle(int x, int y, int radius)
{
	for(int y1=-radius; y1<=0; y1++) 
		for(int x1=-radius; x1<=0; x1++)
			if(x1*x1+y1*y1 <= radius*radius) 
			{
				drawHLine(x+x1, y+y1, 2*(-x1));
				drawHLine(x+x1, y-y1, 2*(-x1));
				break;
			}
}

void UTFT2::clrScr()
{
	long i;
	
	clrXY();
	REG_PIOB_SODR=0x00004000;
	_fast_fill_16(0,0,((disp_x_size+1)*(disp_y_size+1)));

}

void UTFT2::fillScr(byte r, byte g, byte b)
{
	word color = ((r&248)<<8 | (g&252)<<3 | (b&248)>>3);
	fillScr(color);
}

void UTFT2::fillScr(word color)
{
	long i;
	char ch, cl;
	
	ch=byte(color>>8);
	cl=byte(color & 0xFF);

	clrXY();
	REG_PIOB_SODR=0x00004000;
	_fast_fill_16(ch,cl,((disp_x_size+1)*(disp_y_size+1)));

}

void UTFT2::setColor(byte r, byte g, byte b)
{
	fch=((r&248)|g>>5);
	fcl=((g&28)<<3|b>>3);
}

void UTFT2::setColor(word color)
{
	fch=byte(color>>8);
	fcl=byte(color & 0xFF);
}

word UTFT2::getColor()
{
	return (fch<<8) | fcl;
}

void UTFT2::setBackColor(byte r, byte g, byte b)
{
	bch=((r&248)|g>>5);
	bcl=((g&28)<<3|b>>3);
	_transparent=false;
}

void UTFT2::setBackColor(uint32_t color)
{
	if (color==VGA_TRANSPARENT)
		_transparent=true;
	else
	{
		bch=byte(color>>8);
		bcl=byte(color & 0xFF);
		_transparent=false;
	}
}

word UTFT2::getBackColor()
{
	return (bch<<8) | bcl;
}

void UTFT2::setPixel(word color)
{
	LCD_Write_DATA((color>>8),(color&0xFF));	// rrrrrggggggbbbbb
}

void UTFT2::drawPixel(int x, int y)
{
	setXY(x, y, x, y);
	setPixel((fch<<8)|fcl);

	clrXY();
}

void UTFT2::drawLine(int x1, int y1, int x2, int y2)
{
	if (y1==y2)
		drawHLine(x1, y1, x2-x1);
	else if (x1==x2)
		drawVLine(x1, y1, y2-y1);
	else
	{
		unsigned int	dx = (x2 > x1 ? x2 - x1 : x1 - x2);
		short			xstep =  x2 > x1 ? 1 : -1;
		unsigned int	dy = (y2 > y1 ? y2 - y1 : y1 - y2);
		short			ystep =  y2 > y1 ? 1 : -1;
		int				col = x1, row = y1;

				if (dx < dy)
		{
			int t = - (dy >> 1);
			while (true)
			{
				setXY (col, row, col, row);
				LCD_Write_DATA (fch, fcl);
				if (row == y2)
					return;
				row += ystep;
				t += dx;
				if (t >= 0)
				{
					col += xstep;
					t   -= dy;
				}
			} 
		}
		else
		{
			int t = - (dx >> 1);
			while (true)
			{
				setXY (col, row, col, row);
				LCD_Write_DATA (fch, fcl);
				if (col == x2)
					return;
				col += xstep;
				t += dy;
				if (t >= 0)
				{
					row += ystep;
					t   -= dx;
				}
			} 
		}
	
	}
	clrXY();
}

void UTFT2::drawHLine(int x, int y, int l)
{
	if (l<0)
	{
		l = -l;
		x -= l;
	}
	
	setXY(x, y, x+l, y);
	REG_PIOB_SODR=0x00004000;
	_fast_fill_16(fch,fcl,l);

	clrXY();
}

void UTFT2::drawVLine(int x, int y, int l)
{
	if (l<0)
	{
		l = -l;
		y -= l;
	}
	
	setXY(x, y, x, y+l);
	REG_PIOB_SODR=0x00004000;
	_fast_fill_16(fch,fcl,l);

	clrXY();
}

void UTFT2::printChar(byte c, int x, int y)
{
	byte i,ch;
	word j;
	word temp; 

	  
	if (!_transparent)
	{
		if (orient==PORTRAIT)
		{
			setXY(x,y,x+cfont.x_size-1,y+cfont.y_size-1);
	  
			temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
			for(j=0;j<((cfont.x_size/8)*cfont.y_size);j++)
			{
				ch=pgm_read_byte(&cfont.font[temp]);
				for(i=0;i<8;i++)
				{   
					if((ch&(1<<(7-i)))!=0)   
					{
						setPixel((fch<<8)|fcl);
					} 
					else
					{
						setPixel((bch<<8)|bcl);
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
					ch=pgm_read_byte(&cfont.font[temp+zz]);
					for(i=0;i<8;i++)
					{   
						if((ch&(1<<i))!=0)   
						{
							setPixel((fch<<8)|fcl);
						} 
						else
						{
							setPixel((bch<<8)|bcl);
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
				ch=pgm_read_byte(&cfont.font[temp+zz]); 
				for(i=0;i<8;i++)
				{   
				
					if((ch&(1<<(7-i)))!=0)   
					{
						setXY(x+i+(zz*8),y+j,x+i+(zz*8)+1,y+j+1);
						setPixel((fch<<8)|fcl);
					} 
				}
			}
			temp+=(cfont.x_size/8);
		}
	}


	clrXY();
}

void UTFT2::rotateChar(byte c, int x, int y, int pos, int deg)
{
	byte i,j,ch;
	word temp; 
	int newx,newy;
	double radian;
	radian=deg*0.0175;  

	
	temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
	for(j=0;j<cfont.y_size;j++) 
	{
		for (int zz=0; zz<(cfont.x_size/8); zz++)
		{
			ch=pgm_read_byte(&cfont.font[temp+zz]); 
			for(i=0;i<8;i++)
			{   
				newx=x+(((i+(zz*8)+(pos*cfont.x_size))*cos(radian))-((j)*sin(radian)));
				newy=y+(((j)*cos(radian))+((i+(zz*8)+(pos*cfont.x_size))*sin(radian)));

				setXY(newx,newy,newx+1,newy+1);
				
				if((ch&(1<<(7-i)))!=0)   
				{
					setPixel((fch<<8)|fcl);
				} 
				else  
				{
					if (!_transparent)
						setPixel((bch<<8)|bcl);
				}   
			}
		}
		temp+=(cfont.x_size/8);
	}

	clrXY();
}

void UTFT2::print(char *st, int x, int y, int deg)
{
	int stl, i;

	stl = strlen(st);

	if (orient==PORTRAIT)
	{
	if (x==RIGHT)
		x=(disp_x_size+1)-(stl*cfont.x_size);
	if (x==CENTER)
		x=((disp_x_size+1)-(stl*cfont.x_size))/2;
	}
	else
	{
	if (x==RIGHT)
		x=(disp_y_size+1)-(stl*cfont.x_size);
	if (x==CENTER)
		x=((disp_y_size+1)-(stl*cfont.x_size))/2;
	}

	for (i=0; i<stl; i++)
		if (deg==0)
			printChar(*st++, x + (i*(cfont.x_size)), y);
		else
			rotateChar(*st++, x, y, i, deg);
}

void UTFT2::print(String st, int x, int y, int deg)
{
	char buf[st.length()+1];

	st.toCharArray(buf, st.length()+1);
	print(buf, x, y, deg);
}

void UTFT2::printNumI(long num, int x, int y, int length, char filler)
{
	char buf[25];
	char st[27];
	boolean neg=false;
	int c=0, f=0;
  
	if (num==0)
	{
		if (length!=0)
		{
			for (c=0; c<(length-1); c++)
				st[c]=filler;
			st[c]=48;
			st[c+1]=0;
		}
		else
		{
			st[0]=48;
			st[1]=0;
		}
	}
	else
	{
		if (num<0)
		{
			neg=true;
			num=-num;
		}
	  
		while (num>0)
		{
			buf[c]=48+(num % 10);
			c++;
			num=(num-(num % 10))/10;
		}
		buf[c]=0;
	  
		if (neg)
		{
			st[0]=45;
		}
	  
		if (length>(c+neg))
		{
			for (int i=0; i<(length-c-neg); i++)
			{
				st[i+neg]=filler;
				f++;
			}
		}

		for (int i=0; i<c; i++)
		{
			st[i+neg+f]=buf[c-i-1];
		}
		st[c+neg+f]=0;

	}

	print(st,x,y);
}


void UTFT2::_convert_float(char *buf, double num, int width, byte prec)
{
	char format[10];
	
	sprintf(format, "%%%i.%if", width, prec);
	sprintf(buf, format, num);
}
	


void UTFT2::printNumF(double num, byte dec, int x, int y, char divider, int length, char filler)
{
	char st[27];
	boolean neg=false;

	if (dec<1)
		dec=1;
	else if (dec>5)
		dec=5;

	if (num<0)
		neg = true;

	_convert_float(st, num, length, dec);

	if (divider != '.')
	{
		for (int i=0; i<sizeof(st); i++)
			if (st[i]=='.')
				st[i]=divider;
	}

	if (filler != ' ')
	{
		if (neg)
		{
			st[0]='-';
			for (int i=1; i<sizeof(st); i++)
				if ((st[i]==' ') || (st[i]=='-'))
					st[i]=filler;
		}
		else
		{
			for (int i=0; i<sizeof(st); i++)
				if (st[i]==' ')
					st[i]=filler;
		}
	}

	print(st,x,y);
}

void UTFT2::setFont(uint8_t* font)
{
	cfont.font=font;
	cfont.x_size=fontbyte(0);
	cfont.y_size=fontbyte(1);
	cfont.offset=fontbyte(2);
	cfont.numchars=fontbyte(3);
}

uint8_t* UTFT2::getFont()
{
	return cfont.font;
}

uint8_t UTFT2::getFontXsize()
{
	return cfont.x_size;
}

uint8_t UTFT2::getFontYsize()
{
	return cfont.y_size;
}

void UTFT2::drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale)
{
	unsigned int col;
	int tx, ty, tc, tsx, tsy;

	if (scale==1)
	{
		if (orient==PORTRAIT)
		{
						setXY(x, y, x+sx-1, y+sy-1);
			for (tc=0; tc<(sx*sy); tc++)
			{
				col=pgm_read_word(&data[tc]);
				LCD_Write_DATA(col>>8,col & 0xff);
			}
		
		}
		else
		{
						for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+ty, x+sx-1, y+ty);
				for (tx=sx-1; tx>=0; tx--)
				{
					col=pgm_read_word(&data[(ty*sx)+tx]);
					LCD_Write_DATA(col>>8,col & 0xff);
				}
			}
		
		}
	}
	else
	{
		if (orient==PORTRAIT)
		{
						for (ty=0; ty<sy; ty++)
			{
				setXY(x, y+(ty*scale), x+((sx*scale)-1), y+(ty*scale)+scale);
				for (tsy=0; tsy<scale; tsy++)
					for (tx=0; tx<sx; tx++)
					{
						col=pgm_read_word(&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA(col>>8,col & 0xff);
					}
			}
		
		}
		else
		{
						for (ty=0; ty<sy; ty++)
			{
				for (tsy=0; tsy<scale; tsy++)
				{
					setXY(x, y+(ty*scale)+tsy, x+((sx*scale)-1), y+(ty*scale)+tsy);
					for (tx=sx-1; tx>=0; tx--)
					{
						col=pgm_read_word(&data[(ty*sx)+tx]);
						for (tsx=0; tsx<scale; tsx++)
							LCD_Write_DATA(col>>8,col & 0xff);
					}
				}
			}
		
		}
	}
	clrXY();
}

void UTFT2::drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy)
{
	unsigned int col;
	int tx, ty, newx, newy;
	double radian;
	radian=deg*0.0175;  

	if (deg==0)
		drawBitmap(x, y, sx, sy, data);
	else
	{
		for (ty=0; ty<sy; ty++)
			for (tx=0; tx<sx; tx++)
			{
				col=pgm_read_word(&data[(ty*sx)+tx]);

				newx=x+rox+(((tx-rox)*cos(radian))-((ty-roy)*sin(radian)));
				newy=y+roy+(((ty-roy)*cos(radian))+((tx-rox)*sin(radian)));

				setXY(newx, newy, newx, newy);
				LCD_Write_DATA(col>>8,col & 0xff);
			}
	
	}
	clrXY();
}


int UTFT2::getDisplayXSize()
{
	if (orient==PORTRAIT)
		return disp_x_size+1;
	else
		return disp_y_size+1;
}

int UTFT2::getDisplayYSize()
{
	if (orient==PORTRAIT)
		return disp_y_size+1;
	else
		return disp_x_size+1;
}

