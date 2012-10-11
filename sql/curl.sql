/* This file defines the new udfs for Firebird. */

set sql dialect 3;

/*
drop external function bbudf_curl_exec;
drop external function bbudf_curl_get_response_code;
*/

-- FBUDF_API void fn_curl_exec(const char* method,const char* url, const char* sslcert, const char* sslcertpassword,const char* cainfo, const char* headers, blobcallback* datablob, blobcallback* outblob);
declare external function bbudf_curl_exec
cstring(4),cstring(1024),cstring(128),cstring(32),cstring(128),cstring(512) null,blob null,cstring(512) null,blob
returns parameter 9
entry_point 'fn_curl_exec' module_name 'libbbudf';
-- FBUDF_API int fn_curl_get_response_code();
declare external function bbudf_curl_get_response_code
returns int by value
entry_point 'fn_curl_get_response_code' module_name 'libbbudf';