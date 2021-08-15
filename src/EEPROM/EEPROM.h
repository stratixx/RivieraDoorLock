#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#include "../return_code.h"

#define EEMEM_MALLOC(size,ptrType) ((ptrType)EEPROM::eemem_malloc(size))

class EEPROM
{
    public:
        static return_code init();
        // odczyt bajtu z pod adresu EEPROM
        static char read(char*);
        // odczyt bloku danych z pod adresu EEPROM do bufora
        static return_code read(char*, char*, uint16_t);
        // zapiss bajtu pod adres EEPROM
        static return_code write(char*, char);
        // zapis bloku danych pod adres EEPROM
        static return_code write(char*, char*, uint16_t);
        // alokacja w EEPROM, raczej tylko dla symulacji na PC
        static void* eemem_malloc(uint32_t);

    protected:

    private:
        EEPROM() {  };

};

#endif // EEPROM_H
