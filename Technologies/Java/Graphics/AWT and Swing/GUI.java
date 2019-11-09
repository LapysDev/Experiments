/* Import */
// Java
import java.awt.*; // Abstract Window Toolkit
import java.awt.event.*;
import java.awt.image.*;
import java.io.*; // Input-Output
import java.nio.file.*; // Non-Blocking Input-Output
import java.util.*; // Utilities
import java.util.stream.*;

// Java Extension
import javax.imageio.ImageIO; // Image Input-Output
import javax.swing.*; // Swing

/* ... */
class GUI extends JFrame {
    // ...
    @SuppressWarnings("unchecked")

    /* [Constructor] */
    public GUI() {
        // Modification > Target > ...
        this.components = new Components();
        this.playlist = new Playlist();
        this.poster = new Poster();
    }

    /* Class */
        // Components --- NOTE (Lapys) -> All components are stored here.
        private class Components {
            // Initialization > ...
            private JLabel header = new JLabel();
            private JButton loopButton = new JButton();
            private JPanel main = new JPanel();
            private JLabel musicArtiste = new JLabel();
            private JLabel musicDuration = new JLabel();
            private JSlider musicSeeker = new JSlider();
            private JLabel musicTimestamp = new JLabel();
            private JLabel musicTitle = new JLabel();
            private JButton nextSongButton = new JButton();
            private JButton playButton = new JButton();
            private Canvas poster = new Canvas();
            private JButton previousSongButton = new JButton();
            private JButton shuffleButton = new JButton();
            private JToolBar toolbar = new JToolBar();
            private JToggleButton toolbarMenuButton = new JToggleButton();
        };

        // Playlist
        private class Playlist {
            // [Constructor]
            Playlist() { this.update(); }

            // Initialization > Songs
            private File[] songs;

            // Phase > Update --- NOTE (Lapys) -> Update the array of songs in the playlist.
            private void update() {
                // Constant > (Playlist, ...)
                final Playlist playlist = this;
                final Path path = Paths.get("playlist.txt");

                // Error Handling
                try(BufferedReader reader = Files.newBufferedReader(path)) {
                    // Initialization > ...; Loop
                    String subsource = "";
                    do {
                        // Logic
                        if (!subsource.isEmpty()) {
                            // Constant > ...
                            final int playlistSongsLength = playlist.songs.length;
                            final File[] recentPlaylistSongs = new File[playlistSongsLength];

                            // (Loop > )Update > ...
                            for (int iterator = 0; iterator != playlistSongsLength; iterator += 1) recentPlaylistSongs[iterator] = playlist.songs[iterator];
                            playlist.songs = new File[playlistSongsLength + 1];
                            for (int iterator = 0; iterator != playlistSongsLength; iterator += 1) playlist.songs[iterator] = recentPlaylistSongs[iterator];

                            // Update > (Playlist > Songs)
                            playlist.songs[playlistSongsLength] = new File(subsource);
                        }

                        // Update > ...
                        subsource = reader.readLine();
                    } while (subsource != null);
                } catch (IOException error) { error.printStackTrace(); JOptionPane.showMessageDialog(null, "Could not update the playlist", title, JOptionPane.ERROR_MESSAGE); }
            }
        };

        // Poster
        private class Poster {
            // Initialization > Image
            private File image;

            // Method > ...
            private File getImage() { return this.image; }
            private String getImageName() { return this.image.getName(); }
            private String getImagePath() { return this.image.getPath(); }
            private boolean hasImage() { return this.image.exists() && !this.image.isDirectory(); }
            private void setImage(File image) { if (image.isFile()) this.image = image; else JOptionPane.showMessageDialog(null, "Could not load the poster for this song", title, JOptionPane.ERROR_MESSAGE); }
        };

    /* Initialization > ... */
    private Components components;
    private String description = "";
    private String favicon = "";
    private String name = "";
    private Playlist playlist;
    private Poster poster;
    private String title = "";

    /* Phase > Initiate */
    private void initiate() {
        // Constant > (Application, ...)
        final GUI application = this;
        final Components components = application.components;
        final Playlist playlist = application.playlist;
        final Poster poster = application.poster;

        // Modification
            // Components
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

                // Loop Button > ...
                components.loopButton.setBackground(new Color(255, 255, 255));
                components.loopButton.setBorder(null);
                components.loopButton.setBorderPainted(false);
                components.loopButton.setFont(new Font("Google Sans", 1, 20)); // NOTE (Lapys) -> No Internationalization.
                components.loopButton.setForeground(new Color(33, 33, 33));
                components.loopButton.setHorizontalTextPosition(SwingConstants.CENTER);
                components.loopButton.setMargin(new Insets(0, 0, 0, 0));
                components.loopButton.setMaximumSize(new Dimension(40, 40));
                components.loopButton.setMinimumSize(new Dimension(40, 40));
                components.loopButton.setPreferredSize(new Dimension(40, 40));
                components.loopButton.setSize(new Dimension(40, 40));
                components.loopButton.setToolTipText("Loop");
                components.loopButton.setVerticalTextPosition(SwingConstants.CENTER);

                // Main > ...
                components.main.setAlignmentX(0.0f);
                components.main.setAlignmentY(0.0f);
                components.main.setBackground(new Color(255, 255, 255));
                components.main.setForeground(new Color(51, 51, 51));
                components.main.setFocusable(false);
                components.main.setFont(new Font("Roboto", 0, 16)); // NOTE (Lapys) -> No Internationalization.
                components.main.setMaximumSize(new Dimension(400, 500));
                components.main.setMinimumSize(new Dimension(400, 500));
                components.main.setPreferredSize(new Dimension(400, 500));
                components.main.setRequestFocusEnabled(false);
                components.main.setVerifyInputWhenFocusTarget(false);

                // Music Artist > ...
                components.musicArtiste.getAccessibleContext().setAccessibleDescription("The artiste of the current media/ song");
                components.musicArtiste.getAccessibleContext().setAccessibleName("Music Artiste");

                components.musicArtiste.setAlignmentX(0.5f);
                components.musicArtiste.setAlignmentY(0.5f);
                components.musicArtiste.setBackground(new Color(255, 255, 255));
                components.musicArtiste.setEnabled(false);
                components.musicArtiste.setFocusable(false);
                components.musicArtiste.setFont(new Font("Google Sans", 0, 24)); // NOTE (Lapys) -> No Internationalization.
                components.musicArtiste.setForeground(new Color(102, 102, 102));
                components.musicArtiste.setHorizontalAlignment(SwingConstants.CENTER);
                components.musicArtiste.setHorizontalTextPosition(SwingConstants.CENTER);
                components.musicArtiste.setMaximumSize(new Dimension(400, 30));
                components.musicArtiste.setMinimumSize(new Dimension(400, 30));
                components.musicArtiste.setPreferredSize(new Dimension(400, 30));
                components.musicArtiste.setRequestFocusEnabled(false);
                components.musicArtiste.setSize(new Dimension(400, 30));
                components.musicArtiste.setText("...");
                components.musicArtiste.setVerifyInputWhenFocusTarget(false);
                components.musicArtiste.setVerticalAlignment(SwingConstants.CENTER);
                components.musicArtiste.setVerticalTextPosition(SwingConstants.CENTER);

                // Music Duration > ...
                components.musicDuration.setAlignmentX(1.0f);
                components.musicDuration.setAlignmentY(1.0f);
                components.musicDuration.setBackground(new Color(255, 255, 255));
                components.musicDuration.setEnabled(false);
                components.musicDuration.setFocusable(false);
                components.musicDuration.setFont(new Font("Roboto", 0, 16)); // NOTE (Lapys) -> No Internationalization.
                components.musicDuration.setForeground(new Color(33, 33, 33));
                components.musicDuration.setHorizontalAlignment(SwingConstants.CENTER);
                components.musicDuration.setHorizontalTextPosition(SwingConstants.CENTER);
                components.musicDuration.setMaximumSize(new Dimension(75, 40));
                components.musicDuration.setMinimumSize(new Dimension(75, 40));
                components.musicDuration.setPreferredSize(new Dimension(75, 40));
                components.musicDuration.setRequestFocusEnabled(false);
                components.musicDuration.setSize(new Dimension(75, 40));
                components.musicDuration.setText("-:--");
                components.musicDuration.setVerifyInputWhenFocusTarget(false);
                components.musicDuration.setVerticalAlignment(SwingConstants.CENTER);
                components.musicDuration.setVerticalTextPosition(SwingConstants.CENTER);

                // Music Seeker > ...
                components.musicSeeker.setBackground(new Color(255, 255, 255));
                components.musicSeeker.setCursor(new Cursor(Cursor.HAND_CURSOR));
                components.musicSeeker.setFont(new Font("Roboto", 0, 16)); // NOTE (Lapys) -> No Internationalization.
                components.musicSeeker.setForeground(new Color(102, 102, 102));
                components.musicSeeker.setMaximumSize(new Dimension(355, 30));
                components.musicSeeker.setMinimumSize(new Dimension(355, 30));
                components.musicSeeker.setPaintLabels(true);
                components.musicSeeker.setPreferredSize(new Dimension(355, 30));
                components.musicSeeker.setSize(new Dimension(355, 30));
                components.musicSeeker.setValue(0);

                // Music Timestamp > ...
                components.musicTimestamp.setBackground(new Color(255, 255, 255));
                components.musicTimestamp.setEnabled(false);
                components.musicTimestamp.setFocusable(false);
                components.musicTimestamp.setFont(new Font("Roboto", 0, 16)); // NOTE (Lapys) -> No Internationalization.
                components.musicTimestamp.setForeground(new Color(33, 33, 33));
                components.musicTimestamp.setHorizontalAlignment(SwingConstants.CENTER);
                components.musicTimestamp.setHorizontalTextPosition(SwingConstants.CENTER);
                components.musicTimestamp.setMaximumSize(new Dimension(75, 40));
                components.musicTimestamp.setMinimumSize(new Dimension(75, 40));
                components.musicTimestamp.setPreferredSize(new Dimension(75, 40));
                components.musicTimestamp.setRequestFocusEnabled(false);
                components.musicTimestamp.setSize(new Dimension(75, 40));
                components.musicTimestamp.setText("-:--");
                components.musicTimestamp.setVerifyInputWhenFocusTarget(false);
                components.musicTimestamp.setVerticalAlignment(SwingConstants.CENTER);
                components.musicTimestamp.setVerticalTextPosition(SwingConstants.CENTER);

                // Music Title > ...
                components.musicTitle.getAccessibleContext().setAccessibleDescription("The title of the current media/ song");
                components.musicTitle.getAccessibleContext().setAccessibleName("Music Title");

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
                components.musicTitle.setSize(new Dimension(400, 40));
                components.musicTitle.setText("...");
                components.musicTitle.setVerifyInputWhenFocusTarget(false);
                components.musicTitle.setVerticalAlignment(SwingConstants.CENTER);
                components.musicTitle.setVerticalTextPosition(SwingConstants.CENTER);

                // Next Song Button > ...
                components.nextSongButton.setBackground(new Color(255, 255, 255));
                components.nextSongButton.setBorder(null);
                components.nextSongButton.setBorderPainted(false);
                components.nextSongButton.setFont(new Font("Google Sans", 1, 20)); // NOTE (Lapys) -> No Internationalization.
                components.nextSongButton.setForeground(new Color(33, 33, 33));
                components.nextSongButton.setHorizontalTextPosition(SwingConstants.CENTER);
                components.nextSongButton.setMargin(new Insets(0, 0, 0, 0));
                components.nextSongButton.setMaximumSize(new Dimension(40, 40));
                components.nextSongButton.setMinimumSize(new Dimension(40, 40));
                components.nextSongButton.setPreferredSize(new Dimension(40, 40));
                components.nextSongButton.setSize(new Dimension(40, 40));
                components.nextSongButton.setToolTipText("Next Song");
                components.nextSongButton.setVerticalTextPosition(SwingConstants.CENTER);

                // Play Button > ...
                components.playButton.setBackground(new Color(255, 255, 255));
                components.playButton.setBorder(null);
                components.playButton.setBorderPainted(false);
                components.playButton.setFont(new Font("Google Sans", 1, 20)); // NOTE (Lapys) -> No Internationalization.
                components.playButton.setForeground(new Color(33, 33, 33));
                components.playButton.setHorizontalTextPosition(SwingConstants.CENTER);
                components.playButton.setMargin(new Insets(0, 0, 0, 0));
                components.playButton.setMaximumSize(new Dimension(40, 40));
                components.playButton.setMinimumSize(new Dimension(40, 40));
                components.playButton.setPreferredSize(new Dimension(40, 40));
                components.playButton.setSize(new Dimension(40, 40));
                components.playButton.setToolTipText("Play");
                components.playButton.setVerticalTextPosition(SwingConstants.CENTER);

                // Poster > ...
                components.poster = new Canvas()  {
                    // Method > Paint
                    public void paint(Graphics graphics) {
                        // Logic
                        if (application.poster.hasImage())
                            // Error Handling > ...
                            try { graphics.drawImage(ImageIO.read(application.poster.getImage()), 0, 0, 200, 200, null); }
                            catch (IOException error) { error.printStackTrace(); System.exit(1); }
                    }
                };
                components.poster.getAccessibleContext().setAccessibleDescription("Poster");
                components.poster.getAccessibleContext().setAccessibleName("Poster");

                components.poster.setBackground(new Color(0, 0, 0));
                components.poster.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
                components.poster.setEnabled(false);
                components.poster.setFont(new Font("Roboto", 0, 16)); // NOTE (Lapys) -> No Internationalization.
                components.poster.setMaximumSize(new Dimension(200, 200));
                components.poster.setMinimumSize(new Dimension(200, 200));
                components.poster.setName("Poster"); // NOTE (Lapys) -> No Internationalization.
                components.poster.setPreferredSize(new Dimension(200, 200));

                // Previous Song Button > ...
                components.previousSongButton.setBackground(new Color(255, 255, 255));
                components.previousSongButton.setBorder(null);
                components.previousSongButton.setBorderPainted(false);
                components.previousSongButton.setFont(new Font("Google Sans", 1, 20)); // NOTE (Lapys) -> No Internationalization.
                components.previousSongButton.setForeground(new Color(33, 33, 33));
                components.previousSongButton.setHorizontalTextPosition(SwingConstants.CENTER);
                components.previousSongButton.setMargin(new Insets(0, 0, 0, 0));
                components.previousSongButton.setMaximumSize(new Dimension(40, 40));
                components.previousSongButton.setMinimumSize(new Dimension(40, 40));
                components.previousSongButton.setPreferredSize(new Dimension(40, 40));
                components.previousSongButton.setSize(new Dimension(40, 40));
                components.previousSongButton.setToolTipText("Previous Song");
                components.previousSongButton.setVerticalTextPosition(SwingConstants.CENTER);

                components.shuffleButton.setBackground(new Color(255, 255, 255));
                components.shuffleButton.setBorder(null);
                components.shuffleButton.setBorderPainted(false);
                components.shuffleButton.setFont(new Font("Google Sans", 1, 20)); // NOTE (Lapys) -> No Internationalization.
                components.shuffleButton.setForeground(new Color(33, 33, 33));
                components.shuffleButton.setHorizontalTextPosition(SwingConstants.CENTER);
                components.shuffleButton.setMargin(new Insets(0, 0, 0, 0));
                components.shuffleButton.setMaximumSize(new Dimension(40, 40));
                components.shuffleButton.setMinimumSize(new Dimension(40, 40));
                components.shuffleButton.setPreferredSize(new Dimension(40, 40));
                components.shuffleButton.setSize(new Dimension(40, 40));
                components.shuffleButton.setToolTipText("Shuffle");
                components.shuffleButton.setVerticalTextPosition(SwingConstants.CENTER);

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
                getAccessibleContext().setAccessibleName(name);
                getAccessibleContext().setAccessibleParent(this);

                setAlwaysOnTop(false);
                setBackground(new Color(255, 255, 255));
                setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
                setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
                setFont(new Font("Roboto", 0, 16)); // NOTE (Lapys) -> No Internationalization.
                setForeground(new Color(51, 51, 51));
                setIconImage((new ImageIcon(getClass().getResource(favicon))).getImage());
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
                    mainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, mainLayout.createSequentialGroup()
                    .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(components.poster, javax.swing.GroupLayout.PREFERRED_SIZE, 200, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(100, 100, 100))
                    .addGroup(mainLayout.createSequentialGroup()
                    .addGroup(mainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                    .addComponent(components.musicTitle, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(components.musicArtiste, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(mainLayout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(components.musicTimestamp, javax.swing.GroupLayout.PREFERRED_SIZE, 75, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(components.musicDuration, javax.swing.GroupLayout.PREFERRED_SIZE, 75, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap())
                    .addGroup(mainLayout.createSequentialGroup()
                    .addGap(20, 20, 20)
                    .addGroup(mainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(mainLayout.createSequentialGroup()
                    .addComponent(components.loopButton, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(43, 43, 43)
                    .addComponent(components.previousSongButton, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(35, 35, 35)
                    .addComponent(components.playButton, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(35, 35, 35)
                    .addComponent(components.nextSongButton, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(components.shuffleButton, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(components.musicSeeker, javax.swing.GroupLayout.PREFERRED_SIZE, 355, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                );
                mainLayout.setVerticalGroup(
                    mainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(mainLayout.createSequentialGroup()
                    .addGap(30, 30, 30)
                    .addComponent(components.poster, javax.swing.GroupLayout.PREFERRED_SIZE, 200, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(30, 30, 30)
                    .addComponent(components.musicTitle, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(components.musicArtiste, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(mainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(components.musicTimestamp, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(components.musicDuration, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(components.musicSeeker, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(20, 20, 20)
                    .addGroup(mainLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(components.loopButton, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(components.previousSongButton, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(components.nextSongButton, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(components.playButton, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(components.shuffleButton, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addContainerGap(25, Short.MAX_VALUE))
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

            // Poster > Image
            poster.setImage(new File("posters/placeholder.jpg"));

        // Insertion
        components.toolbar.add(components.toolbarMenuButton);
        components.toolbar.add(components.header);

        // ...
        pack();
    }

    /* Main */
    public static void main(String[] arguments) {
        // Event > ... --- NOTE (Lapys) -> Could be reduced to a lambda expression.
        EventQueue.invokeLater(new Runnable() {
            // Method > Run
            public void run() {
                // Constant > Application
                final GUI application = new GUI();

                // Modification > Application > ...
                application.description = "Practical demonstration of a functional graphical user-interface (GUI) made with the Java programming language";
                application.favicon = "favicon.png"; // NOTE (Lapys) -> Apparently fails when it comes to `.ico` files.
                application.name = "Java Graphical User Interface";

                // Application > ...
                application.initiate();
            }
        });
    }
}
