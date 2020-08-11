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

int		uint_printer_2(t_struct *params, char *s)
{
	if (!params->width && params->dot && s[0] == '0'
	&& params->len_before == 1)
		return (0);
	else if (params->dot && s[0] == '0' && params->len_before == 1)
		params->n_printed_here += write(1, " ", params->len_before);
	else
		params->n_printed_here += write(1, s, params->len_before);
	if (params->width && params->minus)
		while (params->n_printed_here < params->width)
			params->n_printed_here += write(1, " ", 1);
	return (1);
}

void	uint_printer(t_struct *params, char *s, int indent)
{
	if (params->width > params->len_before)
		indent = params->width - params->len_before;
	if (params->negative || params->plus || params->space)
		indent--;
	if (params->width > params->len_before && !params->minus)
	{
		while (indent--)
		{
			params->n_printed_here += (params->zero && \
			!params->prec) ? write(1, "0", 1) : \
			write(1, " ", 1);
		}
	}
	if (params->negative)
		params->n_printed_here += write(1, "-", 1);
	if (params->space && !params->negative)
		params->n_printed_here += write(1, " ", 1);
	uint_printer_2(params, s);
}

char	*uint_with_prec(t_struct *params, char *s, int i)
{
	char	*s_prec;
	int		j;

	j = 0;
	if (!(s_prec = (char *)malloc(sizeof(char) *
			(params->prec + 1))))
		s_prec = NULL;
	while (i < (params->prec - params->len_before))
	{
		s_prec[i] = '0';
		i++;
	}
	while (s[j])
	{
		s_prec[i] = s[j];
		i++;
		j++;
	}
	s_prec[i] = '\0';
	free(s);
	return (s_prec);
}

void	uint_from_fmt(t_struct *params, uintmax_t num, int i)
{
	char	*s;

	params->len_before = uint_num_len(num, 10);
	s = itoa_base_uint(num, 10);
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

void	its_uint(va_list args, t_struct *params, char spec)
{
	uintmax_t num;

	num = 0;
	if (params->length == 0 && spec == 'u')
		num = (unsigned int)va_arg(args, int);
	else if (params->length == SHORTSHORT && spec == 'u')
		num = (unsigned char)va_arg(args, int);
	else if (params->length == SHORT && spec == 'u')
		num = (unsigned short)va_arg(args, int);
	else if (params->length == LONG || spec == 'U')
		num = (unsigned long)va_arg(args, unsigned long);
	else if (params->length == LONGLONG)
		num = (unsigned long long)va_arg(args,
				unsigned long long);
	if (params->length == SIZE_T)
		num = (size_t)va_arg(args, size_t);
	if (params->length == INT_UINT_MAX)
		num = (uintmax_t)va_arg(args, uintmax_t);
	uint_from_fmt(params, num, 0);
}
