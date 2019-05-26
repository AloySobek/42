/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 13:33:18 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/26 15:29:29 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_buff_manage g_buff__;

int			eject(void)
{
	g_buff__.g_bytes += write(g_buff__.g_fd, g_buff__.g_buff, g_buff__.g_count);
	g_buff__.g_count = 0;
	return (1);
}

void		ever_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	if (SPEC == 'c' || SPEC == 'C' || SPEC == '%')
		char_handler(list, flags, wid);
	else if (SPEC == 's' || SPEC == 'S')
		string_handler(list, flags, wid, pre);
	else if (SPEC == 'd' || SPEC == 'D' || SPEC == 'i')
		decimal_handler(list, flags, wid, pre);
	else if (SPEC == 'u' || SPEC == 'U')
		unsigned_decimal_handler(list, flags, wid, pre);
	else if (SPEC == 'f' || SPEC == 'F')
		double_handler(list, flags, wid, pre);
	else if (SPEC == 'e' || SPEC == 'E')
		expo_handler(list, flags, wid, pre);
	else if (SPEC == 'g' || SPEC == 'G')
		g_handler(list, flags, wid, pre);
	else if (SPEC == 'x' || SPEC == 'X' || SPEC == 'p')
		hexadecimal_handler(list, flags, wid, pre);
	else if (SPEC == 'o' || SPEC == 'O')
		octal_handler(list, flags, wid, pre);
	else if (SPEC == 'b' || SPEC == 'B')
		binary_handler(list, flags, wid, pre);
	else if (SPEC == 'r' || SPEC == 'k')
		;//date_non_printable_handler(list, flags, wid, pre);
	else if (SPEC == 'a' || SPEC == 'A')
		hexadouble_handler(list, flags, wid, pre);
}

int			length_modifier_collector(const char **str, size_t *flags)
{
	if (**str == 'h' && *(*str + 1) == 'h')
		(!(*flags & J) && !(*flags & Z) && bi(flags, 8, 1)) ? *flags |= HH : 0;
	else if (**str == 'l' && *(*str + 1) == 'l')
		(!(*flags & J) && !(*flags & Z) && bi(flags, 8, 1)) ? *flags |= LL : 0;
	else if (**str == 'h' && *(*str - 1) != 'h' && *(*str + 1) != 'h')
		(!(*flags & J) && !(*flags & Z) && bi(flags, 8, 1)) ? *flags |= H : 0;
	else if (**str == 'l' && *(*str - 1) != 'l' && *(*str + 1) != 'l')
		(!(*flags & J) && !(*flags & Z) && bi(flags, 8, 1)) ? *flags |= L : 0;
	else if (**str == 'j' && bi(flags, 8, 1))
		*flags |= J;
	else if (**str == 'z' && bi(flags, 8, 1))
		*flags |= Z;
	else if (**str == 't' && bi(flags, 8, 1))
		*flags |= T;
	else if (**str == 'L' && bi(flags, 8, 1))
		*flags |= BL;
	else
		return (0);
	return (1);
}

void		flags_collector(const char **str, va_list *list, size_t *flags,
			int *wid, int *pre)
{
	while (!CONV(**str) && !(*flags & UND))
	{
		if (**str == '-')
			*flags |= BIA;
		else if (**str == '+')
			*flags |= PLU;
		else if (**str == ' ')
			*flags |= SPA;
		else if (**str == '#')
			*flags |= HAS;
		else if (**str == '0' && ((*(*str - 1) >= 0 && *(*str - 1) < 48) ||
				*(*str - 1) > 57) && (*flags |= FLO))
			*flags |= 48;
		else if (**str == '@' && *(*str + 1) == '{')
			color_chooser(str, flags);
		else if (**str == '>' && *(*str + 1) == '>' && *(*str + 2) == '{')
			file_descriptor(str, list, flags);
		else if (**str == '.' && precision_collector(str, list, flags, pre))
			continue;
		else if (((**str >= 48 && **str <= 57) || **str == '*') &&
				width_collector(str, list, flags, wid))
			continue;
		else if (length_modifier_collector(str, flags))
			;
		else if (**str != 'h' && **str != 'l' && (*flags |= UND) && EJECT(1))
			print_any_char(**str, flags, wid);
		(*str)++;
	}
	if ((*flags & BIA || *flags & POI) && *pre >= 0 && bi(flags, 8, 0))
		*flags |= 32;
	*flags |= (**str) << 16;
}

int			ft_printf(const char *format, ...)
{
	va_list	listv;
	size_t	flags;
	int		pre;
	int		wid;

	va_start(listv, format);
	g_buff__.g_count = 0;
	g_buff__.g_bytes = 0;
	g_buff__.g_fd = 1;
	pre = 0;
	wid = 0;
	while (*format)
		if (*format == '%' && !(flags = 0) && format++ && (flags |= 32))
		{
			flags_collector(&format, &listv, &flags, &wid, &pre);
			if (flags & UND)
				continue;
			*format && format++ ? ever_handler(&listv, &flags, &wid, &pre) : 0;
		}
		else if (EJECT(1))
			g_buff__.g_buff[g_buff__.g_count++] = *format++;
	va_end(listv);
	eject();
	return (g_buff__.g_bytes);
}
