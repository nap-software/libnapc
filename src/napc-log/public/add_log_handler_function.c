#include <napc-log/_private/_napc-log.h>

napc_ssize napc_addLogHandlerFunction(
	napc_logHandlerFunction handler
) {
	napc_ssize next_handler = -1;

	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(PV_napc_log_handler_array); ++i) {
		if (PV_napc_log_handler_array[i] == NULL) {
			next_handler = i;
		}
	}

	if (next_handler == -1) {
		return -1;
	}

	PV_napc_log_handler_array[next_handler] = handler;

	return next_handler;
}