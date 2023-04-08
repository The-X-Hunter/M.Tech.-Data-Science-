#include<stdio.h>

/*int main(){
    int a[] = {3, 4, 5};
    int k = 2;
    int queries[] = {1, 2};
    int i, j;
    int n = 3;
    int temp;
    for(i = 0; i < k; i++){
        temp = a[n - 1];
        for(j = n - 2; j >= 0; j--) {
            a[(j + 1) % n] = a[j];
        }
        a[0] = temp;
    }
    for(i = 0; i < n; i++){
        j = (i + 2) % n;
        temp = a[j];
        
    }
    for(i = 0; i < n; i++){
        printf("%d\t", a[i]);
    }
    printf("\n");
    return 0;
}*/

int main(){
    int n = 3, k = 2;
    int a[n] = {3, 4, 5};
    int e[k];
    int queries = {1, 2};
    int i;
    for(i = n - 1; i >= n - k; i--){
    }
    return 0;
}
