# Initialization > (Stream, String, Iterator, Length)
stream = ""
string = input("String: ")
iterator = len(string)
length = iterator

# Loop
while iterator:
    # Update > Iterator
    iterator -= 1

    # Initialization > Character
    character = string[length - iterator - 1]

    # Logic
    if iterator == length - 1:
        # Update > Stream
        stream += character.upper()

    elif character == character.upper():
        # Update > Stream
        stream += ' ' + character.lower()

    else:
        # Update > Stream
        stream += character

# Print
print("Format:", stream)

