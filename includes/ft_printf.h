/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:02:54 by tharle            #+#    #+#             */
/*   Updated: 2020/08/13 16:02:57 by tharle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include "../libft/includes/libft.h"

# define ALL_SYM		"cCsSpPdDiIoOuUxXfFrhlLjz0123456789 .-+#%rb"
# define TYPE_SYM		"cCsSpPdDiIoOuUxXfF%rb"
# define FLAGS			" .-+#0hlLjz6"
# define SHORT			1
# define SHORTSHORT		2
# define LONG			3
# define LONGLONG		4
# define LONGDOUBLE		7
# define SIZE_T			8
# define _UINT_MAX	9

typedef struct	s_struct
{
	char		*format;
	int			n_printed;
	int			n_printed_here;
	int			i;
	int			negative;
	int			minus;
	int			plus;
	int			space;
	int			zero;
	int			zero_arg;
	int			hash;
	int			hash_case;
	int			hash_case_zero;
	int			small_hex;
	int			dot;
	int			width;
	int			prec;
	int			prec_was;
	int			prec_zero;
	int			indent;
	int			len;
	int			after_perc;
	char		*f_before;
	char		*f_after;
	int			len_before;
	int			len_after;
}				t_struct;

int				ft_printf(const char *fmt, ...);
int				parser(va_list args, const char *fmt, t_struct *params);
int				usual_parser(va_list args, t_struct *params, const char *fmt);
int				after_perc_parser(t_struct *params, const char *fmt);
int				convertor(va_list args, char letter, t_struct *params);
int				convertor_2(va_list args, char spec, t_struct *params);
int				modifier(va_list args, const char *fmt, t_struct *params);
void			bzero_struct(t_struct *params, int full);

void			length_hooker(const char *fmt, t_struct *prms);
void			flag_modifier(const char *fmt, t_struct	*params);
void			width_determer(const char *fmt, t_struct	*prm);
void			precision_determer(const char *fmt, t_struct	*prm);

void			its_int(va_list args, t_struct *params);
void			int_from_fmt(t_struct *params, intmax_t num, int i);
void			int_printer(t_struct *params, char *s, int indent);
int				int_printer_2(t_struct *params, char *s);
char			*int_with_prec(t_struct *params, char *s, int i);
void			int_checker(t_struct *params);
char			*int_overflow_checker(intmax_t num, char *s);

void			its_char(va_list args, t_struct *params);
void			char_printer(t_struct *params, char c, int indent);

void			its_str(va_list args, t_struct *params);
void			str_printer(t_struct *params, char *s);
void			str_printer_2(t_struct *params);

void			its_ptr(va_list args, t_struct *params);
void			ptr_printer(t_struct *params, char *s);
void			ptr_printer_2(t_struct *params, char*s);
void			ptr_printer_3(t_struct *params, char*s);
void			ptr_printer_4(t_struct *params, char*s);
void			ptr_checker(t_struct *params);

void			its_uint(va_list args, t_struct *params, char spec);
void			uint_from_fmt(t_struct *params, uintmax_t num, int i);
char			*uint_with_prec(t_struct *params, char *s, int i);
void			uint_printer(t_struct *params, char *s, int indent);
int				uint_printer_2(t_struct *params, char *s);

void			its_oct(va_list args, t_struct *params);
void			oct_from_fmt(t_struct *params, uintmax_t num, int i);
char			*oct_with_prec(t_struct *prms, char *s, int i);
char			*oct_hash(t_struct *params, char *s);
void			oct_hash_checker(t_struct *prms, int num);
void			oct_printer(t_struct *params, char *s, int indent);
int				oct_printer_2(t_struct *prms, char *s);

void			its_hex(va_list args, t_struct *params, char spec);
void			hex_from_fmt(t_struct *params, uintmax_t num, int i);
void			hex_from_fmt_2(t_struct *params, char *s, int indent);
char			*hex_hash(t_struct *params, char *s);
char			*hex_with_prec(t_struct *params, char *s, int i);
void			hex_hash_checker(t_struct *params, int num);
void			hex_printer(t_struct *params, char *s, int indent);
int				hex_printer_2(t_struct *params, char *s);

void			its_float(va_list args, t_struct *params);
void			float_solver(long double num, t_struct *params);
char			*int_solver(long double num, int end);
void			decimal_solver(long double num, t_struct *params);
int				is_inf_nan(t_struct *params, long double num);
int				is_odd(char symb);
void			rounding_up(long double num, t_struct *params, int i);
void			f_increment(t_struct *params);
void			float_printer(t_struct *params);
void			float_printer_2(t_struct *params);

int				num_len(intmax_t num, int base);
int				uint_num_len(uintmax_t num, int base);
int				float_num_len(long double num);
long double		ft_atof(char *str);
char			*itoa_base(t_struct *params, intmax_t num, int base);
char			*itoa_base_uint(uintmax_t num, int base);
char			*itoa_base_uppercase(uintmax_t num, int base);

long double		to_power(long long n, int i);
void			percent_printer(t_struct *params);

void			unprintable_creator(va_list args, t_struct *params);
int				len_determer(char *s, int i);
void			str_recreator(char *s, char *s_unpr, int i, int j);

void			type_b(va_list args, t_struct *params);
void			binary_from_fmt(t_struct *params, uintmax_t num, int i);

#endif
