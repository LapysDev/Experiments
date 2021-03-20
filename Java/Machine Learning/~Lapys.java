/* Import > ... */
// : Java > Abstract Window Toolkit
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.ComponentOrientation;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.FontFormatException;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsEnvironment;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.Insets;
import java.awt.KeyboardFocusManager;
import java.awt.KeyEventDispatcher;
import java.awt.LayoutManager;
import java.awt.Rectangle;
import java.awt.RenderingHints;
import java.awt.Toolkit;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import java.awt.geom.Ellipse2D;

// : Java > Input/ Output
import java.io.File;
import java.io.IOException;

// : Java > Structured Query Language (SQL)
import java.sql.Connection;
import java.sql.DriverManager;

// : Java > Utilities
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

// : Java Extensions > Image Input/ Output
// : Java Extensions > Swing
import javax.swing.Action;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ScrollPaneLayout;

/* Class --- REDACT (Lapys) */
    /* Form */
    class JForm extends JPanel {
        // ...
        public JForm() { super(); }
        public JForm(final boolean isDoubleBuffered) { super(isDoubleBuffered); }
        public JForm(final LayoutManager layout) { super(layout); }
        public JForm(final LayoutManager layout, final boolean isDoubleBuffered) { super(layout, isDoubleBuffered); }

        // ...
        @Override
        public boolean isOptimizedDrawingEnabled() { return false; }
    };

    /* Window */
    class JWindow extends JFrame {
        protected JForm activeForm = null;
        protected JForm[] forms;

        // ...
        public JWindow() { super(); }
        public JWindow(final GraphicsConfiguration graphicsConfiguration) { super(graphicsConfiguration); }
        public JWindow(final String title) { super(title); }
        public JWindow(final String title, final GraphicsConfiguration graphicsConfiguration) { super(title, graphicsConfiguration); }

        // ...
        public void switchToForm(final JForm form) { this.switchToForm(form, true); }
        public void switchToForm(final JForm form, final boolean animated) {
            // Constant > (... Active Form)
            final JForm currentActiveForm = form;
            final JForm recentActiveForm = this.activeForm;

            // Loop > ... Update > Window Form
            for (final JForm windowForm : this.forms)
            if (windowForm != currentActiveForm) {
                if (windowForm != recentActiveForm) { windowForm.setLocation(windowForm.getParent().getSize().width, 0); }
                windowForm.getParent().setComponentZOrder(windowForm, 0);
            }

            // Update > ... Active Form
            this.activeForm = currentActiveForm;
            currentActiveForm.getParent().setComponentZOrder(currentActiveForm, 1);

            // ...
            new Timer().scheduleAtFixedRate(new TimerTask() {
                @Override
                public void run() {
                    // Initialization > Current Active Form X Coordinate
                    int currentActiveFormXCoordinate = currentActiveForm.getLocation().x;

                    // Logic
                    if (0 == currentActiveFormXCoordinate) {
                        // ... Update > Recent Active Form
                        if (null != recentActiveForm && currentActiveForm != recentActiveForm)
                        recentActiveForm.setLocation(recentActiveForm.getParent().getSize().width, 0);

                        // Terminate
                        cancel();
                    }

                    else {
                        // Update > Current Active Form ...
                        currentActiveFormXCoordinate -= 10;
                        currentActiveForm.setLocation(animated ? (currentActiveFormXCoordinate < 0 ? 0 : currentActiveFormXCoordinate) : 0, 0);
                    }
                }
            }, 0, 3);
        }
    };

/* Definition > Application */
class Application {
    enum State { INITIATING, RESETTING, UPDATING, TERMINATING };
    protected State state;
};

/* Application */
public class Lapys extends Application {
    /* Global */
    // : Application ...
    final protected static Lapys APPLICATION = new Lapys();
    final protected static String APPLICATION_DESCRIPTION = "Testing software application coupled with database and machine learning technologies";
    final protected static ArrayList<Font> APPLICATION_FONTS = new ArrayList<Font>();
    final protected static String APPLICATION_NAME = "Lapys (AI)";

    // : Database ...
    protected static Connection DATABASE_CONNECTION;
    final protected static String DATABASE_NAME = "Lapys Java";
    final protected static String DATABASE_PASSWORD = "Lapys30*)";
    final protected static String DATABASE_USER = "LapysDev";

    // : Screen ...
    final protected static Dimension SCREEN_SIZE = Toolkit.getDefaultToolkit().getScreenSize();
    final protected static int SCREEN_HEIGHT = SCREEN_SIZE.height;
    final protected static int SCREEN_WIDTH = SCREEN_SIZE.width;

    // : Window
    final protected static JWindow WINDOW = new JWindow(APPLICATION_NAME);
    final protected static JPanel WINDOW_CONTENT = new JPanel();
        // ...
        final protected static JForm ACCOUNT_FORM  = new JForm(true /* boolean isDoubleBuffered */);
        final protected static JForm HOME_FORM     = new JForm(true /* boolean isDoubleBuffered */);
            final JPanel HOME_FORM_ACHIEVEMENTS = new JPanel();
            final JPanel HOME_FORM_CAROUSEL = new JPanel();
            final JPanel HOME_FORM_CONTENT = new JPanel();
            final JScrollPane HOME_FORM_CONTENT_SCROLL = new JScrollPane();
            final JPanel HOME_FORM_FOOTER = new JPanel();
            final JPanel HOME_FORM_INTRODUCTION = new JPanel();
        final protected static JForm REGISTER_FORM = new JForm(true /* boolean isDoubleBuffered */);

    /* Phases */
        /* Initiate */
        protected void Initiate(final String[] arguments) {
            // Constant > Window ...
            final Container windowContentPane = WINDOW.getContentPane();
            final int windowHeight = (int) (SCREEN_HEIGHT * (75.0 / 100.0));
            final ImageIcon windowIcon = new ImageIcon("images/favicon.png");
            final int windowWidth = (int) (SCREEN_WIDTH * (75.0 / 100.0));
            final Dimension windowSize = new Dimension(windowWidth, windowHeight);

            // Register > ...
            for (final String fontPath : new String[] {"open-sans.ttf", "minecraft.otf"})
            try {
                APPLICATION_FONTS.add(Font.createFont(Font.TRUETYPE_FONT, new File("fonts/" + fontPath)).deriveFont(13f));
                GraphicsEnvironment.getLocalGraphicsEnvironment().registerFont(APPLICATION_FONTS.get(APPLICATION_FONTS.size() - 1));
            } catch (final FontFormatException|IOException error) { System.err.println(error); }

            // Modification > Window > ...
            WINDOW.forms = new JForm[] {ACCOUNT_FORM, HOME_FORM, REGISTER_FORM};

            // Insertion
            WINDOW.add(WINDOW_CONTENT); {
                // WINDOW_CONTENT.setLayout(null);
                WINDOW_CONTENT.setLocation(0, 0);

                // : Account Form
                // WINDOW_CONTENT.add(ACCOUNT_FORM); {
                //     ACCOUNT_FORM.setBackground(Color.MAGENTA);
                // }

                // : Home Form
                WINDOW_CONTENT.add(HOME_FORM); {
                    HOME_FORM.add(new JButton("Button A"));
                    HOME_FORM.add(new JButton("Button B"));
                    HOME_FORM.add(new JButton("Button C"));
                    HOME_FORM.setBackground(Color.GREEN);
                    HOME_FORM.setLayout(new FlowLayout(FlowLayout.RIGHT, 0, 0));
                    HOME_FORM.setSize(new Dimension(windowWidth, windowHeight));

                    // : Content Scroll
                    homeFormContentScroll.setLayout(new ScrollPaneLayout()); {
                        homeFormContentScroll.getViewport().setView(homeFormContent);
                        homeFormContentScroll.setBorder(null);
                        homeFormContentScroll.setSize(windowWidth, windowHeight);

                        homeFormContent.setBackground(Color.BLACK);
                        homeFormContent.setSize(new Dimension(windowWidth, windowHeight));
                    }
                }

                // : Register Form
                // WINDOW_CONTENT.add(REGISTER_FORM); {
                //     REGISTER_FORM.setBackground(Color.BLUE);
                // }
            }

            // ...
            WINDOW.pack();
            WINDOW.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
            WINDOW.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            WINDOW.setIconImage(windowIcon.getImage()); // WARN (Lapys) -> Does not accept Windows `.ico` files.
            WINDOW.setLocation((int) ((SCREEN_WIDTH - windowWidth) / 2.0), (int) ((SCREEN_HEIGHT - windowHeight) / 2.0)); // --> WINDOW.setLocationRelativeTo(null);
            WINDOW.setMinimumSize(windowSize);
            WINDOW.setSize(windowSize);
            WINDOW.setTitle(APPLICATION_NAME);
            WINDOW.setVisible(true);

            // Update
            Update();
        }

        /* Reset */
        protected void Reset(final int code) { /* ... */ }

        /* Update */
        protected void Update() {
            // ...
            WINDOW_CONTENT.setSize(WINDOW.getContentPane().getSize());
            for (final JForm windowForm : WINDOW.forms) {
                windowForm.setLocation(0, 0);
                windowForm.setSize(WINDOW_CONTENT.getSize());
            }
        }

        /* Terminate */
        protected void Terminate(final int code) { System.exit(code); }

    /* Main */
    public static void main(final String[] arguments) {
        /* Event */
        // : ...
        EventQueue.invokeLater(new Runnable() {
            @Override public void run() {
                APPLICATION.state = Application.State.INITIATING;
                APPLICATION.Initiate(arguments);
            }
        });

        // : Key --- NOTE (Lapys) -> Close `WINDOW` when the "Escape" key is pressed.
        KeyboardFocusManager.getCurrentKeyboardFocusManager().addKeyEventDispatcher(new KeyEventDispatcher() {
            @Override public boolean dispatchKeyEvent(final KeyEvent event) {
                if (KeyEvent.KEY_PRESSED == event.getID() && KeyEvent.VK_ESCAPE == event.getKeyCode())
                WINDOW.dispatchEvent(new WindowEvent(WINDOW, WindowEvent.WINDOW_CLOSING));

                return false;
            }
        });

        // : Window > (Close ..., Resize)
        WINDOW.addComponentListener(new ComponentAdapter() {
            @Override public void componentResized(final ComponentEvent event) {
                if (APPLICATION.state == Application.State.INITIATING || APPLICATION.state == Application.State.UPDATING) {
                    APPLICATION.state = Application.State.UPDATING;
                    APPLICATION.Update();
                }
            }
        });

        WINDOW.addWindowListener(new WindowAdapter() {
            @Override public void windowClosed(final WindowEvent event) { /* ... */ }
            @Override public void windowClosing(final WindowEvent event) {
                if (APPLICATION.state == Application.State.INITIATING || APPLICATION.state == Application.State.UPDATING) {
                    APPLICATION.state = Application.State.TERMINATING;
                    APPLICATION.Terminate(0x0);
                }
            }
        });
    }
};
