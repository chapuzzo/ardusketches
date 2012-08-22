/*
  UTFT_tinyFAT.h - Add-on library to integrate UTFT and tinyFAT
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

#ifndef UTFT_tinyFAT_h
#define UTFT_tinyFAT_h

#if defined(__AVR__)
	#if defined(ARDUINO) && ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
#else
	#include "WProgram.h"
#endif
#include "UTFT.h"
#include "tinyFAT.h"

class UTFTtf: public UTFT
{
	public:

		UTFTtf(byte model, int RS, int WR,int CS, int RST, int SER=0) : UTFT(model, RS, WR, CS, RST, SER) {}

		word loadBitmap(int x, int y, int sx, int sy, char *filename);
};

#endif