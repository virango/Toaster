#include "StompEditorFrame.h"
#include "ui_StompEditorFrame.h"

StompEditorFrame::StompEditorFrame(QWidget *parent) :
  QStackedWidget(parent),
  ui(new Ui::StompEditorFrame)
{
  ui->setupUi(this);
}

StompEditorFrame::~StompEditorFrame()
{
  delete ui;
}
