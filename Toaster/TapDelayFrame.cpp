#include "TapDelayFrame.h"
#include "ui_TapDelayFrame.h"

TapDelayFrame::TapDelayFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::TapDelayFrame)
  , mpDelay(nullptr)
{
  ui->setupUi(this);
}

TapDelayFrame::~TapDelayFrame()
{
  delete ui;
}
void TapDelayFrame::activate(QObject& stomp)
{
  mpDelay = dynamic_cast<Delay*>(&stomp);

  if(mpDelay != nullptr)
  {
    connect(mpDelay, SIGNAL(bandwidthReceived(double)), this, SLOT(onBandwidth(double)));
    connect(mpDelay, SIGNAL(centerFrequencyReceived(double)), this, SLOT(onCenterFrequency(double)));
    connect(mpDelay, SIGNAL(modulationReceived(double)), this, SLOT(onModulation(double)));
    connect(mpDelay, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpDelay, SIGNAL(clockLeftReceived(::DelayClock)), this, SLOT(onClockLeft(::DelayClock)));
    connect(mpDelay, SIGNAL(clockRightReceived(::DelayClock)), this, SLOT(onClockRight(::DelayClock)));
    connect(mpDelay, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));

    mpDelay->requestBandwidth();
    mpDelay->requestCenterFrequency();
    mpDelay->requestModulation();
    mpDelay->requestDucking();
    mpDelay->requestClockLeft();
    mpDelay->requestClockRight();
    mpDelay->requestVolume();

    ui->lcdDisplay->setStompInstance("Delay Effect");
    ui->lcdDisplay->setStompName(LookUpTables::delayTypeName(mpDelay->getDelayType()));
  }
}

void TapDelayFrame::deactivate()
{
  if(mpDelay != nullptr)
  {
    disconnect(mpDelay, SIGNAL(bandwidthReceived(double)), this, SLOT(onBandwidth(double)));
    disconnect(mpDelay, SIGNAL(centerFrequencyReceived(double)), this, SLOT(onCenterFrequency(double)));
    disconnect(mpDelay, SIGNAL(modulationReceived(double)), this, SLOT(onModulation(double)));
    disconnect(mpDelay, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpDelay, SIGNAL(timeReceived(double)), this, SLOT(onTime(double)));
    disconnect(mpDelay, SIGNAL(ratioReceived(::DelayRatio)), this, SLOT(onRatio(::DelayRatio)));
    disconnect(mpDelay, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  }
  mpDelay = nullptr;
}

void TapDelayFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void TapDelayFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void TapDelayFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void TapDelayFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void TapDelayFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void TapDelayFrame::on_bandwidthDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyBandwidth(value);
}

void TapDelayFrame::on_centerFrequencyDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyCenterFrequency(value);
}

void TapDelayFrame::on_modulationDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyModulation(value);
}

void TapDelayFrame::on_duckingDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyDucking(value);
}

void TapDelayFrame::on_clockLeftDial_valueChanged(int valueIndex)
{
  if(mpDelay != nullptr)
    mpDelay->applyClockLeft((::DelayClock)valueIndex);
}

void TapDelayFrame::on_clockRightDial_valueChanged(int valueIndex)
{
  if(mpDelay != nullptr)
    mpDelay->applyClockRight((::DelayClock)valueIndex);
}

void TapDelayFrame::on_volumeDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyVolume(value);
}

void TapDelayFrame::onBandwidth(double value)
{
  ui->bandwidthDial->setValue(value);
}

void TapDelayFrame::onCenterFrequency(double value)
{
  ui->centerFrequencyDial->setValue(value);
}

void TapDelayFrame::onModulation(double value)
{
  ui->modulationDial->setValue(value);
}

void TapDelayFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
}

void TapDelayFrame::onClockLeft(::DelayClock clockLeft)
{
  ui->clockLeftDial->setValue((int)clockLeft);
}

void TapDelayFrame::onClockRight(::DelayClock clockRight)
{
  ui->clockRightDial->setValue((int)clockRight);
}

void TapDelayFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
}
