#include <stdio.h>

char Car_Cour; // caractère courant

int main() {
    FILE *fp = fopen("amine.txt", "r");
    if (fp == NULL) {
        printf("not found");
        return 0;
    }

    do {
        // Lecture d'un caractère du fichier
        Car_Cour = fgetc(fp);

        // Vérification si on a ateint la fin du fichier
        if (feof(fp))
            break;

        printf("%c\n", Car_Cour);
    } while (1);
    return 0;
}
