/* Import */
import javax.swing.JOptionPane; // Java Extension > Swing > Java Option Pane

/* ... */
public class Demo4 {
    /* Main */
    public static void main(String[] arguments) {
        // Constant > (Breadth, Length)
        int breadth = Integer.parseInt(JOptionPane.showInputDialog("Breadth of the Rectangle"));
        int length = Integer.parseInt(JOptionPane.showInputDialog("Length of the Rectangle"));

        // ...
        JOptionPane.showMessageDialog(null, "Area of the Rectangle = " + (breadth * length));
    }
}
