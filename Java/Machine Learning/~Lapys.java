/* Import > ... */
// : Java > Abstract Window Toolkit
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.ComponentOrientation;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.EventQueue;
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

/* Definition > Application ... */
class Application {};
enum ApplicationState { INITIATING, RESETTING, UPDATING, TERMINATING };

/* Application */
public class Lapys extends Application {
    /* Global */
    // : Application ...
    final protected static String APPLICATION_DESCRIPTION = "Testing software application coupled with database and machine learning technologies";
    protected static ArrayList<Font> APPLICATION_FONTS = new ArrayList<Font>();
    final protected static String APPLICATION_NAME = "Lapys";
    protected static ApplicationState APPLICATION_STATE;

    // : Database ...
    protected static Connection DATABASE_CONNECTION;
    final protected static String DATABASE_NAME = "Lapys Java";
    final protected static String DATABASE_PASSWORD = "Lapys30*)";
    final protected static String DATABASE_USER = "LapysDev";

    // : Screen ...
    final protected static Dimension SCREEN_SIZE = Toolkit.getDefaultToolkit().getScreenSize();
    final protected static int SCREEN_HEIGHT = SCREEN_SIZE.height;
    final protected static int SCREEN_WIDTH = SCREEN_SIZE.width;

    // : Window ...
    final protected static JWindow WINDOW = new JWindow(APPLICATION_NAME);
        // ...
        final protected static JForm ACCOUNT_FORM  = new JForm(true /* boolean isDoubleBuffered */);
        final protected static JForm HOME_FORM     = new JForm(true /* boolean isDoubleBuffered */);
        final protected static JForm REGISTER_FORM = new JForm(true /* boolean isDoubleBuffered */);

    /* Phases */
        /* Initiate --- NOTE (Lapys) */
        protected static void Initiate(final String[] arguments) {
            // Constant > Window ...
            final Container windowContentPane = WINDOW.getContentPane();
            final int windowHeight = (int) (SCREEN_HEIGHT * (75.0 / 100.0));
            final ImageIcon windowIcon = new ImageIcon("images/favicon.png");
            final int windowWidth = (int) (SCREEN_WIDTH * (75.0 / 100.0));
            final Dimension windowSize = new Dimension(windowWidth, windowHeight);
                // [Account] ...
                // [Home] ...
                final JPanel homeFormAchievements = new JPanel();

                final JPanel homeFormCarousel = new JPanel();
                final JPanel homeFormCarouselContentPane = new JPanel();
                final JLabel homeFormCarouselHeader = new JLabel("Header");
                final JPanel homeFormCarouselHeaderGroup = new JPanel();
                final JImage[] homeFormCarouselImages = {
                    new JImage(new ImageIcon("images/backgrounds/billboard.jpg")),
                    new JImage(new ImageIcon("images/backgrounds/campus.jpg")),
                    new JImage(new ImageIcon("images/backgrounds/college.jpg")),
                    new JImage(new ImageIcon("images/backgrounds/hostel.jpg")),
                    new JImage(new ImageIcon("images/backgrounds/senate.jpg")),
                    new JImage(new ImageIcon("images/backgrounds/sports.jpg"))
                };
                final JRoundedButton[] homeFormCarouselIndicators = new JRoundedButton[homeFormCarouselImages.length];
                final JPanel homeFormCarouselIndicatorSection = new JPanel();
                final JButton homeFormCarouselRegisterButton = new JButton("Register");
                final JPanel homeFormCarouselRegisterButtonSection = new JPanel();
                final JLabel homeFormCarouselSubheader = new JLabel("Subheader");
                final JPanel homeFormCarouselTheatre = new JPanel();

                final JScrollPane homeFormContentPane = new JScrollPane();

                final JPanel homeFormFooter = new JPanel();
                final JPanel homeFormFooterNewsletter = new JPanel();
                final JPanel homeFormFooterSocials = new JPanel();

                final JPanel homeFormIntroduction = new JPanel();

                // [Register] ...

            // ... -> Install custom fonts.
            for (final String fontPath : new String[] {
                "open-sans.ttf",
                "minecraft.otf"
            }) try {
                final Font font = Font.createFont(Font.TRUETYPE_FONT, new File("fonts/" + fontPath)).deriveFont(13f);

                APPLICATION_FONTS.add(font);
                GraphicsEnvironment.getLocalGraphicsEnvironment().registerFont(font);
            } catch (final FontFormatException|IOException error) { System.err.println(error); }

            // Insertion > ... -> Structure UI.
            // : Account Form
            WINDOW.add(ACCOUNT_FORM); {}

            // : Home Form
            WINDOW.add(HOME_FORM); {
                /*HOME_FORM.add(homeFormCarousel);*/ {
                    // homeFormCarousel.add(homeFormCarouselContentPane);
                    //     homeFormCarouselContentPane.add(homeFormCarouselHeaderGroup);
                    //         homeFormCarouselHeaderGroup.add(homeFormCarouselHeader);
                    //         homeFormCarouselHeaderGroup.add(homeFormCarouselSubheader);

                    //     homeFormCarouselContentPane.add(homeFormCarouselIndicatorSection);
                    //         for (final JRoundedButton homeFormCarouselIndicator : homeFormCarouselIndicators) {
                    //             homeFormCarouselIndicator.addActionListener(new ActionListener() { @Override public void actionPerformed(final ActionEvent event) {} });
                    //             homeFormCarouselIndicatorSection.add(homeFormCarouselIndicator);
                    //         }

                    //     homeFormCarouselContentPane.add(homeFormCarouselRegisterButtonSection);
                    //         homeFormCarouselRegisterButtonSection.add(homeFormCarouselRegisterButton);

                    // homeFormCarousel.add(homeFormCarouselTheatre);
                    //     for (final JImage homeFormCarouselImage : homeFormCarouselImages)
                    //     homeFormCarouselTheatre.add(homeFormCarouselImage);
                }
            }

            // : Register Form
            WINDOW.add(REGISTER_FORM); {}

            // Style -> Layout/ style UI.
            // : Account Form
            // : Home Form
            final BorderLayout homeFormLayout = new BorderLayout(0, 0); {
                HOME_FORM.add(homeFormContentPane, BorderLayout.CENTER);
                HOME_FORM.setLayout(homeFormLayout);

                final ScrollPaneLayout homeFormContentPaneLayout = new ScrollPaneLayout(); {
                    homeFormContentPane.setBorder(null);
                    homeFormContentPane.setLayout(homeFormContentPaneLayout);

                    homeFormContentPane.setMinimumSize(new Dimension(700, 100));
                    homeFormContentPane.setPreferredSize(new Dimension(700, 100));
                    homeFormContentPane.setSize(new Dimension(700, 100));

                    JPanel sus = new JPanel();
                    sus.setBackground(Color.BLUE);
                    sus.setMinimumSize(new Dimension(600, SCREEN_HEIGHT));
                    sus.setPreferredSize(new Dimension(600, SCREEN_HEIGHT));
                    sus.setSize(new Dimension(600, SCREEN_HEIGHT));
                    homeFormContentPane.getViewport().setView(sus);

                    // : Carousel
                    // : Introduction
                    // : Achievements
                    // : Footer
                }
            }

            // : Register Form

            // ...
            // : Window Content Pane
            windowContentPane.setLayout(null);
            windowContentPane.setSize(windowSize);

            // : Window
            WINDOW.evaluateOffsets(true);

            WINDOW.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
            WINDOW.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            WINDOW.setIconImage(windowIcon.getImage()); // WARN (Lapys) -> Does not accept Windows `.ico` files.
            WINDOW.setLayout(null);
            WINDOW.setLocation((int) ((SCREEN_WIDTH - windowWidth) / 2.0), (int) ((SCREEN_HEIGHT - windowHeight) / 2.0)); // --> WINDOW.setLocationRelativeTo(null);
            WINDOW.setMinimumSize(windowSize);
            WINDOW.setSize(windowSize);
            WINDOW.setTitle(APPLICATION_NAME);
            WINDOW.setVisible(true);

            // WINDOW.pack();
            WINDOW.switchToForm(HOME_FORM, false);
            WINDOW.evaluateOffsets(false);
        }

        /* Update */
        protected static void Update() {
            // Constant > Window ...
            final Container windowContentPane = WINDOW.getContentPane();
            final Dimension windowSize = new Dimension(WINDOW.getWidth(), WINDOW.getHeight());

            // ... > Window ...
            WINDOW.evaluateOffsets(true);
            windowContentPane.setSize(windowSize);

            for (final JForm windowForm : WINDOW.forms)
            windowForm.setSize(new Dimension(windowContentPane.getSize().width, windowContentPane.getSize().height));

            WINDOW.switchToForm(WINDOW.activeForm, false);
            WINDOW.evaluateOffsets(false);
        }

        /* Terminate */
        protected static void Terminate(final int code) {
            // ...
            System.exit(code);
        }

    /* Main */
    public static void main(final String[] arguments) {
        /* Event */
            // ...
            EventQueue.invokeLater(new Runnable() {
                @Override public void run() {
                    APPLICATION_STATE = ApplicationState.INITIATING;
                    Initiate(arguments);
                }
            });

            // Key --- NOTE (Lapys) -> Close `WINDOW` when the "Escape" key is pressed.
            KeyboardFocusManager.getCurrentKeyboardFocusManager().addKeyEventDispatcher(new KeyEventDispatcher() {
                @Override
                public boolean dispatchKeyEvent(final KeyEvent event) {
                    if (KeyEvent.KEY_PRESSED == event.getID() && KeyEvent.VK_ESCAPE == event.getKeyCode())
                    WINDOW.dispatchEvent(new WindowEvent(WINDOW, WindowEvent.WINDOW_CLOSING));

                    return false;
                }
            });

            // Window > (Close ..., Resize)
            WINDOW.addComponentListener(new ComponentAdapter() {
                @Override public void componentResized(final ComponentEvent event) {
                    if (
                        APPLICATION_STATE == ApplicationState.INITIATING ||
                        APPLICATION_STATE == ApplicationState.UPDATING
                    ) { APPLICATION_STATE = ApplicationState.UPDATING; Update(); }
                }
            });

            WINDOW.addWindowListener(new WindowAdapter() {
                @Override public void windowClosed(final WindowEvent event) {
                    /* ... */
                }

                @Override public void windowClosing(final WindowEvent event) {
                    if (
                        APPLICATION_STATE == ApplicationState.INITIATING ||
                        APPLICATION_STATE == ApplicationState.UPDATING
                    ) { APPLICATION_STATE = ApplicationState.TERMINATING; Terminate(0x0); }
                }
            });
    }
};

/* Class */
    /* Form */
    class JForm extends JPanel {
        public JForm() { super(); }
        public JForm(final boolean isDoubleBuffered) { super(isDoubleBuffered); }
        public JForm(final LayoutManager layout) { super(layout); }
        public JForm(final LayoutManager layout, final boolean isDoubleBuffered) { super(layout, isDoubleBuffered); }

        // ...
        @Override
        protected void paintComponent(final Graphics graphics) {
            if (Lapys.HOME_FORM == this) {
                this.setBackground(Color.BLACK);
                super.paintComponent(graphics);
            }

            else {
                Graphics2D graphics2D;

                // ...
                super.paintComponent(graphics);
                graphics2D = (Graphics2D) graphics;

                // ...
                graphics2D.setPaint(new GradientPaint(0, 0, new Color(153, 0, 153), 0, this.getHeight(), new Color(0, 111, 255)));
                graphics2D.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);

                graphics2D.fillRect(0, 0, this.getWidth(), this.getHeight());
            }
        }
    };

    /* Image */
    class JImage extends JLabel {
        public JImage(final Icon image) { super(image); }
        public JImage(final Icon image, final int horizontalAlignment) { super(image, horizontalAlignment); }
    };

    /* Rounded Button */
    class JRoundedButton extends JButton {
        private Icon icon;

        // ...
        public JRoundedButton(final Action action) { super(action); Initiate(Math.max(this.getPreferredSize().width, this.getPreferredSize().height)); }
        public JRoundedButton(final Icon icon) { super(icon); Initiate(Math.max(this.getPreferredSize().width, this.getPreferredSize().height)); }
        public JRoundedButton(final String text) { super(text); Initiate(Math.max(this.getPreferredSize().width, this.getPreferredSize().height)); }
        public JRoundedButton(final String text, final Icon icon) { super(text, icon); Initiate(Math.max(this.getPreferredSize().width, this.getPreferredSize().height)); }

        // ... --- REDACT (Lapys)
        protected void Initiate(final int size) {
            this.setContentAreaFilled(false);
            this.setPreferredSize(new Dimension(size, size));
        }

        // ... --- REDACT (Lapys)
        public boolean contains(final int x, final int y) {
            return new Ellipse2D.Float(0, (int) (this.getHeight() / 8.0), this.getWidth(), this.getHeight() - (int) (this.getHeight() / 4.0)).contains(x, y);
        }

        @Override
        protected void paintBorder(final Graphics graphics) {
            final Graphics2D graphics2D = (Graphics2D) graphics;

            graphics2D.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            graphics2D.setColor(this.getForeground());
            graphics2D.drawOval(0, (int) (this.getHeight() / 8.0), this.getWidth(), this.getHeight() - (int) (this.getHeight() / 4.0));
        }

        @Override
        protected void paintComponent(final Graphics graphics) {
            final Graphics2D graphics2D = (Graphics2D) graphics;

            graphics2D.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            graphics2D.setColor(this.getModel().isArmed() ? Color.lightGray : this.getBackground());
            graphics2D.fillOval(0, (int) (this.getHeight() / 8.0), this.getWidth(), this.getHeight() - (int) (this.getHeight() / 4.0));

            super.paintComponent(graphics2D);
        }
    };

    /* Window */
    class JWindow extends JFrame {
        protected JForm activeForm = null;
        private boolean canEvaluateOffsets = false;
        final protected ArrayList<JForm> forms = new ArrayList<JForm>();
        private Rectangle clientOffsets = null;

        // ...
        public JWindow() { super(); }
        public JWindow(final GraphicsConfiguration graphicsConfiguration) { super(graphicsConfiguration); }
        public JWindow(final String title) { super(title); }
        public JWindow(final String title, final GraphicsConfiguration graphicsConfiguration) { super(title, graphicsConfiguration); }

        // Methods
            // Add, Remove
            public void add(final JForm form) { super.add(form); this.forms.add(form); }
            public void remove(final JForm form) { super.remove(form); this.forms.remove(form); }

            // (Evaluate, Get) Offsets
            public void evaluateOffsets(final boolean assertion) { this.canEvaluateOffsets = assertion; }
            public Rectangle getOffsets() { return null == this.clientOffsets ? new Rectangle(0, 0, this.getWidth(), this.getHeight()) : this.clientOffsets; }

            // Set ...
            public void setBounds(final int x, final int y, final int width, final int height) { super.setBounds(x, y, width, height); this.setOffsets(); }
            public void setMaximumSize(final Dimension maximumSize) { super.setMaximumSize(maximumSize); this.setOffsets(); }
            public void setMinimumSize(final Dimension minimumSize) { super.setMinimumSize(minimumSize); this.setOffsets(); }
            public void setPreferredSize(final Dimension preferredSize) { super.setPreferredSize(preferredSize); this.setOffsets(); }
            public void setSize(final Dimension size) { super.setSize(size); this.setOffsets(); }
            public void setSize(final int width, final int height) { super.setSize(width, height); this.setOffsets(); }

            // Set Offsets
            private void setOffsets() {
                try {
                    if (this.canEvaluateOffsets) {
                        System.out.println("[OFFSET]: {" +
                            (this.getWidth() - this.getContentPane().getSize().width) + ", " +
                            (this.getHeight() - this.getContentPane().getSize().height) + ", " +
                            this.getContentPane().getSize().width + ", " +
                            this.getContentPane().getSize().height +
                        '}');

                        this.clientOffsets = new Rectangle(
                            this.getWidth() - this.getContentPane().getSize().width,
                            this.getHeight() - this.getContentPane().getSize().height,
                            this.getContentPane().getSize().width,
                            this.getContentPane().getSize().height
                        );
                    }
                } catch (final Exception error) { System.out.println(error); }
            }

            // Switch To Form
            public void switchToForm(final JForm form) { this.switchToForm(form, true); }
            public void switchToForm(final JForm form, final boolean animated) {
                // Constant > (Client Area ... Offset, ... Active Form)
                final int clientAreaLeftOffset = this.getOffsets().x;
                final int clientAreaRightOffset = this.getOffsets().width;
                final int clientAreaTopOffset = this.getOffsets().y;

                final JForm currentActiveForm = form;
                final JForm recentActiveForm = this.activeForm;

                // Loop > ... Update > Window Form
                for (final JForm windowForm : this.forms)
                if (currentActiveForm != windowForm) {
                    if (recentActiveForm != windowForm) { windowForm.setLocation(clientAreaRightOffset, clientAreaTopOffset); }
                    this.setComponentZOrder(windowForm, 0);
                }

                // Update > ... Active Form
                this.activeForm = currentActiveForm;
                this.setComponentZOrder(currentActiveForm, 1);

                // ...
                new Timer().scheduleAtFixedRate(new TimerTask() {
                    @Override
                    public void run() {
                        // Initialization > Current Active Form X Coordinate
                        int currentActiveFormXCoordinate = currentActiveForm.getLocation().x;

                        // Logic
                        if (clientAreaLeftOffset == currentActiveFormXCoordinate) {
                            // ... Update > Recent Active Form
                            if (null != recentActiveForm && currentActiveForm != recentActiveForm)
                            recentActiveForm.setLocation(clientAreaRightOffset, clientAreaTopOffset);

                            // Terminate
                            cancel();
                        }

                        else {
                            // Update > Current Active Form ...
                            currentActiveFormXCoordinate -= 10;
                            currentActiveForm.setLocation(animated ? currentActiveFormXCoordinate < clientAreaLeftOffset ? clientAreaLeftOffset : currentActiveFormXCoordinate : clientAreaLeftOffset, clientAreaTopOffset);
                        }
                    }
                }, 0, 3);
            }
    };
