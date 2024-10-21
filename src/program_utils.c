/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 04:30:09 by gasroman          #+#    #+#             */
/*   Updated: 2024/10/19 19:29:35 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

unsigned int	get_current_time(void)
{
	struct timeval	tmp;
	unsigned int	current_time;

	gettimeofday(&tmp, NULL);
	current_time = (unsigned int)tmp.tv_sec * 1000 + tmp.tv_usec * 0.001;
	return (current_time);
}

void	ft_sleep(t_philo *philo)
{
	print_action(philo, SLEEP, ACT_SLEEP);
}

void	ft_think(t_philo *philo)
{
	print_action(philo, THINK, ACT_THINK);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork1);
	print_action(philo, FORK, ACT_FORK);
	if (&philo->fork1 != philo->fork2)
	{
		pthread_mutex_lock(philo->fork2);
		print_action(philo, FORK, ACT_FORK);
		pthread_mutex_lock(&philo->last_meal_flag);
		philo->last_meal = get_sim_time(philo->sim);
		philo->n_meals++;
		pthread_mutex_unlock(&philo->last_meal_flag);
		print_action(philo, EAT, ACT_EAT);
		usleep(philo->sim->t_eat * 1000);
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(&philo->fork1);
	}
	else
		usleep(philo->sim->t_death * 1000);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	pthread_mutex_lock(&philo->sim->action_flag);
	pthread_mutex_unlock(&philo->sim->action_flag);
	if (chech_death(philo->sim) && philo->n_meals != philo->sim->n_meals)
		usleep((philo->sim->t_eat -1) * 1000);
	while (check_death(philo->sim) && philo->n_meals != philo->sim->n_meals)
	{
		ft_eat(philo);
		if (philo->n_meals != philo->sim->n_meals)
		{
			ft_sleep(philo);
			ft_think(philo);
		}
	}
	retun (0);
}
