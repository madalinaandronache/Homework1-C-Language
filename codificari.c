#include <stdio.h>
#include <string.h>

// returneaza caracterul aflat cu n pozitii dupa sau inainte,
// in functie de valoarea lui semn
char transfASCII(char c, int n, int semn) {
    if (semn == 1) {
        int nr = (int)c;
        if (65 <= nr && nr <= 90) {
            if (nr + n <= 90) {
                c = (char)(nr + n);
            } else {
                c = (char)(nr + n + 6);
            }
        } else if (97 <= nr && nr <= 122) {
            if (nr + n <= 122) {
                c = (char)(nr + n);
            } else {
                c = (char)(nr + n - 58);
            }
        }
    } else {
        int nr = (int)c;
        if (65 <= nr && nr <= 90) {
            if (nr - n < 65) {
                c = (char)(58 + nr - n);
            } else {
                c = (char)(nr - n);
            }
        } else if (97 <= nr && nr <= 122) {
            if (nr - n < 97) {
                c = (char)(nr - n - 6);
            } else {
                c = (char)(nr - n);
            }
        }
    }

    return c;
}

// rezolva codificarea B
void codifB(char *s, int n) {
    char p[500], aux[500];
    memset(p, 0, sizeof(p));
    memset(aux, 0, sizeof(aux));
    int semn = 1;
    strcpy(p, s + strlen(s) - n);
    for (int i = 0; i < strlen(p); i++) {
        if (p[i] != ' ') {
            p[i] = transfASCII(p[i], n, semn);
        }
    }
    strncpy(aux, s, strlen(s) - n);
    strcat(p, aux);
    strcpy(s, p);
}

// rezolva decodificarea B
void decodifB(char *s, int n) {
    char p[500], aux[500];
    memset(p, 0, sizeof(p));
    memset(aux, 0, sizeof(aux));
    strncpy(p, s, n);
    p[strlen(p)] = '\0';
    int semn = -1;
    strcpy(aux, s + n);
    for (int i = 0; i < strlen(p); i++) {
        if (p[i] != ' ') {
            p[i] = transfASCII(p[i], n, semn);
        }
    }
    strcat(aux, p);
    strcpy(s, aux);
}

// in aceasta functie se implementeaza sortarea pentru un
// sir de caractere v si se memoreaza in vectorul a, indicii corespunzatori
// pozitiei literelor din cuvantul initial
void sort(char *v, int n, int *a) {
    int aux1, i, j;
    char aux;

    for (int i = 0; i < n; i++) {
        a[i] = i;
    }

    for (int i = 1; i < n; i++) {
        a[i] = i;
    }

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if ((int)v[i] > (int)v[j]) {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                aux1 = a[i];
                a[i] = a[j];
                a[j] = aux1;
            }
        }
    }
}

// rezolva codificare A
void codifA(char *s, char *c) {
    int nr_l;
    int lgs = strlen(s);
    int lgc = strlen(c);
    int rez[50];

    char a[500][50];

    if (lgs % lgc == 0)
        nr_l = lgs / lgc;
    else
        nr_l = lgs / lgc + 1;

    int k = 0;

    for (int i = 1; i <= nr_l; i++) {
        for (int j = 1; j <= lgc; j++) {
            if (k < strlen(s))
                a[i][j] = s[k++];
            else
                a[i][j] = ' ';
        }
    }

    sort(c, lgc, rez);

    k = 0;

    for (int i = 0; i < lgc; i++) {
        for (int j = 1; j <= nr_l; j++) {
            if (k <= nr_l * lgc) s[k++] = a[j][rez[i] + 1];
        }
    }
    s[nr_l * lgc] = '\0';
}

// rezolva decodificarea A
void decodifA(char *s, char *c) {
    int nr_l;
    int lgs = strlen(s);
    int lgc = strlen(c);
    int rez[50];

    char a[500][50];

    if (lgs % lgc == 0)
        nr_l = lgs / lgc;
    else
        nr_l = lgs / lgc + 1;

    sort(c, lgc, rez);

    int k = 0;

    for (int j = 0; j < lgc; j++) {
        for (int i = 1; i <= nr_l; i++) {
            if (k < lgs)
                a[i][rez[j] + 1] = s[k++];
            else
                a[i][rez[j] + 1] = ' ';
        }
    }

    k = 0;

    for (int i = 1; i <= nr_l; i++) {
        for (int j = 1; j <= lgc; j++) {
            s[k++] = a[i][j];
        }
    }
    s[nr_l * lgc] = '\0';
}

int main() {
    int n;
    char s[500], cerinta[100], c[500];

    fgets(s, 500, stdin);
    s[strlen(s) - 1] = '\0';

    scanf("%s", cerinta);

    while (strcmp(cerinta, "STOP") != 0) {
        if (strcmp(cerinta, "CodificareB") == 0) {
            scanf("%d", &n);
            codifB(s, n);
            printf("%s\n", s);
        }
        if (strcmp(cerinta, "CodificareA") == 0) {
            getchar();
            fgets(c, 500, stdin);
            c[strlen(c) - 1] = '\0';
            codifA(s, c);
            printf("%s\n", s);
        }
        if (strcmp(cerinta, "DecodificareB") == 0) {
            scanf("%d", &n);
            decodifB(s, n);
            printf("%s\n", s);
        }
        if (strcmp(cerinta, "DecodificareA") == 0) {
            getchar();
            fgets(c, 500, stdin);
            c[strlen(c) - 1] = '\0';
            decodifA(s, c);
            printf("%s\n", s);
        }
        scanf("%s", cerinta);
    }
    return 0;
}