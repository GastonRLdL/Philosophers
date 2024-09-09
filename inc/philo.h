/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:34:39 by gasroman          #+#    #+#             */
/*   Updated: 2024/09/07 04:33:29 by gasroman         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_mutex_t		l_m_flag;
	pthread_mutex_t		chopstick1;
	pthread_mutex_t		*chopstick2;
	pthread_t			philo;
	int					id;
	int					t_eaten;
	unsigned int		last_meal;
	struct s_program	*program;
}	t_philo;

typedef struct s_program
{
	t_philo			*philo;
	int				flag_dead;
	unsigned int	t_start;
	size_t			n_philo;
	size_t			t_death;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			n_eat;

	pthread_mutex_t	act_flag;
}	t_program;

/***********philo************/
int		print_error(char *str, int type);

/***********parse************/
int		parse(int ac, char **av, t_program *program);

/***********utils************/
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
#endif