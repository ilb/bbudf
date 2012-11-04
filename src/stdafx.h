/*
 */

#if !defined(AFX_STDAFX_H__F60BDFDF_7A2D_11D5_8EEB_4854E8274D24__INCLUDED_)
#define AFX_STDAFX_H__F60BDFDF_7A2D_11D5_8EEB_4854E8274D24__INCLUDED_

#include <ibase.h>
#include <ib_util.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libxml/xmlreader.h>
#if defined(WIN32)
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#include <arpa/inet.h>
#include <syslog.h>
#include <sys/stat.h>
#include <libgen.h>
#endif
#include <curl/curl.h>
#include <stdarg.h>
#include <errno.h>
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F60BDFDF_7A2D_11D5_8EEB_4854E8274D24__INCLUDED_)
