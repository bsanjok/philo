/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gluttony.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:54:22 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/03 18:25:58 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_last_meal(t_program *prgm, t_philo *philos)
{
	pthread_mutex_lock(&philos->meals_eaten_lock);
	pthread_mutex_lock(&prgm->meals_eaten_lock);
	philos->last_meal = ft_gettime();
	pthread_mutex_unlock(&prgm->meals_eaten_lock);
	pthread_mutex_unlock(&philos->meals_eaten_lock);
}

void	increase_eat_count(t_philo *philos)
{
	pthread_mutex_lock(&philos->ate_count_lock);
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->ate_count_lock);
}

static int	eat(t_program *prgm, t_philo *philos)
{
	philo_print_statement(philos, prgm, "is eating");
	set_last_meal(prgm, philos);
	if (prgm->need_eat_count)
		increase_eat_count(philos);
	ft_usleep(prgm->time_to_eat, prgm);
	return (1);
}

int	take_fork_to_eat(t_program *prgm, t_philo *philos)
{
	int	result;

	result = 0;
	if (philos->id % 2)
	{
		if (!take_right_fork(prgm, philos))
			return (0);
		if (!take_left_fork(prgm, philos))
			return (0);
	}
	else
	{
		if (!take_left_fork(prgm, philos))
			return (0);
		if (!take_right_fork(prgm, philos))
			return (0);
	}
	if (eat(prgm, philos))
		result = 1;
	unlock_forks(prgm, philos);
	return (result);
}

int	get_eat_count(t_philo *philos)
{
	int	result;

	pthread_mutex_lock(&(philos->ate_count_lock));
	result = philos->meals_eaten;
	pthread_mutex_unlock(&(philos->ate_count_lock));
	return (result);
}
