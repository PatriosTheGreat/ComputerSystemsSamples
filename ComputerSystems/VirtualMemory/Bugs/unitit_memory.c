
/* Return y = Ax */
int *matvec(int **A, int *x, int n)
{
    int i, j;

    int *y = (int *)Malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            y[i] += A[i][j] * x[j];
    return y;
}