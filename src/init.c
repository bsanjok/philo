/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:52:03 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/01 14:05:08 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_prgm(t_program *prgm, char **argv)
{
	int	i;

	i = 0;
	prgm->number_of_philosophers = atoi(argv[1]);
	prgm->time_to_die = atoi(argv[2]);
	prgm->time_to_eat = atoi(argv[3]);
	prgm->time_to_sleep = atoi(argv[4]);
	prgm->num_times_to_eat = atoi(argv[5]);
	prgm->start_time = ft_gettime();
	prgm->end_now = 0;
	prgm->forks = malloc(sizeof(pthread_mutex_t) * prgm->number_of_philosophers + 1);
	if (!prgm->forks)
		return (0);
	prgm->fork_usage = malloc(sizeof(int) * prgm->number_of_philosophers + 1);
	if (!prgm->fork_usage)
		return (0);
	while (i < prgm->number_of_philosophers)
	{
		pthread_mutex_init(&(prgm->forks[i]), NULL);
		prgm->fork_usage[i] = 0;
		i++;
	}
	prgm->fork_usage[i] = -1;
	pthread_mutex_init(&(prgm->print_lock), NULL);
	return (1);
}

int	philo_init(t_program *prgm)
{
	int			i;

	i = 0;
	prgm->philos = (t_philo *)malloc(sizeof(t_philo) * prgm->number_of_philosophers);
	if (!prgm->philos)
		return (0);
	while (i < prgm->number_of_philosophers)
	{
		pthread_mutex_init(&(prgm->philos[i].meal_lock), NULL);
		pthread_mutex_init(&(prgm->philos[i].dead_lock), NULL);
		pthread_mutex_init(&(prgm->philos[i].meals_eaten_lock), NULL);
		prgm->philos[i].last_meal = 0;
		prgm->philos[i].meals_eaten = 0;
		prgm->philos[i].eating = 0;
		prgm->philos[i].prgm = prgm;
		prgm->philos[i].id = i + 1;
		i++;
	}
	i = 0;
	prgm->philos[0].left_fork_usage = &prgm->fork_usage[0];
	prgm->philos[0].left_fork = &prgm->forks[0];
	prgm->philos[0].right_fork = &prgm->forks[prgm->number_of_philosophers - 1];
	prgm->philos[0].right_fork_usage = &prgm->fork_usage[prgm->number_of_philosophers - 1];
	while (++i < prgm->number_of_philosophers)
	{
		prgm->philos[i].left_fork = &prgm->forks[i];
		prgm->philos[i].right_fork = &prgm->forks[i - 1];
		prgm->philos[i].left_fork_usage = &prgm->fork_usage[i];
		prgm->philos[i].right_fork_usage = &prgm->fork_usage[i - 1];
	}
	i = 0;
	while (i < prgm->number_of_philosophers)
	{
		pthread_mutex_init(&(prgm->forks[i]), NULL);
		if (pthread_create(&(prgm->philos[i].threads), NULL, &start_program, &prgm->philos[i]))
			return (-1);
		i++;
	}
	return (0);
}

size_t	ft_gettime(void)
{
	struct timeval	tv;
	size_t			result;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	result = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (result);
}
