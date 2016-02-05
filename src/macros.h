/*
 * RobotVikings
 * macros.h
 * 12/6/15
 * Defines some macros to be used by other classes
 */

#ifndef _MACROS_H_
#define _MACROS_H_

// What do you want me to write here?
#define forever for(;;)

/*
 * The first 400-ish digits of PI
 * You never know if/when we may need it.
 * Although, we can't actually use all of it, since the number gets cut off by the compiler.
 * Oh well. ¯\_(ツ)_/¯ *shrugs*
 */
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609

// Just in case NULL isn't actually defined.
#ifndef NULL
#define NULL 0
#endif

#endif
