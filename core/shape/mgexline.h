// VGDimExample.h
// Created by Zhang Yungui on 14-11-19.
// License: LGPL, https://github.com/rhcad
//

#ifndef __TOUCHVG__MgExLine__
#define __TOUCHVG__MgExLine__

#include "mgline.h"
#include "mgshape.h"

//! Example shape class with text.
class MgExLine : public MgLine
{
    MG_INHERIT_CREATE(MgExLine, MgLine, 51)
public:
    
protected:
    void _output(MgPath& path) const {}
    
    int _getHandleCount() const { return 2; }
    bool _draw(int mode, GiGraphics& gs, const GiContext& ctx, int segment) const;
    
    //Box2d _getExtent() const;
    //float _hitTest(const Point2d& pt, float tol, MgHitResult& res) const;
};

#endif // __TOUCHVG__MgExLine__
