#include <stdlib.h>
#include <stdio.h>
#include "../includes/ft_printf.h"
#include <limits.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>

# define MIN_LENGTH_FOR_KARATSUBA 4

typedef struct	long_nbr_s
{
	long long	*nbr;
	unsigned long long	size;
}				long_nbr_t;

long_nbr_t	sum(long_nbr_t a, long_nbr_t b)
{
	long_nbr_t s;
	int i;
	int j;

	s.size = a.size + 1;
	s.nbr = malloc(sizeof(long long) * s.size);
	s.nbr[a.size] = 0;
	i = -1;
	while (++i < b.size)
		s.nbr[i] = a.nbr[i] + b.nbr[i];
	return (s);
}

long_nbr_t	*sub(long_nbr_t *a, long_nbr_t b)
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

void	normalize(long_nbr_t *l)
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
			tmp = ((*l).nbr[i] + 1) / 10 - 1;
			(*l).nbr[i + 1] += tmp;
			(*l).nbr[i] -= tmp * 10;
		}
		++i;
	}
}

long_nbr_t *naive_multiply(long_nbr_t a, long_nbr_t b, long_nbr_t *res)
{
	int i;
	int j;

	i = 0;
	while (i < a.size)
	{
		j = 0;
		while (j < b.size)
		{
			(*res).nbr[i + j] += a.nbr[i] * b.nbr[j];
			++j;
		}
		++i;
	}
	return (res);
}

long_nbr_t	karatsuba(long_nbr_t a, long_nbr_t b)
{
	long_nbr_t res;

	res.size = a.size + b.size;
	res.nbr = malloc(sizeof(long long) * res.size);
	if (a.size < MIN_LENGTH_FOR_KARATSUBA)
	{
		ft_bzero(res.nbr, sizeof(long long) * res.size);
		naive_multiply(a, b, &res);
	}
	else
	{
		long_nbr_t a_l;
		a_l.nbr = a.nbr;
		a_l.size = (a.size + 1 ) / 2;
		
		long_nbr_t a_r;
		a_r.nbr = a.nbr + a_l.size;
		a_r.size = a.size / 2;
		
		long_nbr_t b_l;
		b_l.nbr = b.nbr;
		b_l.size = (b.size + 1 ) / 2;
		
		long_nbr_t b_r;
		b_r.nbr = b.nbr + b_l.size;
		b_r.size = b.size / 2;

		long_nbr_t sum_of_l_r = sum(a_l, a_r);
		normalize(&sum_of_l_r);
		long_nbr_t sum_of_l_r_b = sum(b_l, b_r);
		normalize(&sum_of_l_r_b);
		long_nbr_t res_of_sums = karatsuba(sum_of_l_r, sum_of_l_r_b);
		
		long_nbr_t res_1 = karatsuba(a_l, b_l);
		long_nbr_t res_2 = karatsuba(a_r, b_r);
		long_nbr_t all_sum = *sub(sub(&res_of_sums, res_1), res_2);
		
		memcpy(res.nbr, res_1.nbr,
               res_1.size * sizeof(long long));
        memcpy(res.nbr + res_1.size,
               res_2.nbr, res_2.size
               * sizeof(long long));
		for (int i = 0; i < all_sum.size; ++i)
            res.nbr[a_l.size + i] += all_sum.nbr[i];
		free(res_1.nbr);
		free(res_2.nbr);
		free(sum_of_l_r.nbr);
		free(sum_of_l_r_b.nbr);
		free(res_of_sums.nbr);
	}
	normalize(&res);

	return (res);
}

/*#include <stdlib.h>
#include <string.h>
 
#define BASE 10 //система счисления
#define MIN_LENGTH_FOR_KARATSUBA 4 //числа короче умножаются квадратичным алгоритмом
 
typedef int digit; //взят только для разрядов числа
typedef unsigned long int size_length; //тип для длинны числа
 
typedef struct long_value_t { //тип для длинных чисел
    digit* values; //массив с цифрами числа записанными в обратном порядке
    size_length length; //длинна числа
} long_value;
 
long_value sum(long_value a, long_value b) {
    long_value s;
    size_length i;
    s.length = a.length + 1;
    s.values = malloc(sizeof(digit) * s.length);
 
    s.values[a.length - 1] = a.values[a.length - 1];
    s.values[a.length] = 0;
    for (i = 0; i < b.length; ++i) {
        s.values[i] = a.values[i] + b.values[i];
    }
    return s;
}
 
long_value sub(long_value a, long_value b) {
    for (size_length i = 0; i < b.length; ++i) {
        a.values[i] -= b.values[i];
    }
    return a;
}
 
void normalize(long_value l) {
    size_length i;
    for (i = 0; i < l.length - 1; ++i) {
        if (l.values[i] >= BASE) { //если число больше максимального, то организовавается перенос
            digit carryover = l.values[i] / BASE;
            l.values[i + 1] += carryover;
            l.values[i] -= carryover * BASE;
        } else if (l.values[i] < 0) { //если меньше - заем
            digit carryover = (l.values[i] + 1) / BASE - 1;
            l.values[i + 1] += carryover;
            l.values[i] -= carryover * BASE;
        }
    }
}
 
long_value karatsuba(long_value a, long_value b) {
    long_value product; //результирующее произведение
    size_length i;
    product.length = a.length + b.length;
    product.values = malloc(sizeof(digit) * product.length);
 
    if (a.length < MIN_LENGTH_FOR_KARATSUBA) { //если число короче то применять наивное умножение
        memset(product.values, 0, sizeof(digit) * product.length);
        for (size_length i = 0; i < a.length; ++i)
            for (size_length j = 0; j < b.length; ++j) {
                product.values[i + 
            }
    }
    else { //умножение методом Карацубы
        long_value a_part1; //младшая часть числа a
        a_part1.values = a.values;
        a_part1.length = (a.length + 1) / 2;
 
        long_value a_part2; //старшая часть числа a
        a_part2.values = a.values + a_part1.length;
        a_part2.length = a.length / 2;
 
        long_value b_part1; //младшая часть числа b
        b_part1.values = b.values;
        b_part1.length = (b.length + 1) / 2;
 
        long_value b_part2; //старшая часть числа b
        b_part2.values = b.values + b_part1.length;
        b_part2.length = b.length / 2;
 
        long_value sum_of_a_parts = sum(a_part1, a_part2); //cумма частей числа a
        normalize(sum_of_a_parts);
        long_value sum_of_b_parts = sum(b_part1, b_part2); //cумма частей числа b
        normalize(sum_of_b_parts);
        long_value product_of_sums_of_parts = karatsuba(sum_of_a_parts, sum_of_b_parts);
        // произведение сумм частей
 
        long_value product_of_first_parts = karatsuba(a_part1, b_part1); //младший член
        long_value product_of_second_parts = karatsuba(a_part2, b_part2); //старший член
        long_value sum_of_middle_terms = sub(sub(product_of_sums_of_parts, product_of_first_parts), product_of_second_parts);
        //нахождение суммы средних
        memcpy(product.values, product_of_first_parts.values,
               product_of_first_parts.length * sizeof(digit));
        memcpy(product.values + product_of_first_parts.length,
               product_of_second_parts.values, product_of_second_parts.length
               * sizeof(digit));
        for (i = 0; i < sum_of_middle_terms.length; ++i) {
            product.values[a_part1.length + i] += sum_of_middle_terms.values
        free(sum_of_a_parts.values);
        free(sum_of_b_parts.values);
        free(product_of_sums_of_parts.values);
        free(product_of_first_parts.values);
        free(product_of_second_parts.values);
    }
 
    normalize(product); //конечная нормализация числа
 
    return product;
}*/

int main(void)
{
	long_nbr_t a;
	long_nbr_t b;
	long_nbr_t res;
	a.nbr = malloc(5 * sizeof(long long));
	b.nbr = malloc(5 * sizeof(long long));
	a.nbr[0] = 3;
	a.nbr[1] = 3;
	a.nbr[2] = 3;
	a.nbr[3] = 3;
	a.nbr[4] = 3;
	b.nbr[0] = 3;
	b.nbr[1] = 3;
	b.nbr[2] = 3;
	b.nbr[3] = 3;
	b.nbr[4] = 3;
	a.size = 5;
	b.size = 5;
	res = karatsuba(a, b);
	int i = 8;
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
