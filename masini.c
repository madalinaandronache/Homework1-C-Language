#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *brand;
    char *numar;
    char *combustibil;
    double consum;
    int km;
} masini;

// verifica daca un caracter este litera
int isalpha1(char c) {
    if (65 <= (int)c && (int)c <= 90) return 1;
    return 0;
}

// verifica daca un caracter este cifra
int isdigit1(char c) {
    if (48 <= (int)c && (int)c <= 57) return 1;
    return 0;
}

// rezolva cerinta A
void ceriA(masini *m, int n, int *nr) {
    int i;

    for (i = 0; i < n; i++) {
        if (strcmp(m[i].combustibil, "benzina") == 0) {
            nr[0]++;
        }
        if (strcmp(m[i].combustibil, "motorina") == 0) {
            nr[1]++;
        }
        if (strcmp(m[i].combustibil, "hibrid") == 0) {
            nr[2]++;
        }
        if (strcmp(m[i].combustibil, "electric") == 0) {
            nr[3]++;
        }
    }
}

// rezolva cerinta B
void ceriB(masini *m, int n, double *consum, double *pret) {
    for (int i = 0; i < n; i++) {
        consum[i] = (double)((m[i].consum * m[i].km) / 100);
        if (strcmp(m[i].combustibil, "benzina") == 0 ||
            strcmp(m[i].combustibil, "hibrid") == 0) {
            pret[i] = (double)(consum[i] * 8.02);
        } else {
            pret[i] = (double)(consum[i] * 9.29);
        }
    }
}

// rezolva cerinta C
void ceriC(masini *m, int n, int *v) {
    char nume[20];
    int ok = 1, i;
    for (i = 0; i < n; i++) {
        ok = 1;
        strcpy(nume, m[i].numar);
        if (isalpha1(nume[0]) == 1 && isdigit1(nume[1]) == 1 &&
            isdigit1(nume[2]) == 1) {
            if (isalpha1(nume[3]) == 1 && isalpha1(nume[4]) == 1 &&
                isalpha1(nume[5]) == 1 && nume[6] == '\0') {
                ok = 0;
            }
        }
        if (isalpha1(nume[0]) == 1 && isdigit1(nume[1]) == 1 &&
            isdigit1(nume[2]) == 1 && isdigit1(nume[3]) == 1 &&
            isalpha1(nume[4]) == 1 && isalpha1(nume[5]) == 1 &&
            isalpha1(nume[6]) && nume[7] == '\0') {
            ok = 0;
        }
        if (isalpha1(nume[0]) == 1 && isalpha1(nume[1]) == 1 &&
            isdigit1(nume[2]) == 1 && isdigit1(nume[3]) == 1) {
            if (isalpha1(nume[4]) == 1 && isalpha1(nume[5]) == 1 &&
                isalpha1(nume[6]) == 1 && nume[7] == '\0') {
                ok = 0;
            }
        }
        if (isalpha1(nume[0]) == 1 && isalpha1(nume[1]) == 1 &&
            isdigit1(nume[2]) == 1 && isdigit1(nume[3]) == 1 &&
            isdigit1(nume[4]) == 1) {
            if (isalpha1(nume[5]) == 1 && isalpha1(nume[6]) == 1 &&
                isalpha1(nume[7]) == 1 && nume[8] == '\0') {
                ok = 0;
            }
        }
        v[i] = ok;
    }
}

int main() {
    masini *m;
    int n, i, km;
    char brand[20], numar[20], combustibil[20], c;
    double consum;

    scanf("%d", &n);
    m = malloc(n * sizeof(masini));

    // aloc memorie dinamic pentru *m
    for (i = 0; i < n; i++) {
        scanf("%s", brand);
        m[i].brand = (char *)malloc((strlen(brand) + 1) * sizeof(char));
        strcpy(m[i].brand, brand);

        scanf("%s", numar);
        m[i].numar = (char *)malloc((strlen(numar) + 1) * sizeof(char));
        strcpy(m[i].numar, numar);

        scanf("%s", combustibil);
        m[i].combustibil =
            (char *)malloc((strlen(combustibil) + 1) * sizeof(char));
        strcpy(m[i].combustibil, combustibil);

        scanf("%lf", &consum);
        m[i].consum = consum;

        scanf("%d", &km);
        m[i].km = km;
    }
    getchar();
    scanf("%c", &c);

    // daca cerinta este a, afisez mesajele corespunzatoare
    if (c == 'a') {
        int nr[4];

        for (i = 0; i <= 3; i++) {
            nr[i] = 0;
        }

        ceriA(m, n, nr);

        printf("benzina - %d\n", nr[0]);
        printf("motorina - %d\n", nr[1]);
        printf("hibrid - %d\n", nr[2]);
        printf("electric - %d\n", nr[3]);
    }

    // daca cerinta este b, folosind 2 vectori *consum, *pret,
    // memorez pe pozitia i, consumul si pretul pentru fiecare masina
    if (c == 'b') {
        double *consum, *pret;
        char nume[110][20];
        consum = (double *)malloc(n * sizeof(double));
        pret = (double *)malloc(n * sizeof(double));

        ceriB(m, n, consum, pret);

        strcpy(nume[0], m[0].brand);

        int ok, j, k = 0, i = 1;

        // in variabila nume[][], memorez toate numele diferite de
        // masini care se gasesc in datele introduse
        while (i < n) {
            ok = 0;
            for (j = 0; j <= k; j++) {
                if (strcmp(nume[j], m[i].brand) == 0) {
                    ok = 1;
                }
            }
            if (ok == 0) {
                k++;
                strcpy(nume[k], m[i].brand);
            }
            i++;
        }

        double consum_total, pret_total;

        // afisez mesajele corespunzatoare cerintei
        for (i = 0; i <= k; i++) {
            consum_total = 0;
            pret_total = 0;
            for (j = 0; j < n; j++) {
                if (strcmp(m[j].brand, nume[i]) == 0) {
                    consum_total += consum[j];
                    pret_total += pret[j];
                }
            }

            printf("%s a consumat %.2lf - %.2lf lei\n", nume[i], consum_total,
                   pret_total);
        }
    }

    // daca cerinta este c, afisez mesajele corespunzatoare
    if (c == 'c') {
        int v[100], i, ok = 0;
        ceriC(m, n, v);
        for (i = 0; i < n; i++) {
            if (v[i] == 1) {
                for (int j = 0; j < strlen(m[i].brand); j++) {
                    printf("%c", m[i].brand[j]);
                }
                printf(" cu numarul %s: numar invalid\n", m[i].numar);
                ok = 1;
            }
        }
        if (ok == 0) {
            printf("Numere corecte!\n");
        }
    }
    return 0;
}
