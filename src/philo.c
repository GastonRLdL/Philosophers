/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:35:02 by gasroman          #+#    #+#             */
/*   Updated: 2024/10/19 19:29:38 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_simultion(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->action_flag);
	while (i < sim->n_philo && !sim->flag_death)
	{
		if (pthread_create \
		(&sim->philo[i].philo, NULL, &routine, &sim->philo[i]))
		{
			sim->flag_death = 1;
			return (ERROR);
		}
		i++;
	}
	sim->t_start = get_current_time();
	pthread_mutex_unlock(&sim->action_flag);
	return (0);
}

int	prep_philos(t_simulation *sim)
{
	int	i;

	sim->philo = malloc(sim->n_philo * sizeof(t_philo));
	if (!sim->philo)
		return (ERROR);
	if (pthread_mutex_init(&sim->action_flag, NULL))
		return (ERROR);
	i = -1;
	while (++i < sim->n_philo)
	{
		sim->philo[i].id = i;
		sim->philo[i].n_meals = 0;
		sim->philo[i].last_meal = 0;
		sim->philo[i].sim = sim;
		if (pthread_mutex_init(&sim->philo[i].fork1, NULL))
			return (ERROR);
		if (pthread_mutex_init(&sim->philo[i].last_meal_flag, NULL))
			return (ERROR);
		if (i > 0)
			sim->philo[i].fork2 = &sim->philo[i - 1].fork1;
	}
	sim->philo[0].fork2 = &sim->philo[sim->n_philo].fork1;
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_simulation	sim;

	if (ac < 5 || ac > 6)
		return (print_error(WRONG_ARGS, 1));
	ft_bzero(&sim, sizeof(sim));
	if (parse(ac, av, &sim) == -1)
		return (print_error(INV_ARGS, 2));
	init_simulation(&sim);
	return (0);
}
