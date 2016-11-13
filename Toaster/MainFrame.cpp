/*  This file is part of Toaster, the editor and remote control for Kemper profiling amplifier.
*
*   Copyright (C) 2016  Thomas Langer
*
*   Toaster is free software: you can redistribute it and/or modify it under the terms of the
*   GNU General Public License as published by the Free Software Foundation, either version 3
*   of the License, or (at your option) any later version.
*
*   Toaster is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
*   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*   See the GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along with Toaster.
*   If not, see <http://www.gnu.org/licenses/>.
*/
#include "MainFrame.h"
#include "Stomp.h"
#include "Amp.h"
#include "ui_MainFrame.h"
#include "DebugMidi.h"
#include "StompEditorPage.h"
#include "StompEditorFrame.h"
#include "MasterVolume.h"
#include "Settings.h"
#include "Delay.h"
#include "Eq.h"
#include "Cab.h"
#include "Global.h"
#include "Rig.h"
#include "Input.h"
#include "Reverb.h"
#include "Profile.h"
#include "Tap.h"
#include "LookUpTables.h"

MainFrame::MainFrame(QWidget *parent)
  : QFrame(parent)
  , ui(new Ui::MainFrame)
  , mStompACtxMenu(stompAObj)
  , mStompBCtxMenu(stompBObj)
  , mStompCCtxMenu(stompCObj)
  , mStompDCtxMenu(stompDObj)
  , mStompXCtxMenu(stompXObj)
  , mStompModCtxMenu(stompModObj)
  , mStompDelayCtxMenu(stompDelayObj)
  , mDelayCtxMenu(delayObj)
  , mReverbCtxMenu(reverbObj)
  , mOperationMode(Browser)
  , mPreviousOperationMode(Browser)
  , mEditModeButton(NULL)
  , mEditModeModule(NULL)
  , mCurrRigName("")
{
  ui->setupUi(this);

  ui->storeButton->setVisible(false);

  ui->rigVolumeDial->setLookUpTable(LookUpTables::getRigVolumeValues());
  ui->monitorVolumeDial->setLookUpTable(LookUpTables::getMainVolumeValues());
  ui->headphoneVolumeDial->setLookUpTable(LookUpTables::getMainVolumeValues());
  if(Settings::get().getKPAOSVersion() >= 0x04000000)
  {
    ui->delayMixDial->setLookUpTable(LookUpTables::getMixValuesV4());
    ui->reverbMixDial->setLookUpTable(LookUpTables::getMixValuesV4());
  }
  else
  {
    ui->delayMixDial->setLookUpTable(LookUpTables::getMixValues());
    ui->reverbMixDial->setLookUpTable(LookUpTables::getMixValues());
  }

  ui->masterVolumeDBDial->setLookUpTable(LookUpTables::getMainVolumeValues());

  // notifications
  // stomps
  //qRegisterMetaType<::FXType>("::FXType");
  connect(&stompAObj, &Stomp::onOffReceived, this, &MainFrame::onStompAOnOff);
  connect(&stompBObj, &Stomp::onOffReceived, this, &MainFrame::onStompBOnOff);
  connect(&stompCObj, &Stomp::onOffReceived, this, &MainFrame::onStompCOnOff);
  connect(&stompDObj, &Stomp::onOffReceived, this, &MainFrame::onStompDOnOff);
  connect(&stompXObj, &Stomp::onOffReceived, this, &MainFrame::onStompXOnOff);
  connect(&stompModObj, &Stomp::onOffReceived, this, &MainFrame::onStompModOnOff);
  connect(&stompAObj, &Stomp::typeReceived, this, &MainFrame::onStompAType);
  connect(&stompBObj, &Stomp::typeReceived, this, &MainFrame::onStompBType);
  connect(&stompCObj, &Stomp::typeReceived, this, &MainFrame::onStompCType);
  connect(&stompDObj, &Stomp::typeReceived, this, &MainFrame::onStompDType);
  connect(&stompXObj, &Stomp::typeReceived, this, &MainFrame::onStompXType);
  connect(&stompModObj, &Stomp::typeReceived, this, &MainFrame::onStompModType);
  connect(&stompModObj, static_cast<void (Stomp::*)(int)>(&Stomp::modulationRateReceived), this, &MainFrame::onModRate);
  connect(&stompModObj, &Stomp::modulationDepthReceived, this, &MainFrame::onModIntensity);
  // delay
  if(Settings::get().getKPAOSVersion() >= 0x04000000)
  {
    connect(&stompDelayObj, &Stomp::onOffReceived, this, &MainFrame::onDelayOnOff);
    connect(&stompDelayObj, &Stomp::typeReceived, this, &MainFrame::onStompDelayType);
  }
  else
  {
    connect(&delayObj, &Delay::onOffCutsTailReceived, this, &MainFrame::onDelayOnOff);
    connect(&delayObj, &Delay::feedbackReceived, this, &MainFrame::onDelayFeedback);
    connect(&delayObj, &Delay::mixReceived, this, &MainFrame::onDelayMix);
  }
  // reverb
  connect(&reverbObj, &Reverb::onOffCutsTailReceived, this, &MainFrame::onReverbOnOff);
  connect(&reverbObj, &Reverb::timeReceived, this, &MainFrame::onReverbTime);
  connect(&reverbObj, &Reverb::mixReceived, this, &MainFrame::onReverbMix);
  // amp
  connect(&ampObj, &Amp::onOffReceived, this, &MainFrame::onAmpOnOff);
  connect(&ampObj, &Amp::gainReceived, this, &MainFrame::onAmpGain);
  // eq
  connect(&eqObj, &Eq::onOffReceived, this, &MainFrame::onEqOnOff);
  // cab
  connect(&cabObj, &Cab::onOffReceived, this, &MainFrame::onCabOnOff);
  // rig
  //connect(&rigObj, SIGNAL(tempoReceived(double)), this, SLOT(onRigTempo(double)));
  connect(&rigObj, &Rig::volumeReceived, this, &MainFrame::onRigVolume);
  //connect(&rigObj, SIGNAL(tempoEnableReceived(bool)), this, SLOT(onRigTempoEnable(bool)));
  connect(&rigObj, &Rig::stompsEnableReceived, this, &MainFrame::onRigStompsEnable);
  connect(&rigObj, &Rig::stackEnableReceived, this, &MainFrame::onRigStackEnable);
  connect(&rigObj, &Rig::effectsEnableReceived, this, &MainFrame::onRigEffectsEnable);
  // global
  connect(&globalObj, &Global::operationModeReceived, this, &MainFrame::onGlobalOperationMode);
  connect(&globalObj, &Global::mainOutputVolumeReceived, this, &MainFrame::onGlobalMainVolume);
  connect(&globalObj, &Global::headphoneOutputVolumeReceived, this, &MainFrame::onGlobalHeadphoneVolume);
  connect(&globalObj, &Global::monitorOutputVolumeReceived, this, &MainFrame::onGlobalMonitorVolume);
  connect(&globalObj, &Global::directOutputVolumeReceived, this, &MainFrame::onGlobalDirectVolume);
  // input
  connect(&inputObj, &Input::noiseGateReceived, this, &MainFrame::onInputNoiseGate);
  connect(&inputObj, &Input::distortionSenseReceived, this, &MainFrame::onInputDistortionSense);
  connect(&inputObj, &Input::cleanSenseReceived, this, &MainFrame::onInputCleanSense);

  connect(ui->stompEditor, &StompEditorFrame::editorPageChanged, this, &MainFrame::onEditorPageChanged);

  ui->stompAButton->setCtxMenuProvider(&mStompACtxMenu);
  ui->stompBButton->setCtxMenuProvider(&mStompBCtxMenu);
  ui->stompCButton->setCtxMenuProvider(&mStompCCtxMenu);
  ui->stompDButton->setCtxMenuProvider(&mStompDCtxMenu);
  ui->stompXButton->setCtxMenuProvider(&mStompXCtxMenu);
  ui->stompModButton->setCtxMenuProvider(&mStompModCtxMenu);

  if(Settings::get().getKPAOSVersion() >= 0x04000000)
  {
    ui->delayButton->setCtxMenuProvider(&mStompDelayCtxMenu);
  }
  else
  {
    ui->delayButton->setCtxMenuProvider(&mDelayCtxMenu);
  }

  ui->reverbButton->setCtxMenuProvider(&mReverbCtxMenu);

  ui->stompEditor->init();

  MasterVolume& mv = MasterVolume::get();
  mv.init();

  connect(&mv, &MasterVolume::masterVolumeChanged,
          [=](int value) {ui->masterVolumeDBDial->setValue(value);} );

  connect(&mv, &MasterVolume::masterVolumeChanged,
          [=](int value) {ui->masterVolumeDial->setValue(Utils::raw2Phys(value, 10.0, 0));} );

  connect(&mv, &MasterVolume::linksChanged,
          [=](int noOfLinks) { ui->masterVolumeWidget->setCurrentIndex(noOfLinks == 1 ? 0 : 1);});

  connect(ui->headphoneVolumeDial, static_cast<void (QToasterLookUpTableDial::*)(int)>(&QToasterLookUpTableDial::valueChanged), &globalObj, &Global::applyHeadphoneOutputVolume);
  connect(ui->monitorVolumeDial, static_cast<void (QToasterLookUpTableDial::*)(int)>(&QToasterLookUpTableDial::valueChanged), &globalObj, &Global::applyMonitorOutputVolume);

  connect(&profileObj, &Profile::rigNameReceived, this, &MainFrame::onRigNameReveived);
}

MainFrame::~MainFrame()
{
  MasterVolume::get().dispose();
  if(ui != nullptr)
    delete ui;
}
//------------------------------------------------------------------------------------------

// global communication
void MainFrame::connect2KPA(const QString& connectName)
{
  globalObj.connect2KPA(connectName);
}

void MainFrame::disconnectFromKPA()
{
  globalObj.disconnectFromKPA();
}

void MainFrame::requestValues()
{
  stompAObj.requestAllValues();
  stompBObj.requestAllValues();
  stompCObj.requestAllValues();
  stompDObj.requestAllValues();
  stompXObj.requestAllValues();
  stompModObj.requestAllValues();
  if(Settings::get().getKPAOSVersion() >= 0x04000000)
    stompDelayObj.requestAllValues();
  else
    delayObj.requestAllValues();
  reverbObj.requestAllValues();
  ampObj.requestAllValues();
  eqObj.requestAllValues();
  cabObj.requestAllValues();
  rigObj.requestAllValues();
  globalObj.requestAllValues();
  inputObj.requestAllValues();
  profileObj.requestAllValues();

  ui->browser->requestValues();

  MasterVolume::get().requestValues();
  //DebugMidi::get().debugScanRequest(0x04, 0x00, 0x7F);
  //DebugMidi::get().debugScanRequest(0x00, 0x0, 0x7F);
  //DebugMidi::get().debugScanRequest(0x01, 0x00, 0x7F);
}

// stomps
// ui => kpa
void MainFrame::on_stompAButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(stompAObj, bt, longClick);
}

void MainFrame::on_stompBButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(stompBObj, bt, longClick);
}

void MainFrame::on_stompCButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(stompCObj, bt, longClick);
}

void MainFrame::on_stompDButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(stompDObj, bt, longClick);
}

void MainFrame::on_stompXButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(stompXObj, bt, longClick);
}

void MainFrame::on_stompModButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(stompModObj, bt, longClick);
}

void MainFrame::on_modRateDial_valueChanged(double value)
{
  stompModObj.applyModulationRate((int) value);
}

void MainFrame::on_modIntensityDial_valueChanged(double value)
{
  stompModObj.applyModulationDepth(value);
}

// kpa => ui
void MainFrame::onStompAOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompAButton->setState(state);
    update();
  }
}

void MainFrame::onStompBOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompBButton->setState(state);
    update();
  }
}

void MainFrame::onStompCOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompCButton->setState(state);
    update();
  }
}

void MainFrame::onStompDOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompDButton->setState(state);
    update();
  }
}

void MainFrame::onStompXOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompXButton->setState(state);
    update();
  }
}

void MainFrame::onStompModOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompModButton->setState(state);
    update();
  }
}

void MainFrame::onStompAType(::FXType type)
{
  setStompLedColor(type, ui->stompALed);
}

void MainFrame::onStompBType(::FXType type)
{
  setStompLedColor(type, ui->stompBLed);
}

void MainFrame::onStompCType(::FXType type)
{
  setStompLedColor(type, ui->stompCLed);
}

void MainFrame::onStompDType(::FXType type)
{
  setStompLedColor(type, ui->stompDLed);
}

void MainFrame::onStompXType(::FXType type)
{
  setStompLedColor(type, ui->stompXLed);
}

void MainFrame::onStompModType(::FXType type)
{
  setStompLedColor(type, ui->stompModLed);
}

void MainFrame::onStompDelayType(::FXType type)
{
  setStompLedColor(type, ui->stompDelay1Led);
  setStompLedColor(type, ui->stompDelay2Led);
}

void MainFrame::onModIntensity(double value)
{
  ui->modIntensityDial->setValue(value);
}

void MainFrame::onModRate(int value)
{
  ui->modRateDial->setValue(value);
}

//------------------------------------------------------------------------------------------

// reverb
// ui => kpa
void MainFrame::on_reverbButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(reverbObj, bt, longClick);
}

void MainFrame::on_reverbTimeDial_valueChanged(double arg1)
{
  reverbObj.applyTime(arg1);
}

void MainFrame::on_reverbMixDial_valueChanged(int value)
{
  reverbObj.applyMix(value);
}

// kpa => ui
void MainFrame::onReverbOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->reverbButton->setState(state);
    update();
  }
}

void MainFrame::onReverbTime(double time)
{
  ui->reverbTimeDial->setValue(time);
}

void MainFrame::onReverbMix(int mix)
{
  ui->reverbMixDial->setValue(mix);
}
//------------------------------------------------------------------------------------------

// delay
// ui => kpa
void MainFrame::on_delayButton_clicked(QToasterButton& bt, bool longClick)
{
  if(Settings::get().getKPAOSVersion() >= 0x04000000)
  {
    handleStompButtonClick(stompDelayObj, bt, longClick);
  }
  else
  {
    handleStompButtonClick(delayObj, bt, longClick);
  }
}

void MainFrame::on_delayFeedbackDial_valueChanged(double arg1)
{
  delayObj.applyFeedback(arg1);
}

void MainFrame::on_delayMixDial_valueChanged(int value)
{
  delayObj.applyMix(value);
}

// kpa => ui
void MainFrame::onDelayOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->delayButton->setState(state);
    update();
  }
}

void MainFrame::onDelayFeedback(double feedback)
{
  ui->delayFeedbackDial->setValue(feedback);
  update();
}

void MainFrame::onDelayMix(int mix)
{
  ui->delayMixDial->setValue(mix);
  update();
}
//------------------------------------------------------------------------------------------


// amp
// ui => kpa
void MainFrame::on_amplifierButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(ampObj, bt, longClick);
}

void MainFrame::on_gainDial_valueChanged(double gain)
{
  ampObj.applyGain(gain);
}

// kpa => ui
void MainFrame::onAmpOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->amplifierButton->setState(state);
    update();
  }
}

void MainFrame::onAmpGain(double val)
{
  ui->gainDial->setValue(val);
  update();
}
//------------------------------------------------------------------------------------------

// eq
// ui => kpa
void MainFrame::on_eqButton_clicked(QToasterButton& bt, bool /*longClick*/)
{
  eqObj.applyOnOff(bt.toggleOnOff());
  update();
}

// kpa => ui
void MainFrame::onEqOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->eqButton->setState(state);
  update();
}
//------------------------------------------------------------------------------------------

// cab
// ui => kpa
void MainFrame::on_cabinetButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(cabObj, bt, longClick);
}

// kpa => ui
void MainFrame::onCabOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->cabinetButton->setState(state);
    update();
  }
}
//------------------------------------------------------------------------------------------

// rig
// ui => kpa
void MainFrame::on_rigVolumeDial_valueChanged(int value)
{
  rigObj.applyVolume(value);
}

void MainFrame::on_stompsButton_clicked(QToasterButton& bt, bool /*longClick*/)
{
  rigObj.applyStompsEnable(bt.toggleOnOff());
  update();
}

void MainFrame::on_stackButton_clicked(QToasterButton& bt, bool /*longClick*/)
{
  rigObj.applyStackEnable(bt.toggleOnOff());
  update();
}

void MainFrame::on_effectsButton_clicked(QToasterButton& bt, bool /*longClick*/)
{
  rigObj.applyEffectsEnable(bt.toggleOnOff());
  update();
}

// kpa => ui
void MainFrame::onRigVolume(int volume)
{
  ui->rigVolumeDial->setValue(volume);
  update();
}

void MainFrame::onRigStompsEnable(bool stompsEnable)
{
  QToasterButton::State state = stompsEnable ? QToasterButton::On : QToasterButton::Off;
  ui->stompsButton->setState(state);
  update();
}

void MainFrame::onRigStackEnable(bool stackEnable)
{
  QToasterButton::State state = stackEnable ? QToasterButton::On : QToasterButton::Off;
  ui->stackButton->setState(state);
  update();
}

void MainFrame::onRigEffectsEnable(bool effectsEnable)
{
  QToasterButton::State state = effectsEnable ? QToasterButton::On : QToasterButton::Off;
  ui->effectsButton->setState(state);
  update();
}
//------------------------------------------------------------------------------------------

// global
// ui => kpa
void MainFrame::on_chickenHeadDial_valueChanged(const QChickenHeadDial::State& state)
{
  globalObj.applyOperationMode((Global::OperationMode) state);
}

// kpa => ui
void MainFrame::onGlobalOperationMode(unsigned short opMode)
{
  ui->chickenHeadDial->setState((QChickenHeadDial::State)opMode);
  if(mOperationMode != StompEdit)
  {
    ui->modeFrames->setCurrentIndex(opMode-1);
    // todo: a better solution
    if((Global::OperationMode)opMode == Global::Tuner)
      globalObj.requestMasterTune();
  }
  update();
}

void MainFrame::onGlobalMainVolume(int volume)
{
  update();
}

void MainFrame::onGlobalHeadphoneVolume(int volume)
{
  ui->headphoneVolumeDial->setValue(volume);
  update();
}

void MainFrame::onGlobalMonitorVolume(int volume)
{
  ui->monitorVolumeDial->setValue(volume);
  update();
}

void MainFrame::onGlobalDirectVolume(double volume)
{
  update();
}
//------------------------------------------------------------------------------------------

// input
// ui => kpa
void MainFrame::on_noiseGateDial_valueChanged(double noiseGate)
{
  inputObj.applyNoiseGate(noiseGate);
}

void MainFrame::on_distortionSenseDial_valueChanged(double distortionSense)
{
  inputObj.applyDistortionSense(distortionSense);
}

void MainFrame::on_cleanSenseDial_valueChanged(double cleanSense)
{
  inputObj.applyCleanSense(cleanSense);
}

// kpa => ui
void MainFrame::onInputNoiseGate(double noiseGate)
{
  ui->noiseGateDial->setValue(noiseGate);
  update();
}

void MainFrame::onInputDistortionSense(double distortionSense)
{
  ui->distortionSenseDial->setValue(distortionSense);
  update();
}

void MainFrame::onInputCleanSense(double cleanSense)
{
  ui->cleanSenseDial->setValue(cleanSense);
  update();
}
//------------------------------------------------------------------------------------------

// profile
// ui => kpa
void MainFrame::on_rigPrevButton_clicked(QToasterButton &bt, bool)
{
  if(bt.state() == QToasterButton::On)
  {
    profileObj.applyRigPrev();
    requestValues(); // todo: request just the required values
  }
}

void MainFrame::on_rigNextButton_clicked(QToasterButton &bt, bool )
{
  if(bt.state() == QToasterButton::On)
  {
    profileObj.applyRigNext();
    requestValues(); // todo: request just the required values
  }
}
// kpa => ui
//------------------------------------------------------------------------------------------

// utility methods
void MainFrame::handleStompButtonClick(QObject& module, QToasterButton& stompBt, bool longClick)
{
  if(longClick)
  {
    toggleOperationMode(module, StompEdit, &stompBt);
  }
  else
  {
    Stomp* pStomp = qobject_cast<Stomp*>(&module);
    Delay* pDelay = qobject_cast<Delay*>(&module);
    Reverb* pReverb = qobject_cast<Reverb*>(&module);
    Amp* pAmp = qobject_cast<Amp*>(&module);
    Cab* pCab = qobject_cast<Cab*>(&module);
    if(pStomp != nullptr)
    {
      pStomp->applyOnOff(stompBt.toggleOnOff());
      pStomp->requestOnOff();
    }
    else if(pDelay != nullptr)
    {
      pDelay->applyOnOffCutsTail(stompBt.toggleOnOff());
      pDelay->requestOnOffCutsTail();
    }
    else if(pReverb != nullptr)
    {
      pReverb->applyOnOffCutsTail(stompBt.toggleOnOff());
      pReverb->requestOnOffCutsTail();
    }
    else if(pAmp != nullptr)
    {
      pAmp->applyOnOff(stompBt.toggleOnOff());
      pAmp->requestOnOff();
    }
    else if(pCab != nullptr)
    {
      pCab->applyOnOff(stompBt.toggleOnOff());
      pCab->requestOnOff();
    }
  }
  update();
}

void MainFrame::toggleOperationMode(QObject& module, OperationMode opMode, QToasterButton* bt)
{
  if(bt != nullptr)
  {
    if(mEditModeButton != NULL && bt != mEditModeButton)
      mEditModeButton->resetToOnOffState();

    if(bt->state() == QToasterButton::Blinking)
    {
      bt->resetToOnOffState();
      mEditModeButton = nullptr;
      mEditModeModule = nullptr;
      ui->exitButton->setState(QToasterButton::Off);
      ui->modeFrames->setCurrentIndex(ui->modeFrames->indexOf(ui->browser)); // todo:
      ui->stompEditor->deactivate();
      mOperationMode = mPreviousOperationMode;
    }
    else
    {
      bt->setState(QToasterButton::Blinking);
      ui->exitButton->setState(QToasterButton::On);
      mEditModeButton = bt;
      mEditModeModule = &module;
      ui->modeFrames->setCurrentIndex(ui->modeFrames->indexOf(ui->stompEditor));
      ui->stompEditor->activate(module);
      mOperationMode = opMode;
    }
  }
  else if(mEditModeButton != nullptr)
  {
    mEditModeButton->resetToOnOffState();
    mEditModeButton = nullptr;
    ui->exitButton->setState(QToasterButton::Off);
  }
}

void MainFrame::setStompLedColor(::FXType type, QMultiColorLed* ledWidget)
{
  switch(type)
  {
    case WahWah:
    case WahHighPass:
    case WahLowPass:
    case WahVowelFilter:
    case WahFlanger:
    case WahRateReducer:
    case WahRingModulator:
    case WahFrequencyShifter:
    case WahFormantShifter:
    case WahPhaser:
      ledWidget->setColor(QMultiColorLed::Orange);
      break;
    case PureBooster:
    case SoftShaper:
    case HardShaper:
    case WaveShaper:
    case PlusDS:
    case FuzzDS:
    case BitShaper:
    case GreenScream:
    case OneDS:
    case Muffin:
    case MouseDS:
    case RectiShaper:
    case TrebleBooster:
    case LeadBooster:
    case WahPedalBooster:
    case MetalDS:
      ledWidget->setColor(QMultiColorLed::Red);
      break;
    case GraphicEqualizer:
    case StudioEqualizer:
    case MetalEqualizer:
    case StereoWidener:
      ledWidget->setColor(QMultiColorLed::Yellow);
      break;
    case Compressor:
    case NoiseGate21:
    case NoiseGate41:
      ledWidget->setColor(QMultiColorLed::Cyan);
      break;
    case VintageChorus:
    case HyperChorus:
    case AirChorus:
    case MicroPitch:;
    case Vibrato:
    case RotarySpeaker:
    case Tremolo:
      ledWidget->setColor(QMultiColorLed::Blue);
      break;
    case Phaser:
    case PhaserVibe:
    case PhaserOneway:
    case Flanger:
    case FlangerOneway:
      ledWidget->setColor(QMultiColorLed::Purple);
      break;
    case Space:
    case LegacyDelay:
      ledWidget->setColor(QMultiColorLed::Green);
      break;
    case Transpose:
    case PedalPitch:
    case PedalVinylStop:
    case ChromaticPitch:
    case HarmonicPitch:
    case AnalogOctaver:
    case LoopMono:
    case LoopStereo:
    case LoopDistortion:
      ledWidget->setColor(QMultiColorLed::White);
      break;
    default:
      ledWidget->setColor(QMultiColorLed::Off);
      break;
  }
  update();
}
//------------------------------------------------------------------------------------------



void MainFrame::on_exitButton_clicked(QToasterButton& /*bt*/, bool /*longClick*/)
{
  if(mOperationMode == StompEdit && mEditModeButton != nullptr && mEditModeModule != nullptr)
  {
    toggleOperationMode(*mEditModeModule, mPreviousOperationMode, mEditModeButton);
  }
}


void MainFrame::on_prevPageButton_clicked(QToasterButton& /*bt*/, bool /*longClick*/)
{
  ui->stompEditor->prevDisplayPage();
}

void MainFrame::on_nextPageButton_clicked(QToasterButton& /*bt*/, bool /*longClick*/)
{
  ui->stompEditor->nextDisplayPage();
}

void MainFrame::onEditorPageChanged(IStompEditorPage* editorPage)
{
  if(editorPage == nullptr || editorPage->getMaxDisplayPage() == QToasterLCD::Page1)
  {
    ui->prevPageButton->setState(QToasterButton::Off);
    ui->nextPageButton->setState(QToasterButton::Off);
  }
  else
  {
    if(editorPage->getCurrentDisplayPage() > QToasterLCD::Page1)
      ui->prevPageButton->setState(QToasterButton::On);
    else
      ui->prevPageButton->setState(QToasterButton::Off);

    if(editorPage->getCurrentDisplayPage() < editorPage->getMaxDisplayPage())
      ui->nextPageButton->setState(QToasterButton::On);
    else
      ui->nextPageButton->setState(QToasterButton::Off);
  }
  update();
}

void MainFrame::on_inputButton_clicked(QToasterButton &bt, bool /*longClick*/)
{
  handleStompButtonClick(inputObj, bt, true);
}

void MainFrame::on_outputButton_clicked(QToasterButton &bt, bool /*longClick*/)
{
  handleStompButtonClick(globalObj, bt, true);
}


void MainFrame::on_masterVolumeDBDial_valueChanged(int value)
{
  MasterVolume::get().onMasterVolume(value);
  ui->masterVolumeDial->setValue(Utils::raw2Phys(value, 10.0, 0));
}

void MainFrame::on_masterVolumeDial_valueChanged(double value)
{
  unsigned short newValue = phys2Raw(value, 10.0, 0);
  MasterVolume::get().onMasterVolume(newValue);
  ui->masterVolumeDBDial->setValue(newValue);
}

void MainFrame::on_tapButton_clicked(QToasterButton &bt, bool longClick)
{
  if(longClick)
    tapObj.applyTapTempoBeatScanner();
  else
    tapObj.applyTapTempo();
}

void MainFrame::onRigNameReveived(const QString& rigName)
{
  if(mCurrRigName != rigName)
  {
    mCurrRigName = rigName;
    requestValues();
  }
}

