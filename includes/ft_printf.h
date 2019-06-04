/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:49:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/04 20:55:29 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <wchar.h>
# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>

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
# define POI 	17592186044416
# define BIG	35184372088832
# define PTR	70368744177664
# define FLO	140737488355328
# define NEG	281474976710656
# define UNI	562949953421312
# define EXP	1125899906842624
# define INF	2251799813685248
# define ZER	4503599627370496
# define UND	9007199254740992
# define NUL	18014398509481984
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
# define EJECT(x)		((g_buff__.g_count + x) >= BUFF_SIZE ? eject() : 1)
# define BUFF			g_buff__

# define SPEC			(*flags << 40) >> 56
# define BASE			((*flags << 48) >> 56)
# define SIGN			(*flags << 56) >> 56

# define KARATSUBA_MIN 256

typedef union			u_nbr
{
	long double			nbr;
	short				array[5];
}						t_nbr;

typedef struct			s_long
{
	long long			*nbr;
	long long			len;
}						t_long;	

typedef struct			s_bits
{
	unsigned long long	mant: 64;
	long long			expo: 15;
	long long			sign: 1;
	int					size;
	int					bit;
	int					mid;
	int					exp;
	t_nbr				nbr;
}						t_bits;

typedef struct			s_karatsuba_var
{
	t_long				res;
	t_long				a_l;
	t_long				a_r;
	t_long				b_l;
	t_long				b_r;
	t_long				res_1;
	t_long				res_2;
	t_long				res_3;
}						t_karatsuba_var;

typedef struct			s_buff
{
	char				g_buff[BUFF_SIZE];
	int					g_count;
	int					g_bytes;
	int					g_fd;
	int					g_error;
}						t_buff_manage;

extern t_buff_manage	g_buff__;

void					uni(wchar_t c);
int						shift(size_t *flags, int howmuch, char direction);
int						width_collector(const char **str, va_list *list,
						size_t *flags, int *wid);
int						precision_collector(const char **str, va_list *list,
						size_t *flags, int *pre);
void					file_descriptor(const char **str, va_list *list);
void					colour_chooser(const char **str);
int						eject(void);
int						putfloat(char **tra, t_bits *tally, size_t *flags,
						int *pre);
int						ft_printf(const char *format, ...);
void					fill_width(size_t *flags, int *wid);
void					constructor(size_t *flags);
void					char_handler(va_list *list, size_t *flags,
						int *wid);
void					print_double(long double nbr, size_t *flags,
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
void					print_usual_string(char *s, size_t *flags,
						int *wid, int *pre);
void					adjustment_wid_pre(size_t *flags, int *wid,
						int *pre, int i);
void					inf_handler(size_t *flags);
void					roundd(char **str, int *pre, int zer, int che);
void					get_bits(t_bits *tally, long double *nbr,
						size_t *flags, int *pre);
void					hexadecimal_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					unsigned_decimal_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					print_expo_double(long double nbr, size_t *flags,
						int *wid, int *pre);
void					print_double_g_f(long double nbr, size_t *flags,
						int *wid, int *pre);
void					date_nprint(va_list *list, size_t *flags, int *wid,
						int *pre);
void					hexadouble_handler(va_list *list, size_t *flags,
						int *wid, int *pre);
void					print_hexadouble(long double nbr, size_t *flags,
						int *wid, int *pre);
void					print_date(long long iso, size_t *flags, int *wid, int *pre);
int						add_expo(char **str, size_t *flags, t_bits *tally, int *pre);
int						calc_expo(char **med, int *pre, int sta, int end);
void					add_power(char **med, int pwr, int cou);
void					print_hexadouble(long double nbr, size_t *flags, int *wid, int *pre);
void					add_power_neg(char **a, int pwr);
int						ft_atoi(const char *str);
void					ft_bzero(void *s, size_t n);
int						ft_isspace(int c);
int						ft_strcmp(const char *s1, const char *s2);
size_t					ft_strlen(const char *s);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					rec_to_n(int *n);
void					zeroing_buff(int *wid_pre);
void					test(t_long *nbr, int power);
void					init_long(t_long *a, int nbr);

#endif
