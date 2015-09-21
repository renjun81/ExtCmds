//
//  mgdrawicon.cpp
//  ExtCmds
//
//  Created by Macbook on 9/16/15.
//  Copyright (c) 2015 Founder. All rights reserved.
//

#include "mgdrawnoteicon.h"
#include "mgnoteicon.h"
#include "mgstorage.h"

bool MgCmdDrawNoteIcon::initialize(const MgMotion* sender, MgStorage* s)
{
    _initialize(MgNoteIcon::Type(), sender);
    
    if (s)
    {
        char szIcon[64];
        int len = sizeof(szIcon) - 1;
        len = s->readString("icon", szIcon, len);
        szIcon[len] = 0;
        
        ((MgNoteIcon*)dynshape()->shape())->setIconName(szIcon);
        
        Box2d rect(0.f, 0.f, s->readFloat("width", 0), s->readFloat("height", 0));
        rect *= sender->view->xform()->displayToModel();
    
        ((MgNoteIcon*)dynshape()->shape())->setIconSize(Vector2d(rect.width(), rect.height()));
    }
    
    return _initialize(0, sender, s);
}

bool MgCmdDrawNoteIcon::click(const MgMotion* sender)
{
    return touchBegan(sender) && touchEnded(sender);
}

bool MgCmdDrawNoteIcon::touchBegan(const MgMotion* sender)
{
    m_step = 1;
    dynshape()->shape()->setPoint(0, snapPoint(sender, true));
    dynshape()->shape()->update();
    
    return MgCommandDraw::touchBegan(sender);
}

bool MgCmdDrawNoteIcon::touchMoved(const MgMotion* sender)
{
    dynshape()->shape()->setPoint(0, snapPoint(sender));
    dynshape()->shape()->update();
    
    return MgCommandDraw::touchMoved(sender);
}

bool MgCmdDrawNoteIcon::touchEnded(const MgMotion* sender)
{
    addShape(sender);
    m_step = 0;
    
    sender->view->toSelectCommand();
    
    return MgCommandDraw::touchEnded(sender);
}