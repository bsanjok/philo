/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:51:32 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/01 14:06:15 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*start_program(void *philos)
{
	t_philo		*holder;
	t_program	*prgm;

	holder = (t_philo *)philos;
	prgm = holder->prgm;
	while (prgm->dead != 1 && !prgm->end_now)
	{
		if (prgm->dead || check_number_of_times_eaten(prgm))
			return (0);
		if (!take_fork_to_eat(prgm, philos))
			break ;
		if (check_number_of_times_eaten(prgm))
			break ;
		if (check_death(prgm, holder))
			break ;
		if (!sleeping(prgm, philos))
			break ;
		if (check_death(prgm, holder))
			break ;
		philo_print_statement(philos, prgm, "is thinking");
		if (prgm->dead)
			prgm->end_now++;
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
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	*prgm;

	if (argc > 6)
		return (1);
	prgm = malloc(sizeof(t_program));
	if (!prgm)
		return (1);
	init_prgm(prgm, argv);
	philo_init(prgm);
	thread_join(prgm);
	mutex_destroy(prgm);
	return (0);
}
