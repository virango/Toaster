/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package org.toaster.midi.jack;

import java.util.EnumSet;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jaudiolibs.jnajack.Jack;
import org.jaudiolibs.jnajack.JackClient;
import org.jaudiolibs.jnajack.JackException;
import org.jaudiolibs.jnajack.JackMidi;
import org.jaudiolibs.jnajack.JackOptions;
import org.jaudiolibs.jnajack.JackPort;
import org.jaudiolibs.jnajack.JackPortFlags;
import org.jaudiolibs.jnajack.JackPortType;
import org.jaudiolibs.jnajack.JackProcessCallback;
import org.jaudiolibs.jnajack.JackShutdownCallback;
import org.jaudiolibs.jnajack.JackStatus;

/**
 *
 * @author tholan
 */
public class JackMidiSender implements JackProcessCallback, JackShutdownCallback {
  private JackClient client = null;
  private JackPort outputPort = null;
  private byte[] sendData = null; 
  private final String clientName = "Toaster";
  
  public JackMidiSender() throws JackException {
    EnumSet<JackStatus> status = EnumSet.noneOf(JackStatus.class);
    try {
        Jack jack = Jack.getInstance();
        client = jack.openClient(clientName, EnumSet.of(JackOptions.JackNoStartServer), status);
        if (!status.isEmpty()) {
            System.out.println("JACK client status : " + status);
        }
        outputPort = client.registerPort("MIDI out", JackPortType.MIDI, JackPortFlags.JackPortIsOutput);
        
        activate();
    } catch (JackException ex) {
        if (!status.isEmpty()) {
            System.out.println("JACK exception client status : " + status);
        }
        throw ex;
    }
  }
  
  public void activate() throws JackException {
        client.setProcessCallback(this);
        client.onShutdown(this);
        client.activate();
    }
  
  public void send(byte[] data) {
    sendData = data;
  }
          

  @Override
  public boolean process(JackClient client, int nframes) {
    try {
      JackMidi.clearBuffer(outputPort);
      if(sendData != null) {
        JackMidi.eventWrite(outputPort, 0, sendData, sendData.length);
        sendData = null;
      }
    } catch (JackException ex) {
      Logger.getLogger(JackMidiSender.class.getName()).log(Level.SEVERE, null, ex);
      return false;
    }
    return true;
  }

  @Override
  public void clientShutdown(JackClient client) {
    System.out.println("Java MIDI thru test shutdown");
  }
}
