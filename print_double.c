/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/18 20:17:29 by vrichese         ###   ########.fr       */
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
	long double	rou;
	long double	dis;
	size_t		cou;

	(nbr < 0) ? (nbr *= -1) && (*flags |= NEG) && (*wid)-- : (*flags & PLU) ? (*wid)-- : 0;
	cou = 0;
	dis = 1.0;
	rou = nbr;
	while ((rou /= 10) >= 1 && ++cou > 0)
		dis *= 10;
	adjustment_double(flags, wid, pre, cou);
	if (!(*flags & BIA))
	{
		if ((*flags << 56) >> 56 == 32)
		{
			while ((*wid)-- > 0)
				g_buff[g_count++] = (*flags << 56) >> 56;
			(*flags & NEG) ? g_buff[g_count++] = '-' : (*flags & PLU) ? g_buff[g_count++] = '+' : 0;
		} 
		else
		{
			(*flags & NEG) ? g_buff[g_count++] = '-' : (*flags & PLU) ? g_buff[g_count++] = '+' : 0;
			while ((*wid)-- > 0)
				g_buff[g_count++] = (*flags << 56) >> 56;
		}
	}
	else
		(*flags & NEG) ? g_buff[g_count++] = '-' : (*flags & PLU) ? g_buff[g_count++] = '+' : 0;
	cou == 0 ? g_buff[g_count++] = '0' : 0;
	while (nbr >= 1 && dis >= 1 && ((g_count + 1) >= BUFF_SIZE ? eject() : 1))
	{
		g_buff[g_count++] = (int)(nbr / dis) + '0';
		nbr -= (dis * (int)(nbr / dis));
		dis /= 10;
	}
	*pre ? g_buff[g_count++] = '.' : 0;
	rou = 0.5;
	cou = *pre;
	while (cou-- > 0)
		rou /= 10;
	nbr += rou;
	while ((nbr *= 10) > 0 && (*pre)-- && ((g_count + 1) >= BUFF_SIZE ? eject() : 1))
	{
		g_buff[g_count++] = (short)nbr + 48;
		nbr -= (short)nbr;
	}
	while ((*pre)-- > 0 && ((g_count + 1) >= BUFF_SIZE ? eject() : 1))
		g_buff[g_count++] = '0';
	while ((*wid)-- > 0 && ((g_count + 1) >= BUFF_SIZE ? eject() : 1))
		g_buff[g_count++] = (*flags << 56) >> 56;
}
