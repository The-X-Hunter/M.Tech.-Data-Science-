#include<stdio.h>

int divide(int s[], int n, int d, int m, int div[]){
    int i, sum = 0, len = 0, w = 0;
    for(i = 0; i < n; i++){
        sum += s[i];
        len++;
        if(len == m){
            printf("%d, %d\n", sum, d);
            if(sum == d){
                div[w] = (i + 1) - m;
                w++;
            }
            sum -= s[i - 1];
            len--;
        }
    }
    return 0;
}

int main(){
    int i, n, d, m, s[n], div[n], way = 0;
    
    do {
        printf("Enter size of chocolate bar: ");
        scanf("%d", &n);
    } while(n < 1 || n > 100);
    
    printf("Enter integer values on bar pieces:\n");
    //for(i = 0; i < n; i++){
        //do {
            printf("Integer for piece %d: ", i + 1);
            //scanf("%d", &s[i]);
        //} while(s[i] < 1 || s[i] > 5);
    //}
    
    do {
        printf("Enter date of birth: ");
        scanf("%d", &d);
    } while(d < 1 || d > 31);
    
    do {
        printf("Enter month of birth: ");
        scanf("%d", &m);
    } while(m < 1 || m > 12);
    
    divide(s, n, d, m, div);
    /*printf("%d ways are there.\n", way);
    for(i = 0 ; i < way; i++){
        printf("%d:%d, %d:%d\n", div[i], s[div[i]], div[i] + 1, s[div[i] + 1]);
    }*/
    return 0;
}
