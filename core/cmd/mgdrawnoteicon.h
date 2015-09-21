//
//  mgdrawicon.h
//  ExtCmds
//
//  Created by Macbook on 9/16/15.
//  Copyright (c) 2015 Founder. All rights reserved.
//

#ifndef __ExtCmds__mgdrawicon__
#define __ExtCmds__mgdrawicon__

#include "mgcmddraw.h"

class MgCmdDrawNoteIcon : public MgCommandDraw
{
public:
    MgCmdDrawNoteIcon(const char* name = Name()) : MgCommandDraw(name) {}
#ifndef SWIG
    static const char* Name() { return "note_icon"; }
    static MgCommand* Create() { return new MgCmdDrawNoteIcon; }
#endif
    virtual void release() { delete this; }
    virtual bool initialize(const MgMotion* sender, MgStorage* s);
    virtual bool click(const MgMotion* sender);
    virtual bool touchBegan(const MgMotion* sender);
    virtual bool touchMoved(const MgMotion* sender);
    virtual bool touchEnded(const MgMotion* sender);
};

#endif /* defined(__ExtCmds__mgdrawicon__) */
