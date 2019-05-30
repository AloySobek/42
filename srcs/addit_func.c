/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:31:18 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/30 20:02:46 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_thirsty(char c)
{
	if (c == 21)
		write(BUFF.g_fd, "[NAK]", 5);
	else if (c == 22)
		write(BUFF.g_fd, "[SYN]", 5);
	else if (c == 23)
		write(BUFF.g_fd, "[ETB]", 5);
	else if (c == 24)
		write(BUFF.g_fd, "[CAN]", 5);
	else if (c == 25)
		write(BUFF.g_fd, "[EM]", 4);
	else if (c == 26)
		write(BUFF.g_fd, "[SUB]", 5);
	else if (c == 27)
		write(BUFF.g_fd, "[ESC]", 5);
	else if (c == 28)
		write(BUFF.g_fd, "[FS]", 4);
	else if (c == 29)
		write(BUFF.g_fd, "[GS]", 4);
	else if (c == 30)
		write(BUFF.g_fd, "[RS]", 4);
	else if (c == 31)
		write(BUFF.g_fd, "[US]", 4);
}

void	print_twenty(char c)
{
	if (c == 11)
		write(BUFF.g_fd, "[VT]", 5);
	else if (c == 12)
		write(BUFF.g_fd, "[FF]", 4);
	else if (c == 13)
		write(BUFF.g_fd, "[CR]", 4);
	else if (c == 14)
		write(BUFF.g_fd, "[SO]", 4);
	else if (c == 15)
		write(BUFF.g_fd, "[SI]", 4);
	else if (c == 16)
		write(BUFF.g_fd, "[DLE]", 5);
	else if (c == 17)
		write(BUFF.g_fd, "[DC1]", 5);
	else if (c == 18)
		write(BUFF.g_fd, "[DC2]", 5);
	else if (c == 19)
		write(BUFF.g_fd, "[DC3]", 5);
	else if (c == 20)
		write(BUFF.g_fd, "[DC4]", 5);
}

void	print_ten(char c)
{
	if (c == 0)
		write(BUFF.g_fd, "[NUL]", 5);
	else if (c == 1)
		write(BUFF.g_fd, "[SOH]", 5);
	else if (c == 2)
		write(BUFF.g_fd, "[STX]", 5);
	else if (c == 3)
		write(BUFF.g_fd, "[ETX]", 5);
	else if (c == 4)
		write(BUFF.g_fd, "[EOT]", 5);
	else if (c == 5)
		write(BUFF.g_fd, "[ENQ]", 5);
	else if (c == 6)
		write(BUFF.g_fd, "[ACK]", 5);
	else if (c == 7)
		write(BUFF.g_fd, "[BEL]", 5);
	else if (c == 8)
		write(BUFF.g_fd, "[BS]", 4);
	else if (c == 9)
		write(BUFF.g_fd, "[TAB]", 5);
	else if (c == 10)
		write(BUFF.g_fd, "[LF]", 4);
}

void	rec_to_n(int *n)
{
	EJECT(BUFF_SIZE);
	*n = BUFF.g_bytes;
}

void		zeroing_buff(int *wid_pre)
{
	BUFF.g_count = 0;
	BUFF.g_bytes = 0;
	BUFF.g_fd = 1;
	BUFF.g_error = 0;
	wid_pre[0] = 0;
	wid_pre[1] = 0;
}

int		shift(size_t *flags, int howmuch, char direction)
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

void			print_date(long long iso, size_t *flags, int *wid, int *pre)
{
	long long	tmp;
	long long	k;
	int			i;

	k = 1;
	tmp = iso;
	while (tmp)
	{
		tmp /= 10;
		k *= 10;
	}
	k /= 10;
	i = 4;
	while (i--)
	{
		BUFF.g_buff[BUFF.g_count++] = iso / k + '0';
		iso %= k;
		k /= 10;
	}
	BUFF.g_buff[BUFF.g_count++] = '-';
	i = 2;
	while (i--)
	{
		BUFF.g_buff[BUFF.g_count++] = iso / k + '0';
		iso %= k;
		k /= 10;
	}
	BUFF.g_buff[BUFF.g_count++] = '-';
	i = 2;
	while (i--)
	{
		BUFF.g_buff[BUFF.g_count++] = iso / k + '0';
		iso %= k;
		k /= 10;
	}
	BUFF.g_buff[BUFF.g_count++] = 'T';
	i = 2;
	while (i--)
	{
		BUFF.g_buff[BUFF.g_count++] = iso / k + '0';
		iso %= k;
		k /= 10;
	}
	BUFF.g_buff[BUFF.g_count++] = ':';
	i = 2;
	while (i--)
	{
		BUFF.g_buff[BUFF.g_count++] = iso / k + '0';
		iso %= k;
		k /= 10;
	}
	BUFF.g_buff[BUFF.g_count++] = ':';
	i = 2;
	while (i--)
	{
		BUFF.g_buff[BUFF.g_count++] = iso / k + '0';
		iso %= k;
		k /= 10;
	}
	return ;
}

/*void	date_non_printable_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	SPEC == 'k' ? print_date(va_arg(*list, long long), flags, wid, pre) : 0;
	SPEC == 'r' ? print_non_printable(va_arg(*list, char *), flags, wid, pre) : 0;
	
}*/
