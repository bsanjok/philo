/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:51:55 by sbhatta           #+#    #+#             */
/*   Updated: 2023/08/20 14:34:50 by sbhatta          ###   ########.fr       */
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
	pthread_mutex_t	*mutex;
	pthread_t		*threads;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				*num;
	long			start;
	int				index;
	int				leftfork;
	int				rightfork;
}	t_philo;
#endif

double	ft_gettime(void);

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