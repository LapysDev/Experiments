/* Import */
import java.awt.*; // Java > Abstract Window Toolkit > All
import java.awt.event.*; // Java > Abstract Window Toolkit > Event > All

import javax.swing.*; // Java Extension > Swing > All

/* ... */
public class Demo6 {
    // Initialization > ...
    static int count = 0;

    /* Main */
    public static void main(String[] arguments) {
        // Constant > ...
        Button button = new Button("COUNT");
        TextField output = new TextField("0");
        Label label = new Label("Counter");
        ImageIcon icon = new ImageIcon("icon.ico");

        Frame window = new Frame("Java Counter");

        // Insertion
            // [Header]
            window.add(new Panel());
            window.add(new Panel());
            window.add(new Panel());
            window.add(new Panel());
            window.add(new Panel());
            window.add(new Panel());
            window.add(new Panel());

            // [Body]
            window.add(new Panel());
            window.add(label);
            window.add(new Panel());
            window.add(output);
            window.add(new Panel());
            window.add(button);
            window.add(new Panel());

            // [Footer]
            window.add(new Panel());
            window.add(new Panel());
            window.add(new Panel());
            window.add(new Panel());
            window.add(new Panel());
            window.add(new Panel());
            window.add(new Panel());

        // Modification
            // Button > ...
            button.setBackground(Color.WHITE);
            button.setForeground(Color.BLACK);

            // Output > ...
            output.setBackground(Color.WHITE);
            output.setFont(new Font("Google Sans", Font.ITALIC, 30));
            output.setForeground(Color.BLACK);

            // Window > ...
            window.setBackground(Color.DARK_GRAY);
            window.setFont(new Font("Google Sans", Font.BOLD, 20));
            window.setForeground(Color.WHITE);
            window.setLayout(new GridLayout(3, 7));
            window.setSize(700, 200);
            window.setVisible(true);

        // Event > ...
        button.addActionListener(new ActionListener() {public void actionPerformed(ActionEvent event) { output.setText((count += 1) + ""); }});
        window.addWindowListener(new WindowAdapter() {public void windowClosing(WindowEvent event) { System.exit(0); }});
    }
}
