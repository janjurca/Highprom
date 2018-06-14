#include <gtest/gtest.h> // googletest header file
#include "../src/EEPROM.h"
#include "../src/highprom.h"
#include <string>
using std::string;

extern EEPROM_test EEPROM;

TEST(Atomic, Initialization) {
    Highprom prom(100);
    prom.init();
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(EEPROM.read(i), '\0');
    }
}

TEST(Atomic, SimpleInsertion) {
    Highprom prom(100);
    prom.init();
    prom.insertValue("key","value");
    char * expected = "key\0value\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(EEPROM.read(i), expected[i]);
    }
    char dst[20];
    prom.getValue("key",  dst, 20);
    EXPECT_EQ(string(dst), string("value"));
    //EEPROM.print();
}

TEST(Atomic, MultipleInsertion) {
    Highprom prom(100);
    prom.init();
    prom.insertValue("key","value");
    prom.insertValue("key2","ahoji");
    prom.insertValue("key3","johoj");
    char * expected = "key\0value\0key2\0ahoji\0key3\0johoj\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(EEPROM.read(i), expected[i]);
    }
    char dst[20];
    prom.getValue("key",  dst, 20);
    EXPECT_EQ(string(dst), string("value"));

    prom.getValue("key2",  dst, 20);
    EXPECT_EQ(string(dst), string("ahoji"));

    prom.getValue("key3",  dst, 20);
    EXPECT_EQ(string(dst), string("johoj"));

    //EEPROM.print();
}
