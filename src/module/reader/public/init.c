#include <module/reader/_private/_reader.h>

void napc_Reader_init(
	napc__Reader *ctx, const void *data, napc_size data_size
) {
	if (!data_size) {
		NAPC_PANIC("Size cannot be zero inside napc_Reader_init().");
	}

	ctx->data = data;
	ctx->size = data_size;
	ctx->_offset = 0;
	NAPC_MAGIC_INIT(napc__Reader, ctx);
}
