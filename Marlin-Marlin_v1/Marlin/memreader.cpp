/* -*- c++ -*- */

#include "Marlin.h"
#include "memreader.h"
#include "stepper.h"
#include "temperature.h"
#include "language.h"
#include "ultralcd.h"

MemReader::MemReader()
{
   program = 0;
   pos = 0;
   isprinting = false;
}

void MemReader::startMemprint(const uint8_t nr)
{
  if ( ScriptLength[nr] > 0 ) {
    program = nr;
    pos = 0;
    isprinting = true;
    lcd_ForceStatusScreen(true);
    lcd_ForceStatusScreen(false);
  }
}

void MemReader::pauseMemPrint( void )
{
   isprinting=false;
}

void MemReader::resumeMemPrint( void )
{
   isprinting=true;
}


/* ??? Check se serve */
void MemReader::getStatus()
{
  if(isprinting){
    SERIAL_PROTOCOLPGM(MSG_SD_PRINTING_BYTE);
    SERIAL_PROTOCOL(pos);
    SERIAL_PROTOCOLPGM("/");
    SERIAL_PROTOCOLLN(ScriptLength[program]);
  }
  else{
    SERIAL_PROTOCOLLNPGM(MSG_SD_NOT_PRINTING);
  }
}

void MemReader::printingHasFinished()
{
    st_synchronize();
    quickStop();
    isprinting = false;
    autotempShutdown();
}
