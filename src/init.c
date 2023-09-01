/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:52:03 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/01 19:14:38 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_valid_time_to(t_program *prgm)
{
	int	result;

	result = 1;
	if (prgm->time_to_die < 60)
	{
		printf("time_to_die should be above 60ms\n");
		result = 0;
	}
	if (prgm->time_to_eat < 60)
	{
		printf("time_to_eat should be above 60ms\n");
		result = 0;
	}
	if (prgm->time_to_sleep < 60)
	{
		printf("time_to_sleep should be above 60ms\n");
		result = 0;
	}
	return (result);
}

int	init_prgm(t_program *prgm, char **argv, int argc)
{
	int	i;

	i = 0;
	prgm->number_of_philosophers = ft_atoi_long(argv[1]);
	prgm->time_to_die = ft_atoi_long(argv[2]);
	prgm->time_to_eat = ft_atoi_long(argv[3]);
	prgm->time_to_sleep = ft_atoi_long(argv[4]);
	if (!check_valid_time_to(prgm))
		return (0);
	if (prgm->number_of_philosophers == 1)
	{
		ft_usleep(prgm->time_to_die);
		printf("%zu 1 died\n", prgm->time_to_die);
		return (0);
	}
	prgm->dead = 0;
	prgm->all_eaten = 0;
	if (argc == 6)
	{
		prgm->num_times_to_eat = atoi(argv[5]);
		if (prgm->num_times_to_eat <= 0)
		{
			printf("Number of times to eat is set to 0 or less\n");
			return (0);
		}
	}
	prgm->start_time = ft_gettime();
	prgm->end_now = 0;
	prgm->forks = malloc(sizeof(pthread_mutex_t) * prgm->number_of_philosophers);
	if (!prgm->forks)
		return (0);
	prgm->fork_usage = malloc(sizeof(int) * prgm->number_of_philosophers);
	if (!prgm->fork_usage)
		return (0);
	while (i < prgm->number_of_philosophers)
	{
		pthread_mutex_init(&(prgm->forks[i]), NULL);
		prgm->fork_usage[i] = 0;
		i++;
	}
	pthread_mutex_init(&(prgm->print_lock), NULL);
	pthread_mutex_init(&(prgm->end_lock), NULL);
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
		i++;
	}
	i = 0;
	while (i < prgm->number_of_philosophers)
	{
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

void	check_need_of_eat_count(t_program *prgm ,int argc)
{
	if (argc == 6)
		prgm->need_eat_count = 1;
	else
		prgm->need_eat_count = 0;
}
