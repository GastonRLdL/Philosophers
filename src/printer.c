/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:41:53 by gasroman          #+#    #+#             */
/*   Updated: 2024/10/19 19:29:37 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_error(char *str, int type)
{
	int	tmp;

	tmp = (type == 1) && printf("Philo: %s\n", str);
	tmp = (type == 2) && printf("Philo: %s\n", str);
	return (-1);
}

void	print_action(t_philo *philo, int flag, char *action)
{
	pthread_mutex_lock(&philo->sim->action_flag);
	if (comprove_death(philo->sim))
	{
		if (flag == DIE)
		{
			pthread_mutex_lock(&philo->sim->check_flag);
			philo->sim->flag_death = 1;
			pthread_mutex_unlock(&philo->sim->check_flag);
		}
		printf(action, get_sim_time(philo->sim), philo->id + 1);
	}
	pthread_mutex_unlock(&philo->sim->action_flag);
}
