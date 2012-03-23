
#ifndef BASICUI_H_
#define BASICUI_H_

#include <QMainWindow>

class MainWidget;
class Workspace;

class BasicUi: public QMainWindow {

    Q_OBJECT

    public:
        BasicUi(QWidget *parent = 0);
        void setWorkspace(Workspace *);

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
