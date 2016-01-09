#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AboutDialog)
{
  ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
  delete ui;
}

void AboutDialog::setVersionString(const QString versionStr)
{
  ui->versionLabel->setText("Version " + versionStr);
}
