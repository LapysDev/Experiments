/* Import */
import java.awt.*; // Java > Abstract Window Toolkit > All
import java.awt.event.*; // Java > Abstract Window Toolkit > Event > All

import javax.swing.*; // Java Extension > Swing > All

/* ... */
public class GUI {
    /* Main */
    public static void main(String[] arguments) {
        // Constant > ...
        TextField output = new TextField("Placeholder");
        Label footer = new Label("Copyright © Lapys, 2020");
        Label title = new Label("Header");
        Frame window = new Frame("Java Application");

        // Insertion
        window.add(title);
        window.add(output);
        window.add(footer);

        // Modification
            // Footer > ...
            footer.setHorizontalAlignment(JLabel.CENTER);
            footer.setPreferredSize(new Dimension(650, 20));

            // Output > ...
            output.setEditable(false);
            output.setPreferredSize(new Dimension(650, 30));

            // Title > ...
            title.setHorizontalAlignment(JLabel.CENTER);
            title.setPreferredSize(new Dimension(650, 20));

            // Window > ...
            window.setBackground(Color.DARK_GRAY);
            window.setFont(Font.getFont(Font.SERIF));
            window.setFont(new Font("Google Sans", Font.BOLD, 20));
            window.setForeground(Color.WHITE);
            window.setLayout(new FlowLayout());
            window.setLocation(0, 0);
            window.setSize(700, 200);
            window.setVisible(true);

        // Event > ...
        window.addWindowListener(new WindowAdapter() {public void windowClosing(WindowEvent event) { System.exit(0); }});
    }
}
