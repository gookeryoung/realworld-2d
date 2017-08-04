#ifndef GLOBAL_MACROS_H
#define GLOBAL_MACROS_H

#include "_global_types.h"

/* For compatible with c++. */
#ifdef __cplusplus
#define GK_BEGIN_HEADER extern "C" {
#define GK_END_HEADER }
#else
#define GK_BEGIN_HEADER
#define GK_END_HEADER
#endif

/* For inline functions, compatiable with both gcc, clang and msvc compilers. */
#define GK_INLINE __inline
#define GK_STATIC_INLINE static __inline

#ifdef UNIX
#define stricmp strcasecmp
#endif
#ifdef WIN32
/* These will cause fatal error, must fix it before use.
 * #define strncpy(dst, src, n) strncpy_s(dst, _countof(dst), src, n)
 * #define strcpy(dst, src) strcpy_s(dst, _countof(dst), src)
 * #define sprintf(dst, format) sprintf_s(dst, _countof(dst), format)
*/
#define stricmp _stricmp
#define strdup _strdup
#endif

/* For disable compiles' warning with unused parameters. */
#ifndef GK_UNUSED_PARAM
#define GK_UNUSED_PARAM(v) (void)(v)
#endif

/* Useful math function macros. */
#define GK_MAX(x, y) ((x)>(y)?(x):(y))
#define GK_MIN(x, y) ((x)<(y)?(x):(y))
#define GK_ROUNDUP(x,n) (((x)+((n)-1))&(~((n)-1)))
#define GK_ROUNDUP_INT(x) GKROUNDUP(x, sizeof(int))
#define GK_ROUND(val) (int)((val*100+50)/100)

/* Keep a number in a certain range, ensured it to be in range of lower
 * and upper borders. */
#define GK_BOUND(value,lower,upper) (value)=GK_MIN(GK_MAX((value),(lower)),(upper))

/* Get a random integer. */
GK_STATIC_INLINE gint32 GK_RANDOM_INT(int from, int range)
{
#ifndef __GK_SRAND__    /* Ensure initialize seed only once. */
#define __GK_SRAND__
    srand((gint32)time(NULL));
#endif // __GK_SRAND__
    return (from + (gint32)((gfloat)(range + 1) * (rand() / (RAND_MAX + (gfloat)(from)))));
}

/* Get a random float number. */
#define GK_RANDOM_FLOAT(from, range) \
    (gfloat)((gfloat)from+((gfloat)(range+1)*(rand()/(RAND_MAX+(gfloat)from))))

/* Test if a float or double number equals to zero in its accuracy. */
GK_STATIC_INLINE gbool GK_FLOAT_ISNULL(gfloat f)
{ union { gfloat f; guint32 u; } val; val.f = f; return ((val.u == 0u) ? GKTRUE : GKFALSE); }

GK_STATIC_INLINE gbool GK_DOUBLE_ISNULL(gdouble d)
{ union { gdouble d; guint64 u; } val; val.d = d; return (val.u == (guint64)0 ? GKTRUE : GKFALSE);}

/* Test if two float or double numbers is equal in their accuracy. */
GK_STATIC_INLINE gbool GK_FLOAT_EQUAL(gfloat val1, gfloat val2)
{ return (GK_FLOAT_ISNULL(val1 - val2) ? GKTRUE : GKFALSE); }

GK_STATIC_INLINE gbool GK_DOUBLE_EQUAL(gdouble val1, gdouble val2)
{ return (GK_DOUBLE_ISNULL(val1 - val2) ? GKTRUE : GKFALSE); }

/* For geometry calulations */
#define GK_LENGTH(x1,x2) ((x2)-(x1))
#define GK_LENGTH_POW(x1,x2) (((x2)-(x1))*((x2)-(x1)))
#define GK_DISTANCE(x1,y1,x2,y2) (sqrt(GK_LENGTH_POW(x1,x2)+GK_LENGTH_POW(y1,y2)))

/* For assertions and message output. */
#define GK_ASSERT assert
#define GK_REQUIRE(val,format,...) do{\
    if(val) break;\
    fprintf(stderr,"Assertion failed at [%d] in [%s].\n",__LINE__,__FILE__);\
    fprintf(stderr,"Message: ");\
    fprintf(stderr,(format),##__VA_ARGS__);\
    fprintf(stderr,"\n");\
    exit(EXIT_FAILURE);\
    }while(0)

#define GK_CHECK(val,format,...) do{\
    if(val) break;\
    fprintf(stdout,"Check failed at [%d] in [%s].\n",__LINE__,__FILE__);\
    fprintf(stderr,"Message: ");\
    fprintf(stderr,(format),##__VA_ARGS__);\
    fprintf(stderr,"\n");\
    }while(0)

#define GK_MSG(format,...) do{\
    fprintf(stdout,"Message [");\
    fprintf(stdout,(format),##__VA_ARGS__);\
    fprintf(stdout,"]\nFile [%s], line [%d]\n",__FILE__,__LINE__);\
    }while(0)

#define GK_WARNING(format,...) do{\
    fprintf(stderr,(format),##__VA_ARGS__);\
    fprintf(stdout, "File [%s], line [%d]\n",__FILE__,__LINE__);\
    }while(0)

#define GK_RUN_TEST(func) do{\
    fprintf(stdout, "Run function -----###["#func"]###-----\n");\
    func();\
    fprintf(stdout, "Finished     -----###["#func"]###-----\n");\
    } while(0)

/* Exit out of the application without any clean up.
 * You should use this only if there is a irresolvable situation. */
#define GK_BAILOUT(format, ...) do{\
    fprintf(stderr,(format),##__VA_ARGS__);\
    fprintf(stdout, "File %s at line %d\n", __FILE__, __LINE__); \
    exit(EXIT_FAILURE);\
    } while (0)

#endif // GLOBAL_MACROS_H
