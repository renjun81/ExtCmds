// VGDimCmd.h
// Created by Zhang Yungui on 14-11-19.
// License: LGPL, https://github.com/rhcad
//

#ifndef __TOUCHVG__VGDimCmd__
#define __TOUCHVG__VGDimCmd__

#include "mgdrawline.h"

//! Example command class to draw text shapes.
class MgCmdDrawExLine : public MgCmdDrawLine
{
public:
    MgCmdDrawExLine() : MgCmdDrawLine(Name()) {}
#ifndef SWIG
    static const char* Name() { return "ex_line"; }
    static MgCommand* Create() { return new MgCmdDrawExLine; }
#endif
    virtual void release() { delete this; }
    virtual bool initialize(const MgMotion* sender, MgStorage* s);
};

#endif // __TOUCHVG__VGDimCmd__
