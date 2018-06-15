#include "EEPROM.h"
#include <assert.h>     /* assert */
#include "stdio.h"
#include <iostream>

char EEPROM_test::read(int i){
    assert (i<size);
    return array[i];
}

void EEPROM_test::write(int i, char c){
    assert (i<size);
    array[i] = c;
}

void EEPROM_test::print(){
    for (size_t i = 0; i < size; i++) {
        putchar((array[i] == 0)?'|':array[i]);
    }
}

EEPROM_test EEPROM(100);
