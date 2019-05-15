/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expo_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:53:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/15 14:05:50 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_expo_double(long double nbr, size_t *flags, int *wid, int *pre)
{
	long double	roundd;
	ssize_t		interm;
	int			expo;

	    (nbr < 0)   ? (nbr *= -1) && (*flags |= NEG) : 0;
	!(*flags & POI) ?          *pre = 6              : 0;
	roundd   = 1;
	expo     = 0;
	if (nbr >= 10)
	{
		while ((int)nbr >= 10)
		{
			nbr /= 10;
			expo++;
		}
	}
	else if (nbr < 1)
	{
		while ((int)nbr < 1)
		{
			nbr *= 10;
			expo--;
		}
	}
	interm = (ssize_t)nbr;
	while ((interm /= 10) >= 0)
		roundd *= 10;
	interm = (ssize_t)nbr;
	*wid -= *pre > 0 ? *pre + 1 : 0;
	*wid -= 4;
	*wid -= 4;
	if (*wid && !(*flags & BIA))
		while ((*wid)-- > 0)
			g_buff[g_count++] = '0';
	if (interm == 0)
		g_buff[g_count++] = '0';
	while (interm)
	{
		g_buff[g_count] = (ssize_t)(interm / (ssize_t)roundd) + '0';
		interm %= (ssize_t)roundd;
		roundd /= 10;
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
		g_buff[g_count++] = (long long)nbr + 48;
		roundd *= 10;
		nbr -= (long long)nbr;
	}
	if ((*pre)++ > 0)
		while ((*pre)--)
			g_buff[g_count++] = '0';
	g_buff[g_count++] = 'e';
	g_buff[g_count++] = '+';
	g_buff[g_count++] = '0';
	g_buff[g_count++] = '0' + expo;
	while ((*wid)-- > 0)
		g_buff[g_count++] = ' ';
}