import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

/* ... */
public class Accumulator {
    public static void main(String[] arguments) {
        JFrame window = new JFrame("Window Title");
            JPanel input = new JPanel();
                JLabel inputLabel = new JLabel("Enter an integer");
                JTextField inputTextField = new JTextField(10);

            JPanel output = new JPanel();
                JLabel outputLabel = new JLabel("Accumulated sum is");
                JTextField outputTextField = new JTextField(10);

            JPanel button = new JPanel();
                JButton submit = new JButton("Accumulate");

        /* ... */
        window.setLayout(new BoxLayout(window.getContentPane(), BoxLayout.Y_AXIS));

        window.add(input);
            input.add(inputLabel);
            input.add(inputTextField);

        window.add(output);
            output.add(outputLabel);
            output.add(outputTextField);

        window.add(button);
            button.add(submit);

        /* ... */
        submit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                outputTextField.setText(String.valueOf(
                    Integer.parseInt(inputTextField.getText()) +
                    Integer.parseInt(outputTextField.getText())
                ));
            }
        });

        /* ... */
        inputTextField.setText("0");
        outputTextField.setText("0");

        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setSize(750, 500);
        window.setLocationRelativeTo(null);
        window.setVisible(true);
    }
}
