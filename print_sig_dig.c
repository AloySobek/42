/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sig_dig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:40:40 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/13 18:21:31 by vrichese         ###   ########.fr       */
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

int			print_sig_dig(intmax_t nbr, size_t *flags, int *wid, int *pre)
{
	char	tra[20];
	char	*res;
	int		j;
	int		i;

	i = 0;
	nbr < 0 ? negative_handler(nbr, flags, wid) : 0;
	nbr == 0 ? zero_handler(&res, flags, pre, &i) : 0;
	j = i;
	while (nbr != 0)
	{
		tra[j++] = nbr % 10 * ((*flags & NEG) > 0 ? -1 : 1) + '0';
		nbr /= 10;
	}
	adjustment_wid_pre(flags, wid, pre, j);
	res = (char *)malloc(sizeof(char) * (i + (*wid > 0 ? *wid : 0) + (*pre > 0 ? *pre : 0)));
	fill_width(&res, flags, wid, &i);
	while ((*pre)-- > 0)
		res[i++] = '0';
	while (--j >= 0)
		res[i++] = tra[j];
	while ((*wid)-- > 0)
		res[i++] = (*flags << 56) >> 56;
	write(1, res, i);
	free(res);
	return (i);
}
