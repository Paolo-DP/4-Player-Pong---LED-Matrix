import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;

public class GameKeyListener implements KeyListener{
	private ArrayList<Integer> keysdown = new ArrayList();
	private Integer A_key = 65, W_key = 87, S_key = 83, D_key = 68;
	private Integer Up_key = 38, Down_key = 40, Left_key = 37, Right_key = 39;
	private Integer Space_key = 32, Ctrl_key = 17;
	
	private char player_inputs= 0;
	
	@Override
	public void keyPressed(KeyEvent arg0) {
		// TODO Auto-generated method stub
		if(!keysdown.contains(arg0.getKeyCode()))
			keysdown.add(new Integer(arg0.getKeyCode()));
		System.out.println(arg0.getKeyCode());
		
		updatePlayerInputs();
	}

	@Override
	public void keyReleased(KeyEvent arg0) {
		if(keysdown.contains(arg0.getKeyCode()))
			keysdown.remove(new Integer(arg0.getKeyCode()));
		System.out.println(arg0.getKeyCode());
		
		updatePlayerInputs();
	}

	@Override
	public void keyTyped(KeyEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	
	public char getPlayerInputs() {
		/*byte[] b = new byte[player_inputs.length];
		for (int i = 0; i < b.length; i++) {
			b[i] = (byte) player_inputs[i];
		}
		return b;*/
		return player_inputs;
	}
	
	private void updatePlayerInputs() {
		player_inputs=0;
    	if(keysdown.contains(W_key) || keysdown.contains(A_key))
    		player_inputs+=0x20;
    	
    	
    	if(keysdown.contains(Space_key))
    		player_inputs+=0x10;
    	
    	
    	if(keysdown.contains(S_key) || keysdown.contains(D_key))
    		player_inputs+=0x08;
    	
    	
    	if(keysdown.contains(Down_key) || keysdown.contains(Left_key))
    		player_inputs+=0x04;
    	
    	
    	if(keysdown.contains(Ctrl_key))
    		player_inputs+=0x02;
    	
    	
    	if(keysdown.contains(Up_key) || keysdown.contains(Right_key))
    		player_inputs+=0x01;
    	
    	
    	System.out.println("Player input: " + Integer.toBinaryString(player_inputs) + " Hex: " + Integer.toHexString(player_inputs));
    }

}
