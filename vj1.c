#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define max_br_bod 10

typedef struct student{
    char ime[MAX];
    char prez[MAX];
    int bodovi;
} stud;

int main()
{
    FILE *fp=NULL;
    int i;
    stud *st=NULL;
    int br=1;
    char c;
    int rl=0;
    
    fp=fopen("dat1.txt","r");

    if(fp == NULL){
        printf("Ne moze se otvoriti datoteka ");
        return 1;
    }

    do{
        c =fgetc(fp);
        if( c=='\n') br++;

    }while(c != EOF);
    

    for(i=0;i<br;i++){
        fscanf(fp,"%s %s %d",st[i].ime, st[i].prez, &st[i].bodovi );
    }

    for(i=0;i<br;i++){
        rl=(st[i].bodovi*100)/max_br_bod;
        printf("%s %s %d %d",st[i].ime, st[i].prez, st[i].bodovi ,rl );
    }

    fclose(fp);
    free(st);
    return 0;


}