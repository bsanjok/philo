/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gluttony.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:54:22 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/01 15:06:46 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	take_left_fork(t_program *prgm, t_philo *philos)
{
	if (prgm->dead || check_number_of_times_eaten(prgm))
		return (0);
	while (*(philos->left_fork_usage))
	{
		if ((philos->last_meal && check_death(prgm, philos)))
			return (0);
	}
	pthread_mutex_lock(philos->left_fork);
	*(philos->left_fork_usage) = 1;
	philo_print_statement(philos, prgm, "has taken a left fork");
	return (1);
}

static int	take_right_fork(t_program *prgm, t_philo *philos)
{
	if (prgm->dead || check_number_of_times_eaten(prgm))
		return (0);
	while (*(philos->right_fork_usage))
	{
		if ((philos->last_meal && check_death(prgm, philos)))
			return (0);
	}
	pthread_mutex_lock(philos->right_fork);
	*(philos->right_fork_usage) = 1;
	philo_print_statement(philos, prgm, "has taken a right fork");
	return (1);
}

static int	eat(t_program *prgm, t_philo *philos)
{
	size_t	eating_time;

	if (prgm->end_now > 1)
		return (0);
	philo_print_statement(philos, prgm, "is eating");
	pthread_mutex_lock(&philos->meals_eaten_lock);
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->meals_eaten_lock);
	pthread_mutex_lock(&philos->meal_lock);
	eating_time = 0;
	while (1)
	{
		ft_usleep(1);
		eating_time++;
		if (prgm->dead)
		{
			pthread_mutex_unlock(&philos->meal_lock);
			return (0);
		}
		if (eating_time == prgm->time_to_eat)
			break ;
	}
	philos->last_meal = ft_gettime();
	pthread_mutex_unlock(&philos->meal_lock);
	return (1);
}

int	take_fork_to_eat(t_program *prgm, t_philo *philos)
{
	int	result;

	result = 0;
	if (prgm->dead)
		return (0);
	if (philos->id % 2)
	{
		if (!take_right_fork(prgm, philos))
		{
			pthread_mutex_unlock(philos->right_fork);
			*(philos->right_fork_usage) = 0;
			return (0);
		}
		if (!take_left_fork(prgm, philos))
		{
			pthread_mutex_unlock(philos->left_fork);
			*(philos->left_fork_usage) = 0;
			return (0);
		}
	}
	else
	{
		if (!take_left_fork(prgm, philos))
		{
			pthread_mutex_unlock(philos->left_fork);
			*(philos->left_fork_usage) = 0;
			return (0);
		}
		if (!take_right_fork(prgm, philos))
		{
			pthread_mutex_unlock(philos->right_fork);
			*(philos->right_fork_usage) = 0;
			return (0);
		}
	}
	if (eat(prgm, philos))
		result = 1;
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
	*(philos->right_fork_usage) = 0;
	*(philos->left_fork_usage) = 0;
	return (result);
}

int	check_number_of_times_eaten(t_program *prgm)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (prgm->end_now)
		return (1);
	while (i < prgm->number_of_philosophers)
	{
		if (prgm->philos[i].meals_eaten >= prgm->num_times_to_eat)
			j++;
		i++;
	}
	if (j >= prgm->number_of_philosophers)
	{
		prgm->end_now++;
		return (1);
	}
	return (0);
}
