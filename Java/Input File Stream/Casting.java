/* Import */
import java.io.*; // Java > Input-Output
import java.util.Scanner; // Java > Utilities > Scanner

/* ... */
class Casting {
    /* Main */
    public static void main(String[] arguments) {
        // Initialization > Scanner
        Scanner scanner = new Scanner(System.in);

        // Print
        System.out.println("Welcome to Java!\n");

        // Initialization > Scanned ...
        float scannedFloat; int scannedInteger; String scannedString;

        // ...
        System.out.print("INTEGER [INPUT]: "); scannedInteger = scanner.nextInt();
        System.out.print("FLOAT [INPUT]: "); scannedFloat = scanner.nextFloat();
        System.out.print("STRING [INPUT]: "); scannedString = scanner.next();

        System.out.println();

        System.out.println("[INTEGER (OUTPUT)]: " + scannedInteger);
        System.out.println("[FLOAT (OUTPUT)]: " + scannedFloat);
        System.out.println("[STRING (OUTPUT)]: \"" + scannedString + '"');

        // Scanner > Close
        scanner.close();
    }
}
