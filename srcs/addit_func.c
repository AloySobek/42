/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:31:18 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/29 16:34:12 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_thirsty(char c)
{
	if (c == 21)
		write(g_buff__.g_fd, "[NAK]", 5);
	else if (c == 22)
		write(g_buff__.g_fd, "[SYN]", 5);
	else if (c == 23)
		write(g_buff__.g_fd, "[ETB]", 5);
	else if (c == 24)
		write(g_buff__.g_fd, "[CAN]", 5);
	else if (c == 25)
		write(g_buff__.g_fd, "[EM]", 4);
	else if (c == 26)
		write(g_buff__.g_fd, "[SUB]", 5);
	else if (c == 27)
		write(g_buff__.g_fd, "[ESC]", 5);
	else if (c == 28)
		write(g_buff__.g_fd, "[FS]", 4);
	else if (c == 29)
		write(g_buff__.g_fd, "[GS]", 4);
	else if (c == 30)
		write(g_buff__.g_fd, "[RS]", 4);
	else if (c == 31)
		write(g_buff__.g_fd, "[US]", 4);
}

void	print_twenty(char c)
{
	if (c == 11)
		write(g_buff__.g_fd, "[VT]", 5);
	else if (c == 12)
		write(g_buff__.g_fd, "[FF]", 4);
	else if (c == 13)
		write(g_buff__.g_fd, "[CR]", 4);
	else if (c == 14)
		write(g_buff__.g_fd, "[SO]", 4);
	else if (c == 15)
		write(g_buff__.g_fd, "[SI]", 4);
	else if (c == 16)
		write(g_buff__.g_fd, "[DLE]", 5);
	else if (c == 17)
		write(g_buff__.g_fd, "[DC1]", 5);
	else if (c == 18)
		write(g_buff__.g_fd, "[DC2]", 5);
	else if (c == 19)
		write(g_buff__.g_fd, "[DC3]", 5);
	else if (c == 20)
		write(g_buff__.g_fd, "[DC4]", 5);
}

void	print_ten(char c)
{
	if (c == 0)
		write(g_buff__.g_fd, "[NUL]", 5);
	else if (c == 1)
		write(g_buff__.g_fd, "[SOH]", 5);
	else if (c == 2)
		write(g_buff__.g_fd, "[STX]", 5);
	else if (c == 3)
		write(g_buff__.g_fd, "[ETX]", 5);
	else if (c == 4)
		write(g_buff__.g_fd, "[EOT]", 5);
	else if (c == 5)
		write(g_buff__.g_fd, "[ENQ]", 5);
	else if (c == 6)
		write(g_buff__.g_fd, "[ACK]", 5);
	else if (c == 7)
		write(g_buff__.g_fd, "[BEL]", 5);
	else if (c == 8)
		write(g_buff__.g_fd, "[BS]", 4);
	else if (c == 9)
		write(g_buff__.g_fd, "[TAB]", 5);
	else if (c == 10)
		write(g_buff__.g_fd, "[LF]", 4);
}

/*void	print_non_printable(char *str, size_t *flags, int *wid, int *pre)
{
	while (*str != 0)
	{
		*str >= 0 && *str <= 10 ? print_ten(*str) : 0;
		*str > 10 && *str <= 20 ? print_twenty(*str) : 0;
		*str > 20 && *str <= 31 ? print_thirsty(*str) : 0;
		*str == 127 ? write(1, "[DEL]", 5) : 0;
		str++;
	}
}*/

/*void	print_date(long long iso, size_t *flags, int *wid, int *pre)
{
	char *time;
	int i;
	long long inter;
	int k;
	int z;

	k = 1;
	i = 0;
	time = (char *)malloc(1000);
	while ((inter /= 10))
		k *= 10;
	z = 4;
	while (z--)
	{
		time[i++] = iso / k;
		k /= 10;
		iso %= 10;
	}
	z = 2;
	
}*/

/*void	date_non_printable_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	SPEC == 'k' ? print_date(va_arg(*list, long long), flags, wid, pre) : 0;
	SPEC == 'r' ? print_non_printable(va_arg(*list, char *), flags, wid, pre) : 0;
	
}*/
