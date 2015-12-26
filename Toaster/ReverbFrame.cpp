#include "ReverbFrame.h"
#include "ui_ReverbFrame.h"

ReverbFrame::ReverbFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ReverbFrame)
{
  ui->setupUi(this);
}

ReverbFrame::~ReverbFrame()
{
  delete ui;
}
