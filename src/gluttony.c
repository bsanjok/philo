/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gluttony.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:54:22 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/02 19:53:29 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	take_left_fork(t_program *prgm, t_philo *philos)
{
	pthread_mutex_lock(philos->left_fork);
	if (if_end(prgm))
		return (0);
	philo_print_statement(philos, prgm, "has taken a fork");
	return (1);
}

static int	take_right_fork(t_program *prgm, t_philo *philos)
{
	pthread_mutex_lock(philos->right_fork);
	if (if_end(prgm))
		return (0);
	philo_print_statement(philos, prgm, "has taken a fork");
	return (1);
}

void	set_last_meal(t_philo *philos)
{
	pthread_mutex_lock(&philos->meals_eaten_lock);
	philos->last_meal = ft_gettime();
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
	if (if_end(prgm))
		return (0);
	philo_print_statement(philos, prgm, "is eating");
	set_last_meal(philos);
	if (prgm->need_eat_count)
		increase_eat_count(philos);
	if (if_end(prgm))
		return (0);
	ft_usleep(prgm->time_to_eat);
	return (1);
}

int	take_fork_to_eat(t_program *prgm, t_philo *philos)
{
	int	result;

	result = 0;
	if (philos->id % 2)
	{
		if (!take_right_fork(prgm, philos))
		{
			pthread_mutex_unlock(philos->right_fork);
			return (0);
		}
		if (!take_left_fork(prgm, philos))
		{
			pthread_mutex_unlock(philos->left_fork);
			return (0);
		}
	}
	else
	{
		if (!take_left_fork(prgm, philos))
		{
			pthread_mutex_unlock(philos->left_fork);
			return (0);
		}
		if (!take_right_fork(prgm, philos))
		{
			pthread_mutex_unlock(philos->right_fork);
			return (0);
		}
	}
	if (eat(prgm, philos))
		result = 1;
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

void	*monitor_eat_count(void *holder)
{
	int			i;
	int			j;
	t_program	*prgm;

	i = 0;
	j = 0;
	prgm = holder;
	while (!if_end(prgm))
	{
		i = 0;
		j = 0;
		while (i < prgm->number_of_philosophers)
		{
			if (get_eat_count(&prgm->philos[i]) > prgm->num_times_to_eat)
				j++;
			if (j && j == prgm->number_of_philosophers)
			{
				pthread_mutex_lock(&prgm->death_lock);
				prgm->dead = 1;
				pthread_mutex_unlock(&prgm->death_lock);
				return (NULL);
			}
			i++;
		}
		// usleep(1000);
	}
	return (NULL);
}
