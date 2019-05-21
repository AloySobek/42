/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/21 18:55:53 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double		roundd(int pre)
{
	long double	rou;
	size_t		cou;

	rou = 0.5;
	while (pre-- > 0)
		rou /= 10;
	return (rou);
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
	long double rou;
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
		tra[cou++] = '0';
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
	char		tra[1000];
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
