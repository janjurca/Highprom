#ifndef EEPROM_TEST_H
#define EEPROM_TEST_H value
#include <cstdlib>
#include <cwchar>
#include <cstring>

class EEPROM_test {
private:
    /* data */
    size_t size;
    char* array;
public:
    EEPROM_test (size_t size):size(size){
        array = new char[size];
    };
    char read(int i);
    void write(int i, char c);
    void print();

};

extern EEPROM_test EEPROM;

#endif
