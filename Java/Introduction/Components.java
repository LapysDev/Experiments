import java.awt.*;
import javax.swing.*;

public class Components {
    public static void main(String[] arguments) {
        JFrame window = new JFrame("Window Title");
            JPanel firstName = new JPanel();
                JLabel firstNameLabel = new JLabel("First Name");
                JTextField firstNameTextField = new JTextField();

            JPanel lastName = new JPanel();
                JLabel lastNameLabel = new JLabel("Last Name");
                JTextField lastNameTextField = new JTextField();

            JPanel gender = new JPanel();
                JRadioButton maleButton = new JRadioButton("Male");
                JRadioButton femaleButton = new JRadioButton("Female");

            JPanel birthday = new JPanel();
                JLabel birthdayLabel = new JLabel("Birthday");
                JComboBox birthdayDay = new JComboBox(new String[] {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"});
                JComboBox birthdayMonth = new JComboBox(new String[] {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"});
                JComboBox birthdayYear = new JComboBox(new String[] {"1969", "1970", "1971", "1972", "1973", "1974", "1975", "1976", "1977", "1978", "1979", "1980", "1981", "1982", "1983", "1984", "1985", "1986", "1987", "1988", "1989", "1990", "1991", "1992", "1993", "1994", "1995", "1996", "1997", "1998", "1999", "2000", "2001", "2002", "2003", "2004", "2005", "2006", "2007", "2008", "2009", "2010", "2011", "2012", "2013", "2014", "2015", "2016", "2017", "2018", "2019", "2020", "2021"});

            JPanel buttons = new JPanel();
                JButton clear = new JButton("Clear");
                JButton submit = new JButton("Submit");

        /* ... */
        window.setLayout(new BoxLayout(window.getContentPane(), BoxLayout.Y_AXIS));

        window.add(firstName);
            firstName.add(firstNameLabel);
            firstName.add(firstNameTextField);

        window.add(lastName);
            lastName.add(lastNameLabel);
            lastName.add(lastNameTextField);

        window.add(gender);
            gender.add(maleButton);
            gender.add(femaleButton);

        window.add(birthday);
            birthday.add(birthdayLabel);
            birthday.add(birthdayDay);
            birthday.add(birthdayMonth);
            birthday.add(birthdayYear);

        window.add(buttons);
            buttons.add(clear);
            buttons.add(submit);

        /* ... */
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setSize(750, 500);
        window.setLocationRelativeTo(null);
        window.setVisible(true);
    }
}
