#ifndef BACKBONE_API_PREPROCESSOR_H
#define BACKBONE_API_PREPROCESSOR_H

#ifdef BACKBONEAPI_EXPORT
#define BACKBONEAPI_USAGE __declspec(dllexport)
#else
#define BACKBONEAPI_USAGE __declspec(dllimport)
#endif

#endif