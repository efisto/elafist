/*Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
#define MAX_LENGTH (1024)


struct _stackElement;
typedef struct _stackElement* Position;
typedef struct _stackElement {
    double number;
    Position next;
} StackElement;


int calculatePostfixFromFile(Position head, char* fileName, double* result);
int readFile(char* fileName, char* buffer);
int parseStringIntoPostfix(Position head, char* buffer, double* result);
int checkStackAndExtractResult(Position head, double* result);
Position createStackElement(double number);
int push(Position head, Position newStackElement);
int printStack(Position first);
int pop(Position head, double* result);
int popAndPerformOperation(Position head, char operation, double* result);

int main() {
    StackElement head = { .number = 0, .next = NULL };
    double result = 0;
    //ako se uspejsno konacno  izracuna i vrati 0, program ce se izvrsit i ipisatt
    if (calculatePostfixFromFile(&head, "postfix.txt", &result) == 0) {
        printf("Result is: %0.1lf\n", result);
    }

    return EXIT_SUCCESS;
}

int calculatePostfixFromFile(Position head, char* fileName, double* result) {
    char buffer[MAX_LENGTH] = { 0 };
    int status = 0;

    if (readFile(fileName, buffer) != 0 || !buffer) {
        return 0;
    }

    status = parseStringIntoPostfix(head, buffer, result);
    if (status != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int readFile(char* fileName, char* buffer) {
    FILE* filePointer = NULL;


    filePointer = fopen(fileName, "r");

    if (!filePointer) {
        perror("Can't open file!\n");//uloga ovoga, inace?
        return NULL;
    }

    fgets(buffer, MAX_LENGTH, filePointer);//ako je dobro ucitano kroz if, nek procita liniju i ispise
    printf("|%s|\n", buffer);

    fclose(filePointer);

    return 0;
}

int parseStringIntoPostfix(Position head, char* buffer, double* result)
{
    char* currentBuffer = buffer;
    int status = 0;
    int numBytes = 0;
    char operation = 0;
    double number = 0.0;
    Position newStackElement = NULL;

    while (strlen(currentBuffer) > 0) {
        status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);//funlcija ce vracat 1 ako uspjesno procita
        if (status != 1) {
            sscanf(currentBuffer, " %c %n", &operation, &numBytes);
            status = popAndPerformOperation(head, operation, result);

            if (status != EXIT_SUCCESS) //funkcija ce se izvrsit ako je popfunkc vratila 1
            {
                return EXIT_FAILURE;
            }

            number = *result;
        }

        newStackElement = createStackElement(number);
        if (!newStackElement) {
            return EXIT_FAILURE;
        }

        currentBuffer += numBytes;
        printf("|%s| <-->", currentBuffer);
        push(head, newStackElement);
    }

    return checkStackAndExtractResult(head, result);
}

int checkStackAndExtractResult(Position head, double* result) {
    int status = EXIT_SUCCESS;

    status = pop(head, result);

    if (status != EXIT_SUCCESS) {
        return status;
    }

    if (head->next) {
       
        printf("Invalid postfix, please check the file!\r\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

Position createStackElement(double number)
{
    Position newStackElement = NULL;

    newStackElement = (Position)malloc(sizeof(StackElement));//napravljen prsorotr za novi elem +provjera
    if (!newStackElement)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    newStackElement->number = number;//postavljanje date na novi eelement
    newStackElement->next = NULL;

    return newStackElement;
}

int push(Position head, Position newStackElement) 
{
    newStackElement->next = head->next;
    head->next = newStackElement;

    printStack(head->next);

    return EXIT_SUCCESS;//1
}

int printStack(Position first)
{
    Position current = first;

    while (current) {
        printf(" %0.1lf", current->number);
        current = current->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int pop(Position head, double* result) //fukcija za brisnaje elemenata sa stoga POP
{
    Position toDelete = NULL;

    toDelete = head->next;//brisem sljedecie clan
    if (!toDelete)//ako je stack prazana vrati -1, izadi iz funkcije
    {
        printf("Stack is empty! Nothing to pop!\n");
        return -1;
    }
    //brisanje clana i spajanje s postifixom rezultatq
    head->next = toDelete->next;
    *result = toDelete->number;
    free(toDelete);

    return EXIT_SUCCESS;
}

int popAndPerformOperation(Position head, char operation, double* result) {
    double operand1 = 0;
    double operand2 = 0;
    int status1 = 0;
    int status2 = 0;

    status1 = pop(head, &operand1);
    if (status1 != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    status2 = pop(head, &operand2);
    if (status2 != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    switch (operation) {
    case '+':
        *result = operand2 + operand1;
        break;
    case '-':
        *result = operand2 - operand1;
        break;
    case '*':
        *result = operand2 * operand1;
        break;
    case '/':
        if (operand1 != 0)
        {
            puts("errrro");
            return EXIT_FAILD;
        }
        *result = operand2 / operand1;
        break;
    default:
        printf("Operation %c not supported yet!\r\n", operation);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}