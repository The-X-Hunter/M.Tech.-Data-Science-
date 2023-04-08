#include<stdio.h>

int print(int sequence[], int numberOfElements){
    int i;
    for(i = 0; i < numberOfElements; i++){
        printf("%d\t", sequence[i]);
    }
    printf("\n");
    return 0;
}

int sort_0(int sequence[], int numberOfElements, int m){
    int i, j, temp;
    if(m > 0){
        for(i = 0; i < numberOfElements - m; i++){
            j = i + m;
            temp = sequence[j];
            while(j > i){
                if(sequence[i] > sequence[j]){
                    sequence[j] = sequence[i];
                    j = j - m;
                } else {
                    break;
                }
            }
            if(j == i){
                sequence[j] = temp;
            }
        }
        print(sequence, 8);
        sort(sequence, numberOfElements, m / 2);
    }
    return 0;
}

int sort(int sequence[], int numberOfElements, int m){
    int i, j, temp;
    if(m > 0){
        for(i = m; i < numberOfElements - m; i++){
            temp = sequence[i];
            j = i;
            while(j >= 0){
                if(temp > sequence[j]){
                    sequence[j + m] = sequence[j];
                    j = j - m;
                } else {
                    break;
                }
            }
            sequence[j + m] = temp;
        }
        print(sequence, 8);
        sort(sequence, numberOfElements, m / 2);
    }
    return 0;
}

int main(){
    int sequence[] = {20, 35, 18, 8, 14, 41, 3, 39};
    print(sequence, 8);
    sort(sequence, 8, 8 / 2);
    print(sequence, 8);
    return 0;
}
