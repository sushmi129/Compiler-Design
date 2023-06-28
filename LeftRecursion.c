// Implement Elimination of Left Recursion

#include<stdio.h>
#include<string.h>
#include<stdbool.h> 

void ELR(char s[]) {
	int p=0,i,j;
	for(i=0;i<strlen(s);i++)
		if(s[i]=='|')
			p++;
	char s1[p+1][100];
	int idx1=0,idx2=0;
	int count[p+1],c=0;
	for(i=3;i<strlen(s);i++) {
		if(s[i]=='|') {
			count[idx1++]=c;
			c=0; idx2=0;
		} else {
			s1[idx1][idx2++]=s[i];
			c++;
		}
	}
	count[idx1]=c;
	bool isLR =false;
	for(i=0;i<=p;i++) {
		if(s[0]==s1[i][0]) {
		    isLR=true; break;
		}
	}
	if(!isLR) {
		printf("Given production %s is not in left recursion\n",s);
		return;
	}
	printf("After elimination of left recursion \n");
	int f=0;
	printf("%c->",s[0]);
	for(i=0;i<=p;i++) {
		if(s[0]!=s1[i][0]) {
			if(f)
			   printf("|");
			for(j=0;j<count[i];j++)
				printf("%c",s1[i][j]);
			printf("%c'",s[0]);
			f=1;
		}
	}
	printf("\n%c'->",s[0]);
	for(i=0;i<=p;i++) {
		if(s[0]==s1[i][0]) {
			for(j=1;j<count[i];j++)
				   printf("%c",s1[i][j]);
		    printf("%c'|",s[0]);
		}
	}
	printf("E\n");
}

void main() {
	char s[100];
	int n;
	printf("Enter no of productions : ");
	scanf("%d",&n);
	while(n--) {
		printf("Enter the Production in the form(A->A@|B) : ");
		scanf("%s",s);
		printf("The Production is : %s\n",s);
		ELR(s);
	}
}

/*

Enter no of productions : 5
Enter the Production in the form(A->A@|B) : A->A+B|B
The Production is : A->A+B|B
After elimination of left recursion 
A->BA'
A'->+BA'|E
Enter the Production in the form(A->A@|B) : A->Ab|aB|Ac|aC
The Production is : A->Ab|aB|Ac|aC
After elimination of left recursion 
A->aBA'|aCA'
A'->bA'|cA'|E
Enter the Production in the form(A->A@|B) : f->id
The Production is : f->id
Given production f->id is not in left recursion
Enter the Production in the form(A->A@|B) : S->S+(T)|T
The Production is : S->S+(T)|T
After elimination of left recursion 
S->TS'
S'->+(T)S'|E
Enter the Production in the form(A->A@|B) : S->S*T|T
The Production is : S->S*T|T
After elimination of left recursion 
S->TS'
S'->*TS'|E
   
*/
