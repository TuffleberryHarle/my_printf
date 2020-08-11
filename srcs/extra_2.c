/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coclayto <coclayto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:53:04 by coclayto          #+#    #+#             */
/*   Updated: 2020/06/16 22:47:37 by coclayto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		bzero_struct(t_struct *params, int full)
{
	if (full)
	{
		params->i = 0;
		params->n_printed = 0;
	}
	params->n_printed_here = 0;
	params->negative = 0;
	params->minus = 0;
	params->plus = 0;
	params->space = 0;
	params->zero = 0;
	params->zero_arg = 0;
	params->hash = 0;
	params->hash_case = 0;
	params->hash_case_zero = 0;
	params->small_hex = 0;
	params->dot = 0;
	params->width = 0;
	params->prec = 0;
	params->prec_was = 0;
	params->indent = 0;
	params->prec_zero = 0;
	params->length = 0;
	params->len_before = 0;
	params->len_after = 0;
}

long double	to_power(long long n, int i)
{
	long long	j;
	long double	res;

	j = 0;
	res = n;
	if (!i)
		return (1);
	while (j++ < (i - 1))
		res *= n;
	return (res);
}

int			float_num_len(long double num)
{
	int	num_len;

	num_len = 0;
	while (num >= 1)
	{
		num /= 10;
		num_len++;
	}
	if (num_len == 0)
		return (1);
	return (num_len);
}

long double	ft_atof(char *str)
{
	long double	num;

	num = 0;
	while (*str)
	{
		num *= 10;
		num += (long double)(*str - '0');
		str++;
	}
	return (num);
}

void		percent_printer(t_struct *params)
{
	char_printer(params, '%', 0);
	bzero_struct(params, 0);
}
