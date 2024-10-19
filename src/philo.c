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

int	init_program(t_program *program)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&program->act_flag);
	while (i < program->n_philo && !program->flag_dead)
	{
		if (phtread_create(&program->philo[i].philo, NULL, \
			&routine, &program->philo[i]))
		{
			program->flag_dead = 1;
			return (ERROR);
		}
		i++;
	}
	program->t_start = get_current_time();
	pthread_mutex_unlock(&program->act_flag);
	return (0);
}

int	prep_philos(t_program *program)
{
	int	i;

	program->philo = malloc(program->n_philo * sizeof(t_philo));
	if (!program->philo)
		return (ERROR);
	if (pthread_mutex_init(&program->act_flag, NULL))
		return (ERROR);
	i = -1;
	while (++i < program->n_philo)
	{
		program->philo[i].id = i;
		program->philo[i].t_eaten = 0;
		program->philo[i].last_meal = 0;
		program->philo[i].program = program;
		if (pthread_mutex_init(&program->philo[i].chopstick1, NULL))
			return (ERROR);
		if (pthread_mutex_init(&program->philo[i].l_m_flag, NULL))
			return (ERROR);
		if (i > 0)
			program->philo[i].chopstick2 = &program->philo[i - 1].chopstick1;
	}
	program->philo[0].chopstick2 = &program->philo[program->n_philo].chopstick1;
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_program	program;

	if (ac < 5 || ac > 6)
		return (print_error(WRONG_ARGS, 1));
	ft_bzero(&program, sizeof(program));
	if (parse(ac, av, &program) == -1)
		return (print_error(INV_ARGS, 2));
	init_program(&program);
	return (0);
}
