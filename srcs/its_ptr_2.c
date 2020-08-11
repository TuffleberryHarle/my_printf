/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_ptr2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coclayto <coclayto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:45:48 by releanor          #+#    #+#             */
/*   Updated: 2020/06/16 22:47:47 by coclayto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ptr_checker(t_struct *params)
{
	if (params->zero && params->dot)
		params->zero = 0;
	if (params->width > params->prec)
	{
		params->prec = 0;
		params->prec_was = 1;
	}
	if (params->prec > params->width)
		params->width = 0;
	if (params->width > params->len_before)
	{
		params->indent = params->width - params->prec
				- params->len_before - params->plus - 2;
	}
}
