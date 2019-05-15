/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sig_dig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:40:40 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/15 16:26:08 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		negative_handler(intmax_t nbr, size_t *flags, int *wid)
{
	(*wid)--;
	*flags |= NEG;
	*flags |= END;
	*flags |= NEG;
	(*flags & SPA) ? (*flags ^= SPA) : 0;
	(*flags & PLU) ? (*flags ^= PLU) : 0;
}

void		print_sig_dig(intmax_t nbr, size_t *flags, int *wid, int *pre)
{
	char	tra[20];
	int		j;

	nbr < 0 ? negative_handler(nbr, flags, wid) : 0;
	nbr == 0 ? (*flags |= ZER) && zero_handler(flags, pre) : 0;
	j = 0;
	while (nbr != 0)
	{
		tra[j++] = nbr % 10 * ((*flags & NEG) > 0 ? -1 : 1) + '0';
		nbr /= 10;
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
