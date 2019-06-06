/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:28:00 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/06 18:29:50 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			rec_to_n(int *n)
{
	EJECT(BUFF_SIZE);
	*n = BUFF.g_bytes;
}

void			zeroing_buff(int *wid_pre)
{
	BUFF.g_count = 0;
	BUFF.g_bytes = 0;
	BUFF.g_fd = 1;
	BUFF.g_error = 0;
	wid_pre[0] = 0;
	wid_pre[1] = 0;
}

int				shift(size_t *flags, int howmuch, char direction)
{
	if (direction == 'l')
	{
		*flags <<= howmuch;
		*flags >>= howmuch;
	}
	else if (direction == 'r')
	{
		*flags >>= howmuch;
		*flags <<= howmuch;
	}
	return (1);
}
