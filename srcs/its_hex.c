/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: releanor <releanor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:55:06 by releanor          #+#    #+#             */
/*   Updated: 2020/03/06 20:00:16 by releanor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		hex_printer_2(t_struct *params, char *s)
{
	if ((!params->width && params->dot && params->zero_arg
	&& params->prec_zero) || (!params->width && params->dot
	&& !params->prec && !params->prec_zero && params->zero_arg))
		return (0);
	if (params->width && params->dot &&
	params->zero_arg && !params->prec)
		params->n_printed_here += write(1, " ", 1);
	else
		params->n_printed_here += write(1, s, params->len_before);
	if (params->width && params->minus)
		while (params->n_printed_here < params->width)
			params->n_printed_here += write(1, " ", 1);
	return (1);
}

void	hex_printer(t_struct *params, char *s, int indent)
{
	if (params->width > params->len_before)
		indent = params->width - params->len_before;
	if (params->negative || params->plus || params->space)
		indent--;
	if (params->hash_case_zero)
	{
		params->n_printed_here += (params->small_hex == 1) ?
				write(1, "0x", 2) : write(1, "0X", 2);
		indent -= 2;
	}
	if (params->width > params->len_before && !params->minus)
	{
		while (indent--)
		{
			params->n_printed_here += (params->zero
					&& !params->prec) ? write(1, "0", 1) :
							write(1, " ", 1);
		}
	}
	if (params->space && !params->negative)
		params->n_printed_here += write(1, " ", 1);
	hex_printer_2(params, s);
}

void	hex_from_fmt_2(t_struct *params, char *s, int indent)
{
	if (params->hash)
	{
		s = hex_hash(params, s);
		params->hash = 0;
	}
	params->len_before = ft_strlen(s);
	if (params->plus)
		params->plus = 0;
	if (params->space)
		params->space = 0;
	hex_printer(params, s, indent);
	params->n_printed += params->n_printed_here;
	free(s);
	bzero_struct(params, 0);
}

void	hex_from_fmt(t_struct *params, uintmax_t num, int i)
{
	char	*s;
	int		indent;

	indent = 0;
	params->len_before = uint_num_len(num, 16);
	s = (params->small_hex == 1) ? \
    itoa_base_uint(num, 16) :
    		itoa_base_uppercase(num, 16);
	hex_hash_checker(params, num);
	if (params->prec > params->len_before)
		s = hex_with_prec(params, s, i);
	if (params->hash && params->zero &&
	params->width && !params->prec)
	{
		params->hash_case_zero++;
		params->hash = 0;
	}
	hex_from_fmt_2(params, s, indent);
}

void	its_hex(va_list args, t_struct *params, char spec)
{
	uintmax_t num;

	num = 0;
	if (!params->length)
		num = va_arg(args, unsigned int);
	if (params->length == SHORTSHORT)
		num = (unsigned char)va_arg(args, unsigned int);
	if (params->length == SHORT)
		num = (unsigned short)va_arg(args, unsigned int);
	if (params->length == LONG)
		num = (unsigned long)va_arg(args, unsigned long);
	if (params->length == LONGLONG)
		num = (unsigned long long)va_arg(args,
				unsigned long long);
	if (params->length == SIZE_T)
		num = (size_t)va_arg(args, size_t);
	if (params->length == INT_UINT_MAX)
		num = (uintmax_t)va_arg(args, uintmax_t);
	params->small_hex = (spec == 'x') ? 1 : 0;
	hex_from_fmt(params, num, 0);
}
