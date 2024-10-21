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
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR		-1
# define SUCCESS	0

# define TRUE		1
# define FALSE		0

# define WRONG_ARGS	"Invalid number of arguments"
# define INV_ARGS	"Invalid arguments"

# define ACT_FORK	"%d has taken a fork\n"
# define ACT_EAT	"%d is eating\n"
# define ACT_SLEEP	"%d is sleeping\n"
# define ACT_THINK	"%d is thinking\n"
# define ACT_DIE	"%d died\n"

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
	pthread_mutex_t		fork1;
	pthread_mutex_t		*fork2;
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
	int				flag_death;
	unsigned int	t_start;
	int				n_philo;
	size_t			t_death;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			n_meals;
}	t_simulation;

/***********philo************/
int				print_error(char *str, int type);

/***********parse************/
int				parse(int ac, char **av, t_simulation *sim);

/*******parse_utils********/
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);

/*******program_utils********/
unsigned int	get_current_time(void);
void			*routine(void *data);
void			ft_sleep(t_philo *philo);
void			ft_think(t_philo *philo);
void			ft_eat(t_philo *philo);

/*******print_error********/
int				print_error(char *str, int type);

#endif
