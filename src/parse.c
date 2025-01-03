/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:16:20 by gasroman          #+#    #+#             */
/*   Updated: 2024/11/16 20:04:09 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	sign_check(int ac, char **av)
{
	int	i;
	int	j;

	i = ac - 1;
	j = 0;
	while (av[i] && i > 0)
	{
		if (ft_strlen(av[i]) == 1 && av[i][0] == '-')
			return (ERROR);
		if (ft_strlen(av[i]) == 1 && av[i][0] == '+')
			return (ERROR);
		if (av[i][0] == '-' || av[i][0] == '+')
			j++;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (ERROR);
			j++;
		}
		j = 0;
		i--;
	}
	return (SUCCESS);
}

static int	int_check(int ac, char **av)
{
	int	i;
	int	size;

	i = 1;
	while (i < ac)
	{
		size = ft_strlen(av[i]);
		if (size == 0 || ((size > 10 && av[i][0] != '-')
			&& (size > 10 && av[i][0] != '+')) || size > 11)
			return (ERROR);
		if (av[i][0] != '-' && av[i][0] != '+' && size == 10
			&& ft_strncmp(av[i], "2147483647", 10) > 0)
			return (ERROR);
		if (av[i][0] == '-' && size == 11 &&
			ft_strncmp(av[i], "-2147483648", 11) > 0)
			return (ERROR);
		if (av[i][0] == '+' && size == 11 &&
			ft_strncmp(av[i], "+2147483647", 11) > 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	parse(int ac, char **av, t_simulation *sim)
{
	int	*data;
	int	i;

	if (int_check(ac, av) == ERROR || sign_check(ac, av) == ERROR)
		return (ERROR);
	data = malloc(ac * sizeof(int));
	if (!data)
		return (ERROR);
	i = 0;
	while (++i < ac)
		data[i - 1] = ft_atoi(av[i]);
	if (data[0] == 0)
		return (ERROR);
	sim->n_philo = data[0];
	sim->t_death = data[1];
	sim->t_eat = data[2];
	sim->t_sleep = data[3];
	sim->n_meals = -1;
	sim->flag_death = 0;
	if (ac == 6)
		sim->n_meals = data[4];
	free(data);
	return (SUCCESS);
}
