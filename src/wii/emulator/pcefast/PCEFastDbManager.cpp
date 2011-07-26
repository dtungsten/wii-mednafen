#include "main.h"
#include "PCEFast.h"
#include "PCEFastDbManager.h"
#include <wiiuse/wpad.h>

// PCE Keys
#define PCE_MAP_NONE   KEY_MAP_NONE
#define PCE_MAP_I      1
#define PCE_MAP_II     2
#define PCE_MAP_RUN    3
#define PCE_MAP_SELECT 4
#define PCE_MAP_LEFT   5
#define PCE_MAP_RIGHT  6
#define PCE_MAP_UP     7
#define PCE_MAP_DOWN   8
#define PCE_MAP_III    9
#define PCE_MAP_IV     10
#define PCE_MAP_V      11
#define PCE_MAP_VI     12

const MappableButton PCEFastDbManager::PCE_BUTTONS[PCE_BUTTON_COUNT] = 
{
  { "(none)",   PCE_NONE    },
  { "I",        PCE_I       }, 
  { "II",       PCE_II      }, 
  { "Run",      PCE_RUN     },
  { "Select",   PCE_SELECT  },
  { "Left",     PCE_LEFT    },
  { "Right",    PCE_RIGHT   },
  { "Up",       PCE_UP      },
  { "Down",     PCE_DOWN    },
  { "III",      PCE_III     },
  { "IV",       PCE_IV      },
  { "V",        PCE_V       },
  { "VI",       PCE_VI      }
};

const WiiButton PCEFastDbManager::
  WII_BUTTONS[WII_CONTROLLER_COUNT][WII_MAP_BUTTON_COUNT] =
{
  {
    { "Plus",   WPAD_BUTTON_PLUS,   PCE_MAP_RUN    },
    { "Minus",  WPAD_BUTTON_MINUS,  PCE_MAP_SELECT },
    { "2",      WPAD_BUTTON_2,      PCE_MAP_I      }, 
    { "1",      WPAD_BUTTON_1,      PCE_MAP_II     },
    { "A",      WPAD_BUTTON_A,      PCE_MAP_NONE   },
    { "B",      WPAD_BUTTON_B,      PCE_MAP_NONE   },
    { NULL,     0,                  PCE_MAP_NONE   },
    { NULL,     0,                  PCE_MAP_NONE   },
    { NULL,     0,                  PCE_MAP_NONE   },
    { NULL,     0,                  PCE_MAP_NONE   }
  },
  {
    { "Plus",   WPAD_BUTTON_PLUS,       PCE_MAP_RUN    },
    { "Minus",  WPAD_BUTTON_MINUS,      PCE_MAP_SELECT },
    { "2",      WPAD_BUTTON_2,          PCE_MAP_NONE   }, 
    { "1",      WPAD_BUTTON_1,          PCE_MAP_NONE   },
    { "A",      WPAD_BUTTON_A,          PCE_MAP_I      },
    { "B",      WPAD_BUTTON_B,          PCE_MAP_NONE   },
    { "C",      WPAD_NUNCHUK_BUTTON_C,  PCE_MAP_II     },
    { "Z",      WPAD_NUNCHUK_BUTTON_Z,  PCE_MAP_NONE   },
    { NULL,     0,                      PCE_MAP_NONE   },
    { NULL,     0,                      PCE_MAP_NONE   }
  },
  {
    { "Plus",   WPAD_CLASSIC_BUTTON_PLUS,     PCE_MAP_RUN    },
    { "Minus",  WPAD_CLASSIC_BUTTON_MINUS,    PCE_MAP_SELECT },
    { "A",      WPAD_CLASSIC_BUTTON_A,        PCE_MAP_I      }, 
    { "B",      WPAD_CLASSIC_BUTTON_B,        PCE_MAP_II     },
    { "X",      WPAD_CLASSIC_BUTTON_X,        PCE_MAP_NONE   },
    { "Y",      WPAD_CLASSIC_BUTTON_Y,        PCE_MAP_NONE   },
    { "R",      WPAD_CLASSIC_BUTTON_FULL_R,   PCE_MAP_NONE   },
    { "L",      WPAD_CLASSIC_BUTTON_FULL_L,   PCE_MAP_NONE   },
    { "zR",     WPAD_CLASSIC_BUTTON_ZR,       PCE_MAP_NONE   },
    { "zL",     WPAD_CLASSIC_BUTTON_ZL,       PCE_MAP_NONE   }
  },
  {
    { "Start",  PAD_BUTTON_START,             PCE_MAP_RUN    },
    { "A",      PAD_BUTTON_A,                 PCE_MAP_I      },
    { "B",      PAD_BUTTON_B,                 PCE_MAP_II     }, 
    { "X",      PAD_BUTTON_X,                 PCE_MAP_SELECT },
    { "Y",      PAD_BUTTON_Y,                 PCE_MAP_SELECT },
    { "R",      PAD_TRIGGER_R,                PCE_MAP_NONE   },
    { "L",      PAD_TRIGGER_L,                PCE_MAP_NONE   },
    { NULL,     0,                            PCE_MAP_NONE   },
    { NULL,     0,                            PCE_MAP_NONE   },
    { NULL,     0,                            PCE_MAP_NONE   },
  }
};

PCEFastDbManager::PCEFastDbManager( Emulator &emulator ) :
  StandardDatabaseManager( emulator )
{
}

dbEntry* PCEFastDbManager::getEntry()
{
  return (dbEntry*)&m_entry;
}

void PCEFastDbManager::resetToDefaults()
{
  PCEFast& emu = (PCEFast&)getEmulator();
  PCEFastDbEntry* entry = (PCEFastDbEntry*)getEntry();
  memset( entry, 0x0, sizeof( PCEFastDbEntry ) );

  StandardDatabaseManager::resetToDefaults();

  resetButtons();
  applyButtonMap();
}

int PCEFastDbManager::getMappableButtonCount()
{
  return PCE_BUTTON_COUNT;
}

const MappableButton* PCEFastDbManager::getMappableButton( int button )
{
  return &PCE_BUTTONS[button];
}

const WiiButton* PCEFastDbManager::getMappedButton(
  int profile, int controller, int button )
{
  return &(WII_BUTTONS[controller][button]);
}
