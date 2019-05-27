/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sig_dig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:40:40 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/27 16:27:57 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_sig_dig(intmax_t nbr, size_t *flags, int *wid, int *pre)
{
	char	tra[20];
	int		j;

	j = 0;
	nbr < 0 ? *flags |= NEG : 0;
	nbr == 0 && !(*flags & POI && *pre == 0) ? tra[j++] = '0' : 0;
	while (nbr != 0)
	{
		tra[j++] = nbr % 10 * ((*flags & NEG) > 0 ? -1 : 1) + '0';
		nbr /= 10;
	}
	adjustment_wid_pre(flags, wid, pre, j);
	fill_width(flags, wid);
	while ((*pre)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = '0';
	while (--j >= 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = tra[j];
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = (*flags << 56) >> 56;
}
