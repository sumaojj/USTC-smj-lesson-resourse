
#include <iostream>

int main()
{
    int a[20000];
    // initialize the array with negative numbers
    for (int i = 0; i < 20000; i++)
    {
        a[i] = 0;
    }

    int n;
    std::cin >> n;
    int iter = 0;
    while (iter < n)
    {
        iter++;
        int control;
        std::cin >> control;

        switch (control)
        {
        case (1):
        {
            // insert x to last element of the queue
            int x;
            std::cin >> x;
            for (int i = 0; i < n; i++)
            {
                if (a[i] == 0)
                {
                    a[i] = x;
                    break;
                }
            }
            break;
        }
        case (2):
        {
            // print the minimum element of the queue
            if (a[0] == 0)
            {
                std::cout << "ERR_CANNOT_QUERY" << std::endl;
            }
            else
            {
                int min = a[0];
                for (int i = 0; i < n; i++)
                {
                    if (a[i] == 0)
                    {
                        std::cout << min << std::endl;
                        break;
                    }
                    if (a[i] < min)
                    {
                        min = a[i];
                    }
                }
            }
            break;
        }
        case (3):
        {
            // delete the minimum element of the queue
            if (a[0] == 0)
            {
                std::cout << "ERR_CANNOT_POP" << std::endl;
            }
            else
            {
                int min = a[0];
                int min_index = 0;
                for (int i = 0; i < n; i++)
                {
                    if (a[i] == 0)
                    {
                        for (int j = min_index; j < n; j++)
                        {
                            a[j] = a[j + 1];
                        }
                        break;
                    }
                    if (a[i] < min)
                    {
                        min = a[i];
                        min_index = i;
                    }
                }
            }
            break;
        }
        case (4):
        {
            int count = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[i] != 0)
                {
                    count++;
                }
            }
            std::cout << count << std::endl;
            break;
        }
        }
    }

    return 0;
}