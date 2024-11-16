/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:35:02 by gasroman          #+#    #+#             */
/*   Updated: 2024/11/15 20:15:08 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_simulation(t_simulation *sim)
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
	i = 0;
	while (i < sim->n_philo)
	{
		sim->philo[i].id = i;
		sim->philo[i].t_meals = 0;
		sim->philo[i].last_meal = 0;
		sim->philo[i].sim = sim;
		if (pthread_mutex_init(&sim->philo[i].fork1, NULL))
			return (ERROR);
		if (pthread_mutex_init(&sim->philo[i].last_meal_flag, NULL))
			return (ERROR);
		if (i > 0)
			sim->philo[i].fork2 = &sim->philo[i - 1].fork1;
		i++;
	}
	sim->philo[0].fork2 = &sim->philo[sim->n_philo - 1].fork1;
	return (SUCCESS);
}

void	destroy_mutex(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->n_philo)
	{
		pthread_mutex_destroy(&sim->philo[i].fork1);
		pthread_mutex_destroy(&sim->philo[i].last_meal_flag);
		i++;
	}
	pthread_mutex_destroy(&sim->check_flag);
	pthread_mutex_destroy(&sim->action_flag);
}

void	check_philo_status(t_simulation *sim)
{
	int	i;
	int	flag_meals;

	flag_meals = 0;
	while (check_death(sim) && flag_meals != sim->n_philo)
	{
		i = 0;
		flag_meals = 0;
		while (i < sim->n_philo)
		{
			pthread_mutex_lock(&sim->philo[i].last_meal_flag);
			if (sim->philo[i].t_meals == sim->n_meals)
				flag_meals++;
			if (get_sim_time(sim) - sim->philo[i].last_meal >= sim->t_death \
				&& sim->philo[i].t_meals != sim->n_meals)
				print_action(&sim->philo[i], DIE, ACT_DIE);
			pthread_mutex_unlock(&sim->philo[i].last_meal_flag);
			i++;
		}
	}
	while (i > 0)
		pthread_join(sim->philo[--i].philo, NULL);
	free(sim->philo);
	destroy_mutex(sim);
}

int	main(int ac, char **av)
{
	t_simulation	sim;

	if (ac < 5 || ac > 6)
		return (print_error(WRONG_ARGS, 1));
	ft_bzero(&sim, sizeof(sim));
	if (parse(ac, av, &sim) == -1)
		return (print_error(INV_ARGS, 2));
	if (prep_philos(&sim))
		return (ERROR);
	init_simulation(&sim);
	check_philo_status(&sim);
	return (0);
}
