#include <napc-log/_private/_napc-log.h>

static char _message_buffer[1024]; // @static
static char _fn[64]; // @static
static char _message_pad[128]; // @static

static void _shortenFunctionName(const char *fn, char *buf) {
	napc_size fn_len = napc_strlen(fn);
	const napc_size max = 40;

	if (max >= fn_len) {
		napc_strncpy(buf, fn, 64);
		return;
	}

	napc_size start = fn_len - (max - 1);

	for (napc_size i = 0; i < max; ++i) {
		buf[i] = fn[start + i];
	}

	buf[0] = '.';
	buf[1] = '.';
	buf[2] = '.';

	buf[max - 1] = 0;
}

void napc_logMessage(
	const char *subsys,
	int level,
	const char *function,
	const char *fmt, ...
) {
	napc_time time = napc_getTimeSinceBoot();

	{
		const char *label = napc_logLevelToString(level);

		napc_mzero(_fn, sizeof(_fn));
		_shortenFunctionName(function, _fn);

		napc_snprintf(
			_message_buffer, sizeof(_message_buffer),
			"(%-5s +%010" NAPC_TIME_PRINTF " / %8" NAPC_SIZE_PRINTF ") subsys=%-23s [%40s] ",
			label, time, napc_getFreeMemory(), subsys, _fn
		);

		napc_puts(_message_buffer);
	}

	{
		va_list args;

		va_start(args, fmt);
		napc_vsnprintf(_message_buffer, sizeof(_message_buffer), fmt, args);
		va_end(args);
	}

	napc_snprintf(_message_pad, sizeof(_message_pad), "%105s", "");

	for (napc_size i = 0; i < napc_strlen(_message_buffer); ++i) {
		const char ch = _message_buffer[i];

		napc_putc(ch);

		if (ch == '\n') {
			napc_puts(_message_pad);
		}
	}

	napc_puts("\n");
}
