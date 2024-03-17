
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
            // pop the last element of the queue
            if (a[0] == 0)
            {
                std::cout << "Empty" << std::endl;
            }
            else
            {
                for (int i = 0; i < n; i++)
                {
                    if (a[i] == 0)
                    {
                        a[i - 1] = 0;
                        break;
                    }
                }
            }
            break;
        }
        case (3):
        {

            // print the last element of the queue
            if (a[0] == 0)
            {
                std::cout << "Anguei!" << std::endl;
            }
            else
            {
                for (int i = 0; i < n; i++)
                {
                    if (a[i] == 0)
                    {
                        std::cout << a[i - 1] << std::endl;
                        break;
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