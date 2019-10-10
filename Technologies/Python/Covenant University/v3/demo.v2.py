# Initialization > Example (...)
example_1 = False
example_2 = False
example_3 = False
example_4 = True

# Logic
if example_1:
    # Initialization > (X, Y, Z)
    x = int(input("Enter a number X: "))
    y = 0
    z = 0

    # Print
    print("\nX:", x)

    # Logic > Update > (Y, Z)
    if x > 100:
        y = 20
        z = 40

    # Print
    print("Y:", y)
    print("Z:" + z)

elif example_2:
    # Initialization > A
    a = int(input("Enter a number A: "))

    # Print
    print("A:", a)

    # Logic > Update > B
    if a < 10:
        b = 0

    else:
        b = 99

    # Print
    print("B:", b)

elif example_3:
    # Update > Speed
    speed = int(input("Enter a speed: "))

    # Logic > Print
    if speed > 23 and speed < 57:
        print("Speed is normal")

    else:
        print("Speed is abnormal")

elif example_4:
    # Initialization > Number
    number = input("Enter a number from 1-10: ")

    # Logic > Print
    if number == "1":
        print("I")

    elif number == "2":
        print("II")

    elif number == "3":
        print("III")

    elif number == "4":
        print("IV")

    elif number == "5":
        print("V")

    elif number == "6":
        print("VI")

    elif number == "7":
        print("VII")

    elif number == "8":
        print("VIII")

    elif number == "9":
        print("IX")

    elif number == "10":
        print("X")

    else:
        print("Error message")
