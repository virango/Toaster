#include "ToasterWindow.h"
#include "ui_ToasterWindow.h"
#include "Midi.h"
#include "qtoasterdial.h"

ToasterWindow::ToasterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToasterWindow)
{
    ui->setupUi(this);
    Midi::get().openMidiPorts("", "");

    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_actionRequest_triggered()) );
    timer->start(200);
}

ToasterWindow::~ToasterWindow()
{
  delete ui;
}

void ToasterWindow::on_actionRequest_triggered()
{
  ui->mainFrame->requestValues();
}
