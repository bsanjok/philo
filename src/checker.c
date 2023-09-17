/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:11:59 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/03 18:45:27 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	print_invalid_args(const char *msg, int *result, int flag)
{
	if (flag == 1)
		printf("%s should be a number!\n", msg);
	else
		printf("%s should be above 60ms!\n", msg);
	*result = 0;
}

int	check_valid_time_to(t_program *prgm, char **argv)
{
	int	result;

	result = 1;
	if (prgm->number_of_philosophers < 1 || ft_atoi_long(argv[1]) < 0)
	{
		printf("arg[1] number_of_philosophers should be more than 1!\n");
		result = 0;
	}
	if (prgm->time_to_die < 60 || ft_atoi_long(argv[2]) < 0)
		print_invalid_args("arg[2] time_to_die", &result, 0);
	if (prgm->time_to_eat < 60 || ft_atoi_long(argv[3]) < 0)
		print_invalid_args("arg[3] time_to_eat", &result, 0);
	if (prgm->time_to_sleep < 60 || ft_atoi_long(argv[4]) < 0)
		print_invalid_args("arg[4] time_to_sleep", &result, 0);
	if (argv[5] && (prgm->num_times_to_eat <= 0 || ft_atoi_long(argv[5]) < 0))
	{
		printf("arg[5]: num_times_to_eat is set to 0 or less\n");
		result = 0;
	}
	return (result);
}

int	check_valid_args(char **argv)
{
	int	result;

	result = 1;
	if (!ft_isnumber(argv[1]))
		print_invalid_args("arg[1] number_of_philosophers", &result, 1);
	if (!ft_isnumber(argv[2]))
		print_invalid_args("arg[2] time_to_die", &result, 1);
	if (!ft_isnumber(argv[3]))
		print_invalid_args("arg[3] time_to_eat", &result, 1);
	if (!ft_isnumber(argv[4]))
		print_invalid_args("arg[4] time_to_sleep", &result, 1);
	if (argv[5] && !ft_isnumber(argv[5]))
		print_invalid_args("arg[5] num_times_to_eat", &result, 1);
	return (result);
}

void	*monitor_eat_count(void *holder)
{
	int			i;
	int			j;
	t_program	*prgm;

	i = 0;
	j = 0;
	prgm = holder;
	while (!if_end(prgm))
	{
		i = -1;
		j = 0;
		while (++i < prgm->number_of_philosophers)
		{
			if (get_eat_count(&prgm->philos[i]) >= prgm->num_times_to_eat)
				j++;
			if (j && j >= prgm->number_of_philosophers)
			{
				pthread_mutex_lock(&prgm->death_lock);
				prgm->end = 1;
				pthread_mutex_unlock(&prgm->death_lock);
				return (NULL);
			}
		}
	}
	return (NULL);
}
