
import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortEvent;
import com.fazecast.jSerialComm.SerialPortPacketListener;

import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.JFrame;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.geom.Ellipse2D;

public final class PacketListener implements SerialPortPacketListener{
	SerialPort serialPort = null;
	PrintWriter output = null;
	JFrame game = null;
	Scanner input = null;
	String[] displayout = new String[8];
	byte[] trash = new byte[30];
	GameGraphics gg = null;
	
	GameKeyListener keylisten = null;
	private char inputs_out = 'A';
	
	
	public PacketListener(PrintWriter out){
		output = out;
		
		keylisten = new GameKeyListener();
		game = new JFrame();
		game.setSize(720, 720);
		game.setTitle("GameGuy DOT");
		game.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		game.setVisible(true);
		game.addKeyListener(keylisten);
		
		gg = new GameGraphics();
		game.add(gg);
		//gg.changecolor();
		//gg.repaint();
		//game.remove(gg);
		//game.add(gg);
	}
	
    @Override
    public int getListeningEvents() {
        return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
    }

    @Override
    public int getPacketSize() {
        return 20;
    }

    @Override
    public void serialEvent(SerialPortEvent event) {
        byte[] newData = event.getReceivedData();
        
        //String str = new String(newData);
        String str = new String(newData).split("\n", 2)[0];
        int byteSize = 0;
        try {
            byteSize = str.getBytes("UTF-8").length;
        } catch (UnsupportedEncodingException ex) {
            Logger.getLogger(PacketListener.class.getName()).log(Level.SEVERE, null, ex);
        }
        if (byteSize == 20 && str.startsWith("DOT:")) {
            System.out.println("(Received data of size: " + byteSize + ")" + str);
            for(int i=0; i<8; i++) {
            	displayout[i] = Integer.toBinaryString(Integer.parseInt(str.substring(4+(2*i), 6+(2*i)), 16));
            	System.out.println("Row "+ i+": " + displayout[i]);
            	
            	
            	
            	
            	
            }
            inputs_out = keylisten.getPlayerInputs();
            System.out.println("Sending Player inputs: " + Integer.toHexString(inputs_out));
            //serialPort.writeBytes(keylisten.getPlayerInputs(), 10);
            output.print(inputs_out);
        	output.flush();
            gg.updateDots(displayout);
            gg.repaint();
            
        }
        
        
    }
   
}
