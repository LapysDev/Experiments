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
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ScrollPaneLayout;

/* Class --- REDACT (Lapys) */
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

    enum State {
        INITIATING,
        RESETTING,
        UPDATING,
        TERMINATING
    };

    // ...
    protected Application.DatabaseInformation database = new DatabaseInformation();
    protected String description = null;
    protected Application.FontCollection fonts = new FontCollection();
    protected String name = null;
    protected Application.State state;

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

// : Page
class Page extends JPanel {};

// : Window
class Window extends JFrame {
    protected Page activePage;
    protected ArrayList<Page> pages;

    // ...
    public Window() { super(); }
    public Window(final GraphicsConfiguration graphicsConfiguration) { super(graphicsConfiguration); }
    public Window(final String title) { super(title); }
    public Window(final String title, final GraphicsConfiguration graphicsConfiguration) { super(title, graphicsConfiguration); }

    // ...
    protected void setFavicon(final String path) { this.setIconImage(new ImageIcon(path).getImage()); }

    protected void switchToPage(final Page form) { this.switchToPage(form, 0); }
    protected void switchToPage(final Page form, final int animationDuration) {}
};

// : ...

/* Application */
public class Lapys extends Application {
    /* ... */
    static final Application application = new Application();
        static final int applicationDatabaseTableFieldCount = 6;
        static final String[] applicationDatabaseTableFieldNames = {"Age", "Gender", "ID", "Matriculation Number", "Name", "Program"};
        static final String[] applicationDatabaseTableFieldKeys = {null, null, "PRIMARY KEY", null, null, null};
        static final String[] applicationDatabaseTableFieldMiscellanies = {null, null, "AUTO_INCREMENT", null, null, null};
        static final boolean[] applicationDatabaseTableFieldNullities = {true, true, false, true, true, true};
        static final String[] applicationDatabaseTableFieldTypes = {"INT", "INT", "INT", "VARCHAR(24)", "VARCHAR(64)", "VARCHAR(64)"};
        static final String applicationDatabaseTableName = "Testers";

    static final Window window = new Window();

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

            // ...
            application.connectToDatabaseServer();
            application.registerFont(Font.MONOSPACED, "fonts/minecraft.otf");
            application.registerFont(Font.SANS_SERIF, "fonts/open-sans.ttf");

            window.pack();
            window.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
            window.setDefaultCloseOperation(Window.EXIT_ON_CLOSE);
            window.setFavicon("images/favicon.png"); // WARN (Lapys) -> Does not accept `.ico` (`image/x-icon` MIME type) files.
            window.setLocation((screenSize.width - windowSize.width) / 2, (screenSize.height - windowSize.height) / 2); // --> window.setLocationRelativeTo(null);
            window.setMinimumSize(windowSize);
            window.setSize(windowSize);
            window.setTitle(application.name);
            window.setVisible(true);
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

            // INSERT INTO `Testers` (`Age`, `Gender`, `Matriculation Number`, `Name`, `Program`) VALUES ('21', '0', '16CG021462', 'Lapys \'Lazuli?\'', 'Computing Science');
            // SELECT * FROM `Testers`; --> Age | Gender | ID | Matriculation Number | Name | Program
            // DELETE FROM `Testers`;
            // DELETE FROM `Testers` WHERE `Age`=21';
            // DELETE FROM `Testers` WHERE `Name`='Lapys \'Lazuli?\'';
            // UPDATE `Testers` SET `Age`=22, `Name`='Lapys' WHERE `ID`=2;
        }
    }

    /* : Reset */
    protected static void Reset(final int code) { /* ... */ }

    /* : Terminate */
    protected static void Terminate(final int code) {
        application.disconnectFromDatabaseServer();
        System.exit(code);
    }

    /* : Update */
    protected static void Update() {}

    /* Main */
    public static void main(final String[] arguments) {
        // Event
        // : ...
        EventQueue.invokeLater(new Runnable() { @Override public void run() { application.state = Application.State.INITIATING; Initiate(arguments); } });
        KeyboardFocusManager.getCurrentKeyboardFocusManager().addKeyEventDispatcher(new KeyEventDispatcher() { @Override public boolean dispatchKeyEvent(final KeyEvent event) { if (KeyEvent.KEY_PRESSED == event.getID() && KeyEvent.VK_ESCAPE == event.getKeyCode()) { window.dispatchEvent(new WindowEvent(window, WindowEvent.WINDOW_CLOSING)); } return false; } });

        // : Window > (Closing, Resize)
        window.addComponentListener(new ComponentAdapter() { @Override public void componentResized(final ComponentEvent event) { if (Application.State.INITIATING == application.state || Application.State.UPDATING == application.state) { application.state = Application.State.UPDATING; Update(); } } });
        window.addWindowListener(new WindowAdapter() { @Override public void windowClosing(final WindowEvent event) { if (Application.State.INITIATING == application.state || Application.State.UPDATING == application.state) { application.state = Application.State.TERMINATING; Terminate(0x0); } } });
    }
};
