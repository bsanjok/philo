/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:13:28 by sbhatta           #+#    #+#             */
/*   Updated: 2023/09/01 19:16:50 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
	c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

static long	ft_atoi_long_sup(const char *str, int i)
{
	int		digit;
	long	result;

	digit = 0;
	result = 0;
	while ((char)str[i] != '\0')
	{
		if ((char)str[i] == '-' || (char)str[i] == '+')
			break ;
		else if (ft_isspace((char)str[i]) == 1)
			break ;
		else
		{
			if ((char)str[i] >= '0' && (char)str[i] <= '9')
				digit = (char)str[i] - '0';
			else
				break ;
			if (digit > 9)
				break ;
			result = 10 * result + digit;
			i++;
		}
	}
	return (result);
}

long	ft_atoi_long(const char *str)
{
	int			sign;
	long		result;
	int			i;

	sign = 0;
	result = 0;
	i = 0;
	while (ft_isspace((char)str[i]) == 1)
		i++;
	if ((char)str[i] == '-')
	{
		sign = 1;
		i++;
	}
	else if ((char)str[i] == '+')
	{
		sign = 0;
		i++;
	}
	result = ft_atoi_long_sup(str, i);
	if (sign == 1)
		return (-result);
	return (result);
}
