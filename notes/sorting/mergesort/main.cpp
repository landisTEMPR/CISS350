#include <iostream>

void merge(int x[], int start, int mid, int end, int t[])
{
    int i = start;   // left half pointer
    int j = mid;     // right half pointer
    int k = start;   // temp array pointer

    while (i < mid && j < end)
    {
        if (x[i] <= x[j])
            t[k++] = x[i++];
        else
            t[k++] = x[j++];
    }

    while (i < mid)
        t[k++] = x[i++];

    while (j < end)
        t[k++] = x[j++];

    // copy sorted segment back into x
    for (int l = start; l < end; l++)
        x[l] = t[l];
}

void mergeSort(int x[], int start, int end, int t[])
{
    int n = end - start;
    if (n <= 1) return;

    int mid = start + n / 2;
    mergeSort(x, start, mid, t);
    mergeSort(x, mid, end, t);
    merge(x, start, mid, end, t);
}

int main()
{
    int x[] = {1, 3, 4, 2, 1, 9, 10, 5, 2, 1, 9, 6, 8};
    int size = sizeof(x) / sizeof(x[0]);
    int t[size];

    mergeSort(x, 0, size, t);

    for (int i = 0; i < size; i++)
        std::cout << x[i] << " ";

    return 0;
}
