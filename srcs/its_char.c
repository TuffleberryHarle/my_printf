/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:07:03 by tharle            #+#    #+#             */
/*   Updated: 2020/08/13 16:07:05 by tharle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	char_printer(t_struct *params, char c, int indent)
{
	if (params->width > 1 && !params->minus)
	{
		indent = params->width - 1;
		{
			while (indent--)
				params->n_printed_here += (params->zero)
						? write(1, "0", 1)
						: write(1, " ", 1);
		}
	}
	if (c == '\0')
		params->n_printed_here += write(1, "\0", 1);
	else
		params->n_printed_here += write(1, &c, 1);
	if (params->width && params->minus)
		while (params->n_printed_here < params->width)
			params->n_printed_here += write(1, " ", 1);
	params->n_printed += params->n_printed_here;
}

void	its_char(va_list args, t_struct *params)
{
	unsigned char	c;

	c = (unsigned char)va_arg(args, int);
	char_printer(params, c, 0);
	bzero_struct(params, 0);
}
