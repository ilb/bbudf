/* This file defines the new udfs for Firebird. */

set sql dialect 3;

/*
drop external function bbudf_file_get_contents;
drop external function bbudf_file_put_contents;
drop external function bbudf_tempnam;
*/

--FBUDF_API blobcallback* fn_file_get_contents(const paramdsc* v, blobcallback* outblob)
declare external function bbudf_file_get_contents cstring(512), blob returns parameter 2 entry_point 'fn_file_get_contents' module_name 'libbbudf';
--FBUDF_API int fn_file_put_contents(const char* filename, blobcallback* inblob, int* mode, int* append);
declare external function bbudf_file_put_contents cstring(512),blob,integer null,integer null returns integer by value entry_point 'fn_file_put_contents' module_name 'libbbudf';
--FBUDF_API char* fn_tempnam(const char *dir, const char *pfx, paramdsc* rc);
declare external function bbudf_tempnam cstring(64) null, cstring(64), varchar(255) by descriptor returns parameter 3 entry_point 'fn_tempnam' module_name 'libbbudf';