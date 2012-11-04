/*
 */

#ifndef _BBUDF_FILE_H
#define	_BBUDF_FILE_H


#ifdef __cplusplus
extern "C" {
#endif
namespace file {
	int blob2file(blobcallback* inblob,FILE* fp);
}
FBUDF_API void fn_file_get_contents(const char* filename, blobcallback* outblob);
FBUDF_API int fn_file_put_contents(const char* filename, blobcallback* inblob, int* mode, int* append);
FBUDF_API char* fn_tempnam(const char *dir, const char *pfx, paramdsc* rc);
FBUDF_API int fn_mkpath(const char *path, int* mode);
FBUDF_API char* fn_dirname(const char *path, paramdsc* rc);
#ifdef __cplusplus
}
#endif

#endif	/* _BBUDF_FILE_H */
