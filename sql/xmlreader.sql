/* This file defines the new udfs for Firebird. */

set sql dialect 3;

/*
drop external function bbudf_xmlreader_open;
drop external function bbudf_xmlreader_close;
drop external function bbudf_xmlreader_read;
drop external function bbudf_xmlreader_name;
drop external function bbudf_xmlreader_value;
drop external function bbudf_xmlreader_depth;
drop external function bbudf_xmlreader_nodetype;
drop external function bbudf_xmlreader_isemptyelement;
drop external function bbudf_xmlreader_getattribute;
drop external function bbudf_xmlreader_readString;
*/

declare external function bbudf_xmlreader_open
cstring(512) CHARACTER SET UTF8 returns int by value
entry_point 'fn_xmlreader_open' module_name 'libbbudf';

declare external function bbudf_xmlreader_openblob
blob returns int by value
entry_point 'fn_xmlreader_openblob' module_name 'libbbudf';

declare external function bbudf_xmlreader_close
int returns int by value
entry_point 'fn_xmlreader_close' module_name 'libbbudf';

declare external function bbudf_xmlreader_read
int returns int by value
entry_point 'fn_xmlreader_read' module_name 'libbbudf';

declare external function bbudf_xmlreader_name
int returns cstring(128) CHARACTER SET UTF8 free_it
entry_point 'fn_xmlreader_name' module_name 'libbbudf';

declare external function bbudf_xmlreader_value
int returns cstring(512) CHARACTER SET UTF8 free_it
entry_point 'fn_xmlreader_value' module_name 'libbbudf';

declare external function bbudf_xmlreader_depth
int returns int by value
entry_point 'fn_xmlreader_depth' module_name 'libbbudf';

declare external function bbudf_xmlreader_nodetype
int returns int by value
entry_point 'fn_xmlreader_nodetype' module_name 'libbbudf';

declare external function bbudf_xmlreader_isemptyelement
int returns int by value
entry_point 'fn_xmlreader_isemptyelement' module_name 'libbbudf';

declare external function bbudf_xmlreader_getattribute
int,cstring(128) returns cstring(512) CHARACTER SET UTF8 free_it
entry_point 'fn_xmlreader_getattribute' module_name 'libbbudf';

declare external function bbudf_xmlreader_readString
int returns cstring(8191) CHARACTER SET UTF8 free_it
entry_point 'fn_xmlreader_readString' module_name 'libbbudf';
