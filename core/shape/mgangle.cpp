//
//  mgangle.cpp
//  DemoCmds
//
//  Created by Macbook on 9/9/15.
//  Copyright (c) 2015 Founder. All rights reserved.
//

#include "mgangle.h"
#include "mgshape_.h"
#include <sstream>
#include "mgline.h"
#include "mglog.h"


MG_IMPLEMENT_CREATE(MgAngle)

MgAngle::MgAngle(){}
MgAngle::~MgAngle(){}

bool MgAngle::_draw(int mode, GiGraphics& gs, const GiContext& ctx, int segment) const
{
    float textHeight = 5.f;
    float radiusForText = 15.f;
    
    bool bRet = false;
    if ( getPointCount() == 3 )
    {
        Point2d p1 = getPoint(0);
        Point2d p0 = getPoint(1);
        Point2d p2 = getPoint(2);
        
        MgPath path;
        path.moveTo(p1);
        path.lineTo(p0);
        path.lineTo(p2);
        bRet = gs.drawPath(&ctx, path, mode == 0);
        
        GiContext context(ctx);
        context.setLineStyle(GiContext::kDashLine);
        
        float startAngle = (p1-p0).angle2();
        float endAngle = (p2-p0).angle2();
        float swipeAngle = endAngle - startAngle;
        
        if ( startAngle < 0 )
        {
            if ( swipeAngle > _M_PI )
                swipeAngle = swipeAngle - 2*_M_PI;
            else if ( swipeAngle < -_M_PI )
                swipeAngle = 2*_M_PI + swipeAngle;
        }
        if ( endAngle < 0 )
        {
            if ( swipeAngle > _M_PI )
                swipeAngle -= _M_PI;
            else if ( swipeAngle < -M_PI )
                swipeAngle = 2*_M_PI + swipeAngle;
        }
        
        std::stringstream ss;
        ss << mgbase::roundReal(mgbase::rad2Deg(fabsf(swipeAngle)), 1) << "°";
        
        float smallEdgeLen = mgMin((p1-p0).length(), (p2-p0).length());
        float minRadiusForText = (textHeight + 2)/(2*sin(fabsf(swipeAngle)/2.f));
        float alpha = startAngle + swipeAngle/2;
        Point2d pt = p0;
        
        if ( minRadiusForText > radiusForText )   // draw text and arc in the angle
        {
            pt.offset(minRadiusForText * cos(alpha), minRadiusForText * sin(alpha));
            gs.drawTextAt(ctx.getLineARGB(), ss.str().c_str(), pt, textHeight,
                          GiGraphics::kAlignCenter|GiGraphics::kAlignVCenter,
                          mgbase::toRange(alpha, _MGZERO - _M_PI_2, _MGZERO + _M_PI_2) );
            
            if ( smallEdgeLen > radiusForText * 2 )
                gs.drawArc(&context, p0, radiusForText, radiusForText, startAngle, swipeAngle);
            else
                gs.drawArc(&context, p0, smallEdgeLen * 2, smallEdgeLen * 2, startAngle, swipeAngle);
        }
        else
        {
            pt.offset(radiusForText * cos(alpha), radiusForText * sin(alpha));
            gs.drawTextAt(ctx.getLineARGB(), ss.str().c_str(), pt, textHeight,
                          GiGraphics::kAlignCenter|GiGraphics::kAlignVCenter,
                          mgbase::toRange(alpha, _MGZERO - _M_PI_2, _MGZERO + _M_PI_2));
            
            float angleGap = asin((textHeight+1.f)/(2*radiusForText));
            
            if ( smallEdgeLen > radiusForText * 2 )
            {
                gs.drawArc(&context, p0, radiusForText, radiusForText, startAngle, swipeAngle/2 - mgSign(swipeAngle) * angleGap);
                
                gs.drawArc(&context, p0, radiusForText, radiusForText, endAngle, -(swipeAngle/2 - mgSign(swipeAngle) * angleGap));
            }
            else
                gs.drawArc(&context, p0, smallEdgeLen/2, smallEdgeLen/2, startAngle, swipeAngle);

        }
    }
    else
        bRet = gs.drawLine(&ctx, _getPoint(0), _getPoint(1));
    
    return bRet;
}
