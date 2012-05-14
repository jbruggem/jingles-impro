
#ifndef BASICUI_H_
#define BASICUI_H_

#include <QMainWindow>
#include "QsLog.h"
#include "mainwidget.h"
#include "workspace.h"
#include "uicontroller.h"

class BasicUi: public QMainWindow {

    Q_OBJECT

    public:
        BasicUi(UiController * controller, QWidget *parent = 0);
        void setWorkspace(Workspace *);
        void setUiController(UiController *);
        ~BasicUi(){
            if(NULL != mainWidget)
                delete mainWidget;
        }

    private:
        MainWidget *mainWidget;
        // QGridLayout  *layout;
        // QPushButton  *editModeButton;
        // EditWidget  *editWidget;
        // PlayWidget  *playWidget;
        // bool editMode;
        // Workspace *wsp;
        // Controller *controller;
};

#endif
