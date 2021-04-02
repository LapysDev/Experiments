/* NOTE (Lapys) -> Compilation commands (on Windows administrative)
    attrib +r *.java
    cls
    asadmin start-domain --domaindir . web
    javac Lapys.java
    java -cp .;libraries/mysql-connector.jar Lapys
    asadmin stop-domain --domaindir . web
    del /q *
    attrib -r *.java
*/
/* Import > ... */
// : Java > Abstract Window Toolkit
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.ComponentOrientation;
import java.awt.Container;
import java.awt.Cursor;
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
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.Insets;
import java.awt.KeyboardFocusManager;
import java.awt.KeyEventDispatcher;
import java.awt.LayoutManager;
import java.awt.Point;
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
import java.lang.Integer;
import java.lang.Math;
import java.lang.System;

// : Java > Network
import java.net.URI;
import java.net.URISyntaxException;

// : Java > Structured Query Language (SQL)
import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

// : Java > Utilities
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Timer;
import java.util.TimerTask;

// : Java Extensions > Swing
import javax.swing.Action;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;
import javax.swing.ScrollPaneLayout;
import javax.swing.text.Document;

/* Class --- REDACT (Lapys) --- NOTE (Lapys) */
// : Application
class Application {
    // ...
    public Application() {}
    public Application(final String name) { this.name = name; }

    // ...
    protected class DatabaseInformation {
        public Connection connection = null;
        public String name = null;
        public DatabaseMetaData metadata = null;
        public String password = "";
        public int port = 3306;
        public ArrayList<DatabaseTableInformation> tables = new ArrayList<DatabaseTableInformation>();
        public String user = "root";
    };

    protected class DatabaseTableInformation {
        public DatabaseTableInformation(final String name) { this.name = name; }

        // ...
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

    protected class FontCollection {
        public Font dialog = new Font(Font.DIALOG, Font.PLAIN, 13);
        public Font dialogInput = new Font(Font.DIALOG_INPUT, Font.PLAIN, 13);
        public Font monospace = new Font(Font.MONOSPACED, Font.PLAIN, 13);
        public Font sansSerif = new Font(Font.SANS_SERIF, Font.PLAIN, 13);
        public Font serif = new Font(Font.SERIF, Font.PLAIN, 13);
    };

    // ...
    protected Color color = new Color(153, 0, 170);
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
                if (false == this.database.connection.isClosed())
                this.database.connection.close();

                this.database.connection = null;
                this.database.metadata = null;
            }
        } catch (final SQLException error) { System.err.println(error); }
    }

    protected void evaluateDatabase() {
        if (this.hasConnectedDatabaseServer())
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

// : Button
class Button extends JButton {
    public Button() { super(); this.setCursor(Button.CURSOR); }
    public Button(final Action action) { super(action); this.setCursor(Button.CURSOR); }
    public Button(final Icon icon) { super(icon); this.setCursor(Button.CURSOR); }
    public Button(final String text) { super(text); this.setCursor(Button.CURSOR); }
    public Button(final Action action, final Color backgroundColor) { super(action); this.setBackground(backgroundColor); this.setCursor(Button.CURSOR); }
    public Button(final Icon icon, final Color backgroundColor) { super(icon); this.setBackground(backgroundColor); this.setCursor(Button.CURSOR); }
    public Button(final String text, final Color backgroundColor) { super(text); this.setBackground(backgroundColor); this.setCursor(Button.CURSOR); }
    public Button(final String text, final Icon icon) { super(text, icon); this.setCursor(Button.CURSOR); }
    public Button(final String text, final Icon icon, final Color backgroundColor) { super(text, icon); this.setBackground(backgroundColor); this.setCursor(Button.CURSOR); }

    // ...
    final public static Cursor CURSOR = new Cursor(Cursor.HAND_CURSOR);

    // ...
    @Override protected void paintBorder(final Graphics graphics) {
        final Graphics2D graphics2D = (Graphics2D) graphics;

        if (this.getModel().isArmed()) {
            graphics2D.setColor(this.getForeground());
            graphics2D.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            graphics2D.drawRect(0, 0, this.getWidth(), this.getHeight());
        }
    }
};

// : Carousel
class Carousel extends Panel {
    public Carousel(final String... media) {
        super((LayoutManager) null, true);

        // ...
        CarouselIndicator.LAYOUT_CONSTRAINTS.anchor = GridBagConstraints.LAST_LINE_START;
        CarouselIndicator.LAYOUT_CONSTRAINTS.gridx = 0;
        CarouselIndicator.LAYOUT_CONSTRAINTS.gridy = 0;
        CarouselIndicator.LAYOUT_CONSTRAINTS.insets = new Insets(0, 5, 20, 5);
        CarouselIndicator.LAYOUT_CONSTRAINTS.weightx = 0.0f;
        CarouselIndicator.LAYOUT_CONSTRAINTS.weighty = 1.0f;

        this.activeMedia = this.foregroundMedia;

        // ...
        this.add(this.backgroundMedia);
        this.add(this.foregroundMedia);
        this.add(this.headerGroup);
        this.add(this.indicatorList);
        this.add(this.mediaFilter);

        this.headerGroup.add(this.header);
        this.headerGroup.add(this.subheader);

        // ...
        this.setBackground(Color.BLACK);
        this.setComponentZOrder(this.backgroundMedia, 4);
        this.setComponentZOrder(this.foregroundMedia, 3);
        this.setComponentZOrder(this.headerGroup, 1);
        this.setComponentZOrder(this.indicatorList, 0);
        this.setComponentZOrder(this.mediaFilter, 2);

        this.backgroundMedia.setHorizontalAlignment(ImageLabel.CENTER);
        this.backgroundMedia.setLocation(this.getWidth(), 0);

        this.foregroundMedia.setHorizontalAlignment(ImageLabel.CENTER);
        this.foregroundMedia.setLocation(0, 0);

        this.header.setText("Carousel Title");

        this.headerGroup.setLayout(new BoxLayout(this.headerGroup, BoxLayout.Y_AXIS));
        this.headerGroup.setLocation(0, 0);
        this.headerGroup.setOpaque(false);

        this.indicatorList.setLayout(new GridBagLayout());
        this.indicatorList.setLocation(0, 0);
        this.indicatorList.setOpaque(false);

        this.mediaFilter.setBackground(new Color(0.0f, 0.0f, 0.0f, 0.5f));
        this.mediaFilter.setLocation(0, 0);
        this.mediaFilter.setOpaque(true);

        this.subheader.setBorder(BorderFactory.createEmptyBorder(0, 20, 0, 0));
        this.subheader.setText("Carousel Flavor");

        // ...
        for (final String path : media)
        this.addMedia(path);
    }

    // ...
    private ImageLabel activeMedia;
    private String activeMediaPath;

    final protected ImageLabel backgroundMedia = new ImageLabel();
    final protected ImageLabel foregroundMedia = new ImageLabel();

    final protected ShadowedLabel header = new ShadowedLabel();
    final protected Panel headerGroup = new Panel();

    final protected Panel mediaFilter = new Panel(true);
    final private ArrayList<String> mediaPaths = new ArrayList<String>();

    private Color indicatorBackgroundColor = new Color(0.0f, 0.0f, 0.0f, 0.5f);
    private Color indicatorForegroundColor = new Color(1.0f, 1.0f, 1.0f, 0.5f);
    final protected Panel indicatorList = new Panel();
    private CarouselIndicator[] indicators = new CarouselIndicator[0];

    final protected ShadowedLabel subheader = new ShadowedLabel();

    // ...
    public void addMedia(final String path) { this.mediaPaths.add(path); this.updateComponents(); }
    public void addMedia(final String path, final String... paths) { this.mediaPaths.add(path); for (int iterator = 0; iterator != paths.length; ++iterator) { this.mediaPaths.add(paths[iterator]); } this.updateComponents(); }

    @Override public void doLayout() {
        super.doLayout();

        for (final Component component : this.getComponents())
        component.doLayout();
    }

    public Color getIndicatorBackground() { return this.indicatorBackgroundColor; }
    public int getIndicatorCount() { return this.indicators.length; }
    public Color getIndicatorForeground() { return this.indicatorForegroundColor; }
    public CarouselIndicator[] getIndicators() { return this.indicators; }

    public ArrayList<String> getMedia() { return this.mediaPaths; }
    public int getMediaCount() { return this.mediaPaths.size(); }

    public void removeMedia(final String path) { this.mediaPaths.remove(path); this.updateComponents(); }
    public void removeMedia(final String path, final String... paths) { this.mediaPaths.remove(path); for (int iterator = 0; iterator != paths.length; ++iterator) { this.mediaPaths.remove(paths[iterator]); } this.updateComponents(); }

    public void setIndicatorBackground(final Color color) { this.indicatorBackgroundColor = color; }
    public void setIndicatorForeground(final Color color) { this.indicatorForegroundColor = color; }

    protected void switchToMedia(final int index) {
        if (index < this.mediaPaths.size()) {
            final String mediaPath = this.mediaPaths.get(index);

            if (mediaPath != this.activeMediaPath) {
                final ImageLabel currentActiveMedia = this.activeMedia == this.backgroundMedia ? this.foregroundMedia : this.backgroundMedia;
                final ImageLabel recentActiveMedia = this.activeMedia;

                // ...
                this.activeMedia = currentActiveMedia;
                this.activeMediaPath = mediaPath;

                // ...
                this.setComponentZOrder(currentActiveMedia, this.getComponentCount() - 1);
                this.setComponentZOrder(recentActiveMedia, this.getComponentCount() - 2);

                recentActiveMedia.setImageIcon(new ImageIcon(mediaPath));

                // ...
                new Timer().scheduleAtFixedRate(new TimerTask() {
                    @Override public void run() {
                        int recentActiveMediaXCoordinate = recentActiveMedia.getLocation().x;

                        if (0 == recentActiveMediaXCoordinate) { currentActiveMedia.setLocation(currentActiveMedia.getParent().getWidth(), 0); cancel(); }
                        else { recentActiveMediaXCoordinate -= 10; recentActiveMedia.setLocation(recentActiveMediaXCoordinate = recentActiveMediaXCoordinate < 0 ? 0 : recentActiveMediaXCoordinate, 0); }
                    }
                }, 0, 3);
            }
        }
    }

    private void updateComponents() {
        int iterator = this.indicatorList.getComponentCount();
        final int length = this.mediaPaths.size();

        if (iterator != length) {
            this.indicators = new CarouselIndicator[length];

            while (iterator > length) this.indicatorList.remove(--iterator);

            for (; iterator++ != length; ++CarouselIndicator.LAYOUT_CONSTRAINTS.gridx) {
                this.indicatorList.add(new CarouselIndicator(this), CarouselIndicator.LAYOUT_CONSTRAINTS);
                CarouselIndicator.LAYOUT_CONSTRAINTS.gridx = iterator;
            }

            for (iterator = length; 0 != iterator--; ) this.indicators[iterator] = (CarouselIndicator) this.indicatorList.getComponent(iterator);
        }
    }
};

// : Carousel Indicator
class CarouselIndicator extends RoundedButton {
    public CarouselIndicator(final Carousel carousel) {
        super();

        this.carousel = carousel;

        this.addActionListener(CarouselIndicator.ACTION_LISTENER);
        this.setBackground(this.carousel.getIndicatorBackground());

        this.setForeground(this.carousel.getIndicatorForeground());
        this.setPreferredSize(this.getPreferredSize());
    }

    // ...
    final public static ActionListener ACTION_LISTENER = new ActionListener() {
        @Override public void actionPerformed(final ActionEvent event) {
            final CarouselIndicator indicator = (CarouselIndicator) event.getSource();
            final CarouselIndicator[] indicators = indicator.carousel.getIndicators();

            for (int iterator = 0; iterator != indicators.length; ++iterator)
            if (indicator == indicators[iterator]) {
                indicator.carousel.switchToMedia(iterator);
                break;
            }
        }
    };

    private Carousel carousel;
    final public static GridBagConstraints LAYOUT_CONSTRAINTS = new GridBagConstraints();

    // ...
    @Override public Dimension getPreferredSize() {
        final int size = (int) (Math.min(this.carousel.getHeight(), this.carousel.getWidth()) / 19.2f);
        return new Dimension(size, size);
    }
};

// : Frame
class Frame extends JFrame {
    public Frame() { super(); }
    public Frame(final GraphicsConfiguration graphicsConfiguration) { super(graphicsConfiguration); }
    public Frame(final String title) { super(title); }
    public Frame(final String title, final GraphicsConfiguration graphicsConfiguration) { super(title, graphicsConfiguration); }
};

// : Gradient Button
class GradientButton extends Button {
    public GradientButton() { super(); }
    public GradientButton(final Action action) { super(action); }
    public GradientButton(final Icon icon) { super(icon); }
    public GradientButton(final GradientPaint gradient) { super(); this.setGradient(gradient); }
    public GradientButton(final String text) { super(text); }
    public GradientButton(final Action action, final GradientPaint gradient) { super(action); this.setGradient(gradient); }
    public GradientButton(final Icon icon, final GradientPaint gradient) { super(icon); this.setGradient(gradient); }
    public GradientButton(final String text, final GradientPaint gradient) { super(text); this.setGradient(gradient); }
    public GradientButton(final String text, final Icon icon) { super(text, icon); }
    public GradientButton(final String text, final Icon icon, final GradientPaint gradient) { super(text, icon); this.setGradient(gradient); }

    // ...
    protected GradientPaint gradient = null;

    // ...
    public GradientPaint getGradient() { return this.gradient; }

    @Override protected void paintComponent(final Graphics graphics) {
        final GradientPaint gradient = this.getGradient();
        final Graphics2D graphics2D = (Graphics2D) graphics;

        if (null != gradient) {
            this.setBackground(new Color(0.0f, 0.0f, 0.0f, 0.0f));

            graphics2D.setPaint(gradient);
            graphics2D.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);

            graphics2D.fillRect(0, 0, this.getWidth(), this.getHeight());
        }

        super.paintComponent(graphics);
    }

    public void setGradient(final GradientPaint gradient) { this.gradient = gradient; }
};

// : Gradient Panel
class GradientPanel extends Panel {
    public GradientPanel() { super(true); }
    public GradientPanel(final boolean isDoubleBuffered) { super(isDoubleBuffered); }
    public GradientPanel(final LayoutManager layout) { super(layout); }
    public GradientPanel(final LayoutManager layout, final boolean isDoubleBuffered) { super(layout, isDoubleBuffered); }

    // ...
    protected GradientPaint gradient = null;

    // ...
    public GradientPaint getGradient() { return this.gradient; }
    @Override public boolean isOptimizedDrawingEnabled() { return false; }

    @Override protected void paintComponent(final Graphics graphics) {
        final GradientPaint gradient = this.getGradient();
        final Graphics2D graphics2D = (Graphics2D) graphics;

        super.paintComponent(graphics);
        if (null != gradient) {
            graphics2D.setPaint(gradient);
            graphics2D.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);

            graphics2D.fillRect(0, 0, this.getWidth(), this.getHeight());
        }
    }

    public void setGradient(final GradientPaint gradient) { this.gradient = gradient; }
};

// : Image Label
class ImageLabel extends Label {
    public ImageLabel() { super(); }
    public ImageLabel(final ImageIcon imageIcon) { super(imageIcon); this.setImageIcon(imageIcon); }
    public ImageLabel(final ImageIcon imageIcon, final int horizontalAlignment) { super(imageIcon, horizontalAlignment); this.setImageIcon(imageIcon); }

    // ...
    private Integer height = null;
    private ImageIcon imageIcon = null;
    private ImageIcon scaledImageIcon = null;
    private Integer width = null;

    // ...
    public ImageIcon getImageIcon() { return null == this.scaledImageIcon ? this.imageIcon : this.scaledImageIcon; }
    public Dimension getImageSize() { return null == this.getIcon() ? null : new Dimension(null == this.height ? this.getIcon().getIconHeight() : this.height.intValue(), null == this.width ? this.getIcon().getIconWidth() : this.width.intValue()); }

    public void setImageIcon(final ImageIcon imageIcon) { super.setIcon(this.imageIcon = imageIcon); }
    public void setImageSize(final Dimension size) {
        final ImageIcon imageIcon = this.imageIcon;

        if (null == size) {
            this.height = null;
            this.width = null;
            this.scaledImageIcon = null;

            this.setImageIcon(this.imageIcon);
        }

        else {
            this.height = new Integer(size.height);
            this.width = new Integer(size.width);
            this.scaledImageIcon = new ImageIcon(this.imageIcon.getImage().getScaledInstance(this.width.intValue(), this.height.intValue(), Image.SCALE_SMOOTH));

            this.setImageIcon(this.scaledImageIcon);
        }

        this.imageIcon = imageIcon;
    }
};

// : Label
class Label extends JLabel {
    public Label() { super(); }
    public Label(final Icon image) { super(image); }
    public Label(final String text) { super(text); }
    public Label(final Icon image, final int horizontalAlignment) { super(image, horizontalAlignment); }
    public Label(final String text, final int horizontalAlignment) { super(text, horizontalAlignment); }
    public Label(final String text, final Icon icon, final int horizontalAlignment) { super(text, icon, horizontalAlignment); }
};

// : Panel
class Panel extends JPanel {
    public Panel() { super(true); }
    public Panel(final boolean isDoubleBuffered) { super(isDoubleBuffered); }
    public Panel(final LayoutManager layout) { super(layout); }
    public Panel(final LayoutManager layout, final boolean isDoubleBuffered) { super(layout, isDoubleBuffered); }
};

// : Rounded Button
class RoundedButton extends Button {
    public RoundedButton() { super(); this.setContentAreaFilled(false); }
    public RoundedButton(final Action action) { super(action); this.setContentAreaFilled(false); }
    public RoundedButton(final ImageIcon imageIcon) { super(imageIcon); this.setContentAreaFilled(false); this.setImageIcon(imageIcon); }
    public RoundedButton(final String text) { super(text); this.setContentAreaFilled(false); }
    public RoundedButton(final Action action, final Color backgroundColor) { super(action); this.setBackground(backgroundColor); this.setContentAreaFilled(false); }
    public RoundedButton(final ImageIcon imageIcon, final Color backgroundColor) { super(imageIcon); this.setBackground(backgroundColor); this.setContentAreaFilled(false); this.setImageIcon(imageIcon); }
    public RoundedButton(final String text, final Color backgroundColor) { super(text); this.setBackground(backgroundColor); this.setContentAreaFilled(false); }
    public RoundedButton(final String text, final ImageIcon imageIcon) { super(text, imageIcon); this.setContentAreaFilled(false); this.setImageIcon(imageIcon); }
    public RoundedButton(final String text, final ImageIcon imageIcon, final Color backgroundColor) { super(text, imageIcon); this.setBackground(backgroundColor); this.setContentAreaFilled(false); this.setImageIcon(imageIcon); }

    private ImageIcon imageIcon = null;
    private Dimension imageSize = null;

    // ...
    @Override public boolean contains(final int x, final int y) { return new Ellipse2D.Float(0, this.getHeight() / 8, this.getWidth(), this.getHeight() - (this.getHeight() / 4)).contains(x, y);}

    public ImageIcon getImageIcon() { return this.imageIcon; }
    public Dimension getImageSize() { return null == this.imageIcon ? this.getSize() : this.imageSize; }

    @Override protected void paintBorder(final Graphics graphics) {
        final Graphics2D graphics2D = (Graphics2D) graphics;

        graphics2D.setColor(this.getForeground());
        graphics2D.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        graphics2D.drawOval(1, 1, this.getWidth() - 2, this.getHeight() - 2);
    }

    @Override protected void paintComponent(final Graphics graphics) {
        final Color backgroundColor = this.getBackground();
        final Icon icon = this.getIcon();
        final Graphics2D graphics2D = (Graphics2D) graphics;

        graphics2D.setColor(this.getModel().isArmed() ? new Color(backgroundColor.getRed(), backgroundColor.getGreen(), backgroundColor.getBlue(), backgroundColor.getAlpha() / 2) : backgroundColor);
        graphics2D.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        graphics2D.fillOval(0, 0, this.getWidth(), this.getHeight());
        if (null != icon) icon.paintIcon(this, graphics2D, 0, 0);
    }

    public void setImageIcon(final ImageIcon imageIcon) {
        this.imageIcon = 0 == this.getHeight() || 0 == this.getWidth() ? imageIcon : new ImageIcon(imageIcon.getImage().getScaledInstance(this.getWidth(), this.getHeight(), Image.SCALE_SMOOTH));
        this.imageSize = new Dimension(this.imageIcon.getIconWidth(), this.imageIcon.getIconHeight());
        super.setIcon(this.imageIcon);
    }

    public void setImageSize(final Dimension size) {
        if (null == this.imageIcon) this.imageSize = this.getSize();
        else { this.setImageIcon(new ImageIcon(this.imageIcon.getImage().getScaledInstance(size.width, size.height, Image.SCALE_SMOOTH))); this.imageSize = size; }
    }
};

// : Scroll Pane
class ScrollPane extends JScrollPane {
    public ScrollPane() { super(); }
    public ScrollPane(final Component view) { super(view); }
    public ScrollPane(final int verticalScrollbarPolicy, final int horizontalScrollbarPolicy) { super(verticalScrollbarPolicy, horizontalScrollbarPolicy); }
};

// : Shadowed Label
class ShadowedLabel extends Label {
    protected Color shadowColor = new Color(0.0f, 0.0f, 0.0f, 0.075f);
    protected Dimension shadowSize = new Dimension(5, 5);

    // ...
    public ShadowedLabel() { super(); }
    public ShadowedLabel(final Color color) { super(); this.setShadowColor(color); }
    public ShadowedLabel(final Icon image) { super(image); }
    public ShadowedLabel(final String text) { super(text); }
    public ShadowedLabel(final Color color, final Dimension size) { super(); this.setShadowColor(color); this.setShadowSize(size); }
    public ShadowedLabel(final Icon image, final Color color) { super(image); this.setShadowColor(color); }
    public ShadowedLabel(final Icon image, final int horizontalAlignment) { super(image, horizontalAlignment); }
    public ShadowedLabel(final String text, final Color color) { super(text); this.setShadowColor(color); }
    public ShadowedLabel(final String text, final int horizontalAlignment) { super(text, horizontalAlignment); }
    public ShadowedLabel(final Icon image, final Color color, final Dimension size) { super(image); this.setShadowColor(color); this.setShadowSize(size); }
    public ShadowedLabel(final Icon image, final int horizontalAlignment, final Color color) { super(image, horizontalAlignment); this.setShadowColor(color); }
    public ShadowedLabel(final String text, final Color color, final Dimension size) { super(text); this.setShadowColor(color); this.setShadowSize(size); }
    public ShadowedLabel(final String text, final int horizontalAlignment, final Color color) { super(text, horizontalAlignment); this.setShadowColor(color); }
    public ShadowedLabel(final String text, final Icon icon, final int horizontalAlignment) { super(text, icon, horizontalAlignment); }
    public ShadowedLabel(final Icon image, final int horizontalAlignment, final Color color, final Dimension size) { super(image, horizontalAlignment); this.setShadowColor(color); this.setShadowSize(size); }
    public ShadowedLabel(final String text, final int horizontalAlignment, final Color color, final Dimension size) { super(text, horizontalAlignment); this.setShadowColor(color); this.setShadowSize(size); }
    public ShadowedLabel(final String text, final Icon icon, final int horizontalAlignment, final Color color) { super(text, icon, horizontalAlignment); this.setShadowColor(color); }
    public ShadowedLabel(final String text, final Icon icon, final int horizontalAlignment, final Color color, final Dimension size) { super(text, icon, horizontalAlignment); this.setShadowColor(color); this.setShadowSize(size); }

    // ...
    protected Color getShadowColor() { return this.shadowColor; }
    protected Dimension getShadowSize() { return this.shadowSize; }

    @Override public void paintComponent(final Graphics graphics) {
        final Point origin = this.getLocationOnScreen();
        final Point rootPaneOrigin = this.getRootPane().getContentPane().getLocationOnScreen();

        final Graphics2D graphics2D = (Graphics2D) graphics;
        final TextLayout textLayout = new TextLayout(this.getText(), this.getFont(), graphics2D.getFontRenderContext());
        final int x = origin.x - rootPaneOrigin.x, y = origin.y - rootPaneOrigin.y;

        for (int shadowHeightOffset = this.shadowSize.height, shadowWidthOffset = this.shadowSize.width; 0 != shadowHeightOffset && 0 != shadowWidthOffset; --shadowHeightOffset, --shadowWidthOffset) {
            graphics2D.setPaint(this.shadowColor);
            textLayout.draw(graphics2D, x + shadowWidthOffset, y + shadowHeightOffset);
        }

        super.paintComponent(graphics);
    }

    protected void setShadowColor(final Color color) { this.shadowColor = color; }
    protected void setShadowSize(final Dimension size) { this.shadowSize = size; }
};

// : Text Field
class TextField extends JTextField {
    public TextField() { super(); }
    public TextField(final int columns) { super(columns); }
    public TextField(final String text) { super(text); }
    public TextField(final String text, final int columns) { super(text, columns); }
    public TextField(final Document document, final String text, final int columns) { super(document, text, columns); }
};

// : Window
class Window extends Frame {
    public Window() { super(); }
    public Window(final GraphicsConfiguration graphicsConfiguration) { super(graphicsConfiguration); }
    public Window(final String title) { super(title); }
    public Window(final String title, final GraphicsConfiguration graphicsConfiguration) { super(title, graphicsConfiguration); }

    // ...
    protected Container activePage = null;
    private String faviconPath = null;
    protected ArrayList<Container> pages = new ArrayList<Container>();

    // ...
    /* @Override protected void add() {} */
    protected Container addPage(final Container page) { return this.addPage(this, page); }
    protected Container addPage(final Container container, final Container page) {
        this.activePage = 0 == this.pages.size() ? page : this.activePage;
        this.pages.add(page);

        container.add(page);

        return page;
    }

    protected String getFavicon() { return this.faviconPath; }

    /* @Override protected void remove() {} */
    protected boolean removePage(final Container page) { return this.removePage(this, page); }
    protected boolean removePage(final Container container, final Container page) {
        for (final Container windowPage : this.pages)
        if (page == windowPage) { container.remove(page); return true; }

        return false;
    }

    protected void setFavicon(final String path) { this.setIconImage(new ImageIcon(this.faviconPath = path).getImage()); }

    protected void switchToActivePage() { this.switchToPage(this.activePage); }
    protected void switchToActivePage(final int animationDuration, final int animationSpeed) { this.switchToPage(this.activePage, animationDuration, animationSpeed); }
    protected void switchToPage(final Container page) { this.switchToPage(page, 1, null == page ? 10 : page.getParent().getWidth()); }
    protected void switchToPage(final Container page, final int animationDuration, final int animationSpeed) {
        if (0 != this.pages.size()) {
            final Container currentActivePage = page;
            final Container recentActivePage = this.activePage;

            this.activePage = currentActivePage;

            for (final Container windowPage : this.pages)
            if (currentActivePage != windowPage && recentActivePage != windowPage) {
                final Container pageContainer = windowPage.getParent();

                windowPage.setLocation(pageContainer.getWidth(), 0);
                pageContainer.setComponentZOrder(windowPage, pageContainer.getComponentCount() - 1);
            }

            currentActivePage.getParent().setComponentZOrder(currentActivePage, 0);
            new Timer().scheduleAtFixedRate(new TimerTask() {
                @Override public void run() {
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
    private enum RegistrationFormState { LOGIN, SIGN_IN };

    /* ... */
    final static Application application = new Application();
        final static int applicationDatabaseTableFieldCount = 6;
        final static String[] applicationDatabaseTableFieldNames = {"Age", "Gender", "ID", "Matriculation Number", "Name", "Program"};
        final static String[] applicationDatabaseTableFieldKeys = {null, null, "PRIMARY KEY", null, null, null};
        final static String[] applicationDatabaseTableFieldMiscellanies = {null, null, "AUTO_INCREMENT", null, null, null};
        final static boolean[] applicationDatabaseTableFieldNullities = {true, true, false, true, true, true};
        final static String[] applicationDatabaseTableFieldTypes = {"INT", "INT", "INT", "VARCHAR(24)", "VARCHAR(64)", "VARCHAR(64)"};
        final static String applicationDatabaseTableName = "Testers";
        static State applicationState;

    final static Window window = new Window();
        final static Container windowContentPane = window.getContentPane();
        final static Panel windowPageContainer = new Panel((LayoutManager) null);

        final static Panel accountPage = (Panel) window.addPage(windowPageContainer, new Panel(new GridBagLayout()));
            final static Label accountAgeValue = new Label();
            final static Label accountGenderValue = new Label();
            final static Label accountMatriculationNumberValue = new Label();
            final static Label accountNameValue = new Label();
            final static Label accountProgramValue = new Label();

            final static Panel[] accountContainers = new Panel[5];
            final static Label[] accountLabels = {new Label("Age"), new Label("Gender"), new Label("Matriculation Number"), new Label("Name"), new Label("Program")};
            final static Label[] accountValues = {accountAgeValue, accountGenderValue, accountMatriculationNumberValue, accountNameValue, accountProgramValue};

        final static ScrollPane homePage = (ScrollPane) window.addPage(windowPageContainer, new ScrollPane());
        final static GradientPanel homePageContent = new GradientPanel(true);
            final static Carousel homeCarousel = new Carousel(
                "images/backgrounds/billboard.jpg",
                "images/backgrounds/campus.jpg",
                "images/backgrounds/college.jpg",
                "images/backgrounds/hostel.jpg",
                "images/backgrounds/senate.jpg",
                "images/backgrounds/sports.jpg"
            );
            final static GradientButton homeCarouselButton = new GradientButton();
            final static Panel homeCarouselButtonContainer = new Panel(new BorderLayout());
            final static Panel homeCarouselButtonSubcontainer = new Panel(new FlowLayout(FlowLayout.RIGHT, 40, 0));

            final static Panel homeIntroduction = new Panel(new FlowLayout(FlowLayout.LEADING, 0, 0));
            final static Panel homeIntroductionCardDescriptionContainer = new Panel(new GridLayout(1, 3, 40, 50));
            final static Label[] homeIntroductionCardDescriptions = {
                // [Airplane]
                new Label(
                    "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" + "\n" +
                    "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," + "\n" +
                    "quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo" + "\n" +
                    "consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse" + "\n" +
                    "cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non" + "\n" +
                    "proident, sunt in culpa qui officia deserunt mollit anim id est laborum." + "\n"
                ),

                // [Auction]
                new Label(
                    "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" + "\n" +
                    "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," + "\n" +
                    "quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo" + "\n" +
                    "consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse" + "\n" +
                    "cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non" + "\n" +
                    "proident, sunt in culpa qui officia deserunt mollit anim id est laborum." + "\n"
                ),

                // [Fuel]
                new Label(
                    "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" + "\n" +
                    "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," + "\n" +
                    "quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo" + "\n" +
                    "consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse" + "\n" +
                    "cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non" + "\n" +
                    "proident, sunt in culpa qui officia deserunt mollit anim id est laborum." + "\n"
                )
            };
            final static Panel homeIntroductionCardIconContainer = new Panel(new GridLayout(1, 3, 40, 50));
            final static ImageLabel[] homeIntroductionCardIcons = {
                /* [Airplane] */ new ImageLabel(new ImageIcon("images/icons/airplane.png")),
                /* [Auction]  */ new ImageLabel(new ImageIcon("images/icons/auction.png")),
                /* [Fuel]     */ new ImageLabel(new ImageIcon("images/icons/fuel.png"))
            };

            final static Panel homeFooter = new Panel(new GridBagLayout());
            final static Panel homeFooterDivider = new Panel();
            final static GradientButton homeFooterNewsletterButton = new GradientButton();
            final static Panel homeFooterNewsletterButtonContainer = new Panel(new FlowLayout(FlowLayout.CENTER, 0, 0));
            final static Panel homeFooterNewsletterContainer = new Panel(new GridLayout(2, 1));
            final static TextField homeFooterNewsletterField = new TextField(30);
            final static Panel homeFooterNewsletterFieldContainer = new Panel(new FlowLayout(FlowLayout.CENTER, 0, 0));
            final static Panel homeFooterSocialsButtonContainer = new Panel(new GridBagLayout());
            final static RoundedButton[] homeFooterSocialsButtons = {
                new RoundedButton(new ImageIcon("images/icons/facebook.png"), new Color(60, 90, 153)),
                new RoundedButton(new ImageIcon("images/icons/linkedin.png"), new Color(16, 96, 166)),
                new RoundedButton(new ImageIcon("images/icons/twitter.png"), new Color(29, 161, 242)),
                new RoundedButton(new ImageIcon("images/icons/youtube.png"), new Color(255, 0, 0))
            };
            final static Label homeFooterSocialsCallToAction = new Label();
            final static Panel homeFooterSocialsContainer = new Panel();
            final static Label homeFooterSocialsCopyright = new Label();

            final static Panel homeShowcase = new Panel(new GridLayout(2, 1));
            final static ShadowedLabel homeShowcaseHeader = new ShadowedLabel();
            final static ShadowedLabel homeShowcaseSubheader = new ShadowedLabel();

        final static GradientPanel registrationPage = (GradientPanel) window.addPage(windowPageContainer, new GradientPanel((LayoutManager) null, true));
            final static TextField registrationLoginAgeField = new TextField(20);
            final static Label registrationLoginAgeLabel = new Label();
            final static Button registrationLoginButton = new Button();
            final static TextField registrationLoginGenderField = new TextField(20);
            final static Label registrationLoginGenderLabel = new Label();
            final static TextField registrationLoginMatriculationNumberField = new TextField(20);
            final static Label registrationLoginMatriculationNumberLabel = new Label();
            final static TextField registrationLoginNameField = new TextField(20);
            final static Label registrationLoginNameLabel = new Label();
            final static Panel registrationLoginPanel = new Panel(new GridBagLayout());
            final static TextField registrationLoginProgramField = new TextField(20);
            final static Label registrationLoginProgramLabel = new Label();
            final static Button registrationLoginSubmit = new Button();

            final static Panel[] registrationLoginContainers = new Panel[5];
            final static TextField[] registrationLoginFields = {registrationLoginAgeField, registrationLoginGenderField, registrationLoginMatriculationNumberField, registrationLoginNameField, registrationLoginProgramField};
            final static Label[] registrationLoginLabels = {registrationLoginAgeLabel, registrationLoginGenderLabel, registrationLoginMatriculationNumberLabel, registrationLoginNameLabel, registrationLoginProgramLabel};

            final static Button registrationSignInButton = new Button();
            final static Panel registrationSignInMatriculationNumberContainer = new Panel(new GridLayout(2, 1));
            final static TextField registrationSignInMatriculationNumberField = new TextField(20);
            final static Label registrationSignInMatriculationNumberLabel = new Label();
            final static Panel registrationSignInPanel = new Panel();
            final static Button registrationSignInSubmit = new Button();

            final static Panel registrationTabContainer = new Panel(new FlowLayout(FlowLayout.CENTER, 0, 0));
            final static Panel registrationTabSubcontainer = new Panel(new GridLayout(1, 2));

            static RegistrationFormState registrationState = RegistrationFormState.SIGN_IN;

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
            // Constant > ...
            final Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
            final Dimension windowSize = new Dimension((int) ((75.0f / 100.0f) * (float) screenSize.width), (int) ((75.0f / 100.0f) * (float) screenSize.height));

            // Insertion > ...
            for (int iterator = 0; iterator != accountContainers.length; ++iterator) {
                final Panel accountContainer = new Panel(new FlowLayout(FlowLayout.LEADING, 0, 0));

                accountContainers[iterator] = accountContainer;
                accountValues[iterator] = new Label();

                accountPage.add(accountContainer, new GridBagConstraints(0, iterator, 1, 1, 1.0, 1.0, GridBagConstraints.CENTER, GridBagConstraints.HORIZONTAL, new Insets(5, 0, 5, 0), 0, 0));

                accountContainer.add(accountLabels[iterator]);
                accountContainer.add(accountValues[iterator]);
            }

            homeCarousel.add(homeCarouselButtonContainer);
            homeCarouselButtonContainer.add(homeCarouselButtonSubcontainer, BorderLayout.PAGE_END);
            homeCarouselButtonSubcontainer.add(homeCarouselButton);

            homeFooter.add(homeFooterNewsletterContainer, new GridBagConstraints(0, 0, 1, 1, 1.0, 0.45, GridBagConstraints.CENTER, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 0, 0));
            homeFooter.add(homeFooterDivider, new GridBagConstraints(0, 1, 1, 1, 1.0, 0.1, GridBagConstraints.CENTER, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 0, 0));
            homeFooter.add(homeFooterSocialsContainer, new GridBagConstraints(0, 2, 1, 1, 1.0, 0.45, GridBagConstraints.CENTER, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 0, 0));

            homeFooterNewsletterButtonContainer.add(homeFooterNewsletterButton);

            homeFooterNewsletterContainer.add(homeFooterNewsletterFieldContainer);
            homeFooterNewsletterContainer.add(homeFooterNewsletterButtonContainer);

            homeFooterNewsletterFieldContainer.add(homeFooterNewsletterField);

            homeFooterSocialsContainer.add(homeFooterSocialsCallToAction);
            homeFooterSocialsContainer.add(homeFooterSocialsButtonContainer);
            homeFooterSocialsContainer.add(homeFooterSocialsCopyright);

            for (int iterator = 0; iterator != homeFooterSocialsButtons.length; ++iterator)
            homeFooterSocialsButtonContainer.add(homeFooterSocialsButtons[iterator], new GridBagConstraints(iterator, 0, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(0, 10, 0, 10), 0, 0));

            homeIntroduction.add(homeIntroductionCardIconContainer);
            homeIntroduction.add(homeIntroductionCardDescriptionContainer);
            for (final Label homeIntroductionCardDescription : homeIntroductionCardDescriptions) homeIntroductionCardDescriptionContainer.add(homeIntroductionCardDescription);
            for (final ImageLabel homeIntroductionCardIcon : homeIntroductionCardIcons) homeIntroductionCardIconContainer.add(homeIntroductionCardIcon);

            homePageContent.add(homeCarousel);
            homePageContent.add(homeShowcase);
            homePageContent.add(homeIntroduction);
            homePageContent.add(homeFooter);

            homeShowcase.add(homeShowcaseHeader);
            homeShowcase.add(homeShowcaseSubheader);

            for (int iterator = 0; iterator != registrationLoginContainers.length; ++iterator) {
                final Panel registrationLoginContainer = new Panel(new GridLayout(2, 1));

                registrationLoginContainers[iterator] = registrationLoginContainer;

                registrationLoginPanel.add(registrationLoginContainer, new GridBagConstraints(0, iterator, 1, 1, 1.0, 1.0, GridBagConstraints.CENTER, GridBagConstraints.HORIZONTAL, new Insets(5, 0, 5, 0), 0, 0));

                registrationLoginContainer.add(registrationLoginLabels[iterator]);
                registrationLoginContainer.add(registrationLoginFields[iterator]);
            }

            registrationLoginPanel.add(registrationLoginSubmit, new GridBagConstraints(0, registrationLoginContainers.length, 1, 1, 1.0, 1.0, GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(5, 0, 5, 0), 0, 0));

            registrationPage.add(registrationTabContainer);
            registrationPage.add(registrationLoginPanel);
            registrationPage.add(registrationSignInPanel);

            registrationSignInPanel.add(registrationSignInMatriculationNumberContainer);
            registrationSignInPanel.add(registrationSignInSubmit);

            registrationSignInMatriculationNumberContainer.add(registrationSignInMatriculationNumberLabel);
            registrationSignInMatriculationNumberContainer.add(registrationSignInMatriculationNumberField);

            registrationTabContainer.add(registrationTabSubcontainer);

            registrationTabSubcontainer.add(registrationLoginButton);
            registrationTabSubcontainer.add(registrationSignInButton);

            window.add(windowPageContainer);

            // Event > ...
            homeCarouselButton.addActionListener(new ActionListener() {
                @Override public void actionPerformed(final ActionEvent event) {
                    window.switchToPage(registrationPage, 3, 10);
                }
            });

            registrationLoginButton.addActionListener(new ActionListener() {
                @Override public void actionPerformed(final ActionEvent event) {
                    registrationState = RegistrationFormState.LOGIN;

                    registrationLoginButton.setBackground(Color.WHITE);
                    registrationLoginButton.setForeground(application.color);

                    registrationSignInButton.setBackground(application.color);
                    registrationSignInButton.setForeground(Color.WHITE);

                    Update();
                }
            });

            registrationLoginSubmit.addActionListener(new ActionListener() {
                @Override public void actionPerformed(final ActionEvent event) {
                    window.switchToPage(accountPage, 3, 10);

                    // accountAgeValue.setText(registrationLoginAgeField.getText());
                    // accountGenderValue.setText(registrationLoginGenderField.getText());
                    // accountMatriculationNumberValue.setText(registrationLoginMatriculationNumberField.getText());
                    // accountNameValue.setText(registrationLoginNameField.getText());
                    // accountProgramValue.setText(registrationLoginProgramField.getText());
                }
            });

            registrationSignInButton.addActionListener(new ActionListener() {
                @Override public void actionPerformed(final ActionEvent event) {
                    registrationState = RegistrationFormState.SIGN_IN;

                    registrationLoginButton.setBackground(application.color);
                    registrationLoginButton.setForeground(Color.WHITE);

                    registrationSignInButton.setBackground(Color.WHITE);
                    registrationSignInButton.setForeground(application.color);

                    Update();
                }
            });

            // ...
            // : [Application] ...
            application.connectToDatabaseServer();
            application.registerFont(Font.MONOSPACED, "fonts/minecraft.otf");
            application.registerFont(Font.SANS_SERIF, "fonts/open-sans.ttf");

            // : [Home] ...
            homeCarousel.setComponentZOrder(homeCarouselButtonContainer, 2);
            homeCarousel.switchToMedia(0); {
                homeCarousel.header.setFont(new Font(application.fonts.sansSerif.getName(), Font.BOLD, 42));
                homeCarousel.header.setForeground(Color.WHITE);

                homeCarousel.subheader.setForeground(Color.WHITE);
                homeCarousel.subheader.setFont(new Font(application.fonts.sansSerif.getName(), Font.PLAIN, 24));
            }

            homeCarouselButton.setFont(new Font(application.fonts.sansSerif.getName(), Font.PLAIN, 20));
            homeCarouselButton.setForeground(Color.WHITE);
            homeCarouselButton.setMargin(new Insets(5, 10, 5, 10));
            homeCarouselButton.setText("Login / Signup");

            homeCarouselButtonContainer.setOpaque(false);

            homeCarouselButtonSubcontainer.setBorder(BorderFactory.createEmptyBorder(0, 0, 60, 0));
            homeCarouselButtonSubcontainer.setOpaque(false);

            homeFooter.setBackground(application.color);

            homeFooterDivider.setBackground(Color.GRAY);

            homeFooterNewsletterButton.setForeground(Color.WHITE);
            homeFooterNewsletterButton.setFont(new Font(application.fonts.sansSerif.getName(), Font.PLAIN, 20));
            homeFooterNewsletterButton.setPreferredSize(new Dimension(500, 50));
            homeFooterNewsletterButton.setText("Subscribe");

            homeFooterNewsletterButtonContainer.setOpaque(false);

            homeFooterNewsletterContainer.setOpaque(false);

            homeFooterNewsletterField.setPreferredSize(new Dimension(300, 50));

            homeFooterNewsletterFieldContainer.setOpaque(false);

            homeFooterSocialsCallToAction.setFont(new Font(application.fonts.sansSerif.getName(), Font.PLAIN, 16));
            homeFooterSocialsCallToAction.setForeground(Color.WHITE);
            homeFooterSocialsCallToAction.setHorizontalAlignment(Label.CENTER);
            homeFooterSocialsCallToAction.setText("or you can check out our other handles");

            homeFooterSocialsContainer.setLayout(new GridLayout(3, 1));
            homeFooterSocialsContainer.setOpaque(false);

            homeFooterSocialsButtonContainer.setOpaque(false);

            homeFooterSocialsCopyright.setFont(new Font(application.fonts.sansSerif.getName(), Font.PLAIN, 16));
            homeFooterSocialsCopyright.setForeground(Color.WHITE);
            homeFooterSocialsCopyright.setHorizontalAlignment(Label.CENTER);
            homeFooterSocialsCopyright.setText("<html> &#169; Copyright " + Calendar.getInstance().get(Calendar.YEAR) + " LapysDev </html>");

            homeIntroduction.setBackground(Color.WHITE);

            homeIntroductionCardDescriptionContainer.setOpaque(false);

            homeIntroductionCardIconContainer.setOpaque(false);

            homePage.setBorder(null);
            homePage.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
            homePage.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
            homePage.setViewportView(homePageContent);

            homePageContent.setLayout(new BoxLayout(homePageContent, BoxLayout.Y_AXIS));

            homeShowcase.setOpaque(false);

            homeShowcaseHeader.setBorder(BorderFactory.createEmptyBorder(0, 50, 15, 0));
            homeShowcaseHeader.setFont(new Font(application.fonts.sansSerif.getName(), Font.BOLD, 40));
            homeShowcaseHeader.setForeground(Color.WHITE);
            homeShowcaseHeader.setText("Lapys AI");
            homeShowcaseHeader.setVerticalAlignment(ShadowedLabel.BOTTOM);

            homeShowcaseSubheader.setBorder(BorderFactory.createEmptyBorder(15, 75, 0, 0));
            homeShowcaseSubheader.setFont(new Font(application.fonts.sansSerif.getName(), Font.BOLD, 30));
            homeShowcaseSubheader.setForeground(Color.WHITE);
            homeShowcaseSubheader.setText("Creativity, Development, Innovation");
            homeShowcaseSubheader.setVerticalAlignment(ShadowedLabel.TOP);

            new Timer().scheduleAtFixedRate(new TimerTask() {
                int homeCarouselCurrentMediaIndex = 0;

                @Override public void run() {
                    ++homeCarouselCurrentMediaIndex;
                    homeCarousel.switchToMedia(homeCarouselCurrentMediaIndex = homeCarouselCurrentMediaIndex > homeCarousel.getMediaCount() - 1 ? 0 : homeCarouselCurrentMediaIndex);
                }
            }, 0, 5000);

            for (final RoundedButton homeFooterSocialsButton : homeFooterSocialsButtons) {
                homeFooterSocialsButton.setBackground(Color.WHITE);
                homeFooterSocialsButton.setForeground(new Color(0.0f, 0.0f, 0.0f, 0.0f));
            }

            for (final Label homeIntroductionCardDescription : homeIntroductionCardDescriptions) {
                homeIntroductionCardDescription.setBorder(BorderFactory.createEmptyBorder(20, 50, 20, 50));
                homeIntroductionCardDescription.setHorizontalAlignment(Label.LEFT);
                homeIntroductionCardDescription.setVerticalAlignment(Label.TOP);
                homeIntroductionCardDescription.setOpaque(false);
                homeIntroductionCardDescription.setText("<html> " + homeIntroductionCardDescription.getText().replaceAll("\n", "<br/>") + " </html>");
            }

            for (final ImageLabel homeIntroductionCardIcon : homeIntroductionCardIcons) {
                homeIntroductionCardIcon.setHorizontalAlignment(ImageLabel.CENTER);
                homeIntroductionCardIcon.setVerticalAlignment(ImageLabel.CENTER);
            }

            // : [Registration] ...
            registrationLoginButton.setBackground(application.color);
            registrationLoginButton.setFont(new Font(application.fonts.sansSerif.getName(), Font.PLAIN, 25));
            registrationLoginButton.setForeground(Color.WHITE);
            registrationLoginButton.setText("LOGIN");

            registrationLoginAgeLabel.setText("Age");

            registrationLoginGenderLabel.setText("Gender");

            registrationLoginMatriculationNumberLabel.setText("Matriculation Number");

            registrationLoginNameLabel.setText("Name");

            registrationLoginPanel.setBackground(Color.WHITE);

            registrationLoginProgramLabel.setText("Program");

            registrationLoginSubmit.setBackground(application.color);
            registrationLoginSubmit.setFont(new Font(application.fonts.sansSerif.getName(), Font.BOLD, 26));
            registrationLoginSubmit.setForeground(Color.WHITE);
            registrationLoginSubmit.setMinimumSize(new Dimension(200, (registrationLoginSubmit.getFont().getSize() * 11) / 10));
            registrationLoginSubmit.setText("Submit");

            registrationSignInButton.setBackground(Color.WHITE);
            registrationSignInButton.setFont(new Font(application.fonts.sansSerif.getName(), Font.PLAIN, 25));
            registrationSignInButton.setForeground(application.color);
            registrationSignInButton.setText("SIGN IN");

            registrationSignInMatriculationNumberField.setBorder(BorderFactory.createLineBorder(application.color.brighter(), 1));
            registrationSignInMatriculationNumberField.setFont(new Font(application.fonts.sansSerif.getName(), Font.PLAIN, 25));
            registrationSignInMatriculationNumberField.setForeground(Color.DARK_GRAY);

            registrationSignInMatriculationNumberLabel.setBackground(application.color);
            registrationSignInMatriculationNumberLabel.setBorder(BorderFactory.createEmptyBorder(10, 15, 10, 15));
            registrationSignInMatriculationNumberLabel.setForeground(Color.WHITE);
            registrationSignInMatriculationNumberLabel.setFont(new Font(application.fonts.sansSerif.getName(), Font.PLAIN, 30));
            registrationSignInMatriculationNumberLabel.setOpaque(true);
            registrationSignInMatriculationNumberLabel.setText("Matriculation Number");

            registrationSignInPanel.setBackground(Color.WHITE);

            for (final Panel registrationLoginContainer : registrationLoginContainers) {
                registrationLoginContainer.setBackground(new Color(0.0f, 0.0f, 0.0f, 0.0f));
                registrationLoginContainer.setBorder(BorderFactory.createEmptyBorder(0, 100, 0, 100));
                registrationLoginContainer.setOpaque(false);
            }

            for (final Label registrationLoginLabel : registrationLoginLabels) {
                registrationLoginLabel.setBackground(application.color);
                registrationLoginLabel.setBorder(BorderFactory.createEmptyBorder(5, 10, 5, 10));
                registrationLoginLabel.setFont(new Font(application.fonts.sansSerif.getName(), Font.PLAIN, 15));
                registrationLoginLabel.setForeground(Color.WHITE);
                registrationLoginLabel.setOpaque(true);
            }

            for (final TextField registrationLoginField : registrationLoginFields) {
                registrationLoginField.setBorder(BorderFactory.createLineBorder(application.color.brighter(), 1));
                registrationLoginField.setForeground(Color.DARK_GRAY);
            }

            // : [Window] ...
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

            // try { java.awt.Desktop.getDesktop().browse(new URI("http://localhost:8080/predict/car-fuel.jsp")); }
            // catch (final IOException|URISyntaxException error) { System.err.println(error); }
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
        Update();
    }

    /* : Reset */
    protected static void Reset(final int code) { /* Do nothing */ }

    /* : Terminate */
    protected static void Terminate(final int code) {
        // ...
        application.disconnectFromDatabaseServer();
        System.exit(code);
    }

    /* : Update */
    protected static void Update() {
        // [Window] ...
        for (final Container windowPage : window.pages) {
            if (windowPage instanceof GradientPanel) { ((GradientPanel) windowPage).setGradient(new GradientPaint(0.0f, 0.0f, application.color, windowPage.getWidth() / 8.0f, windowPage.getHeight() * 2.0f, Color.BLUE)); }

            windowPage.setPreferredSize(windowPageContainer.getSize());
            windowPage.setSize(windowPageContainer.getSize());
            windowPage.doLayout();
        }

        window.switchToActivePage();

        // [Home] ...
        homePageContent.setGradient(new GradientPaint(0.0f, 0.0f, application.color, homePageContent.getWidth() / 6.0f, homePageContent.getHeight() * 0.375f, Color.BLUE));
        homePageContent.setSize(new Dimension(homePage.getWidth(), homePage.getHeight() * homePageContent.getComponentCount()));

        for (final Component homePageSection : homePageContent.getComponents()) {
            homePageSection.setPreferredSize(homePage.getSize());
            homePageSection.setSize(homePage.getSize());
        }

        // [Home Carousel] ...
        homeCarouselButton.setBackground(application.color);
        homeCarouselButton.setGradient(new GradientPaint(0.0f, 0.0f, application.color, homeCarouselButton.getWidth() / 8.0f, homeCarouselButton.getHeight() * 1.25f, Color.BLUE));

        homeCarouselButtonContainer.setSize(homeCarousel.getSize());
        homeCarouselButtonContainer.doLayout();
        homeCarouselButtonSubcontainer.doLayout();

        homeCarousel.backgroundMedia.setSize(homeCarousel.getSize());
        homeCarousel.foregroundMedia.setSize(homeCarousel.getSize());

        homeCarousel.headerGroup.setLocation((int) (homeCarousel.getWidth() * (5.0f / 100.0f)), 15);
        homeCarousel.headerGroup.setSize(new Dimension((int) (homeCarousel.getWidth() * (90.0f / 100.0f)), homeCarousel.header.getHeight() + homeCarousel.subheader.getHeight()));

        homeCarousel.indicatorList.setSize(new Dimension(homeCarousel.getWidth() / 2, homeCarousel.getHeight()));
        for (final CarouselIndicator homeCarouselIndicator : homeCarousel.getIndicators()) homeCarouselIndicator.setPreferredSize(homeCarouselIndicator.getPreferredSize());

        homeCarousel.mediaFilter.setSize(homeCarousel.getSize());

        homeCarousel.doLayout();
        homeCarousel.switchToMedia(0);

        // [Home Footer] ...
        homeFooterDivider.setMaximumSize(new Dimension(homeFooter.getWidth(), 5));
        homeFooterNewsletterButton.setGradient(new GradientPaint(0.0f, 0.0f, application.color, homeFooterNewsletterButton.getPreferredSize().width / 8.0f, homeFooterNewsletterButton.getPreferredSize().height * 1.25f, Color.BLUE));
        homeFooterNewsletterContainer.setMinimumSize(new Dimension(homeFooter.getWidth(), 50 + homeFooterNewsletterButton.getPreferredSize().height + homeFooterNewsletterField.getPreferredSize().height));

        for (final RoundedButton homeFooterSocialsButton : homeFooterSocialsButtons) {
            homeFooterSocialsButton.setImageSize(new Dimension(65, 65));
            homeFooterSocialsButton.setPreferredSize(homeFooterSocialsButton.getImageSize());
            homeFooterSocialsButton.setSize(homeFooterSocialsButton.getImageSize());
        }

        // [Home Introduction] ...
        homeIntroductionCardDescriptionContainer.setPreferredSize(new Dimension(homeIntroduction.getWidth(), (homeIntroduction.getHeight() * 3) / 5));
        homeIntroductionCardDescriptionContainer.setSize(homeIntroductionCardDescriptionContainer.getPreferredSize());

        homeIntroductionCardIconContainer.setPreferredSize(new Dimension(homeIntroduction.getWidth(), (homeIntroduction.getHeight() * 2) / 5));
        homeIntroductionCardIconContainer.setSize(homeIntroductionCardIconContainer.getPreferredSize());

        for (final ImageLabel homeIntroductionCardIcon : homeIntroductionCardIcons) {
            final int homeIntroductionCardIconSize = Math.min((homeIntroductionCardIcon.getHeight() * 4) / 5, (homeIntroductionCardIcon.getWidth() * 4) / 5);
            homeIntroductionCardIcon.setImageSize(new Dimension(homeIntroductionCardIconSize, homeIntroductionCardIconSize));
        }

        // [Home Showcase] ...
        homeShowcase.setPreferredSize(new Dimension(homePage.getWidth(), homePage.getHeight() / 2));

        // [Registration] ...
        registrationTabContainer.setLayout(new GridLayout(1, 1));
        registrationTabContainer.setLocation((registrationPage.getWidth() * 1) / 10, (registrationPage.getHeight() * 1) / 10);
        registrationTabContainer.setSize(new Dimension((registrationPage.getWidth() * 4) / 5, 40));
        registrationTabContainer.doLayout();

        registrationLoginPanel.setLocation(RegistrationFormState.LOGIN == registrationState ? (registrationPage.getWidth() * 1) / 10 : registrationPage.getWidth(), registrationTabContainer.getSize().height + registrationTabContainer.getLocation().y);
        registrationLoginPanel.setSize(new Dimension((registrationPage.getWidth() * 4) / 5, (registrationPage.getHeight() * 4) / 5));

        registrationSignInPanel.setLocation(RegistrationFormState.SIGN_IN == registrationState ? (registrationPage.getWidth() * 1) / 10 : registrationPage.getWidth(), registrationTabContainer.getSize().height + registrationTabContainer.getLocation().y);
        registrationSignInPanel.setSize(new Dimension((registrationPage.getWidth() * 4) / 5, (registrationPage.getHeight() * 4) / 5));
    }

    /* Main */
    public static void main(final String[] arguments) {
        // Event
        // : ...
        EventQueue.invokeLater(new Runnable() { @Override public void run() { applicationState = State.INITIATING; Initiate(arguments); } });
        KeyboardFocusManager.getCurrentKeyboardFocusManager().addKeyEventDispatcher(new KeyEventDispatcher() { @Override public boolean dispatchKeyEvent(final KeyEvent event) { if (KeyEvent.KEY_PRESSED == event.getID() && KeyEvent.VK_ESCAPE == event.getKeyCode()) { if (false == window.getFocusOwner() instanceof TextField) window.dispatchEvent(new WindowEvent(window, WindowEvent.WINDOW_CLOSING)); } return false; } });

        // : Window > (Closing, Resize)
        window.addComponentListener(new ComponentAdapter() { @Override public void componentResized(final ComponentEvent event) { if (State.INITIATING == applicationState || State.UPDATING == applicationState) { applicationState = State.UPDATING; Update(); } } });
        window.addWindowListener(new WindowAdapter() { @Override public void windowClosing(final WindowEvent event) { if (State.INITIATING == applicationState || State.UPDATING == applicationState) { applicationState = State.TERMINATING; Terminate(0x0); } } });
    }
};
