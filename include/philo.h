/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjokbhatta <sanjokbhatta@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:51:55 by sbhatta           #+#    #+#             */
/*   Updated: 2023/08/30 14:13:06 by sanjokbhatt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t			threads;
	int					id;
	int					eating;
	int					meals_eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		print_lock;
	size_t				last_meal;
	struct s_program	*prgm;

}	t_philo;

typedef struct s_program
{
	int					dead;
	pthread_mutex_t		*forks;
	pthread_mutex_t		start_time_lock;
	pthread_mutex_t		print_lock;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				time_to_eat;
	size_t				start_time;
	int					number_of_philosophers;
	int					num_times_to_eat;
	int					end_now;
	t_philo				*philos;

}	t_program;
#endif

size_t	ft_gettime(void);
int		ft_usleep(size_t ms);
int check_death(t_program *prgm, t_philo *philos);
int	sleeping(t_program *prgm, t_philo *philos);
/*
// take one fork
  - lock mutex
  - check death (if dead, then unlock mutex)
  - print
// take one fork
  - lock mutex
  - check death (if dead, then unlock mutex)
  - print
// eat
  - check death (if dead, then unlock mutex)
  - print
  - while loop  with sleep
// unlock one fork
  - unlock fork
// unlock one fork
  - unlock fork
// sleep
  - check death (if dead, then unlock mutex)
  - print
  - while loop with sleep
// think while of smaller intervals of sleep so that u can check death even when u r sleeping
  - check death (if dead, then unlock mutex)
  - print
  - while loop with sleep (depends on some variable that you decide)
*/