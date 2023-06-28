// Implementation of Finding a Left Factoring

#include <stdio.h>
#include <string.h>

int main() {
    char gram[20], part1[20], part2[20], modifiedGram[20];
    int i, k = 0, pos = 0;
    printf("Enter Production : A -> ");
    scanf("%s", gram);
    sscanf(gram, "%[^|]|%s", part1, part2);
    for (i = 0; part1[i] == part2[i]; i++) {
        modifiedGram[k++] = part1[i];
        pos = i + 1;
    }
    printf("\nA -> %sX", modifiedGram);
    printf("\nX -> %s|%s\n", &part1[pos],&part2[pos]);
    return 0;
}

/*
OUTPUT:
------

Enter Production : A -> aAb|aAc

A -> aAX
X -> b|c

Enter Production : A -> abA|Aab

A -> X
X -> abA|Aab
*/
