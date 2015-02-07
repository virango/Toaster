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
public class RigSysEx extends SysExBase {
  // address page
  private static final byte[] addressPage = {0x04};
  private static final byte[] addressPageName = {0x00};
  // parameter
  private static final byte[] name = {0x01};
  private static final byte[] tempo = {0x00};
  private static final byte[] volume = {0x01};
  private static final byte[] tempoEnable = {0x02};
  
  public void RigSysEx() {
  }
  
  public byte[] requestRigName(){
    return createStringParamGetCmd(addressPageName, name);
  }
}
