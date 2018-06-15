# Arduino Highprom
Contains library with high level abstraciton of eeprom on arduino.
This library allows you to ease your work with EEPROM memmory on you arduino. It is doing associative array abstraction over part (or full) of Arduino EEPROM.

The mechanism works on storing C strings (array of character ending by '\0'), so in EEPROM is in fact stored pairs, key and value.

Then the string value inserting/updating is as simple as this:
```c
prom.insertValue("key","value");
```
