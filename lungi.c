#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// transforma un char in numarul int reprezentat de caracter
int transf_char_int(char c) {
    int nr = (int)c - 48;
    return nr;
}

// transforma un numar int in caracterul reprezentat de numar
char transf_int_char(int nr) {
    char c = (char)(nr + 48);
    return c;
}

// memoreza in a[i] rezultatul adunarii dintre numarul a[i] si b[i]
// si in variabila plus elementul care se va aduna la urmatoarea operatie
// daca suma depaseste 10.
void adunare_numere(char *a, char *b, int i, int *plus) {
    int nr1, nr2, s;
    nr1 = transf_char_int(a[i]);
    nr2 = transf_char_int(b[i]);
    s = nr1 + nr2 + *plus;
    if (s < 10) {
        a[i] = transf_int_char(s);
        *plus = 0;
    } else if (s >= 10) {
        a[i] = transf_int_char(s - 10);
        *plus = 1;
    }
}

// memoreza in a[i] rezultatul scaderii dintre numarul a[i] si b[i], cand
// numarul memorat in a este mai mare decat numarul memorat in b,
// si in variabila plus elementul care se va aduna la urmatoarea operatie
// daca diferenta este mai mica decat 0.
void scadere_numereab(char *a, char *b, int i, int *plus) {
    int nr1, nr2, s;
    nr1 = transf_char_int(a[i]);
    nr2 = transf_char_int(b[i]);
    s = nr1 - nr2 + *plus;
    if (0 <= s && s < 10) {
        a[i] = transf_int_char(s);
        *plus = 0;
    } else if (s < 0) {
        a[i] = transf_int_char(10 + s);
        *plus = -1;
    }
}

// memoreza in a[i] rezultatul scaderii dintre numarul a[i] si b[i], cand
// numarul memorat in b este mai mare decat numarul memorat in a,
// si in variabila plus elementul care se va aduna la urmatoarea operatie
// daca diferenta este mai mica decat 0.
void scadere_numereba(char *a, char *b, int i, int *plus) {
    int nr1, nr2, s;
    nr1 = transf_char_int(a[i]);
    nr2 = transf_char_int(b[i]);
    s = nr2 - nr1 + *plus;
    if (0 <= s && s < 10) {
        a[i] = transf_int_char(s);
        *plus = 0;
    } else if (s < 0) {
        a[i] = transf_int_char(10 + s);
        *plus = -1;
    }
}
// scade partile reale ale numerelor atunci cand numarul real memorat in a
// este mai mare decat numarul real memorat in b
void scadere_realeab(char *a, char *b, int n) {
    int plus = 0, i;
    for (i = (n - 1) / 2 - 1; i > 0; i--) {
        scadere_numereab(a, b, i, &plus);
    }
}

// scade partile imaginare ale numerelor atunci cand numarul imaginar
// memorat in a este mai mare decat numarul imaginar memorat in b
void scadere_imaginarab(char *a, char *b, int n) {
    int plus = 0, i;
    for (i = (n - 2); i > (n - 1) / 2; i--) {
        scadere_numereab(a, b, i, &plus);
    }
}

// scade partile reale ale numerelor atunci cand numarul real memorat in b
// este mai mare decat numarul real memorat in a
void scadere_realeba(char *a, char *b, int n) {
    int plus = 0, i;
    for (i = (n - 1) / 2 - 1; i > 0; i--) {
        scadere_numereba(a, b, i, &plus);
    }
}

// scade partile imaginare ale numerelor atunci cand numarul imaginar
// memorat in b este mai mare decat numarul imaginar memorat in a
void scadere_imaginarba(char *a, char *b, int n) {
    int plus = 0, i;
    for (i = (n - 2); i > (n - 1) / 2; i--) {
        scadere_numereba(a, b, i, &plus);
    }
}

// calculeaza rezultatul obtinut prin adunarea partilor reale si imaginare
// ale numerelor memorate in sirurile a si b. In functie de bitul de semn
// al acestora se apeleaza functia care realizeaza operatia corecta
void calcul(char *a, char *b, int n) {
    int i, plus;
    char a1[1010], b1[1010];

    if ((a[0] == '0' && b[0] == '0') || (a[0] == '1' && b[0] == '1')) {
        plus = 0;
        for (i = (n - 1) / 2 - 1; i > 0; i--) {
            adunare_numere(a, b, i, &plus);
        }
    }

    if ((a[(n - 1) / 2] == '0' && b[(n - 1) / 2] == '0') ||
        (a[(n - 1) / 2] == '1' && b[(n - 1) / 2] == '1')) {
        plus = 0;
        for (i = (n - 2); i > (n - 1) / 2; i--) {
            adunare_numere(a, b, i, &plus);
        }
    }

    if (a[0] == '0' && b[0] == '1') {
        strncpy(a1, a + 1, (n - 1) / 2);
        a1[strlen(a1)] = '\0';

        strncpy(b1, b + 1, (n - 1) / 2);
        b1[strlen(b1)] = '\0';

        if (strcmp(a1, b1) == 0) {
            for (i = 0; i < (n - 1) / 2; i++) {
                a[i] = '0';
            }
        }
        if (strcmp(a1, b1) > 0) {
            a[0] = '0';
            scadere_realeab(a, b, n);
        }
        if (strcmp(a1, b1) < 0) {
            a[0] = '1';
            scadere_realeba(a, b, n);
        }
    } else if (a[0] == '1' && b[0] == '0') {
        strncpy(a1, a + 1, (n - 1) / 2 - 1);
        a1[strlen(a1)] = '\0';

        strncpy(b1, b + 1, (n - 1) / 2 - 1);
        b1[strlen(b1)] = '\0';

        if (strcmp(a1, b1) == 0) {
            for (i = 0; i < (n - 1) / 2; i++) {
                a[i] = '0';
            }
        }
        if (strcmp(a1, b1) > 0) {
            a[0] = '1';
            scadere_realeab(a, b, n);
        }
        if (strcmp(a1, b1) < 0) {
            a[0] = '0';
            scadere_realeba(a, b, n);
        }
    }

    if (a[(n - 1) / 2] == '0' && b[(n - 1) / 2] == '1') {
        strcpy(a1, a + (n - 1) / 2 + 1);
        strcpy(b1, b + (n - 1) / 2 + 1);

        if (strcmp(a1, b1) == 0) {
            for (i = (n - 1) / 2; i < strlen(a); i++) {
                a[i] = '0';
            }
        }
        if (strcmp(a1, b1) > 0) {
            a[(n - 1) / 2] = '0';
            scadere_imaginarab(a, b, n);
        }
        if (strcmp(a1, b1) < 0) {
            a[(n - 1) / 2] = '1';
            scadere_imaginarba(a, b, n);
        }
    } else if (a[(n - 1) / 2] == '1' && b[(n - 1) / 2] == '0') {
        strcpy(a1, a + (n - 1) / 2 + 1);
        strcpy(b1, b + (n - 1) / 2 + 1);

        if (strcmp(a1, b1) == 0) {
            for (i = (n - 1) / 2; i < strlen(a); i++) {
                a[i] = '0';
            }
        }
        if (strcmp(a1, b1) > 0) {
            a[(n - 1) / 2] = '1';
            scadere_imaginarab(a, b, n);
        }
        if (strcmp(a1, b1) < 0) {
            a[(n - 1) / 2] = '0';
            scadere_imaginarba(a, b, n);
        }
    }
}

// se citesc de la tastatura sirurile si operatia corespunzatoare
// pana cand se intalneste caracterul '0' pentru operatie.
// Daca operatia este minus, se schimba biti de semn ai sirului b
// si se realizeaza operatia de adunare intre a si b
int main() {
    int n;
    char a[1010], b[1010], operatie;

    scanf("%d", &n);
    getchar();

    fgets(a, 1002, stdin);
    a[strlen(a) - 1] = '\0';

    scanf("%c", &operatie);
    getchar();

    while (operatie != '0') {
        fgets(b, 1002, stdin);
        b[strlen(b) - 1] = '\0';

        if (operatie == '+') {
            calcul(a, b, n);
            printf("%s\n", a);
        }
        if (operatie == '-') {
            if (b[0] == '0') {
                b[0] = '1';
            } else {
                b[0] = '0';
            }

            if (b[(n - 1) / 2] == '0') {
                b[(n - 1) / 2] = '1';
            } else {
                b[(n - 1) / 2] = '0';
            }

            calcul(a, b, n);
            printf("%s\n", a);
        }
        scanf("%c", &operatie);
        getchar();
    }

    return 0;
}
