/* Import */
import java.awt.*; // Java > Abstract Window Toolkit > All
import java.awt.event.*; // Java > Abstract Window Toolkit > Event > All

import javax.swing.JLabel; // Java Extension > Swing > Java Label

/* ... */
public class Demo3 {
    /* Main */
    public static void main(String[] arguments) {
        // Constant > (Label, Window)
        Label label = new Label();
        Frame window = new Frame("Demo 3");

        // Insertion
        window.add(label);

        // Modification
            // Label > ...
            label.setText("Hello, World!");

            // Window > ...
            window.setLayout(new GridLayout(1, 1));
            window.setSize(400, 400);
            window.setVisible(true);

        // Event > Window > Close
        window.addWindowListener(new WindowAdapter() {
            // Function > Window Closing
            public void windowClosing(WindowEvent event){
                // System > Exit
                System.exit(0);
            }
        });
    }
}
