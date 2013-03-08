#include "window.h"
#include "generator.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    QAction *newAct = new QAction(tr("&New"), this);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(generate()));
}
