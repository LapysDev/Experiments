/* Import */
import java.io.*; // Java > Input-Output
import java.util.Scanner; // Java > Utilities > Scanner

/* ... */
class AreaOfCircle {
    /* Main */
    public static void main(String[] arguments) {
        // : Constant > Scanner
        // : Initialization > Radius
        Scanner SCANNER = new Scanner(System.in);
        float radius;

        // ...
        System.out.print("Radius Of Circle: "); radius = SCANNER.nextFloat();
        System.out.print("Area Of Circle: " + ((22.00 / 7.00) * (radius * radius)));

        // Scanner > Close
        SCANNER.close();
    }
}
