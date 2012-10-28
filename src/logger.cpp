#include "stdafx.h"
#include "bbudf.h"
#include "logger.h"

namespace logger {

	void syslog(int error, const char * format, ...) {
#if defined(WIN32)
#else
		va_list args;
		va_start(args, format);
		vsyslog((error ? LOG_ERR : LOG_DEBUG) | LOG_DAEMON | LOG_PID, format, args);
		va_end(args);
#endif
	}

	void blobprinf(blobcallback* blob, const char * format, ...) {
		char buf[1024];
		va_list args;
		va_start(args, format);
		int length = vsnprintf(buf, sizeof (buf), format, args);
		va_end(args);
		blob->blob_put_segment(blob->blob_handle, (ISC_UCHAR*) buf, length);
	}

}
