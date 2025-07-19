/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:11:38 by zkharbac          #+#    #+#             */
/*   Updated: 2025/07/19 09:02:12 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit_str(const char *str)
{
	int	i;

	i = 0;
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
	long	num;
	int		i;

	i = 0;
	num = 0;
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

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (0);
	if (!safe_atoi(argv[1], &data->nb_philos) || data->nb_philos <= 0)
		return (0);
	if (!safe_atoi(argv[2], &data->time_to_die) || data->time_to_die <= 0)
		return (0);
	if (!safe_atoi(argv[3], &data->time_to_eat) || data->time_to_eat <= 0)
		return (0);
	if (!safe_atoi(argv[4], &data->time_to_sleep) || data->time_to_sleep <= 0)
		return (0);
	if (argc == 6)
	{
		if (!safe_atoi(argv[5], &data->must_eat) || data->must_eat <= 0)
			return (0);
		data->has_optional_arg = 1;
	}
	else
		data->has_optional_arg = 0;
	return (1);
}
