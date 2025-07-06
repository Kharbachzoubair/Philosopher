/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:11:53 by zkharbac          #+#    #+#             */
/*   Updated: 2025/07/06 13:11:55 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit_str(const char *str)
{
	int	i = 0;

	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	safe_atoi(const char *str, int *result)
{
	long	num = 0;
	int		i = 0;

	if (!is_digit_str(str))
		return (0);
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	*result = (int)num;
	return (1);
}
