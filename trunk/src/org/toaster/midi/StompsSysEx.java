/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package org.toaster.midi;

/**
 *
 * @author tholan
 */
public class StompsSysEx extends SysExBase{
  public enum Stomp {
    A,B,C,D,X,MOD
  }
  // address pages
  private static final byte[] addressPageA                = {0x32};
  private static final byte[] addressPageB                = {0x33};
  private static final byte[] addressPageC                = {0x34};
  private static final byte[] addressPageD                = {0x35};
  private static final byte[] addressPageX                = {0x38};
  private static final byte[] addressPageMOD              = {0x5A};
  // parameter
  private static final byte[] type                        = {0x00};
  private static final byte[] onOff                       = {0x03};
  private static final byte[] mix                         = {0x04};
  private static final byte[] volume                      = {0x06};
  private static final byte[] stereo                      = {0x07};
  private static final byte[] wahManual                   = {0x08};
  private static final byte[] wahPeak                     = {0x09};
  private static final byte[] wahRange                    = {0x0A};
  private static final byte[] wahPedalMode                = {0x0C};
  private static final byte[] wahTouchAttack              = {0x0D};
  private static final byte[] wahTouchRelease             = {0x0E};
  private static final byte[] wahTouchBoost               = {0x0F};
  private static final byte[] distortionShaperDrive       = {0x10};
  private static final byte[] distortionBoosterTone       = {0x11};
  private static final byte[] compressorGateIntensity     = {0x12};
  private static final byte[] compressorAttack            = {0x13};
  private static final byte[] modulationRate              = {0x14};
  private static final byte[] modulationDepth             = {0x15};
  private static final byte[] modulationFeedback          = {0x16};
  private static final byte[] modulationCrossover         = {0x17};
  private static final byte[] modulationHyperChorusAmount = {0x18};
  private static final byte[] modulationManual            = {0x19};
  private static final byte[] modulationPhaserPeakSpread  = {0x1A};
  private static final byte[] modulationPhaserStages      = {0x1B};
  private static final byte[] rotarySpeed                 = {0x1E};
  private static final byte[] rotaryDistance              = {0x1F};
  private static final byte[] rotaryBalance               = {0x20};
  private static final byte[] compressorSquash            = {0x21};
  private static final byte[] graphicEQBand1              = {0x22};
  private static final byte[] graphicEQBand2              = {0x23};
  private static final byte[] graphicEQBand3              = {0x24};
  private static final byte[] graphicEQBand4              = {0x25};
  private static final byte[] graphicEQBand5              = {0x26};
  private static final byte[] graphicEQBand6              = {0x27};
  private static final byte[] graphicEQBand7              = {0x28};
  private static final byte[] graphicEQBand8              = {0x29};
  private static final byte[] parametricEQLowGain         = {0x2A};
  private static final byte[] parametricEQLowFrequency    = {0x2B};
  private static final byte[] parametricEQHighGain        = {0x2C};
  private static final byte[] parametricEQHighFrequency   = {0x2D};
  private static final byte[] parametricEQPeakGain        = {0x2E};
  private static final byte[] parametricEQPeakFrequency   = {0x2F};
  private static final byte[] parametricEQPeakQFactor     = {0x30};
  private static final byte[] parametricEQPeakGain2       = {0x31};
  private static final byte[] parametricEQPeakFrequency2  = {0x32};
  private static final byte[] parametricEQPeakQFactor2    = {0x33};
  private static final byte[] wahPeakRange                = {0x34};
  private static final byte[] ducking                     = {0x35};
  private static final byte[] voiceMix                    = {0x37};
  private static final byte[] voice1Pitch                 = {0x38};
  private static final byte[] voice2Pitch                 = {0x39};
  private static final byte[] detune                      = {0x3A};
  private static final byte[] smoothChords                = {0x3C};
  private static final byte[] pureTuning                  = {0x3D};
  private static final byte[] key                         = {0x40};
  
  public void StompsSysEx() {
  }
  
  public byte[] switchStomp(Stomp stomp, boolean onOff){
    byte[] val = {0x00, 0x00};
    if(onOff)
      val[1] = 0x01;
    return createSingleParamSetCmd(getAddressPage(stomp), this.onOff, val);
  }
  
  public byte[] requestType(Stomp stomp){
    return createSingleParamGetCmd(getAddressPage(stomp), this.type);
  }
  
  public byte[] requestOnOffState(Stomp stomp) {
    return createSingleParamGetCmd(getAddressPage(stomp), this.onOff);
  }
    
  private byte[] getAddressPage(Stomp stomp){
    switch(stomp) {
      case A:
        return addressPageA;
      case B:
        return addressPageB;
      case C:
        return addressPageC;
      case D:
        return addressPageD;
      case X:
        return addressPageX;
      case MOD:
        return addressPageMOD;
    }
    return null;
  }
}
