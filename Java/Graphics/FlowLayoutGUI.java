/* Import > ... */
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

/* Flow Layout */
public class FlowLayoutGUI {
    /* Main */
    public static void main(String[] args) {
        final JFrame frame = new JFrame();
        final JPanel panel = new JPanel();

        // ...
        frame.add(panel);

        panel.add(new JButton("A"));
        panel.add(new JButton("B"));
        panel.add(new JButton("C"));

        // ...
        frame.setBackground(new Color(127, 0, 127));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(null);
        frame.setSize(new Dimension(500, 500));
        frame.setVisible(true);

        panel.setBackground(new Color(0, 127, 255));
        panel.setLayout(new FlowLayout(FlowLayout.RIGHT, 0, 0));
        panel.setLocation(0, 0);
        panel.setSize(new Dimension(300, 300));
    }
};
