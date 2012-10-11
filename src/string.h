/*
 */

#ifndef _BBUDF_STRING_H
#define	_BBUDF_STRING_H


#ifdef __cplusplus
extern "C" {
#endif

FBUDF_API void fn_strerror(int* errnum, paramdsc* rc);
FBUDF_API void fn_getenv(char* name, paramdsc* rc);

#ifdef __cplusplus
}
#endif

#endif	/* _BBUDF_FILE_H */
