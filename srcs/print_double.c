/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/24 09:07:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		add_power(char *summ, int pwr)
{
    char	power[5002] = {0};
    int		n;

    n = 5000;
    power[n] = 1;
	while (pwr-- && (n = 5001))
    {
        while (--n)
            power[n] *= 2;
        n = 5001;
        while (--n)
            if (power[n] > 9)
            {
                power[n] -= 10;
				++power[n - 1];
            }
    }
	n = 5001;
    while (--n)
        summ[n] += power[n];
    n = 5001;
    while (--n)
        if (summ[n] > 9)
        {
            summ[n] -= 10;
            ++summ[n - 1];
        }
}

void	add_power_neg(char *summ, int pwr)
{
	char power[5002] = {0};
	int n;
	int m;

	pwr *= -1;
	pwr != 0 ? power[pwr - 1] = 1 : 0;
	m = pwr;
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
	   summ[n] += power[n];
	n = m;
	while (n--)
		while (summ[n] > 9)
		{
			summ[n] -= 10;
			++summ[n - 1];
		}
}

void		roundd(char *str, int pre)
{
	int count;

	count = 0;
	while (pre--)
		count++;
	while(count--)
	{
		if (str[count + 1] + 5 > '9')
		{
			str[cou;
		if (str[count] >)
	}
}

void			inf_handler(long double *nbr, size_t *flags, int *wid, int *pre)
{
	if (*nbr != *nbr)
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
	else if (*nbr && *nbr == *nbr * 10)
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

int				putfloat(char *tra, long double *nbr, size_t *flags, int *pre)
{
	t_nbr new;
	t_bits bits;
	char summ[5002] = {0};
	char summ2[5002] = {0};
	int n;
	int n2;
	int bl;
	int cou;

	bl = 64;
	cou = 0;
	new.nbr = *nbr;
	bits.mant = *(long long *)&new.nbr;
	bits.expo = new.array[4] - 16383;
	bits.sign = new.array[4] >> 15;
	while (bl-- > 0)
	{
		if (bits.mant & (1L << bl))
			bits.expo >= 0 ? add_power(&summ[0], bits.expo) : add_power_neg(&summ2[0], bits.expo);
		bits.expo--;
	}
	n = 0;
    while (!summ[n] && n < 5000)
        n++;
	//printf("%d\n", n);
    while (n <= 5000)
	{
		tra[cou++] = summ[n] + '0';
    	n++;
    }
	tra[cou++] = '.';
    n2 = 0;
    while (n2 < *pre)
   	{
       tra[cou++] = summ2[n2] + '0';
       ++n2;
    }
	bits.sign ? *flags |= NEG : 0;
	if (((SPEC) == 'g' || (SPEC) == 'G') && !(*flags & HAS) && tra[(cou - 1)] == '0')
	{
		cou--;
		while (tra[cou] == '0')
			cou--;
		cou++;
	}
	return (cou);
}

void			print_double(long double nbr, size_t *flags, int *wid, int *pre)
{
	char		tra[5002];
	int			i;
	int			j;

	((nbr < 0) || ((1 / nbr) < 0)) ? (*flags |= NEG) && (nbr *= -1) : 0;
	j = 0;
	i = 0;
	nbr != nbr ? (*flags |= NAN) && (*pre = 0) : 0;
	nbr && nbr == nbr * 10 ? (*flags |= INF) && (*pre = 0) : 0;
	!(*flags & (INF | NAN)) ? (j = putfloat(&tra[0], &nbr, flags, pre)) :
	inf_handler(&nbr, flags, wid, pre);
	adjustment_wid_pre(flags, wid, pre, j);
	fill_width(flags, wid, pre);
	while (i < j && EJECT(1))
		g_buff[g_count++] = tra[i++];
	while ((*wid)-- > 0 && EJECT(1))
		g_buff[g_count++] = (*flags << 56) >> 56;
}

/*long double rou;
	long double dis;
	int			cou;

	rou = *nbr;
	cou = 0;
	dis = 1;
	while ((rou /= 10) >= 1 && !(*flags & (INF | NAN)))
		dis *= 10;
	while (*nbr >= 0 && dis >= 1 && EJECT(1))
	{
		tra[cou++] = (int)(*nbr / dis) + '0';
		*nbr -= (dis * (int)(*nbr / dis));
		dis /= 10;
	}
	*pre ? tra[cou++] = '.' : 0;
	*nbr += roundd(*pre);
	while ((*nbr *= 10) > 0 && (*pre)-- && EJECT(1) && (tra[cou++] = (int)*nbr + 48))
		*nbr -= (int)*nbr;
	while ((*pre)-- > 0 && EJECT(1))
		tra[cou++] = '0';*/