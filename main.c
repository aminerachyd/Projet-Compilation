#include <stdio.h>

// Déclaration des classes lexicales
typedef enum {
    ID_TOKEN,
    NUM_TOKEN,
    PROGRAM_TOKEN,
    CONST_TOKEN,
    VAR_TOKEN,
    BEGIN_TOKEN,
    END_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    READ_TOKEN,
    WRITE_TOKEN,
    PV_TOKEN,
    PT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIR_TOKEN,
    AFF_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    FIN_TOKEN,
    ERREUR_TOKEN
} CODES_LEX;

// Déclaration de la structure du symbole courant, contient le code du symbole ( TOKEN ) et le nom du symbole
typedef struct {
    CODES_LEX CODE;
    char NOM[20];
} TSym_Cour;
// Caractère courant, lit le fichier
char Car_Cour;

// Méthodes pour la lecture de chaque symbole

void Lire_nombre() {

}

void Lire_mot() {

}

void Lire_chaine() {

}

void Lire_special() {

}

void Lire_errone() {

}

void Ouvrir_Fichier(char PATH[50]){
    FILE *fp = fopen("pascal.p", "r");
}

int main() {
    // Le fichier à lire, on met le code pascal dedans
    FILE *fp = fopen("pascal.p", "r");

    // Test si le fichier n'existe pas
    if (fp == NULL) {
        printf("Not found");
        return 0;
    }

    // Le fichier existe, on procède par sa lecture
    do {
        // Lecture d'un caractère du fichier
        Car_Cour = fgetc(fp);

        // Vérification si on a ateint la fin du fichier
        if (feof(fp))
            break;
        if (Car_Cour>31) // Test si le caractère n'est pas un séparateur
            printf("%c\n", Car_Cour);
    } while (1);
    return 0;
}
