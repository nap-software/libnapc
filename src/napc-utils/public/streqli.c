#include <napc-utils/_private/_napc-utils.h>

bool napc_streqli(const char *str1, const char *str2) {
	return strcasecmp(str1, str2) == 0;
}
