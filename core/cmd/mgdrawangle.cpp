//
//  mgdrawangle.cpp
//  DemoCmds
//
//  Created by Macbook on 9/9/15.
//  Copyright (c) 2015 Founder. All rights reserved.
//

#include "mgdrawangle.h"
#include "mgshapet.h"
#include "mgangle.h"
#include "mgline.h"
#include "mglines.h"
#include "mglog.h"


#define MIN_EDGE_LENGTH 10.f

MgCmdDrawAngle::MgCmdDrawAngle(const char* name) : MgCommandDraw(name)
{
}

MgCmdDrawAngle::~MgCmdDrawAngle()
{
}

bool MgCmdDrawAngle::initialize(const MgMotion* sender, MgStorage* s)
{
    _head = -1;
    _nCnt = 0;
    
    return _initialize(MgAngle::Type(), sender);
}

bool MgCmdDrawAngle::touchBegan(const MgMotion* sender)
{
    m_step = 1;
    
    Point2d pnt(snapPoint(sender, true));
    MgBaseLines* lines = (MgBaseLines*)dynshape()->shape();
    lines->resize(2);
    
    dynshape()->shape()->setPoint(0, pnt);
    dynshape()->shape()->setPoint(1, pnt);
    dynshape()->shape()->update();
    

    
    return MgCommandDraw::touchBegan(sender);
}

bool MgCmdDrawAngle::touchMoved(const MgMotion* sender)
{
    ignoreStartPoint(sender, m_step-1);
    
    //Point2d pnt = (m_step == 1) ? snapPointWidhOptions(sender, 0) : snapPoint(sender);
    Point2d pnt = (m_step == 1) ? sender->pointM : snapPoint(sender);
    
    MgBaseLines* shp = (MgBaseLines*)dynshape()->shape();
    
    int nPtCacheSize = sizeof(_pts)/sizeof(_pts[0]);
    _head = (_head + 1) % nPtCacheSize;
    //_pts[_head] = Point2d(sender->velocity.x, sender->velocity.y);
    _pts[_head] = pnt;
    _nCnt = (_nCnt < nPtCacheSize) ? _nCnt+1 : nPtCacheSize;
    
    if ( _nCnt >= nPtCacheSize )
    {
        Point2d pt0 , pt1, pt2;
        
        pt0 = pnt;
        pt2 = shp->getPoint(0);
        pt1 = _pts[(_head + 1) % nPtCacheSize];
        
        Vector2d v1(pt0 - pt1);
        Vector2d v2(pt1 - pt2);
        float angle = v1.angleTo(v2);
        
        if ( m_step == 1 && pt0.distanceTo(pt2) > MIN_EDGE_LENGTH && angle >= _M_PI_4 )
        {
            ((MgMotion*)sender)->pointM.set(pt1);
            shp->setPoint(1, snapPointWidhOptions(sender, 0));
            ((MgMotion*)sender)->pointM.set(pnt);
            shp->resize(3);
            m_step++;
        }
    }
    shp->setPoint(m_step, pnt);
    shp->update();
    
    return MgCommandDraw::touchMoved(sender);
}

bool MgCmdDrawAngle::touchEnded(const MgMotion* sender)
{
    MgBaseLines* lines = (MgBaseLines*)dynshape()->shape();
    lines->setClosed(false);
    if (lines->getPointCount() == 3 )
    {
        Point2d pt0 = lines->getPoint(2);
        Point2d pt1 = lines->getPoint(1);
        if ( pt0.distanceTo(pt1) > MIN_EDGE_LENGTH )
            addShape(sender);
    }
    m_step = 0;
    return MgCommandDraw::touchEnded(sender);
}

//bool MgCmdDrawAngle::draw(const MgMotion* sender, GiGraphics* gs)
//{
//    GiContext ctxshap(0, GiColor(0, 0, 255, 128), GiContext::kDashLine);
//    for ( int i = 0; i < POINT_CACHE_SIZE; i++ )
//    {
//        gs->drawCircle(&ctxshap, _pts[i], 0.3);
//
//    }
//    gs->drawLines(&ctxshap, POINT_CACHE_SIZE, _pts);
//    return MgCommandDraw::draw(sender, gs);
//}
