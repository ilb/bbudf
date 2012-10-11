/*
 */

#ifndef _BBUDF_CURL_H
#define	_BBUDF_CURL_H


#ifdef __cplusplus
extern "C" {
#endif

FBUDF_API void fn_curl_exec(const char* method,const char* url, const char* sslcert, const char* sslcertpassword,const char* cainfo, const char* headers, blobcallback* datablob, const char* cookies, blobcallback* outblob);
FBUDF_API long fn_curl_get_response_code();

#ifdef __cplusplus
}
#endif

#endif	/* _BBUDF_CURL_H */
