
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


class producto{
    public:
        string nombre;
        int stock;
        float precio;

        producto(string n, int s, float p);
        producto();
        void show();

        void operator = (producto data){
            nombre = data.nombre;;
            stock = data.stock;
            precio = data.precio;
        }
};

producto::producto(string n, int s, float p){
    nombre = n;
    stock = s;
    precio = p;
}

producto::producto(){
    nombre = "";
    stock = 0;
    precio = 0;
}

void producto::show(){
    cout << nombre << " " << stock << " " << precio << "$ \n" ;
}


class lista{
    private:
    vector<producto> array;

    public:
    
    producto* operator [] (int index){
        return &array[index];
    }
    
    producto* operator [] (string name){

        for(int i = 0; i < array.size(); i++) if(array[i].nombre == name) return &array[i];
        return NULL;
    }


    void show();
    void push(producto data);

    void upload(string adress);
    void download(string adress);

};

void lista::show(){
    for(int i = 0; i < array.size(); i++) array[i].show();
}

void lista::push(producto data){
    array.push_back(data);
}

void lista::download(string adress){
    
    fstream db(adress);

    producto data;

    string precio;
    string stock;

    while(getline(db, data.nombre)){

        getline(db, precio);
        data.precio = stof(precio);

        getline(db, stock);
        data.stock = stoi(stock);

        array.push_back(data);
    }
}

void lista::upload(string adress){
    fstream db(adress);
    for(int i = 0; i < array.size(); i++) db << array[i].nombre << "\n" << array[i].precio << "\n" << array[i].stock << "\n";
}