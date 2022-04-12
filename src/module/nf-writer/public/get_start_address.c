#include <module/nf-writer/_private/_nf-writer.h>

void *napc_NFWriter_getStartAddress(
	const napc__NFWriter *ctx
) {
	NAPC_MAGIC_ASSERT(napc__NFWriter, ctx);

	return napc_Writer_getCurrentAddress(&ctx->_writer);
}