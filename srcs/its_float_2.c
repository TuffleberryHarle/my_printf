/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_float_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:07:23 by tharle            #+#    #+#             */
/*   Updated: 2020/08/13 16:07:25 by tharle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	float_printer_2(t_struct *params)
{
	int	i;

	i = 0;
	ft_putstr(params->f_before);
	params->n_printed_here += params->len_before;
	if ((params->hash || params->prec) && !ft_isalpha(params->f_before[0]))
		params->n_printed_here += write(1, ".", 1);
	if (params->prec)
	{
		while (i++ < params->prec - params->len_after)
			params->n_printed_here += write(1, "0", 1);
		ft_putstr(params->f_after);
		params->n_printed_here += params->len_after;
	}
	if (params->width && params->minus)
		while (params->n_printed_here < params->width)
			params->n_printed_here += write(1, " ", 1);
	params->n_printed += params->n_printed_here;
}

void	float_printer(t_struct *params)
{
	int len;
	int	indent;

	indent = 0;
	len = params->len_before + params->len_after;
	if ((params->hash || params->prec) && !ft_isalpha(params->f_before[0]))
		len++;
	if (params->width > len)
		indent = params->width - len;
	if (params->negative || params->plus || params->space)
		indent--;
	if (params->width > len && !params->minus && !params->zero)
		while (indent--)
			params->n_printed_here += write(1, " ", 1);
	if (params->space && !params->negative)
		params->n_printed_here += write(1, " ", 1);
	if (params->negative)
		params->n_printed_here += write(1, "-", 1);
	if (params->plus && !params->negative)
		params->n_printed_here += write(1, "+", 1);
	if (params->width > len && !params->minus && params->zero)
		while (indent--)
			params->n_printed_here += write(1, "0", 1);
	float_printer_2(params);
}

void	f_increment(t_struct *params)
{
	long double f_before;

	f_before = ft_atof(params->f_before);
	f_before++;
	params->f_before = itoa_base_uint((uintmax_t)f_before, 10);
}

int		is_odd(char symb)
{
	return ((symb - '0') % 2);
}

int		is_inf_nan(t_struct *params, long double num)
{
	params->len_before = 3;
	if (num == (1.0 / 0.0) || num == -(1.0 / 0.0))
	{
		if (num == -(1.0 / 0.0))
			params->negative = 1;
		params->f_before = "inf";
		float_printer(params);
		return (1);
	}
	if (!(num == num))
	{
		params->f_before = "nan";
		params->plus = 0;
		float_printer(params);
		return (1);
	}
	return (0);
}
