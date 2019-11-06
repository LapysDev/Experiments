/* Import */
import java.io.*; // Java > Input-Output > [All]
import java.nio.file.*; // Java > Non-Blocking Input-Output > File > [All]
import java.util.stream.Stream; // Java > Language > Object

/* ... */
public class ReadFiles {
    /* Main */
    public static void main(String[] arguments) {
        // Initialization > ...
        String filename = "ReadFiles.txt";
        Path path = Paths.get(filename);
        String[] sources = {"", "", "", "", ""};

        // ...
        try(BufferedReader reader = Files.newBufferedReader(path)) {
            String subsource = "";

            do { sources[0] += subsource + '\n'; subsource = reader.readLine(); }
            while (subsource != null);

            sources[0] = sources[0].substring(1, sources[0].length() - 1);
        } catch (IOException error) { error.printStackTrace(); }
        System.out.println("[SOURCE | 1]: \"" + sources[0] + "\"\n");

        // ...
        try(Stream<String> stream = Files.lines(path)) {
            stream.forEach((String subsource) -> { sources[1] += subsource + '\n'; });
            sources[1] = sources[1].substring(0, sources[1].length() - 1);
        } catch (IOException error) { error.printStackTrace(); }
        System.out.println("[SOURCE | 2]: \"" + sources[1] + "\"\n");

        // ...
        try { sources[2] = new String(Files.readAllBytes(path)); }
        catch (IOException error) { error.printStackTrace(); }
        System.out.println("[SOURCE | 3]: \"" + sources[2] + "\"\n");

        // ...
        try {
            Files.readAllLines(path).forEach((String subsource) -> { sources[3] += subsource + '\n'; });
            sources[3] = sources[3].substring(0, sources[3].length() - 1);
        } catch (IOException error) { error.printStackTrace(); }
        System.out.println("[SOURCE | 4]: \"" + sources[3] + "\"\n");

        // ...
        try {
            Files.lines(path).forEach((String subsource) -> { sources[4] += subsource + '\n'; });
            sources[4] = sources[4].substring(0, sources[4].length() - 1);
        } catch (IOException error) { error.printStackTrace(); }
        System.out.println("[SOURCE | 5]: \"" + sources[4] + "\"\n");
    }
}
