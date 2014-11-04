/*
 * LCDisplay.cpp
 *
 *  Created on: 04.11.2014
 *      Author: heiko
 */

#include "LCDisplay.h"

LCDisplay::LCDisplay(LcdHwConfig_t oLcdHwConfig) {

	this->oLcdHwConfig_ = oLcdHwConfig;
}

LCDisplay::~LCDisplay() {
	// TODO Auto-generated destructor stub
}

void LCDisplay::SetDisplayLight(bool bSwitchOn) volatile {

	if(bSwitchOn) {
		*this->oLcdHwConfig_.nDispLightPort |= (1 << this->oLcdHwConfig_.nDispLightPin);
	} else {
		*this->oLcdHwConfig_.nDispLightPort &= ~(1 << this->oLcdHwConfig_.nDispLightPin);
	}
}

void LCDisplay::LcdEnable() volatile {

	*this->oLcdHwConfig_.nLcdPort |= (1 << this->oLcdHwConfig_.nLcdEn);
	_delay_us( LCD_ENABLE_US );
	*this->oLcdHwConfig_.nLcdPort &= ~(1 << this->oLcdHwConfig_.nLcdEn);
}

void LCDisplay::LcdOut(uint8_t nData) volatile {

	nData &= 0xF0;

	*this->oLcdHwConfig_.nLcdPort &= ~(0xF0>>(4-this->oLcdHwConfig_.nLcdStartPin));
	*this->oLcdHwConfig_.nLcdPort |= (nData>>(4-this->oLcdHwConfig_.nLcdStartPin));
	LcdEnable();
}

void LCDisplay::InitLCDisplay() volatile {

	uint8_t pins = (0x0F << this->oLcdHwConfig_.nLcdStartPin) |
                   (1<<this->oLcdHwConfig_.nLcdRS) |
                   (1 << this->oLcdHwConfig_.nLcdEn);

	*this->oLcdHwConfig_.nLcdDdr |= pins;

    *this->oLcdHwConfig_.nLcdPort &= ~pins;

    _delay_ms( LCD_BOOTUP_MS );

    LcdOut( LCD_SOFT_RESET );
    _delay_ms( LCD_SOFT_RESET_MS1 );

    LcdEnable();
    _delay_ms( LCD_SOFT_RESET_MS2 );

    LcdEnable();
    _delay_ms( LCD_SOFT_RESET_MS3 );

    LcdOut( LCD_SET_FUNCTION |
             LCD_FUNCTION_4BIT );
    _delay_ms( LCD_SET_4BITMODE_MS );

    WriteCommand( LCD_SET_FUNCTION |
                 LCD_FUNCTION_4BIT |
                 LCD_FUNCTION_2LINE |
                 LCD_FUNCTION_5X7 );

    WriteCommand( LCD_SET_DISPLAY |
                 LCD_DISPLAY_ON |
                 LCD_CURSOR_OFF |
                 LCD_BLINKING_OFF);

    WriteCommand( LCD_SET_ENTRY |
                 LCD_ENTRY_INCREASE |
                 LCD_ENTRY_NOSHIFT );

    ClearLCDisplay();
}

void LCDisplay::ClearLCDisplay() volatile {

    WriteCommand( LCD_CLEAR_DISPLAY );
    _delay_ms( LCD_CLEAR_DISPLAY_MS );

}

void LCDisplay::CursorHome() volatile {

    WriteCommand( LCD_CURSOR_HOME );
    _delay_ms( LCD_CURSOR_HOME_MS );

}

void LCDisplay::CurserPos(uint8_t nRow, uint8_t nCol) volatile {
    uint8_t data;

    switch (nCol)
    {
        case 1:    // 1. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE1 + nRow;
            break;

        case 2:    // 2. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE2 + nRow;
            break;

        case 3:    // 3. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE3 + nRow;
            break;

        case 4:    // 4. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE4 + nRow;
            break;

        default:
            return;
    }

    WriteCommand( data );
}

void LCDisplay::WriteData(uint8_t nData) volatile {
    *this->oLcdHwConfig_.nLcdPort |= (1<<this->oLcdHwConfig_.nLcdRS);

    LcdOut( nData );
    LcdOut( nData<<4 );

    _delay_us( LCD_WRITEDATA_US );

}

void LCDisplay::WriteString(const char *nString) volatile {

    while( *nString != '\0' )
        WriteData( *nString++ );

}

void LCDisplay::GenerateChar(uint8_t nCode, const uint8_t *nData) volatile {

    WriteCommand( LCD_SET_CGADR | (nCode<<3) );

    for ( uint8_t i=0; i<8; i++ )
    {
        WriteData( nData[i] );
    }

}

void LCDisplay::WriteCommand(uint8_t nCommand) volatile {

    *this->oLcdHwConfig_.nLcdPort &= ~(1<< this->oLcdHwConfig_.nLcdRS);

    LcdOut( nCommand );
    LcdOut( nCommand<<4 );

    _delay_us( LCD_COMMAND_US );

}
