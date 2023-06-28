// Implement Lexical Analzer

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100

enum TokenType {
    NUMBER, ID, KEYWORD, SYMBOL, OPERATOR, ERROR,
};

const char *TokenTypeStrings[] = {
    "NUMBER","ID","KEYWORD","SYMBOL","OPERATOR","ERROR",
};

struct Token {
    enum TokenType type;
    char value[MAX_TOKEN_LEN];
};
int isKeyword(const char *str) {
    static const char *keywords[] = {
        "auto","break","case","char","const","continue","default","do",
        "double","else","enum","extern","float","for","goto","if",
        "int","long","register","return","short","signed","sizeof",
        "static","struct","switch","typedef","union","unsigned","void",
        "volatile","while"
    };
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(keywords[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

struct Token getNextToken(const char *input, int *start) {
    int len = strlen(input);
    int lineIndex = 0;
    char c = input[*start];
    while (*start < len) {
        if (isspace(c)) {
            (*start)++;
            c = input[*start];
            continue;
        }
        if (isdigit(c)) {
            struct Token t = {NUMBER, ""};
            do {
                t.value[lineIndex++] = c;
                (*start)++;
                c = input[*start];
            } while (isdigit(c));
            return t;
        }
        if (isalpha(c)) {
            struct Token t = {ID, ""};
            do {
                t.value[lineIndex++] = c;
                (*start)++;
                c = input[*start];
            } while (isalnum(c));
            t.type = isKeyword(t.value) ? KEYWORD : ID;
            return t;
        }
        if (ispunct(c)) {
            struct Token t = {SYMBOL, ""};
            t.value[lineIndex++] = c;
            (*start)++;
            t.type = strchr("+-*/%><=", c) != NULL? OPERATOR : SYMBOL;
            return t;
        }
        struct Token t = {ERROR, ""};
        t.value[lineIndex++] = c;
        (*start)++;
        return t;
    }
    struct Token t = {EOF, ""};
    return t;
}
int main() {
    char input[1000];
    printf("Enter a string: ");
    scanf("%[^\n]s", input);
    int start = 0;
    struct Token t;
    while ((t = getNextToken(input, &start)).type != EOF) {
        printf("%s : %s\n", t.value, TokenTypeStrings[t.type]);
    }
    return 0;
}

/*
OUTPUT :
--------------
Enter a string: void main(){ int a = b*c; return; }
void : KEYWORD
main : ID
( : SYMBOL
) : SYMBOL
{ : SYMBOL
int : KEYWORD
a : ID
= : OPERATOR
b : ID
* : OPERATOR
c : ID
; : SYMBOL
return : KEYWORD
; : SYMBOL
} : SYMBOL
*/

