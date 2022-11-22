#include <iostream>
#include <string>
using namespace std;

class matrix{
   
    public:
        float* matriz;

        int row;
        int col;

        matrix(int r, int c); //constuctor

        float & operator () (int r, int c);

        matrix t(void); //matriz traspuesta
        matrix adj(void); //matriz de adjuntos
        float adj(int r, int c); //adjunto
        float det(void); //determinante

        void operator = (matrix data);
        void operator = (float* data);
        matrix operator + (matrix data);
        matrix operator * (matrix data);
        matrix operator * (float data);
        matrix operator ! (void); //matirz inversa

};

matrix::matrix(int r, int c){
    row = r;
    col = c;
    matriz = new float [r*c];

    
    for(int i = 0; i < row*col; i++) matriz[i] = 0;
}


float & matrix::operator () (int r, int c){
    if(r < row && c < col) return matriz[r*col + c];
}

void matrix::operator = (matrix data){
    if((data.row == row) && (data.col == col)) for(int i = 0; i < row*col; i++) matriz[i]=data.matriz[i];
}

void matrix::operator = (float* data){
    for(int i = 0; i < row*col; i++) matriz[i]=data[i];
}

matrix matrix::operator + (matrix data){
    matrix res(row, col);
    if(data.row == row && data.col == col) {
        for(int i = 0; i < row*col; i++) res.matriz[i]=matriz[i]+data.matriz[i];
        return res;
    }
}

matrix matrix::operator * (matrix data){
    if(data.row == col){
        matrix res(data.row, data.col);

        for(int r = 0; r < data.row; r++) for(int c = 0; c < data.col; c++){
            float num = 0;
            for(int i = 0; i < row; i++) num += this->operator()(r, i) * data(i, c); 
            res(r,c) = num;
        };
        return res; 
    
    }
}

matrix matrix::operator * (float data){
    matrix res(row, col); 
    for(int i = 0; i < row*col; i++) res.matriz[i]=matriz[i]*data;
    return res;
    
}

matrix matrix::operator ! (){
    if(col == row && this->det()) return this->t().adj() * (1/(this->det()));
}



matrix matrix::t(){
    matrix res(col,row);   
    for(int r = 0; r < col; r++) for(int c = 0; c < row; c++) res(r,c)=this->operator()(c,r);
    return res;
}

matrix matrix::adj(){
    if(col == row) {
        matrix res(col,row);
        for(int r = 0; r < row; r++) for(int c = 0; c < col; c++) res(r,c) = adj(r,c);
        return res;
    }
}

float matrix::adj(int i, int j){
    if(col == row){
        matrix adjs(row-1, col-1);
        for(int r = 0; r < row - 1; r++) for(int c = 0; c < col - 1; c++) adjs(r,c) = this->operator()((r<i?r:r+1),(c<j?c:c+1));   
        return (-2*((i+j)%2)+1) * adjs.det();
    }

}

float matrix::det(){
    if(col == row){
        if(col == 1 && row == 1) return this->operator()(0,0);
        else{
            float res = 0;
            for(int r = 0; r < row; r++) res += this->operator()(0,r) * this->adj(0,r); 
            return res;
        }
    }
}

ostream& operator<<(ostream& cout, matrix matriz){
    string res = "";
    for(int r = 0; r < matriz.row; r++){
        for(int c = 0; c < matriz.col; c++) res += to_string(matriz(r,c)) + " "; 
        res += "\n";    
    }   
    return cout << res; 
}