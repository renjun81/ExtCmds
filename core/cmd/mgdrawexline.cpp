// VGDimCmd.cpp
// Created by Zhang Yungui on 14-11-19.
// License: LGPL, https://github.com/rhcad
//

#include "mgexline.h"
#include "mgdrawexline.h"

bool MgCmdDrawExLine::initialize(const MgMotion* sender, MgStorage* s)
{
    return _initialize(MgExLine::Type(), sender, s);
}
