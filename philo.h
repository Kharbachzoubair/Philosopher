/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:48:23 by zkharbac          #+#    #+#             */
/*   Updated: 2025/07/20 18:20:55 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				has_optional_arg;
	int				someone_died;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	start_mutex;
	struct s_philo	*philos;
	pthread_t		monitor_thread;
}	t_data;

int			parse_args(int argc, char **argv, t_data *data);
int			safe_atoi(const char *str, int *result);
int			is_digit_str(const char *str);
long long	get_time(void);
void		ft_usleep(long long time, t_data *data);
void		*philo_routine(void *arg);
void		print_status(t_philo *philo, char *msg);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		one_philo(t_philo *philo);
int			init_simulation(t_data *data);
void		cleanup(t_data *data);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
void		*monitor_routine(void *arg);

#endif
