#include "stdafx.h"
#include "bbudf.h"
#include "string.h"
#include "logger.h"

FBUDF_API void fn_strerror(int* errnum, paramdsc* rc) {
#if defined(WIN32)
#else
	char buf[255];
	char* value=strerror_r(*errnum,buf,sizeof(buf));
	internal::set_any_string_type(rc, strlen(value), (ISC_UCHAR*) value);
#endif
}

FBUDF_API void fn_getenv(char* name, paramdsc* rc) {
	char* value=getenv(name);
        if(value==NULL){
		internal::setnull(rc);
		return;
        }
	int len=strlen(value);
	const int maxlen=255; //rc->dsc_length-internal::varchar_indicator_size;
	if(len>maxlen){
		len=maxlen;
	}
	internal::set_any_string_type(rc, len, (ISC_UCHAR*) value);
}