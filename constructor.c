/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:36:35 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/14 21:09:51 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	constructor(size_t *flags)
{
		if (*flags & NEG && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
			g_buff[g_count++] = '-';
		if (*flags & HAS && (*flags << 48) >> 56 == 8 && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
			g_buff[g_count++] = '0';
		if (((*flags & HAS && (*flags << 48) >> 56 == 16 && !(*flags & BIG)) || *flags & PTR) && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
		{
			g_buff[g_count++] = '0';
			g_buff[g_count++] = 'x';
		}
		else if (*flags & HAS && (*flags << 48) >> 56 == 16 && *flags & BIG && !(*flags & PTR) && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
		{
			g_buff[g_count++] = '0';
			g_buff[g_count++] = 'X';
		}
		else if (*flags & HAS && (*flags << 48) >> 56 == 2 && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
		{
			g_buff[g_count++] = '0';
			g_buff[g_count++] = 'b';
		}
		if (!(*flags & NEG) && *flags & PLU && (*flags << 48) >> 56 == 10 && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
			g_buff[g_count++] = '+';
		if (!(*flags & NEG) && !(*flags & PLU) && *flags & SPA && (*flags << 48) >> 56 == 10 && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
			g_buff[g_count++] = ' ';
}

void	adjustment_wid_pre(size_t *flags, int *wid, int *pre, int len)
{
	*pre -= len;
	*wid = *wid - len - (*pre > 0 ? *pre : 0);
	if (*flags & SPA && !(*flags & BIA))
		*wid -= 1;
	if (*flags & PLU && !(*flags & END) && (*flags << 48) >> 56 == 10)
		*wid -= 1;
	if ((*flags << 56) >> 56 == 32)
	{
		*wid -= (*flags & HAS && (*flags << 48) >> 56 == 8) ? 1 : 0; 
		*wid -= (*flags & HAS && (*flags << 48) >> 56 == 16) ? 2 : 0;
	}
	else
		*wid -= (*flags & HAS) ? (((*flags << 48) >> 56 == 8) ? 1 : 2) : 0;
}

void		zero_handler(size_t *flags, int *pre) 
{
	if (*pre == 0 && *flags & POI)
	{
		if ((*flags << 48) >> 56 == 8 && (*flags & HAS) && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
			g_buff[g_count++] = '0';
	}
	else
	{
		(g_count + 1) == BUFF_SIZE ? eject() : 1;
		g_buff[g_count++] = '0';
	}
	if (*flags & HAS && !(*flags & PTR) && (*flags << 48) >> 56 != 10)
		*flags ^= HAS;
}

void		fill_width(size_t *flags, int *wid)
{
	if (!(*flags & BIA))
	{
		if (((*flags << 56) >> 56) == 32)
		{
			while ((*wid)-- > 0 && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
				g_buff[g_count++] = (*flags << 56) >> 56;
			constructor(flags);
		}
		else
		{
			constructor(flags);
			while ((*wid)-- > 0 && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
				g_buff[g_count++] = (*flags << 56) >> 56;
		}
	}
	else
		constructor(flags);
}
