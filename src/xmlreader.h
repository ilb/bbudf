/*
 */

#ifndef _XMLREADER_H
#define	_XMLREADER_H


#ifdef __cplusplus
extern "C" {
#endif

FBUDF_API xmlTextReaderPtr fn_xmlreader_open(const char* path);
FBUDF_API xmlTextReaderPtr fn_xmlreader_openblob(blobcallback* datablob);
FBUDF_API int fn_xmlreader_close(xmlTextReaderPtr* reader);
FBUDF_API int fn_xmlreader_read(xmlTextReaderPtr* reader);
FBUDF_API char* fn_xmlreader_name(xmlTextReaderPtr* reader);
FBUDF_API char* fn_xmlreader_value(xmlTextReaderPtr* reader);
FBUDF_API int fn_xmlreader_depth(xmlTextReaderPtr* reader);
FBUDF_API int fn_xmlreader_nodetype(xmlTextReaderPtr* reader);
FBUDF_API int fn_xmlreader_isemptyelement(xmlTextReaderPtr* reader);
FBUDF_API char* fn_xmlreader_getattribute(xmlTextReaderPtr* reader, const char* name);
FBUDF_API char* fn_xmlreader_readString(xmlTextReaderPtr* reader);
#ifdef __cplusplus
}
#endif

#endif	/* _XMLREADER_H */
