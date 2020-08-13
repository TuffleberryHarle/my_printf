/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:06:12 by tharle            #+#    #+#             */
/*   Updated: 2020/08/13 16:06:15 by tharle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		convertor_2(va_list args, char spec, t_struct *params)
{
	if (spec == '%')
		percent_printer(params);
	else if (spec == 'r')
		unprintable_creator(args, params);
	else if (spec == 'b')
		type_b(args, params);
	else
		bzero_struct(params, 0);
	return (params->i);
}

int		convertor(va_list args, char letter, t_struct *params)
{
	if (letter == 'c' || letter == 'C')
		its_char(args, params);
	else if (letter == 'd' || letter == 'i'
	|| letter == 'D' || letter == 'I')
		its_int(args, params);
	else if (letter == 'u' || letter == 'U')
		its_uint(args, params, letter);
	else if (letter == 'f' || letter == 'F')
		its_float(args, params);
	else if (letter == 's' || letter == 'S')
		its_str(args, params);
	else if (letter == 'p' || letter == 'P')
		its_ptr(args, params);
	else if (letter == 'x' || letter == 'X')
		its_hex(args, params, letter);
	else if (letter == 'o' || letter == 'O')
		its_oct(args, params);
	return (convertor_2(args, letter, params));
}
