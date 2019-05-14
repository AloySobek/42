/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uns_dig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:11:48 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/14 23:13:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_uns_dig(uintmax_t nbr, size_t *flags, int *wid, int *pre)
{
	char	tra[20];
	int		j;

	nbr == 0 ? zero_handler(flags, pre) : 0;
	j = 0;
	while (nbr != 0)
	{
		tra[j++] = (nbr % ((*flags << 48) >> 56) > 9) ? (nbr % ((*flags << 48) >> 56) + (*flags & BIG ? 55 : 87)) : (nbr % ((*flags << 48) >> 56) + '0');
		nbr /= ((*flags << 48) >> 56);
	}
	adjustment_wid_pre(flags, wid, pre, j);
	fill_width(flags, wid);
	while ((*pre)-- > 0 && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
		g_buff[g_count++] = '0';
	while (--j >= 0 && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
		g_buff[g_count++] = tra[j];
	while ((*wid)-- > 0 && ((g_count + 1) == BUFF_SIZE ? eject() : 1))
		g_buff[g_count++] = (*flags << 56) >> 56;
}