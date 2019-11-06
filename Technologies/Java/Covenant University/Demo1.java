/* Import */
import javax.swing.JOptionPane; // Java Extension > Swing > Java Option Pane

/* ... */
public class Demo1 {
    /* Main */
    public static void main(String[] arguments) {
        // Initialization
            // (Integer, String) (A, B)
            String stringA = JOptionPane.showInputDialog("Enter first integer");
            String stringB = JOptionPane.showInputDialog("Enter second integer");

            int integerA = Integer.parseInt(stringA);
            int integerB = Integer.parseInt(stringB);

            // Sum
            int sum = integerA + integerB;

        // ...
        JOptionPane.showMessageDialog(null, "Sum = " + sum/*, "Sum of Two Integers", JOptionPane.INFORMATION_MESSAGE*/);
    }
}
