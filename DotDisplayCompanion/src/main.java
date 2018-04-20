
/*import java.util.Scanner;

import javax.swing.JFrame;
import javax.swing.JSlider;
import com.fazecast.jSerialComm.*;

public class main {
	public static int packetSize=7;
	

	public static void main(String[] args) {

		SerialPort[] ports = SerialPort.getCommPorts();
		System.out.println("Select a port:");
		int i = 1;
		for(SerialPort port : ports)
			System.out.println(i++ +  ": " + port.getSystemPortName());
		Scanner s = new Scanner(System.in);
		int chosenPort = s.nextInt();

		SerialPort serialPort = ports[chosenPort - 1];
		if(serialPort.openPort())
			System.out.println("Port opened successfully.");
		else {
			System.out.println("Unable to open the port.");
			return;
		}
		//serialPort.setComPortParameters(9600, 8, 1, SerialPort.NO_PARITY);
		//serialPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_BLOCKING, 0, 0);
		
		PacketListener listener = new PacketListener();
		serialPort.addDataListener(listener);
		
		System.out.println("Done.");
		
		
		System.out.println("Port Closed");
	}

}*/

import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;
import com.fazecast.jSerialComm.*;

public class main{

	
	private static PacketListener gamelistener = null;

	public static void main(String[] args) {
		
		
		
		SerialPort[] ports = SerialPort.getCommPorts();
		System.out.println("Select a port:");
		int i = 1;
		for(SerialPort port : ports)
			System.out.println(i++ +  ": " + port.getSystemPortName());
		Scanner s = new Scanner(System.in);
		int chosenPort = s.nextInt();

		SerialPort serialPort = ports[chosenPort - 1];
		if(serialPort.openPort())
			System.out.println("Port opened successfully.");
		else {
			System.out.println("Unable to open the port.");
			return;
		}
		//serialPort.setComPortParameters(9600, 8, 1, SerialPort.NO_PARITY);
		serialPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 0, 0);

		//data.close();
		/*while(data.hasNextLine()){
			System.out.print("data");
			System.out.println(data.nextLine());
		}*/
		PrintWriter output = new PrintWriter(serialPort.getOutputStream());
		gamelistener = new PacketListener(output);
        serialPort.addDataListener(gamelistener);
		
		//serialPort.closePort();
		System.out.println("Done.");
	}


}