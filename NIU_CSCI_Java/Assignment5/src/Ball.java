import javax.swing.*;
import java.awt.*;

public class Ball extends JPanel {

    boolean animate = true;
    boolean current;
    boolean cut;

    long time = 10;
    Color color;
    // Ball Size
    float radius = 15;
    float diameter = radius * 2;

    // Center of Call
    float X = radius + 50;
    float Y = radius + 20;

    float horizontalMovement = 1;
    float verticalMovement = 1;

    public void draw(Graphics g) {

        if(current) {
            g.setColor(color);
            g.fillOval((int) (X - radius), (int) (Y - radius), (int) diameter, (int) diameter);
            g.setColor(Color.black);
            g.drawOval((int) (X - radius), (int) (Y - radius), (int) diameter, (int) diameter);
        }
        else
        {
            g.setColor(color);
            g.drawOval((int) (X - radius), (int) (Y - radius), (int) diameter, (int) diameter);
            g.setColor(Color.white);
            g.fillOval((int) (X - radius), (int) (Y - radius), (int) diameter, (int) diameter);
        }
    }
}