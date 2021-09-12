#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fptr;
    fptr = fopen("testcase.txt","w");
    for (int i = 0; i < 3; i++) {
        fprintf(fptr, "%d ", rand()/10000);
    }
    fprintf(fptr, "%d\n", rand()/10000);

    /*for (int i = 0; i < 100; i++) {
        fprintf(fptr, "%d ", rand()/10000);
    }
    fprintf(fptr, "%d\n", rand()/10000);


    for (int i = 0; i < 30; i++) {
        fprintf(fptr, "%d ", rand()/10000);
    }
    fprintf(fptr, "%d\n", rand()/10000);

    /*for (int i = 0; i < 10000; i++) {
        fprintf(fptr, "%d ", rand());
    }
    fprintf(fptr, "%d\n", rand()/10000);*/
}