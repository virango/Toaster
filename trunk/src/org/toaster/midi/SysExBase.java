/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.toaster.midi;

import java.util.Arrays;

/**
 *
 * @author tholan
 */
public class SysExBase {
  protected static final byte[] syx = {(byte)0xF0};
  protected static final byte[] manufacturerID = {0x00, 0x20, 0x33};
  protected static final byte[] productType = {0x02};
  protected static final byte[] deviceID = {0x7F};
  protected static final byte[] eox = {(byte)0xF7};
  
  protected static final byte[] instance = {0x00};
    
  // function codes
  protected static final byte[] singleParamChange = {0x01};
  protected static final byte[] multiParamChange = {0x02};
  protected static final byte[] stringParam = {0x03};
  protected static final byte[] BLOB = {0x04};
  protected static final byte[] extParamChange = {0x06};
  protected static final byte[] extStringParamChange = {0x07};
  
  protected void SysExBase(){
  }
   
  protected byte[] concatAll(byte[] first, byte[]... rest) {
    int totalLength = first.length;
    for (byte[] array : rest) {
      totalLength += array.length;
    }
    byte[] result = Arrays.copyOf(first, totalLength);
    int offset = first.length;
    for (byte[] array : rest) {
      System.arraycopy(array, 0, result, offset, array.length);
      offset += array.length;
    }
    return result;
  }
  
  protected byte[] header(){
    return concatAll(syx, manufacturerID, productType, deviceID);
  }
}
