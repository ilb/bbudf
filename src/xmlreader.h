/*
 */

#ifndef _XMLREADER_H
#define	_XMLREADER_H


#ifdef __cplusplus
extern "C" {
#endif

FBUDF_API int fn_xmlreader_open(const char* path);
FBUDF_API int fn_xmlreader_openblob(blobcallback* datablob);
FBUDF_API int fn_xmlreader_close(int* readerId);
FBUDF_API int fn_xmlreader_read(int* readerId);
FBUDF_API char* fn_xmlreader_name(int* readerId);
FBUDF_API char* fn_xmlreader_localname(int* readerId);
FBUDF_API char* fn_xmlreader_value(int* readerId);
FBUDF_API int fn_xmlreader_depth(int* readerId);
FBUDF_API int fn_xmlreader_nodetype(int* readerId);
FBUDF_API int fn_xmlreader_isemptyelement(int* readerId);
FBUDF_API char* fn_xmlreader_getattribute(int* readerId, const char* name);
FBUDF_API char* fn_xmlreader_readString(int* readerId);
#ifdef __cplusplus
}
#endif

#endif	/* _XMLREADER_H */
