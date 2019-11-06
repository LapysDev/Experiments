/* Import */
import java.awt.*; // Java > Abstract Window Toolkit > [All]
import java.awt.event.*;
import javax.swing.*; // Java Extension > Swing > [All]
import java.util.*; // Java > Utilities > [All]

/* ... */
public class GUI extends JFrame {
    // ...
    @SuppressWarnings("unchecked")

    // [Constructor]
    public GUI() { this.components = new Components(); }
    public GUI(String name) { this.components = new Components(); this.name = name; }
    public GUI(String name, String description) { this.components = new Components(); this.description = description; this.name = name; }

    // Class > Components --- NOTE (Lapys) -> All components are stored here.
    private class Components {
        // Initialization > ...
        private JLabel header = new JLabel();
        private JPanel main = new JPanel();
        private JLabel musicTitle = new JLabel();
        private Canvas poster = new Canvas();
        private JToolBar toolbar = new JToolBar();
        private JToggleButton toolbarMenuButton = new JToggleButton();
    };

    // Initialization > ...
    private Components components;
    private String description = "";
    private String name = "";
    private String title = "";

    // Method > Initiate
    private void initiate() {
        // Modification
            // Header > ...
            components.header.setAlignmentX(0.5f);
            components.header.setAlignmentY(0.5f);
            components.header.setBackground(new Color(0, 102, 255));
            components.header.setFont(new Font("Google Sans", 1, 25)); // NOTE (Lapys) -> No Internationalization.
            components.header.setForeground(new Color(255, 255, 255));
            components.header.setHorizontalAlignment(SwingConstants.CENTER);
            components.header.setMaximumSize(new Dimension(300, 40));
            components.header.setMinimumSize(new Dimension(300, 40));
            components.header.setOpaque(true);
            components.header.setPreferredSize(new Dimension(300, 40));
            components.header.setText("Now Playing");
            components.header.setVerticalAlignment(SwingConstants.CENTER);

            // Main > ...
            components.main.setAlignmentX(0.0f);
            components.main.setAlignmentY(0.0f);
            components.main.setBackground(new Color(255, 0, 0));
            components.main.setForeground(new Color(51, 51, 51));
            components.main.setFocusable(false);
            components.main.setFont(new Font("Roboto", 0, 16)); // NOTE (Lapys) -> No Internationalization.
            components.main.setMaximumSize(new Dimension(400, 500));
            components.main.setMinimumSize(new Dimension(400, 500));
            components.main.setPreferredSize(new Dimension(400, 500));
            components.main.setRequestFocusEnabled(false);
            components.main.setVerifyInputWhenFocusTarget(false);

            // Music Title > ...
            components.musicTitle.getAccessibleContext().setAccessibleName("Title");
            components.musicTitle.getAccessibleContext().setAccessibleDescription("The title of the current media/ song");

            components.musicTitle.setAlignmentX(0.5f);
            components.musicTitle.setAlignmentY(0.5f);
            components.musicTitle.setBackground(new Color(255, 255, 255));
            components.musicTitle.setFont(new Font("Google Sans", 1, 30)); // NOTE (Lapys) -> No Internationalization.
            components.musicTitle.setForeground(new Color(255, 255, 255));
            components.musicTitle.setHorizontalAlignment(SwingConstants.CENTER);
            components.musicTitle.setHorizontalTextPosition(SwingConstants.CENTER);
            components.musicTitle.setEnabled(false);
            components.musicTitle.setFocusable(false);
            components.musicTitle.setMaximumSize(new Dimension(400, 40));
            components.musicTitle.setMinimumSize(new Dimension(400, 40));
            components.musicTitle.setName("Title"); // NOTE (Lapys) -> No Internationalization.
            components.musicTitle.setPreferredSize(new Dimension(400, 40));
            components.musicTitle.setRequestFocusEnabled(false);
            components.musicTitle.setText("...");
            components.musicTitle.setVerifyInputWhenFocusTarget(false);
            components.musicTitle.setVerticalAlignment(SwingConstants.CENTER);
            components.musicTitle.setVerticalTextPosition(SwingConstants.CENTER);

            // Poster > ...
            components.poster.getAccessibleContext().setAccessibleName("Poster");
            components.poster.getAccessibleContext().setAccessibleDescription("Poster");

            components.poster.setBackground(new Color(0, 0, 0));
            components.poster.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
            components.poster.setEnabled(false);
            components.poster.setFont(new Font("Roboto", 0, 16)); // NOTE (Lapys) -> No Internationalization.
            components.poster.setMaximumSize(new Dimension(200, 200));
            components.poster.setMinimumSize(new Dimension(200, 200));
            components.poster.setName("Poster"); // NOTE (Lapys) -> No Internationalization.
            components.poster.setPreferredSize(new Dimension(200, 200));

            // Toolbar > ...
            components.toolbar.getAccessibleContext().setAccessibleName("Toolbar");

            components.toolbar.setAlignmentX(0.0f);
            components.toolbar.setAlignmentY(0.0f);
            components.toolbar.setBackground(new Color(0, 102, 255));
            components.toolbar.setBorder(null);
            components.toolbar.setBorderPainted(false);
            components.toolbar.setFloatable(false);
            components.toolbar.setFont(new Font("Roboto", 0, 16)); // NOTE (Lapys) -> No Internationalization.
            components.toolbar.setForeground(new Color(51, 51, 51));
            components.toolbar.setMaximumSize(new Dimension(400, 50));
            components.toolbar.setMinimumSize(new Dimension(400, 50));
            components.toolbar.setName("Toolbar"); // NOTE (Lapys) -> No Internationalization.
            components.toolbar.setRollover(true);

            // Toolbar Menu Button > ...
            components.toolbarMenuButton.getAccessibleContext().setAccessibleName("Menu Button");

            components.toolbarMenuButton.setBackground(new Color(0, 102, 255));
            components.toolbarMenuButton.setBorderPainted(false);
            components.toolbarMenuButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
            components.toolbarMenuButton.setFont(new Font("Google Sans", 1, 30)); // NOTE (Lapys) -> No Internationalization.
            components.toolbarMenuButton.setForeground(new Color(255, 255, 255));
            components.toolbarMenuButton.setHorizontalTextPosition(SwingConstants.CENTER);
            components.toolbarMenuButton.setMargin(new Insets(0, 30, 0, 30));
            components.toolbarMenuButton.setMaximumSize(new Dimension(50, 25));
            components.toolbarMenuButton.setMinimumSize(new Dimension(50, 25));
            components.toolbarMenuButton.setName("Menu Button"); // NOTE (Lapys) -> No Internationalization.
            components.toolbarMenuButton.setPreferredSize(new Dimension(50, 25));
            components.toolbarMenuButton.setText("=");
            components.toolbarMenuButton.setToolTipText("Check the playlist");
            components.toolbarMenuButton.setVerticalTextPosition(SwingConstants.CENTER);

            // ...
            getAccessibleContext().setAccessibleDescription(description);
            getAccessibleContext().setAccessibleParent(this);

            setAlwaysOnTop(false);
            setBackground(new Color(255, 255, 255));
            setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
            setFont(new Font("Roboto", 0, 16)); // NOTE (Lapys) -> No Internationalization.
            setForeground(new Color(51, 51, 51));
            setLocationRelativeTo(null);
            setLocation(new Point((GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDisplayMode().getWidth() - 400) / 2, (GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDisplayMode().getHeight() - 550) / 2));
            setMaximumSize(new Dimension(400, 550));
            setMinimumSize(new Dimension(400, 550));
            setName(name); // NOTE (Lapys) -> No Internationalization.
            setPreferredSize(new Dimension(400, 550));
            setResizable(false);
            setSize(new Dimension(400, 550));
            setTitle(name);
            setVisible(true);

        GroupLayout mainLayout = new GroupLayout(components.main);
        components.main.setLayout(mainLayout);
        mainLayout.setHorizontalGroup(
            mainLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(GroupLayout.Alignment.TRAILING, mainLayout.createSequentialGroup()
                .addComponent(components.musicTitle, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, Short.MAX_VALUE))
            .addGroup(GroupLayout.Alignment.TRAILING, mainLayout.createSequentialGroup()
                .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(components.poster, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addGap(99, 99, 99))
        );
        mainLayout.setVerticalGroup(
            mainLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(mainLayout.createSequentialGroup()
                .addGap(34, 34, 34)
                .addComponent(components.poster, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addGap(26, 26, 26)
                .addComponent(components.musicTitle, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addContainerGap(200, Short.MAX_VALUE))
        );

        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                    .addComponent(components.toolbar, GroupLayout.PREFERRED_SIZE, 400, GroupLayout.PREFERRED_SIZE)
                    .addComponent(components.main, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addGap(0, 2, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(components.toolbar, GroupLayout.PREFERRED_SIZE, 50, GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(components.main, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        // Insertion
        components.toolbar.add(components.toolbarMenuButton);
        components.toolbar.add(components.header);

        // Event > ...
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        // ...
        pack();
    }

    /* Main */
    public static void main(String[] arguments) {
        // Event > ... --- NOTE (Lapys) -> Could be reduced to a lambda expression.
        java.awt.EventQueue.invokeLater(new Runnable() {
            // Method > Run
            public void run() {
                // Constant > Application
                final GUI application = new GUI(
                    /* Name */ "Java Graphical User Interface",
                    /* Description */ "Practical demonstration of a functional graphical user-interface (GUI) made with the Java programming language"
                );

                // Application > ...
                application.initiate();
            }
        });
    }
}
