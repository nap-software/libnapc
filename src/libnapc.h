#if !defined(LIBNAPC_h)
	#define LIBNAPC_h

	#include <stdbool.h> // bool
	#include <stdlib.h> // NULL, free()
	#include <stdarg.h> // va_list

	// Source: https://stackoverflow.com/a/39618857/2005038
	/* Normally casting an expression to void discards its value, but GCC
	   versions 3.4 and newer have __attribute__ ((__warn_unused_result__))
	   which may cause unwanted diagnostics in that case.  Use __typeof__
	   and __extension__ to work around the problem, if the workaround is
	   known to be needed.  */
	#if 3 < __GNUC__ + (4 <= __GNUC_MINOR__)
		#define NAPC_IGNORE_VALUE(x) \
			(__extension__ ({ __typeof__ (x) __x = (x); (void) __x; }))
	#else
		#define NAPC_IGNORE_VALUE(x) ((void) (x))
	#endif

	#define NAPC_CONCAT_(a, b) a ## b
	#define NAPC_CONCAT(a, b) NAPC_CONCAT_(a, b)

	#define NAPC_FN_PRINTFLIKE(_1, _2) __attribute__((format(printf, _1, _2)))

	/*!
	 * @name NAPC_FN_WARNUNUSED_RET
	 * @version 1.0.0
	 * @description
	 * Tell the compiler to emit a warning if the return value of a function is not used.
	 * @changelog 1.0.0 17.02.2022 initial version
	 * @example
	 * int my_function() NAPC_FN_WARNUNUSED_RET() {
	 *     return 4;
	 * }
	 * 
	 * void napc_setup(const char *platform) {
	 *     my_function(); // will generate a compiler warning
	 * }
	 * 
	 * bool napc_loop(napc_time uptime) {
	 *     return false;
	 * }
	 */
	#define NAPC_FN_WARNUNUSED_RET()   __attribute__((warn_unused_result))
	#define NAPC_FN_NOINLINE()         __attribute__((noinline))
	#define NAPC_FN_NORETURN()         __attribute__((noreturn))
	#define NAPC_UNUSED_FN_PARAM()     __attribute__((unused))
	#define NAPC_FN_WEAK()             __attribute__((weak))

	#define NAPC_DEPRECATED_WITH_MESSAGE(_message, _replacement) \
			__attribute__((deprecated(_message, _replacement)))

	#define NAPC_DEPRECATED() \
			__attribute__((deprecated))

	#define NAPC_ARRAY_ELEMENTS(array) (sizeof(array) / sizeof(* array))

	#include <inttypes/inttypes.h>
#endif
