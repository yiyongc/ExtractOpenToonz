#pragma once

#ifndef STAGE_INCLUDED
#define STAGE_INCLUDED

#include "../timage.h"
#include "../trastercm.h"
#include "../tgl.h"

#undef DVAPI
#undef DVVAR
#ifdef TOONZLIB_EXPORTS
#define DVAPI DV_EXPORT_API
#define DVVAR DV_EXPORT_VAR
#else
#define DVAPI DV_IMPORT_API
#define DVVAR DV_IMPORT_VAR
#endif

//=============================================================================
// forward declarations
class ToonzScene;
class TXsheet;
class TXshSimpleLevel;
class TXshLevel;
class TFrameId;
class TFlash;
class OnionSkinMask;
class TFx;
class TXshColumn;
class TVectorImage;
class TRasterImage;
class TToonzImage;
class QPainter;
class QPolygon;
class QMatrix;
//=============================================================================

//=============================================================================
// Stage namespace

namespace Stage {
//=============================================================================

extern const double inch;
extern const double standardDpi;

class Visitor;
struct VisitArgs;

//=============================================================================
// Player

//=============================================================================
// Visitor

//-----------------------------------------------------------------------------

void visit(Visitor &visitor, const VisitArgs &args);

//-----------------------------------------------------------------------------

void visit(Visitor &visitor, ToonzScene *scene, TXsheet *xsh, int row);

//-----------------------------------------------------------------------------

void visit(Visitor &visitor, TXshSimpleLevel *level, const TFrameId &fid,
                 const OnionSkinMask &osm, bool isPlaying);

//-----------------------------------------------------------------------------

void visit(Visitor &visitor, TXshLevel *level, const TFrameId &fid,
                 const OnionSkinMask &osm, bool isPlaying);

//-----------------------------------------------------------------------------
}  // namespace Stage
//=============================================================================

const int c_noOnionSkin = -123238796;

#endif
