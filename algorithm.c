#include <limits.h>
int g_m = 0;

int	find_min(int *D, int vertices, bool *marked, int *M)
{
	int min = INT_MAX;
	int v;

	for (int i = 0; i < vertices; i++)
		if (D[i] < min && marked[i] == 0)
			{
				v = i;
				min = D[i];
			}
	M[g_m++] = v;
	marked[v] = 1;
	return v;
}

void	find_path(int **D, int vert, int i, int *M)
{
	if (vert == 0)
	{
		return ;
	}
	if (D[vert - 1][i] != D[vert][i])
	{
		printf("%d ", M[vert] + 1);
		find_path(D, vert - 1, M[vert], M);
	}
	else
		find_path(D, vert - 1, i, M);
}

void	Dijkstra(int **D, int vertices)
{
	int *M;
	int v;
	int temp;
	bool *marked;
	int start = 0;

	M = (int*)calloc(vertices, sizeof(int));
	marked = (bool*)calloc(vertices, sizeof(bool));
	g_m = 0;

	for (int k = 0; k < vertices; k++)
	{
		if (k == 0)
		{
			memcpy(D[k], g_tab[start], sizeof(int) * vertices);
			M[g_m++] = start;
			marked[start] = 1;
			v = find_min(D[k], vertices, marked, M);
		}
		else
			{
		for(int i = 0; i < vertices; i++)
		if (marked[i] == 0)
		D[k][i] = min(D[k - 1][i], D[k-1][v] + g_tab[v][i]);
				else
			D[k][i] = D[k - 1][i];
			v = find_min(D[k], vertices, marked, M);
			}
	}
	--g_m;
	for (int i = 0; i < vertices; i++)
	{
		if (i == start)
			continue ;
		printf("%d " start + 1);		
		find_path(D, vertices - 1, i, M);
		printf("%d " i + 1);		
	}
}

void	ft_create_D(int ***D)
{
	int i;

	*D = (int**)malloc(sizeof(int*) * g_count);
	i = -1;
	while (++i < g_count)
		*(*D + i) = (int*)malloc(sizeof(int) * g_count);
}
