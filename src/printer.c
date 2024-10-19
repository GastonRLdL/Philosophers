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
