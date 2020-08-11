/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coclayto <coclayto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:38:17 by releanor          #+#    #+#             */
/*   Updated: 2020/06/15 01:10:20 by coclayto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	str_printer_2(t_struct *params)
{
	if (params->width > params->len_before && !params->minus && !params->dot)
		params->indent = params->width - params->len_before;
	else if (params->width && params->width > params->len_before
	         && params->prec && params->prec < params->len_before)
		params->indent = params->width - params->prec;
	else if (params->width > params->len_before && params->prec
	&& params->prec > params->len_before)
		params->indent = params->width - params->len_before;
	else if (params->width && params->dot && !params->prec
	&& !params->prec_zero)
		params->indent = params->width;
	else if (params->width && params->dot && params->prec
	         && !params->prec_zero && params->width > params->prec)
		params->indent = params->width - params->prec;
}

void	str_printer(t_struct *params, char *s)
{
	if (params->dot && params->prec & params->prec_zero)
		params->width = 0;
	if (!params->minus)
		str_printer_2(params);
	while (params->indent--)
		params->n_printed_here += (params->zero) ? write(1, "0", 1)
				: write(1, " ", 1);
	if (params->prec && params->prec < params->len_before)
	{
		if (params->width && params->width > params->prec && !params->minus)
			while (params->n_printed_here < params->width)
				params->n_printed_here += write(1, s, params->prec);
		else
			while (params->n_printed_here < params->prec)
				params->n_printed_here += write(1, s, params->prec);
	}
	else if (params->dot && !params->prec)
		write(1, "", 0);
	else
		params->n_printed_here += write(1, s, params->len_before);
	if (params->width && params->minus)
		while (params->n_printed_here < params->width)
			params->n_printed_here += write(1, " ", 1);
	params->n_printed += params->n_printed_here;
}

void	its_str(va_list args, t_struct *params)
{
	char	*s;

	if (!(s = (char *)va_arg(args, char *)))
		s = "(null)";
	params->len_before = ft_strlen(s);
	str_printer(params, s);
	bzero_struct(params, 0);
}
