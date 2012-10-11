/*
 */

#ifndef _BBUDF_SYSLOG_H
#define	_BBUDF_SYSLOG_H

namespace logger {
	void syslog(int error,const char * format, ...);
	void blobprinf(blobcallback* blob,const char * format, ...);
}

#endif	/* _BBUDF_FILE_H */
