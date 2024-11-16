/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:34:39 by gasroman          #+#    #+#             */
/*   Updated: 2024/11/15 20:15:02 by gasroman         ###   ########.fr       */
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

# define ENO_PHILO	"Not enough philosofers"
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
	int					t_meals;
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
	int				n_meals;
}	t_simulation;

/***********philo************/
int				print_error(char *str, int type);
int				init_simulation(t_simulation *sim);
void			check_philo_status(t_simulation *sim);
void			destroy_mutex(t_simulation *sim);

/***********parse************/
int				parse(int ac, char **av, t_simulation *sim);

/*******parse_utils********/
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);

/*******routine********/
void			*routine(void *data);
void			ft_sleep(t_philo *philo);
void			ft_think(t_philo *philo);
void			ft_eat(t_philo *philo);
unsigned int	get_current_time(void);

/*******general_utils********/
int				print_error(char *str, int type);
void			print_action(t_philo *philo, int flag, char *action);
unsigned int	get_sim_time(t_simulation *sim);
int				check_death(t_simulation *sim);

#endif
