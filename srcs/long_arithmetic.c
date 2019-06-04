/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:10:22 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/04 20:58:26 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <string.h>
#include <stdio.h>

void				zero_passer(t_long *a, int b)
{
	int				i;

	i = (*a).len - 1;
	while (i >= 0 && (*a).nbr[i--] == 0)
		(*a).len--;
	b ? (*a).len++ : 0;
}

void				add_power_neg(char **a, int pwr)
{
	char			power[pwr + 2];
	int				n;
	int				m;
	long long		tmp;

	m = pwr;
	ft_bzero(power, m + 2);
	power[m - 1] = 1;
	while (pwr-- && (n = m))
	{
		while (n--)
			power[n] *= 5;
		n = m;
		while (n--)
			while (power[n] > 9)
			{
				tmp = power[n] / 10;
				power[n - 1] += tmp;
				power[n] -= tmp * 10;
			}
	}
	n = m;
	while (n--)
		(*a)[n] += power[n];
	while (m--)
	{
		while ((*a)[m] > 9)
		{
			tmp = (*a)[m] / 10;
			(*a)[m - 1] += tmp;
			(*a)[m] -= tmp * 10;
		}
	}
}

void				compensation(t_long *a, int zero)
{
	long long		*new_nbr;
	int				x;
	int				y;
	int				z;

	new_nbr = (long long *)malloc(sizeof(long long) * ((*a).len - zero));
	ft_bzero(new_nbr, sizeof(long long) * ((*a).len - zero));
	x = 0;
	y = 0;
	z = zero;
	while (zero--)
		y++;
	while (y <= (*a).len - 1)
		new_nbr[x++] = (*a).nbr[y++];
	free((*a).nbr);
	(*a).nbr = new_nbr;
	(*a).len -= z;
}

void				restore_parity(t_long *a, int len)
{
	long long		*new_nbr;
	int				x;
	int				y;
	int				z;

	new_nbr = (long long *)malloc(sizeof(long long) * ((*a).len + len));
	ft_bzero(new_nbr, sizeof(long long) * ((*a).len + len));
	x = 0;
	y = len;
	while (y--)
		new_nbr[x++] = 0;
	z = (*a).len - 1;
	while (z >= 0 && (*a).nbr[z] == 0)
		z--;
	y = 0;
	while (y <= z)
		new_nbr[x++] = (*a).nbr[y++];
	free((*a).nbr);
	(*a).nbr = new_nbr;
	(*a).len += len;
}

void				normalize(t_long *a)
{
	long long		tmp;
	int				i;

	i = 0;
	while (i < ((*a).len - 1))
	{
		if ((*a).nbr[i] >= 10)
		{
			tmp = (*a).nbr[i] / 10;
			(*a).nbr[i + 1] += tmp;
			(*a).nbr[i] -= tmp * 10;
		}
		else if ((*a).nbr[i] < 0)
		{
			tmp = (((*a).nbr[i] + 1) / 10) - 1;
			(*a).nbr[i + 1] += tmp;
			(*a).nbr[i] -= tmp * 10;
		}
		++i;
	}
}

t_long				sum(t_long a, t_long b)
{
	t_long			s;
	int				i;

	s.len = a.len > b.len ? a.len + 1 : b.len + 1;
	s.nbr = (long long *)malloc(sizeof(long long) * s.len);
	i = -1;
	while (++i < s.len)
		s.nbr[i] = (i < a.len ? a.nbr[i] : 0) + (i < b.len ? b.nbr[i] : 0);
	normalize(&s);
	return (s);
}

t_long				*sub(t_long *a, t_long b)
{
	int				i;

	i = -1;
	while (++i < b.len)
		(*a).nbr[i] -= b.nbr[i];
	normalize(a);
	return (a);
}

void				multi(t_long a, t_long b, t_long *res)
{
	int				i;
	int				j;

	ft_bzero((*res).nbr, sizeof(long long) * (*res).len);
	i = -1;
	while (++i < a.len)
	{
		j = -1;
		while (++j < b.len)
			(*res).nbr[i + j] += a.nbr[i] * b.nbr[j];
	}
}

void				init_var(t_long *a, t_karatsuba_var *var, int flag)
{
	if (flag)
	{
		(*var).a_l.nbr = (*a).nbr;
		(*var).a_l.len = ((*a).len + 1) / 2;
		(*var).a_r.nbr = (*a).nbr + (*var).a_l.len;
		(*var).a_r.len = (*a).len / 2;
	}
	else
	{
		(*var).b_l.nbr = (*a).nbr;
		(*var).b_l.len = ((*a).len + 1) / 2;
		(*var).b_r.nbr = (*a).nbr + (*var).a_l.len;
		(*var).b_r.len = (*a).len / 2;
	}
}

void				tidy_up(t_karatsuba_var *var)
{
	free((*var).res_1.nbr);
	free((*var).res_2.nbr);
	free((*var).res_3.nbr);
}

t_long				karatsuba(t_long a, t_long b)
{
	t_karatsuba_var	var;
	int				i;

	var.res.len = a.len + b.len;
	var.res.nbr = (long long *)malloc(sizeof(long long) * var.res.len);
	if (a.len < KARATSUBA_MIN || b.len < KARATSUBA_MIN)
		multi(a, b, &var.res);
	else
	{
		init_var(&a, &var, 1);
		init_var(&b, &var, 0);
		var.res_1 = karatsuba(var.a_l, var.b_l);
		var.res_2 = karatsuba(var.a_r, var.b_r);
		var.res_3 = karatsuba((sum(var.a_l, var.a_r)), (sum(var.b_l, var.b_r)));
		sub(sub(&var.res_3, var.res_1), var.res_2);
		ft_memcpy(var.res.nbr, var.res_1.nbr, var.res_1.len * 8);
		ft_memcpy(var.res.nbr + var.res_1.len, var.res_2.nbr, var.res_2.len *
		sizeof(long long));
		i = -1;
		while (++i < var.res_3.len)
			var.res.nbr[var.a_l.len + i] += var.res_3.nbr[i];
		tidy_up(&var);
	}
	normalize(&var.res);
	return (var.res);
}

void				init_long(t_long *a, int nbr)
{
	(*a).nbr = (long long *)malloc(sizeof(long long));
	(*a).len = 1;
	(*a).nbr[0] = nbr;
}

void				test(t_long *nbr, int power)
{
	t_long			a;
	t_long			b;
	int				i;

	i = 0;
	init_long(&a, 1);
	init_long(&b, 2);
	while (power)
	{
		if (power & 1)
		{
			if (a.len != b.len)
			{
				if (a.len > b.len)
				{
					i = a.len - b.len;
					restore_parity(&b, i);
				}
				else
				{	
					i = b.len - a.len;
					restore_parity(&a, i);
				}
			}
			a = karatsuba(a, b);
			if (i)
			{
				compensation(&a, i);
				i = 0;
			}
			zero_passer(&a, 0);
		}
		b = karatsuba(b, b);
		zero_passer(&b, 1);
		power >>= 1;
	}
	*nbr = sum(*nbr, a);
	zero_passer(nbr, 0);
}

void				roundd(char **str, int *pre, int sta, int end)
{
	int				flag;
	int				n;

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
