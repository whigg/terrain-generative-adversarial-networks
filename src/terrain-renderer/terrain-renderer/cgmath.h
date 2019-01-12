#ifndef __CGMATH_H__
#define __CGMATH_H__
//###################################################################
// COMMON HEADERS for GXUT
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
// C standard
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// user types
typedef unsigned int	uint;
typedef unsigned char	uchar;
typedef unsigned short	ushort;
// end COMMON HEADERS for GXUT
//###################################################################

// define
#ifndef PI
#define PI 3.141592653589793f
#endif

#ifndef max
	#define max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef min
	#define min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef clamp
	#define clamp(value,vmin,vmax) (max(vmin,min(vmax,value)))
#endif
#ifndef isnan
	#define	isnan(x) (x!=x)
#endif

//*******************************************************************
// NEVER USE VIRTUAL for a template class !!!
//*******************************************************************

template <class T> struct _tvec2
{
	union{ struct { T r, g; }; struct { T x, y; }; };

	// constructor/set
	_tvec2(){ x=y=0; }
	_tvec2( T a ){ x=y=a; }						inline void set( T a ){ x=y=a; }						
	_tvec2( T a, T b ){ x=a;y=b; }				inline void set( T a, T b ){ x=a;y=b; }
	_tvec2( const _tvec2& v ){ x=v.x;y=v.y; }	inline void set( const _tvec2& v ){ x=v.x;y=v.y; }
	_tvec2( const T* a ){ x=a[0];y=a[1]; }		inline void set( const T* a ){ x=a[0];y=a[1]; }

	// assignment
	inline _tvec2& operator=( T a ){ set(a); return *this; }
	inline _tvec2& operator=( const T* a ){ set(a); return *this; }

	// array operator
	inline T& operator[]( int i ){ return (&x)[i]; }
	inline const T& operator[]( int i ) const { return (&x)[i]; }
	inline T& at( int i ){ return (&x)[i]; }
	inline const T& at( int i ) const { return (&x)[i]; }

	// casting
	inline operator T*(){ return &x; }
	inline operator const T*(){ return &x; }

	// length and unary
	inline T length(){ return T(sqrt(x*x+y*y)); }	inline const T length() const { return T(sqrt(x*x+y*y)); }
	inline T length2(){ return T(x*x+y*y); }		inline const T length2() const { return T(x*x+y*y); }
	inline _tvec2 operator+(){ return *this; }
	inline _tvec2 operator+() const { return *this; }
	inline _tvec2 operator-(){ return _tvec2(-x,-y); }
	inline _tvec2 operator-() const { return _tvec2(-x,-y); }

	// normalize
	inline _tvec2 normalize(){ return operator/(length()); }

	// binary
	inline _tvec2 operator+( _tvec2& v ){ return _tvec2(x+v.x,y+v.y); }
	inline _tvec2 operator+( const _tvec2& v ) const { return _tvec2(x+v.x,y+v.y); }
	inline _tvec2 operator-( _tvec2& v ){ return _tvec2(x-v.x,y-v.y); }
	inline _tvec2 operator-( const _tvec2& v ) const { return _tvec2(x-v.x,y-v.y); }
	inline _tvec2 operator*( T a ){ return _tvec2(x*a,y*a); }
	inline _tvec2 operator/( T a ){ return _tvec2(x/a,y/a); }
	inline _tvec2 operator*( _tvec2& v ){ return _tvec2(x*v.x,y*v.y); }
	inline _tvec2 operator/( _tvec2& v ){ return _tvec2(x/v.x,y/v.y); }
	inline _tvec2 operator*( const _tvec2& v ) const { return _tvec2(x*v.x,y*v.y); }
	inline _tvec2 operator/( const _tvec2& v ) const { return _tvec2(x/v.x,y/v.y); }

	// assignment
	inline _tvec2& operator+=( const _tvec2& v ){ x+=v.x; y+=v.y; return *this; }
	inline _tvec2& operator-=( const _tvec2& v ){ x-=v.x; y-=v.y; return *this; }
	inline _tvec2& operator*=( T a ){ x*=a; y*=a; return *this; }
	inline _tvec2& operator/=( T a ){ x/=a; y/=a; return *this; }
	inline _tvec2& operator*=( _tvec2& v ){ x*=v.x; y*=v.y; return *this; }
	inline _tvec2& operator/=( _tvec2& v ){ x/=v.x; y/=v.y; return *this; }

	// comparison
	inline bool operator==( _tvec2& v ){ return x==v.x&&y==v.y; }
	inline bool operator!=( _tvec2& v ){ return x!=v.x||y!=v.y; }
	inline bool operator==( const _tvec2& v ) const { return x==v.x&&y==v.y; }
	inline bool operator!=( const _tvec2& v ) const { return x!=v.x||y!=v.y; }

	// dot product
	inline T dot( _tvec2 v ){ return x*v.x+y*v.y; }
	inline T dot( const _tvec2& v ) const { return x*v.x+y*v.y; }

	// swizzle
	inline _tvec2& xy(){ return *this; }
};

template <class T> struct _tvec3
{
	union
	{
		struct { T r, g, b; };
		struct { T x, y, z; };
		struct { _tvec2<T> xy; T z; };
		struct { T x; _tvec2<T> yz; };
		struct { _tvec2<T> rg; T b; };
		struct { T r; _tvec2<T> gb; };
	};

	// constructor/set
	_tvec3(){ x=y=z=0; }
	_tvec3( T a ){ x=y=z=a; }								inline void set( T a ){ x=y=z=a; }
	_tvec3( T a, T b, T c ){ x=a;y=b;z=c; }					inline void set( T a, T b, T c ){ x=a;y=b;z=c; }
	_tvec3( const _tvec3& v ){ x=v.x;y=v.y;z=v.z; }			inline void set( const _tvec3& v ){ x=v.x;y=v.y;z=v.z; }
	_tvec3( const T* a ){ x=a[0];y=a[1];z=a[2]; }			inline void set( const T* a ){ x=a[0];y=a[1];z=a[2]; }
	_tvec3( const _tvec2<T>& v, T c ){ x=v.x;y=v.y;z=c; }	inline void set( const _tvec2<T>& v, T c ){ x=v.x;y=v.y;z=c; }
	_tvec3( T a, const _tvec2<T>& v ){ x=a;y=v.x;z=v.y; }	inline void set( T a, const _tvec2<T>& v ){ x=a;y=v.x;z=v.y; }

	// assignment
	inline _tvec3& operator=( T a ){ set(a); return *this; }
	inline _tvec3& operator=( const T* a ){ set(a); return *this; }

	// array operator
	inline T& operator[]( int i ){ return (&x)[i]; }
	inline const T& operator[]( int i ) const { return (&x)[i]; }
	inline T& at( int i ){ return (&x)[i]; }
	inline const T& at( int i ) const { return (&x)[i]; }

	// casting
	inline operator T*(){ return &x; }
	inline operator const T*(){ return &x; }

	// length and unary
	inline T length(){ return T(sqrt(x*x+y*y+z*z)); }	inline const T length() const { return T(sqrt(x*x+y*y+z*z)); }
	inline T length2(){ return T(x*x+y*y+z*z); }		inline const T length2() const { return T(x*x+y*y+z*z); }
	inline _tvec3 operator+(){ return *this; }
	inline _tvec3 operator+() const { return *this; }
	inline _tvec3 operator-(){ return _tvec3(-x,-y,-z); }
	inline _tvec3 operator-() const { return _tvec3(-x,-y,-z); }

	// normalize
	inline _tvec3 normalize(){ return operator/(length()); }

	// binary
	inline _tvec3 operator+( _tvec3& v ){ return _tvec3(x+v.x,y+v.y,z+v.z); }
	inline _tvec3 operator+( const _tvec3& v ) const { return _tvec3(x+v.x,y+v.y,z+v.z); }
	inline _tvec3 operator-( _tvec3& v ){ return _tvec3(x-v.x,y-v.y,z-v.z); }
	inline _tvec3 operator-( const _tvec3& v ) const { return _tvec3(x-v.x,y-v.y,z-v.z); }
	inline _tvec3 operator*( T a ){ return _tvec3(x*a,y*a,z*a); }
	inline _tvec3 operator/( T a ){ return _tvec3(x/a,y/a,z/a); }
	inline _tvec3 operator*( _tvec3& v ){ return _tvec3(x*v.x,y*v.y,z*v.z); }
	inline _tvec3 operator/( _tvec3& v ){ return _tvec3(x/v.x,y/v.y,z/v.z); }
	inline _tvec3 operator*( const _tvec3& v ) const { return _tvec3(x*v.x,y*v.y,z*v.z); }
	inline _tvec3 operator/( const _tvec3& v ) const { return _tvec3(x/v.x,y/v.y,z/v.z); }

	// assignment
	inline _tvec3& operator+=( const _tvec3& v ){ x+=v.x; y+=v.y; z+=v.z; return *this; }
	inline _tvec3& operator-=( const _tvec3& v ){ x-=v.x; y-=v.y; z-=v.z; return *this; }
	inline _tvec3& operator*=( T a ){ x*=a; y*=a; z*=a; return *this; }
	inline _tvec3& operator/=( T a ){ x/=a; y/=a; z/=a; return *this; }
	inline _tvec3& operator*=( _tvec3& v ){ x*=v.x; y*=v.y; z*=v.z; return *this; }
	inline _tvec3& operator/=( _tvec3& v ){ x/=v.x; y/=v.y; z/=v.z; return *this; }

	// comparison
	inline bool operator==( _tvec3& v ){ return x==v.x&&y==v.y&&z==v.z; }
	inline bool operator!=( _tvec3& v ){ return x!=v.x||y!=v.y||z!=v.z; }
	inline bool operator==( const _tvec3& v ) const { return x==v.x&&y==v.y&&z==v.z; }
	inline bool operator!=( const _tvec3& v ) const { return x!=v.x||y!=v.y||z!=v.z; }

	// dot product
	inline T dot( _tvec3 v ){ return x*v.x+y*v.y+z*v.z; }
	inline T dot( const _tvec3& v ) const { return x*v.x+y*v.y+z*v.z; }

	// _tvec3 only: cross product
	inline _tvec3 operator^( _tvec3& v ){ return _tvec3( y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x ); }
	inline _tvec3 operator^( const _tvec3& v ) const { return _tvec3( y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x ); }
	inline _tvec3 cross( _tvec3& v ){ return _tvec3( y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x ); }
	inline _tvec3 cross( const _tvec3& v ) const { return _tvec3( y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x ); }
};

template <class T> struct _tvec4
{
	union
	{
		struct { T r, g, b, a; };
		struct { T x, y, z, w; };
		struct { _tvec2<T> xy; _tvec2<T> zw; };
		struct { T x; _tvec2<T> yz; T w; };
		struct { _tvec3<T> xyz; T w; };
		struct { T x; _tvec3<T> yzw; };
		struct { _tvec2<T> rg; _tvec2<T> ba; };
		struct { T r; _tvec2<T> gb; T a; };
		struct { _tvec3<T> rgb; T a; };
		struct { T r; _tvec3<T> gba; };
	};

	// constructor/set
	_tvec4(){ x=y=z=w=0; }
	_tvec4( T a ){ x=y=z=w=a; }										inline void set( T a ){ x=y=z=w=a; }
	_tvec4( T a, T b, T c, T d ){ x=a;y=b;z=c;w=d; }				inline void set( T a, T b, T c, T d ){ x=a;y=b;z=c;w=d; }
	_tvec4( const _tvec4& v ){ x=v.x;y=v.y;z=v.z;w=v.w; }			inline void set( const _tvec4& v ){ x=v.x;y=v.y;z=v.z;w=v.w; }
	_tvec4( const T* a ){ x=a[0];y=a[1];z=a[2];w=a[3]; }			inline void set( const T* a ){ x=a[0];y=a[1];z=a[2];w=a[3]; }
	_tvec4( const _tvec2<T>& v, T c, T d ){ x=v.x;y=v.y;z=c;w=d; }	inline void set( const _tvec2<T>& v, T c, T d ){ x=v.x;y=v.y;z=c;w=d; }
	_tvec4( T a, T b, const _tvec2<T>& v ){ x=a;y=b;z=v.x;w=v.y; }	inline void set( T a, T b, const _tvec2<T>& v ){ x=a;y=b;z=v.x;w=v.y; }	
	_tvec4( const _tvec3<T>& v, T d ){ x=v.x;y=v.y;z=v.z;w=d; }		inline void set( const _tvec3<T>& v, T d ){ x=v.x;y=v.y;z=v.z;w=d; }
	_tvec4( T a, const _tvec3<T>& v ){ x=a;y=v.x;z=v.y;w=v.z; }		inline void set( T a, const _tvec3<T>& v ){ x=a;y=v.x;z=v.y;w=v.z; }
	_tvec4( const _tvec2<T>& v1, const _tvec2<T>& v2 ){ x=v1.x;y=v1.y;z=v2.x;w=v2.y; }
	inline void set( const _tvec2<T>& v1, const _tvec2<T>& v2 ){ x=v1.x;y=v1.y;z=v2.x;w=v2.y; }

	// assignment
	inline _tvec4& operator=( T a ){ set(a); return *this; }
	inline _tvec4& operator=( const T* a ){ set(a); return *this; }
	
	// array operator
	inline T& operator[]( int i ){ return (&x)[i]; }
	inline const T& operator[]( int i ) const { return (&x)[i]; }
	inline T& at( int i ){ return (&x)[i]; }
	inline const T& at( int i ) const { return (&x)[i]; }

	// casting
	inline operator T*(){ return &x; }
	inline operator const T*(){ return &x; }

	// length and unary
	inline T length(){ return T(sqrt(x*x+y*y+z*z+w*w)); }	inline const T length() const { return T(sqrt(x*x+y*y+z*z+w*w)); }
	inline T length2(){ return T(x*x+y*y+z*z+w*w); }		inline const T length2() const { return T(x*x+y*y+z*z+w*w); }
	inline _tvec4 operator+(){ return *this; }
	inline _tvec4 operator+() const { return *this; }
	inline _tvec4 operator-(){ return _tvec4(-x,-y,-z,-w); }
	inline _tvec4 operator-() const { return _tvec4(-x,-y,-z,-w); }

	// normalize
	inline _tvec4 normalize(){ return operator/(length()); }

	// binary
	inline _tvec4 operator+( _tvec4& v ){ return _tvec4(x+v.x,y+v.y,z+v.z,w+v.w); }
	inline _tvec4 operator+( const _tvec4& v ) const { return _tvec4(x+v.x,y+v.y,z+v.z,w+v.w); }
	inline _tvec4 operator-( _tvec4& v ){ return _tvec4(x-v.x,y-v.y,z-v.z,w-v.w); }
	inline _tvec4 operator-( const _tvec4& v ) const { return _tvec4(x-v.x,y-v.y,z-v.z,w-v.w); }
	inline _tvec4 operator*( T a ){ return _tvec4(x*a,y*a,z*a,w*a); }
	inline _tvec4 operator/( T a ){ return _tvec4(x/a,y/a,z/a,w/a); }
	inline _tvec4 operator*( _tvec4& v ){ return _tvec4(x*v.x,y*v.y,z*v.z,w*v.w); }
	inline _tvec4 operator/( _tvec4& v ){ return _tvec4(x/v.x,y/v.y,z/v.z,w/v.w); }
	inline _tvec4 operator*( const _tvec4& v ) const { return _tvec4(x*v.x,y*v.y,z*v.z,w*v.w); }
	inline _tvec4 operator/( const _tvec4& v ) const { return _tvec4(x/v.x,y/v.y,z/v.z,w/v.w); }

	// assignment
	inline _tvec4& operator+=( const _tvec4& v ){ x+=v.x; y+=v.y; z+=v.z; w+=v.w; return *this; }
	inline _tvec4& operator-=( const _tvec4& v ){ x-=v.x; y-=v.y; z-=v.z; w-=v.w; return *this; }
	inline _tvec4& operator*=( T a ){ x*=a; y*=a; z*=a; w*=a; return *this; }
	inline _tvec4& operator/=( T a ){ x/=a; y/=a; z/=a; w/=a; return *this; }
	inline _tvec4& operator*=( _tvec4& v ){ x*=v.x; y*=v.y; z*=v.z; w*=v.w; return *this; }
	inline _tvec4& operator/=( _tvec4& v ){ x/=v.x; y/=v.y; z/=v.z; w/=v.w; return *this; }

	// comparison
	inline bool operator==( _tvec4& v ){ return x==v.x&&y==v.y&&z==v.z&&w==v.w; }
	inline bool operator!=( _tvec4& v ){ return x!=v.x||y!=v.y||z!=v.z||w!=v.w; }
	inline bool operator==( const _tvec4& v ) const { return x==v.x&&y==v.y&&z==v.z&&w==v.w; }
	inline bool operator!=( const _tvec4& v ) const { return x!=v.x||y!=v.y||z!=v.z||w!=v.w; }

	// dot product
	inline T dot( _tvec4 v ){ return x*v.x+y*v.y+z*v.z+w*v.w; }
	inline T dot( const _tvec4& v ) const { return x*v.x+y*v.y+z*v.z+w*v.w; }
};

//*******************************************************************
// typedef
typedef _tvec2<float>	float2;		typedef _tvec3<float> float3;		typedef _tvec4<float> float4;
typedef _tvec2<int>		int2;		typedef _tvec3<int>	int3;			typedef _tvec4<int>	int4;
typedef _tvec2<uint>	uint2;		typedef _tvec3<uint>	uint3;		typedef _tvec4<uint>	uint4;

typedef _tvec2<float>	vec2;		typedef _tvec3<float> vec3;			typedef _tvec4<float> vec4;
typedef _tvec2<int>		ivec2;		typedef _tvec3<int>	ivec3;			typedef _tvec4<int>	ivec4;
typedef _tvec2<uint>	uvec2;		typedef _tvec3<uint>	uvec3;		typedef _tvec4<uint>	uvec4;
typedef _tvec2<uchar>	uchar2;		typedef _tvec3<uchar>	uchar3;		typedef _tvec4<uchar>	uchar4;

//*******************************************************************
// matrix 4x4: uses a standard row-major notation.
//             Be careful with OpenGL column-major notations.
struct matrix
{
	union { float a[16]; struct {float _11,_12,_13,_14,_21,_22,_23,_24,_31,_32,_33,_34,_41,_42,_43,_44;}; };

	matrix(){ setIdentity(); }
	matrix( float* f ){ memcpy(a,f,sizeof(float)*16); }
	matrix( float f11, float f12, float f13, float f14, float f21, float f22, float f23, float f24, float f31, float f32, float f33, float f34, float f41, float f42, float f43, float f44 ){_11=f11;_12=f12;_13=f13;_14=f14;_21=f21;_22=f22;_23=f23;_24=f24;_31=f31;_32=f32;_33=f33;_34=f34;_41=f41;_42=f42;_43=f43;_44=f44;}
	
	// basic operation
	inline void setIdentity(){ _12=_13=_14=_21=_23=_24=_31=_32=_34=_41=_42=_43=0.0f;_11=_22=_33=_44=1.0f; }
	inline matrix transpose() const { return matrix(_11,_21,_31,_41,_12,_22,_32,_42,_13,_23,_33,_43,_14,_24,_34,_44); }

	// static
	static matrix identity(){ return matrix(); }
	
	// column/row vectors
	inline vec4 cvec4( int col ) const { return vec4(a[col+0],a[col+4],a[col+8],a[col+12]); }
	inline vec3 cvec3( int col ) const { return vec3(a[col+0],a[col+4],a[col+8]); }
	inline vec4& rvec4( int row ){ return reinterpret_cast<vec4&>(a[4*row]); }
	inline vec3& rvec3( int row ){ return reinterpret_cast<vec3&>(a[4*row]); }

	// casting operator overloading
	inline float& operator[]( unsigned i ){ return a[i]; }
	inline float& operator[]( int i ){ return a[i]; }
	inline const float& operator[]( unsigned i ) const { return a[i]; }
	inline const float& operator[]( int i ) const { return a[i]; }
	inline operator float*(){ return a; }
	inline operator const float*() const { return a; }
	
	// binary operator overloading
	inline vec4 operator*( const vec4& v ){ return vec4( v.dot(rvec4(0)), v.dot(rvec4(1)), v.dot(rvec4(2)), v.dot(rvec4(3)) ); }
	inline vec3 operator*( const vec3& v ){ vec4 v4(v,1); return vec3( v4.dot(rvec4(0)), v4.dot(rvec4(1)), v4.dot(rvec4(2)) ); }
	inline matrix operator*( matrix& M )
	{
		float*b=M.a;
		return matrix(	b[0]*a[0]+b[4]*a[1]+b[8]*a[2]+b[12]*a[3],		b[1]*a[0]+b[5]*a[1]+b[9]*a[2]+b[13]*a[3],		b[2]*a[0]+b[6]*a[1]+b[10]*a[2]+b[14]*a[3],		b[3]*a[0]+b[7]*a[1]+b[11]*a[2]+b[15]*a[3],
						b[0]*a[4]+b[4]*a[5]+b[8]*a[6]+b[12]*a[7],		b[1]*a[4]+b[5]*a[5]+b[9]*a[6]+b[13]*a[7],		b[2]*a[4]+b[6]*a[5]+b[10]*a[6]+b[14]*a[7],		b[3]*a[4]+b[7]*a[5]+b[11]*a[6]+b[15]*a[7],
						b[0]*a[8]+b[4]*a[9]+b[8]*a[10]+b[12]*a[11],		b[1]*a[8]+b[5]*a[9]+b[9]*a[10]+b[13]*a[11],		b[2]*a[8]+b[6]*a[9]+b[10]*a[10]+b[14]*a[11],	b[3]*a[8]+b[7]*a[9]+b[11]*a[10]+b[15]*a[11],
						b[0]*a[12]+b[4]*a[13]+b[8]*a[14]+b[12]*a[15],	b[1]*a[12]+b[5]*a[13]+b[9]*a[14]+b[13]*a[15],	b[2]*a[12]+b[6]*a[13]+b[10]*a[14]+b[14]*a[15],	b[3]*a[12]+b[7]*a[13]+b[11]*a[14]+b[15]*a[15] );
	}

	// determinant
	inline float determinant() const 
	{
		return
		_41*_32*_23*_14 - _31*_42*_23*_14 - _41*_22*_33*_14 + _21*_42*_33*_14 +
		_31*_22*_43*_14 - _21*_32*_43*_14 - _41*_32*_13*_24 + _31*_42*_13*_24 +
		_41*_12*_33*_24 - _11*_42*_33*_24 - _31*_12*_43*_24 + _11*_32*_43*_24 +
		_41*_22*_13*_34 - _21*_42*_13*_34 - _41*_12*_23*_34 + _11*_42*_23*_34 +
		_21*_12*_43*_34 - _11*_22*_43*_34 - _31*_22*_13*_44 + _21*_32*_13*_44 +
		_31*_12*_23*_44 - _11*_32*_23*_44 - _21*_12*_33*_44 + _11*_22*_33*_44 ;
	}

	matrix inverse() const 
	{
		float det=determinant(); if( det==0 ) printf( "matrix::inverse() might be singular.\n" );
		float s=1.0f/det;
		return matrix(	(_32*_43*_24 - _42*_33*_24 + _42*_23*_34 - _22*_43*_34 - _32*_23*_44 + _22*_33*_44)*s,
						(_42*_33*_14 - _32*_43*_14 - _42*_13*_34 + _12*_43*_34 + _32*_13*_44 - _12*_33*_44)*s,
						(_22*_43*_14 - _42*_23*_14 + _42*_13*_24 - _12*_43*_24 - _22*_13*_44 + _12*_23*_44)*s,
						(_32*_23*_14 - _22*_33*_14 - _32*_13*_24 + _12*_33*_24 + _22*_13*_34 - _12*_23*_34)*s,

						(_41*_33*_24 - _31*_43*_24 - _41*_23*_34 + _21*_43*_34 + _31*_23*_44 - _21*_33*_44)*s,
						(_31*_43*_14 - _41*_33*_14 + _41*_13*_34 - _11*_43*_34 - _31*_13*_44 + _11*_33*_44)*s,
						(_41*_23*_14 - _21*_43*_14 - _41*_13*_24 + _11*_43*_24 + _21*_13*_44 - _11*_23*_44)*s,
						(_21*_33*_14 - _31*_23*_14 + _31*_13*_24 - _11*_33*_24 - _21*_13*_34 + _11*_23*_34)*s,

						(_31*_42*_24 - _41*_32*_24 + _41*_22*_34 - _21*_42*_34 - _31*_22*_44 + _21*_32*_44)*s,
						(_41*_32*_14 - _31*_42*_14 - _41*_12*_34 + _11*_42*_34 + _31*_12*_44 - _11*_32*_44)*s,
						(_21*_42*_14 - _41*_22*_14 + _41*_12*_24 - _11*_42*_24 - _21*_12*_44 + _11*_22*_44)*s,
						(_31*_22*_14 - _21*_32*_14 - _31*_12*_24 + _11*_32*_24 + _21*_12*_34 - _11*_22*_34)*s,

						(_41*_32*_23 - _31*_42*_23 - _41*_22*_33 + _21*_42*_33 + _31*_22*_43 - _21*_32*_43)*s,
						(_31*_42*_13 - _41*_32*_13 + _41*_12*_33 - _11*_42*_33 - _31*_12*_43 + _11*_32*_43)*s,
						(_41*_22*_13 - _21*_42*_13 - _41*_12*_23 + _11*_42*_23 + _21*_12*_43 - _11*_22*_43)*s,
						(_21*_32*_13 - _31*_22*_13 + _31*_12*_23 - _11*_32*_23 - _21*_12*_33 + _11*_22*_33)*s );
	}
};

//*******************************************************************
// multiply vertor-matrix
inline vec4 mul(vec4& v, matrix* m){return vec4(v.dot(m->cvec4(0)),v.dot(m->cvec4(1)),v.dot(m->cvec4(2)),v.dot(m->cvec4(3)));}
inline vec4 mul(vec4& v, matrix& m){return mul(v,&m);}
inline vec4 operator*( vec4& v, matrix& m ){ return mul(v,m); }
inline vec4 operator*( vec4& v, matrix* m ){ return mul(v,m); }
inline vec4 mul(matrix* m, vec4& v){return vec4(v.dot(m->rvec4(0)),v.dot(m->rvec4(1)),v.dot(m->rvec4(2)),v.dot(m->rvec4(3)));}
inline vec4 mul(matrix& m, vec4& v){return mul(&m,v);}

//*******************************************************************
inline vec2 operator*( float f, vec2& v ){ return v*f; }
inline vec3 operator*( float f, vec3& v ){ return v*f; }
inline vec4 operator*( float f, vec4& v ){ return v*f; }
inline vec2 operator+( float f, vec2& v ){ return v+f; }
inline vec3 operator+( float f, vec3& v ){ return v+f; }
inline vec4 operator+( float f, vec4& v ){ return v+f; }
inline vec2 operator-( float f, vec2& v ){ return -v+f; }
inline vec3 operator-( float f, vec3& v ){ return -v+f; }
inline vec4 operator-( float f, vec4& v ){ return -v+f; }

//*******************************************************************
// dot product
inline float dot(vec2& v1,vec2& v2){ return v1.dot(v2); }
inline float dot(vec3& v1,vec3& v2){ return v1.dot(v2); }
inline float dot(vec4& v1,vec4& v2){ return v1.dot(v2); }

//*******************************************************************
// utility math functions
inline float deg2rad( float f ){ return float(f*PI/180.0f); }
inline double deg2rad( double f ){ return double(f*PI/180.0); }
inline float rad2deg( float f ){ return float(f*180.0f/PI); }
inline double rad2deg( double f ){ return double(f*180.0/PI); }
inline bool isPowerOfTwo( int i ){ return (i&(i-1))==0; }
inline bool isPowerOfTwo( unsigned i ){ return (i&(i-1))==0; }
inline int nextPowerOfTwo( int n ){ n=n-1; for( int k=1; k<sizeof(int)*CHAR_BIT; k<<=1 ) n=n|n>>k; return n+1; }
inline uint nextPowerOfTwo( uint n ){ return uint(nextPowerOfTwo(int(n))); }
inline int nearestPowerOfTwo( int n ){ n=n-1; for( int k=1; k<sizeof(int)*CHAR_BIT; k<<=1 ) n=n|n>>k; return n+1; }
inline uint nearestPowerOfTwo( uint n ){ return uint(nearestPowerOfTwo(int(n))); }
inline uint getMipLevels( int i ){ uint l=0,s=uint(i); while(s){s=s>>1;l++;} return l; }
inline uint getMipLevels( uint i ){ uint l=0,s=uint(i); while(s){s=s>>1;l++;} return l; }
inline uint getMipmapLevels( int i ){ uint l=0,s=uint(i); while(s){s=s>>1;l++;} return l; }
inline uint getMipmapLevels( uint i ){ uint l=0,s=uint(i); while(s){s=s>>1;l++;} return l; }
inline vec2 abs( const vec2& v ){ return vec2(fabs(v.x),fabs(v.y)); }
inline vec3 abs( const vec3& v ){ return vec3(fabs(v.x),fabs(v.y),fabs(v.z)); }
inline vec4 abs( const vec4& v ){ return vec4(fabs(v.x),fabs(v.y),fabs(v.z),fabs(v.w)); }
inline float frac( float f ){ return float(f-floor(f)); }
inline double frac( double f ){ return double(f-floor(f)); }

//*******************************************************************
// shader-like built-in functions
inline vec2 normalize( vec2& v ){ return v.normalize(); }
inline vec3 normalize( vec3& v ){ return v.normalize(); }
inline vec4 normalize( vec4& v ){ return v.normalize(); }
inline float length( vec2& v ){ return v.length(); }
inline float length( vec3& v ){ return v.length(); }
inline float length( vec4& v ){ return v.length(); }
inline float length2( vec2& v ){ return v.length2(); }
inline float length2( vec3& v ){ return v.length2(); }
inline float length2( vec4& v ){ return v.length2(); }
inline int sign( float f ){ return f>0.0f?1:f<0.0f?-1:0; }
inline ivec2 sign( vec2& v ){ return ivec2(sign(v.x),sign(v.y)); }
inline ivec3 sign( vec3& v ){ return ivec3(sign(v.x),sign(v.y),sign(v.z)); }
inline ivec4 sign( vec4& v ){ return ivec4(sign(v.x),sign(v.y),sign(v.z),sign(v.w)); }

#endif