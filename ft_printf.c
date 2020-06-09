/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfreitas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:57:57 by sfreitas          #+#    #+#             */
/*   Updated: 2020/04/29 22:58:33 by sfreitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(const char *format, ...)
{
	va_list			item;
	struct hub_op	options;
	char			*text;

	va_start(item, format);
	while(search_percent((char*)format))
	{
		options = big_hub(-1, -1);
		if (options.width == -1)
			options = big_hub(va_arg(item, int), 2);
		if (options.precision == -1)
			options = big_hub(va_arg(item, int), 3);
		mensage_arg_solve(va_arg(item, void*), options.specifier);
		//ESPAÇO PARA O TRATAMENTO DE ARGUMENTO
		options = big_hub(0, 0);
	}
/*	printf("Flag: %d | ",m_options[0]);
	printf("Width: %d | ", m_options[1]);
	printf("Precision: %d | ", m_options[2]);
	printf("Length: %d | ", m_options[3]);
	printf("specifier: %c | ", m_options[4]);*/
	va_end(item);
	return (0);
}

void	mensage_arg_solve(void *value, char specifier)
{
	if (specifier == 'd' || specifier == 'i')
		store_int(value);
	else if (specifier == 'f' || specifier == 'F')
		store_float((float*)value);
}
//Tratamento dos argumentos
void	store_int (void *value)
{
	char *valor = (char*)value;
	struct hub_op	options;
	char *text;

	text = ft_itoa(valor);
}

void	store_float (float *value)
{
	struct hub_op	options;
	char *text;

	text = ft_itoa(*value);
}

char		search_percent(char *text)
{
	static int	i;

	while (text[i])
	{
		if (text[i] != '%')
			mensage_buffer(text[i]);
		else
		{
			i += specifier_options((char*)&text[i]);
			return (text[i]);
		}
		i++;
	}
	return (text[i]);
}

char		*mensage_buffer(char c)
{
	static char	*buffer;
	static int	i;

	buffer = add_buffer(c, buffer, i);
	i++;
	return (buffer);
}

struct hub_op	big_hub(int value, char field)
{
	static struct hub_op s_options;

	if (field == 0)
	{
		s_options.flags = 0;
		s_options.width = 0;
		s_options.precision = 0;
		s_options.length = 0;
		s_options.specifier = 0;
	}
	else if (field == 1)
		s_options.flags = value;
	else if (field == 2)
		s_options.width = value;
	else if (field == 3)
		s_options.precision = value;
	else if (field == 4)
		s_options.length = value;
	else if (field == 5)
		s_options.specifier = value;
	return (s_options);

}

char	*add_buffer(char c, char *buffer, int size)
{
	int i;
	char *temp;

	i = 0;
	temp = calloc(size + 2, sizeof(c));
	if (buffer)
	{
		while (buffer[i])
		{
			temp[i] = buffer[i];
			i++;
		}
		free(buffer);
	}
	temp[i] = c;
	return (temp);
}
