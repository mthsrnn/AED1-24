#include <stdio.h>

int romanToInt(char* s) {
    int i = 0, j, valor = 0;
    int valores[15];

    while(s[i] != '\0'){
        switch(s[i]) {
            case 'I':
                valores[i] = 1;
                i++;
                break;
            case 'V':
                valores[i] = 5;
                i++;               
                break;
            case 'X':
                valores[i] = 10;
                i++;
                break;
            case 'L':
                valores[i] = 50;
                i++;
                break;
            case 'C':
                valores[i] = 100;
                i++;
                break;
            case 'D':
                valores[i] = 500;
                i++;
                break;
            case 'M':
                valores[i] = 1000;
                i++;
                break;
        }
    }
    for(j = 0; j < i; j++){
        if(j + 1 <= i && valores[j+1] > valores[j]){
            valor -= valores[j];
            continue;
        }
        valor += valores[j];
    }
    return valor;
}

int main(int argc, char *argv[])
{
  printf("%d", romanToInt("VIII"));
  return 0;
}
