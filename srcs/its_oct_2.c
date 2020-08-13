/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_oct_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:08:14 by tharle            #+#    #+#             */
/*   Updated: 2020/08/13 16:08:16 by tharle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*oct_with_prec(t_struct *prms, char *s, int i)
{
	char	*s_prec;
	int		j;

	j = 0;
	if (!(s_prec = (char *)malloc(sizeof(char)
			* (prms->prec + 1))))
		s_prec = NULL;
	while (i < (prms->prec - prms->len_before))
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

char	*oct_hash(t_struct *params, char *s)
{
	char	*s_hash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(s_hash = (char *)malloc(sizeof(char)
			* (params->len_before + 2))))
		s_hash = NULL;
	s_hash[i++] = '0';
	while (s[j])
	{
		s_hash[i] = s[j];
		i++;
		j++;
	}
	s_hash[i] = '\0';
	free(s);
	return (s_hash);
}
