/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   despair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:58:22 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/01 14:06:34 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_death(t_program *prgm, t_philo *philos)
{
	pthread_mutex_lock(&philos->dead_lock);
	if (prgm->time_to_die < ft_gettime() - philos->last_meal)
	{
		prgm->dead = 1;
		print_dead(philos, prgm, "died");
		pthread_mutex_unlock(&philos->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philos->dead_lock);
	return (0);
}

int	print_dead(t_philo *philos, t_program *prgm, char *msg)
{
	if (prgm->end_now > 1)
		return (0);
	pthread_mutex_lock(&prgm->print_lock);
	printf("%zums %d %s\n", ft_gettime() - prgm->start_time, philos->id, msg);
	pthread_mutex_unlock(&prgm->print_lock);
	return (1);
}
