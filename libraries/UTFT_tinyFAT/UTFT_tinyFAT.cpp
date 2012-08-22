/*
  UTFT_tinyFAT.cpp - Add-on library to integrate UTFT and tinyFAT
  Copyright (C)2010-2012 Henning Karlsen. All right reserved
  
  Basic functionality of this library are based on the demo-code provided by
  ITead studio. You can find the latest version of the library at
  http://www.henningkarlsen.com/electronics

  If you make any modifications or improvements to the code, I would appreciate
  that you share the code with me so that I might include it in the next release.
  I can be contacted through http://www.henningkarlsen.com/electronics/contact.php

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "UTFT_tinyFAT.h"

word UTFTtf::loadBitmap(int x, int y, int sx, int sy, char *filename)
{
	int res;
	int cx, cy, cp;
	word temp, result;
	byte r,g,b;

	res=file.openFile(filename, FILEMODE_BINARY);
	if (res==NO_ERROR)
	{
		cbi(P_CS, B_CS);
		cx=0;
		cy=0;
		result=512;
		if (orient==PORTRAIT)
		{
			setXY(x, y, x+sx-1, y+sy-1);
		}
		while (result==512)
		{
			result=file.readBinary();
			switch(result)
			{
				case ERROR_WRONG_FILEMODE:
					return ERROR_WRONG_FILEMODE;
					break;
				case ERROR_NO_FILE_OPEN:
					return ERROR_NO_FILE_OPEN;
					break;
				default:
					if (orient==PORTRAIT)
					{
						for (int i=0; i<result; i+=2)
							LCD_Write_DATA(file.buffer[i],file.buffer[i+1]);
					}
					else
					{
						cp=0;
						while (cp<result)
						{
							if (((result-cp)/2)<(sx-cx))
							{
								setXY(x+cx, y+cy, x+cx+((result-cp)/2)-1, y+cy);
								for (int i=(result-cp)-2; i>=0; i-=2)
									LCD_Write_DATA(file.buffer[cp+i],file.buffer[cp+i+1]);
								cx+=((result-cp)/2);
								cp=result;
							}
							else
							{
								setXY(x+cx, y+cy, x+sx-1, y+cy);
								for (int i=sx-cx-1; i>=0; i--)
									LCD_Write_DATA(file.buffer[cp+(i*2)],file.buffer[cp+(i*2)+1]);
								cp+=(sx-cx)*2;
								cx=0;
								cy++;
							}
						}
					}
					break;
			}              
		}
		file.closeFile();
		setXY(0,0,getDisplayXSize()-1,getDisplayYSize()-1);
		sbi(P_CS, B_CS);
		return 0;
	}
	else
	{
		return res;
	}
};
