// Implementation of Operator Precedence Parsing

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char input[50];
int i=0;
char lasthandle[6],stack[50],handles[][5]={")E(","E*E","E+E","i","E^E"};

int top=0,l;
char prec[4][4]={
        '>', '<','<','>',
        '>', '>','<','>',
        '>', '>','>','>',
        '<', '<','<','>'};


int getindex(char c) {
        switch(c) {
                case '+':return 0;
                case '*':return 1;
                case 'i':return 2;
                case '$':return 3;
        }
}

int shift() {
        stack[++top]=input[i++];
        stack[top+1]='\0';
}

int reduce() {
        int i,len,found,t;
        for(i=0;i<5;i++) {
                len=strlen(handles[i]);
                if(stack[top]==handles[i][0]&&top+1>=len) {
                        found=1;
                        for(t=0;t<len;t++) {
                                if(stack[top-t]!=handles[i][t]) {
                                        found=0;
                                        break;
                                }
                        }
                        if(found==1) {
                                stack[top-t+1]='E';
                                top=top-t+1;
                                strcpy(lasthandle,handles[i]);
                                stack[top+1]='\0';
                                return 1;//successful reduction
                        }
                }
        }
        return 0;
}

void dispstack() {
        int j;
        for(j=0;j<=top;j++)
                printf("%c",stack[j]);
}

void dispinput() {
        int j;
        for(j=i;j<l;j++)
                printf("%c",input[j]);
}

void main() {
        int j;
        printf("\nEnter the string : ");
        scanf("%s",input);
        strcat(input,"$");
        l=strlen(input);
        strcpy(stack,"$");
        printf("\nSTACK\tINPUT\tACTION");
	printf("\n-----\t-----\t------\n");
        while(i<=l) {
                shift();
                printf("\n");
                dispstack();
                printf("\t");
                dispinput();
                printf("\tShift");
                if(prec[getindex(stack[top])][getindex(input[i])]=='>') {
                        while(reduce()) {
                                printf("\n");
                                dispstack();
                                printf("\t");
                                dispinput();
                                printf("\tReduced: E->%s",lasthandle);
                        }
                }
        }

        if(strcmp(stack,"$E$")==0)
                printf("\nAccepted\n");
        else
                printf("\nNot Accepted\n");
}

/*
OUTPUT:
------
Enter the string : i*i+i

STACK   INPUT   ACTION
-----   -----   ------

$i      *i+i$   Shift
$E      *i+i$   Reduced: E->i
$E*     i+i$    Shift
$E*i    +i$     Shift
$E*E    +i$     Reduced: E->i
$E      +i$     Reduced: E->E*E
$E+     i$      Shift
$E+i    $       Shift
$E+E    $       Reduced: E->i
$E      $       Reduced: E->E+E
$E$             Shift
$E$             Shift
Accepted

*/
