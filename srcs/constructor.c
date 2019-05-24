/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:36:35 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/23 23:22:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	constructor(size_t *flags, int *pre)
{
	if (*flags & NEG && EJECT(1))
		g_buff[g_count++] = '-';
	if (*flags & HAS && BASE == 8 && EJECT(1))
		g_buff[g_count++] = '0';
	if (((*flags & HAS && BASE == 16 && !(*flags & BIG)) || *flags & PTR) &&
		EJECT(2))
	{
		g_buff[g_count++] = '0';
		g_buff[g_count++] = 'x';
	}
	else if (*flags & HAS && BASE == 16 && !(*flags & PTR) && EJECT(2))
	{
		g_buff[g_count++] = '0';
		g_buff[g_count++] = 'X';
	}
	else if (*flags & HAS && BASE == 2 && EJECT(2) && (g_buff[g_count++] = '0'))
		g_buff[g_count++] = *flags & BIG ? 'B' : 'b';
	if (!(*flags & NEG) && *flags & PLU && (BASE == 10 || *flags & END) &&
		!(*flags & NAN) && EJECT(1))
		g_buff[g_count++] = '+';
	if (!(*flags & NEG) && !(*flags & PLU) && *flags & SPA && (BASE == 10
		|| *flags & END) && !(*flags & NAN) && EJECT(1))
		g_buff[g_count++] = ' ';
}

void	adjustment_wid_pre(size_t *flags, int *wid, int *pre, int len)
{
	!(*flags & END) || *flags & INF || *flags & NAN ? *pre -= len : 0;
	(*flags & END) && *pre == 0 && !(*flags & (INF | NAN)) ? (*wid)++ : 0;
	*flags & NEG ? (*wid)-- : 0;
	*flags & INF || *flags & NAN ? (*wid) -= 3 : 0;
	BASE == 8 && *flags & HAS ? (*pre)-- : 0;
	*wid -= len;
	*wid -= *pre > 0 && !(*flags & END) ? *pre : 0;
	if (*flags & SPA && !(*flags & BIA) && !(*flags & NEG) && !(*flags & NAN))
		*wid -= 1;
	if (*flags & PLU && !(*flags & (NEG | NAN)) && (BASE == 10 || *flags & END))
		*wid -= 1;
	if (SIGN == 32)
	{
		*wid -= (*flags & HAS && BASE == 8 && !(*flags & END)) ? 1 : 0;
		*wid -= (*flags & HAS && (BASE == 16 || BASE == 2) && !(*flags & END)) ? 2 : 0;
	}
	else
	{
		if (*flags & HAS && !(*flags & END))
			*wid -= ((BASE == 8) ? 1 : 2);
	}
}

int		zero_handler(size_t *flags, int *wid, int *pre)
{
	if (*pre == 0 && *flags & POI)
	{
		if (BASE == 8 && (*flags & HAS) && EJECT(1))
			g_buff[g_count++] = '0';
	}
	else
	{
		BASE == 10 ? constructor(flags, pre) : 0;
		EJECT(1);
		!(*flags & PTR) ? g_buff[g_count++] = '0' : 0;
	}
	if (*flags & HAS && !(*flags & PTR) && BASE != 10)
		*flags ^= HAS;
	return (1);
}

void	fill_width(size_t *flags, int *wid, int *pre)
{
	if (*flags & INF || *flags & NAN)
	{
		*flags >>= 8;
		*flags <<= 8;
		*flags |= 32;
	}
	if (!(*flags & BIA))
	{
		if (SIGN == 32)
		{
			while ((*wid)-- > 0 && EJECT(1))
				g_buff[g_count++] = SIGN;
			!(*flags & ZER) || *flags & PTR ? constructor(flags, pre) : 0;
		}
		else
		{
			!(*flags & ZER) || *flags & PTR ? constructor(flags, pre) : 0;
			while ((*wid)-- > 0 && EJECT(1))
				g_buff[g_count++] = SIGN;
		}
	}
	else
		!(*flags & ZER) || *flags & PTR ? constructor(flags, pre) : 0;
}
