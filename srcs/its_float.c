/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coclayto <coclayto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:27:41 by coclayto          #+#    #+#             */
/*   Updated: 2020/06/16 22:46:59 by coclayto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	rounding_up(long double num, t_struct *params, int i)
{
	if ((num > 0.5) \
	|| (num == 0.5 && is_odd(params->f_after[params->len_after])))
	{
		if (i)
		{
			if (params->f_after[--i] != '9')
				params->f_after[i]++;
			else
			{
				while (params->f_after[i] == '9' && i >= 0)
					params->f_after[i--] = '0';
				(i >= 0) ? params->f_after[i]++ : f_increment(params);
			}
		}
		else
			f_increment(params);
	}
}

void	decimal_solver(long double num, t_struct *params)
{
	int		i;
	char	*str;

	i = 0;
	str = params->f_after;
	if (!(params->f_after = (char*)malloc(sizeof(str)
			* params->prec + 1)))
		exit(1);
	while (i < params->prec)
	{
		num *= (long double)10;
		params->f_after[i] = (int)(num) + '0';
		num -= (int)num;
		params->len_after++;
		i++;
	}
	params->f_after[i] = '\0';
	rounding_up(num, params, i);
	params->len_before = ft_strlen(params->f_before);
}

char	*int_solver(long double num, int end)
{
	int			i;
	int			len;
	char		*str;
	char		*ptr;
	long double temp;

	i = 0;
	len = float_num_len(num);
	if (!(str = (char*)malloc(sizeof(str) * len + end)))
		exit(1);
	ptr = str;
	while (len)
	{
		temp = num;
		while (i++ < (len - 1))
			temp /= 10;
		*ptr++ = (int)temp + '0';
		temp = (int)temp;
		while (i-- > 1)
			temp *= 10;
		num -= temp;
		len--;
	}
	*ptr = '\0';
	return (str);
}

void	float_solver(long double num, t_struct *params)
{
	int			len;
	long double	temp;
	long double	f_decimal;
	char		*str;

	temp = num * to_power(10, params->prec);
	str = int_solver(temp, 1);
	temp -= ft_atof(str);
	len = ft_strlen(str);
	if (temp > 0.5 || (temp == 0.5 && is_odd(str[len - 1])))
		num += (0.5 / to_power(10, params->prec));
	free(str);
	params->f_before = int_solver(num, 2);
	f_decimal = num - ft_atof(params->f_before);
	decimal_solver(f_decimal, params);
}

void	its_float(va_list args, t_struct *params)
{
	long double num;

	if (params->length == LONG)
		num = (double)va_arg(args, double);
	if (params->length == LONGDOUBLE)
		num = (long double)va_arg(args, long double);
	if (params->length == 0)
		num = (double)va_arg(args, double);
	if (is_inf_nan(params, num))
	{
		params->hash = 0;
		params->zero = 0;
		return ;
	}
	if (!params->prec && !params->prec_zero)
		params->prec = 6;
	if (num < 0)
	{
		params->negative++;
		num *= -1;
	}
	float_solver(num, params);
	float_printer(params);
	free(params->f_before);
	free(params->f_after);
}
