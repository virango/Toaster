#include "StompControlStackedWidget.h"
#include "ui_StompControlStackedWidget.h"

StompControlStackedWidget::StompControlStackedWidget(QWidget *parent) :
  QStackedWidget(parent),
  ui(new Ui::StompControlStackedWidget)
{
  ui->setupUi(this);
}

StompControlStackedWidget::~StompControlStackedWidget()
{
  delete ui;
}
