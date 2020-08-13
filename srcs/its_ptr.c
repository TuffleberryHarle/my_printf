/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:08:21 by tharle            #+#    #+#             */
/*   Updated: 2020/08/13 16:08:22 by tharle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ptr_printer_2(t_struct *params, char *s)
{
	while (params->indent--)
		params->n_printed_here += write(1, " ", 1);
	if (params->plus)
		params->n_printed_here += write(1, "+", 1);
	params->n_printed_here += write(1, "0x", 2);
	if (params->dot && !params->prec_was && !params->prec)
		write(1, "", 0);
	else
		params->n_printed_here += write(1, s, params->len_before);
}

void	ptr_printer_3(t_struct *params, char *s)
{
	if (params->plus)
		params->n_printed_here += write(1, "+", 1);
	params->n_printed_here += write(1, "0x", 2);
	while (params->indent--)
		params->n_printed_here += write(1, "0", 1);
	if (params->dot && !params->prec)
		write(1, "", 0);
	else
		params->n_printed_here += write(1, s, params->len_before);
}

void	ptr_printer_4(t_struct *params, char *s)
{
	if (params->plus)
		params->n_printed_here += write(1, "+", 1);
	params->n_printed_here += write(1, "0x", 2);
	if (params->dot && !params->prec)
		write(1, "", 0);
	else
		params->n_printed_here += write(1, s, params->len_before);
}

void	ptr_printer(t_struct *params, char *s)
{
	ptr_checker(params);
	if (params->width && params->width > params->len_before
		&& !params->zero && !params->minus)
		ptr_printer_2(params, s);
	else if (params->width && params->width > params->len_before
	&& params->zero && !params->minus)
		ptr_printer_3(params, s);
	else if (params->prec && params->prec > params->len_before)
	{
		params->n_printed_here += write(1, "0x", 2);
		while (params->n_printed_here < params->prec
										+ 2 - params->len_before)
			params->n_printed_here += write(1, "0", 1);
		params->n_printed_here += write(1, s, params->len_before);
	}
	else
		ptr_printer_4(params, s);
	if (params->width && params->minus)
		while (params->n_printed_here < params->width)
			params->n_printed_here += write(1, " ", 1);
}

void	its_ptr(va_list args, t_struct *params)
{
	uintmax_t	ptr;
	char		*s;

	ptr = (uintmax_t)va_arg(args, void *);
	params->len_before = uint_num_len(ptr, 16);
	s = itoa_base_uint(ptr, 16);
	ptr_printer(params, s);
	params->n_printed += params->n_printed_here;
	free(s);
	bzero_struct(params, 0);
}
