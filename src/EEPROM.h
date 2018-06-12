#ifndef EEPROM_TEST_H
#define EEPROM_TEST_H value
#include <cstdlib>
#include <cwchar>
#include <cstring>

class EEPROM_test {
private:
    /* data */
    size_t size;
public:
    EEPROM_test (size_t size):size(size){};
    char read(int i);
    void write(int i, char c);

};

extern EEPROM_test EEPROM;

#endif
