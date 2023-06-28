
#include<stdio.h>
#include<string.h>
int i=1,j=0,no=0,tmpch=90;
char str[100],left[15],right[15];
void findopr();
void explore();
void fleft(int);
void fright(int);
struct exp
{
    int pos;
    char op;
}k[15];

void main()
{
    
    printf("\t\tIntermediate code generation\n");
    printf("Enter the expression: ");
    scanf("%s",str);
    printf("The Intermediate code:\t\t Expression\n");
    findopr();
    explore();
    printf("\n");
}
void findopr(){
    for(i=0;str[i]!='\0';i++)
    if(str[i]==':'){
        k[j].pos=i;
        k[j++].op=':';
    }
    
    for(i=0;str[i]!='\0';i++)
    if(str[i]=='/'){
        k[j].pos=i;
        k[j++].op='/';
    }
    for(i=0;str[i]!='\0';i++)
    if(str[i]=='*'){
        k[j].pos=i;
        k[j++].op='*';
    }
    for(i=0;str[i]!='\0';i++)
    if(str[i]=='-'){
        k[j].pos=i;
        k[j++].op='-';
    }
    for(i=0;str[i]!='\0';i++)
    if(str[i]=='+'){
        k[j].pos=i;
        k[j++].op='+';
    }
}

void explore(){
    i=1;
    while(k[i].op!='\0'){
        fleft(k[i].pos);
        fright(k[i].pos);
        str[k[i].pos]=tmpch--;
        printf("\t %c:=%s%c%s\t\t",str[k[i].pos],left,k[i].op,right);
        for(j=0;j<strlen(str);j++)
        if(str[j]!='$')
        printf("%c",str[j]);
        printf("\n");
        i++;
    }
    fright(-1);
    if(no==0){
        fleft(strlen(str));
        printf("\t %s:=%s",right,left);
    }
    printf("\t %s:=%c",right,str[k[--i].pos]);

}

void fleft(int x){
    int w=0,flag=0;
    x--;
    while(x!=-1 && str[x]!='+' && str[x]!='*' && str[x]!='=' && str[x]!='\0' && str[x]!='-' && str[x]!='/' && str[x]!=':'){
        if(str[x]!='$' && flag==0)
        {
            left[w++]=str[x];
            left[w]='\0';
            str[x]='$';
            flag=1;
        }
        x--;
    }
}
void fright(int x){
    int w=0,flag=0;
    x++;
    while(x!=-1 && str[x]!='+' && str[x]!='*' && str[x]!='=' && str[x]!='\0' && str[x]!='-' && str[x]!='/' && str[x]!=':'){
        if(str[x]!='$'&& flag==0)
        {
            right[w++]=str[x];
            right[w]='\0';
            str[x]='$';
            flag=1;
        }
        x++;
    }
}

/*
OUTPUT:
-------
                 Intermediate code generation
Enter the expression: w:=a+b*c/d
The Intermediate code:           Expression
         Z:=c/d         w:=a+b*Z
         Y:=b*Z         w:=a+Y
         X:=a+Y         w:=X
         w:=X    w:=$
*/
