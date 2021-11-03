/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:51:47 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/03 16:51:49 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_error(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

int	error_manager(int error)
{
	if (error == 1)
		return (write_error("At least one wrong argument"));
	if (error == 2)
		return (write_error("Fatal error when intializing semaphores"));
	return (1);
}
