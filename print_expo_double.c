/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expo_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:53:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/16 15:25:21 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_expo_double(long double nbr, size_t *flags, int *wid, int *pre)
{
	long double	rou;
	long double	dis;
	size_t		cou;
	int			expo;

	(nbr < 0) ? (nbr *= -1) && (*flags |= NEG) && (*wid)-- : (*flags * PLU) ? (*wid)-- : 0;
	!(*flags & POI) ? *pre = 6 : 0;
	cou = 0;
	dis = 1.0;
	expo   = 0;
	if (nbr >= 10)
	{
		while (nbr >= 10)
		{
			nbr /= 10;
			expo++;
		}
	}
	else if (nbr < 1)
	{
		while (nbr < 1)
		{
			nbr *= 10;
			expo--;
		}
	}
	rou = nbr;
	while ((rou /= 10) >= 1 && ++cou > 0)
		dis *= 10;
	*wid -= *pre > 0 ? *pre + 1 : 0;
	*wid -= 4;
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
	(*flags & BIG) ? (g_buff[g_count++] = 'E') : (g_buff[g_count++] = 'e');
	expo >= 0 ? (g_buff[g_count++] = '+') : (g_buff[g_count++] = '-') && (expo *= -1);
	expo >= 10 ? (g_buff[g_count++] = expo / 10 + '0') && (g_buff[g_count++] = expo % 10 + '0') : (g_buff[g_count++] = '0') && (g_buff[g_count++] = expo + '0');
	while ((*wid)-- > 0 && ((g_count + 1) >= BUFF_SIZE ? eject() : 1))
		g_buff[g_count++] = (*flags << 56) >> 56;
}