#include "WahWahWidget.h"
#include "ui_WahWahWidget.h"

WahWahWidget::WahWahWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::WahWahWidget)
{
  ui->setupUi(this);
}

WahWahWidget::~WahWahWidget()
{
  delete ui;
}
