#pragma once
#ifndef _EXPORT_H
#define _EXPORT_H

#pragma warning(disable : 4251)
#pragma warning(disable : 4275)

#ifdef OPENSANDBOX_EXPORT
#define API_OPENSANDBOX __declspec(dllexport)
#else
#define API_OPENSANDBOX __declspec(dllimport)
#endif // OPENSANDBOX_EXPORT

#endif // _EXPORT_H