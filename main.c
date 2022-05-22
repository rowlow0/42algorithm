#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10
#define K 40

int	**init(int ***map, int n)
{
	*map = malloc(sizeof(*map)  * n);
	for (int i = 0; i < n; i++)
	{
		*(*map + i) = malloc(sizeof(**map) * n);
		for (int j = 0; j < n; j++)
			*(*(*map + i) + j) = '0';
	}
	return *map;
}

void	clear(int ***map, int n)
{
	for (int i = 0; i < n; i++)
		free(*(*map + i));
	free(*map);
	*map = 0;
}

void    print_map(int **map, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%c ",map[i][j]);
        printf("\n");
    }
    printf("\n");
}

void    reset(int **map, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            map[i][j] = '0';
}

void rook(int **map, int n)
{
	if (n <= 0)
	{
		printf("there is no place for rook\n");
		return ;
	}
    printf("answer 1\n");
    for (int i = 0; i < n; i++)
            map[i][i] = 'R';
    print_map(map, n);
    reset(map, n);
}

void bishop(int **map, int n)
{
	if (n <= 0)
	{
		printf("there is no place for bishop\n");
		return ;
	}
    printf("answer 2\n");
    for (int i = 0; i < n; i++)
    	map[0][i] = 'B';
    print_map(map, n);
    reset(map, n);
}

void queen(int **map, int n)
{
    printf("answer 3\n");
	if (n < 4)
	{
		printf("there is no place for queen\n");
		return ;
	}
	int floor = n % 2 ? 1 : 0;
    for (int i = 0; i < n / 2 + floor; i++)
		map[i][i * 2] = 'Q';
	for (int i = 0; i < n /2; i++)
		map[i + n / 2 + floor][i * 2 + 1] = 'Q';
    print_map(map, n);
    reset(map, n);
}

void knight(int **map, int n, int k)
{
	printf("answer 4\n");
	if (k <= 0 || n <= 0 || (n != 2 && n != 3 && k > (int)ceil((double)n / 3) * n) || (n == 2 && (k > 4)) || (n == 3 && (k > 3)))
	{
		printf("there is no place for knight\n");
		return ;
	}
	else if (n == 2)
	{
		for(int i = 0; i < n && k; i++)
			for(int j = 0; j < n && k; j++)
					map[i][j] = 'K';
	}
	else
	{
		for (int i = 0; i < n && k; i += 3)
			for (int j = 0; j < n && k; j++)
				if(k--)
					map[i][j] = 'K';
	}
	print_map(map, n);
    reset(map, n);
}

void tour_knight(int **map, int n)
{
	if (n < 5)
	{
		printf("there is no place for knight tour\n");
		return ;
	}
	(void)map;
}

int main()
{
    int **map = init(&map, N);
	rook(map, N);
    bishop(map, N);
	queen(map, N);
	knight(map, N, K);
	tour_knight(map, N);
	clear(&map, N);
	//system("leaks a.out");
    return (0);
}

/*
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
*/