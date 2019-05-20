/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/20 21:10:33 by vrichese         ###   ########.fr       */
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
	{
		if (!(*flags & BIG))
		{
			g_buff[g_count++] = 'n';
			g_buff[g_count++] = 'a';
			g_buff[g_count++] = 'n';
		}
		else
		{
			g_buff[g_count++] = 'N';
			g_buff[g_count++] = 'A';
			g_buff[g_count++] = 'N';
		}
	}	
	else if (*nbr && *nbr == *nbr * 10)
	{
		if (!(*flags & BIG))
		{
			g_buff[g_count++] = 'i';
			g_buff[g_count++] = 'n';
			g_buff[g_count++] = 'f';
		}
		else
		{
			g_buff[g_count++] = 'I';
			g_buff[g_count++] = 'N';
			g_buff[g_count++] = 'F';
		}
	}
	*pre = 0;
}

void			putfloat(long double *nbr, long double *dis, size_t *flags,
				int *wid, int *pre)
{
	while (*nbr >= 0 && *dis >= 1 && EJECT(1))
	{
		g_buff[g_count++] = (int)(*nbr / *dis) + '0';
		*nbr -= (*dis * (int)(*nbr / *dis));
		*dis /= 10;
	}
	*pre ? g_buff[g_count++] = '.' : 0;
	*nbr += roundd(*pre);
	while ((*nbr *= 10) > 0 && (*pre)-- && EJECT(1))
	{
		g_buff[g_count++] = (int)*nbr + 48;
		*nbr -= (int)*nbr;
	}
	if (((SPEC) == 'g' || (SPEC) == 'G') && !(*flags & HAS))
	{
		g_count--;
		while (g_buff[g_count] == '0')
			g_count--;
		g_buff[g_count] == '.' ? g_count-- : 0;
		g_count++;
	}
}

void			print_double(long double nbr, size_t *flags, int *wid, int *pre)
{
	long double	rou;
	long double	dis;
	size_t		cou;

	(nbr < 0) ? (nbr *= -1) && (*flags |= NEG) : 0;
	cou = 0;
	dis = 1.0;
	rou = nbr;
	if (nbr != nbr)
	{
		*flags & PLU ? *flags ^= PLU : 0;
		*flags & SPA ? *flags ^= SPA : 0;
		*flags |= INF;
	}
	rou && rou == rou * 10 ? *flags |= INF : 0;
	while ((rou /= 10) >= 1 && ++cou > 0 && !(*flags & INF))
		dis *= 10;
	adjustment_wid_pre(flags, wid, pre, cou);
	fill_width(flags, wid, pre);
	!(*flags & INF) ? putfloat(&nbr, &dis, flags, wid, pre) : inf_handler(&nbr, flags, wid, pre);
	while ((*pre)-- > 0 && EJECT(1))
		g_buff[g_count++] = '0';
	while ((*wid)-- > 0 && EJECT(1))
		g_buff[g_count++] = (*flags << 56) >> 56;
}
