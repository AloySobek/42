/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:49:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/14 23:20:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"

#define test(x)

# define A(x)		(x == 'c' || x == 'C' || x == 's' || x == 'S' || x == 'd')
# define B(x)		(x == 'D' || x == 'i' || x == 'u' || x == 'U' || x == 'f')
# define C(x)		(x == 'F' || x == 'e' || x == 'E' || x == 'g' || x == 'G')
# define D(x)		(x == 'a' || x == 'A' || x == 'x' || x == 'X' || x == 'o')
# define E(x)       (x == 'O' || x == 'p' || x == '%' || x ==  0  || x == 'n')
# define F(x)		(x == 'b' || x == 'B')
# define CONV(x)	(A(x) || B(x) || C(x) || D(x) || E(x) || F(x))

# define BIA		1099511627776
# define PLU		2199023255552
# define SPA		4398046511104
# define HAS		8796093022208
# define POI		17592186044416
# define BIG		35184372088832
# define PTR		70368744177664
# define END		140737488355328
# define NEG        281474976710656
# define UNI        562949953421312
# define DOL		1125899906842624
# define APO		2251799813685248
# define SOON		4503599627370496
# define HH			72057594037927936
# define LL			144115188075855872
# define BL			288230376151711744
# define H			576460752303423488
# define L			1152921504606846976
# define J			2305843009213693952
# define Z			4611686018427387904
# define T			9223372036854775808U

# define BUFF_SIZE	4096

extern char *g_buff;
extern int g_count;
extern int g_bytes;

int					ft_printf(const char *format, ...);
int 				binary_handler(va_list *list, size_t *flags, int *wid, int *pre);
int					double_handler(va_list *list, size_t *flags, int *wid, int *pre);
int					expo_handler(va_list *list, size_t *flags, int *wid, int *pre);
int					expt_handler(va_list *list, size_t *flags, int *wid, int *pre);
void				flags_collector(const char **str, va_list *list, size_t *flags, int *wid, int *pre);
int                 putfloat(long double nbr, size_t *flags, int *wid, int *pre);
int					eject(void);
void				hexadecimal_handler(va_list *list, size_t *flags, int *wid, int *pre);
void				decimal_handler(va_list *list, size_t *flags, int *wid, int *pre);
void				unsigned_decimal_handler(va_list *list, size_t *flags, int *wid, int *pre);
void				octal_handler(va_list *list, size_t *flags, int *wid, int *pre);
void				pointer_handler(va_list *list, size_t *flags, int *wid, int *pre);
void				print_sig_dig(intmax_t nbr, size_t *flags, int *wid, int *pre);
void				char_handler(va_list *list, size_t *flags, int *wid);
void				string_handler(va_list *list, size_t *flags, int *wid, int *pre);
void				print_any_string(wchar_t *s, size_t *flags, int *wid, int *pre);
void				print_any_char(wchar_t c, size_t *flags, int *wid);
void				print_uns_dig(uintmax_t nbr, size_t *flags, int *wid, int *pre);
void				print_double(long double nbr, size_t *flags, int *wid, int *pre);
void				print_expo_double(long double nbr, size_t *flags, int *wid, int *pre);
void				uni(wchar_t c);
void				constructor(size_t *flags);
void                adjustment_wid_pre(size_t *flags, int *wid, int *pre, int i);
void				zero_handler(size_t *flags, int *pre);
void 				fill_width(size_t * flags, int *wid);

#endif