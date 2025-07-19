/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 08:56:27 by zkharbac          #+#    #+#             */
/*   Updated: 2025/07/19 10:20:03 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time, t_data *data)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(100);
	}
}

void	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_died || strcmp(msg, "died") == 0)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%lld %d %s\n", get_time() - philo->data->start_time,
			philo->id, msg);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
