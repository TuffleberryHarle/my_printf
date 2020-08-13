/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:06:54 by tharle            #+#    #+#             */
/*   Updated: 2020/08/13 16:06:56 by tharle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	binary_from_fmt(t_struct *params, uintmax_t num, int i)
{
	char	*s;

	params->len_before = uint_num_len(num, 2);
	s = itoa_base_uint(num, 2);
	if (params->prec && params->prec > params->len_before)
	{
		s = uint_with_prec(params, s, i);
		params->len_before = ft_strlen(s);
	}
	if (params->plus)
		params->plus = 0;
	if (params->hash)
		params->hash = 0;
	if (params->space)
		params->space = 0;
	uint_printer(params, s, 0);
	params->n_printed += params->n_printed_here;
	free(s);
	bzero_struct(params, 0);
}

void	type_b(va_list args, t_struct *params)
{
	uintmax_t num;

	num = 0;
	if (params->len)
		num = (unsigned int)va_arg(args, int);
	else if (params->len == SHORTSHORT)
		num = (unsigned char)va_arg(args, int);
	else if (params->len == SHORT)
		num = (unsigned short)va_arg(args, int);
	else if (params->len == LONG)
		num = (unsigned long)va_arg(args, unsigned long);
	else if (params->len == LONGLONG)
		num = (unsigned long long)va_arg(args, \
		unsigned long long);
	if (params->len == SIZE_T)
		num = (size_t)va_arg(args, size_t);
	if (params->len == _UINT_MAX)
		num = (uintmax_t)va_arg(args, uintmax_t);
	binary_from_fmt(params, num, 0);
}
