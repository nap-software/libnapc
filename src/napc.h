#if !defined(NAPC_h)
	#define NAPC_h

	#if defined(__cplusplus)
		extern "C" {
	#endif

	/*!
	 * @name napc_version
	 * @brief Get version of libnapc.
	 * @version 1.2.0
	 * @description
	 * Returns the version of libnapc implementation.
	 * @changelog 1.2.0 20.03.2022 initial version
	 */
	const char *napc_version(void);

	#include <napc-serial/napc-serial.h>
	#include <napc-time/napc-time.h>
	#include <napc-delay/napc-delay.h>
	#include <napc-utils/napc-utils.h>
	#include <napc-panic/napc-panic.h>
	#include <napc-core/napc-core.h>
	#include <napc-log/napc-log.h>
	#include <napc-rand-source/napc-rand-source.h>

	#include <module/pool/pool.h>
	#include <module/timer/timer.h>
	#include <module/random/random.h>
	#include <module/parser/parser.h>
	#include <module/aes/aes.h>
	#include <module/hmac/hmac.h>
	#include <module/misc/misc.h>
	#include <module/reader/reader.h>
	#include <module/writer/writer.h>
	#include <module/ipv4participant/ipv4participant.h>
	#include <module/dns/dns.h>
	#include <module/mem/mem.h>

	#include <hw.module/eth/eth.h>
	#include <hw.module/udp/udp.h>
	#include <hw.module/file/file.h>
	#include <hw.module/fs/fs.h>
	#include <hw.module/env/env.h>

	extern void napc_main(const char *platform);

	#if defined(__cplusplus)
		}
	#endif
#endif
