/*
    BAUTISTA DE SUTO NAGY
    - CLASES
    - ARCHIVOS 
    - PUNTERO A FUNCIONES 

*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <WinUser.h>

#include "Clases.cpp"

using namespace std;

lista inventario;

void show(){

    cout << "NOMBRE STOCK PRECIO\n";
    inventario.show();

 
}

void closelook(){
    string name;
    cout << "Ingrese el nombre del producto: ";
    cin >> name;
    cout << "NOMBRE STOCK PRECIO\n";
    if(inventario[name]) inventario[name]->show();
    else cout << "Este producto no exisite";  
}

void add(){
    string name;
    int stock;
    int price;

    cout << "Ingrese el nombre del producto: ";
    cin >> name;

    if (inventario[name]){
        
        cout << "Ingrese nuevo del stock del producto: ";
        cin >> stock;
        inventario[name]->stock += stock; 

    }else{
        cout << "Ingrese el precio del producto: ";
        cin >> price;
        cout << "Ingrese el stock del producto: ";
        cin >> stock;

        producto dato(name, stock, price);
        inventario.push(dato);
    }

    inventario.upload("db.txt");
}

void sell(){
    string name;
    int cantidad;
    bool confirmar;

    cout << "Ingrese el nombre del producto: ";
    cin >> name;

    if(inventario[name]){

        cout << "Ingrese la cantidada: ";
        cin >> cantidad;

        if(inventario[name]->stock < cantidad) cout << "No hay suficiente stock";
        else{
            cout << "Precio total: " << cantidad * inventario[name]->precio << "$" << "\nPor favor confirme la venta:";           
            cin >> confirmar;
            if(confirmar){
                cout << "Venta confimada";
                inventario[name]->stock -= cantidad;
                inventario.upload("db.txt");
            }else cout << "Venta cancelada";
        }

    }else cout << "El producto no existe";
}


void getout(){
    cout << "\nAprete ESC par volver al menu"; 
    while(1)if(GetKeyState(VK_ESCAPE) & 0x8000)break;
    system("CLS");
}

void (*(ESTADO[4]))() = {&show, &closelook, &add, &sell};

int main(){
    
    int comando;
    inventario.download("db.txt");

    while(1){        
        cout << "Bienvenido\n1-Ver todos los productos\n2-Buscar producto\n3-Añadir producto\n4-Vender producto\n\n";
        cout << "\nQue quieres hacer ahora:";
        cin >> comando;
        cout << "\n";    
        system("CLS");
        if(comando < 5 && comando > 0){
            ESTADO[comando-1]();
            getout();
        }
    }
    return 0;

}