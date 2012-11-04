#include "stdafx.h"
#include "bbudf.h"
#include "file.h"

namespace file {
	int blob2fd(blobcallback* inblob, int fd) {
		int result = 0;
		ISC_UCHAR *buf;
		ISC_USHORT length, actual_length;
		length = inblob->blob_max_segment + 1L;
		buf = (ISC_UCHAR *) malloc(length);
		while (inblob->blob_get_segment(inblob->blob_handle, buf, length, &actual_length)) {
			if (write(fd, buf, actual_length) == -1) {
				result = errno;
				break;
			}
		}
		free(buf);
		return result;
	}

	int blob2file(blobcallback* inblob, FILE* fp) {
		int result = 0;
		ISC_UCHAR *buf;
		ISC_USHORT length, actual_length;
		length = inblob->blob_max_segment + 1L;
		buf = (ISC_UCHAR *) malloc(length);
		while (inblob->blob_get_segment(inblob->blob_handle, buf, length, &actual_length)) {
			if (fwrite(buf, actual_length, 1, fp) != actual_length) {
				result = ferror(fp);
				break;
			}
		}
		free(buf);
		return result;
	}
	//http://stackoverflow.com/questions/675039/how-can-i-create-directory-tree-in-c-linux

	int do_mkdir(const char *path, int mode) {
		struct stat st;
		int status = 0;

		if (stat(path, &st) != 0) {
			/* Directory does not exist. EEXIST for race condition */
			if (mkdir(path, mode) != 0 && errno != EEXIST)
				status = -1;
		} else if (!S_ISDIR(st.st_mode)) {
			errno = ENOTDIR;
			status = -1;
		}

		return (status);
	}
}

FBUDF_API void fn_file_get_contents(const char* filename, blobcallback* outblob) {
	if (!filename || *filename == 0) {
		outblob->blob_handle = 0;
		return;
	}
	if (!outblob || !outblob->blob_handle) {
		return;
	}
	ISC_UCHAR buf[16384];
	int fd = open(filename, O_RDONLY);
	if (fd != -1) {
		int len = read(fd, buf, sizeof (buf));
		if (len != -1) {
			while (len > 0) {
				outblob->blob_put_segment(outblob->blob_handle, buf, len);
				len = read(fd, buf, sizeof (buf));
			}
		} else {
			outblob->blob_handle = 0;
		}
		close(fd);
	} else {
		outblob->blob_handle = 0;
	}
	return;
}

FBUDF_API int fn_file_put_contents(const char* filename, blobcallback* inblob, int* mode, int* append) {
	int result = 0;
	int oflag = O_CREAT | O_WRONLY | ((append && *append) ? O_APPEND : O_TRUNC);
	int fd = open(filename, oflag, (mode && *mode) ? *mode : 0666);
	if (fd != -1) {
		file::blob2fd(inblob, fd);
		close(fd);
	} else {
		result = errno;
	}
	return result;
}

FBUDF_API char* fn_tempnam(const char *dir, const char *pfx, paramdsc* rc) {
	char* value = tempnam(dir, pfx);
	int len = strlen(value);
	if (len > 255) {
		len = 255;
	}
	internal::set_any_string_type(rc, len, (ISC_UCHAR*) value);
	free(value);
}

/**
 ** mkpath - ensure all directories in path exist
 ** Algorithm takes the pessimistic view and works top-down to ensure
 ** each directory in path exists, rather than optimistically creating
 ** the last element and working backwards.
 */
FBUDF_API int fn_mkpath(const char *path, int* mode) {
	char *pp;
	char *sp;
	int status;
	int mode_=(mode && *mode) ? *mode : 0777;
	char *copypath = strdup(path);
	int result = 0;

	status = 0;
	pp = copypath;
	while (status == 0 && (sp = strchr(pp, PATH_SEPARATOR)) != 0) {
		if (sp != pp) {
			/* Neither root nor double slash in path */
			*sp = '\0';
			status = file::do_mkdir(copypath, mode_);
			*sp = PATH_SEPARATOR;
		}
		pp = sp + 1;
	}
	if (status == 0) {
		status = file::do_mkdir(path, mode_);
	}
	if (status != 0) {
		result=errno;
	}
	free(copypath);
	return result;
}

FBUDF_API void fn_dirname(const char *path, paramdsc* rc) {
	char *dirc=strdup(path);
	char *dirn=dirname(dirc);
	int len = strlen(dirn);
	if (len > 512) {
		len = 512;
	}
	internal::set_any_string_type(rc, len, (ISC_UCHAR*) dirn);
	free(dirc);
}

FBUDF_API int fn_unlink(const char *path) {
	int result=0;
	int status=unlink(path);
	if (status!=0){
		result=errno;
	}
	return result;
}
