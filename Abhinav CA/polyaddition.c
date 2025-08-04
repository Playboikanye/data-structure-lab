#include <stdio.h>

struct Term {
    int coeff;
    int expo;
};

void readpoly(struct Term p[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Term %d:\n  Coefficient: ", i + 1);
        scanf("%d", &p[i].coeff);
        printf("  Exponent: ");
        scanf("%d", &p[i].expo);
    }
}

void displaypoly(struct Term p[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%dx^%d", p[i].coeff, p[i].expo);
        if (i < count - 1)
            printf(" + ");
    }
    printf("\n");
}

int addpoly(struct Term p1[], int n1, struct Term p2[], int n2, struct Term result[]) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (p1[i].expo > p2[j].expo) {
            result[k++] = p1[i++];
        } else if (p1[i].expo < p2[j].expo) {
            result[k++] = p2[j++];
        } else {
            result[k].coeff = p1[i].coeff + p2[j].coeff;
            result[k].expo = p1[i].expo;
            i++; j++; k++;
        }
    }
    while (i < n1)
        result[k++] = p1[i++];
    while (j < n2)
        result[k++] = p2[j++];
    return k;
}

int main() {
    struct Term p1[20], p2[20], result[40];
    int deg1, deg2;

    printf("Enter the degree of the first polynomial:\n");
    scanf("%d", &deg1);
    printf("Enter the terms of the first polynomial:\n");
    readpoly(p1, deg1 + 1); 
    printf("Enter the degree of the second polynomial:\n");
    scanf("%d", &deg2);
    printf("Enter the terms of the second polynomial:\n");
    readpoly(p2, deg2 + 1);

    printf("The first polynomial is:\n");
    displaypoly(p1, deg1 + 1);

    printf("The second polynomial is:\n");
    displaypoly(p2, deg2 + 1);

    int res_terms = addpoly(p1, deg1 + 1, p2, deg2 + 1, result);

    printf("The result polynomial after addition is:\n");
    displaypoly(result, res_terms);

    return 0;
}
