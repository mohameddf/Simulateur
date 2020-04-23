#ifndef VRESWIDGET_H
#define VRESWIDGET_H

#include "VWidget.h"
#include "../core/ValveRes.h"

class VResWidget : public VWidget {
private:

    ValveRes * vres;
public:
    VResWidget(MainGui *,ValveRes *);
    ~VResWidget();
    void showInfos() override;
};

#endif
