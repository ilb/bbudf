/*
 *
 */


// bbudf.cpp : Defines the entry point for the DLL application.
//

/*
CVC: The MS way of doing things puts the includes in stdafx. I expect
that you can continue this trend without problems on other compilers
or platforms. Since I conditioned the Windows-related includes, it should
be easy to add needed headers to stdafx.h after a makefile is built.
*/


#include "stdafx.h"

#ifndef FBUDF_EXPORTS
#define FBUDF_EXPORTS
#endif

#include "bbudf.h"



//Original code for this library was written by Claudio Valderrama
// on July 2001 for IBPhoenix.

// Define this symbol if you want truncate and round to be symmetric wr to zero.
//#define SYMMETRIC_MATH

#if defined (_WIN32)
/*
BOOL APIENTRY DllMain( HANDLE ,//hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID //lpReserved
					  )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
*/
#endif


// To do: go from C++ native types to abstract FB types.




namespace internal
{
	typedef ISC_USHORT fb_len;

	const long seconds_in_day = 86400;
	const long tenthmsec_in_day = seconds_in_day * ISC_TIME_SECONDS_PRECISION;
	const int varchar_indicator_size = sizeof(ISC_USHORT);
	const int max_varchar_size = 65535 - varchar_indicator_size; // in theory


	// This definition comes from jrd\val.h and is used in helper
	// functions {get/set}_varchar_len defined below.
	struct vvary
	{
		fb_len		vary_length;
		ISC_UCHAR	vary_string[max_varchar_size];
	};

	/*
	inline fb_len get_varchar_len(const char* vchar)
	{
		return reinterpret_cast<const vvary*>(vchar)->vary_length;
	}
	*/

	inline fb_len get_varchar_len(const ISC_UCHAR* vchar)
	{
		return reinterpret_cast<const vvary*>(vchar)->vary_length;
	}

	inline void set_varchar_len(char* vchar, const fb_len len)
	{
		reinterpret_cast<vvary*>(vchar)->vary_length = len;
	}

	inline void set_varchar_len(ISC_UCHAR* vchar, const fb_len len)
	{
		reinterpret_cast<vvary*>(vchar)->vary_length = len;
	}

	bool isnull(const paramdsc* v)
	{
		return !v || !v->dsc_address || (v->dsc_flags & DSC_null);
	}

	paramdsc* setnull(paramdsc* v)
	{
		if (v)
			v->dsc_flags |= DSC_null;
		return v;
	}

	int get_int_type(const paramdsc* v, ISC_INT64& rc)
	{
		int s = -1;
		switch (v->dsc_dtype)
		{
		case dtype_short:
			rc = *reinterpret_cast<ISC_SHORT*>(v->dsc_address);
			s = sizeof(ISC_SHORT);
			break;
		case dtype_long:
			rc = *reinterpret_cast<ISC_LONG*>(v->dsc_address);
			s = sizeof(ISC_LONG);
			break;
		case dtype_int64:
			rc = *reinterpret_cast<ISC_INT64*>(v->dsc_address);
			s = sizeof(ISC_INT64);
			break;
		default:
			break;
		}
		return s;
	}

	void set_int_type(paramdsc* v, const ISC_INT64 iv)
	{
		switch (v->dsc_dtype)
		{
		case dtype_short:
			*reinterpret_cast<ISC_SHORT*>(v->dsc_address) = static_cast<ISC_SHORT>(iv);
			break;
		case dtype_long:
			*reinterpret_cast<ISC_LONG*>(v->dsc_address) = static_cast<ISC_LONG>(iv);
			break;
		case dtype_int64:
			*reinterpret_cast<ISC_INT64*>(v->dsc_address) = iv;
			break;
		}
	}

	int get_double_type(const paramdsc* v, double& rc)
	{
		int s = -1;
		switch (v->dsc_dtype)
		{
		case dtype_real:
			rc = static_cast<double>(*reinterpret_cast<float*>(v->dsc_address));
			s = sizeof(float);
			break;
		case dtype_double:
			rc = *reinterpret_cast<double*>(v->dsc_address);
			s = sizeof(double);
			break;
		default:
			break;
		}
		return s;
	}

	void set_double_type(paramdsc* v, const double iv)
	{
		switch (v->dsc_dtype)
		{
		case dtype_real:
			*reinterpret_cast<float*>(v->dsc_address) = static_cast<float>(iv);
			break;
		case dtype_double:
			*reinterpret_cast<double*>(v->dsc_address) = iv;
			break;
		}
	}

	int get_any_string_type(const paramdsc* v, ISC_UCHAR*& text)
	{
		int len = v->dsc_length;
		switch (v->dsc_dtype)
		{
		case dtype_text:
			text = v->dsc_address;
			break;
		case dtype_cstring:
			text = v->dsc_address;
			if (len && text)
			{
				const ISC_UCHAR* p = text; //strlen(v->dsc_address);
				while (*p)
					++p; // couldn't use strlen!
				if (p - text < len)
					len = p - text;
			}
			break;
		case dtype_varying:
			len -= varchar_indicator_size;
			text = reinterpret_cast<vvary*>(v->dsc_address)->vary_string;
			{
				const int x = get_varchar_len(v->dsc_address);
				if (x < len)
					len = x;
			}
			break;
		default:
			len = -1;
			break;
		}
		return len;
	}
	void set_any_string_type(paramdsc* v, const int len0, ISC_UCHAR* text = 0)
	{
		fb_len len = static_cast<fb_len>(len0);
		switch (v->dsc_dtype)
		{
		case dtype_text:
			v->dsc_length = len;
			if (text)
				memcpy(v->dsc_address, text, len);
			else
				memset(v->dsc_address, ' ', len);
			break;
		case dtype_cstring:
			v->dsc_length = len;
			if (text)
				memcpy(v->dsc_address, text, len);
			else
				v->dsc_length = len = 0;
			v->dsc_address[len] = 0;
			break;
		case dtype_varying:
			if (!text)
				len = 0;
			else if (len > max_varchar_size)
				len = max_varchar_size;
			v->dsc_length = len + static_cast<fb_len>(varchar_indicator_size);
			set_varchar_len(v->dsc_address, len);
			if (text)
				memcpy(v->dsc_address + varchar_indicator_size, text, len);
			break;
		}
	}
	int get_scaled_double(const paramdsc* v, double& rc)
	{
		ISC_INT64 iv;
		int rct = get_int_type(v, iv);
		if (rct < 0)
			rct = get_double_type(v, rc);
		else
		{
			rc = static_cast<double>(iv);
			int scale = v->dsc_scale;
			for (; scale < 0; ++scale)
				rc /= 10;
			for (; scale > 0; --scale)
				rc *= 10;
		}
		return rct;
	}
} // namespace internal

