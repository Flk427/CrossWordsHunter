#ifndef GUIHELPERS_H
#define GUIHELPERS_H

#include "gui/MainWindow.h"
#include "core/thread/BaseThreadBody.h"

class GuiHelpers
{
public:
	GuiHelpers();
};

void createSearchProgressBarWidget(MainWindow* owner, BaseThreadBody* treadBody);

#endif // GUIHELPERS_H
