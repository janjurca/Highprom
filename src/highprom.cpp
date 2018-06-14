#include "highprom.h"

void Highprom::init(){
    for (size_t i = 0; i < size; i++) {
        EEPROM.write(i, '\0');
    }
}
char * Highprom::getValue(char *key, char *dst, unsigned n){
    int valueIndex = indexOfValue(key);
    if (valueIndex == -1) {
        dst = NULL;
        return dst;
    } else {
        for (unsigned i = 0; i < n; i++) {
            dst[i] = EEPROM.read(valueIndex++);
            if (dst[i] == '\0') {
                break;
            }
        }
        dst[n-1] = '\0';
        return dst;
    }
}

int Highprom::indexOfValue(char* key){
    int len = strlen(key);
    for (int i = 0; i < size - len; i++) {
        for (int j = 0; j < len; j++) {
            char c = EEPROM.read(i + j);
            if (c != key[j]) {
                break;
            }
            if (j+1 == len) {
                return i + len + 1;
            }
        }
    }
    return -1;
}

int Highprom::getValueLength(int index){
    int i = 0;
    for (; EEPROM.read(i) != '\0'; i++) {
    }
    return i;
}

void Highprom::removeValue(char *key){
    //spocitej delku a ty před tim posun
    int index = indexOfValue(key);
    if (index != -1) {
        int key_length = getValueLength(index);
        int value_length  = getValueLength(index+key_length);
        for (size_t i = index+key_length+value_length; i < size; i++) {
            EEPROM.write(index++, EEPROM.read(i));
        }
    }
}

bool Highprom::insertValue(char *key, char *value){
    int current_index = indexOfValue(key);
    if (current_index == -1) {
        return insertAtEnd(key, value);
    } else {
        int old_lenght = getValueLength(current_index);
        if (old_lenght == strlen(value)) {
            for (size_t i = 0; i < strlen(value); i++) {
                EEPROM.write(current_index+i, value[i]);
            }
        } else{
            removeValue(key);
            insertAtEnd(key, value);
        }
    }
}

bool Highprom::writeOnAdress(char* str, size_t address){
    unsigned end = strlen(str) + address;
    size_t i;
    for (i = address; i < end ;i++){
        if (i > size) {
            break;
        }
        EEPROM.write(i, str[i]);
    }
    return (i == end)?true:false;
}

int Highprom::getNextStringIndex(int startIndex){
    char c;
    do {
        c = EEPROM.read(startIndex++);
    } while(c != '\0' && startIndex < size);
    return startIndex;
}

void Highprom::eraseFromTo(int start, int end){
    for (int i = start; i < end; i++) {
        EEPROM.write(i, '\0');
    }
}

bool Highprom::insertAtEnd(char* key,char* value){
    int index_first = getFirstFreeIndex();
    int index = index_first;
    size_t i = 0;
    for (; i < strlen(key); i++) {
        if (index+i >= size) {
            eraseFromTo(index, index+i);
            return false;
        }
        EEPROM.write(index+i, key[i]);
    }
    EEPROM.write(index+i, '\0');
    index = index + i + 1;
    i = 0;
    for (; i < strlen(value); i++) {
        if (index+i >= size) {
            eraseFromTo(index_first, index+i);
            return false;
        }
        EEPROM.write(index+i, value[i]);
    }
    return true;
}

int Highprom::getFirstFreeIndex(){
    for (int i = size-1; i > 0; i--) {
        if (EEPROM.read(i) != '\0') {
            return i+2;
        }
    }
}
