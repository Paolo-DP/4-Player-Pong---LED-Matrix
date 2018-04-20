import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JComponent;
import java.awt.geom.Ellipse2D;
import java.awt.Rectangle;

public class GameGraphics extends JComponent{
	Color green = new Color(0,240,40);
	Color gray = new Color(220,220,220);
	Color black = new Color(50,50,50);
	Ellipse2D[][] dots = new Ellipse2D[8][8];
	boolean[][] dotIsLit = new boolean[8][8];
	
	public GameGraphics() {
		for(int i=0; i<8; i++) {
			for(int j=0; j<8; j++) {
				dots[i][j] = null;
				dotIsLit[i][j] = false;
			}
		}
	}
	
	public void paintComponent(Graphics g) {
		Graphics2D display = (Graphics2D) g;
		Rectangle backg = new Rectangle(0,0,720,720);
		
		display.setColor(black);
		display.fill(backg);
		
		for(int i=0; i<8; i++) {
			for(int j=0; j<8; j++) {
				if(dotIsLit[i][j]) 
					display.setColor(green);
				else
					display.setColor(gray);
				dots[i][j] = new Ellipse2D.Float(85*(j)+5, 85*(i)+5, 65,65);
				display.fill(dots[i][j]);
			}
		}
	}
	
	public void updateDots(String[] lit) {
		for(int i=0; i<8; i++) {
			for(int j=0; j<8; j++) {
				if(j<(8-lit[i].length()))
					dotIsLit[i][j]=true;
				else
					dotIsLit[i][j] = (lit[i].charAt(j-(8-lit[i].length())) == '0');
			}
		}
		
	}
	
}
