#include <stdio.h>
#include <stdlib.h>

struct term{
	int coeff;
	int expo;
};

struct poly {
     int n;
	 struct term *t;
};

void create(struct poly*);
void display(struct poly);
struct poly* addPoly(struct poly *, struct poly *);
int max(struct poly);
struct poly* mulPoly(struct poly *, struct poly *);
int main(int argc, char *argv[])
{
	struct poly p1, p2, *addp, *multp;
	int n;
	create(&p1);	
	create(&p2);
	
	display(p1);	
	printf("\n%d is max\n",max(p1));
	display(p2);
	printf("\n%d is max\n",max(p2));
	addp=addPoly(&p1, &p2);
	display(*addp);	
	multp=mulPoly(&p1, &p2);
	display(*multp);	
	return 0;
}

void create(struct poly *temp){
	int i;
	printf("Enter the terms(non-zero)	: ");
    scanf("%d",&temp->n);

	temp->t=(struct term*)malloc(temp->n*sizeof(struct term));

	for (i=0;i<temp->n;i++) {
		printf("\nEnter term	: %d",i);
		printf("\nEnter coeff	: ");
        scanf("%d",&temp->t[i].coeff);
		printf("Enter expo	: ");
        scanf("%d",&temp->t[i].expo);	     
	}
	printf("\n");
}

void display(struct poly temp){
	int i;
	printf("Given Polynomical is	: ");
	for (i=0;i<temp.n;i++) {
	     if(temp.t[i].expo !=0 && temp.t[i].expo !=1)
			 printf("%dx^%d +",temp.t[i].coeff, temp.t[i].expo);
		 else if(temp.t[i].expo ==1)
			 printf("%dx +",temp.t[i].coeff);
		 else if(temp.t[i].coeff !=0)
			printf("%d",temp.t[i].coeff);
	}
	printf("\n");
}
int max(struct poly temp){
	int i, n=temp.t[0].expo;
	for (i=1;i<temp.n;i++) {
	     if(n <temp.t[i].expo)
			 n=temp.t[i].expo;
	}
		 return(n);
}
struct poly* addPoly(struct poly *p1, struct poly *p2){
	int i=0, j=0, k=0;
	struct poly *p3 =(struct poly*)malloc(sizeof(struct poly));
	p3->n=p1->n+p2->n;
	p3->t=(struct term*)malloc(p3->n*sizeof(struct term));

	while(i<p1->n&&j<p2->n){
	    printf("%d * %d, %d * %d\n", p1->t[i].coeff, p1->t[i].expo, p2->t[j].coeff, p2->t[j].expo);
		if(p1->t[i].expo > p2->t[j].expo){
			p3->t[k]=p1->t[i];
			i++;
			k++;
		}
		else if(p2->t[j].expo > p1->t[i].expo){
			p3->t[k]=p2->t[j];
			j++;
			k++;
		}
		else{
			p3->t[k].expo=p1->t[i].expo;
			p3->t[k].coeff=p1->t[i].coeff+p2->t[j].coeff;
			i++;
			k++;
			j++;
		}
	}
	for (;i<p1->n;i++) {	     
			p3->t[k]=p1->t[i];
			//i++;
			k++;
	}
	for (;j<p2->n;j++) {
			p3->t[k]=p2->t[j];
			//j++;
			k++;
	}
	return(p3);
}

struct poly* mulPoly(struct poly *p1, struct poly *p2){
	int i=0, j=0, k=0;
	struct poly *multp, *p3, *p4;
	while(i<p1->n) {
		p4=(struct poly*)malloc(sizeof(struct poly));
		p4->n=p2->n;
		p4->t=(struct term*)malloc(p4->n*sizeof(struct term));
		for (j=0;j<p2->n;j++) {
		     p4->t[j].coeff=p1->t[i].coeff*p2->t[j].coeff;
			 p4->t[j].expo=p1->t[i].expo+p2->t[j].expo;			 
		}
		if(i==0){
			p3=p4;
		}else {
		    multp=addPoly(p3, p4);
			p3=multp;			
		}		
		i++;
	}
	return(p3);
}
