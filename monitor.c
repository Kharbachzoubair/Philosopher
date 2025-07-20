/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:16:26 by zkharbac          #+#    #+#             */
/*   Updated: 2025/07/20 12:08:16 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, int i, int *full_philos)
{
	long long	time_since_meal;

	pthread_mutex_lock(&data->death_mutex);
	time_since_meal = get_time() - data->philos[i].last_meal;
	if (!data->someone_died && time_since_meal > data->time_to_die)
	{
		data->someone_died = 1;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d died\n", get_time() - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	if (data->has_optional_arg && data->philos[i].meals >= data->must_eat)
		(*full_philos)++;
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		full_philos;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		full_philos = 0;
		while (++i < data->nb_philos)
			if (check_death(data, i, &full_philos))
				return (NULL);
		if (data->has_optional_arg && full_philos == data->nb_philos)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

void	cleanup(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(data->monitor_thread, NULL);
	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->start_mutex);
	free(data->forks);
	free(data->philos);
}
