#include <module/reader/_private/_reader.h>

const char *napc_Reader_readLine(
	napc__Reader *ctx, char *line_buffer, napc_size line_buffer_size
) {
	NAPC_MAGIC_ASSERT(napc__Reader, ctx);

	if (!line_buffer_size) {
		NAPC_PANIC(
			"line_buffer_size cannot be zero inside napc_reader__readLine()."
		);
	}

	char ch = 0;
	napc_size pos = 0;

	napc_mzero(line_buffer, line_buffer_size);

	while (napc_Reader_readChar(ctx, &ch)) {
		bool shouldWrite = (line_buffer_size > pos);

		if (ch == '\n') {
			// Terminate line
			if (shouldWrite) line_buffer[pos] = 0;
			++pos;
			break;
		}

		if (shouldWrite) line_buffer[pos] = ch;
		++pos;
	}

	// Nothing has been read
	if (pos == 0) return NULL;

	// Attempt to terminate line
	if (line_buffer_size > pos) line_buffer[pos] = 0;

	// Always terminate line
	line_buffer[line_buffer_size - 1] = 0;

	return line_buffer;
}
