/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:36:35 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/27 19:28:34 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	constructor(size_t *flags)
{
	if (*flags & NEG && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = '-';
	if (*flags & HAS && BASE == 8 && !(*flags & ZER) && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = '0';
	if (((*flags & HAS && BASE == 16 && !(*flags & BIG)) || *flags & PTR) &&
		!(*flags & ZER) && EJECT(2))
	{
		g_buff__.g_buff[g_buff__.g_count++] = '0';
		g_buff__.g_buff[g_buff__.g_count++] = 'x';
	}
	else if (*flags & HAS && BASE == 16 && !(*flags & PTR) && !(*flags & ZER)
		&& EJECT(2))
	{
		g_buff__.g_buff[g_buff__.g_count++] = '0';
		g_buff__.g_buff[g_buff__.g_count++] = 'X';
	}
	else if (*flags & HAS && BASE == 2 && EJECT(2) &&
		(g_buff__.g_buff[g_buff__.g_count++] = '0'))
		g_buff__.g_buff[g_buff__.g_count++] = *flags & BIG ? 'B' : 'b';
	if (!(*flags & NEG) && *flags & PLU && (BASE == 10 || *flags & END) &&
		!(*flags & NAN) && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = '+';
	if (!(*flags & NEG) && !(*flags & PLU) && *flags & SPA && (BASE == 10
		|| *flags & END) && !(*flags & NAN) && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = ' ';
}

void	adjustment_wid_pre(size_t *flags, int *wid, int *pre, int len)
{
	!(*flags & END) || *flags & INF || *flags & NAN ? *pre -= len : 0;
	*flags & NEG ? (*wid)-- : 0;
	*flags & INF || *flags & NAN ? (*wid) -= 3 : 0;
	SPEC == 'e' || SPEC == 'G' ? *wid -= 4 : 0;
	BASE == 8 && *flags & HAS && !(*flags & ZER) ? (*pre)-- : 0;
	*wid -= len;
	*wid -= *pre > 0 && !(*flags & END) ? *pre : 0;
	if (*flags & SPA && !(*flags & PLU) && !(*flags & NEG) && !(*flags & PTR)
		&& !(*flags & NAN) && BASE != 8 && BASE != 16)
		*wid -= 1;
	if (*flags & PLU && !(*flags & (NEG | NAN)) && (BASE == 10 || *flags & END))
		*wid -= 1;
	if (SIGN == 32)
	{
		*wid -= (*flags & HAS && BASE == 8 && !(*flags & ZER) && !(*flags & END)) ? 1 : 0;
		*wid -= (*flags & HAS && (BASE == 16 || BASE == 2) &&
		!(*flags & ZER) && !(*flags & END)) ? 2 : 0;
	}
	else
	{
		if (*flags & HAS && !(*flags & END) && !(*flags & ZER) && BASE != 10)
			*wid -= ((BASE == 8) ? 1 : 2);
	}
}

int		zero_handler(size_t *flags, int *pre)
{
	if (*pre == 0 && *flags & POI)
	{
		if (BASE == 8 && (*flags & HAS) && EJECT(1))
			g_buff__.g_buff[g_buff__.g_count++] = '0';
	}
	else
	{
		EJECT(1);
		!(*flags & PTR) ? g_buff__.g_buff[g_buff__.g_count++] = '0' : 0;
	}
	if (*flags & HAS && !(*flags & PTR) && BASE != 10)
		*flags ^= HAS;
	return (1);
}

void	fill_width(size_t *flags, int *wid)
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
				g_buff__.g_buff[g_buff__.g_count++] = SIGN;
			constructor(flags);
		}
		else
		{
			constructor(flags);
			while ((*wid)-- > 0 && EJECT(1))
				g_buff__.g_buff[g_buff__.g_count++] = SIGN;
		}
	}
	else
		constructor(flags);
}
