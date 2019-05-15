/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/15 20:44:14 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			adjustment_double(size_t *flags, int *wid, int *pre, int len)
{
	*wid -= *pre;
	*wid -= len;
	*wid -= 2;
}

void			print_double(long double nbr, size_t *flags, int *wid, int *pre)
{
	long double	roundd;
	size_t		interm;
	long double	i;

	(nbr < 0) ? (nbr *= -1) && (*flags |= NEG) : 0;
	!(*flags & POI) ? *pre = 6 : 0;
	interm   = 0;
	i        = 1.0;
	roundd = nbr;
	while ((roundd /= 10) >= 1 && ++interm > 0)
		i *= 10;
	adjustment_double(flags, wid, pre, interm);
	while ((*wid)-- > 0)
		g_buff[g_count++] = (*flags << 56) >> 56;
	if (interm == 1)
		g_buff[g_count++] = '0';
	while (nbr >= 1 && i >= 1)
	{
		((g_count + 1) >= BUFF_SIZE ? eject() : 1);
		g_buff[g_count++] = (int)(nbr / i) + '0';
		nbr -= (i * (int)(nbr / i));
		i /= 10;
	}
	if (*pre)
		g_buff[g_count++] = '.';
	roundd = 0.5;
	interm = *pre;
	while (interm-- > 0)
		roundd /= 10;
	nbr   -= (ssize_t)nbr;
	nbr   += roundd;
	while ((nbr *= 10) > 0 && (*pre)--)
	{
		((g_count + 1) >= BUFF_SIZE ? eject() : 1);
		g_buff[g_count++] = (short)nbr + 48;
		nbr -= (short)nbr;
	}
	while ((*pre)-- > 0)
	{
		((g_count + 1) >= BUFF_SIZE ? eject() : 1);
		g_buff[g_count++] = '0';
	}
	while ((*wid)-- > 0)
	{	
		((g_count + 1) >= BUFF_SIZE ? eject() : 1);
		g_buff[g_count++] = (*flags << 56) >> 56;
	}
}
