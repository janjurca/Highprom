#include "highprom.h"

void Highprom::init(){
    for (int i = 0; i < size; i++) {
        EEPROM.write(i, '\0');
    }
}
char * Highprom::getValue(char const *key, char *dst, unsigned n){
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

int Highprom::indexOfValue(char const* key){
    int len = strlen(key);
    int key_index = indexOfKey(key);
    if (key_index == -1) {
        return -1;
    } else {
        return indexOfKey(key) + len +1;
    }
}

int Highprom::indexOfKey(char const*key){
    int len = strlen(key);
    bool reading_key = true;
    for (int i = 0; i < size - len; i++) {
        char c;
        bool matched = true;
        int j = 0;
        for (; (c = EEPROM.read(i + j)) != '\0' ; j++) { // Iterate through one word whatever it is
            if (reading_key) {
                if (j < len && matched) {
                    if (c != key[j]) {
                        matched = false;
                    }
                    if (j+1 == len && matched) {
                        return i;
                    }
                }
            }
        }
        i = i + j;
        reading_key = !reading_key;
    }
    return -1;
}

int Highprom::getValueLength(int index){
    int i = index;
    for (; EEPROM.read(i) != '\0'; i++) {
    }
    return i -index;
}

void Highprom::removeCell(int index){
    if (index >= 0 && index < size) {
        int cell_length = getValueLength(index);
        for (int i = index+cell_length + 1; i < size; i++) {
            EEPROM.write(index++, EEPROM.read(i));
        }
    }
}

void Highprom::removeValue(char const*key){
    removeCell(indexOfValue(key));
    removeCell(indexOfKey(key));
}

bool Highprom::insertValue(char const*key, char const*value){
    int current_index = indexOfValue(key);
    if (current_index == -1) {
        return insertAtEnd(key, value);
    } else {
        int old_lenght = getValueLength(current_index);
        if (old_lenght == (int)strlen(value)) { //TODO solve types
            for (size_t i = 0; i < strlen(value); i++) {
                EEPROM.write(current_index+i, value[i]);
            }
            return true;
        } else{
            removeValue(key);
            return insertAtEnd(key, value);
        }
    }
}

bool Highprom::writeOnAdress(char const* str, int address){
    int end = strlen(str) + address;
    int i;
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

bool Highprom::insertAtEnd(char const* key,char const* value){
    int index_first = getFirstFreeIndex();
    int index = ++index_first;
    int i = 0;
    for (; i < (int)strlen(key); i++) {
        if (index+i >= size) {
            eraseFromTo(index, index+i);
            return false;
        }
        //fprintf(stderr,"halooooo----------------------------|%d|----------------------- ",index);
        EEPROM.write(index+i, key[i]);
    }
    EEPROM.write(index+i, '\0');
    index = index + i + 1;
    i = 0;
    for (; i < (int)strlen(value); i++) {
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
            return i+1;
        }
    }
    return -1;
}
