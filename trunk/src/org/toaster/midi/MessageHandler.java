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
public class MessageHandler implements InputConsumer{
  protected static final byte syx = (byte)0xF0;
  @Override
  public byte getStatusByte() {
    return syx;
  }

  @Override
  public void consume(byte[] msg) {
    System.out.print("Msg: ");
    for(int i = 0; i < msg.length; i++){
      System.out.printf("0x%X ", msg[i]);
    }
    System.out.println();
  }

  
}
