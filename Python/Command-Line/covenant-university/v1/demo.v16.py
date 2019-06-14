# Initialization > Score
score = int(input('Enter a test score: '))

# Loop
while score < 0 or score > 100:
    # Print
    print('ERROR: The score cannot be negative or greater than 100.')

    # Update > Score
    score = int(input('Enter the correct score: '))
