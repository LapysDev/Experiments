/* Import */
import java.io.*; // Java > Input-Output
import java.util.Scanner; // Java > Utilities > Scanner

/* ... */
class ArithmeticOperations {
    /* Main */
    public static void main(String[] arguments) {
        // : Constant > Scanner
        // : Initialization > Number (A, B)
        Scanner SCANNER = new Scanner(System.in);
        float numberA, numberB;

        // ...
        System.out.print("First Number: "); numberA = SCANNER.nextFloat();
        System.out.print("Second Number: "); numberB = SCANNER.nextFloat();

        System.out.println();

        System.out.println("Addition: " + (numberA + numberB));
        System.out.println("Division: " + (numberA / numberB));
        System.out.println("Multiplication: " + (numberA * numberB));
        System.out.println("Subtraction: " + (numberA - numberB));

        // Scanner > Close
        SCANNER.close();
    }
}
