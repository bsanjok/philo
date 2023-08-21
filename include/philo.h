/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:51:55 by sbhatta           #+#    #+#             */
/*   Updated: 2023/08/21 17:53:47 by sbhatta          ###   ########.fr       */
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
	int					left_index;
	int					right_index;
	size_t				last_meal;
	size_t				start_time;
	int					*dead;
	struct s_program	*prgm;

}	t_philo;

typedef struct s_program
{
	int					dead;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		dead_lock;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				time_to_eat;
	int					number_of_philosophers;
	int					num_times_to_eat;

	t_philo				*philos;

}	t_program;
#endif

size_t	ft_gettime(void);
int		ft_usleep(size_t ms);

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