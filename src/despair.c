/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   despair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:58:22 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/02 19:34:08 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	last_ate_at(t_philo *philos)
{
	size_t	result;

	pthread_mutex_lock(&philos->meals_eaten_lock);
	result = philos->last_meal;
	pthread_mutex_unlock(&philos->meals_eaten_lock);
	return (result);
}

void	*monitor_death(void *holder)
{
	t_program	*prgm;
	int			i;

	prgm = holder;
	i = 0;
	while (!if_end(prgm))
	{
		i = 0;
		while (i < prgm->number_of_philosophers)
		{
			if (prgm->time_to_die < ft_gettime() - last_ate_at(&prgm->philos[i]))
			{
				pthread_mutex_lock(&prgm->death_lock);
				prgm->dead = 1;
				pthread_mutex_unlock(&prgm->death_lock);
				print_dead(prgm->philos, prgm, "died");
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	print_dead(t_philo *philos, t_program *prgm, char *msg)
{
	// if (if_end(prgm))
	// 	return (0);
	pthread_mutex_lock(&prgm->print_lock);
	printf("%zu %d %s\n", ft_gettime() - prgm->start_time, philos->id, msg);
	pthread_mutex_unlock(&prgm->print_lock);
	return (1);
}
