/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package org.toaster.midi.jack;

import java.util.EnumSet;
import java.util.LinkedList;
import java.util.List;
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
import org.toaster.midi.InputConsumer;

/**
 *
 * @author tholan
 */
public class Client implements JackProcessCallback, JackShutdownCallback {
  private JackClient client = null;
  private JackPort inputPort = null;
  private JackPort outputPort = null;
  private JackMidi.Event midiEvent = null; 
  private final String clientName = "Toaster";
  private List<InputConsumer> inputConsumerList = null;
  private byte[] outputData = null;
  private byte[] inputData = null;
  
  public Client() throws JackException {
    EnumSet<JackStatus> status = EnumSet.noneOf(JackStatus.class);
    try {
        Jack jack = Jack.getInstance();
        client = jack.openClient(clientName, EnumSet.of(JackOptions.JackNoStartServer), status);
        if (!status.isEmpty()) {
            System.out.println("JACK client status : " + status);
        }
        outputPort = client.registerPort("MIDI out", JackPortType.MIDI, JackPortFlags.JackPortIsOutput);
        inputPort = client.registerPort("MIDI in", JackPortType.MIDI, JackPortFlags.JackPortIsInput);
        midiEvent = new JackMidi.Event();
        inputConsumerList = new LinkedList<>();
        inputData = new byte[1000];
        activate();
    } catch (JackException ex) {
        if (!status.isEmpty()) {
            System.out.println("JACK exception client status : " + status);
        }
        throw ex;
    }
  }
  
  public void addInputConsumer(InputConsumer inputConsumer) {
    if(inputConsumer != null)
      inputConsumerList.add(inputConsumer);
  }
  
  public final void activate() throws JackException {
    client.setProcessCallback(this);
    client.onShutdown(this);
    client.activate();
  }
  
  public void send(byte[] data) {
    outputData = data;
  }
          
  @Override
  public boolean process(JackClient client, int nframes) {
    try {
      
      JackMidi.clearBuffer(outputPort);
      int eventCount = JackMidi.getEventCount(inputPort);
      for (int i = 0; i < eventCount; ++i) {
        JackMidi.eventGet(midiEvent, inputPort, i);
        int size = midiEvent.size();
        if (inputData == null || inputData.length < size) {
            inputData = new byte[size];
        }
        midiEvent.read(inputData);
        for(int j = 0; i < inputConsumerList.size(); ++i) {
          InputConsumer inputConsumer = inputConsumerList.get(j);
          if(inputData[0] == inputConsumer.getStatusByte())
          {
            inputConsumer.consume(inputData);
            inputData = null;
          }
        }  
      }
      
      if(outputData != null) {
          JackMidi.eventWrite(outputPort, 0, outputData, outputData.length);
          outputData = null;
      }
    } catch (JackException ex) {
      Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
      return false;
    }
    return true;
  }

  @Override
  public void clientShutdown(JackClient client) {
    System.out.println("Java MIDI thru test shutdown");
  }
}
