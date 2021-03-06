#include "holberton.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * rev_string - function that reverses a string
 * @args: pointer to the current arg
 * @flagstr: tmpBuffer
 * Return: reversed string
 */
char *rev_string(va_list args, __attribute__((unused))char *flagstr)
{
	int i = 0;
	int max, min, temp;
	char *s = va_arg(args, char *);
	char *str;

	if (s == NULL)
	{
		str = _calloc(sizeof(char), (7));
		str = _strcat(str, "(null)");
		return (str);
	}

	if (!s)
		return (NULL);
	min = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	str = _calloc(i + 1, sizeof(char));
	max = i - 1;
	for (min = 0; min <= i / 2; min++, max--)
	{
		temp = s[max];
		str[max] = s[min];
		str[min] = temp;
	}
	return (str);
}
