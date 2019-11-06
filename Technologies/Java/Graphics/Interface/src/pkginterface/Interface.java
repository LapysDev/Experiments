/* Packages */
package pkginterface;

/* Import */
import java.awt.*; // Java > Abstract Window Toolkit > [All]
import java.awt.event.*;

import javax.swing.*; // Java > Swing > [All]

/* ... */
public class Interface {
    /* Main */
    public static void main(String[] args) {
        // Constant > Window
        Frame window = new Frame("Java Application");
        
        // Modification > Window > ...
        window.setSize(400, 400);
        window.setVisible(true);

        // Event > Window > ...
        window.addWindowListener(new WindowAdapter() {public void windowClosing(WindowEvent event) { System.exit(0); }});
    }
}
