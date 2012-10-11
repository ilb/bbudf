#include "stdafx.h"
#include "bbudf.h"
#include "inet.h"

 FBUDF_API void fn_inet_pton(const paramdsc* srcdsc, paramdsc* rc) {
	if(internal::isnull(srcdsc)){
		internal::setnull(rc);
		return;
	}
	unsigned char* src = 0;
	int srclen = internal::get_any_string_type(srcdsc,  src);
	if (srclen < 0) {
		internal::setnull(rc);
		return;
	}
	
	unsigned char buf[sizeof(struct in6_addr)];
	int s = inet_pton(AF_INET, (char*) src, buf);
	
	if (s<=0) {
		internal::setnull(rc);
		return;
	}
	//ISC_INT64 iv=1;
	ISC_INT64 iv=ntohl(*(ISC_INT64*) buf);
	internal::set_int_type(rc, iv);
	rc->dsc_scale = 0;
}
FBUDF_API void fn_inet_ntop(const paramdsc* srcdsc, paramdsc* rc) {
	if(internal::isnull(srcdsc)){
		internal::setnull(rc);
		return;
	}
	unsigned char str[INET6_ADDRSTRLEN];
	ISC_INT64 src;
	int srclen = internal::get_int_type(srcdsc,src);
	if (srclen < 0) {
		internal::setnull(rc);
		//internal::set_any_string_type(rc, 1, (unsigned char*)"a");
		return;
	}
	ISC_INT64 iv=htonl(src);
	if (inet_ntop(AF_INET,  &iv, (char*) str, INET6_ADDRSTRLEN) == NULL) {
		internal::setnull(rc);
		//internal::set_any_string_type(rc, 1, (unsigned char*)"b");
		return;
	}
	internal::set_any_string_type(rc, strlen((char*)str), str);
}