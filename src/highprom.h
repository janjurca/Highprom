#ifndef EEPROM_EXT_H
#define EEPROM_EXT_H value

#ifdef DEBUG_GTESTING
#include <stdio.h>
#include <cstring>
#include "../tests/EEPROM.h"
#include "iostream"
using namespace std;
#endif

#ifndef DEBUG_GTESTING
#include <EEPROM.h>
#include "Arduino.h"
#endif




class Highprom {
public:
    /**
     * initialize basics variable
     * @param size size of eeprom space that have to be used by this library
     */
    Highprom(int size): size(size){};

    /**
     * Use just once for initialization of library. Erase all data in desired size(from constructor) and set them to zero
     */
    void init();

    /**
     * Try to find desired variable defined by key in eeprom memmory
     * @param  key string that lead to variable
     * @param  dst destination buffer
     * @param  n max length of destination buffer
     * @return     pointer to buffer, null if key havent been found
     */
    char* getValue(char const* key, char * dst, unsigned n);
    /**
     * Insert or update value specified by key
     * @param  key   key label of value
     * @param  value value to save
     * @return       true if it was ok
     */
    bool insertValue(char const * key,char const* value);

    /**
     * Remove value from EEPROM
     * @param key key of value
     */
    void removeValue(char const* key);

protected:
    int size = 0;
    bool insertAtEnd(char const* key,char const* value);
    int getFirstFreeIndex();
    void eraseFromTo(int start,int end);
    int indexOfValue(char const* key);
    int indexOfKey(char const* key);
    int getValueLength(int index);
    bool writeOnAdress(char const* str, int address);
    int getNextStringIndex(int startIndex);
    void removeCell(int index);
};




#endif
