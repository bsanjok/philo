/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:51:32 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/29 11:48:30 by sbhatta          ###   ########.fr       */
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

void	*print_hello(void *arg)
{
	int	i;

	i = 0;
	arg = NULL;
	while (i < 100)
	{
		printf("Hello\n");
		i++;
		usleep(10000);
	}
	return (NULL);
}

void	*print_world(void *arg)
{
	int	i;

	i = 0;
	arg = NULL;
	while (i < 100)
	{
		printf("\t\tWorld\n");
		i++;
		usleep(10000);
	}
	return (NULL);
}

void	thread_test(void)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, print_hello, NULL))
		exit (1);
	if (pthread_create(&t2, NULL, print_world, NULL))
		exit (1);
	if (pthread_join(t1, NULL))
		exit(1);
	if (pthread_join(t2, NULL))
		exit (1);
}


void	*take_fork(void *philo)
{
	t_philo	*holder;

	holder = (t_philo *)philo;
	pthread_mutex_lock(&holder->mutex[holder->index]);
	printf("I take a fork from %d\n", holder->index);
	pthread_mutex_unlock(&holder->mutex[holder->index]);
	return (NULL);
}

void	init_philos(t_philo *philo)
{
	int	i;

	i = 0;
	philo->index = 0;
	while (i < philo->number_of_philosophers)
	{
		philo->index++;
		pthread_mutex_init(&(philo->mutex[i]), NULL);
		if (pthread_create(&philo->threads[i], NULL, &take_fork, philo))
			exit (1);
		i++;
		usleep(10000);
	}
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_join(philo->threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo->mutex[i]);
		i++;
	}
	printf("n: %d\n", *philo->num);
}

long	ft_gettime(void)
{
	struct timeval	tv;
	long			result;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	result = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (result);
}

int	philo_init(t_philo *philo, char **argv)
{
	philo->number_of_philosophers = atoi(argv[1]);
	philo->time_to_die = atoi(argv[2]);
	philo->time_to_eat = atoi(argv[3]);
	philo->time_to_sleep = atoi(argv[4]);
	philo->threads = malloc(philo->number_of_philosophers);
	if (!philo->threads)
		return (1);
	*philo->num = 0;
	philo->start = ft_gettime();
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo *philo;

	if (argc != 5)
		return (1);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	philo->num = malloc(sizeof(int));
	if (!philo->num)
		exit (1);
	philo->mutex = malloc(atoi(argv[1]) * sizeof(pthread_mutex_t));
	if (!philo->mutex)
		exit (1);
	philo_init(philo, argv);
	printf("time: %ld\n", philo->start);
	usleep(1000);
	printf("elapsed: %ld \n", ft_gettime() - philo->start);
	init_philos(philo);
	return (0);
}
