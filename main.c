#include <stdio.h>
#include <string.h>

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
TSym_Cour Sym_Cour;
FILE *fp;

// Vérification si Car_Cour est une lettre
int Car_is_letter() {
    return (Car_Cour < 91 && Car_Cour > 64) || (Car_Cour > 96 && Car_Cour < 122);
}

// Vérification si Car_Cour est un nombre
int Car_is_number() {
    return Car_Cour > 47 && Car_Cour < 58;
}

// Vérification si Car_Cour est un caractère spécial ( et pas seulement ceux que doit comprendre le compilateur )
int Car_is_special() {
    return Car_Cour > 32 && Car_Cour < 127 && !Car_is_letter() && !Car_is_number();
}

// Méthodes pour la lecture de chaque symbole
void Lire_nombre() {

}

void Lire_mot() {
    // On remplit le nom du mot
    for (int i = 0; i < 20; i++) {
        Sym_Cour.NOM[i] = Car_Cour;
        // Passage au prochain caractère
        Car_Cour = fgetc(fp);
        if (Car_Cour < 33) {
            break;
        }
    }
    if (!strcmp(Sym_Cour.NOM, "program")) {
        Sym_Cour.CODE = PROGRAM_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, "const")) {
        Sym_Cour.CODE = CONST_TOKEN;
        return;

    }
    if (!strcmp(Sym_Cour.NOM, "var")) {
        Sym_Cour.CODE = VAR_TOKEN;
        return;

    }
    if (!strcmp(Sym_Cour.NOM, "begin")) {
        Sym_Cour.CODE = BEGIN_TOKEN;
        return;

    }
    if (!strcmp(Sym_Cour.NOM, "end")) {
        Sym_Cour.CODE = END_TOKEN;
        return;

    }
    if (!strcmp(Sym_Cour.NOM, "if")) {
        Sym_Cour.CODE = IF_TOKEN;
        return;

    }
    if (!strcmp(Sym_Cour.NOM, "then")) {
        Sym_Cour.CODE = THEN_TOKEN;
        return;

    }
    if (!strcmp(Sym_Cour.NOM, "while")) {
        Sym_Cour.CODE = WHILE_TOKEN;
        return;

    }
    if (!strcmp(Sym_Cour.NOM, "do")) {
        Sym_Cour.CODE = DO_TOKEN;
        return;

    }
    if (!strcmp(Sym_Cour.NOM, "read")) {
        Sym_Cour.CODE = READ_TOKEN;
        return;

    }
    if (!strcmp(Sym_Cour.NOM, "write")) {
        Sym_Cour.CODE = WRITE_TOKEN;
        return;

    }
    Sym_Cour.CODE = ID_TOKEN;
}

void Lire_chaine() {

}

void Lire_special() {

}

void Lire_errone() {

}

void Lire_Caractere() {
    // Test si le fichier n'existe pas
    if (fp == NULL) {
        printf("File not found");
        return;
    }
    Car_Cour = fgetc(fp);
}


void Sym_Suiv() {
    // Test si le caractère n'est pas un séparateur
    if (Car_Cour > 32) {
        // Si le caractère est une lettre
        if (Car_is_letter()) {
            Lire_mot();
        }
        if (Car_is_number()) {
            Lire_nombre();
        }
        if (Car_is_special()) {
            Lire_special();
        }
    } else {
        Car_Cour = fgetc(fp);
        memset(Sym_Cour.NOM,0,20);
        return;
    }
}

void AfficherToken(TSym_Cour sym_cour) {
    printf("%d", sym_cour.CODE);
}

void Ouvrir_Fichier(char PATH[50]) {
    // Le fichier à lire, on met le code pascal dedans
    fp = fopen(PATH, "r");
}

int main() {
    Ouvrir_Fichier("pascal.p");
    Lire_Caractere();
    while (Car_Cour != EOF) {
        Sym_Suiv();
        AfficherToken(Sym_Cour);
    }
    return 0;
}
