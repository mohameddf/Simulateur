#ifndef VMRWIDGET_H
#define VMRWIDGET_H

#include "VWidget.h"
#include "../core/ValveMR.h"

class VMRWidget : public VWidget {
private:
    ValveMr * vmr;
public:
    VMRWidget(MainGui *, ValveMr *);
    ~VMRWidget();
    void showInfos() override;
};

#endif
