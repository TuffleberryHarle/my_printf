/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: releanor <releanor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:53:04 by coclayto          #+#    #+#             */
/*   Updated: 2020/03/15 15:25:55 by coclayto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		usual_parser(va_list args, t_struct *params, const char *fmt)
{
	params->i++;
	if (ft_strchr(TYPE_SYM, fmt[params->i]))
	{
		params->i = convertor(args, fmt[params->i], params) + 1;
		params->after_perc = 0;
		return (0);
	}
	else if (ft_strchr(FLAGS, fmt[params->i]) || ft_isdigit(fmt[params->i]))
	{
		params->i = modifier(args, fmt, params) - 1;
		if (params->i > (int)ft_strlen(fmt) - 1 && fmt[params->i] != '\0')
		{
			params->i--;
			return (0);
		}
	}
	return (1);
}

int		after_perc_parser(t_struct *params, const char *fmt)
{
	if (fmt[params->i] == '%')
		params->i++;
	if (fmt[params->i] == ' ' && params->i == 1)
	{
		if (fmt[params->i + 1] == '\0')
			return (0);
		params->i++;
	}
	while (ft_strchr(FLAGS, fmt[params->i]))
		params->i++;
	if (fmt[params->i] == '\0')
		exit(0);
	if (fmt[params->i + 1] == '%' && fmt[params->i + 2] != '\0')
	{
		return (0);
		params->i--;
	}
	params->n_printed += write(1, &fmt[params->i], 1);
	params->after_perc = 0;
	params->i++;
	return (1);
}

int		parser(va_list args, const char *fmt, t_struct *params)
{
	params->after_perc = 0;
	while (fmt[params->i] && params->i < (int)ft_strlen(fmt))
	{
		if (fmt[params->i] != '%' && fmt[params->i])
			params->n_printed += write(1, &fmt[params->i], 1);
		else if (fmt[params->i] == '%')
		{
			if (!ft_strchr(ALL_SYM, fmt[params->i + 1]) && params->after_perc)
				break ;
			params->after_perc = 1;
			while (ft_strchr(ALL_SYM, fmt[params->i + 1])
			&& params->i < (int)ft_strlen(fmt))
				if (!usual_parser(args, params, fmt))
					break ;
			while (!ft_strchr("%", fmt[params->i + 1])
			&& params->i < (int)ft_strlen(fmt) && params->after_perc)
				if (!after_perc_parser(params, fmt))
					break ;
			continue;
		}
		params->i++;
	}
	return (params->n_printed);
}

int		ft_printf(const char *fmt, ...)
{
	va_list		args;
	t_struct	*params;
	int			printed;

	if (!(params = (t_struct *)malloc(sizeof(t_struct))))
		return (0);
	bzero_struct(params, 1);
	params->format = (char *)fmt;
	va_start(args, fmt);
	if (!fmt[0])
		return (0);
	if (fmt[0] == '%' && !fmt[1])
		return (0);
	printed = parser(args, fmt, params);
	va_end(args);
	free(params);
	return (printed);
}
