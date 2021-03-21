/* Import > ... */
// : Java > Abstract Window Toolkit
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.ComponentOrientation;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.font.TextLayout;
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

// : Java > Language
import java.lang.Exception;
import java.lang.Throwable;

// : Java > Structured Query Language (SQL)
import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

// : Java > Utilities
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

// : Java Extensions > Image Input/ Output
// : Java Extensions > Swing
import javax.swing.Action;
import javax.swing.BoxLayout;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ScrollPaneLayout;

/* Class --- REDACT (Lapys) --- NOTE (Lapys) */
// : Application
class Application {
    // ...
    public Application() {}
    public Application(final String name) { this.name = name; }

    // ...
    class DatabaseInformation {
        public Connection connection = null;
        public String name = null;
        public DatabaseMetaData metadata = null;
        public String password = "";
        public int port = 3306;
        public ArrayList<DatabaseTableInformation> tables = new ArrayList<DatabaseTableInformation>();
        public String user = "root";
    };

    class DatabaseTableInformation {
        public DatabaseTableInformation(final String name) { this.name = name; }

        public String catalog = null;
        public String name = null;
        public String remarks = null;
        public String schema = null;
        public String selfReferencingColumnName = null;
        public String selfReferencingColumnNameGeneration = null;
        public String type = null;
        public String typesCatalog = null;
        public String typesSchema = null;
        public String typeName = null;
    };

    class FontCollection {
        public Font dialog = new Font(Font.DIALOG, Font.PLAIN, 13);
        public Font dialogInput = new Font(Font.DIALOG_INPUT, Font.PLAIN, 13);
        public Font monospace = new Font(Font.MONOSPACED, Font.PLAIN, 13);
        public Font sansSerif = new Font(Font.SANS_SERIF, Font.PLAIN, 13);
        public Font serif = new Font(Font.SERIF, Font.PLAIN, 13);
    };

    // ...
    protected Application.DatabaseInformation database = new DatabaseInformation();
    protected String description = null;
    protected Application.FontCollection fonts = new FontCollection();
    protected String name = null;

    // ...
    protected boolean connectToDatabaseServer() {
        try {
            this.database.connection = DriverManager.getConnection("jdbc:mysql://localhost:" + this.database.port + '/', this.database.user, this.database.password);
            this.database.metadata = this.database.connection.getMetaData();

            return true;
        } catch (final SQLException error) { System.err.println(error); }

        return false;
    }

    protected void disconnectFromDatabaseServer() {
        try {
            if (null != this.database.connection) {
                this.database.connection.close();

                this.database.connection = null;
                this.database.metadata = null;
            }
        } catch (final SQLException error) { System.err.println(error); }
    }

    protected void evaluateDatabase() {
        try {
            final ResultSet databaseMetadataTables = this.database.metadata.getTables(null, null /* String schemaPattern */, "%" /* --> this.database.name */, new String[] {"TABLE"});
            final ResultSet databaseTables = this.queryDatabase("SHOW TABLES FROM `" + this.database.name + '`');

            for (; databaseMetadataTables.next(); databaseTables.first())
            while (databaseTables.next()) {
                final String databaseMetadataTableName = databaseMetadataTables.getString("TABLE_NAME");
                final String databaseTableName = databaseTables.getString(0x1);

                if (databaseTableName.equals(databaseMetadataTableName)) {
                    final DatabaseTableInformation databaseTable = new DatabaseTableInformation(databaseMetadataTableName);

                    databaseTable.catalog = databaseMetadataTables.getString("TABLE_CAT");
                    databaseTable.remarks = databaseMetadataTables.getString("REMARKS");
                    databaseTable.schema = databaseMetadataTables.getString("TABLE_SCHEM");
                    databaseTable.selfReferencingColumnName = databaseMetadataTables.getString("SELF_REFERENCING_COL_NAME");
                    databaseTable.selfReferencingColumnNameGeneration = databaseMetadataTables.getString("REF_GENERATION");
                    databaseTable.type = databaseMetadataTables.getString("TABLE_TYPE");
                    databaseTable.typesCatalog = databaseMetadataTables.getString("TYPE_CAT");
                    databaseTable.typesSchema = databaseMetadataTables.getString("TYPE_SCHEM");
                    databaseTable.typeName = databaseMetadataTables.getString("TYPE_NAME");

                    this.database.tables.add(databaseTable);
                    break;
                }
            }

            while (databaseTables.next()) {
                final String databaseTableName = databaseTables.getString(0x1);
                boolean hasDatabaseTable = false;

                for (final DatabaseTableInformation databaseTable : this.database.tables)
                if (databaseTableName.equals(databaseTable.name)) { hasDatabaseTable = true; break; }

                if (false == hasDatabaseTable)
                this.database.tables.add(new DatabaseTableInformation(databaseTableName));
            }
        } catch (final SQLException error) { System.err.println(error); }
    }

    protected boolean hasConnectedDatabaseServer() {
        try { return null != this.database.connection && false == this.database.connection.isClosed(); }
        catch (final SQLException error) { System.err.println(error); }

        return false;
    }

    protected int modifyDatabase(final String query) {
        try { return this.hasConnectedDatabaseServer() ? this.database.connection.createStatement().executeUpdate(query) : -1; }
        catch (final SQLException error) { System.err.println(error); }

        return -1;
    }

    protected ResultSet queryDatabase(final String query) {
        try { return this.hasConnectedDatabaseServer() ? this.database.connection.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY).executeQuery(query) : null; }
        catch (final SQLException error) { System.err.println(error); }

        return null;
    }

    protected boolean registerFont(final String name, final String path) {
        try {
            final Font font = Font.createFont(Font.TRUETYPE_FONT, new File(path)).deriveFont(13f);

            GraphicsEnvironment.getLocalGraphicsEnvironment().registerFont(font);
            switch (name) {
                case Font.DIALOG: this.fonts.dialog = font; break;
                case Font.DIALOG_INPUT: this.fonts.dialogInput = font; break;
                case Font.MONOSPACED: this.fonts.monospace = font; break;
                case Font.SANS_SERIF: this.fonts.sansSerif = font; break;
                case Font.SERIF: this.fonts.serif = font; break;
            }

            return true;
        } catch (final FontFormatException|IOException error) { System.err.println(error); }

        return false;
    }
};

// : Button -> Gradient background.
class Button extends JButton {};

// : Page -> Gradient background optimized for animations & transitions.
class Page extends JPanel {
    public Page() { super(true); }
    public Page(final boolean isDoubleBuffered) { super(isDoubleBuffered); }
    public Page(final LayoutManager layout) { super(layout); }
    public Page(final LayoutManager layout, final boolean isDoubleBuffered) { super(layout, isDoubleBuffered); }

    // ...
    @Override public boolean isOptimizedDrawingEnabled() { return false; }
    @Override protected void paintComponent(final Graphics graphics) { super.paintComponent(graphics); {
        final Graphics2D graphics2D = (Graphics2D) graphics;

        graphics2D.setPaint(new GradientPaint(0, 0, new Color(153, 0, 170), this.getWidth() / 8.0f, this.getHeight() * 1.25f, new Color(0, 51, 192)));
        graphics2D.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);

        graphics2D.fillRect(0, 0, this.getWidth(), this.getHeight());
    } }
};

// : Rounded Button
class RoundedButton extends JButton {};

// : Shadowed Text
class ShadowedText extends JLabel {
    // ...
    @Override
    public void paint(final Graphics graphics) {  {
        final Graphics2D graphics2D = (Graphics2D) graphics;
        final TextLayout textLayout = new TextLayout(this.getText(), this.getFont(), graphics2D.getFontRenderContext());

        graphics2D.setPaint(new Color(0.0f, 0.0f, 0.0f, 0.3f));
        textLayout.draw(graphics2D, this.getLocation().x + 3, this.getLocation().y + 3);

        graphics2D.setPaint(Color.BLACK);
        textLayout.draw(graphics2D, this.getLocation().x, this.getLocation().y);
    } super.paint(graphics); }
    public void paint(Graphics g) {
        String text = "Hello World";
        int x = 10;
        int y = 100;

        Font font = new Font("Georgia", Font.ITALIC, 50);
        Graphics2D g1 = (Graphics2D) g;

        TextLayout textLayout = new TextLayout(text, font, g1.getFontRenderContext());
        g1.setPaint(new Color(150, 150, 150));
        textLayout.draw(g1, x + 3, y + 3);

        g1.setPaint(Color.BLACK);
        textLayout.draw(g1, x, y);
      }
};

// : Window
class Window extends JFrame {
    public Window() { super(); }
    public Window(final GraphicsConfiguration graphicsConfiguration) { super(graphicsConfiguration); }
    public Window(final String title) { super(title); }
    public Window(final String title, final GraphicsConfiguration graphicsConfiguration) { super(title, graphicsConfiguration); }

    // ...
    class WindowException extends Exception {
        public WindowException() { super(); }
        public WindowException(final String message) { super(message); }
        public WindowException(final Throwable cause) { super(cause); }
        public WindowException(final String message, final Throwable cause) { super(message, cause); }
        public WindowException(final String message, final Throwable cause, final boolean enableSuppression, boolean writableStackTrace) { super(message, cause, enableSuppression, writableStackTrace); }
    };

    // ...
    protected Page activePage = null;
    private String faviconPath = null;
    private ArrayList<String> pageNames = new ArrayList<String>();
    protected ArrayList<Page> pages = new ArrayList<Page>();

    // ...
    protected Page addPage(final Container container, final String name) /* throws WindowException */ {
        for (final String pageName : this.pageNames) {
            try { if (name == pageName) throw new WindowException("`Page` component with the name `" + name.replaceAll("`", "\\`") + "` already exists"); }
            catch (final WindowException error) { System.err.println(error); }
        }

        final Page page = new Page(true /* boolean isDoubleBuffered */);

        container.add(page);
        page.setName(name);

        this.activePage = 0 == this.pages.size() ? page : this.activePage;
        this.pageNames.add(name);
        this.pages.add(page);

        return page;
    }
    protected String getFavicon() { return this.faviconPath; }
    protected Page getPageByName(final String name) { for (int iterator = 0; iterator != this.pageNames.size(); ++iterator) { if (name == this.pageNames.get(iterator)) return this.pages.get(iterator); } return null; }
    protected boolean hasPageByName(final String name) { for (final String pageName : this.pageNames) { if (name == pageName) return true; } return false; }
    protected boolean removePage(final String name) { for (int iterator = 0; iterator != this.pageNames.size(); ++iterator) { if (name == this.pageNames.get(iterator)) { this.pages.get(iterator).getParent().remove(this.pages.get(iterator)); return true; } } return false; }
    protected void setFavicon(final String path) { this.setIconImage(new ImageIcon(this.faviconPath = path).getImage()); }

    protected void switchToActivePage() { this.switchToPage(this.activePage); }
    protected void switchToActivePage(final int animationDuration, final int animationSpeed) { this.switchToPage(this.activePage, animationDuration, animationSpeed); }
    protected void switchToPage(final Page page) { this.switchToPage(page, 1, null == page ? 10 : page.getParent().getWidth()); }
    protected void switchToPage(final Page page, final int animationDuration, final int animationSpeed) {
        if (0 != this.pages.size()) {
            final Page currentActivePage = page;
            final Page recentActivePage = this.activePage;

            this.activePage = currentActivePage;

            for (final Page windowPage : this.pages)
            if (currentActivePage != windowPage && recentActivePage != windowPage) {
                final Container pageContainer = windowPage.getParent();

                windowPage.setLocation(pageContainer.getWidth(), 0);
                pageContainer.setComponentZOrder(windowPage, pageContainer.getComponentCount() - 1);
            }

            currentActivePage.getParent().setComponentZOrder(currentActivePage, 0);
            new Timer().scheduleAtFixedRate(new TimerTask() {
                @Override
                public void run() {
                    int currentActivePageXCoordinate = currentActivePage.getLocation().x;

                    if (0 == currentActivePageXCoordinate) { if (currentActivePage != recentActivePage) { recentActivePage.setLocation(recentActivePage.getParent().getWidth(), 0); } cancel(); }
                    else { currentActivePageXCoordinate -= animationSpeed; currentActivePage.setLocation(currentActivePageXCoordinate = currentActivePageXCoordinate < 0 ? 0 : currentActivePageXCoordinate, 0); }
                }
            }, 0, animationDuration);
        }
    }
};

/* Application */
public class Lapys extends Application {
    private enum State { INITIATING, RESETTING, UPDATING, TERMINATING };

    /* ... */
    static final Application application = new Application();
        static final int applicationDatabaseTableFieldCount = 6;
        static final String[] applicationDatabaseTableFieldNames = {"Age", "Gender", "ID", "Matriculation Number", "Name", "Program"};
        static final String[] applicationDatabaseTableFieldKeys = {null, null, "PRIMARY KEY", null, null, null};
        static final String[] applicationDatabaseTableFieldMiscellanies = {null, null, "AUTO_INCREMENT", null, null, null};
        static final boolean[] applicationDatabaseTableFieldNullities = {true, true, false, true, true, true};
        static final String[] applicationDatabaseTableFieldTypes = {"INT", "INT", "INT", "VARCHAR(24)", "VARCHAR(64)", "VARCHAR(64)"};
        static final String applicationDatabaseTableName = "Testers";
        static State applicationState;

    static final Window window = new Window();
        static final Container windowContentPane = window.getContentPane();
        static final JPanel windowPageContainer = new JPanel();

        static final Page dummyPage = window.addPage(windowPageContainer, "dummy");
        static final Page homePage = window.addPage(windowPageContainer, "home");
            static final JPanel homeCarousel = new JPanel();
            static final JLabel homeCarouselBackgroundMedia = new JLabel();
            static final Button homeCarouselButton = new Button();
            static final JLabel homeCarouselForegroundMedia = new JLabel();
            static final JPanel homeCarouselHeaderGroup = new JPanel();
            static final ShadowedText homeCarouselHeader = new ShadowedText();
            static final String[] homeCarouselMediaPaths = {
                "images/backgrounds/billboard.jpg",
                "images/backgrounds/campus.jpg",
                "images/backgrounds/college.jpg",
                "images/backgrounds/hostel.jpg",
                "images/backgrounds/senate.jpg",
                "images/backgrounds/sports.jpg"
            };
            static final JPanel homeCarouselIndicatorList = new JPanel();
            static final RoundedButton[] homeCarouselIndicators = new RoundedButton[homeCarouselMediaPaths.length];
            static final ShadowedText homeCarouselSubheader = new ShadowedText();

    /* Phases */
    /* : Initiate */
    protected static void Initiate(final String[] arguments) {
        // Modification > Application > ...
        application.database.name = "Java - Lapys (AI) Testers".toLowerCase(); // NOTE (Lapys) -> The MySQL database server does not persist the casing of table names.
        application.database.password = "Lapys30*)";
        application.database.port = 3306;
        application.database.user = "LapysDev";
        application.description = "Testing software application coupled with database and machine learning technologies";
        application.name = "Lapys (AI)";

        /* [Front-end] ... */ {
            // Constant > (Screen, Window) Size
            final Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
            final Dimension windowSize = new Dimension(
                (int) ((75.0f / 100.0f) * (float) screenSize.width),
                (int) ((75.0f / 100.0f) * (float) screenSize.height)
            );

            // Insertion
            homeCarousel.add(homeCarouselBackgroundMedia);
            homeCarousel.add(homeCarouselForegroundMedia);
            homeCarousel.add(homeCarouselHeaderGroup);
            homeCarousel.add(homeCarouselIndicatorList);
            homeCarouselHeaderGroup.add(homeCarouselHeader);
            homeCarouselHeaderGroup.add(homeCarouselSubheader);
            homePage.add(homeCarousel);
            window.add(windowPageContainer);

            // [Application] ...
            application.connectToDatabaseServer();
            application.registerFont(Font.MONOSPACED, "fonts/minecraft.otf");
            application.registerFont(Font.SANS_SERIF, "fonts/open-sans.ttf");

            // [Home] ...
            for (int iterator = 0; iterator != homeCarouselIndicators.length; ++iterator)
            homeCarouselIndicators[iterator] = new RoundedButton();

            homeCarousel.setBackground(Color.BLACK);
            homeCarousel.setLayout(null);

            homeCarouselHeader.setForeground(Color.WHITE);
            homeCarouselHeader.setFont(new Font(application.fonts.sansSerif.getName(), Font.BOLD, 30));
            homeCarouselHeader.setText("Carousel Title");

            homeCarouselHeaderGroup.setBackground(Color.BLUE);
            homeCarouselHeaderGroup.setLayout(new BoxLayout(homeCarouselHeaderGroup, BoxLayout.Y_AXIS));

            homeCarouselSubheader.setForeground(Color.WHITE);
            homeCarouselSubheader.setFont(new Font(application.fonts.sansSerif.getName(), Font.PLAIN, 20));
            homeCarouselSubheader.setText("Carousel Subtitle");

            homePage.setLayout(new BoxLayout(homePage, BoxLayout.Y_AXIS));

            // [Window] ...
            for (final Page windowPage : window.pages)
            windowPage.setSize(windowPageContainer.getSize());

            window.pack();
            window.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
            window.setDefaultCloseOperation(Window.EXIT_ON_CLOSE);
            window.setFavicon("images/favicon.png"); // WARN (Lapys) -> Does not accept `.ico` (`image/x-icon` MIME type) files.
            window.setLocation((screenSize.width - windowSize.width) / 2, (screenSize.height - windowSize.height) / 2); // --> window.setLocationRelativeTo(null);
            window.setMinimumSize(windowSize);
            window.setSize(windowSize);
            window.setTitle(application.name);
            window.setVisible(true);
            window.switchToPage(homePage);

            windowContentPane.setPreferredSize(windowSize);
            windowPageContainer.setLayout(null);
        }

        /* [Back-end] ... */ {
            // Initialization > Application Has Database Table
            boolean applicationHasDatabaseTable = false;

            // ... --- NOTE (Lapys) -> Get the database.
            application.modifyDatabase("CREATE DATABASE IF NOT EXISTS `" + application.database.name + '`');
            application.queryDatabase("USE `" + application.database.name + '`');
            application.evaluateDatabase();

            // ... Update > Application Has Database Table
            for (final Application.DatabaseTableInformation applicationDatabaseTable : application.database.tables)
            if (applicationDatabaseTableName.equalsIgnoreCase(applicationDatabaseTable.name)) { applicationHasDatabaseTable = true; break; }

            // Error Handling --- NOTE (Lapys) -> Get the database table.
            try {
                // Logic --- NOTE (Lapys) -> Ensure the table is as expected.
                if (applicationHasDatabaseTable) {
                    // ...; Loop
                    final ResultSet applicationDatabaseTableDescription = application.queryDatabase("DESCRIBE `" + applicationDatabaseTableName + '`');
                    for (boolean hasField; applicationHasDatabaseTable && applicationDatabaseTableDescription.next(); ) {
                        // Constant > Application Database Table Field (Key, Miscellany, Name, Nullity, Type)
                        final String applicationDatabaseTableFieldKey = applicationDatabaseTableDescription.getString("Key");
                        final String applicationDatabaseTableFieldMiscellany = applicationDatabaseTableDescription.getString("Extra");
                        final String applicationDatabaseTableFieldName = applicationDatabaseTableDescription.getString("Field");
                        final String applicationDatabaseTableFieldNullity = applicationDatabaseTableDescription.getString("Null");
                        final String applicationDatabaseTableFieldType = applicationDatabaseTableDescription.getString("Type");

                        // ...; Loop
                        hasField = false;
                        for (int iterator = 0; applicationDatabaseTableFieldCount != iterator && false == hasField; ++iterator) {
                            // Constant > ... Field (Key, Miscellany, Name, Nullity, Type)
                            final String fieldKey = applicationDatabaseTableFieldKeys[iterator];
                            final String fieldMiscellany = applicationDatabaseTableFieldMiscellanies[iterator];
                            final String fieldName = applicationDatabaseTableFieldNames[iterator];
                            final boolean fieldNullity = applicationDatabaseTableFieldNullities[iterator];
                            final String fieldType = applicationDatabaseTableFieldTypes[iterator];

                            // Logic > Assertion
                            if (applicationDatabaseTableFieldName == fieldName || applicationDatabaseTableFieldName.equalsIgnoreCase(fieldName)) {
                                // [Miscellany]
                                if (applicationHasDatabaseTable) {
                                    if (applicationDatabaseTableFieldMiscellany == fieldMiscellany) applicationHasDatabaseTable = true;
                                    else applicationHasDatabaseTable = null == fieldMiscellany ? applicationDatabaseTableFieldMiscellany.isEmpty() : applicationDatabaseTableFieldMiscellany.equalsIgnoreCase(fieldMiscellany);
                                }

                                // [Key]
                                if (applicationHasDatabaseTable) {
                                    if (applicationDatabaseTableFieldKey == fieldKey) applicationHasDatabaseTable = true;
                                    else if (null != fieldKey) {
                                        if (fieldKey.equals("MULTIPLE KEY")) applicationHasDatabaseTable = applicationDatabaseTableFieldKey.equalsIgnoreCase("MUL");
                                        else if (fieldKey.equals("PRIMARY KEY")) applicationHasDatabaseTable = applicationDatabaseTableFieldKey.equalsIgnoreCase("PRI");
                                        else if (fieldKey.equals("UNIQUE KEY")) applicationHasDatabaseTable = applicationDatabaseTableFieldKey.equalsIgnoreCase("UNI");
                                    }
                                }

                                // [Nullity]
                                if (applicationHasDatabaseTable) {
                                    if (false == fieldNullity) applicationHasDatabaseTable = applicationDatabaseTableFieldNullity.equals("NO");
                                    else if (true == fieldNullity) applicationHasDatabaseTable = applicationDatabaseTableFieldNullity.equals("YES");
                                }

                                // [Type]
                                if (applicationHasDatabaseTable) {
                                    if (applicationDatabaseTableFieldType == fieldType) applicationHasDatabaseTable = true;
                                    else applicationHasDatabaseTable = null == fieldType ? applicationDatabaseTableFieldType.isEmpty() : applicationDatabaseTableFieldType.equalsIgnoreCase(fieldType);
                                }

                                // Update > Has Field
                                hasField = true;
                            }
                        }

                        // ... Update > Application Has Database Table
                        if (false == hasField)
                        applicationHasDatabaseTable = false;
                    }
                }

                // Logic --- NOTE (Lapys) -> Either the table does not exist or has an unexpected description.
                if (false == applicationHasDatabaseTable) {
                    // ...; Loop
                    String applicationDatabaseTableSyntax = "";
                    for (int iterator = 0; applicationDatabaseTableFieldCount != iterator; ++iterator) {
                        // Constant > ... Field (Key, Miscellany, Name, Nullity, Type)
                        final String fieldDelimiter = applicationDatabaseTableFieldCount - 1 == iterator ? "" : ", ";
                        final String fieldKey = applicationDatabaseTableFieldKeys[iterator];
                        final String fieldMiscellany = applicationDatabaseTableFieldMiscellanies[iterator];
                        final String fieldName = applicationDatabaseTableFieldNames[iterator];
                        final boolean fieldNullity = applicationDatabaseTableFieldNullities[iterator];
                        final String fieldType = applicationDatabaseTableFieldTypes[iterator];

                        // Update > Application Database Table Syntax
                        applicationDatabaseTableSyntax += '`' + fieldName + "` ";
                        applicationDatabaseTableSyntax += fieldType;
                        applicationDatabaseTableSyntax += fieldNullity ? "" : " NOT NULL";
                        applicationDatabaseTableSyntax += null != fieldMiscellany ? ' ' + fieldMiscellany : "";
                        applicationDatabaseTableSyntax += null != fieldKey ? ", " : fieldDelimiter;
                        applicationDatabaseTableSyntax += null != fieldKey ? fieldKey + ' ' + "(`" + fieldName + "`)" + fieldDelimiter : "";
                    }

                    // ...
                    application.modifyDatabase("DROP TABLE IF EXISTS `" + applicationDatabaseTableName + '`');
                    application.modifyDatabase("CREATE TABLE `" + applicationDatabaseTableName + "` (" + applicationDatabaseTableSyntax + ')');
                }
            } catch (final Exception error) { System.err.println(error); }

            // DELETE FROM `Testers`;
            // DELETE FROM `Testers` WHERE `Age`=21';
            // DELETE FROM `Testers` WHERE `Name`='Lapys \'Lazuli?\'';
            // INSERT INTO `Testers` (`Age`, `Gender`, `Matriculation Number`, `Name`, `Program`) VALUES ('21', '0', '16CG021462', 'Lapys \'Lazuli?\'', 'Computing Science');
            // SELECT * FROM `Testers`; --> Age | Gender | ID | Matriculation Number | Name | Program
            // UPDATE `Testers` SET `Age`=22, `Name`='Lapys' WHERE `ID`=2;
        }

        /* Update */
        KeyboardFocusManager.getCurrentKeyboardFocusManager().addKeyEventDispatcher(new KeyEventDispatcher() { @Override public boolean dispatchKeyEvent(final KeyEvent event) {
            if (KeyEvent.KEY_PRESSED == event.getID()) window.switchToPage(homePage == window.activePage ? dummyPage : homePage, 3, 10);
            return false;
        } });
        Update();
    }

    /* : Reset */
    protected static void Reset(final int code) { /* ... */ }

    /* : Terminate */
    protected static void Terminate(final int code) {
        // ...
        application.disconnectFromDatabaseServer();
        System.exit(code);
    }

    /* : Update */
    protected static void Update() {
        // [Window] ...
        for (final Page windowPage : window.pages) windowPage.setSize(windowPageContainer.getSize());

        window.switchToActivePage();
        for (final Page windowPage : window.pages) windowPage.doLayout();

        // [Home] ...
        homeCarouselHeaderGroup.setLocation((int) (homeCarousel.getWidth() * (5.0f / 100.0f)), 15);
        homeCarouselHeaderGroup.setSize(new Dimension((int) (homeCarousel.getWidth() * (90.0f / 100.0f)), homeCarouselHeader.getHeight() + homeCarouselSubheader.getHeight()));
        homeCarouselHeaderGroup.doLayout();
    }

    /* Main */
    public static void main(final String[] arguments) {
        // Event
        // : ...
        EventQueue.invokeLater(new Runnable() { @Override public void run() { applicationState = State.INITIATING; Initiate(arguments); } });
        KeyboardFocusManager.getCurrentKeyboardFocusManager().addKeyEventDispatcher(new KeyEventDispatcher() { @Override public boolean dispatchKeyEvent(final KeyEvent event) { if (KeyEvent.KEY_PRESSED == event.getID() && KeyEvent.VK_ESCAPE == event.getKeyCode()) { window.dispatchEvent(new WindowEvent(window, WindowEvent.WINDOW_CLOSING)); } return false; } });

        // : Window > (Closing, Resize)
        window.addComponentListener(new ComponentAdapter() { @Override public void componentResized(final ComponentEvent event) { if (State.INITIATING == applicationState || State.UPDATING == applicationState) { applicationState = State.UPDATING; Update(); } } });
        window.addWindowListener(new WindowAdapter() { @Override public void windowClosing(final WindowEvent event) { if (State.INITIATING == applicationState || State.UPDATING == applicationState) { applicationState = State.TERMINATING; Terminate(0x0); } } });
    }
};
