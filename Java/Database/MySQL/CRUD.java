/* Import > ... */
// : Java > Abstract Window Toolkit
import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.KeyboardFocusManager;
import java.awt.KeyEventDispatcher;
import java.awt.RenderingHints;
import java.awt.Shape;
import java.awt.Toolkit;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.WindowEvent;

import java.awt.geom.Ellipse2D;

import java.awt.image.BufferedImage;

// : Java > Input/ Output
import java.io.File;

// : Java > Utilities
import java.util.Timer;
import java.util.TimerTask;

// : Java Extensions > Image I/O
import javax.imageio.ImageIO;

// : Java Extensions > Swing
import javax.swing.Action;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.GroupLayout;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

/* Class --- REDACT (Lapys) */
  /* Java Image */
  class JImage extends JComponent {
    private Image image;

    // ...
    public JImage(final String path) { super(); this.setImage(path); }

    // ...
    protected Image getImage() { return this.image; }
    protected void setImage(final String path) { this.image = Toolkit.getDefaultToolkit().getImage(path); }

    @Override protected void paintComponent(final Graphics graphics) { ((Graphics2D) graphics).drawImage(this.getImage(), this.getX(), this.getY(), this.getWidth(), this.getHeight(), 0, 0, this.getImage().getWidth(this), this.getImage().getHeight(this), this); }
  };

  /* Java Rounded Button */
  class JRoundedButton extends JButton {
    private Icon icon;

    // ...
    public JRoundedButton(final Action action) { super(action); init(Math.max(this.getPreferredSize().width, this.getPreferredSize().height)); }
    public JRoundedButton(final Icon icon) { super(icon); init(Math.max(this.getPreferredSize().width, this.getPreferredSize().height)); }
    public JRoundedButton(final String string) { super(string); init(Math.max(this.getPreferredSize().width, this.getPreferredSize().height)); }
    public JRoundedButton(final String string, final Icon icon) { super(string, icon); init(Math.max(this.getPreferredSize().width, this.getPreferredSize().height)); }

    // ...
    private void init(final int size) {
      this.setContentAreaFilled(false);
      this.setPreferredSize(new Dimension(size, size));
    }

    // ...
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

/* Application */
public class CRUD {
  /* Main
      --- NOTE ---
        #Lapys:
          LOGO
          CRUD APPLICATION
          LOGIN [VALIDATE]
            INSERT NAME/ MATRICULATION NUMBER
            INSERT PASSWORD

            VALID - READ STUDENT ACCOUNT FROM DATABASE TABLE
              NAME
              COURSE
              EMAIL
              MATRICULATION NUMBER
              [UPDATE ACCOUNT] - MODIFY {NAME, COURSE, EMAIL, MATRICULATION NUMBER} IN DATABASE TABLE
              [RESET PASSWORD] - MODIFY {PASSWORD} FIELD IN DATABASE TABLE
              [DELETE ACCOUNT] - REMOVE STUDENT ACCOUNT FROM DATABASE TABLE

            INVALID - TRY AGAIN

          SIGN UP [VALIDATE]
            INSERT NAME
            INSERT COURSE
            INSERT MATRICULATION NUMBER
            INSERT EMAIL
            INSERT PASSWORD

            VALID - ADD STUDENT ACCOUNT TO DATABASE TABLE | READ STUDENT ACCOUNT FROM DATABASE TABLE
              ...

            INVALID - TRY AGAIN
  */
  /* Global > ... */
    // Application ...
    final private static String APPLICATION_DESCRIPTION = "Client-side software application that Creates, Reads, Updates, and Deletes relevant data with a MySQL database";
    final private static String APPLICATION_NAME = "CRUD Application";

    final private static String APPLICATION_ROOT_PATH = "";
    final private static String APPLICATION_ICON_PATH = APPLICATION_ROOT_PATH + "images/icons/covenant.png";

    // Screen ...
    final private static Dimension SCREEN_SIZE = Toolkit.getDefaultToolkit().getScreenSize();
    final private static int SCREEN_HEIGHT = SCREEN_SIZE.height;
    final private static int SCREEN_WIDTH = SCREEN_SIZE.width;

  /* Main --- NOTE (Lapys) */
  public static void main(final String[] arguments) throws Exception {
      /* Constant > ... */
      final JFrame WINDOW = new JFrame(APPLICATION_NAME);
      final GroupLayout WINDOW_LAYOUT = new GroupLayout(WINDOW.getContentPane());

      final int WINDOW_HEIGHT = (int) (SCREEN_HEIGHT * (75.0 / 100.0));
      final int WINDOW_WIDTH = (int) (SCREEN_WIDTH * (75.0 / 100.0));

      final Color WINDOW_BACKGROUND_COLOR = new Color(255, 255, 255);
        // : [Carousel]
        final JPanel CAROUSEL = new JPanel();
        final GroupLayout CAROUSEL_LAYOUT = new GroupLayout(CAROUSEL);

        final JLabel CAROUSEL_HEADER = new JLabel("Carousel Header");
        final JLabel CAROUSEL_SUBTEXT = new JLabel("Carousel Subtext");

        // : [Footer]
        final JPanel FOOTER = new JPanel();
        final JLabel FOOTNOTE = new JLabel("Copyright @ Lapys, 2020");

        // : [Logo]
        final JImage LOGO = new JImage(APPLICATION_ICON_PATH);
        final JPanel LOGO_PANEL = new JPanel();
        final GroupLayout LOGO_PANEL_LAYOUT = new GroupLayout(LOGO_PANEL);

        // : [Registration]
        final JButton LOGIN_BUTTON = new JButton("LOGIN");
        final JButton SIGNUP_BUTTON = new JButton("SIGN UP");

        final JPanel REGISTRATION_PANEL = new JPanel();
        final GroupLayout REGISTRATION_PANEL_LAYOUT = new GroupLayout(REGISTRATION_PANEL);

        // : [Social]
        final JButton FACEBOOK_BUTTON = new JRoundedButton(new ImageIcon("images/icons/facebook.png"));
        final JButton LINKEDIN_BUTTON = new JRoundedButton(new ImageIcon("images/icons/linkedin.png"));
        final JButton TWITTER_BUTTON = new JRoundedButton(new ImageIcon("images/icons/twitter.png"));
        final JButton YOUTUBE_BUTTON = new JRoundedButton(new ImageIcon("images/icons/youtube.png"));

        final JPanel SOCIAL_PANEL = new JPanel();
        final GroupLayout SOCIAL_PANEL_LAYOUT = new GroupLayout(SOCIAL_PANEL);

        // : [Title]
        final JLabel TITLE = new JLabel(APPLICATION_NAME);

      // Insertion -> Structure UI components.
      WINDOW.add(LOGO_PANEL);
        LOGO_PANEL.add(LOGO);

      WINDOW.add(TITLE);
      WINDOW.add(CAROUSEL);
        CAROUSEL.add(CAROUSEL_HEADER);
        CAROUSEL.add(CAROUSEL_SUBTEXT);

      WINDOW.add(REGISTRATION_PANEL);
        REGISTRATION_PANEL.add(LOGIN_BUTTON);
        REGISTRATION_PANEL.add(SIGNUP_BUTTON);

      WINDOW.add(SOCIAL_PANEL);
        SOCIAL_PANEL.add(FACEBOOK_BUTTON);

      WINDOW.add(FOOTER);
        FOOTER.add(FOOTNOTE);

      // ... -> Order UI components.
      CAROUSEL.setLayout(CAROUSEL_LAYOUT); {
        CAROUSEL_LAYOUT.setHorizontalGroup(CAROUSEL_LAYOUT
          .createSequentialGroup()
          .addGroup(CAROUSEL_LAYOUT.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addComponent(CAROUSEL_HEADER)
            .addComponent(CAROUSEL_SUBTEXT)
        ));
        CAROUSEL_LAYOUT.setVerticalGroup(CAROUSEL_LAYOUT
          .createSequentialGroup()
            .addGroup(CAROUSEL_LAYOUT.createSequentialGroup().addComponent(CAROUSEL_HEADER))
            .addGroup(CAROUSEL_LAYOUT.createSequentialGroup().addComponent(CAROUSEL_SUBTEXT))
        );
      }

      LOGO_PANEL.setLayout(LOGO_PANEL_LAYOUT); {
        LOGO_PANEL_LAYOUT.setHorizontalGroup(LOGO_PANEL_LAYOUT.createSequentialGroup().addComponent(LOGO));
        LOGO_PANEL_LAYOUT.setVerticalGroup(LOGO_PANEL_LAYOUT.createSequentialGroup().addComponent(LOGO));
      }

      REGISTRATION_PANEL.setLayout(REGISTRATION_PANEL_LAYOUT); {
        REGISTRATION_PANEL_LAYOUT.setHorizontalGroup(REGISTRATION_PANEL_LAYOUT.createSequentialGroup()
          .addComponent(LOGIN_BUTTON)
          .addComponent(SIGNUP_BUTTON)
        );
        REGISTRATION_PANEL_LAYOUT.setVerticalGroup(REGISTRATION_PANEL_LAYOUT.createParallelGroup(GroupLayout.Alignment.BASELINE)
          .addComponent(LOGIN_BUTTON)
          .addComponent(SIGNUP_BUTTON)
        );
      }

      SOCIAL_PANEL.setLayout(SOCIAL_PANEL_LAYOUT); {
        SOCIAL_PANEL_LAYOUT.setHorizontalGroup(SOCIAL_PANEL_LAYOUT.createSequentialGroup()
          .addComponent(FACEBOOK_BUTTON)
          .addComponent(LINKEDIN_BUTTON)
          .addComponent(TWITTER_BUTTON)
          .addComponent(YOUTUBE_BUTTON)
        );
        SOCIAL_PANEL_LAYOUT.setVerticalGroup(SOCIAL_PANEL_LAYOUT.createParallelGroup(GroupLayout.Alignment.BASELINE)
          .addComponent(FACEBOOK_BUTTON)
          .addComponent(LINKEDIN_BUTTON)
          .addComponent(TWITTER_BUTTON)
          .addComponent(YOUTUBE_BUTTON)
        );
      }

      WINDOW.getContentPane().setLayout(WINDOW_LAYOUT); {
        WINDOW_LAYOUT.setAutoCreateContainerGaps(true);
        WINDOW_LAYOUT.setAutoCreateGaps(true);

        WINDOW_LAYOUT.setHorizontalGroup(WINDOW_LAYOUT
          .createSequentialGroup()
          .addGroup(WINDOW_LAYOUT.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addComponent(LOGO_PANEL)
            .addComponent(TITLE)
            .addComponent(CAROUSEL)
            .addComponent(REGISTRATION_PANEL)
            .addComponent(SOCIAL_PANEL)
            .addComponent(FOOTER)
        ));
        WINDOW_LAYOUT.setVerticalGroup(WINDOW_LAYOUT
          .createSequentialGroup()
            .addGroup(WINDOW_LAYOUT.createSequentialGroup().addComponent(LOGO_PANEL))
            .addGroup(WINDOW_LAYOUT.createSequentialGroup().addComponent(TITLE))
            .addGroup(WINDOW_LAYOUT.createSequentialGroup().addComponent(CAROUSEL))
            .addGroup(WINDOW_LAYOUT.createSequentialGroup().addComponent(REGISTRATION_PANEL))
            .addGroup(WINDOW_LAYOUT.createSequentialGroup().addComponent(SOCIAL_PANEL))
            .addGroup(WINDOW_LAYOUT.createSequentialGroup().addComponent(FOOTER))
        );
      }

      // Update > ... -> Style UI components.
      WINDOW.getContentPane().setBackground(WINDOW_BACKGROUND_COLOR);
      WINDOW.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      WINDOW.setIconImage(new ImageIcon(APPLICATION_ICON_PATH).getImage()); // WARN (Lapys) -> Does not accept Windows `.ico` files.
      WINDOW.setLocation((int) ((SCREEN_WIDTH - WINDOW_WIDTH) / 2.0), (int) ((SCREEN_HEIGHT - WINDOW_HEIGHT) / 2.0));
      WINDOW.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
      WINDOW.setTitle(APPLICATION_NAME);

      // Event
        // (Login, Sign Up) Button
        LOGIN_BUTTON.addActionListener(new ActionListener() {
          @Override public void actionPerformed(final ActionEvent event) {}
        });

        SIGNUP_BUTTON.addActionListener(new ActionListener() {
          @Override public void actionPerformed(final ActionEvent event) {}
        });

      // Event
        // ...
        EventQueue.invokeLater(new Runnable() {
          @Override
          public void run() { WINDOW.setVisible(true); }
        });

        // Key -> Close `WINDOW` when "Escape" key is pressed.
        KeyboardFocusManager.getCurrentKeyboardFocusManager().addKeyEventDispatcher(new KeyEventDispatcher() {
          @Override
          public boolean dispatchKeyEvent(final KeyEvent event) {
            switch (event.getID()) {
              // [Key Down]
              case KeyEvent.KEY_PRESSED:
                if (KeyEvent.VK_ESCAPE == event.getKeyCode())
                WINDOW.dispatchEvent(new WindowEvent(WINDOW, WindowEvent.WINDOW_CLOSING));
              break;

              // [Key Up]
              case KeyEvent.KEY_RELEASED: break;
            }

            return false;
          }
        });
  }
}
