#include <stdlib.h>
#include <stdio.h>
#include "../includes/ft_printf.h"
#include <limits.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>

# define MIN_LENGTH_FOR_KARATSUBA 4

typedef struct	long_nbr
{
	long long	*nbr;
	long long	size;
}				long_nbr;

int		max_size(long_nbr x, long_nbr y)
{
	if (x.size > y.size)
		return (x.size);
	return (y.size);
}

/*long_nbr	sum(long_nbr a, long_nbr b)
{
	long_nbr s;
	long_nbr high;
	long_nbr low;
	int i;
	int j;

	
	if (a.size > b.size)
	{
		high = a;
		low = b;
	}
	else
	{
		high = b;
		low = a;
	}
	s.size = high.size + 1;
	s.nbr = (long long *)malloc(sizeof(long long) * s.size);
	s.nbr[s.size - 1] = 0;
	i = -1;
	while (++i < s.size - 1)
		s.nbr[i] = high.nbr[i] + (low.size > i ? low.nbr[i] : 0);
	return (s);
}*/

long_nbr sum(long_nbr a, long_nbr b)
{
  long_nbr s;
  s.size = a.size + 1;
  s.nbr = (long long *)malloc(sizeof(long long) * s.size);
 
  s.nbr[a.size - 1] = a.nbr[a.size - 1];
  s.nbr[a.size] = 0;
  for (long long i = 0; i < b.size; ++i)
    s.nbr[i] = a.nbr[i] + b.nbr[i];
  return s;
}

long_nbr	*sub(long_nbr *a, long_nbr b)
{
	int i;

	i = 0;
	while (i < b.size)
	{
		(*a).nbr[i] -= b.nbr[i];
		++i;
	}
	return (a);
}

void	normalize(long_nbr *l)
{
	int i;
	long long tmp;

	i = 0;
	while (i < (*l).size - 1) 
	{
		if ((*l).nbr[i] >= 10)
		{
			tmp = (*l).nbr[i] / 10;
			(*l).nbr[i + 1] += tmp;
			(*l).nbr[i] -= tmp * 10;
		}
		else if ((*l).nbr[i] < 0)
		{
			tmp = ((*l).nbr[i]) / 10;
			tmp == 0 ? (tmp = 1) : 0;
			(*l).nbr[i + 1] -= tmp;
			(*l).nbr[i] += tmp * 10;
		}
		++i;
	}
}

void	naive_multiply(long_nbr *x, long_nbr *y, long_nbr *res)
{
	int n;
	int i;
	int j;

	i = 0;
	(*x).size > (*y).size ? (n = (*x).size) : (n = (*y).size);
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			(*res).nbr[i + j] += (*x).nbr[i] * (*y).nbr[j];
			++j;
		}
		++i;
	}
}

long_nbr	karatsuba(long_nbr a, long_nbr b)
{
	long_nbr res;

	res.size = a.size + b.size;
	res.nbr = (long long *)malloc(sizeof(long long) * res.size);
	if (a.size < MIN_LENGTH_FOR_KARATSUBA)
	{
		ft_bzero(res.nbr, sizeof(long long) * res.size);
		for (long long i = 0; i < a.size; ++i)
			for(long long j = 0; j < b.size; ++j)
				res.nbr[i + j] += a.nbr[i] * b.nbr[j];
	}
	else
	{
		long_nbr a_l;
		a_l.nbr = a.nbr;
		a_l.size = (a.size + 1 ) / 2;
		
		long_nbr a_r;
		a_r.nbr = a.nbr + a_l.size;
		a_r.size = a.size / 2;
		
		long_nbr b_l;
		b_l.nbr = b.nbr;
		b_l.size = (b.size + 1 ) / 2;
		
		long_nbr b_r;
		b_r.nbr = b.nbr + b_l.size;
		b_r.size = b.size / 2;

		long_nbr sum_of_l_r = sum(a_l, a_r);
		normalize(&sum_of_l_r);
		long_nbr sum_of_l_r_b = sum(b_l, b_r);
		normalize(&sum_of_l_r_b);
		long_nbr res_of_sums = karatsuba(sum_of_l_r, sum_of_l_r_b);

		long_nbr res_1 = karatsuba(a_l, b_l);
		long_nbr res_2 = karatsuba(a_r, b_r);

		sub(sub(&res_of_sums, res_1), res_2);

		memcpy(res.nbr, res_1.nbr, res_1.size * sizeof(long long));
		memcpy(res.nbr + res_1.size, res_2.nbr, res_2.size * sizeof(long long));
		for (long long i = 0; i < res_of_sums.size; ++i)
			res.nbr[a_l.size + i] += res_of_sums.nbr[i];
	}
	//ree(res.nbr);
	normalize(&res);
	return (res);
}

int main(void)
{
	long_nbr a;
	long_nbr b;
	long_nbr res;
	a.nbr = (long long *)malloc(5);
	b.nbr = (long long *)malloc(5);
	a.nbr[0] = 0;
	a.nbr[1] = 5;
	a.nbr[2] = 5;
	a.nbr[3] = 5;
	a.nbr[4] = 5;
	b.nbr[0] = 0;
	b.nbr[1] = 5;
	b.nbr[2] = 5;
	b.nbr[3] = 5;
	b.nbr[4] = 5;
	a.size = 5;
	b.size = 5;
	res = karatsuba(a, b);
	int i = 3;
	while (i >= 0)
		printf("%lld", res.nbr[i--]);
	return (0);
}

/*
void	caratsuba_multiply(long_nbr *x, long_nbr *y, long_nbr *res)	
{
	int n;
	
	n == 0 ? n = max_size(x, y) : 0;
	if (n < 4)
	{
		naive_multiply(x, y, res);
		return ;
	}
	caratsuba_multiply(x, y,)
	caratsuba_multiply(x, y, res, n / 2);
}

int main(int argc, char **argv)
{
	char str[102] = {0};
	int i;

	i = -7;
	while (i >= -50)	
		add_power_neg(&str[0], i--);
	i = 0;
	while (!str[i])
		i++;
	while (str[i])
		printf("%c", str[i++]);
	printf("5d");
	long long str[20] = {1, 8, 4, 4, 6, 7, 4, 4, 0, 7, 3, 7, 0, 9, 5, 5, 1, 6, 1, 5};
	long long str1[20] = {1, 8, 4, 4, 6, 7, 4, 4, 0, 7, 3, 7, 0, 9, 5, 5, 1, 6, 1, 5};
	long long res[40];
	int n;

	n = 20;
	
	caratsuba_multiply(&str[0], &str1[0], &res[0], 20);
	double e;
	int test;
	char hello[129];

	int i = 0;
	while (++i <= 127)
		hello[i - 1] = i;
	hello[i] = 0;
	test = 0;
	e = 2.51;
	int count = 0;
	test = ft_printf("{%.f}", e);
	printf("      >>>>>      bytes = %d\n", test);
	//printf("%d\n", count);
	test = printf("{%.f}", e);
	printf("      >>>>>      bytes = %d\n", test);
	//printf("%d\n", count);
	return (0);
}*/
