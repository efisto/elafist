#include <stdio.h>
#include <stdlib.h>

struct osoba{
    int yearofbirth;
    char surname[50];
    char name[50];

    struct osoba next;
};

int main()
{
    struct osoba head={.next = NULL,.name =NULL};

        int odabir = 0;

        scanf("%d",&odabir);

        switch(odabir){
            case A:
        }


}