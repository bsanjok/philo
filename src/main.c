/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:51:32 by sbhatta           #+#    #+#             */
/*   Updated: 2023/08/21 13:51:01 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_and_exit(void *n, int exit_code)
{
	if (n)
	{
		free(n);
		n = NULL;
	}
	exit(exit_code);
}

int	philo_print_statement(t_program *philo, size_t philo_index, char *msg)
{
	pthread_mutex_lock(&philo->print_msg);
	printf("%zu ms Philosopher %lu %s.\n", ft_gettime() - philo->start, philo_index, msg);
	pthread_mutex_unlock(&philo->print_msg);
	return (0);
}

void	*start_program(void *philo)
{
	t_program	*holder;

	holder = (t_program *)philo;
	while (!holder->dead)
	{
		pthread_mutex_lock(&holder->fork[holder->index]);
		pthread_mutex_lock(&holder->eat);
		philo_print_statement(philo, holder->index, "is eating");
		ft_usleep(holder->time_to_eat);
		pthread_mutex_unlock(&holder->eat);
		pthread_mutex_unlock(&holder->fork[holder->index]);
	}
	return (NULL);
}

int	init_programs(t_program *philo)
{
	size_t	i;

	i = 0;
	philo->index = 0;
	pthread_mutex_init(&(philo->print_msg), NULL);
	pthread_mutex_init(&(philo->eat), NULL);
	pthread_mutex_lock(&philo->print_msg);
	while (i < philo->number_of_philosophers)
	{
		philo->index++;
		pthread_mutex_init(&(philo->fork[i]), NULL);
		if (pthread_create(&philo->head->threads[i], NULL, &start_program, philo))
			return (0);
		i++;
		usleep(1000);
	}
	philo->start = ft_gettime();
	pthread_mutex_unlock(&philo->print_msg);
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_join(philo->head->threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->print_msg);
	pthread_mutex_destroy(&philo->eat);
	return (1);
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

int		ft_usleep(size_t ms)
{
	size_t	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < ms)
		usleep(500);
	return (0);
}

int	philo_init(t_program *philo, char **argv)
{
	philo->head = malloc(sizeof(t_philo));
	philo->number_of_philosophers = atoi(argv[1]);
	philo->leftfork = 0;
	philo->rightfork = 0;
	philo->dead = 0;
	philo->time_to_die = atoi(argv[2]);
	philo->time_to_eat = atoi(argv[3]);
	philo->time_to_sleep = atoi(argv[4]);
	philo->head->threads = malloc(philo->number_of_philosophers);
	if (!philo->head->threads)
		return (1);
	*philo->num = 0;
	philo->start = ft_gettime();
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	*philo;

	if (argc != 5)
		return (1);
	philo = malloc(sizeof(t_program));
	if (!philo)
		return (1);
	philo->num = malloc(sizeof(int));
	if (!philo->num)
		exit (1);
	philo->fork = malloc(atoi(argv[1]) * sizeof(pthread_mutex_t));
	if (!philo->fork)
		exit (1);
	philo_init(philo, argv);
	init_programs(philo);
	return (0);
}
