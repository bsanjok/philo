/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:11:59 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/02 18:07:34 by sbhatta          ###   ########.fr       */
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
	if (prgm->number_of_philosophers < 1)
	{
		printf("arg[1] number_of_philosophers should be more than 1!\n");
		result = 0;
	}
	if (prgm->time_to_die < 60)
		print_invalid_args("arg[2] time_to_die", &result, 0);
	if (prgm->time_to_eat < 60)
		print_invalid_args("arg[3] time_to_eat", &result, 0);
	if (prgm->time_to_sleep < 60)
		print_invalid_args("arg[4] time_to_sleep", &result, 0);
	if (argv[5] && prgm->num_times_to_eat <= 0)
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
