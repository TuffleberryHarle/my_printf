/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_oct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: releanor <releanor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:36:52 by releanor          #+#    #+#             */
/*   Updated: 2020/03/13 04:36:11 by releanor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		oct_printer_2(t_struct *prms, char *s)
{
	if ((!prms->width && prms->dot && prms->zero_arg
	&& prms->prec_zero)
	|| (!prms->width && prms->dot && !prms->prec &&
	!prms->prec_zero && prms->zero_arg))
	{
		if (prms->hash_case)
		{
			prms->n_printed_here += write(1, "0", 1);
			return (1);
		}
		return (0);
	}
	if (prms->width && prms->dot && prms->zero_arg &&
	!prms->prec && !prms->hash_case)
		prms->n_printed_here += write(1, " ", 1);
	else
		prms->n_printed_here += write(1, s, prms->len_before);
	if (prms->width && prms->minus)
		while (prms->n_printed_here < prms->width)
			prms->n_printed_here += write(1, " ", 1);
	return (1);
}

void	oct_printer(t_struct *params, char *s, int indent)
{
	if (params->width > params->len_before)
		indent = params->width - params->len_before;
	if (params->negative || params->plus || params->space)
		indent--;
	if (params->width > params->len_before && !params->minus)
	{
		while (indent--)
		{
			params->n_printed_here += (params->zero && !params->prec)
					? write(1, "0", 1)
					: write(1, " ", 1);
		}
	}
	if (params->negative)
		params->n_printed_here += write(1, "-", 1);
	if (params->space && !params->negative)
		params->n_printed_here += write(1, " ", 1);
	oct_printer_2(params, s);
}

void	oct_hash_checker(t_struct *prms, int num)
{
	if ((num == 0) && (prms->len_before == 1))
		prms->zero_arg++;
	if (!prms->width && prms->hash && prms->dot && prms->zero_arg)
		prms->hash_case++;
	if (prms->hash && prms->width && !prms->prec && prms->zero_arg)
		prms->hash_case++;
	if (prms->hash && prms->dot && !prms->prec
	&& !prms->prec_zero && prms->zero_arg)
		prms->hash = 0;
	if (prms->zero_arg)
		prms->hash = 0;
	if (prms->hash && prms->dot && prms->prec > prms->len_before)
		prms->hash = 0;
}

void	oct_from_fmt(t_struct *params, uintmax_t num, int i)
{
	char	*s;
	int		indent;

	indent = 0;
	params->len_before = uint_num_len(num, 8);
	s = itoa_base_uint(num, 8);
	oct_hash_checker(params, num);
	if (params->hash)
		s = oct_hash(params, s);
	if (params->prec > params->len_before)
		s = oct_with_prec(params, s, i);
	params->len_before = ft_strlen(s);
	if (params->plus)
		params->plus = 0;
	if (params->space)
		params->space = 0;
	oct_printer(params, s, indent);
	params->n_printed += params->n_printed_here;
	free(s);
	bzero_struct(params, 0);
}

void	its_oct(va_list args, t_struct *params)
{
	uintmax_t num;

	num = 0;
	if (params->length == 0)
		num = va_arg(args, unsigned int);
	if (params->length == SHORTSHORT)
		num = (unsigned char)va_arg(args, unsigned int);
	if (params->length == SHORT)
		num = (unsigned short)va_arg(args, unsigned int);
	if (params->length == LONG)
		num = (unsigned long)va_arg(args, unsigned long);
	if (params->length == LONGLONG)
		num = (unsigned long long)va_arg(args, unsigned long long);
	oct_from_fmt(params, num, 0);
}
