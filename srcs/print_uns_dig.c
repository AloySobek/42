/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uns_dig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:11:48 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/20 15:13:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_uns_dig(uintmax_t nbr, size_t *flags, int *wid, int *pre)
{
	char	tra[20];
	int		j;

	j = 0;
	nbr == 0 ? (*flags |= ZER) && zero_handler(flags, wid, pre) : 0;
	nbr == 0 && *flags & PTR && (*flags & ZER) ? tra[j++] = '0' : 0;
	nbr == 0 && *flags & PTR && (*flags & POI && *pre == 0) ? j-- : 0;
	while (nbr != 0)
	{
		if (nbr % BASE > 9)
			tra[j++] = nbr % BASE + ((*flags & BIG) ? 55 : 87);
		else
			tra[j++] = nbr % BASE + '0';
		nbr /= ((*flags << 48) >> 56);
	}
	adjustment_wid_pre(flags, wid, pre, j);
	fill_width(flags, wid, pre);
	while ((*pre)-- > 0 && EJECT(1))
		g_buff[g_count++] = '0';
	while (--j >= 0 && EJECT(1))
		g_buff[g_count++] = tra[j];
	while ((*wid)-- > 0 && EJECT(1))
		g_buff[g_count++] = (*flags << 56) >> 56;
}
