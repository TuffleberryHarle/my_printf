/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_uint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: releanor <releanor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:43:43 by releanor          #+#    #+#             */
/*   Updated: 2020/03/13 02:18:27 by releanor         ###   ########.fr       */
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
	if (params->length)
		num = (unsigned int)va_arg(args, int);
	else if (params->length == SHORTSHORT)
		num = (unsigned char)va_arg(args, int);
	else if (params->length == SHORT)
		num = (unsigned short)va_arg(args, int);
	else if (params->length == LONG)
		num = (unsigned long)va_arg(args, unsigned long);
	else if (params->length == LONGLONG)
		num = (unsigned long long)va_arg(args, \
		unsigned long long);
	if (params->length == SIZE_T)
		num = (size_t)va_arg(args, size_t);
	if (params->length == INT_UINT_MAX)
		num = (uintmax_t)va_arg(args, uintmax_t);
	binary_from_fmt(params, num, 0);
}
