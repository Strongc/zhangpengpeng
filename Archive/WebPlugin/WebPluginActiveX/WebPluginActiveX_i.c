

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Sat Mar 21 14:58:49 2015
 */
/* Compiler settings for .\WebPluginActiveX.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_WebPluginActiveXLib,0x7279F726,0x4F7F,0x4F25,0xA8,0xB0,0x18,0x4B,0x5C,0x26,0x05,0x91);


MIDL_DEFINE_GUID(IID, DIID__DWebPluginActiveX,0x699825D2,0x88F3,0x4159,0x8B,0x1D,0x3F,0x64,0xE8,0x5F,0x61,0x29);


MIDL_DEFINE_GUID(IID, DIID__DWebPluginActiveXEvents,0x6CDB8D17,0xA795,0x4F69,0xAE,0x2D,0x1C,0x55,0x99,0x1E,0x71,0xE0);


MIDL_DEFINE_GUID(CLSID, CLSID_WebPluginActiveX,0x769E0ED3,0xA72E,0x465A,0xB8,0xCB,0xD4,0xAE,0x45,0xD6,0x9F,0x0D);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



