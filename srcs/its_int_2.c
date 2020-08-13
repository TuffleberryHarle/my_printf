/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_int_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:07:57 by tharle            #+#    #+#             */
/*   Updated: 2020/08/13 16:07:58 by tharle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*int_with_prec(t_struct *params, char *s, int i)
{
	char	*s_prec;
	int		j;

	j = 0;
	if (!(s_prec = (char *)malloc(sizeof(char) \
	* (params->prec + 1))))
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

char	*int_overflow_checker(intmax_t num, char *s)
{
	if (num == LLONG_MIN)
	{
		free(s);
		s = "9223372036854775808";
	}
	else if (num == LLONG_MAX)
	{
		free(s);
		s = "9223372036854775807";
	}
	return (s);
}
