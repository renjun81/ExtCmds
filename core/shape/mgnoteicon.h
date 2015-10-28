//
//  mgicon.h
//  ExtCmds
//
//  Created by Macbook on 9/16/15.
//  Copyright (c) 2015 Founder. All rights reserved.
//

#ifndef __ExtCmds__mgicon__
#define __ExtCmds__mgicon__

#include "mgbasesp.h"

//! 点图形类
/*! \ingroup CORE_SHAPE
 */
class MgNoteIcon : public MgBaseShape
{
    MG_DECLARE_CREATE(MgNoteIcon, MgBaseShape, 53)
public:

#ifndef SWIG
    const char* getIconName() const { return _iconName; }
#endif
    void setIconName(const char* iconName);
    
    Vector2d getIconSize() const { return _size; }
    void setIconSize(Vector2d size)
    {
        _size = size;
        if (_size.x < 1 || _size.y < 1)
            _size.x = _size.y = 4.f;
    }
    
protected:
    bool _isClosed() const { return true; }
    void _output(MgPath& path) const {};
    
    bool _save(MgStorage* s) const;
    bool _load(MgShapeFactory* factory, MgStorage* s);
    bool _draw(int mode, GiGraphics& gs, const GiContext& ctx, int segment) const;
    
    bool _hitTestBox(const Box2d& rect) const;

private:
    bool drawBox(GiGraphics& gs, const GiContext& ctx) const;
    
private:
    Point2d _point;
    Vector2d _size;
    char    _iconName[64];
};

#endif /* defined(__ExtCmds__mgicon__) */
