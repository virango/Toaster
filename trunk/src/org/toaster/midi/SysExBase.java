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
  // header
  protected static final byte[] syx                   = {(byte)0xF0};
  protected static final byte[] manufacturerID        = {0x00,0x20,0x33};
  protected static final byte[] productType           = {0x02};
  protected static final byte[] deviceID              = {0x7F};
  protected static final byte[] eox                   = {(byte)0xF7};
  protected static final byte[] header                = {(byte)0xF0,0x00,0x20,0x33,0x02,(byte)0x7F};
  
  protected static final byte[] instance              = {0x00};
  
  
    
  // function codes
  protected static final byte[] singleParamChange     = {0x01};
  protected static final byte[] multiParamChange      = {0x02};
  protected static final byte[] stringParam           = {0x03};
  protected static final byte[] BLOB                  = {0x04};
  protected static final byte[] extParamChange        = {0x06};
  protected static final byte[] extStringParamChange  = {0x07};
  protected static final byte[] reqSingleParamVal     = {0x41};
  protected static final byte[] reqMultiParamVals     = {0x42};
  protected static final byte[] reqStringParam        = {0x43};
  protected static final byte[] reqExtStringParam     = {0x47};
  
  protected void SysExBase(){
  }
  
  protected byte[] createSingleParamGetCmd(byte[] addressPage, byte[] param){
    return concatAll(header, reqSingleParamVal, instance, addressPage, param, eox);
  }
  
  protected byte[] createStringParamGetCmd(byte[] addressPage, byte[] param){
    return concatAll(header, reqStringParam, instance, addressPage, param, eox);
  }
  
  protected byte[] createSingleParamSetCmd(byte[] addressPage, byte[] param, byte[] val){
    return concatAll(header, singleParamChange, instance, addressPage, param, val, eox);
  }
  
  protected byte[] createStringParamSetCmd(byte[] addressPage, byte[] param, byte[] val){
    return concatAll(header, stringParam, instance, addressPage, param, val, eox);
  }
  
  protected boolean checkByteParams(byte[] first, byte[]... rest) {
    boolean result = false;
    if(first != null && first.length > 0) {
      result = true;
      for (byte[] array : rest) {
        if(array == null || array.length == 0) {
          result = false;
          break;
        }
      }
    }
    return result;
  }
  
  protected byte[] concatAll(byte[] first, byte[]... rest) {
    byte[] result = null;
    if(checkByteParams(first, rest)) {   
      int totalLength = first.length;
      for (byte[] array : rest) {
        totalLength += array.length;
      }
      result = Arrays.copyOf(first, totalLength);
      int offset = first.length;
      for (byte[] array : rest) {
        System.arraycopy(array, 0, result, offset, array.length);
        offset += array.length;
      }
    }
    return result;
  }
}
