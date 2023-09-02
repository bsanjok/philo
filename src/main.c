/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:51:32 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/02 19:53:55 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	if_end(t_program *prgm)
{
	int	result;

	pthread_mutex_lock(&(prgm->death_lock));
	result = prgm->dead;
	pthread_mutex_unlock(&(prgm->death_lock));
	return (result);
}

void	*start_program(void *philos)
{
	t_philo		*holder;
	t_program	*prgm;

	holder = (t_philo *)philos;
	prgm = holder->prgm;
	while (!if_end(prgm))
	{
		if (if_end(prgm))
			break ;
		if (!take_fork_to_eat(prgm, philos))
			break ;
		if (if_end(prgm))
			break ;
		if (!sleeping(prgm, holder))
			break ;
		if (if_end(prgm))
			break ;
		philo_print_statement(holder, prgm, "is thinking");
	}
	return (NULL);
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
	pthread_join(prgm->monitor_death, NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	*prgm;

	if (argc > 6 || argc < 5)
	{
		printf("Invalid input! \n ./philo [arg1][arg2][arg3][arg4][arg5]\n");
		printf("[arg1]: number_of_philosophers\n");
		printf("[arg2]: time_to_die\n");
		printf("[arg3]: time_to_eat\n");
		printf("[arg4]: time_to_sleep\n");
		printf("[arg5]: number_of_times_each_philosopher_must_eat (optional)\n");
		return (1);
	}
	prgm = malloc(sizeof(t_program));
	if (!prgm)
		return (1);
	check_need_of_eat_count(prgm, argc);
	if (!init_prgm(prgm, argv))
		return (ft_free(prgm), 12);
	philo_init(prgm);
	thread_join(prgm);
	free_and_exit(prgm);
	return (0);
}
