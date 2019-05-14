/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:36:35 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/14 10:58:52 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	constructor(char **str, size_t *flags, int *j)
{
		if (*flags & NEG)
			(*str)[(*j)++] = '-';
		if (*flags & HAS && (*flags << 48) >> 56 == 8)
			(*str)[(*j)++] = '0';
		if ((*flags & HAS && (*flags << 48) >> 56 == 16 && !(*flags & BIG)) || *flags & PTR)
		{
			(*str)[(*j)++] = 'x';
			(*str)[(*j)++] = '0';
		}
		if (*flags & HAS && (*flags << 48) >> 56 == 16 && *flags & BIG && !(*flags & PTR))
		{
			(*str)[(*j)++] = 'X';
			(*str)[(*j)++] = '0';
		}
		if (!(*flags & NEG) && *flags & PLU && (*flags << 48) >> 56 == 10)
			(*str)[(*j)++] = '+';
		if (!(*flags & NEG) && !(*flags & PLU) && *flags & SPA && (*flags << 48) >> 56 == 10)
			(*str)[(*j)++] = ' ';
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

void		zero_handler(char **res, size_t *flags, int *pre, int *i) 
{
	if (*pre == 0 && *flags & POI)
	{
		if ((*flags << 48) >> 56 == 8 && (*flags & HAS))
			(*res)[(*i)++] = '0';
	}
	else
		(*res)[(*i)++] = '0';
	if (*flags & HAS && !(*flags & PTR) && (*flags << 48) >> 56 != 10)
		*flags ^= HAS;
}

void		fill_width(char **res, size_t *flags, int *wid, int *i)
{
	if (!(*flags & BIA))
	{
		if (((*flags << 56) >> 56) == 32)
		{
			while ((*wid)-- > 0)
				(*res)[(*i)++] = (*flags << 56) >> 56;
			constructor(res, flags, i);
		}
		else
		{
			constructor(res, flags, i);
			while ((*wid)-- > 0)
				(*res)[(*i)++] = (*flags << 56) >> 56;
		}
	}
	else
		constructor(res, flags, i);
}
