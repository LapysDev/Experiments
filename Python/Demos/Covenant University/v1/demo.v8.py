# Initialization > (Query, Recur)
query = True
recur = True

# Loop
while recur:
    # Logic
    if query:
        # Update > Number (A, B)
        numberA = float(input('Number A: '))
        numberB = float(input('Number B: '))

        # Print
        print('Sum:', numberA + numberB, '\n')

    # Update > Recur
    recur = input('Do you want to restart this program (Y / N)? ')

    # Logic
    if recur == 'y' or recur == 'Y':
        # Update > (Query, Recur)
        query = True
        recur = True

    elif recur == 'n' or recur == 'N':
        # Update > (Query, Recur)
        query = False
        recur = False

    else:
        # Update > (Query, Recur)
        query = False
        recur = True

        # Print
        print("Invalid command (Either key in 'Y' or 'N')\n")
