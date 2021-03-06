#include <module/writer/_private/_writer.h>

bool napc_Writer_writeString(
	napc__Writer *ctx, const char *value
) {
	napc_size str_len = napc_strlen(value);

	if (!PV_napc_Writer_checkAccess(ctx, str_len, "string")) {
		return false;
	}

	char *data = ctx->data;

	for (napc_size i = 0; i < str_len; ++i) {
		data[ctx->_offset + i] = value[i];
	}

	ctx->_offset += str_len;

	return true;
}
