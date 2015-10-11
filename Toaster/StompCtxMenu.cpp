#include <QMenu>
#include "Stomp.h"
#include "StompCtxMenu.h"

StompCtxMenu::StompCtxMenu(Stomp& stomp)
  : mStomp(stomp)
{
  createWahMenu();
  createDistortionMenu();
  createEQMenu();
  createCompGateMenu();
  createChorusMenu();
  createPhaserFlangerMenu();
  createPitchShifterMenu();
  createEffectLoopMenu();
  createDelayReverbMenu();
}

void StompCtxMenu::createMenu(QMenu& menu)
{
  QAction* action = menu.addAction("None");
  action->setData(QVariant((unsigned int)None));
  connect(&menu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  menu.addMenu(&mWahMenu);
  menu.addMenu(&mDistortionMenu);
  menu.addMenu(&mEQMenu);
  menu.addMenu(&mCompGateMenu);
  menu.addMenu(&mChorusMenu);
  menu.addMenu(&mPhaserFlangerMenu);
  menu.addMenu(&mPitchShifterMenu);
  menu.addMenu(&mEffectLoopMenu);
  menu.addMenu(&mDelayReverbMenu);
}

void StompCtxMenu::createWahMenu()
{
  mWahMenu.setTitle("Wah");
  connect(&mWahMenu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  QAction* action = mWahMenu.addAction("Wah Wah");
  action->setData(QVariant((unsigned int)WahWah));

  action = mWahMenu.addAction("Wah Low Pass");
  action->setData(QVariant((unsigned int)WahLowPass));

  action = mWahMenu.addAction("Wah High Pass");
  action->setData(QVariant((unsigned int)WahHighPass));

  action = mWahMenu.addAction("Wah Vowel Filter");
  action->setData(QVariant((unsigned int)WahVowelFilter));

  action = mWahMenu.addAction("Wah Phaser");
  action->setData(QVariant((unsigned int)WahPhaser));

  action = mWahMenu.addAction("Wah Flanger");
  action->setData(QVariant((unsigned int)WahFlanger));

  action = mWahMenu.addAction("Wah Rate Reducer");
  action->setData(QVariant((unsigned int)WahRateReducer));

  action = mWahMenu.addAction("Wah Ring Modulator");
  action->setData(QVariant((unsigned int)WahRingModulator));

  action = mWahMenu.addAction("Wah Frequency Shifter");
  action->setData(QVariant((unsigned int)WahFrequencyShifter));

  action = mWahMenu.addAction("Wah Formant Shifter");
  action->setData(QVariant((unsigned int)WahFormantShifter));
}

void StompCtxMenu::createDistortionMenu()
{
  mDistortionMenu.setTitle("Distortion");
  connect(&mDistortionMenu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  QAction* action = mDistortionMenu.addAction("Bit Shaper");
  action->setData(QVariant((unsigned int)BitShaper));

  action = mDistortionMenu.addAction("Recti Shaper");
  action->setData(QVariant((unsigned int)RectiShaper));

  action = mDistortionMenu.addAction("Soft Shaper");
  action->setData(QVariant((unsigned int)SoftShaper));

  action = mDistortionMenu.addAction("Hard Shaper");
  action->setData(QVariant((unsigned int)HardShaper));

  action = mDistortionMenu.addAction("Wave Shaper");
  action->setData(QVariant((unsigned int)WaveShaper));

  action = mDistortionMenu.addAction("Green Scream");
  action->setData(QVariant((unsigned int)GreenScream));

  action = mDistortionMenu.addAction("Plus DS");
  action->setData(QVariant((unsigned int)PlusDS));

  action = mDistortionMenu.addAction("One DS");
  action->setData(QVariant((unsigned int)OneDS));

  action = mDistortionMenu.addAction("Muffin");
  action->setData(QVariant((unsigned int)Muffin));

  action = mDistortionMenu.addAction("Mouse DS");
  action->setData(QVariant((unsigned int)MouseDS));

  action = mDistortionMenu.addAction("Fuzz DS");
  action->setData(QVariant((unsigned int)FuzzDS));

  action = mDistortionMenu.addAction("Metal DS");
  action->setData(QVariant((unsigned int)MetalDS));

  action = mDistortionMenu.addAction("Treble Booster");
  action->setData(QVariant((unsigned int)TrebleBooster));

  action = mDistortionMenu.addAction("Lead Booster");
  action->setData(QVariant((unsigned int)LeadBooster));

  action = mDistortionMenu.addAction("Pure Booster");
  action->setData(QVariant((unsigned int)PureBooster));

  action = mDistortionMenu.addAction("Wah Pedal Booster");
  action->setData(QVariant((unsigned int)WahPedalBooster));
}

void StompCtxMenu::createEQMenu()
{
  mEQMenu.setTitle("EQ");
  connect(&mEQMenu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  QAction* action = mEQMenu.addAction("Graphic Equalizer");
  action->setData(QVariant((unsigned int)GraphicEqualizer));

  action = mEQMenu.addAction("Studio Equalizer");
  action->setData(QVariant((unsigned int)StudioEqualizer));

  action = mEQMenu.addAction("Metal Equalizer");
  action->setData(QVariant((unsigned int)MetalEqualizer));

  action = mEQMenu.addAction("Stereo Weidener");
  action->setData(QVariant((unsigned int)StereoWeidener));
}

void StompCtxMenu::createCompGateMenu()
{
  mCompGateMenu.setTitle("Compressor/Gate");
  connect(&mCompGateMenu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  QAction* action = mCompGateMenu.addAction("Compressor");
  action->setData(QVariant((unsigned int)Compressor));

  action = mCompGateMenu.addAction("Noise Gate 2:1");
  action->setData(QVariant((unsigned int)NoiseGate21));

  action = mCompGateMenu.addAction("Noise Gate 4:1");
  action->setData(QVariant((unsigned int)NoiseGate41));
}

void StompCtxMenu::createChorusMenu()
{
  mChorusMenu.setTitle("Chorus");
  connect(&mChorusMenu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  QAction* action = mChorusMenu.addAction("Vintage Chorus");
  action->setData(QVariant((unsigned int)VintageChorus));

  action = mChorusMenu.addAction("Hyper Chorus");
  action->setData(QVariant((unsigned int)HyperChorus));

  action = mChorusMenu.addAction("Air Chorus");
  action->setData(QVariant((unsigned int)AirChorus));

  action = mChorusMenu.addAction("Micro Pitch");
  action->setData(QVariant((unsigned int)MicroPitch));

  action = mChorusMenu.addAction("Vibrato");
  action->setData(QVariant((unsigned int)Vibrato));

  action = mChorusMenu.addAction("Rotary Speaker");
  action->setData(QVariant((unsigned int)RotarySpeaker));

  action = mChorusMenu.addAction("Tremolo");
  action->setData(QVariant((unsigned int)Tremolo));
}

void StompCtxMenu::createPhaserFlangerMenu()
{
  mPhaserFlangerMenu.setTitle("Phaser/Flanger");
  connect(&mPhaserFlangerMenu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  QAction* action = mPhaserFlangerMenu.addAction("Phaser");
  action->setData(QVariant((unsigned int)Phaser));

  action = mPhaserFlangerMenu.addAction("Phaser Vibe");
  action->setData(QVariant((unsigned int)PhaserVibe));

  action = mPhaserFlangerMenu.addAction("Phaser Oneway");
  action->setData(QVariant((unsigned int)PhaserOneway));

  action = mPhaserFlangerMenu.addAction("Flanger");
  action->setData(QVariant((unsigned int)Flanger));

  action = mPhaserFlangerMenu.addAction("Flanger Oneway");
  action->setData(QVariant((unsigned int)FlangerOneway));
}

void StompCtxMenu::createPitchShifterMenu()
{
  mPitchShifterMenu.setTitle("Pitch Shifter");
  connect(&mPitchShifterMenu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  QAction* action = mPitchShifterMenu.addAction("Transpose");
  action->setData(QVariant((unsigned int)Transpose));

  action = mPitchShifterMenu.addAction("Pedal Pitch");
  action->setData(QVariant((unsigned int)PedalPitch));

  action = mPitchShifterMenu.addAction("Pedal Vinyl Stop");
  action->setData(QVariant((unsigned int)PedalVinylStop));

  action = mPitchShifterMenu.addAction("Chromatic Pitch");
  action->setData(QVariant((unsigned int)ChromaticPitch));

  action = mPitchShifterMenu.addAction("Harmonic Pitch");
  action->setData(QVariant((unsigned int)HarmonicPitch));

  action = mPitchShifterMenu.addAction("Analog Octaver");
  action->setData(QVariant((unsigned int)AnalogOctaver));
}

void StompCtxMenu::createEffectLoopMenu()
{
  mEffectLoopMenu.setTitle("Effect Loop");
  connect(&mEffectLoopMenu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  QAction* action = mEffectLoopMenu.addAction("Loop Mono");
  action->setData(QVariant((unsigned int)LoopMono));

  action = mEffectLoopMenu.addAction("Loop Stereo");
  action->setData(QVariant((unsigned int)LoopStereo));

  action = mEffectLoopMenu.addAction("Loop Distortion");
  action->setData(QVariant((unsigned int)LoopDistortion));
}

void StompCtxMenu::createDelayReverbMenu()
{
  mDelayReverbMenu.setTitle("Delay/Reverb");
  connect(&mDelayReverbMenu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  QAction* action = mDelayReverbMenu.addAction("Space");
  action->setData(QVariant((unsigned int)Space));
}


void StompCtxMenu::setType(QAction* action)
{
  FXType fxType = (FXType)action->data().toUInt();
  mStomp.applyType(fxType);
}
