#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;


//Setting the i-th bit to either 1 or 0
//Bit i will be set if val is 1, and cleared if x is 0

int setBit(int i, char val, int bits);
int getBit(int i, int val);

int setBit(int i, char val, int bits){


    if(val == 1){
        int a =1;

        a = a << i;  

        bits = bits | a;

    }

    if(val == 0){
        int a = 1;

        a = a << i;  

        a = ~a;

        bits = bits & a; 
    }

    return bits;
}

int getBit(int i, int val){

    val = val & ( 1 << i );

    if(val == 0){
        return 0;
    }
    else if(val > 0){
        return 1;
    }
}

int main(){

    int size = 5;

    char c[size];

    c[0] = 7;
    c[1] = 1;
    c[2] = 5;
    c[3] = 2;
    c[4] = 3;
    c[5] = 7;


    char d[2] = {};
    int j = 2;
    int num = 0;
    int ch = 0;

    while(num < 5+1){
        for(int i = 7; i >= 0; j--, i--){
            d[ch] = setBit(i, getBit(j, c[num]), d[ch]);
            
            if(j == 0){
                num++;
                j = 3;
            }
        }
        ch++;
    }

    FILE* ptrFile = fopen ("text" , "wb");

    fwrite(d, 1, sizeof(d+1), ptrFile ); // записать в файл содержимое буфера
    fclose (ptrFile);


    ptrFile = fopen( "text" , "rb" );

    if (ptrFile == NULL){
        fputs("Ошибка файла!!!!!\n", stderr);
        exit(1);
    }

    // определяем размер файла
    fseek(ptrFile , 0 , SEEK_END);                          // устанавливаем позицию в конец файла
    long lSize = ftell(ptrFile);                            // получаем размер в байтах
    rewind (ptrFile);                                       // устанавливаем указатель в конец файла

    char buffer[lSize];
    if (buffer == NULL){
        fputs("Ошибка памяти!!!\n", stderr);
        exit(2);
    }

    size_t result = fread(buffer, 1, lSize, ptrFile); 
    if (result != lSize){
        fputs("Ошибка чтения!!!!\n", stderr);
        exit (3);
    }

    fclose (ptrFile); 





    num = 0;
    char newc[100] = {0};

    ch = 0;

    while(num < 2+1){//количество чисел в buffer
        for(int i = 7; i >= 0; j--, i--){//идем по битам в каждом числе

            newc[ch] = setBit(j, getBit(i, buffer[num]), newc[ch]); // берем биты и записываем в последние три бита каждого числа
            
            if(j == 0){;
                ch++;
                j = 3;
            }
        }
        num++;
    }

    for(int i = 0; i < 6; i++){ 
        cout << (int)newc[i] << endl;
    }


    return 0;

}
