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
  private static final byte[] addressPageA = {0x32};
  private static final byte[] addressPageB = {0x33};
  private static final byte[] addressPageC = {0x34};
  private static final byte[] addressPageD = {0x35};
  private static final byte[] addressPageX = {0x38};
  private static final byte[] addressPageMOD = {0x5A};
  
  // parameter
  private static final byte[] type = {0x00};
  private static final byte[] onOff = {0x03};
  
  public void StompsSysEx() {
  }
  
  public byte[] switchStomp(Stomp stomp, boolean onOff){
    byte[] val = {0x00, 0x00};
    if(onOff)
      val[1] = 0x01;
    byte[] addressPage = getAddressPage(stomp);
    return concatAll(header(), singleParamChange, instance, addressPage, this.onOff, val, eox);
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
