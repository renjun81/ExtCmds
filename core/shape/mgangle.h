//
//  mgangle.h
//  DemoCmds
//
//  Created by Macbook on 9/9/15.
//  Copyright (c) 2015 Founder. All rights reserved.
//

#ifndef DemoCmds_mgangle_h
#define DemoCmds_mgangle_h

#include "mglines.h"
#include "mgshape.h"

class MgAngle : public MgBaseLines
{
    MG_INHERIT_CREATE(MgAngle, MgBaseLines, 52)
public:
    
protected:
    void _output(MgPath& path) const{}
    
    bool _draw(int mode, GiGraphics& gs, const GiContext& ctx, int segment) const;
};


#endif
