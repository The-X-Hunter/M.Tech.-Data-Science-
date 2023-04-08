#include<stdio.h>

int getMax(int sequence[], int numberOfElements, int key){
    int i, maxElem;
    for(i = 0; i < numberOfElements; i++){
        if(i % key == 0){
            maxElem = sequence[i];
        }
    }
    return 0;
}

int main(){
    int sequence[] = {20, 35, 18, 8, 14, 41, 3, 39};
    getMax(sequence, 8, 3);
    return 0;
}
