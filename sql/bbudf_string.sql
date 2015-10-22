/* This file defines the new udfs for Firebird. */

set sql dialect 3;

/*
drop external function bbudf_strerror;
drop external function bbudf_getenv;
*/

--FBUDF_API void fn_strerror(int* errnum, paramdsc* rc);
declare external function bbudf_strerror int, varchar(255) by descriptor returns parameter 2 entry_point 'fn_strerror' module_name 'libbbudf';
--FBUDF_API void fn_getenv(const char* name, paramdsc* rc);
declare external function bbudf_getenv cstring(255), varchar(255) by descriptor returns parameter 2 entry_point 'fn_getenv' module_name 'libbbudf';
