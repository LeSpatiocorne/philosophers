/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidruon <nidruon@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:25:29 by nidruon           #+#    #+#             */
/*   Updated: 2025/07/05 00:06:14 by nidruon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct s_philo
{
	int				id;
	pthread_t		thread;
	int				times_eaten;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
};

struct s_data
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	int				all_alive;
	long			start_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
};

void	ft_putstr_fd(int fd, char *str);
long	ft_atol(char *str);
void	*ft_ternary(int condition, void *true, void *false);

long	get_time_in_ms(void);
long	timestamp(long start);
void	ft_usleep(size_t ms);

int		parse_arguments(int ac, char **av, t_data *data);

int		init_data(t_data *data);
void	cleanup_data(t_data *data);

void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);
void	print_status(t_philo *philo, char *message, char *color);

void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);
int		check_alive(t_philo *philo);
int		is_dead(t_philo *philo);
int		get_times_eaten(t_philo *philo);
int		start_simulation(t_data *data);

#endif