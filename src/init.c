/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:52:03 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/17 14:30:04 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	load_philo_args(t_program *prgm, char **argv)
{
	if (!check_valid_args(argv))
		return (0);
	prgm->number_of_philosophers = ft_atoi_long(argv[1]);
	prgm->time_to_die = ft_atoi_long(argv[2]);
	prgm->time_to_eat = ft_atoi_long(argv[3]);
	prgm->time_to_sleep = ft_atoi_long(argv[4]);
	if (argv[5])
		prgm->num_times_to_eat = ft_atoi_long(argv[5]);
	if (!check_valid_time_to(prgm, argv))
		return (0);
	if (prgm->number_of_philosophers == 1)
	{
		ft_usleep(prgm->time_to_die, prgm);
		printf("0 1 has taken a fork\n%zu 1 died\n", prgm->time_to_die);
		return (0);
	}
	return (1);
}

int	init_prgm(t_program *prgm, char **argv)
{
	int	i;

	i = -1;
	if (!load_philo_args(prgm, argv))
		return (0);
	prgm->end = 0;
	prgm->start_time = ft_gettime();
	prgm->monitor_eating = 0;
	prgm->monitor_end = 0;
	prgm->forks = malloc(sizeof(pthread_mutex_t) * \
	prgm->number_of_philosophers);
	if (!prgm->forks)
		return (0);
	while (++i < prgm->number_of_philosophers)
		pthread_mutex_init(&(prgm->forks[i]), NULL);
	pthread_mutex_init(&(prgm->print_lock), NULL);
	pthread_mutex_init(&(prgm->meals_eaten_lock), NULL);
	pthread_mutex_init(&(prgm->death_lock), NULL);
	pthread_mutex_init(&(prgm->fork_taken_lock), NULL);
	return (1);
}

int	philo_alloc(t_program *prgm)
{
	int			i;

	i = -1;
	while (++i < prgm->number_of_philosophers)
	{
		prgm->philos[i].last_meal = ft_gettime();
		prgm->philos[i].fork_taken = 0;
		prgm->philos[i].is_eating = 0;
		prgm->philos[i].meals_eaten = 0;
		prgm->philos[i].prgm = prgm;
		prgm->philos[i].id = i + 1;
		pthread_mutex_init(&(prgm->philos[i].meals_eaten_lock), NULL);
		pthread_mutex_init(&(prgm->philos[i].ate_count_lock), NULL);
		pthread_mutex_init(&(prgm->philos[i].fork_taken_lock), NULL);
	}
	i = 0;
	prgm->philos[0].left_fork = &prgm->forks[0];
	prgm->philos[0].right_fork = &prgm->forks[prgm->number_of_philosophers - 1];
	while (++i < prgm->number_of_philosophers)
	{
		prgm->philos[i].left_fork = &prgm->forks[i];
		prgm->philos[i].right_fork = &prgm->forks[i - 1];
	}
	return (1);
}

int	philo_init(t_program *prgm)
{
	int			i;

	i = -1;
	prgm->philos = (t_philo *)malloc(sizeof(t_philo) * \
	prgm->number_of_philosophers);
	if (!prgm->philos)
		return (0);
	if (!philo_alloc(prgm))
		return (0);
	while (++i < prgm->number_of_philosophers)
	{
		if (pthread_create(&(prgm->philos[i].threads), NULL, \
			&start_program, &prgm->philos[i]))
			return (-1);
	}
	if (pthread_create(&(prgm->monitor_end), NULL, &monitor_end, prgm))
		return (-1);
	if (prgm->need_eat_count)
		if (pthread_create(&(prgm->monitor_eating), NULL, \
		&monitor_eat_count, prgm))
			return (-1);
	return (1);
}
