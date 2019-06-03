/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:10:22 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/03 21:32:56 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <string.h>
#include <stdio.h>

/*void		add_power(char **med, int pwr, int cou)
{
	char	power[pwr / 2 + 2];
	int		n;
	int		m;
	int		z;

	m = pwr / 2;
	ft_bzero(power, m + 2);
	power[m] = 1;
	while (pwr-- && (n = m + 1))
	{
		while (n--)
			power[n] *= 2;
		n = m + 1;
		while (n--)
			power[n] > 9 ? (power[n] -= 10) >= 0 && ++power[n - 1] : 0;
	}
	n = m;
	z = cou;
	while (n >= 0)
		(*med)[z--] += power[n--];
	z = cou + 1;
	while (z--)
		(*med)[z] > 9 ? ((*med)[z] -= 10) >= 0 && ++((*med)[z - 1]) : 0;
}

void		add_power_neg(char **med, int pwr, int cou)
{
	char	power[-pwr + 2];
	int		n;
	int		m;

	pwr *= -1;
	m = pwr;
	ft_bzero(power, m + 2);
	power[m - 1] = 1;
	while (pwr-- && (n = m))
	{
		while (n--)
			power[n] *= 5;
		n = m;
		while (n--)
			while (power[n] > 9 && (power[n] -= 10) >= 0)
				++power[n - 1];
	}
	n = m;
	while (n--)
		(*med)[cou + n] += power[n];
	while (m--)
		while ((*med)[cou + m] > 9 && ((*med)[cou + m] -= 10) >= 0)
			++(*med)[cou + m - 1];
}*/

void	normalize(long_nbr_t *l)
{
	long long i;
	long long tmp;

	i = 0;
	while (i < ((*l).size - 1)) 
	{
		if ((*l).nbr[i] >= 10)
		{
			tmp = (*l).nbr[i] / 10;
			(*l).nbr[i + 1] += tmp;
			(*l).nbr[i] -= tmp * 10;
		}
		else if ((*l).nbr[i] < 0)
		{
			tmp = (((*l).nbr[i] + 1) / 10) - 1;
			(*l).nbr[i + 1] += tmp;
			(*l).nbr[i] -= tmp * 10;
		}
		++i;
	}
}

long_nbr_t	sum(long_nbr_t a, long_nbr_t b)
{
	long_nbr_t s;
	long long i;

	s.size = a.size + 1;
	s.nbr = (long long *)malloc(sizeof(long long) * s.size);
	s.nbr[a.size - 1] = a.nbr[a.size - 1];
	s.nbr[a.size] = 0;
	i = 0;
	while (i < a.size)
	{
		a.nbr[i] += (i < b.size ? b.nbr[i] : 0);
		++i;
	}
	i = 0;
	while (i < a.size)
	{
		s.nbr[i] = a.nbr[i];
		++i;
	}
	normalize(&s);
	i = s.size - 1;
	while (i >= 0 && s.nbr[i--] == 0)
		s.size--;
	return (s);
}

long_nbr_t	*sub(long_nbr_t *a, long_nbr_t b)
{
	long long	i;

	i = 0;
	while (i < b.size)
	{
		(*a).nbr[i] -= b.nbr[i];
		++i;
	}
	normalize(a);
	i = (*a).size - 1;
	while (i >= 0 && (*a).nbr[i--] == 0)
		(*a).size--;
	return (a);
}

long_nbr_t *naive_multiply(long_nbr_t a, long_nbr_t b, long_nbr_t *res)
{
	long long i;
	long long j;

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

long_nbr_t		karatsuba(long_nbr_t a, long_nbr_t b)
{	
	long_nbr_t	res;
	int			n;
	int			i;

	res.size = a.size + b.size;
	res.nbr = (long long *)malloc(sizeof(long long) * res.size);
	if (a.size < MIN_LENGTH_FOR_KARATSUBA || b.size < MIN_LENGTH_FOR_KARATSUBA)
	{
		ft_bzero(res.nbr, sizeof(long long) * res.size);
		naive_multiply(a, b, &res);
	}
	else
	{
		long_nbr_t a_l;
		a_l.nbr = a.nbr;
		a_l.size = (a.size + 1) / 2;		
		long_nbr_t a_r;
		a_r.nbr = a.nbr + a_l.size;
		a_r.size = a.size / 2;	
		long_nbr_t b_l;
		b_l.nbr = b.nbr;
		b_l.size = (b.size + 1) / 2;
		long_nbr_t b_r;
		b_r.nbr = b.nbr + b_l.size;
		b_r.size = b.size / 2;
		long_nbr_t res_1 = karatsuba(a_l, b_l);
		long_nbr_t res_2 = karatsuba(a_r, b_r);
		long_nbr_t res_3 = karatsuba((sum(a_l, a_r)), (sum(a_l, a_r)));	
		sub(sub(&res_2, res_1), res_3);
		ft_memcpy(res.nbr, res_1.nbr, res_1.size * sizeof(long long));
        ft_memcpy(res.nbr + res_1.size, res_2.nbr, res_2.size * sizeof(long long));
		i = -1;
		while (++i < res_3.size)
            res.nbr[a_l.size + i] += res_3.nbr[i];
		free(res_1.nbr);
		free(res_2.nbr);
		free(res_3.nbr);
	}
	normalize(&res);
	return (res);
}

void			test(long_nbr_t *nbr, int power, int base)
{
	long_nbr_t a;
	long_nbr_t b;
	int i;
	
	a.nbr = (long long *)malloc(sizeof(long long));
	a.size = 1;
	a.nbr[0] = 1;
	b.nbr = (long long *)malloc(sizeof(long long));
	b.size = 1;
	b.nbr[0] = 2;
	power = 4192;
	/*while (power)
	{
		if (power & 1)
		{
			a = karatsuba(a, b);
			i = a.size - 1;
			while (i >= 0)
				printf("%lld", a.nbr[i--]);
			printf("|||");
			while (a.size - 1 >= 0 && a.nbr[a.size - 1] == 0)
				a.size--;
			i = a.size - 1;
			while (i >= 0)
				printf("%lld", a.nbr[i--]);
			printf("\n\n\n");
		}
		i = b.size - 1;
		while (i >= 0)
			printf("%lld", b.nbr[i--]);	
		printf("///");
		b = karatsuba(b, b);
		while (b.size - 1 >= 0 && b.nbr[b.size - 1] == 0)
			b.size--;
		i = b.size - 1;
		while (i >= 0)
			printf("%lld", b.nbr[i--]);
		printf("\n\n\n");
		power >>= 1;
	}
	int j = a.size - 1;
	while (j >= 0)
		printf("%lld", a.nbr[j--]);
	//printf("///%ld///", strlen(""));*/
	long_nbr_t test;
	test.nbr = (long long *)malloc(sizeof(long long) * 10);
	test.size = 10;
	test.nbr[0] = 6;
	test.nbr[1] = 9;
	test.nbr[2] = 2;
	test.nbr[3] = 7;
	test.nbr[4] = 6;
	test.nbr[5] = 9;
	test.nbr[6] = 4;
	test.nbr[7] = 9;
	test.nbr[8] = 2;
	test.nbr[9] = 4;
	long_nbr_t test1;
	test1.nbr = (long long *)malloc(sizeof(long long) * 10);
	test1.size = 10;
	test1.nbr[0] = 6;
	test1.nbr[1] = 1;
	test1.nbr[2] = 6;
	test1.nbr[3] = 1;
	test1.nbr[4] = 5;
	test1.nbr[5] = 5;
	test1.nbr[6] = 9;
	test1.nbr[7] = 0;
	test1.nbr[8] = 1;
	test1.nbr[9] = 3;
	//test1.nbr[10] = 7;
	//test1.nbr[11] = 0;
	//test1.nbr[12] = 4;
	//test1.nbr[13] = 4;
	//test1.nbr[14] = 7;
	//test1.nbr[15] = 6;
	//test1.nbr[16] = 4;
	//test1.nbr[17] = 4;
	//test1.nbr[18] = 8;
	//test1.nbr[19] = 1;
	long_nbr_t res;
	//res = *sub(&test1, test);
	res = karatsuba(test, test1);
	normalize(&res);
	int h = res.size - 1;
	while (h >= 0)
		printf("%lld", res.nbr[h--]);
	exit(1);
	if ((*nbr).size > 0)
	{
		*nbr = sum(*nbr, a);
		normalize(nbr);
	}
	else
		*nbr = a;
}

void		roundd(char **str, int *pre, int sta, int end)
{
	int flag;
	int n;

	n = sta + (*pre > 0 ? *pre : 0);
	flag = 0;
	if ((*str)[n + 2] >= '5')
	{
		if ((*str)[n + 2] == '5')
			while (end > n + 2)
				if ((*str)[end--] > '0' && (flag = 1))
					break ;
		if ((*str)[n + 2] > '5')
			(*str)[n + 1] != '.' ? ++(*str)[n + 1] : ++(*str)[n];
		else if ((*str)[n + 2] == '5')
		{
			if ((*str)[n + 1] != '.')
				(*str)[n + 1] % 2 != 0 || flag ? ++(*str)[n + 1] : 0;
			else
				(*str)[n]  % 2 != 0 || flag ? ++(*str)[n] : 0;
		}
	}
	while ((*str)[n + 1] > '9' && (*str)[n + 1] != '.' && ((*str)[n--] -= 10) >= 0)
		(*str)[n] != '.' ? (*str)[n] += 1 : 0;
	(*str)[n] == '.' && n != sta + *pre ? (*str)[--n]++ : 0;
	while (n >= 0 && (*str)[n] > '9' && ((*str)[n--] -= 10) >= 0 && ++(*str)[n])
		(*str)[n] < '0' ? (*str)[n] += '0' : 0;
}
