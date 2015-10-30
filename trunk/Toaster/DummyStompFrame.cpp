#include "DummyStompFrame.h"
#include "ui_DummyStompFrame.h"

DummyStompFrame::DummyStompFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DummyStompFrame)
{
  ui->setupUi(this);
}

DummyStompFrame::~DummyStompFrame()
{
  delete ui;
}
