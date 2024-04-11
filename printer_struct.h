#ifndef PRINTER_STRUCT_H
#define PRINTER_STRUCT_H

#include "cola.h"

typedef struct _printers{
    char name[50];
    char brand[50];
    char model[50];
    char location[50];
    TCOLA queue;
    int queue_elements;
} printers;

#endif // PRINTER_STRUCT_H