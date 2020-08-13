/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_ptr_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:08:34 by tharle            #+#    #+#             */
/*   Updated: 2020/08/13 16:08:36 by tharle           ###   ########.fr       */
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
