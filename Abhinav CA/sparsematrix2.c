#include <stdio.h>

void convertToTuple(int a[10][10], int m, int n, int tuple[100][3]) {
    int k = 1;
    tuple[0][0] = m;
    tuple[0][1] = n;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                tuple[k][0] = i;
                tuple[k][1] = j;
                tuple[k][2] = a[i][j];
                k++;
            }
        }
    }

    tuple[0][2] = k - 1; 
}


void printTuple(int tuple[100][3]) {
    int count = tuple[0][2];
    printf("Row\tCol\tVal\n");
    for (int i = 0; i <= count; i++) {
        printf("%d\t%d\t%d\n", tuple[i][0], tuple[i][1], tuple[i][2]);
    }
}


void sumTuples(int a[100][3], int b[100][3], int result[100][3]) {
    if (a[0][0] != b[0][0] || a[0][1] != b[0][1]) {
        printf("Matrices are not of the same size. Cannot add.\n");
        result[0][2] = 0;
        return;
    }

    int i = 1, j = 1, k = 1;
    result[0][0] = a[0][0];
    result[0][1] = a[0][1];

    while (i <= a[0][2] && j <= b[0][2]) {
        if (a[i][0] == b[j][0] && a[i][1] == b[j][1]) {
            result[k][0] = a[i][0];
            result[k][1] = a[i][1];
            result[k][2] = a[i][2] + b[j][2];
            i++; j++; k++;
        }
        else if ((a[i][0] < b[j][0]) || (a[i][0] == b[j][0] && a[i][1] < b[j][1])) {
            result[k][0] = a[i][0];
            result[k][1] = a[i][1];
            result[k][2] = a[i][2];
            i++; k++;
        }
        else {
            result[k][0] = b[j][0];
            result[k][1] = b[j][1];
            result[k][2] = b[j][2];
            j++; k++;
        }
    }

   
    while (i <= a[0][2]) {
        result[k][0] = a[i][0];
        result[k][1] = a[i][1];
        result[k][2] = a[i][2];
        i++; k++;
    }
    while (j <= b[0][2]) {
        result[k][0] = b[j][0];
        result[k][1] = b[j][1];
        result[k][2] = b[j][2];
        j++; k++;
    }

    result[0][2] = k - 1;
}


void transposeTuple(int a[100][3], int b[100][3]) {
    b[0][0] = a[0][1];
    b[0][1] = a[0][0];
    b[0][2] = a[0][2];

    int k = 1;
    for (int col = 0; col < a[0][1]; col++) {
        for (int i = 1; i <= a[0][2]; i++) {
            if (a[i][1] == col) {
                b[k][0] = a[i][1];
                b[k][1] = a[i][0];
                b[k][2] = a[i][2];
                k++;
            }
        }
    }
}


int main() {
    int a[10][10], b[10][10];
    int m, n, m1, n1;
    int sa[100][3], sb[100][3], sum[100][3], trans[100][3];

    
    printf("Enter rows and columns of first matrix: ");
    scanf("%d %d", &m, &n);
    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    
    printf("Enter rows and columns of second matrix: ");
    scanf("%d %d", &m1, &n1);
    if (m1 != m || n1 != n) {
        printf("Matrices must be of same dimensions for addition.\n");
        return 1;
    }
    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < m1; i++)
        for (int j = 0; j < n1; j++)
            scanf("%d", &b[i][j]);

    
    convertToTuple(a, m, n, sa);
    convertToTuple(b, m1, n1, sb);

    printf("\nTuple format of first matrix:\n");
    printTuple(sa);
    printf("\nTuple format of second matrix:\n");
    printTuple(sb);

    
    sumTuples(sa, sb, sum);
    printf("\nSum of the matrices (tuple form):\n");
    printTuple(sum);

    
    transposeTuple(sum, trans);
    printf("\nTranspose of the result (tuple form):\n");
    printTuple(trans);

    return 0;
}
