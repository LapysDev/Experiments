import javax.swing.JOptionPane;

public class Demo5 {
    public static void main(String[] arguments) {
        boolean hasMinimumValue = false;

        int minimum = 0;
        int numbersCount = Integer.parseInt(JOptionPane.showInputDialog("Number of Integers"));


        for (int i = 0; i < numbersCount; i++) {
            int number = Integer.parseInt(JOptionPane.showInputDialog("Input an Integer"));

            if (!hasMinimumValue || number < minimum) {
                hasMinimumValue = true;
                minimum = number;
            }
        }

        JOptionPane.showMessageDialog(null, "Minimum Integer = " + minimum);
    }
}
