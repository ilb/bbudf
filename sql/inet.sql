/* This file defines the new udfs for Firebird. */

set sql dialect 3;

declare external function IPSTRINGTONUMBER
cstring(46) by descriptor, int by descriptor returns parameter 2
entry_point 'fn_inet_pton' module_name 'libbbudf';

declare external function IPNUMBERTOSTRING
int by descriptor, varchar(46) by descriptor returns parameter 2
entry_point 'fn_inet_ntop' module_name 'libbbudf';