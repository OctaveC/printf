#include "holberton.h"
/**
 * _print_char - Add char to our buffer
 * @args: pointer to the current va_arg
 * @flagstr: This a string of our flags, which we will apply
 *
 * Return: Our temporary buffer
 */
char *print_char(va_list args, char *flagstr)
{
	char c = va_arg(args, int);
	
	return (c);

}
/**
 * _print_string - Add a string to our buffer
 * @args: pointer to the current va_arg
 * @flagstr: This a string of our flags, which we will apply
 *
 * Return: Our temporary buffer
 */
char *print_string(va_list args, char *flagstr)
{
	char *s = va_arg(args, char *);

	if (s == NULL)
		s = "(NULL)";

	return (s);
}