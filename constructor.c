/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:36:35 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/19 16:08:29 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	constructor(size_t *flags)
{
		if (*flags & NEG && EJECT(1))
			g_buff[g_count++] = '-';
		if (*flags & HAS && BASE == 8 && EJECT(1))
			g_buff[g_count++] = '0';
		if (((*flags & HAS && BASE == 16 && !(*flags & BIG)) || *flags & PTR) && EJECT(2))
		{
			g_buff[g_count++] = '0';
			g_buff[g_count++] = 'x';
		}
		else if (*flags & HAS && BASE == 16 && *flags & BIG && !(*flags & PTR) && EJECT(2))
		{
			g_buff[g_count++] = '0';
			g_buff[g_count++] = 'X';
		}
		else if (*flags & HAS && BASE == 2 && EJECT(2))
		{
			g_buff[g_count++] = '0';
			g_buff[g_count++] = 'b';
		}
		if (!(*flags & NEG) && *flags & PLU && (BASE == 10 || *flags & END) && EJECT(1))
			g_buff[g_count++] = '+';
		if (!(*flags & NEG) && !(*flags & PLU) && *flags & SPA && (BASE == 10 || *flags & END) && EJECT(1))
			g_buff[g_count++] = ' ';
}

void	adjustment_wid_pre(size_t *flags, int *wid, int *pre, int len)
{
	!(*flags & END) ? *pre -= len : (*wid -= 2);
	*flags & NEG ? (*wid)-- : 0;
	*wid -= len;
	*wid -= *pre > 0 ? *pre : 0;
	if (*flags & SPA && !(*flags & BIA) && !(*flags & NEG))
		*wid -= 1;
	if (*flags & PLU && !(*flags & NEG) && (BASE == 10 || *flags & END))
		*wid -= 1;
	if ((*flags << 56) >> 56 == 32)
	{
		*wid -= (*flags & HAS && BASE == 8) ? 1 : 0; 
		*wid -= (*flags & HAS && BASE == 16) ? 2 : 0;
	}
	else
		*wid -= (*flags & HAS) ? ((BASE == 8) ? 1 : 2) : 0;
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
		BASE == 10 || *flags & PTR ? constructor(flags) : 0;
		EJECT(1);
		*pre < 1 && *wid < 1 ? g_buff[g_count++] = '0' : 0;
	}
	if (*flags & HAS && !(*flags & PTR) && BASE != 10)
		*flags ^= HAS;
	return (1);
}

void	fill_width(size_t *flags, int *wid)
{
	if (!(*flags & BIA))
	{
		if (((*flags << 56) >> 56) == 32)
		{
			while ((*wid)-- > 0 && EJECT(1))
				g_buff[g_count++] = (*flags << 56) >> 56;
			!(*flags & ZER) && !(*flags & PTR) ? constructor(flags) : 0;
		}
		else
		{
			!(*flags & ZER) && !(*flags & PTR) ? constructor(flags) : 0;
			while ((*wid)-- > 0 && EJECT(1))
				g_buff[g_count++] = (*flags << 56) >> 56;
		}
	}
	else
		!(*flags & ZER) && !(*flags & PTR) ? constructor(flags) : 0;
}

void 	erase_zero(size_t *flags)
{
	int a;

	a = *flags;
	if (a == 6)
		return ;
}