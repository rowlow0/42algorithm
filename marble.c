#include <stdio.h>
#include <stdlib.h>
#define N 5
#define K 3
#define M 1
#define first 1

int max_fibonacci(int n)
{
    //if (n == 0 || n == 1)
    //    return n;
    int f1 = 0, f2 = 1, sum = f1 + f2;
    while (sum <= n)
    {
        f1 = f2;
        f2 = sum;
        sum = f1 + f2;
    }
    return f2;
}
 
int zeckendorf(int n)
{
    int f;
    while (n > 0)
    {
        f = max_fibonacci(n);
        n = n - f;
    }
    return (n + f);
}

int is_fibonacci(int i)
{
    int a = 0,b = 1, sum = a + b;
    for(;i > sum;)
    {
        a = b;
        b = sum;
        sum = a + b;
    }
    if (i == sum)
        return (1);
    return (0);
}

 int main()
 {
     if(2 > N || M <= 0 || K < M || K > N)
        return (1);
    int count, limit, pre;
    count = N, limit = K, pre = M;
    printf("game 1\n");
    if(first)
    {
        if(count <= limit || (count - limit) % 2 == 0)
            printf("victory\n");
        else
            printf("idk\n");
    }
    else
    {
        count -= pre;
        if(count <= limit || (count - limit) % 2)
            printf("victory\n");
        else
            printf("idk\n");
    }
    printf("game 2\n");
    count = N, pre = M;
    if(first)
    {
        if(!is_fibonacci(count))
            printf("victory\n");
        else
            printf("idk\n");
    }
    else
    {
        count -= pre;
        if (is_fibonacci(count))
        {
            if (count <= 2 * pre)
                printf("victory\n");
            else
                printf("idk\n");
        }
        else 
        {
            int fibonacci = zeckendorf(count);
            if (fibonacci <= pre * 2)
                printf("victory\n");
            else
                printf("idk\n");
        }
    }
    printf("game 3\n");
        count = N, limit = K, pre = M;
    if(first)
    {
        if(((count <= limit || (count - limit) % 2 == 0)) && !is_fibonacci(count))
            printf("victory\n");
        else
            printf("idk\n");
    }
    else
    {
        count -= pre;
        if((count <= limit || (count - limit) % 2) && (is_fibonacci(count) && count <= 2 * pre || zeckendorf(count) <= pre *2))
            printf("victory\n");
        else
            printf("idk\n");
    }
    printf("game 4\n");
    count = N, limit = K, pre = M;
    if(first)
    {
        if((count <= limit || (count - limit) % 2 == 0) || !is_fibonacci(count))
            printf("victory\n");
        else
            printf("idk\n");
    }
    else
    {
        count -= pre;
        if(count <= limit || (count - limit) % 2)
            printf("victory\n");
        else if(is_fibonacci(count))
        {
            if (count <= 2 * pre)
                printf("victory\n");
        }
        else
        {
            int fibonacci = zeckendorf(count);
            if (fibonacci <= pre * 2)
                printf("victory\n");
            else
                printf("idk\n");
        }
    }
    return (0);
 }
