#ifndef GLOBAL_MEMORY_H
#define GLOBAL_MEMORY_H

#include "_global_macros.h"

/* For memory allcations and deallocations. */
#ifdef GK_USE_GC
#include "memory_alloc.h"           /* Using garbage collector */
#define MALLOC GK_malloc
#define REALLOC GK_realloc
#define FREE GK_Free
#else                               /* No GC, use built-in functions. */
//#include <Python.h>
//#define __MALLOC PyMem_Malloc
//#define __REALLOC PyMem_Realloc
//#define __FREE PyMem_Free
#include <Python.h>
#define __MALLOC malloc
#define __REALLOC realloc
#define __FREE free
#endif

#if defined(_MSC_VER)
#include <malloc.h>
#define GK_ALLOC_ARRAY(type,name,size) type* name=(type*)_alloca((size)*sizeof(type))
#else
#define GK_ALLOC_ARRAY(type,name,size) type name[size]
#endif

#define GK_MALLOC(target,type,amount)do{\
    (target)=(type*)__MALLOC(((amount)+1)*sizeof(type));\
    if((amount)<=0)GK_BAILOUT("%s","Must allocate at least 1 byte of ram.\n");\
    if((target)==NULL){\
    GK_BAILOUT("Could not allocate %d bytes of ram.\n",(int)((amount)*sizeof(type)));\
    }\
    memset(target,0,((amount)*sizeof(type)));\
    printf("Allocate %d bytes of ram at 0x%p for ["#target"](instance of ["#type"]).\n",(int)((amount)*sizeof(type)),target);\
    }while(0)

#define GK_MALLOC_SIZE(target,type,size) do{\
    (target)=(type*)__MALLOC(size);\
    if((target)==NULL)GK_BAILOUT("Could not allocate %d bytes of ram.\n",(size));\
    memset(target,0,(size));\
    printf("Allocate 0x%p for ["#target"](instance of ["#type"]).\n", (target));\
    }while(0)

#define GK_MALLOC_NOINIT(target,type,amount) do{\
    (target)=(type*)__MALLOC((amount+1)*sizeof(type));\
    if((target)==NULL){\
    GK_BAILOUT("Could not allocate %d bytes of ram.\n",(int)((amount)*sizeof(type)));\
    }\
    printf("Allocate 0x%p for ["#target"](instance of ["#type"]).\n",target);\
    } while (0)

GK_STATIC_INLINE void GK_DELETE(void *target)
{ GK_REQUIRE(target, "Null pointer deleted."); printf("Delete ram at 0x%p.\n", target); __FREE(target); target=NULL; }

GK_STATIC_INLINE void GK_MEMSET(void *target, guint32 size)
{ printf("Clear ram at 0x%p.\n", target); memset(target, 0, (size)); }

GK_STATIC_INLINE void GK_DELETE_NORESET(void *target)
{ GK_REQUIRE(target, "Null pointer deleted."); printf("Delete ram at 0x%p.\n", target); __FREE(target); }

/* Resize allocated ram. */
#define GK_REALLOC(target,type,amount) do {\
    (target)=__REALLOC((target),sizeof(type)*(amount+1));\
    if(target==NULL){\
    GK_BAILOUT("Could not allocate %d bytes of ram.\n",(int)((amount)*sizeof(type)));\
    }\
    memset(target,0,amount*sizeof(type));\
    printf("Reallocate 0x%p for ["#target"](instance of ["#type"]).\n",(target));\
    } while (0)

/* Resize allocated ram. */
#define GK_REALLOC_SIZE(target,type,size) do {\
    (target)=__REALLOC((target),size);\
    if(target==NULL)GK_BAILOUT("Could not allocate %d bytes of ram.\n",(int)(size));\
    memset(target,0,size);\
    printf("Reallocate 0x%p for ["#target"](instance of ["#type"])\n", (target));\
    } while (0)

#define GK_MEMCPY(dst,src,size) do{\
    memcpy(dst,src,size);\
    printf("Copy memory from ["#src"] at 0x%p to ["#dst"] at 0x%p.\n",src,dst);\
    }while(0)

#define GK_STRCPY(dst,src) do{\
    strcpy(dst,src);\
    printf("Copy string from ["#src"] at 0x%p to ["#dst"] at 0x%p.\n",src,dst);\
    }while(0)

#define GK_MEMMOVE(dst,src,size) do{\
    memmove(dst,src,size);\
    printf("Move memory from ["#src"] at 0x%p to ["#dst"] at 0x%p.\n",src,dst);\
    }while(0)

/* Create one instance of a object. */
#define GK_NEW(target,type) do{\
    GK_MALLOC(target,type,1);\
    }while(0)

#endif // GLOBAL_MEMORY_H
