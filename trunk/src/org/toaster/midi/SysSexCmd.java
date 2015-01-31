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
public class SysSexCmd {
  private final byte[] syx = {(byte)0xF0};
  private final byte[] manufacturerID = {0x00, 0x20, 0x33};
  private final byte[] productType = {0x02};
  private final byte[] deviceID = {0x7F};
  private final byte[] eox = {(byte)0xF7};
    
  // function codes
  private final byte[] singleParameterChange = {0x01};
  private final byte[] multiParameterChange = {0x02};
  private final byte[] stringParameter = {0x03};
  private final byte[] BLOB = {0x04};
  private final byte[] extendedParameterChange = {0x06};
  private final byte[] extendedStringParameterChange = {0x07};
  
  // rig
  private final byte[] rigAddressPage = {0x04};
  private final byte[] rigTempo = {0x00};
  
  private byte[] concatAll(byte[] first, byte[]... rest) {
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
  
  private byte[] Header(){
    return concatAll(syx, manufacturerID, productType, deviceID);
  }
}
