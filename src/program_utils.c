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
void	_sleep(t_philo *philo)
{
	print_action(philo, SLEEP, ACT_SLEEP);
}
void	_think(t_philo *philo)
{
	print_action(philo, THINK, ACT_THINK);
}
void	_eat(t_philo *philo)
{

}
void	*routine(void *data)
{
	t_philo  *philo;

	philo = data;
	pthread_mutex_lock(&philo->program->act_flag);
	pthread_mutex_unlock(&philo->program->act_flag);
	if (chech_death(philo->program) && philo->t_eaten != philo->program->n_eat)
		usleep((philo->program->t_eat -1) * 1000);
	while (check_death(philo->program) && philo->t_eaten != philo->program->n_eat)
	{
		_eat(philo);
		if (philo->t_eaten  != philo->program->n_eat)
		{
			_sleep(philo);
			_think(philo);
		}
	}
	retun (0);
}
