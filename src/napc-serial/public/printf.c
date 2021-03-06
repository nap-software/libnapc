#include <napc-serial/_private/_napc-serial.h>
#include <string.h> // memset()
#include <stdio.h> // vsnprintf()

static char _printf_buffer[512]; // @static

void napc_printf(const char *fmt, ...) {
	if (PV_napc_serial_muted) return;

	va_list args;

	memset(_printf_buffer, 0, sizeof(_printf_buffer));

	va_start(args, fmt);
	vsnprintf(_printf_buffer, sizeof(_printf_buffer), fmt, args);
	va_end(args);

	_printf_buffer[sizeof(_printf_buffer) - 1] = 0;

	napc_puts(_printf_buffer);
}
