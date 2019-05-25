/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_douie.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/24 15:19:51 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		add_power(char **med, int pwr, int cou)
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
            if (power[n] > 9)
            {
                power[n] -= 10;
				++power[n - 1];
            }
    }
	n = m;
	z = cou;
    while (n >= 0)
        (*med)[z--] += power[n--];
	z = cou + 1;
    while (z--)
	{
		if ((*med)[z] > 9)
        {
            (*med)[z] -= 10;
            ++((*med)[z - 1]);
        }
	}
}

void	add_power_neg(char **med, int pwr, int cou)
{
	char power[-pwr + 2];
	int n;
	int m;

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
			while (power[n] > 9)
			{
				power[n] -= 10;
				++power[n - 1];
			}
	}
	n = m;
	while (n--)
	   (*med)[cou + n] += power[n];
	n = m;
	while (n--)
		while ((*med)[cou + n] > 9)
		{
			(*med)[cou + n] -= 10;
			++(*med)[cou + n - 1];
		}
}

void		roundd(char **str, int n, int *pre)
{
	if ((*str)[n--] >= '5') 
		(*str)[n + 1] == '5' && (*str)[n] % 2 == 0 && *pre > 30 ? 0 : ((*str)[n] += 1);
	while ((*str)[n] > '9' && (*str)[n] != '.')
	{
		(*str)[n] -= 10;
		(*str)[n - 1] != '.' ? (*str)[n - 1] += 1 : 0;
		n--;
	}
	(*str)[n] == '.' ? (*str)[--n]++ : 0;
	while (n >= 0 && (*str)[n] > '9')
	{
		(*str)[n] -= 10;
		(*str)[n - 1] += 1;
		(*str)[n - 1] < '0' ? (*str)[n - 1] += '0' : 0;
		n--;
	}
}

void			inf_handler(size_t *flags, int *wid, int *pre)
{
	if (*flags & NAN)
		if (!(*flags & BIG) && (g_buff[g_count++] = 'n'))
		{
			g_buff[g_count++] = 'a';
			g_buff[g_count++] = 'n';
		}
		else
		{
			g_buff[g_count++] = 'N';
			g_buff[g_count++] = 'A';
			g_buff[g_count++] = 'N';
		}
	else if (*flags & INF)
	{
		if (!(*flags & BIG) && (g_buff[g_count++] = 'i'))
		{
			g_buff[g_count++] = 'n';
			g_buff[g_count++] = 'f';
		}
		else if (*flags & BIG && (g_buff[g_count++] = 'I'))
		{
			g_buff[g_count++] = 'N';
			g_buff[g_count++] = 'F';
		}
	}
}

void			get_bits(t_bits *tally, long double *nbr, size_t *flags, int *pre)
{
	int size;

	(*tally).nbr.nbr = *nbr;
	(*tally).mant = *(long long *)&(*tally).nbr.nbr;
	(*tally).expo = (*tally).nbr.array[4] - 16383;
	(*tally).sign = (*tally).nbr.array[4] >> 15;
	*nbr != *nbr ? (*flags |= NAN) && (*pre = 0) : 0;
	*nbr && *nbr == (*nbr * 10) ? (*flags |= INF) && (*pre = 0) : 0;
	(*tally).sign ? *flags |= NEG : 0;
	if ((*tally).expo < 0)
		(*tally).size = ((*tally).expo - 63) * -1;
	else if ((*tally).expo <= 63 && (*tally).expo >= 0)
	{
		(*tally).size = 64;
		(*tally).size < *pre ? (*tally).size += *pre : 0;
	}
	else 
		(*tally).size = (*tally).expo;
}

void			pass_zero(char **med, size_t *flags, int *cou)
{
	if (((SPEC) == 'g' || (SPEC) == 'G') && !(*flags & HAS) && (*med)[(*cou - 1)] == '0')
	{
		(*cou)--;
		while ((*med)[*cou] == '0')
			(*cou)--;
		(*med)[*cou] == '.' ? (*cou)-- : 0;
		(*cou)++;
	}
}

int				putfloat(char **med, t_bits *tally, size_t *flags, int *pre)
{
	int che;
	int cou;
	int bit;
	int zer;

	cou = 1;
	bit = 64;
	che = (*tally).expo > 0 ? (*tally).expo / 2 + 1: 2;
	(*tally).expo < 0 ? zer = 1 : (zer = 0);
	while (bit-- > 0)
	{
		if ((*tally).mant & (1L << bit))
			(*tally).expo >= 0 ? add_power(med, (*tally).expo, che) : add_power_neg(med, (*tally).expo, che + 2);
		(*tally).expo--;
	}
	bit = 1;
	while (!(*med)[bit])
		bit++;
	zer ? (*med)[cou++] = '0' : 0;
	while (bit <= che)
		(*med)[cou++] = ((*med)[bit++] + '0');
	*pre > 0 ? (*med)[cou++] = '.' : 0;
	bit = che + 2;
	while (bit <= *pre + che + 2)
		(*med)[cou++] = (*med)[bit++] + '0';
	roundd(med, --cou, pre);
	pass_zero(med, flags, &cou);
	return (cou - 1);
}

void			print_double(long double nbr, size_t *flags, int *wid, int *pre)
{
	t_bits		tally;
	char		*med;
	int			i;
	int			j;

	get_bits(&tally, &nbr, flags, pre);
	!(*flags & (INF | NAN)) ? med = (char *)malloc(tally.size) : 0;
	!(*flags & (INF | NAN)) ? ft_bzero(med, tally.size) : 0;
	j = 0;
	!(*flags & (INF | NAN)) ? j = putfloat(&med, &tally, flags, pre) : 0;
	!(*flags & (INF | NAN)) && med[0] != 0 ? !(i = 0) && (*wid)-- : (i = 1);
	adjustment_wid_pre(flags, wid, pre, j);
	fill_width(flags, wid, pre);
	(*flags & (INF | NAN)) ? inf_handler(flags, wid, pre) : 0;
	while (i <= j && EJECT(1) && !(*flags & (INF | NAN)))
		g_buff[g_count++] = med[i++];
	while ((*wid)-- > 0 && EJECT(1))
		g_buff[g_count++] = (*flags << 56) >> 56;
	!(*flags & (INF | NAN)) ? free(med) : 0;
}
