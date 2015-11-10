#include "BrowserFrame.h"
#include "ui_BrowserFrame.h"

BrowserFrame::BrowserFrame(QWidget *parent)
  : QFrame(parent)
  , ui(new Ui::BrowserFrame)
  , mStompA(StompA)
  , mStompB(StompB)
  , mStompC(StompC)
  , mStompD(StompD)
  , mStompX(StompX)
  , mStompMod(StompMOD)
{
  ui->setupUi(this);
  ui->browseModeDial->setValues(ui->lcdDisplay->getBrowserModeViews());
  // stomps
  connect(&mStompA, SIGNAL(onOffReceived(bool)), this, SLOT(onStompAOnOff(bool)));
  connect(&mStompB, SIGNAL(onOffReceived(bool)), this, SLOT(onStompBOnOff(bool)));
  connect(&mStompC, SIGNAL(onOffReceived(bool)), this, SLOT(onStompCOnOff(bool)));
  connect(&mStompD, SIGNAL(onOffReceived(bool)), this, SLOT(onStompDOnOff(bool)));
  connect(&mStompX, SIGNAL(onOffReceived(bool)), this, SLOT(onStompXOnOff(bool)));
  connect(&mStompMod, SIGNAL(onOffReceived(bool)), this, SLOT(onStompModOnOff(bool)));
  connect(&mStompA, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompAType(::FXType)));
  connect(&mStompB, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompBType(::FXType)));
  connect(&mStompC, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompCType(::FXType)));
  connect(&mStompD, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompDType(::FXType)));
  connect(&mStompX, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompXType(::FXType)));
  connect(&mStompMod, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompModType(::FXType)));
  // delay
  connect(&mDelay, SIGNAL(onOffCutsTailReceived(bool)), this, SLOT(onDelayOnOff(bool)));
  // reverb
  connect(&mReverb, SIGNAL(onOffCutsTailReceived(bool)), this, SLOT(onReverbOnOff(bool)));
  // eq
  connect(&mEq, SIGNAL(bassReceived(double)), this, SLOT(onEqBass(double)));
  connect(&mEq, SIGNAL(middleReceived(double)), this, SLOT(onEqMiddle(double)));
  connect(&mEq, SIGNAL(trebleReceived(double)), this, SLOT(onEqTreble(double)));
  connect(&mEq, SIGNAL(presenceReceived(double)), this, SLOT(onEqPresence(double)));
  // profile
  connect(&mProfile, SIGNAL(rigNameReceived(const QString&)), this, SLOT(onRigName(const QString&)));
  connect(&mProfile, SIGNAL(rigAuthorReceived(const QString&)), this, SLOT(onRigAuthor(const QString&)));
  connect(&mProfile, SIGNAL(ampNameReceived(const QString&)), this, SLOT(onAmpName(const QString&)));
  // extended parameter
  connect(&mExtParam, SIGNAL(browserViewReceived(uint)), this, SLOT(onBrowserView(uint)));
}

BrowserFrame::~BrowserFrame()
{
  delete ui;
}
//------------------------------------------------------------------------------------------

// stomps
// ui => kpa
// kpa => ui
void BrowserFrame::onStompAOnOff(bool onOff)
{
  ui->lcdDisplay->setStompAEnabled(onOff);
}

void BrowserFrame::onStompBOnOff(bool onOff)
{
  ui->lcdDisplay->setStompBEnabled(onOff);
}

void BrowserFrame::onStompCOnOff(bool onOff)
{
  ui->lcdDisplay->setStompCEnabled(onOff);
}

void BrowserFrame::onStompDOnOff(bool onOff)
{
  ui->lcdDisplay->setStompDEnabled(onOff);
}

void BrowserFrame::onStompXOnOff(bool onOff)
{
  ui->lcdDisplay->setStompXEnabled(onOff);
}

void BrowserFrame::onStompModOnOff(bool onOff)
{
  ui->lcdDisplay->setStompModEnabled(onOff);
}

void BrowserFrame::onStompAType(::FXType type)
{
  ui->lcdDisplay->setStompAFXType(type);
}

void BrowserFrame::onStompBType(::FXType type)
{
  ui->lcdDisplay->setStompBFXType(type);
}

void BrowserFrame::onStompCType(::FXType type)
{
  ui->lcdDisplay->setStompCFXType(type);
}

void BrowserFrame::onStompDType(::FXType type)
{
  ui->lcdDisplay->setStompDFXType(type);
}

void BrowserFrame::onStompXType(::FXType type)
{
  ui->lcdDisplay->setStompXFXType(type);
}

void BrowserFrame::onStompModType(::FXType type)
{
  ui->lcdDisplay->setStompModFXType(type);
}
//------------------------------------------------------------------------------------------

// delay
// ui => kpa
// kpa => ui
void BrowserFrame::onDelayOnOff(bool onOff)
{
  ui->lcdDisplay->setDelayEnabled(onOff);
}
//------------------------------------------------------------------------------------------

// reverb
// ui => kpa
// kpa => ui
void BrowserFrame::onReverbOnOff(bool onOff)
{
  ui->lcdDisplay->setReverbEnabled(onOff);
}
//------------------------------------------------------------------------------------------

// eq
// ui => kpa
void BrowserFrame::on_eqBassDial_valueChanged(double value)
{
  mEq.applyBass(value);
}

void BrowserFrame::on_eqBassDial_valueChanged(const QString &value)
{
  ui->lcdDisplay->setBrowserModeBassValueText(value);
}

void BrowserFrame::on_eqMiddleDial_valueChanged(double value)
{
  mEq.applyMiddle(value);
}

void BrowserFrame::on_eqMiddleDial_valueChanged(const QString &value)
{
  ui->lcdDisplay->setBrowserModeMiddleValueText(value);
}

void BrowserFrame::on_eqTrebleDial_valueChanged(double value)
{
  mEq.applyTreble(value);
}

void BrowserFrame::on_eqTrebleDial_valueChanged(const QString &value)
{
  ui->lcdDisplay->setBrowserModeTrebleValueText(value);
}

void BrowserFrame::on_eqPresenceDial_valueChanged(double value)
{
  mEq.applyPresence(value);
}

void BrowserFrame::on_eqPresenceDial_valueChanged(const QString &value)
{
  ui->lcdDisplay->setBrowserModePresenceValueText(value);
}

// kpa => ui
void BrowserFrame::onEqBass(double bass)
{
  ui->eqBassDial->setValue(bass);
  update();
}

void BrowserFrame::onEqMiddle(double middle)
{
  ui->eqMiddleDial->setValue(middle);
  update();
}

void BrowserFrame::onEqTreble(double treble)
{
  ui->eqTrebleDial->setValue(treble);
  update();
}

void BrowserFrame::onEqPresence(double presence)
{
  ui->eqPresenceDial->setValue(presence);
  update();
}
//------------------------------------------------------------------------------------------

// profile
// ui => kpa
// kpa => ui
void BrowserFrame::onRigName(const QString& rigName)
{
  ui->lcdDisplay->setBrowserModeRigName(rigName);
}

void BrowserFrame::onRigAuthor(const QString& rigAuthor)
{
  ui->lcdDisplay->setBrowserModeRigAuthor(rigAuthor);
}

void BrowserFrame::onAmpName(const QString& ampName)
{
  ui->lcdDisplay->setBrowserModeAmpName(ampName);
}
//------------------------------------------------------------------------------------------

// extParam
// ui => kpa
void BrowserFrame::on_browseModeDial_valueChanged(int view)
{
  mExtParam.applyBrowserView(view);
}

// kpa => ui
void BrowserFrame::onBrowserView(unsigned int view)
{
  ui->lcdDisplay->setBrowserModeView(view);
}
//------------------------------------------------------------------------------------------





