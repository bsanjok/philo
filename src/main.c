/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:51:32 by sbhatta           #+#    #+#             */
/*   Updated: 2023/08/27 14:19:01 by sbhatta          ###   ########.fr       */
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

int	philo_print_statement(t_philo *philos, t_program *prgm, char *msg)
{
	pthread_mutex_lock(&prgm->print_lock);
	printf("%zu ms Philosopher %d %s.\n", ft_gettime() - prgm->start_time, philos->id, msg);
	pthread_mutex_unlock(&prgm->print_lock);
	return (0);
}

int	eat(t_program *prgm, t_philo *philos, int philo_index)
{
	pthread_mutex_lock(&philos->meal_lock);
	philos[philo_index].meals_eaten++;
	if (philos[philo_index].meals_eaten == 10)
		prgm->dead = 1;
	pthread_mutex_unlock(&philos->meal_lock);
	return (1);
}

int	sleeping(t_program *prgm, t_philo *philos)
{
	philo_print_statement(philos, prgm, "is sleeping");
	ft_usleep(prgm->time_to_sleep);
	return (1);
}

int	take_left_fork(t_program *prgm, t_philo *philos)
{
	pthread_mutex_lock(&philos->left_fork);
	philo_print_statement(philos, prgm, "has taken left fork");
	return (1);
}

int	take_right_fork(t_program *prgm, t_philo *philos)
{
	pthread_mutex_lock(&philos->right_fork);
	philo_print_statement(philos, prgm, "has taken right fork");
	return (1);
}

int	take_fork_to_eat(t_program *prgm, t_philo *philos)
{
	if (philos->id % 2)
	{
		take_right_fork(prgm, philos);
		take_left_fork(prgm, philos);
	}
	else
	{
		take_left_fork(prgm, philos);
		take_right_fork(prgm, philos);
	}
	philo_print_statement(philos, prgm, "is eating");
	eat(prgm, philos, philos->id);
	ft_usleep(prgm->time_to_eat);
	pthread_mutex_unlock(&philos->left_fork);
	pthread_mutex_unlock(&philos->right_fork);
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
		sleeping(prgm, philos);
		philo_print_statement(philos, prgm, "is thinking");
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
	prgm->start_time = ft_gettime();
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
	pthread_mutex_init(&(prgm->start_time_lock), NULL);
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
		prgm->philos[i].meal_lock = prgm->meal_lock;
		prgm->philos[i].last_meal = 0;
		prgm->philos[i].meals_eaten = 0;
		prgm->philos[i].eating = 0;
		prgm->philos[i].prgm = prgm;
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
	i = 0;
	prgm->philos[0].left_fork = prgm->forks[i];
	prgm->philos[0].right_fork = prgm->forks[prgm->number_of_philosophers - 1];
	while (++i < prgm->number_of_philosophers)
	{
		prgm->philos[i].left_fork = prgm->forks[i];
		prgm->philos[i].right_fork = prgm->forks[i - 1];
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
	pthread_mutex_destroy(&prgm->start_time_lock);
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
