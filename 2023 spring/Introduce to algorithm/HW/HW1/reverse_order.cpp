#include <iostream>
// Merge sort and counting the number of inversions
long merge1(long a[], long l, long m, long r)
{
    long count = 0;
    long n1 = m - l + 1;
    long n2 = r - m;

    long L[n1], R[n2];

    for (long i = 0; i < n1; i++)
    {
        L[i] = a[l + i];
    }
    for (long j = 0; j < n2; j++)
    {
        R[j] = a[m + 1 + j];
    }

    long i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
            count += n1 - i;
        }
        k++;
    }

    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }
    return count;
}

long mergeSort(long a[], long l, long r)
{
    long count = 0;
    if (l < r)
    {
        long m = l + (r - l) / 2;
        count += mergeSort(a, l, m);
        count += mergeSort(a, m + 1, r);
        count += merge1(a, l, m, r);
    }
    return count;
}

int main()
{
    long n;
    std::cin >> n;
    long a[n];
    for (long i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }

    long count = 0;
    // using Merge sort to sort the array
    count = mergeSort(a, 0, n - 1);
    std::cout << count << std::endl;
}