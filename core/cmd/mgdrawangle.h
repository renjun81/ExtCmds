//
//  mgdrawangle.h
//  DemoCmds
//
//  Created by Macbook on 9/9/15.
//  Copyright (c) 2015 Founder. All rights reserved.
//

#ifndef __DemoCmds__mgdrawangle__
#define __DemoCmds__mgdrawangle__

#include "mgcmddraw.h"

class MgCmdDrawAngle : public MgCommandDraw
{
public:
    MgCmdDrawAngle(const char* name = Name());
    virtual ~MgCmdDrawAngle();
#ifndef SWIG
    static const char* Name() { return "angle"; }
    static MgCommand* Create() { return new MgCmdDrawAngle; }
#endif
    virtual void release() { delete this; }
    virtual bool initialize(const MgMotion* sender, MgStorage* s);
    virtual bool touchBegan(const MgMotion* sender);
    virtual bool touchMoved(const MgMotion* sender);
    virtual bool touchEnded(const MgMotion* sender);
    
    //virtual bool draw(const MgMotion* sender, GiGraphics* gs);
    
private:
    Point2d _pts[2];
    int _head;
    int _nCnt;
};

#endif /* defined(__DemoCmds__mgdrawangle__) */
