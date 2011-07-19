#ifndef LYNX_DB_MANAGER_H
#define LYNX_DB_MANAGER_H

#include "StandardDatabaseManager.h"

#define LYNX_BUTTON_COUNT         10

/*
 * Lynx database entry 
 */
typedef struct LynxDbEntry
{
  StandardDbEntry base;
  int orient;
} LynxDbEntry;

class LynxDbManager : public StandardDatabaseManager
{
private:
  LynxDbEntry m_entry;

protected:
  bool writeEntryValues( FILE* file, const char* hash, const dbEntry *entry );
  void readEntryValue( dbEntry *entry, const char* name, const char* value );

public:
  static const MappableButton LYNX_BUTTONS[LYNX_BUTTON_COUNT];
  static const WiiButton 
    WII_BUTTONS[WII_CONTROLLER_COUNT][WII_MAP_BUTTON_COUNT];
  LynxDbManager( Emulator& emulator );
  const WiiButton* getMappedButton( int profile, int controller, int button );
  int getMappableButtonCount();
  const MappableButton* getMappableButton( int button );
  void resetToDefaults();
  dbEntry* getEntry();
};

#endif