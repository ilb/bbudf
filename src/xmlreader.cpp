#include "stdafx.h"
#include "bbudf.h"
#include "xmlreader.h"
#include "logger.h"
#include "file.h"

namespace xmlreader {
	//TODO
	void xmlreader_errorhandler(void *arg, const char *msg, xmlParserSeverities severity, xmlTextReaderLocatorPtr locator){
		
	}
	char* xml2fbstr(xmlChar* xmlresult){
		char* ibresult=NULL;
		if(xmlresult) {
			int size=strlen((char*)xmlresult)+1;
			ibresult=(char*)ib_util_malloc(size);
			memcpy(ibresult,xmlresult,size);
			xmlFree(xmlresult);
		}
		return ibresult;
	}
	/*
	int readfunction_blob(void * context, char * buffer, int len){
		unsigned short actual_length;
		blobcallback* blob=(blobcallback*) context;
		int res=blob->blob_get_segment(blob->blob_handle,(ISC_UCHAR*)buffer,len,&actual_length);
		logger::syslog(0, "xmlreader::readfunction_blob() len=%d,res=%d,actual_length=%d",len,res,actual_length);
		return actual_length;
	}
	int closefunction_blob(void * context){
		return 0;
	}
	*/
}

FBUDF_API xmlTextReaderPtr fn_xmlreader_open(const char* path) {
	xmlTextReaderPtr reader=xmlNewTextReaderFilename(path);
	if (reader) {
		xmlTextReaderSetErrorHandler(reader, (xmlTextReaderErrorFunc)xmlreader::xmlreader_errorhandler, NULL);
	}
	return reader;
}

FBUDF_API xmlTextReaderPtr fn_xmlreader_openblob(blobcallback* datablob) {
	xmlTextReaderPtr reader=NULL;
	FILE* fptmp=tmpfile();
	file::blob2file(datablob,fptmp);
	rewind(fptmp);
	xmlParserInputBufferPtr input=xmlParserInputBufferCreateFile(fptmp,XML_CHAR_ENCODING_UTF8);
	if(input) {
		reader=xmlNewTextReader(input,"blob.xml");
		//так делать нельзя, т.к. после выхода из функции *datablob пользоваться нельзя
		//xmlReaderForIO(xmlreader::readfunction_blob,NULL,datablob,"blob.xml",NULL,0);
		if (reader) {
			xmlTextReaderSetErrorHandler(reader, (xmlTextReaderErrorFunc)xmlreader::xmlreader_errorhandler, NULL);
		}
	}
	return reader;
}

FBUDF_API int fn_xmlreader_close(xmlTextReaderPtr* reader) {
	xmlFreeTextReader(*reader);
	return 0;
}

FBUDF_API int fn_xmlreader_read(xmlTextReaderPtr* reader) {
	return xmlTextReaderRead(*reader);
}

FBUDF_API char* fn_xmlreader_name(xmlTextReaderPtr* reader) {
	return xmlreader::xml2fbstr(xmlTextReaderName(*reader));
}
FBUDF_API char* fn_xmlreader_localname(xmlTextReaderPtr* reader) {
	return xmlreader::xml2fbstr(xmlTextReaderLocalName(*reader));
}
FBUDF_API char* fn_xmlreader_value(xmlTextReaderPtr* reader) {
	return xmlreader::xml2fbstr(xmlTextReaderValue(*reader));
}

FBUDF_API int fn_xmlreader_depth(xmlTextReaderPtr* reader) {
	return xmlTextReaderDepth(*reader);
}
FBUDF_API int fn_xmlreader_nodetype(xmlTextReaderPtr* reader) {
	return xmlTextReaderNodeType(*reader);
}

FBUDF_API int fn_xmlreader_isemptyelement(xmlTextReaderPtr* reader) {
	return xmlTextReaderIsEmptyElement(*reader);
}

FBUDF_API char* fn_xmlreader_getattribute(xmlTextReaderPtr* reader, const char* name) {
	return xmlreader::xml2fbstr(xmlTextReaderGetAttribute(*reader,(xmlChar*)name));
}

FBUDF_API char* fn_xmlreader_readString(xmlTextReaderPtr* reader) {
	return xmlreader::xml2fbstr(xmlTextReaderReadString(*reader));
}
