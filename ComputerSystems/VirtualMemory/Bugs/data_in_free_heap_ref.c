int *heapref(int n, int m)
{
    int i;
    int *x, *y;
    x = (int *)Malloc(n * sizeof(int));
    // ...
    // Other calls to malloc and free go here
    free(x);
    y = (int *)Malloc(m * sizeof(int));
    for (i = 0; i < m; i++)
        y[i] = x[i]++; /* Oops! x[i] is a word in a free block */

    return y;
}