/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:28:39 by tharle            #+#    #+#             */
/*   Updated: 2020/08/13 16:28:42 by tharle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	precision_determer(const char *fmt, t_struct *prm)
{
	if (fmt[prm->i] == '.')
	{
		prm->i++;
		prm->dot++;
	}
	if (ft_isdigit(fmt[prm->i]))
	{
		prm->prec = ft_atoi(&fmt[prm->i]);
		if (fmt[prm->i] == '0')
			prm->prec_zero++;
		prm->i += uint_num_len(prm->prec, 10);
	}
}

void	width_determer(const char *fmt, t_struct *prm)
{
	if (ft_isdigit(fmt[prm->i]))
	{
		prm->width = ft_atoi(&fmt[prm->i]);
		prm->i += uint_num_len(prm->width, 10);
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

void	length_hooker(const char *fmt, t_struct *prms)
{
	if (ft_strchr("hlLjz", fmt[prms->i]))
	{
		while (ft_strchr("hlLjz", fmt[prms->i]))
		{
			if (fmt[prms->i] == 'h' && prms->len < SHORT)
				prms->len = SHORT;
			if (fmt[prms->i] == 'h' && fmt[prms->i + 1] == 'h'
				&& prms->len < SHORTSHORT)
				prms->len = SHORTSHORT;
			if (fmt[prms->i] == 'l' && prms->len < LONG)
				prms->len = LONG;
			if (fmt[prms->i] == 'l' && fmt[prms->i + 1] == 'l'
				&& prms->len < LONGLONG)
				prms->len = LONGLONG;
			if (fmt[prms->i] == 'L')
				prms->len = LONGDOUBLE;
			if (fmt[prms->i] == 'z' && prms->len < SIZE_T)
				prms->len = SIZE_T;
			if (fmt[prms->i] == 'j' && prms->len < _UINT_MAX)
				prms->len = _UINT_MAX;
			prms->i++;
		}
	}
}

int		modifier(va_list args, const char *fmt,
					t_struct *params)
{
	if (args == NULL)
		return (0);
	flag_modifier(fmt, params);
	width_determer(fmt, params);
	length_hooker(fmt, params);
	precision_determer(fmt, params);
	return (params->i);
}
