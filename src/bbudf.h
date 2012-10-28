/*
 * File:   bbudf.h
 * Author: slavb
 *
 * Created on April 20, 2011, 2:09 PM
 */

#ifndef _BBUDF_H
#define	_BBUDF_H

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the FBUDF_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// FBUDF_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#if defined(WIN32)
#ifdef FBUDF_EXPORTS
#define FBUDF_API __declspec(dllexport)
#else
#define FBUDF_API __declspec(dllimport)
#endif
#else
#define FBUDF_API
#endif

//Original code for this library was written by Claudio Valderrama
// on July 2001 for IBPhoenix.

namespace internal {
	extern const int varchar_indicator_size;
	extern bool isnull(const paramdsc* v);
	extern paramdsc* setnull(paramdsc* v);
	extern int get_int_type(const paramdsc* v, ISC_INT64& rc);
	extern void set_int_type(paramdsc* v, const ISC_INT64 iv);
	extern int get_double_type(const paramdsc* v, double& rc);
	extern void set_double_type(paramdsc* v, const double iv);
	extern int get_any_string_type(const paramdsc* v, ISC_UCHAR*& text);
	extern void set_any_string_type(paramdsc* v, const int len0, ISC_UCHAR* text);
};

#endif	/* _BBUDF_H */
