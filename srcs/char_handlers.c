/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 12:26:23 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/30 18:26:08 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	char_handler(va_list *list, size_t *flags, int *wid)
{
	SPEC == 'C' || *flags & L ? *flags |= UNI : 0;
	*flags & NUL && !(*flags & BIA) ? *flags |= 48 : 0;
	if (SPEC == '%')
		print_any_char('%', flags, wid);
	else
		print_any_char(va_arg(*list, wchar_t), flags, wid);
}

void	string_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	SPEC == 'C' || *flags & L ? *flags |= UNI : 0;
	*flags & NUL && !(*flags & BIA) ? *flags |= 48 : 0;
	if (*flags & UNI)
		print_uni_string(va_arg(*list, wchar_t *), flags, wid, pre);
	else
		print_usual_string(va_arg(*list, char *), flags, wid, pre);
}
