/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <tharle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:46:52 by tharle            #+#    #+#             */
/*   Updated: 2020/03/13 02:22:13 by tharle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	precision_determer(const char *fmt, t_struct *params)
{
	if (fmt[params->i] == '.')
	{
		params->i++;
		params->dot++;
	}
	if (ft_isdigit(fmt[params->i]))
	{
		params->prec = ft_atoi(&fmt[params->i]);
		if (fmt[params->i] == '0')
			params->prec_zero++;
		params->i += uint_num_len(params->prec, 10);
	}
}

void	width_determer(const char *fmt, t_struct *params)
{
	if (ft_isdigit(fmt[params->i]))
	{
		params->width = ft_atoi(&fmt[params->i]);
		params->i += uint_num_len(params->width, 10);
	}
}

void	flag_modifier(const char *fmt, t_struct *params)
{
	while (ft_strchr("-+ #0", fmt[params->i]))
	{
		if (fmt[params->i] == '-')
			params->minus = 1;
		if (fmt[params->i] == '+')
			params->plus = 1;
		if (fmt[params->i] == ' ')
			params->space = 1;
		if (fmt[params->i] == '#')
			params->hash = 1;
		if (fmt[params->i] == '0')
			params->zero = 1;
		params->i++;
	}
	if (params->plus == 1)
		params->space = 0;
	if (params->minus == 1)
		params->zero = 0;
}

void	length_hooker(const char *fmt, t_struct *params)
{
	if (ft_strchr("hlLjz", fmt[params->i]))
	{
		while (ft_strchr("hlLjz", fmt[params->i]))
		{
			if (fmt[params->i] == 'h' && params->length < SHORT)
				params->length = SHORT;
			if (fmt[params->i] == 'h' && fmt[params->i + 1] == 'h'
			&& params->length < SHORTSHORT)
				params->length = SHORTSHORT;
			if (fmt[params->i] == 'l' && params->length < LONG)
				params->length = LONG;
			if (fmt[params->i] == 'l' && fmt[params->i + 1] == 'l'
			&& params->length < LONGLONG)
				params->length = LONGLONG;
			if (fmt[params->i] == 'L')
				params->length = LONGDOUBLE;
			if (fmt[params->i] == 'z' && params->length < SIZE_T)
				params->length = SIZE_T;
			if (fmt[params->i] == 'j' && params->length < INT_UINT_MAX)
				params->length = INT_UINT_MAX;
			params->i++;
		}
	}
}

int		modifier(va_list args, const char *fmt, t_struct *params)
{
	if (args == NULL)
		return (0);
	flag_modifier(fmt, params);
	width_determer(fmt, params);
	length_hooker(fmt, params);
	precision_determer(fmt, params);
	return (params->i);
}
