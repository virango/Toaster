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
public class SystemSysEx extends SysExBase{
  // address page
  private static final byte[] addressPage = {0x7F};
  // parameter
  private static final byte[] mainOutputVolume = {0x00};
  private static final byte[] headphoneOutputVolume = {0x01};
  private static final byte[] monitorOutputVolume = {0x02};
  
  public void SystemSysEx() {
  }

  public byte[] requestMainOutputVolume(){
    return createSingleParamGetCmd(addressPage, mainOutputVolume);
  }
  
}
