/* Create an nxm array */
int **makeArray1(int n, int m)
{
    int i;
    int **A = (int **)Malloc(n * sizeof(int)); // need size(int*)

    for (i = 0; i < n; i++)
        A[i] = (int *)Malloc(m * sizeof(int));
    return A;
}