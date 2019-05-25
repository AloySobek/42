/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:49:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/25 20:11:34 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# define A(x)	(x == 'c' || x == 'C' || x == 's' || x == 'S' || x == 'd')
# define B(x)	(x == 'D' || x == 'i' || x == 'u' || x == 'U' || x == 'f')
# define C(x)	(x == 'F' || x == 'e' || x == 'E' || x == 'g' || x == 'G')
# define D(x)	(x == 'a' || x == 'A' || x == 'x' || x == 'X' || x == 'o')
# define E(x)	(x == 'O' || x == 'p' || x == '%' || x ==  0  || x == 'n')
# define F(x)	(x == 'b' || x == 'B' || x == 'r' || x == 'k')
# define CONV(x)(A(x) || B(x) || C(x) || D(x) || E(x) || F(x))

# define BIA	1099511627776
# define PLU	2199023255552
# define SPA	4398046511104
# define HAS	8796093022208
# define POI	17592186044416
# define BIG	35184372088832
# define PTR	70368744177664
# define END	140737488355328
# define NEG	281474976710656
# define UNI	562949953421312
# define DOL	1125899906842624
# define INF	2251799813685248
# define ZER	4503599627370496
# define UND	9007199254740992
# define FLO	18014398509481984
# define NAN	36028797018963968
# define HH		72057594037927936
# define LL		144115188075855872
# define BL		288230376151711744
# define H		576460752303423488
# define L		1152921504606846976
# define J		2305843009213693952
# define Z		4611686018427387904
# define T		9223372036854775808U

# define BUFF_SIZE		256
# define SPEC			(*flags << 40) >> 56
# define BASE			((*flags << 48) >> 56)
# define SIGN			(*flags << 56) >> 56
# define EJECT(x)		((g_count + x) >= BUFF_SIZE ? eject() : 1)

typedef union			u_nbr
{
	long double			nbr;
	short				array[5];
}						t_nbr;

typedef struct			s_bits
{
	unsigned long long	mant: 64;
	long long			expo: 15;
	long long			sign: 1;
	int					size;
	t_nbr				nbr;
}						t_bits;

extern char				g_buff[BUFF_SIZE];
extern int				g_count;
extern int				g_bytes;
extern int				g_fd;

void					uni(wchar_t c);
int						eject(void);
int						putfloat(char **tra, t_bits *tally, size_t *flags,
						int *pre);
int						ft_printf(const char *format, ...);
void					g_handler(va_list *list, size_t *flags, int *wid,
						int *pre);
void					fill_width(size_t *flags, int *wid, int *pre);
void					constructor(size_t *flags, int *pre);
int						zero_handler(size_t *flags, int *wid, int *pre);
void					char_handler(va_list *list, size_t *flags,
						int *wid);
void					print_double(long double nbr, size_t *flags,
						int *wid, int *pre);
void					expo_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					print_sig_dig(intmax_t nbr, size_t *flags,
						int *wid, int *pre);
void					print_uns_dig(uintmax_t nbr, size_t *flags,
						int *wid, int *pre);
void					octal_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					string_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					print_any_char(wchar_t c, size_t *flags,
						int *wid);
void					double_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					binary_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					decimal_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					pointer_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					print_uni_string(wchar_t *s, size_t *flags,
						int *wid, int *pre);
void					calculation_expo(long double *nbr, int *expo);
void					print_usual_string(char *s, size_t *flags,
						int *wid, int *pre);
void					adjustment_wid_pre(size_t *flags, int *wid,
						int *pre, int i);
void					inf_handler(size_t *flags, int *wid, int *pre);
void					roundd(char **str, int n, int *pre);
void					get_bits(t_bits *tally, long double *nbr,
						size_t *flags, int *pre);
void					flags_collector(const char **str, va_list *list,
						size_t *flags, int *wid, int *pre);
void					hexadecimal_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					unsigned_decimal_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					print_expo_double(long double nbr, size_t *flags,
						int *wid, int *pre);
void					print_double_g_f(long double nbr, size_t *flags,
						int *wid, int *pre);
void					date_non_printable_handler(va_list *list, size_t *flags,
						int *wid, int *pre);

#endif
