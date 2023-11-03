#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct osoba;

typedef struct osoba *pozicija;

struct osoba{
    int yearofbirth;
    char surname[50];
    char name[50];
    pozicija Next;

};


void unosIspred(pozicija p){
    pozicija q;

        q=(pozicija)malloc(sizeof(struct osoba));
        printf("Unesite podatke o osobi");
        scanf("%s %s %d", q->name, q->surname, q->yearofbirth);

        q->Next= p->Next;
        p->Next= q;
}

void ispis(pozicija p){
    if(NULL ==p)
        printf("Pogreska\n");
    else{
        printf("Ispis liste:\n");
        while(p !=NULL){
            printf("%s %s %d\n\t",p->name,p->surname,p->yearofbirth);
            p=p->Next;
        }
    }
}

pozicija unosIza(pozicija p){
    while(NULL != p->Next)
        p=p->Next;
        return p;
}

pozicija pronadi(pozicija p){
    char pr[50];

    printf("Unesi prezime osobe da je pronades");
    scanf("%s", pr);

    while(p != NULL && strcmp(p->surname, pr) != 0)
            p=p->Next;

            return p;
}

pozicija pronIspred(pozicija p){
    char pr[50];

    if(NULL == p->Next)
        p=NULL;
    else{
    printf("Unesi prezime osobe da je pronades");
    scanf("%s", pr);

    while(strcmp(p->Next->surname, pr)!=0 && p->Next->Next != NULL);
            p=p->Next;

    if(strcmp(p->Next->surname, pr)!=0)
        p=NULL;        
    }
    return p;
}
void izbrisi(pozicija p){
    pozicija ispred;
    ispred=pronIspred(p);
    if(NULL !=ispred){
        p=ispred->Next;
        ispred->Next =p->Next;
        printf("Osoba je obrissana");
        free(p);
    }
    else 
        printf("Greska pri brisanju");
}

void citajIzDat(pozicija p){
    FILE *fp;
    char dat[50];
    pozicija temp;

    printf("Unesi ime datoteke koju ucitavas");
    scanf(" %s", dat);

    fp=fopen(dat, "r");

    if(NULL == fp)
        printf("Greska");
        else{
            while(feof(fp)==0)
            {
                temp=(pozicija)malloc(sizeof(struct osoba));

                fscanf(fp,"%s %s %d", temp->name, temp->surname, temp->yearofbirth);

                temp->Next=p->Next;
                p->Next=temp;
                p=temp;
            }
            fclose(fp);
        }
}

int main()
{
    struct osoba Head, *p;
    pozicija temp;
    Head.Next=NULL;


        char odabir = 0;
        printf("Unesi a-za unos elemenata na pocetak\n\tb-za ispis niza\n\tc-za unos elemenata na kraj\n\td-za pronalazak prezimena\n\te-za brisanje elementa iz niza\n\tf-dodaj novi element iza odredenog\n\tg-dodaj novi element nakon odredenog\n\th-citaj listu iz datoteke\n\t");
        scanf("%s",&odabir);

        switch(odabir){
            case 'A':
            case 'a':
                unosIspred(&Head);
                break;
            case 'b':
            case 'B':
                ispis(Head.Next);
                break;
            case 'c':
            case 'C':
              p=unosIza(&Head);
                unosIspred(p);
                break;  
            case 'd':
            case 'D':
                p=pronadi(Head.Next);
                if(NULL == p)
                    printf("Greska u pretrazi");
                else 
                    printf("%s %s %d",p->name,p->surname,p->yearofbirth);     
                break;
            case 'e':
            case 'E':
                izbrisi(&Head);
                break;
            case 'f':
            case 'F':
                p=pronadi(Head.Next);
                if(NULL ==p)
                    printf("Greska u trazenju");
                else 
                    unosIspred(p);
                    break;
            case 'g':
            case 'G':
                p= pronIspred(&Head);
                if(NULL==p)
                    printf("Greska pri trazenju");
                else 
                    unosIspred(p);
                    break;   
            case 'h':
            case 'H':
                citajIzDat(&Head);
                break;                
            default:
                printf("Greska");
        }

 
    }
 