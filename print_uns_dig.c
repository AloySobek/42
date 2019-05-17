/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uns_dig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:11:48 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/17 20:00:56 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_uns_dig(uintmax_t nbr, size_t *flags, int *wid, int *pre)
{
	char	tra[20];
	int		j;

	j = 0;
	nbr == 0 ? zero_handler(flags, wid, pre) : 0;
	while (nbr != 0)
	{
		tra[j++] = (nbr % ((*flags << 48) >> 56) > 9) ? (nbr % ((*flags << 48) >> 56) + (*flags & BIG ? 55 : 87)) : (nbr % ((*flags << 48) >> 56) + '0');
		nbr /= ((*flags << 48) >> 56);
	}
	adjustment_wid_pre(flags, wid, pre, j);
	fill_width(flags, wid);
	while ((*pre)-- > 0 && ((g_count + 1) >= BUFF_SIZE ? eject() : 1))
		g_buff[g_count++] = '0';
	while (--j >= 0 && ((g_count + 1) >= BUFF_SIZE ? eject() : 1))
		g_buff[g_count++] = tra[j];
	while ((*wid)-- > 0 && ((g_count + 1) >= BUFF_SIZE ? eject() : 1))
		g_buff[g_count++] = (*flags << 56) >> 56;
}