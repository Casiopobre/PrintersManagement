#ifndef PRINTEADORAS_H
#define PRINTEADORAS_H
#include "printer_struct.h"

/**
 * Le o arquivo e almacena os datos nunha lista de estruturas tipo printer
 *
 * @param printers_list A lista de impresoras na que gardar as estruturas
 * @param fileName Nome do arquivo a abrir
 */
void read_file(char fileName[], TLISTA printers_list);

/**
 * Imprime a lista de impresoras por pantalla.
 *
 * @param printers_list A lista de impresoras a imprimir.
 */
void print_list(TLISTA printers_list);

/**
 * Elimina unha impresora da lista.
 * 
 * @param printers_list A lista de impresoras.
 * @param printerName O nome da impresora a eliminar.
 */
void del_printer(TLISTA printers_list, char printerName[]);

/**
 * Engade unha impresora a lista.
 *
 * @param printers_list A lista de impresoras.
 * @param printer A impresora a engadir.
 */
void add_printer(TLISTA printers_list, printers printer);

/**
 * Envía un traballo a cola dunha impresora.
 *
 * @param printers_list A lista de impresoras.
 * @param printerName O nome da impresora.
 * @param documentID A ID do traballo a engadir na cola.
 */
void add_to_queue(TLISTA printers_list, char printerName[], TIPOELEMENTOCOLA documentID);

/**
 * Mostra a cola de impresion dunha impresora.
 *
 * @param printers_list A lista de impresoras.
 * @param printerName O nome da impresora.
 */
void print_queue(TLISTA printers_list, char printerName[]);

/**
 * Elimina o ultimo elemento da cola dunha impresora.
 *
 * @param printers_list A lista de impresoras.
 * @param printerName O nome da impresora.
 */
void print_document(TLISTA printers_list, char printerName[]);

/**
 * Mostra a(s) impresora(s) con menos elementos na cola.
 *
 * @param printers_list A lista de impresoras.
 */
void show_low_queue_printers(TLISTA printers_list);

/**
 * Sae do program e actualiza o arquivo de entrada coa lista modificada
 *
 * @param printers_list A lista de impresoras.
 * @param fileName O nome do  arquivo onde se guarda a lista actualidaza.
 */
void safe_exit(TLISTA printers_list, char fileName[]);

/**
 * Sae do program e actualiza o arquivo de entrada coa lista modificada
 *
 * @param printers_list A lista de impresoras.
 */
void free_memory(TLISTA printers_list);

#endif //PRINTEADORAS_H