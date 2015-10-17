#include "MainFrame.h"
#include "ui_MainFrame.h"
#include "DebugMidi.h"

MainFrame::MainFrame(QWidget *parent)
  : QFrame(parent)
  , ui(new Ui::MainFrame)
  , mStompA(StompA)
  , mStompB(StompB)
  , mStompC(StompC)
  , mStompD(StompD)
  , mStompX(StompX)
  , mStompMod(StompMOD)
  , mStompACtxMenu(mStompA)
  , mStompBCtxMenu(mStompB)
  , mStompCCtxMenu(mStompC)
  , mStompDCtxMenu(mStompD)
  , mStompXCtxMenu(mStompX)
  , mStompModCtxMenu(mStompMod)
  , mOperationMode(Browser)
  , mEditModeButton(NULL)
{
  ui->setupUi(this);

  // notifications
  // stomps
  qRegisterMetaType<::FXType>("::FXType");
  connect(&mStompA, SIGNAL(onOffReceived(bool)), this, SLOT(onStompAOnOff(bool)));
  connect(&mStompB, SIGNAL(onOffReceived(bool)), this, SLOT(onStompBOnOff(bool)));
  connect(&mStompC, SIGNAL(onOffReceived(bool)), this, SLOT(onStompCOnOff(bool)));
  connect(&mStompD, SIGNAL(onOffReceived(bool)), this, SLOT(onStompDOnOff(bool)));
  connect(&mStompX, SIGNAL(onOffReceived(bool)), this, SLOT(onStompXOnOff(bool)));
  connect(&mStompMod, SIGNAL(onOffReceived(bool)), this, SLOT(onStompModOnOff(bool)));
  connect(&mDelay, SIGNAL(onOffCutsTailReceived(bool)), this, SLOT(onStompDelayOnOff(bool)));
  connect(&mDelay, SIGNAL(feedbackReceived(double)), this, SLOT(onStompDelayFeedback(double)));
  connect(&mDelay, SIGNAL(mixReceived(double)), this, SLOT(onStompDelayMix(double)));
  connect(&mReverb, SIGNAL(onOffCutsTailReceived(bool)), this, SLOT(onStompReverbOnOff(bool)));
  connect(&mReverb, SIGNAL(timeReceived(double)), this, SLOT(onStompReverbTime(double)));
  connect(&mReverb, SIGNAL(mixReceived(double)), this, SLOT(onStompReverbMix(double)));
  connect(&mStompA, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompAType(::FXType)));
  connect(&mStompB, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompBType(::FXType)));
  connect(&mStompC, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompCType(::FXType)));
  connect(&mStompD, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompDType(::FXType)));
  connect(&mStompX, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompXType(::FXType)));
  connect(&mStompMod, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompModType(::FXType)));
  // amp
  connect(&mAmp, SIGNAL(onOffReceived(bool)), this, SLOT(onAmpOnOff(bool)));
  connect(&mAmp, SIGNAL(gainReceived(double)), this, SLOT(onAmpGain(double)));
  // eq
  connect(&mEq, SIGNAL(onOffReceived(bool)), this, SLOT(onEqOnOff(bool)));
  // cab
  connect(&mCab, SIGNAL(onOffReceived(bool)), this, SLOT(onCabOnOff(bool)));
  // rig
  //connect(&mRig, SIGNAL(tempoReceived(double)), this, SLOT(onRigTempo(double)));
  connect(&mRig, SIGNAL(volumeReceived(double)), this, SLOT(onRigVolume(double)));
  //connect(&mRig, SIGNAL(tempoEnableReceived(bool)), this, SLOT(onRigTempoEnable(bool)));
  connect(&mRig, SIGNAL(stompsEnableReceived(bool)), this, SLOT(onRigStompsEnable(bool)));
  connect(&mRig, SIGNAL(stackEnableReceived(bool)), this, SLOT(onRigStackEnable(bool)));
  connect(&mRig, SIGNAL(effectsEnableReceived(bool)), this, SLOT(onRigEffectsEnable(bool)));
  // global
  connect(&mGlobal, SIGNAL(operationModeReceived(unsigned short)), this, SLOT(onGlobalOperationMode(unsigned short)));
  connect(&mGlobal, SIGNAL(mainOutputVolumeReceived(double)), this, SLOT(onGlobalMainVolume(double)));
  connect(&mGlobal, SIGNAL(headphoneOutputVolumeReceived(double)), this, SLOT(onGlobalHeadphoneVolume(double)));
  connect(&mGlobal, SIGNAL(monitorOutputVolumeReceived(double)), this, SLOT(onGlobalMonitorVolume(double)));
  connect(&mGlobal, SIGNAL(directOutputVolumeReceived(double)), this, SLOT(onGlobalDirectVolume(double)));
  // input
  connect(&mInput, SIGNAL(noiseGateReceived(double)), this, SLOT(onInputNoiseGate(double)));
  connect(&mInput, SIGNAL(distortionSenseReceived(double)), SLOT(onInputDistortionSense(double)));
  connect(&mInput, SIGNAL(cleanSenseReceived(double)), SLOT(onInputCleanSense(double)));

  ui->qStompAButton->setCtxMenuProvider(&mStompACtxMenu);
  ui->qStompBButton->setCtxMenuProvider(&mStompBCtxMenu);
  ui->qStompCButton->setCtxMenuProvider(&mStompCCtxMenu);
  ui->qStompDButton->setCtxMenuProvider(&mStompDCtxMenu);
  ui->qStompXButton->setCtxMenuProvider(&mStompXCtxMenu);
  ui->qStompModButton->setCtxMenuProvider(&mStompModCtxMenu);
}

MainFrame::~MainFrame()
{
    delete ui;
}

void MainFrame::connect2KPA(const QString& connectName)
{
  mGlobal.connect2KPA(connectName);
}

void MainFrame::disconnectFromKPA()
{
  mGlobal.disconnectFromKPA();
}

void MainFrame::requestValues()
{
  mStompA.requestAllValues();
  mStompB.requestAllValues();
  mStompC.requestAllValues();
  mStompD.requestAllValues();
  mStompX.requestAllValues();
  mStompMod.requestAllValues();
  mDelay.requestAllValues();
  mReverb.requestAllValues();
  mAmp.requestAllValues();
  mEq.requestAllValues();
  mCab.requestAllValues();
  mRig.requestAllValues();
  mGlobal.requestAllValues();
  mInput.requestAllValues();
  mProfile.requestAllValues();

  //DebugMidi::get().debugScanRequest(0x04, 0x00, 0x7F);
  //DebugMidi::get().debugScanRequest(0x00, 0x0, 0x7F);
  //DebugMidi::get().debugScanRequest(0x01, 0x00, 0x7F);
}

void MainFrame::handleStompButtonClick(Stomp& stomp, QToasterButton& stompBt, bool longClick)
{
  if(longClick)
  {
    toggleOperationMode(StompEdit, &stompBt);
  }
  else
  {
    stomp.applyOnOff(stompBt.toggleOnOff());
  }
  update();
}

void MainFrame::toggleOperationMode(OperationMode opMode, QToasterButton* bt)
{
  mOperationMode = opMode;
  if(bt != NULL)
  {
    if(mEditModeButton != NULL && bt != mEditModeButton)
      mEditModeButton->resetToOnOffState();

    if(bt->state() == QToasterButton::Blinking)
    {
      bt->resetToOnOffState();
      mEditModeButton = NULL;
    }
    else
    {
      bt->setState(QToasterButton::Blinking);
      mEditModeButton = bt;
    }
  }
  else if(mEditModeButton != NULL)
  {
    mEditModeButton->resetToOnOffState();
    mEditModeButton = NULL;
  }
}

/*
 * stomps slots
 */
void MainFrame::on_qStompAButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompA, bt, longClick);
}

void MainFrame::on_qStompBButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompB, bt, longClick);
}

void MainFrame::on_qStompCButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompC, bt, longClick);
}

void MainFrame::on_qStompDButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompD, bt, longClick);
}

void MainFrame::on_qStompXButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompX, bt, longClick);
}

void MainFrame::on_qStompModButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompMod, bt, longClick);
}

void MainFrame::onStompAOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompAButton->setState(state);
  update();
}

void MainFrame::onStompBOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompBButton->setState(state);
  update();
}

void MainFrame::onStompCOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompCButton->setState(state);
  update();
}

void MainFrame::onStompDOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompDButton->setState(state);
  update();
}

void MainFrame::onStompXOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompXButton->setState(state);
  update();
}

void MainFrame::onStompModOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompModButton->setState(state);
  update();
}

void MainFrame::onStompDelayOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompDelayButton->setState(state);
  update();
}

void MainFrame::onStompDelayFeedback(double feedback)
{
  ui->qDelayFeedbackDial->setValue(feedback);
  update();
}

void MainFrame::onStompDelayMix(double mix)
{
  ui->qDelayMixDial->setValue(mix);
  update();
}

void MainFrame::onStompReverbOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompReverbButton->setState(state);
  update();
}

void MainFrame::onStompAType(::FXType type)
{
  // TODO: set the LED color
}

void MainFrame::onStompBType(::FXType type)
{
  // TODO: set the LED color
}

void MainFrame::onStompCType(::FXType type)
{
  // TODO: set the LED color
}

void MainFrame::onStompDType(::FXType type)
{
  // TODO: set the LED color
}

void MainFrame::onStompXType(::FXType type)
{
  // TODO: set the LED color
}

void MainFrame::onStompModType(::FXType type)
{
  // TODO: set the LED color
}


/*
 * amp slots
 */
void MainFrame::on_qGainDial_valueChanged(double gain)
{
  mAmp.applyGain(gain);
}

void MainFrame::on_qAmplifierButton_clicked(QToasterButton& bt, bool longClick)
{
  if(longClick)
    toggleOperationMode(AmpEdit, &bt);
  else
    mAmp.applyOnOff(bt.toggleOnOff());
  update();
}

void MainFrame::onAmpOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qAmplifierButton->setState(state);
  update();
}

void MainFrame::onAmpGain(double val)
{
  ui->qGainDial->setValue(val);
  update();
}

void MainFrame::onEqOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qEQButton->setState(state);
  update();
}

void MainFrame::on_qVolumeDial_valueChanged(double physVal)
{
  mRig.applyVolume(physVal);
}

void MainFrame::onRigVolume(double volume)
{
  ui->qVolumeDial->setValue(volume);
  update();
}

void MainFrame::onRigStompsEnable(bool stompsEnable)
{
  QToasterButton::State state = stompsEnable ? QToasterButton::On : QToasterButton::Off;
  ui->qStompsButton->setState(state);
  update();
}

void MainFrame::onRigStackEnable(bool stackEnable)
{
  QToasterButton::State state = stackEnable ? QToasterButton::On : QToasterButton::Off;
  ui->qStackButton->setState(state);
  update();
}

void MainFrame::onRigEffectsEnable(bool effectsEnable)
{
  QToasterButton::State state = effectsEnable ? QToasterButton::On : QToasterButton::Off;
  ui->qEffectsButton->setState(state);
  update();
}

void MainFrame::on_qChickenHeadDial_valueChanged(const QChickenHeadDial::State& state)
{
  mGlobal.applyOperationMode((Global::OperationMode) state);
}

void MainFrame::onGlobalOperationMode(unsigned short opMode)
{
  ui->qChickenHeadDial->setState((QChickenHeadDial::State)opMode);
  update();
}

void MainFrame::on_qStompsButton_clicked(QToasterButton& bt, bool longClick)
{
  mRig.applyStompsEnable(bt.toggleOnOff());
  update();
}

void MainFrame::on_qStackButton_clicked(QToasterButton& bt, bool longClick)
{
  mRig.applyStackEnable(bt.toggleOnOff());
  update();
}

void MainFrame::on_qEffectsButton_clicked(QToasterButton& bt, bool longClick)
{
  mRig.applyEffectsEnable(bt.toggleOnOff());
  update();
}

void MainFrame::on_qEQButton_clicked(QToasterButton& bt, bool longClick)
{
  if(longClick)
    toggleOperationMode(EQEdit, &bt);
  else
    mEq.applyOnOff(bt.toggleOnOff());
  update();
}

void MainFrame::onCabOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qCabinetButton->setState(state);
  update();
}

void MainFrame::on_qCabinetButton_clicked(QToasterButton& bt, bool longClick)
{
  if(longClick)
    toggleOperationMode(CabEdit, &bt);
  else
    mCab.applyOnOff(bt.toggleOnOff());
  update();
}

void MainFrame::on_qMonitorVolumeDial_valueChanged(double volume)
{
  mGlobal.applyMonitorOutputVolume(volume);
}

void MainFrame::on_qHeadphoneVolumeDial_valueChanged(double volume)
{
  mGlobal.applyHeadphoneOutputVolume(volume);
}

void MainFrame::onGlobalMainVolume(double volume)
{
  update();
}

void MainFrame::onGlobalHeadphoneVolume(double volume)
{
  ui->qHeadphoneVolumeDial->setValue(volume);
  update();
}

void MainFrame::onGlobalMonitorVolume(double volume)
{
  ui->qMonitorVolumeDial->setValue(volume);
  update();
}

void MainFrame::onGlobalDirectVolume(double volume)
{
  update();
}

void MainFrame::on_qNoiseGateDial_valueChanged(double noiseGate)
{
  mInput.applyNoiseGate(noiseGate);
}

void MainFrame::on_qDistortionSenseDial_valueChanged(double distortionSense)
{
  mInput.applyDistortionSense(distortionSense);
}

void MainFrame::on_qCleanSenseDial_valueChanged(double cleanSense)
{
  mInput.applyCleanSense(cleanSense);
}

void MainFrame::onInputNoiseGate(double noiseGate)
{
  ui->qNoiseGateDial->setValue(noiseGate);
  update();
}

void MainFrame::onInputDistortionSense(double distortionSense)
{
  ui->qDistortionSenseDial->setValue(distortionSense);
  update();
}

void MainFrame::onInputCleanSense(double cleanSense)
{
  ui->qCleanSenseDial->setValue(cleanSense);
  update();
}

void MainFrame::on_qRigPrevButton_clicked(QToasterButton &bt, bool longClick)
{
  if(bt.state() == QToasterButton::On)
  {
    mProfile.applyRigPrev();
    requestValues(); // todo: request just the required values
  }
}

void MainFrame::on_qRigNextButton_clicked(QToasterButton &bt, bool longClick)
{
  if(bt.state() == QToasterButton::On)
  {
    mProfile.applyRigNext();
    requestValues(); // todo: request just the required values
  }
}

void MainFrame::on_qStompDelayButton_clicked(QToasterButton& bt, bool longClick)
{
  if(longClick)
  {
    toggleOperationMode(StompEdit, &bt);
  }
  else
  {
    mDelay.applyOnOffCutsTail(bt.toggleOnOff());
  }
  update();
}

void MainFrame::on_qStompReverbButton_clicked(QToasterButton& bt, bool longClick)
{
  if(longClick)
  {
    toggleOperationMode(StompEdit, &bt);
  }
  else
  {
    mReverb.applyOnOffCutsTail(bt.toggleOnOff());
  }
  update();
}

void MainFrame::on_qDelayFeedbackDial_valueChanged(double arg1)
{
  mDelay.applyFeedback(arg1);
}

void MainFrame::on_qDelayMixDial_valueChanged(double arg1)
{
    mDelay.applyMix(arg1);
}

void MainFrame::on_qReverbTimeDial_valueChanged(double arg1)
{
  mReverb.applyTime(arg1);
}

void MainFrame::on_qReverbMixDial_valueChanged(double arg1)
{
  mReverb.applyMix(arg1);
}

void MainFrame::onStompReverbTime(double time)
{
  ui->qReverbTimeDial->setValue(time);
}

void MainFrame::onStompReverbMix(double mix)
{
  ui->qReverbMixDial->setValue(mix);
}
