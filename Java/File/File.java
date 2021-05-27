/* Import > Java */
import java.io.File; // Input/ Output > File
import java.io.FileNotFoundException; // Input/ Output > File Not Found Exception
import java.io.IOException; // Input/ Output > Input/ Output Exception
import java.io.FileReader; // Input/ Output > File Reader
import java.io.FileWriter; // Input/ Output > File Writer

import java.util.Scanner; // Utility > Scanner

/* Application */
public class File {
    public static void main(String[] arguments) {
        try {
            final File file = new File("file.txt");
            final FileWriter writer = new FileWriter("file.txt");

            if (file.createNewFile()) System.out.println("Creating \"file.txt\" using `File`");
            else System.out.println("Created \"file.txt\" using `File`");

            System.out.println("Writing \"file.txt\" using `FileWriter`");
            writer.write(
                "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" +
                "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," +
                "quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo" +
                "consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse" +
                "cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non" +
                "proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
            );
            writer.close();
        } catch (IOException error) {
            System.err.println("An error occurred.");
            error.printStackTrace();
        }

        /* ... */
        try {
            final File file = new File("file.txt");
            final Scanner scanner = new Scanner(file);

            System.out.print("Reading \"file.txt\" using `File` and `Scanner`:\n\t\"");
                for (boolean once = false; scanner.hasNextLine(); once = true)
                System.out.println((once ? "\t" : "") + scanner.nextLine());
            System.out.println('"');

            scanner.close();
        } catch (FileNotFoundException error) {
            System.err.println("An error occurred.");
            error.printStackTrace();
        }

        try {
            final FileReader reader = new FileReader("file.txt");

            System.out.print("Reading \"file.txt\" using `FileReader`:\n\t\"");
                for (int character; -1 != (character = reader.read()); )
                System.out.print((char) character);
            System.out.println('"');

            reader.close();
        } catch (IOException error) {
            System.err.println("An error occurred.");
            error.printStackTrace();
        }
    }
}
