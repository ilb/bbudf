#include "stdafx.h"
#include "bbudf.h"
#include "xmlreader.h"
#include "logger.h"
#include "file.h"

namespace xmlreader {
	//FIXME 100
	//__thread xmlTextReaderPtr instance[100];
	//__thread int instanceCnt=0;
	std::map <int, xmlTextReaderPtr> instance;
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
	int addInstance(xmlTextReaderPtr reader){
		int readerId=xmlreader::instance.size()+1;
		xmlreader::instance[readerId]=reader;
		return readerId;
	}
	xmlTextReaderPtr getInstance(int i){
		return xmlreader::instance[i];
	}
	void removeInstance(int i){
		xmlreader::instance.erase(i);
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

FBUDF_API int fn_xmlreader_open(const char* path) {
	xmlTextReaderPtr reader=xmlNewTextReaderFilename(path);
	if (reader) {
		xmlTextReaderSetErrorHandler(reader, (xmlTextReaderErrorFunc)xmlreader::xmlreader_errorhandler, NULL);
	}
	return xmlreader::addInstance(reader);
}

FBUDF_API int fn_xmlreader_openblob(blobcallback* datablob) {
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
	return xmlreader::addInstance(reader);
}

FBUDF_API int fn_xmlreader_close(int* readerId) {
	xmlTextReaderPtr reader=xmlreader::getInstance(*readerId);
	xmlFreeTextReader(reader);
	xmlreader::removeInstance(*readerId);
	return 0;
}

FBUDF_API int fn_xmlreader_read(int* readerId) {
	xmlTextReaderPtr reader=xmlreader::getInstance(*readerId);
	return xmlTextReaderRead(reader);
}

FBUDF_API char* fn_xmlreader_name(int* readerId) {
	xmlTextReaderPtr reader=xmlreader::getInstance(*readerId);
	return xmlreader::xml2fbstr(xmlTextReaderName(reader));
}
FBUDF_API char* fn_xmlreader_localname(int* readerId) {
	xmlTextReaderPtr reader=xmlreader::getInstance(*readerId);
	return xmlreader::xml2fbstr(xmlTextReaderLocalName(reader));
}
FBUDF_API char* fn_xmlreader_value(int* readerId) {
	xmlTextReaderPtr reader=xmlreader::getInstance(*readerId);
	return xmlreader::xml2fbstr(xmlTextReaderValue(reader));
}

FBUDF_API int fn_xmlreader_depth(int* readerId) {
	xmlTextReaderPtr reader=xmlreader::getInstance(*readerId);
	return xmlTextReaderDepth(reader);
}
FBUDF_API int fn_xmlreader_nodetype(int* readerId) {
	xmlTextReaderPtr reader=xmlreader::getInstance(*readerId);
	return xmlTextReaderNodeType(reader);
}

FBUDF_API int fn_xmlreader_isemptyelement(int* readerId) {
	xmlTextReaderPtr reader=xmlreader::getInstance(*readerId);
	return xmlTextReaderIsEmptyElement(reader);
}

FBUDF_API char* fn_xmlreader_getattribute(int* readerId, const char* name) {
	xmlTextReaderPtr reader=xmlreader::getInstance(*readerId);
	return xmlreader::xml2fbstr(xmlTextReaderGetAttribute(reader,(xmlChar*)name));
}

FBUDF_API char* fn_xmlreader_readString(int* readerId) {
	xmlTextReaderPtr reader=xmlreader::getInstance(*readerId);
	return xmlreader::xml2fbstr(xmlTextReaderReadString(reader));
}
