/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_nonprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: releanor <releanor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:34:13 by releanor          #+#    #+#             */
/*   Updated: 2020/03/06 12:33:06 by releanor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		len_determer(char *s, int i)
{
	int res;

	res = 0;
	while (s[i])
	{
		if ((s[i] >= 1 && s[i] <= 32) || s[i] == 127)
			res += 2;
		else
			res++;
		i++;
	}
	return (res);
}

void	str_recreator(char *s, char *s_unpr, int i, int j)
{
	while (s[i])
	{
		if ((s[i] >= 1 && s[i] <= 32) || s[i] == 127)
		{
			s_unpr[j++] = '^';
			if (s[i] == 0)
				s_unpr[j] = '@';
			else if (s[i] == 127)
				s_unpr[j] = '?';
			else
				s_unpr[j] = 64 + s[i];
		}
		else
			s_unpr[j] = s[i];
		i++;
		j++;
	}
	s_unpr[j] = '\0';
}

void	unprintable_creator(va_list args, t_struct *params)
{
	char	*s;
	char	*s_unpr;
	int		len_2;

	if (!(s = (char *)va_arg(args, char *)))
		s = "(null)";
	params->len_before = ft_strlen(s);
	len_2 = len_determer(s, 0);
	if (!(s_unpr = (char *)malloc(sizeof(*s_unpr)
			* ((len_2) + 1)))) s_unpr = "(null)";
	str_recreator(s, s_unpr, 0, 0);
	params->len_before = len_2;
	str_printer(params, s_unpr);
	free(s_unpr);
	bzero_struct(params, 0);
}
