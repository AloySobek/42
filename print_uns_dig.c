/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uns_dig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:11:48 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/14 20:58:31 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_uns_dig(uintmax_t nbr, size_t *flags, int *wid, int *pre)
{
	char	tra[20];
	char	*res;
	int		j;
	int		i;

	i = 0;
	nbr == 0 ? zero_handler(flags, pre) : 0;
	j = i;
	while (nbr != 0)
	{
		tra[j++] = (nbr % ((*flags << 48) >> 56) > 9) ? (nbr % ((*flags << 48) >> 56) + (*flags & BIG ? 55 : 87)) : (nbr % ((*flags << 48) >> 56) + '0');
		nbr /= ((*flags << 48) >> 56);
	}
	adjustment_wid_pre(flags, wid, pre, j);
	fill_width(flags, wid);
	while ((*pre)-- > 0)
		res[i++] = '0';
	while (--j >= 0)
		res[i++] = tra[j];
	while ((*wid)-- > 0)
		res[i++] = (*flags << 56) >> 56;
	write(1, res, i);
	return (i);
}