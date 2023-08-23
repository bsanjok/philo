/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:51:32 by sbhatta           #+#    #+#             */
/*   Updated: 2023/08/23 13:59:09 by sbhatta          ###   ########.fr       */
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

int	philo_print_statement(t_philo *philos, t_program *prgm, size_t philo_index, char *msg)
{
	pthread_mutex_lock(&prgm->print_lock);
	printf("%zu ms Philosopher %lu %s.\n", ft_gettime() - philos->start_time, philo_index, msg);
	pthread_mutex_unlock(&prgm->print_lock);
	return (0);
}

int	eat(t_program *prgm, t_philo *philos, int philo_index)
{
	pthread_mutex_lock(&prgm->meal_lock);
	philo_print_statement(philos, prgm, philo_index, "is eating");
	philos[philo_index].meals_eaten++;
	if (philos[philo_index].meals_eaten == 10)
		prgm->dead = 1;
	pthread_mutex_unlock(&prgm->meal_lock);
	return (1);
}

int	sleeping(t_program *prgm, t_philo *philos, int philo_index)
{
	philo_print_statement(philos, prgm, philo_index, "is sleeping");
	ft_usleep(prgm->time_to_sleep);
	return (1);
}

int	take_fork_to_eat(t_program *prgm, t_philo *philos)
{
	pthread_mutex_lock(&prgm->forks[philos->left_index]);
	philos->start_time = ft_gettime();
	philo_print_statement(philos, prgm, philos->id, "has taken left fork");
	pthread_mutex_lock(&prgm->forks[philos->right_index]);
	philo_print_statement(philos, prgm, philos->id, "has taken right fork");
	pthread_mutex_unlock(&prgm->forks[philos->right_index]);
	pthread_mutex_unlock(&prgm->forks[philos->left_index]);
	eat(prgm, philos, philos->id);
	ft_usleep(prgm->time_to_eat);
	sleeping(prgm, philos, philos->id);
	return (1);
}

void	*start_program(void *philos)
{
	t_philo		*holder;
	t_program	*prgm;
	int			i;

	i = 0;
	holder = (t_philo *)philos;
	prgm = holder->prgm;
	while (prgm->dead != 1)
	{
		take_fork_to_eat(prgm, philos);
	}
	return (NULL);
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

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < ms)
		usleep(500);
	return (0);
}

int	init_prgm(t_program *prgm, char **argv)
{
	int	i;

	i = 0;
	prgm->number_of_philosophers = atoi(argv[1]);
	prgm->time_to_die = atoi(argv[2]);
	prgm->time_to_eat = atoi(argv[3]);
	prgm->time_to_sleep = atoi(argv[4]);
	prgm->forks = malloc(sizeof(pthread_mutex_t) * prgm->number_of_philosophers + 1);
	if (!prgm->forks)
		return (0);
	while (i < prgm->number_of_philosophers)
	{
		pthread_mutex_init(&(prgm->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(prgm->print_lock), NULL);
	pthread_mutex_init(&(prgm->meal_lock), NULL);
	pthread_mutex_init(&(prgm->dead_lock), NULL);
	return (1);
}

int	philo_init(t_program *prgm)
{
	int			i;
	t_philo		*temp;

	i = 0;
	prgm->philos = (t_philo *)malloc(sizeof(t_philo) * prgm->number_of_philosophers);
	if (!prgm->philos)
		return (0);
	while (i < prgm->number_of_philosophers)
	{
		prgm->philos[i].last_meal = 0;
		prgm->philos[i].meals_eaten = 0;
		prgm->philos[i].eating = 0;
		prgm->philos[i].prgm = prgm;
		prgm->philos[i].start_time = 0;
		prgm->philos[i].left_index = i;
		prgm->philos[i].right_index = i + 1;
		prgm->philos[i].id = i + 1;
		i++;
	}
	i = 0;
	while (i < prgm->number_of_philosophers)
	{
		temp = prgm->philos;
		pthread_mutex_init(&(prgm->forks[i]), NULL);
		if (pthread_create(&(temp[i].threads), NULL, &start_program, &prgm->philos[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	mutex_destroy(t_program *prgm)
{
	int		i;

	i = 0;
	while (i < prgm->number_of_philosophers)
	{
		pthread_mutex_destroy(&prgm->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&prgm->print_lock);
	pthread_mutex_destroy(&prgm->meal_lock);
	pthread_mutex_destroy(&prgm->dead_lock);
	return (1);
}

int	thread_join(t_program *prgm)
{
	int			i;
	t_philo		temp;

	i = 0;
	while (i < prgm->number_of_philosophers)
	{
		temp = prgm->philos[i];
		pthread_join(temp.threads, NULL);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	*prgm;

	if (argc != 5)
		return (1);
	prgm = malloc(sizeof(t_program));
	if (!prgm)
		return (1);
	init_prgm(prgm, argv);
	philo_init(prgm);
	thread_join(prgm);
	mutex_destroy(prgm);
	// init_programs(philo);
	return (0);
}
