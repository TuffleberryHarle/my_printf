/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: releanor <releanor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:34:13 by releanor          #+#    #+#             */
/*   Updated: 2020/03/06 12:33:06 by releanor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	int_checker(t_struct *params)
{
	if (params->negative && params->zero)
		params->n_printed_here += write(1, "-", 1);
	if (params->plus && !params->negative && params->zero)
		params->n_printed_here += write(1, "+", 1);
	if (params->space && !params->negative && params->zero)
		params->n_printed_here += write(1, " ", 1);
}

int		int_printer_2(t_struct *params, char *s)
{
	if ((!params->width && params->dot && params->zero_arg
	&& params->prec_zero) || (!params->width &&
	params->dot && !params->prec && !params->prec_zero
	&& params->zero_arg))
		return (0);
	if (params->width && params->dot && params->zero_arg
	&& !params->prec)
		if (params->plus)
			write(1, "", 0);
		else
			params->n_printed_here += write(1, " ", 1);
	else
		params->n_printed_here += write(1, s, params->len_before);
	if (params->width && params->minus)
		while (params->n_printed_here < params->width)
			params->n_printed_here += write(1, " ", 1);
	return (1);
}

void	int_printer(t_struct *params, char *s, int indent)
{
	int_checker(params);
	if (params->width > params->len_before)
		indent = params->width - params->len_before;
	if (params->negative || params->plus || params->space)
		indent--;
	if (params->zero_arg && params->plus && params->dot &&
	params->width && !params->prec)
		indent++;
	if (params->width > params->len_before && !params->minus)
	{
		while (indent--)
		{
			params->n_printed_here += (params->zero
					&& !params->prec) \
			? write(1, "0", 1) : \
			write(1, " ", 1);
		}
	}
	if (params->negative && !params->zero)
		params->n_printed_here += write(1, "-", 1);
	if (params->plus && !params->negative && !params->zero)
		params->n_printed_here += write(1, "+", 1);
	if (params->space && !params->negative && !params->zero)
		params->n_printed_here += write(1, " ", 1);
	int_printer_2(params, s);
}

void	int_from_fmt(t_struct *params, intmax_t num, int i)
{
	char	*s;
	int		indent;

	indent = 0;
	params->len_before = num_len(num, 10);
	s = itoa_base(params, num, 10);
	s = int_overflow_checker(num, s);
	if (params->dot)
		params->zero = 0;
	if ((num == 0) && (params->len_before == 1))
		params->zero_arg++;
	if (params->prec && params->prec \
 > params->len_before && !params->negative)
		s = int_with_prec(params, s, i);
	else if (params->prec && params->prec > \
	params->len_before && params->negative)
		s = int_with_prec(params, s, i);
	params->len_before = ft_strlen(s);
	int_printer(params, s, indent);
	params->n_printed += params->n_printed_here;
	if (num != LLONG_MAX && num != LLONG_MIN)
		free(s);
	bzero_struct(params, 0);
}

void	its_int(va_list args, t_struct *params)
{
	intmax_t num;

	num = 0;
	if (params->length == 0)
		num = (int)va_arg(args, int);
	if (params->length == SHORTSHORT)
		num = (signed char)va_arg(args, int);
	if (params->length == SHORT)
		num = (short int)va_arg(args, int);
	if (params->length == LONG)
		num = (long int)va_arg(args, long int);
	if (params->length == LONGLONG)
		num = (long long int)va_arg(args, long long int);
	if (params->length == SIZE_T)
		num = (size_t)va_arg(args, size_t);
	if (params->length == INT_UINT_MAX)
		num = (intmax_t)va_arg(args, intmax_t);
	if (params->dot > 1 && params->prec)
	{
		params->dot = 0;
		params->zero = 0;
		params->prec = 0;
	}
	int_from_fmt(params, num, 0);
}
