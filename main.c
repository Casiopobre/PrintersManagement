#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cola.h"
#include "lista.h"
#include "printeadoras.h"

// NOTA: todos os printf("\033[(num1);(num2)m") teñen proposito unicamente estetico (cambian a cor do texto)

int main(int argc, char *argv[]){
    char p_name[50];
    int doc_ID;
    char option;
    TLISTA printers_list;
    crearLista(&printers_list);
    printers printer;

    // Comprobamos que o nome do arquivo se pase por linea de comandos
    if(argc != 2){
        printf("\nNumero de argumentos incorrecto. TRY AGAIN :)\n");
        return 0;
    }

    // Lemos o arquivo e guardamos os datos nunha lista
    read_file(argv[1], &printers_list);

    do{
        printf("\033[1;35m");
        printf("\n--------------------------------------------------------");
        printf("\n~*~*~*~*~*~*~*~ Seleccione unha opción ~*~*~*~*~*~*~*~\n");
        printf("\na) Eliminar impresora\n");
        printf("\nb) Engadir impresora\n");
        printf("\nc) Enviar traballo\n");
        printf("\nd) Ver listado de traballos pendentes de impresión\n");
        printf("\ne) Imprimir traballo\n");
        printf("\nf) Buscar impresoras con pouca carga\n");
        printf("\ns) Saír\n");
        printf("--------------------------------------------------------\n");
        printf("\033[1;0m");
        printf("\nOpcion:");
        scanf(" %c", &option);
        switch (option){
            case 'a':
                printf("Introduza o nome da impresora a eliminar: ");
                scanf("%s", p_name);

                del_printer(&printers_list, p_name);
                break;

            case 'b':
                printf("Introduza o nome da impresora nova: \n");
                scanf("%s", printer.name);
                printf("Introduza a marca da impresora nova: \n");
                scanf("%s", printer.brand);
                printf("Introduza o modelo da impresora nova: \n");
                scanf("%s", printer.model);
                printf("Introduza a ubicacion da impresora nova: \n");
                scanf("%s", printer.location);
                crearCola(&printer.queue);
                printer.queue_elements = 0;
                add_printer(&printers_list, printer);
                break;
            case 'c':
                printf("Introduza o nome da impresora a enviar o traballo: \n");
                scanf("%s", p_name);
                printf("Introduza o codigo numerico do traballo a enviar: \n");
                scanf("%d", &doc_ID);
                add_to_queue(&printers_list, p_name, doc_ID);
                break;
            case 'd':
                printf("Introduza o nome da impresora da que quere coñecer a cola de impresion: \n");
                scanf("%s", p_name);
                print_queue(&printers_list, p_name);
                break;
            case 'e':
                printf("Introduza o nome da impresora que quere por a imprimir: \n");
                scanf("%s", p_name);
                print_document(&printers_list, p_name);
                break;
            case 'f':
                show_low_queue_printers(&printers_list);
                break;
            case 's':
                safe_exit(&printers_list, argv[1]);
                printf("\033[1;32m");
                printf("\nSaindo do programa . . . \n");
                printf("\033[1;0m");
                free_memory(printers_list);
                break;
            default:
                printf("\033[1;33m");
                printf(" Opcion inválida. Porfavor tenteo de novo :)");
                printf("\033[1;0m");
                break;
        }
    } while(option != 's');
    
    return(EXIT_SUCCESS);
}
