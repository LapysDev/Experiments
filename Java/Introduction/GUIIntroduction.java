/* Import */
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

/* Application */
public class GUIIntroduction {
    /* Main */
    public static void main(String[] arguments) {
        // Constant > ...
        final JFrame FRAME = new JFrame("GUI Introduction");
          final JPanel BUTTON_PANEL = new JPanel();
            final JButton BUTTON = new JButton();

          final JPanel LABEL_PANEL = new JPanel();
            final JLabel LABEL = new JLabel("...");

        // Insertion
        FRAME.add(LABEL_PANEL);
        FRAME.add(BUTTON_PANEL);
          BUTTON_PANEL.add(BUTTON);
          BUTTON_PANEL.setLayout(new FlowLayout());

          LABEL_PANEL.add(LABEL);
          LABEL_PANEL.setLayout(new FlowLayout());

        // Update > ...
        BUTTON.addActionListener(new ActionListener() {
          @Override
          public void actionPerformed(ActionEvent event) {
            LABEL.setText("Hello, World!");
          }
        });
        BUTTON.setText("Hello");
        BUTTON_PANEL.setSize(500, 150);

        FRAME.setSize(500, 300);
        FRAME.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        FRAME.setLocationRelativeTo(null);
        FRAME.setVisible(true);

        LABEL_PANEL.setLocation(0, 150);
        LABEL_PANEL.setSize(500, 150);
    }
}
