
.PHONY: all
all: highprom

EEPROM.o: EEPROM.cpp EEPROM.h

highprom.o: highprom.cpp highprom.h

highprom: highprom.o EEPROM.o main.cpp

clean:
	rm *.o highprom
