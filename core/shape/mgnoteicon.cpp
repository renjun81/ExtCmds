//
//  MgNoteIcon.cpp
//  ExtCmds
//
//  Created by Macbook on 9/16/15.
//  Copyright (c) 2015 Founder. All rights reserved.
//

#include "mgnoteicon.h"
#include "mgshape_.h"
#include "gicontxt.h"
#include "gigraph.h"

MG_IMPLEMENT_CREATE(MgNoteIcon)

MgNoteIcon::MgNoteIcon()
{
}

MgNoteIcon::~MgNoteIcon()
{
}

int MgNoteIcon::_getPointCount() const
{
    return 1;
}

Point2d MgNoteIcon::_getPoint(int) const
{
    return _point;
}

void MgNoteIcon::_setPoint(int, const Point2d& pt)
{
    _point = pt;
}

void MgNoteIcon::_copy(const MgNoteIcon& src)
{
#if defined(_MSC_VER) && _MSC_VER >= 1400 // VC8
    strcpy_s(_iconName, sizeof(_iconName), src._iconName);
#else
    strcpy(_iconName, src._iconName);
#endif
    _point = src._point;
    _size = src._size;
    __super::_copy(src);
}

bool MgNoteIcon::_equals(const MgNoteIcon& src) const
{
    return (_point == src._point && (strcmp(_iconName, src._iconName) == 0) && __super::_equals(src));
}

void MgNoteIcon::_transform(const Matrix2d& mat)
{
    _point *= mat;
    __super::_transform(mat);
}

void MgNoteIcon::_clear()
{
    _point = Point2d::kOrigin();
    __super::_clear();
}

void MgNoteIcon::_update()
{
    _extent.set(_point, _size.x, _size.y);
    __super::_update();
}

float MgNoteIcon::_hitTest(const Point2d& pt, float tol, MgHitResult& res) const
{
    Point2d points[4] = { _extent.leftTop(), _extent.rightTop(), _extent.rightBottom(), _extent.leftBottom() };
    return linesHit(4, points, true, pt, tol*1.5, res);
}

bool MgNoteIcon::_hitTestBox(const Box2d& rect) const
{
    return rect.contains(_point);
}

bool MgNoteIcon::_save(MgStorage* s) const
{
    bool ret = __super::_save(s);
    
    s->writeFloat("x", _point.x);
    s->writeFloat("y", _point.y);
    
    s->writeFloat("width", _size.x);
    s->writeFloat("height", _size.y);
    return ret;
}

bool MgNoteIcon::_load(MgShapeFactory* factory, MgStorage* s)
{
    bool ret = __super::_load(factory, s);
    
    const char* szIcon = _options.getOptionString("icon");
    
    setIconName(szIcon);
    
//    len = s->readString("text");
//    _text.resize(len);
//    if (len > 0 && ret) {
//        ret = s->readString("text", &_text[0], len) == len;
//    }
    
    _size.set(s->readFloat("width", 0), s->readFloat("height", 0));
    if (_size.x < 1 || _size.y < 1)
        _size.x = _size.y = 4.f;
    
    _point.set(s->readFloat("x", _point.x), s->readFloat("y", _point.y));
    
    return ret;
}

void MgNoteIcon::setIconName(const char* iconName)
{
    int len = sizeof(_iconName) - 1;
    if( len < 0 ) return;
    
#if defined(_MSC_VER) && _MSC_VER >= 1400 // VC8
    strncpy_s(_iconName, sizeof(_iconName), iconName, len);
#else
    strncpy(_iconName, iconName, len);
#endif
    _iconName[len] = 0;
    
    _options.setOptionString("icon", _iconName);
}

bool MgNoteIcon::_draw(int, GiGraphics& gs, const GiContext& ctx, int) const
{
    return (gs.drawImage(_iconName, _point, _size.x, _size.y, 0) || drawBox(gs, ctx));
}

bool MgNoteIcon::drawBox(GiGraphics& gs, const GiContext& ctx) const
{
    GiContext tmpctx(ctx);
    tmpctx.setNoFillColor();
    tmpctx.setLineStyle(GiContext::kSolidLine);
    
    GiContext ctxline(tmpctx);
    ctxline.setLineWidth(0, false);
    
    Box2d rect(_point, _size.x, _size.y);
    return (true // gs.drawPolygon(&tmpctx, 4, _points)
            && gs.drawLine(&ctxline, rect.leftTop(), rect.rightBottom())
            && gs.drawLine(&ctxline, rect.leftBottom(), rect.rightTop()));
}
