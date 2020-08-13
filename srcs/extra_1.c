/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:06:24 by tharle            #+#    #+#             */
/*   Updated: 2020/08/13 16:06:27 by tharle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		num_len(intmax_t num, int base)
{
	int		num_len;

	if (!num)
		return (1);
	num_len = 0;
	num = (num < 0) ? -num : num;
	while (num >= 1)
	{
		num /= base;
		num_len++;
	}
	return (num_len);
}

int		uint_num_len(uintmax_t num, int base)
{
	uintmax_t		num_len;

	num_len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= base;
		num_len++;
	}
	return (num_len);
}

char	*itoa_base(t_struct *params, intmax_t num, int base)
{
	char	*res;
	int		i;

	i = num_len(num, base);
	params->negative = (num < 0 && base == 10) ? 1 : 0;
	num = (num < 0 && base == 10) ? -num : num;
	if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	res[i--] = '\0';
	while (i >= 0)
	{
		res[i] = (num % base < 10) ? (num % base) + '0' : \
		(num % base + 'a' - 10);
		num /= base;
		i--;
	}
	return (res);
}

char	*itoa_base_uint(uintmax_t num, int base)
{
	char	*res;
	int		i;

	i = uint_num_len(num, base);
	if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	res[i--] = '\0';
	while (i >= 0)
	{
		res[i] = (num % base < 10) ? (num % base) + '0'
				: (num % base + 'a' - 10);
		num /= base;
		i--;
	}
	return (res);
}

char	*itoa_base_uppercase(uintmax_t num, int base)
{
	char	*res;
	int		i;

	i = uint_num_len(num, base);
	if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	res[i--] = '\0';
	while (i >= 0)
	{
		res[i] = (num % base < 10) ? (num % base) + '0' : \
		(num % base + 'A' - 10);
		num /= base;
		i--;
	}
	return (res);
}
