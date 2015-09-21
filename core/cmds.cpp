// cmds.cpp
#include "cmds.h"
#include "cmdsubject.h"
#include "mgspfactory.h"
#include "mgshapet.h"

#include "mgexline.h"
#include "mgdrawexline.h"

#include "mgangle.h"
#include "mgdrawangle.h"

#include "mgnoteicon.h"
#include "mgdrawnoteicon.h"

void ExtCmds::registerExtendCmds(long mgView)
{
    MgView* view = MgView::fromHandle(mgView);
    
    MgShapeT<MgExLine>::registerCreator(view->getShapeFactory());
    mgRegisterCommand<MgCmdDrawExLine>(view);
    
    MgShapeT<MgAngle>::registerCreator(view->getShapeFactory());
    mgRegisterCommand<MgCmdDrawAngle>(view);
    
    MgShapeT<MgNoteIcon>::registerCreator(view->getShapeFactory());
    mgRegisterCommand<MgCmdDrawNoteIcon>(view);
}