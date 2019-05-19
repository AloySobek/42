/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/19 17:41:39 by vrichese         ###   ########.fr       */
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

void			putfloat(long double *nbr, long double *dis, int *pre)
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
	while ((rou /= 10) >= 1 && ++cou > 0)
		dis *= 10;
	adjustment_wid_pre(flags, wid, pre, cou);
	fill_width(flags, wid);
	putfloat(&nbr, &dis, pre);
	while ((*pre)-- > 0 && EJECT(1))
		g_buff[g_count++] = '0';
	while ((*wid)-- > 0 && EJECT(1))
		g_buff[g_count++] = (*flags << 56) >> 56;
}
