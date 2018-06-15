#ifndef EEPROM_EXT_H
#define EEPROM_EXT_H value

#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#include <cstring>
#include "tests/EEPROM.h"
#include "iostream"
using namespace std;
#endif

#ifndef DEBUG
#include <EEPROM.h>
#include "Arduino.h"
#endif




class Highprom {
public:
    /**
     * initialize basics variable
     * @param size size of eeprom space that have to be used by this library
     */
    Highprom(size_t size): size(size){};

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
    char* getValue(char* key, char* dst, unsigned n);

    /**
     * Insert or update value specified by key
     * @param  key   key label of value
     * @param  value value to save
     * @return       true if it was ok
     */
    bool insertValue(char* key,char* value);


    void removeValue(char* key);

protected:
    size_t size = 0;
    bool insertAtEnd(char* key,char* value);
    int getFirstFreeIndex();
    void eraseFromTo(int start,int end);
    int indexOfValue(char* key);
    int indexOfKey(char* key);
    int getValueLength(int index);
    bool writeOnAdress(char* str, size_t address);
    int getNextStringIndex(int startIndex);
    void removeCell(int index);
};




#endif
