/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_any_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:33:25 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/26 13:17:07 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_any_char(wchar_t c, size_t *flags, int *wid)
{
	(*wid)--;
	if (!(*flags & BIA))
		while ((*wid)-- > 0 && EJECT(1))
			g_buff__.g_buff[g_buff__.g_count++] = (*flags << 56) >> 56;
	EJECT(1);
	*flags & UNI && c > 127 ? uni(c) :
	(g_buff__.g_buff[g_buff__.g_count++] = c);
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = (*flags << 56) >> 56;
}
