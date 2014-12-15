/**
 * @file                standart_arguments.h
 * @brief               Macros to access standart arguments.
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                2001-2002
 */

#ifndef __ENVIROMENT_STANDART_ARGUMENTS_H__
#define __ENVIROMENT_STANDART_ARGUMENTS_H__

typedef char *va_list;

#define	__va_promote(type) \
	(((sizeof (type) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#define	va_start(ap, last) \
	(ap = ((char *)&(last) + __va_promote(last)))

#define	va_arg(ap, type) \
	((type *)(ap += sizeof (type)))[-1]

#define	va_end(ap)

#endif /* __ENVIROMENT_STANDART_ARGUMENTS_H__ */
