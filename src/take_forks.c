/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 12:58:09 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/03 14:12:17 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	take_left_fork(t_program *prgm, t_philo *philos)
{
	pthread_mutex_lock(philos->left_fork);
	if (if_end(prgm))
	{
		if (philos->fork_taken)
			pthread_mutex_unlock(philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
		return (0);
	}
	pthread_mutex_lock(&prgm->fork_taken_lock);
	pthread_mutex_lock(&philos->fork_taken_lock);
	philos->fork_taken = 1;
	pthread_mutex_unlock(&philos->fork_taken_lock);
	pthread_mutex_unlock(&prgm->fork_taken_lock);
	philo_print_statement(philos, prgm, "has taken a fork");
	return (1);
}

int	take_right_fork(t_program *prgm, t_philo *philos)
{
	pthread_mutex_lock(philos->right_fork);
	if (if_end(prgm))
	{
		if (philos->fork_taken)
			pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		return (0);
	}
	philo_print_statement(philos, prgm, "has taken a fork");
	pthread_mutex_lock(&prgm->fork_taken_lock);
	pthread_mutex_lock(&philos->fork_taken_lock);
	philos->fork_taken = 1;
	pthread_mutex_unlock(&philos->fork_taken_lock);
	pthread_mutex_unlock(&prgm->fork_taken_lock);
	return (1);
}

void	unlock_forks(t_program *prgm, t_philo *philos)
{
	pthread_mutex_lock(&prgm->fork_taken_lock);
	pthread_mutex_lock(&philos->fork_taken_lock);
	philos->fork_taken = 0;
	pthread_mutex_unlock(&philos->fork_taken_lock);
	pthread_mutex_unlock(&prgm->fork_taken_lock);
	if (philos->id % 2)
	{
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
	}
}
