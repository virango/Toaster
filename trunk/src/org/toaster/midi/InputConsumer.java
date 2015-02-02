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
public interface InputConsumer {
  public byte getStatusByte();
  public void consume(byte[] msg);
}
