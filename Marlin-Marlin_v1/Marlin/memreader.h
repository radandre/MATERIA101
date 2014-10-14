/* -*- c++ -*- */

#ifndef MEMREADER_H
#define MEMREADER_H

//Length=13 ( 1 in meno dello 0 finale )
/*static uint8_t LEVEL_PLATE[] = { 'M', '7', '1', ' ', '(', 'p', 'i', 'p', 'p', 'o', ')', 0xd, 0x0d, 0x00 };*/

#include "language.h"

#if LANGUAGE_CHOICE == 7
#if MACHINE_3D == 1
#include "sc_3d_level_plate_a.h"
#include "sc_3d_level_plate_m.h"
#else
#include "sc_level_plate_a.h"
#include "sc_level_plate_m.h"
#endif
#elif LANGUAGE_CHOICE == 1
#if MACHINE_3D == 1
#include "sc_3d_level_plate_a_en.h"
#include "sc_3d_level_plate_m_en.h"
#else
#include "sc_level_plate_a_en.h"
#include "sc_level_plate_m_en.h"
#endif
#else
#include "sc_level_plate_a.h"
#include "sc_level_plate_m.h"
#endif

#if MACHINE_3D == 1
#include "sc_3d_change_left.h"
#include "sc_3d_change_right.h"
#else
#include "sc_change_left.h"
#include "sc_change_right.h"
#endif

#include "sc_nozzles.h"

static uint8_t *Script[6] = { 0,
                              LEVEL_PLATE_A,
                              LEVEL_PLATE_M,
                              NOZZLES,
                              CHANGE_RIGHT,
#if EXTRUDERS > 1
                              CHANGE_LEFT
#else
                              0
#endif
};
                              
// Utilities program length
static uint32_t ScriptLength[6] = { -1,
                                     LEVEL_PLATE_A_LENGTH,
                                     LEVEL_PLATE_M_LENGTH,
                                     NOZZLES_LENGTH,
				     CHANGE_RIGHT_LENGTH,
#if EXTRUDERS > 1
                                     CHANGE_LEFT_LENGTH
#else
                                     -1
#endif
};

class MemReader
{
public:
  MemReader();
  
  void startMemprint(const uint8_t nr);
  void pauseMemPrint();
  void resumeMemPrint();
  void getStatus();
  void printingHasFinished();

  FORCE_INLINE bool eof() { return pos>=ScriptLength[program]; };
  FORCE_INLINE int16_t get() {  if ( pos<=ScriptLength[program] ) 
                                  return (int16_t)Script[program][pos++];
                                else
                                  return -1;
                             };
  FORCE_INLINE uint8_t percentDone(){if(!isprinting) return 0; return pos/((ScriptLength[program]+99)/100); };

public:
  bool isprinting;  

private:
  uint8_t program;
  uint32_t pos;

};
extern MemReader utility;
#endif
