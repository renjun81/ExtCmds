// MgExLine.cpp
// Created by Zhang Yungui on 14-11-19.
// License: LGPL, https://github.com/rhcad
//

#include "mglog.h"
#include "mgexline.h"
#include "mgshape_.h"
#include <sstream>

MG_IMPLEMENT_CREATE(MgExLine)

MgExLine::MgExLine(){}
MgExLine::~MgExLine(){}

bool MgExLine::_draw(int mode, GiGraphics& gs, const GiContext& ctx, int segment) const
{
    float textHeight = 5.f;
    
    float alpha = angle();
    float len = length();
    
    Point2d p0 = getPoint(0);
    Point2d p1 = getPoint(1);
    Point2d pc = center();
    
    int nTextCount = 0;
    float paramLength = extrasc()->getOptionFloat("length", 0.f);
    const char* text = extrasc()->getOptionString("text");
    const char* szUnit = extrasc()->getOptionString("unit");
    
    if ( paramLength > 0 ) nTextCount++;
    if ( strlen(text) > 0 ) nTextCount++;
    
    std::stringstream ss;
    if ( paramLength > 0 )
        ss << paramLength << szUnit;
    else
        ss << text << szUnit;
    text = ss.str().c_str();
    
    const char *curText;
    float textWidth, r;
    if ( nTextCount == 1 )
    {
        curText = (paramLength > 0) ? ss.str().c_str() : text;
        
        textWidth = gs.calcTextWidth(curText, textHeight);
        
        if ( len > textWidth + 4 )
        {
            // show length on center of line
            Point2d pc0 = pc, pc1 = pc;
            
            r = textWidth/2 + 0.5;
            pc0.offset(- r * cos(alpha), - r * sin(alpha));
            pc1.offset(r * cos(alpha), r * sin(alpha));
            
            MgPath path;
            GiContext ctx1(ctx);
            ctx1.setEndArrayHead(GiContext::kArrowNone);
            path.moveTo(p0); path.lineTo(pc0);
            gs.drawPath(&ctx1, path, mode == 0);
            
            ctx1.setEndArrayHead(ctx.getEndArrayHead());
            ctx1.setStartArrayHead(GiContext::kArrowNone);
            path.clear(); path.moveTo(pc1); path.lineTo(p1);
            gs.drawPath(&ctx1, path, mode == 0);
            
            alpha = mgbase::toRange(alpha, _MGZERO - _M_PI_2, _MGZERO + _M_PI_2);
        }
        else
        {
            MgPath path;
            path.moveTo(p0);
            path.lineTo(p1);
            gs.drawPath(&ctx, path, mode == 0);
            
            r = (textHeight + 1)/2;
            alpha = mgbase::toRange(alpha, _MGZERO - _M_PI_2, _MGZERO + _M_PI_2);
            // put length text under the line
            pc.offset(r * sin(alpha), - r * cos(alpha));
        }
        
        gs.drawTextAt(ctx.getLineARGB(), curText, pc, textHeight, GiGraphics::kAlignCenter|GiGraphics::kAlignVCenter, alpha);
    }
    else
    {
        MgPath path;
        path.moveTo(p0);
        path.lineTo(p1);
        gs.drawPath(&ctx, path, mode == 0);
        
        if ( nTextCount == 2 )
        {
            alpha = mgbase::toRange(alpha, _MGZERO - _M_PI_2, _MGZERO + _M_PI_2);
            
            curText = ss.str().c_str();
            textWidth = gs.calcTextWidth(curText, textHeight);
            r = (textHeight + 1)/2;
            
            // put length text over the line
            pc.offset(-r * sin(alpha), + r * cos(alpha));
            gs.drawTextAt(ctx.getLineARGB(), curText, pc, textHeight, GiGraphics::kAlignCenter|GiGraphics::kAlignVCenter, alpha);
            
            curText = text;
            textWidth = gs.calcTextWidth(curText, textHeight);
            r = (textHeight + 1)/2;
            // put description text below the line
            pc = center();
            pc.offset(r * sin(alpha), - r * cos(alpha));
            gs.drawTextAt(ctx.getLineARGB(), curText, pc, textHeight, GiGraphics::kAlignCenter|GiGraphics::kAlignVCenter, alpha);
        }
    }

    return true;
}

/*
Box2d MgExLine::_getExtent() const
{
    Box2d rect = __super::_getExtent();
    
    int nNoteCount = getNoteCount();
    for ( int i = 0; i < nNoteCount; i++ )
    {
        rect.unionWith(getNoteIconRect(i));
    }
    
    return rect;
}

float MgExLine::_hitTest(const Point2d& pt, float tol, MgHitResult& res) const
{
    float dist = __super::_hitTest(pt, tol, res);
    
    res.isnote = false;
    res.noteId = -1;
    
    int nNoteCount = getNoteCount();
    for ( int i = 0; i < nNoteCount; i++ )
    {
        if ( getNoteIconRect(i).contains(pt) )
        {
            res.isnote = true;
            res.noteId = i;
            dist = 0;  // means hit the note icon
            break;
        }
    }
    
    return dist;
}
*/