#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cola.h"
#include "lista.h"

// NOTA: todos os printf("\033[(num)1;(num2)m") teñen proposito unicamente estetico (cambian a cor do texto)

void read_file(char fileName[], TLISTA printers_list){
    FILE* printers_file = fopen(fileName, "r"); // Abrimos o arquivo en modo lectura para gardar os datos
    if (printers_file == NULL){
        printf("\033[1;33m");
        perror("Erro ao abrir o arquivo :(\n");
        printf("\033[1;0m");
    }

    printers printer; 
    TPOSICION position = primeroLista(printers_list);

    // Bucle para escanear cada unha das impresoras do documento: escanea liña a liña mentres o numero de elementos escaneados sexa == 4
    while(fscanf(printers_file, "%s %s %s %s\n", printer.name, printer.brand, printer.model, printer.location) == 4){
        crearCola(&printer.queue); // Creamos unha cola para cada impresora
        insertarElementoLista(&printers_list, position, printer); // Insertamos cada impresora na lista
        position = siguienteLista(printers_list, position); // Pasamos a posicion seguinte da lista para gardar a nova impresora
        // Para comprobar que se escanearon correctamente
        // printf("%s %s %s %s\n \n", printer.name, printer.brand, printer.model, printer.location);
    }
    fclose(printers_file); // Pechamos o arquivo
}

void print_list(TLISTA printers_list){
    printers printer;
    TPOSICION position = primeroLista(printers_list);

    // Comprobacion de que a lista non este vacia
    if (esListaVacia(printers_list)){
        printf("\033[1;33m");
        printf("A lista esta vacia :( \n");
        printf("\033[1;0m");
        return;
    }
    printf("\033[0;34m");
    printf("\n|Nome| * |Marca| * |Modelo| * |Ubicacion|\n \n");
    // Bucle para iterar sobre a lista
    while(position != finLista(printers_list)){ 
        recuperarElementoLista(printers_list, position, &printer);
        printf("%s %s %s %s \n \n", printer.name, printer.brand, printer.model, printer.location);
        position = siguienteLista(printers_list, position);
    }
    printf("\033[1;0m");
}

void del_printer(TLISTA printers_list, char printerName[]){
    printers printer;
    TPOSICION position = primeroLista(printers_list);
    // Bucle para iterar sobre a lista
    while(position != finLista(printers_list)){
        recuperarElementoLista(printers_list, position, &printer);
        // Condicional para atopar a impresora buscada (compara os nomes das impresoras)
        if (strcmp(printer.name, printerName) == 0){
            if(esColaVacia(printer.queue))
                destruirCola(&printer.queue);
        suprimirElementoLista(&printers_list, position);
        printf("\033[1;32m");
        printf("\nImpresora eliminada correctamente! :)\n Lista actualizada de impresoras:");
        printf("\033[1;0m");
        print_list(printers_list);
        return;
    }
    position = siguienteLista(printers_list, position);
    }
    printf("\033[1;33m");
    printf("\nA impresora non esta na lista :(\n Por favor, selecione unha das seguintes impresoras: \n");
    printf("\033[1;0m");
    print_list(printers_list);
}

void add_printer(TLISTA printers_list, printers printer){
    
    insertarElementoLista(&printers_list, finLista(printers_list), printer);
    printf("\033[1;34m");
    printf("\n~*~*~*~*~ Lista de impresoras dispoñibles: ~*~*~*~*~");
    printf("\033[1;0m");
    print_list(printers_list);
}

void add_to_queue(TLISTA printers_list, char printerName[], TIPOELEMENTOCOLA documentID){
    printers printer;
    TPOSICION position = primeroLista(printers_list);
    // Bucle para iterar sobre a lista
    while(position != finLista(printers_list)){
        recuperarElementoLista(printers_list, position, &printer);
        // Condicional para atopar a impresora buscada (compara os nomes das impresoras)
        if (strcmp(printer.name, printerName) == 0){
            anadirElementoCola(&printer.queue, documentID);
        return;
    }
    position = siguienteLista(printers_list, position);
    }
    printf("\033[1;33m");
    printf("\n Non se atopou a impresora solicitada :(\n");
    printf("\033[1;0m");
}

void print_queue(TLISTA printers_list, char printerName[]){ 
    printers printer;
    TIPOELEMENTOCOLA documentID;
    TPOSICION position = primeroLista(printers_list);
    // Bucle para iterar sobre a lista
    while(position != finLista(printers_list)){
        recuperarElementoLista(printers_list, position, &printer);
        // Condicional para atopar a impresora buscada (compara os nomes das impresoras)
        if (strcmp(printer.name, printerName) == 0){
            // Creamos unha cola auxiliar para ir pasando os elementos e imprimilos
            TCOLA aux_queue;
            crearCola(&aux_queue);
            // Comprobamos que a cola non este vacia
            if (esColaVacia(printer.queue) == 1){
                printf("\033[1;33m");
                printf("\nA impresora %s non ten traballos pendentes de impresión.\n", printer.name);
                printf("\033[1;0m");
                return;
            }
            printf("\033[1;34m");
            printf("~*~*~*~*~ Lista de impresión de %s: ~*~*~*~*~\n", printer.name);
            printf("\033[0;34m");
            // Pasamos los elementos a una cola auxiliar para poder imprimirlos
            while(esColaVacia(printer.queue) == 0){
                consultarPrimerElementoCola(printer.queue, &documentID);
                printf("%d\n", documentID);
                suprimirElementoCola(&printer.queue);
                anadirElementoCola(&aux_queue, documentID);
            }
            printf("\033[1;0m");
            // Devolvemos los elementos a la cola inicial para poder almacenarlos
            while (esColaVacia(aux_queue) == 0){
                consultarPrimerElementoCola(aux_queue, &documentID);
                anadirElementoCola(&printer.queue, documentID);
                suprimirElementoCola(&aux_queue);
            }
        return;
    }
    position = siguienteLista(printers_list, position);
    }
    printf("\033[1;33m");
    printf("\nNon se atopou a impresora solicitada :(\n");
    printf("\033[1;0m");
}

void print_document(TLISTA printers_list, char printerName[]){
    printers printer;
    TIPOELEMENTOCOLA documentID;
    TPOSICION position = primeroLista(printers_list);
    // Bucle para iterar sobre a lista 
    while(position != finLista(printers_list)){
        recuperarElementoLista(printers_list, position, &printer);
        // Condicional para atopar a impresora buscada (compara os nomes das impresoras)
        if (strcmp(printer.name, printerName) == 0){
            // Comprobamos que a cola non este vacia
            if (esColaVacia(printer.queue) == 1){
                printf("\033[1;33m");
                printf("\nA impresora %s non ten traballos pendentes de impresión.\n", printer.name);
                printf("\033[1;0m");
                return;
            } else{
                consultarPrimerElementoCola(printer.queue, &documentID);
                printf("\033[1;32m");
                printf("O docuemnto %d acaba de ser impreso :)\n", documentID);
                printf("\033[1;0m");
                suprimirElementoCola(&printer.queue);
            }
        return;
    }
    position = siguienteLista(printers_list, position);
    }
    printf("\033[1;33m");
    printf("\nNon se atopou a impresora solicitada :(\n");
    printf("\033[1;0m");
}

void show_low_queue_printers(TLISTA printers_list){
    int counter = 1024;
    printers printer;
    TPOSICION position = primeroLista(printers_list);
    // Bucle que vai contando os elementos da cola (queue_elements) de cada impresora e gardandoos na estrutura printer
    while (position != finLista(printers_list)){
        recuperarElementoLista(printers_list, position, &printer);
        printer.queue_elements = count_queue_elements(printer.queue);
        if (printer.queue_elements<=counter)
            counter=printer.queue_elements;
        position = siguienteLista(printers_list, position);
    }
    printf("\033[1;34m");
    printf("\n~*~*~*~*~ Impresoras con menor carga de traballo: ~*~*~*~*~\n");
    printf("\033[0;34m");
    position = primeroLista(printers_list);
    while (position != finLista(printers_list)){
        recuperarElementoLista(printers_list, position, &printer);
        if (count_queue_elements(printer.queue)==counter)
            printf("%s \n", printer.name);
        position = siguienteLista(printers_list, position);
    }
    printf("\033[1;0m");
}

void safe_exit(TLISTA printers_list, char fileName[]){
    // Abrimos o arquivo
    FILE* printers_file = fopen(fileName, "w"); 
    if (printers_file == NULL){
        printf("\033[1;33m");
        perror("Erro ao abrir o arquivo :(\n");
        printf("\033[1;0m");
    }
    printers printer;
    TPOSICION position = primeroLista(printers_list);

    // Bucle para iterar sobre as impresoras
    while(position != finLista(printers_list)){
        recuperarElementoLista(printers_list, position, &printer);
        // Para escribirlas en el documento
        fprintf(printers_file,"%s %s %s %s\n", printer.name, printer.brand, printer.model, printer.location);
        position = siguienteLista(printers_list, position);
    }
    // Pechamos o arquivo
    fclose(printers_file);    
}

void free_memory(TLISTA printers_list){
    printers printer;
    TPOSICION position = primeroLista(printers_list);

    while(position != finLista(printers_list)){
        recuperarElementoLista(printers_list, position, &printer);
        destruirCola(&printer.queue);
        suprimirElementoLista(&printers_list, position);
    }
    destruirLista(&printers_list);
}
