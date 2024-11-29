#include <stdio.h>



void level2_b(){
    printf("[hello.c] level2_b\r\n");
}
void level2_a(){
    printf("[hello.c] level2_a\r\n");
}

void level1_a(){
    printf("[hello.c] level1_a\r\n");
    level2_a();
}
void level1_b(){
    printf("[hello.c] level1_b\r\n");
    level2_b();
}

void haha(){
    printf("[hello.c] haha\r\n");
}


int main(){
    printf("[hello.c]【start】hello world!\r\n");
    int n = 10;
    int m = 20;
    if(n > m){
        level1_a();
    }
    else{
        level1_b();
    }
    haha();
    printf("[hello.c]【end】hello world!\r\n");
    return 0;
}