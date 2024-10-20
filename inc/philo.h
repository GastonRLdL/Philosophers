/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:34:39 by gasroman          #+#    #+#             */
/*   Updated: 2024/10/19 18:43:37 by gasroman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR		-1
# define SUCCESS	0

# define TRUE		1
# define FALSE		0

# define WRONG_ARGS	"Invalid number of arguments"
# define INV_ARGS	"Invalid arguments"

# define ACT_FORK	"[%u] %d has taken a fork%s\n"
# define ACT_EAT	"\x1B[32m[%u] %d is eating%s\n"
# define ACT_SLEEP	"\x1B[36m[%u] %d is sleeping%s\n"
# define ACT_THINK	"\x1B[33m[%u] %d is thinking%s\n"
# define ACT_DIE	"\x1B[31m[%u] %d died%s\n"

enum
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
};

typedef struct s_philo
{
	pthread_mutex_t		last_meal_flag;
	pthread_mutex_t		chopstick1;
	pthread_mutex_t		*chopstick2;
	pthread_t			philo;
	int					id;
	int					n_meals;
	unsigned int		last_meal;
	struct s_simulation	*sim;
}	t_philo;

typedef struct s_simulation
{
	pthread_mutex_t	action_flag;
	pthread_mutex_t	check_flag;
	t_philo			*philo;
	int				flag_dead;
	unsigned int	t_start;
	size_t			n_philo;
	size_t			t_death;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			n_meals;
}	t_simulation;

/***********philo************/
int		print_error(char *str, int type);

/***********parse************/
int		parse(int ac, char **av, t_program *program);

/*******program_utils********/
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);

/*******print_error********/
int		print_error(char *str, int type);

#endif