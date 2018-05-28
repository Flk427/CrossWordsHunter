#ifndef GUIHELPERS_H
#define GUIHELPERS_H

#include "gui/MainWindow.h"
#include "core/thread/BaseTreadBody.h"

class GuiHelpers
{
public:
	GuiHelpers();
};

void createSearchProgressBarWidget(MainWindow* owner, BaseTreadBody* treadBody);

#endif // GUIHELPERS_H
