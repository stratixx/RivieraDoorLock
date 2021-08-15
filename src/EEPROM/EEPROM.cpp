#include "EEPROM.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#define EEPROM_SIZE 512
#define EEPROM_FILENAME "EEPROM/eeprom.txt"
#define POINTER(arg1,arg2) ((char*)((int)arg1 + (int)arg2))

// tablica emuluj¹ca komórki pamiêci EEPROM
char memory[EEPROM_SIZE];

void read_from_file();
void save_to_file();

return_code EEPROM::init()
{
    read_from_file();
    //cout<<memory;
    return OK;
}

// odczyt bajtu z pod adresu
char EEPROM::read(char* src)
{
    return *POINTER(memory,src);
}

// odczyt bloku danych z pod adresu
return_code EEPROM::read(char* src, char* dest, uint16_t counter)
{
    if( (int)POINTER(src,counter)>=EEPROM_SIZE )
        return POINTER_ERROR;
    memcpy(dest, POINTER(memory,src), counter);
    return OK;
}

// zapiss bajtu pod adres
return_code EEPROM::write(char* dest, char byte)
{
    if( (int)dest>=EEPROM_SIZE)
        return POINTER_ERROR;
    *POINTER(memory,dest) = byte;
    save_to_file();
    return OK;
}

// zapis bloku danych pod adres
return_code EEPROM::write(char* src, char* dest, uint16_t counter)
{
    if( (int)POINTER(dest,counter)>=EEPROM_SIZE )
        return POINTER_ERROR;
    memcpy(POINTER(memory,dest), src, counter);
    save_to_file();
    return OK;
}

// alokacja w EEPROM, raczej tylko dla symulacji na PC
void * EEPROM::eemem_malloc(uint32_t mallocSize)
{
    static uint32_t top = 0;
    void * pointer = (void*)top;
    top += mallocSize;
    return pointer;
}

void read_from_file()
{
    ifstream file;
    file.open(EEPROM_FILENAME, ios::in | ios::binary);
    file.read(memory, EEPROM_SIZE);
    file.close();
}

void save_to_file()
{
    ofstream file;
    file.open(EEPROM_FILENAME, ios::out | ios::binary);
    file.write(memory, EEPROM_SIZE);
    file.close();
}
