/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:11:38 by zkharbac          #+#    #+#             */
/*   Updated: 2025/07/06 13:11:40 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
