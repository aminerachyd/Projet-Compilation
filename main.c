#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    EG_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    EOF_TOKEN,
    ERREUR_TOKEN,
    NULL_TOKEN
} CODES_LEX;

// Déclaration des erreurs
typedef enum {
    ID_ERR,
    NUM_ERR,
    PROGRAM_ERR,
    CONST_ERR,
    VAR_ERR,
    BEGIN_ERR,
    END_ERR,
    IF_ERR,
    THEN_ERR,
    WHILE_ERR,
    DO_ERR,
    READ_ERR,
    WRITE_ERR,
    PV_ERR,
    PT_ERR,
    PLUS_ERR,
    MOINS_ERR,
    MULT_ERR,
    DIV_ERR,
    VIR_ERR,
    AFF_ERR,
    EG_ERR,
    INF_ERR,
    INFEG_ERR,
    SUP_ERR,
    SUPEG_ERR,
    DIFF_ERR,
    PO_ERR,
    PF_ERR,
    ERR_CAR_INC,
    ERR_FICH_VID,
    CONST_VAR_BEGIN_ERR,
} ERREURS;

// Déclaration de la structure d'une erreur
typedef struct {
    ERREURS CODE_ERR;
    char mes[40]
} Erreurs;

// Déclaration de la structure du symbole courant, contient le code du symbole ( TOKEN ) et le nom du symbole
typedef struct {
    CODES_LEX CODE;
    char NOM[20];
} TSym_Cour;

void CONSTS();

void VARS();

void EXPR();

void AFFEC();

void TANTQUE();

void ECRIRE();

void LIRE();

void COND();

void SI();

void INST();

void INSTS();

void BLOCK();

void PROGRAM();

void RELOP();

void ADDOP();

void TERM();

void MULOP();

void FACT();

void ID();

void NUM();

void Chiffre();

void Lettre();

// Tableau des erreurs
Erreurs MES_ERR[100] = {{ERR_CAR_INC,  "caractère	inconnu"},
                        {ERR_FICH_VID, "fichier	vide", "« IDF	très	long"}};

// Tableau des enumérations
// Ce tableau sert uniquement à donner un équivalent en string des enumérations en haut
// Voir la fonction AfficherToken(sym_cour)
const char *enumName[] = {
        "ID_TOKEN",
        "NUM_TOKEN",
        "PROGRAM_TOKEN",
        "CONST_TOKEN",
        "VAR_TOKEN",
        "BEGIN_TOKEN",
        "END_TOKEN",
        "IF_TOKEN",
        "THEN_TOKEN",
        "WHILE_TOKEN",
        "DO_TOKEN",
        "READ_TOKEN",
        "WRITE_TOKEN",
        "PV_TOKEN",
        "PT_TOKEN",
        "PLUS_TOKEN",
        "MOINS_TOKEN",
        "MULT_TOKEN",
        "DIV_TOKEN",
        "VIR_TOKEN",
        "AFF_TOKEN",
        "EG_TOKEN",
        "INF_TOKEN",
        "INFEG_TOKEN",
        "SUP_TOKEN",
        "SUPEG_TOKEN",
        "DIFF_TOKEN",
        "PO_TOKEN",
        "PF_TOKEN",
        "EOF_TOKEN",
        "ERREUR_TOKEN"
};

// Caractère courant, lit le fichier
char Car_Cour;
TSym_Cour Sym_Cour;
FILE *fp;

void Erreur(ERREURS ERR) {
    int ind_err = ERR;
    printf("Erreur numéro %d \t	: %s \n", ind_err, MES_ERR[ind_err].mes);
    exit(1);
}

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
    memset(Sym_Cour.NOM, 0, 20);
    Sym_Cour.CODE = NULL_TOKEN;
    // On remplit le nom du numero
    for (int i = 0; i < 20; i++) {
        Sym_Cour.NOM[i] = Car_Cour;
        // Passage au prochain caractère
        Car_Cour = fgetc(fp);
        if (Car_Cour < 33 || !Car_is_number()) { // TODO traiter le cas de la virgule
            // Si le caractère n'est pas un nombre, on s'arrete
            break;
        }
    }
    Sym_Cour.CODE = NUM_TOKEN;
    return;
}

void Lire_mot() {
    memset(Sym_Cour.NOM, 0, 20);
    Sym_Cour.CODE = NULL_TOKEN;
    // On remplit le nom du mot
    for (int i = 0; i < 20; i++) {
        Sym_Cour.NOM[i] = Car_Cour;
        // Passage au prochain caractère
        Car_Cour = fgetc(fp);
        if (Car_Cour < 33 || Car_is_special()) {
            // Si le caractère est un séparateur, on s'arrete
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
    memset(Sym_Cour.NOM, 0, 20);
    Sym_Cour.CODE = NULL_TOKEN;
    // On remplit le nom du spécial
    for (int i = 0; i < 20; i++) {
        Sym_Cour.NOM[i] = Car_Cour;
        // Passage au prochain caractère
        Car_Cour = fgetc(fp);

        if (!strcmp(Sym_Cour.NOM, "(")) {
            Sym_Cour.CODE = PO_TOKEN;
            return;
        }
        if (!strcmp(Sym_Cour.NOM, ")")) {
            Sym_Cour.CODE = PF_TOKEN;
            return;
        }

        if (Car_Cour < 33 || !Car_is_special()) {
            // Si le caractère n'est pas un spécial, on s'arrete
            break;
        }
    }

    if (!strcmp(Sym_Cour.NOM, ";")) {
        Sym_Cour.CODE = PV_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, ".")) {
        Sym_Cour.CODE = PT_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, "+")) {
        Sym_Cour.CODE = PLUS_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, "-")) {
        Sym_Cour.CODE = MOINS_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, "*")) {
        Sym_Cour.CODE = MULT_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, "/")) {
        Sym_Cour.CODE = DIV_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, ",")) {
        Sym_Cour.CODE = VIR_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, ":=")) {
        Sym_Cour.CODE = AFF_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, "=")) {
        Sym_Cour.CODE = EG_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, "<")) {
        Sym_Cour.CODE = INF_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, "<=")) {
        Sym_Cour.CODE = INFEG_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, ">")) {
        Sym_Cour.CODE = SUP_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, ">=")) {
        Sym_Cour.CODE = SUPEG_TOKEN;
        return;
    }
    if (!strcmp(Sym_Cour.NOM, "<>")) {
        Sym_Cour.CODE = DIFF_TOKEN;
        return;
    }
    Sym_Cour.CODE = ERREUR_TOKEN;
    return;
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
            return;
        }
        if (Car_is_number()) {
            Lire_nombre();
            return;
        }
        if (Car_is_special()) {
            Lire_special();
            return;
        }
    } else {
        Car_Cour = fgetc(fp);
        memset(Sym_Cour.NOM, 0, 20);
        Sym_Cour.CODE = NULL_TOKEN;
        return;
    }
}

void AfficherToken(TSym_Cour sym_cour) {
    if (sym_cour.CODE != NULL_TOKEN)
        printf("%s\n", enumName[sym_cour.CODE]);
    if (Car_Cour == EOF)
        printf("%s\n", enumName[EOF_TOKEN]);
}

void Ouvrir_Fichier(char PATH[50]) {
    // Le fichier à lire, on met le code pascal dedans
    fp = fopen(PATH, "r");
}

// Fonction pour tester un symbole
void Test_Symbole(CODES_LEX CODE, ERREURS CODE_ERR) {
    if (Sym_Cour.CODE == CODE) {
        Sym_Suiv();
    } else
        Erreur(CODE_ERR);
}

//---------------------------------------------
// REGLES SYNTAXIQUES
//---------------------------------------------
void PROGRAM() {
    Test_Symbole(PROGRAM_TOKEN, PROGRAM_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(PV_TOKEN, PV_ERR);
    BLOCK();
    Test_Symbole(PT_TOKEN, PT_ERR);
}

void BLOCK() {
    CONSTS();
    VARS();
    INSTS();
}

void CONSTS() {
    switch (Sym_Cour.CODE) {
        case CONST_TOKEN:
            Sym_Suiv();
            Test_Symbole(ID_TOKEN, ID_ERR);
            Test_Symbole(EG_TOKEN, EG_ERR);
            Test_Symbole(NUM_TOKEN, NUM_ERR);
            Test_Symbole(PV_TOKEN, PV_ERR);
            while (Sym_Cour.CODE == ID_TOKEN) {
                Sym_Suiv();
                Test_Symbole(EG_TOKEN, EG_ERR);
                Test_Symbole(NUM_TOKEN, NUM_ERR);
                Test_Symbole(PV_TOKEN, PV_ERR);
            };
            break;
        case VAR_TOKEN:
            break;
        case BEGIN_TOKEN:
            break;
        default:
            Erreur(CONST_VAR_BEGIN_ERR);
            break;
    }
}

void VARS() {
    Test_Symbole(VAR_TOKEN, VAR_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    while (Sym_Cour.CODE == VIR_TOKEN) {
        Test_Symbole(ID_TOKEN, ID_ERR);
    }
    Test_Symbole(PV_TOKEN, PV_ERR);
}

void INSTS() {
    Test_Symbole(BEGIN_TOKEN, BEGIN_ERR);
    INST();
    while (Sym_Cour.CODE == PV_TOKEN) {
        INST();
    }
    Test_Symbole(END_TOKEN, END_ERR);
}

void INST() {   // TODO kifach tdir dak ORs, chi switch 3la SymCour.CODE
    INSTS();
    AFFEC();
    SI();
    TANTQUE();
    ECRIRE();
    LIRE();
}

void AFFEC() {
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(AFF_TOKEN, AFF_TOKEN);
    EXPR();
}

void SI() {
    Test_Symbole(IF_TOKEN, IF_ERR);
    COND();
    Test_Symbole(THEN_TOKEN, THEN_ERR);
    INST();
}

void TANTQUE() {
    Test_Symbole(WHILE_TOKEN, WHILE_ERR);
    COND();
    Test_Symbole(DO_TOKEN, DO_TOKEN);
    INST();
}

void ECRIRE() {
    Test_Symbole(WRITE_TOKEN, WRITE_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    EXPR();
    while (Sym_Cour.CODE == VIR_TOKEN) {
        EXPR();
    }
    Test_Symbole(PF_TOKEN, PF_ERR);
}

void LIRE() {
    Test_Symbole(READ_TOKEN, READ_TOKEN);
    Test_Symbole(PO_TOKEN, PO_ERR);
    ID();
    while (Sym_Cour.CODE == VIR_TOKEN) {
        ID();
    }
    Test_Symbole(PF_TOKEN, PF_ERR);
}

void COND() {
    EXPR();
    RELOP();
    EXPR();
}

void RELOP() {  // TODO dak le OR b un switch sur SymCour.CODE
    Test_Symbole(EG_TOKEN, EG_ERR);
    Test_Symbole(DIFF_TOKEN, DIFF_ERR);
    Test_Symbole(SUP_TOKEN, SUP_ERR);
    Test_Symbole(INF_TOKEN, INF_ERR);
    Test_Symbole(SUPEG_TOKEN, SUPEG_ERR);
    Test_Symbole(INFEG_TOKEN, INFEG_ERR);
}

void EXPR() {   // TODO remplacer le 1 par une condition
    TERM();
    while(1){
        ADDOP();
        TERM();
    }
}

void ADDOP() {  // TODO dak le OR b un switch
    Test_Symbole(PLUS_TOKEN,PLUS_ERR);
    Test_Symbole(MOINS_TOKEN,MOINS_ERR);
}

void TERM() { // TODO remplacer le 1 par une condition
    FACT();
    while(1){
        MULOP();
        FACT();
    }
}

void MULOP() {
    Test_Symbole(MULT_TOKEN,MULT_ERR);
    Test_Symbole(DIV_TOKEN,DIV_ERR);
}

void FACT() {   // TODO dak le OR b un switch
    ID();
    NUM();

    Test_Symbole(PO_TOKEN,PO_ERR);
    EXPR();
    Test_Symbole(PF_TOKEN,PF_ERR);
}

void ID() {
    Lettre();

    while(1){ // TODO remplacer 1 par une condition
        // TODO Or -> switch
        Lettre();
        Chiffre();
    }
}

void NUM() {
    Chiffre();
    while(1){ // TODO remplacer 1 par une condition
        Chiffre();
    }
}

void Chiffre() { // TODO pas sur ici
    Test_Symbole(NUM_TOKEN,NUM_ERR);
}

void Lettre() { // TODO lettre ??

}

int main() {
    Ouvrir_Fichier("pascal.p");
    /* Test de l'analyseur lexical
    Lire_Caractere();
    while (Car_Cour != EOF) {
        Sym_Suiv();
        AfficherToken(Sym_Cour);
    }*/






    return 0;
}
