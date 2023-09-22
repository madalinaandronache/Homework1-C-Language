#include <stdio.h>

// returneaza pentru prizonierul i, numarul regasit la pasul nr.
int cutii(int *v, int nr, int i) {
    if (nr == 1) return v[i];
    return v[cutii(v, nr - 1, i)];
}

// rezolva cerinta A, verificand daca fiecare prizonier
// ajunge in maxim n/2 pasi la numarul sau corespunzator
void cerintaA(int *a, int n) {
    int i, j, ok, ok2 = 0;
    for (i = 1; i <= n; i++) {
        ok = 0;
        for (j = 1; j < (n + 1) / 2; j++) {
            if (cutii(a, j, i) == i) {
                ok = 1;
                break;
            }
        }
        if (ok == 0) {
            printf("Nu\n");
            ok2 = 1;
            break;
        }
    }

    if (ok2 == 0) {
        printf("Da\n");
    }
}

// rezolva cerinta B, verificand pentru fiecare dintre cei n
// prizonieri daca genereaza un ciclu si nu a fost anterior afisat,
// afisand fiecare ciclu nou gasit.
void cerintaB(int *a, int n) {
    int i, j, b[501];

    for (i = 1; i <= n; i++) {
        b[i] = 0;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (cutii(a, j, i) == i) {
                break;
            }
        }
        if (b[i] == 0) {
            if (j == 1)
                printf("%d\n", i);
            else
                printf("%d ", i);

            b[i] = 1;

            for (int k = 1; k < j; k++) {
                b[cutii(a, k, i)] = 1;
                if (k != j - 1)
                    printf("%d ", cutii(a, k, i));
                else
                    printf("%d\n", cutii(a, k, i));
            }
        }
    }
}


// citeste datele initiale ale problemei si apeleaza functiile
// care rezolva cerintele A si B.
int main() {
    int n, a[501];

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    cerintaA(a, n);
    cerintaB(a, n);

    return 0;
}
