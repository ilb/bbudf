#include "stdafx.h"
#include "bbudf.h"
#include "curl.h"
#include "logger.h"
namespace curl {
	//TODO http://www.openssl.org/docs/crypto/threads.html#DESCRIPTION
	__thread CURL* ch=NULL;
	__thread long curl_response_code=0;
	int curl_global_init_called=0;

	size_t readfunction_blob( char *ptr, size_t size, size_t nmemb, void *userdata){
		unsigned short length,actual_length;
		length=size*nmemb;
		blobcallback* blob=(blobcallback*) userdata;
		int res;
		res=blob->blob_get_segment(blob->blob_handle,(ISC_UCHAR*)ptr,length,&actual_length);
		logger::syslog(0, "xmlreader::readfunction_blob() len=%d,res=%d,actual_length=%d",length,res,actual_length);
		return actual_length;
	}

	size_t writefunction_blob( char *ptr, size_t size, size_t nmemb, void *userdata){
		size_t length=size*nmemb;
		if(length>0){
			blobcallback* outblob=(blobcallback*) userdata;
			outblob->blob_put_segment(outblob->blob_handle, (ISC_UCHAR*) ptr, length);
		}
		return length;
	}
}

FBUDF_API void fn_curl_exec(const char* method,const char* url, const char* sslcert, const char* sslcertpassword,const char* cainfo, const char* headers, blobcallback* datablob, const char* cookies, blobcallback* outblob) {
	curl::curl_response_code=0;
	if (!outblob || !outblob->blob_handle){
		return;
	}
	CURLcode code;
	if(!curl::curl_global_init_called) {
		code=curl_global_init(CURL_GLOBAL_ALL);
		if(code != CURLE_OK){
			logger::blobprinf(outblob,"curl_global_init() failed: %s\n",curl_easy_strerror(code));
			return;
		}
		curl::curl_global_init_called=1;
	}
	CURL* ch;
	if(curl::ch==NULL){
		curl::ch=curl_easy_init();
		if(!curl::ch){
			logger::blobprinf(outblob,"curl_easy_init() failed\n");
			return;
		}
	}
	ch=curl::ch;
	curl_easy_setopt(ch,CURLOPT_NOSIGNAL,1);
	if (strcmp(method,"GET")==0){
		curl_easy_setopt(ch,CURLOPT_HTTPGET,1);
	}else if (strcmp(method,"POST")==0){
		curl_easy_setopt(ch,CURLOPT_POST,1);
	}else if (strcmp(method,"PUT")==0){
		curl_easy_setopt(ch,CURLOPT_PUT,1);
	}else if (strcmp(method,"HEAD")==0){
		curl_easy_setopt(ch,CURLOPT_NOBODY,1);
	}else{
		logger::blobprinf(outblob,"unknown method '%s'",method);
		return;
	}
	curl_easy_setopt(ch,CURLOPT_URL,url);
	curl_easy_setopt(ch,CURLOPT_SSLCERT,sslcert);
	curl_easy_setopt(ch,CURLOPT_SSLCERTPASSWD,sslcertpassword);
	curl_easy_setopt(ch,CURLOPT_CAINFO,cainfo);
	curl_easy_setopt(ch,CURLOPT_WRITEFUNCTION,curl::writefunction_blob);
	curl_easy_setopt(ch,CURLOPT_WRITEDATA,outblob);
	struct curl_slist *slist=NULL;
	if(headers){
#if defined(WIN32)
#else
		
		char *saveptr;
		char *headersdup=strdup(headers);
		char *token=strtok_r(headersdup, "\n", &saveptr);
		while(token){
			 slist = curl_slist_append(slist, token);
			 token=strtok_r(NULL, "\n", &saveptr);
		}
		free(headersdup);
#endif
	}
	curl_easy_setopt(ch, CURLOPT_HTTPHEADER, slist);
	curl_easy_setopt(ch, CURLOPT_COOKIE, cookies);
	if(datablob && datablob->blob_handle){
		//logger::syslog(0, "setup readfunction_blob(), data length=%d",datablob->blob_total_length);
		curl_easy_setopt(ch,CURLOPT_READFUNCTION,curl::readfunction_blob);
		curl_easy_setopt(ch,CURLOPT_READDATA,datablob);
		if (strcmp(method,"PUT")==0) {
			curl_easy_setopt(ch,CURLOPT_INFILESIZE,datablob->blob_total_length);
		}else{
			curl_easy_setopt(ch,CURLOPT_POSTFIELDSIZE,datablob->blob_total_length);
		}
	}
	code=curl_easy_perform(ch);
	if(slist){
		 curl_slist_free_all(slist);
	}
	if(code != CURLE_OK){
		logger::blobprinf(outblob,"curl_easy_perform() failed: %s\n",curl_easy_strerror(code));
		return;
	}
	curl_easy_getinfo(ch, CURLINFO_RESPONSE_CODE, &curl::curl_response_code);
}
FBUDF_API long fn_curl_get_response_code() {
	return curl::curl_response_code;
}