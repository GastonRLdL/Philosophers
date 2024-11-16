/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:41:53 by gasroman          #+#    #+#             */
/*   Updated: 2024/11/16 20:02:24 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_error(char *str, int type)
{
	int	tmp;

	tmp = (type == 0) && printf("Philo: %s\n", str);
	tmp = (type == 1) && printf("Philo: %s\n", str);
	tmp = (type == 2) && printf("Philo: %s\n", str);
	return (-1);
}

void	print_action(t_philo *philo, int flag, char *action)
{
	pthread_mutex_lock(&philo->sim->action_flag);
	if (check_death(philo->sim))
	{
		if (flag == DIE)
		{
			pthread_mutex_lock(&philo->sim->check_flag);
			philo->sim->flag_death = 1;
			pthread_mutex_unlock(&philo->sim->check_flag);
		}
		printf("Philosopher %d: ", philo->id + 1);
		printf(action, get_sim_time(philo->sim), philo->id + 1);
	}
	pthread_mutex_unlock(&philo->sim->action_flag);
}

unsigned int	get_sim_time(t_simulation *sim)
{
	return (get_current_time() - sim->t_start);
}

int	check_death(t_simulation *sim)
{
	int	is_n_death;

	is_n_death = 1;
	pthread_mutex_lock(&sim->check_flag);
	if (sim->flag_death == 1)
		is_n_death = 0;
	pthread_mutex_unlock(&sim->check_flag);
	return (is_n_death);
}
