#include <module/writer/_private/_writer.h>

static char _tmp_buffer[128]; // @static

bool napc_Writer_writeStringFormat(
	napc__Writer *ctx, const char *fmt, ...
) {
	va_list args;
	va_start(args, fmt);
	napc_vsnprintf(_tmp_buffer, sizeof(_tmp_buffer), fmt, args);
	va_end(args);

	return napc_Writer_writeString(ctx, _tmp_buffer);
}
