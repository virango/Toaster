#include "InputFrame.h"
#include "ui_InputFrame.h"
#include "LookUpTables.h"

InputFrame::InputFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::InputFrame)
  , mpInput(nullptr)
{
  ui->setupUi(this);
}

InputFrame::~InputFrame()
{
  delete ui;
}

void InputFrame::activate(QObject& module)
{
  mpInput = qobject_cast<Input*>(&module);

  if(mpInput != nullptr)
  {
    connect(mpInput, &Input::cleanSenseReceived, this, &InputFrame::OnCleanSens);
    connect(mpInput, &Input::distortionSenseReceived, this, &InputFrame::OnDistortionSens);
    connect(&mGlobal, &Global::inputSourceReceived, this, &InputFrame::OnInputSource);
    connect(&mGlobal, &Global::reampSensReceived, this, &InputFrame::OnReampSens);

    mpInput->requestAllValues();
    mGlobal.requestInputSource();
    mGlobal.requestReampSense();
  }
}

void InputFrame::deactivate()
{
  if(mpInput != nullptr)
  {
    disconnect(mpInput, &Input::cleanSenseReceived, this, &InputFrame::OnCleanSens);
    disconnect(mpInput, &Input::distortionSenseReceived, this, &InputFrame::OnDistortionSens);
    disconnect(&mGlobal, &Global::inputSourceReceived, this, &InputFrame::OnInputSource);
    disconnect(&mGlobal, &Global::reampSensReceived, this, &InputFrame::OnReampSens);

    mpInput = nullptr;
  }
}

QToasterLCD::Page InputFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page InputFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void InputFrame::setCurrentDisplayPage(QToasterLCD::Page /*page*/)
{
}

void InputFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void InputFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void InputFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void InputFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void InputFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void InputFrame::on_cleanSensDial_valueChanged(double value)
{
  if(mpInput != nullptr)
    mpInput->applyCleanSense(value);
}

void InputFrame::on_distortionSensDial_valueChanged(double value)
{
  if(mpInput != nullptr)
    mpInput->applyDistortionSense(value);
}

void InputFrame::on_inputSourceDial_valueChanged(int valueIndex)
{
  mGlobal.applyInputSource(valueIndex);
}

void InputFrame::on_reampSensDial_valueChanged(double value)
{
  mGlobal.applyReampSense(value);
}

void InputFrame::OnCleanSens(double value)
{
  ui->cleanSensDial->setValue(value);
  update();
}

void InputFrame::OnDistortionSens(double value)
{
  ui->distortionSensDial->setValue(value);
  update();
}

void InputFrame::OnInputSource(int valueIndex)
{
  ui->inputSourceDial->setValue(valueIndex);
  update();
}

void InputFrame::OnReampSens(double value)
{
  ui->reampSensDial->setValue(value);
}
