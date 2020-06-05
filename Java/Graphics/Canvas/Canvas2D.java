/* Import */
import java.awt.image.BufferedImage; // Java > Abstract Window Toolkit > Image > Buffered Image
import java.awt.Canvas; // Java > Abstract Window Toolkit > Canvas
import java.awt.Color; // Java > Abstract Window Toolkit > Color
import java.awt.Dimension;  // Java > Abstract Window Toolkit > Dimension
import java.awt.Graphics; // Java > Abstract Window Toolkit > Graphics
import java.awt.Image; // Java > Abstract Window Toolkit > Graphics
import java.io.File; // Java > Input-Output > File

import javax.imageio.ImageIO; // Java Extension > Image Input-Output > Image Input-Output
import javax.swing.JFrame;  // Java Extension > Swing > Canvas

/* ... */
public class Canvas2D {
    /* Main */
    public static void main(String[] arguments) {
        // Constant > (Canvas, Window)
        final Canvas canvas = new Canvas() {
            // Method > Paint
            public void paint(Graphics graphics) {
                // Error > ...
                try { graphics.drawImage(ImageIO.read(new File("image.png")), 0, 0, null); }
                catch (Exception error) { error.printStackTrace(); }
            }
        };
        final JFrame window = new JFrame("Canvas");

        // Logic
        if (canvas == null) {
            // Error; ...
            System.err.print("`java.awt.Canvas` class is not found");
            System.exit(1);
        }

        else {
            // Modification > (Canvas, Window) > ...
            canvas.setBounds(0, 0, 200, 200);
            canvas.setFocusable(false);
            canvas.setMaximumSize(new Dimension(200, 200));
            canvas.setMinimumSize(new Dimension(200, 200));
            canvas.setPreferredSize(new Dimension(200, 200));
            canvas.setSize(new Dimension(200, 200));

            window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            window.setLocationRelativeTo(null);
            window.setResizable(false);
            window.setSize(new Dimension(400, 400));
            window.setVisible(true);

            // Insertion; ...
            window.add(canvas);
        }
    }
}
