/*
    BAUTISTA DE SUTO NAGY
    - ESTRUCTURAS
    - LISTAS ENLAZADAS
    - ORDENAMIENTO
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct productos{
    char nombre[256];
    int stock;
    float precio;
    struct productos *next;
    struct productos *prev;
}producto;

typedef producto *puntero;

puntero inventario = NULL;


//------------------------
puntero find(puntero inventario, char producto[256]){
   
    while(inventario!=NULL){
        if(strcmp(inventario->nombre, producto) == 0) return inventario;
        inventario=inventario->next;
    }
    return NULL;
}

void add(){
    char nombre[256];
    printf("ingrese el nombre del producto: ");      
    scanf("%s", nombre);
   
    puntero existe = find(inventario, nombre);
   
    if(existe == NULL){
        puntero p = malloc(sizeof(producto));
        p->next = NULL;
        p->prev = NULL;
       
        strcpy(p->nombre, nombre);
        printf("ingrese el stock: ");
        scanf("%d", &(p->stock));
       
        printf("ingrese el precio: ");
        scanf("%f", &(p->precio));
       
        p->next = inventario;
        if(inventario) inventario->prev = p;
        inventario = p;
       
    }else{
        int stock;        
        printf("ingrese el nuevo stock: ");
        scanf("%d", &stock);
        existe->stock+=stock;
    }
}

void look(puntero inventario){
    while(inventario!=NULL){
        printf("%s %d %.2f  \n", inventario->nombre, inventario->stock, inventario->precio);
        inventario=inventario->next;
       
    }
}


void sell(puntero producto, int cantidad){
    if(producto->stock >= cantidad){
       
        printf("precio total: %f$ \n", cantidad * producto->precio);
       
        int confirmar;
        printf("Por favor confirme la venta: ");      
        scanf("%d", &confirmar);

        if(confirmar){
            printf("Venta confimada");  
            producto->stock-=cantidad;
        }else{
            printf("Venta cancelada");
        }
       
    }else printf("No hay suficiente stock");
}

void ordenar(){
   
    while(inventario->next!=NULL){
        if( (inventario->next)->stock > inventario->stock ){
         
            puntero p1, p2, p3, p4;
            p1 = inventario->prev;
            p2 = inventario->next;
            p3 = inventario;
            p4 = (inventario->next)->next;
           
            p3->prev=p2;
            p3->next=p4;
           
            p2->prev=p1;
            p2->next=p3;
           
            if(p4) p4->prev=p3;
            if(p1) p1->next=p2;
           
            while(inventario->prev!=NULL) inventario = inventario->prev;
           
        }else inventario=inventario->next;
    }
    while(inventario->prev!=NULL) inventario = inventario->prev;
    look(inventario);

   
}


int main() {
    printf("Bienvenido\n1-Ver todos los productos \n2-Buscar producto \n3-Añadir producto \n4-Vender producto \n5-Ordenar producto \n");
    for(;;){
        int comando;
        char nombre[255];
        puntero producto;

        printf("Que quieres Hacer (ingrese el numero de la opcion):");  
        scanf("%d", &comando);

        switch (comando){
            case 1:
                look(inventario);
            break;
           

            case 2:
               
               
                printf("ingrese el nombre del producto: ");      
                scanf("%s", nombre);
               
                producto = find(inventario, nombre);
               
                if(producto == NULL) printf("El producto no existe");
                else printf("%s %d %.2f  \n", producto->nombre, producto->stock, producto->precio);
               

            break;

            case 3:
                add();
            break;

            case 4:
                printf("ingrese el nombre del producto: ");      
                scanf("%s", nombre);
               
                producto = find(inventario, nombre);
               
                if(producto == NULL) printf("El producto no existe");
                else{
                    int cantidad;
                    printf("ingrese la cantidada: ");
                    scanf("%d", &cantidad);
                    sell(producto, cantidad);
                   
                }
               
            break;

            case 5:
    
            ordenar();
           
            break;
   
            default:
                printf("Esa opcion no existe");
            break;
        }
       
        printf("\n\n");
    }
    return 0;
}