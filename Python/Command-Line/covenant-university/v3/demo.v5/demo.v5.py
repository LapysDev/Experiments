# Initialization > (Occurrences, Text)
occurrences = {}
text = open("text.txt")

# Loop > Iterate through Text
for line in text:
    # Initialization > Word
    word = ""

    # Loop > Iterate through the Line
    for character in line:
        # Logic --- NOTE (Lapys) -> Any delimiter for a word.
        if character == ' ' or character == '\n':
            # Initialization > Occurrence Found
            occurrence_found = False

            # Loop > Index Occurrences
            for occurrence in occurrences:
                # Logic
                if occurrence == word:
                    # Modification > Occurrences > [Word]
                    occurrences[word] += 1

                    # Update > Occurrence Found
                    occurrence_found = True

            # Logic
            if not occurrence_found:
                # Modification > Occurrences > [Word]
                occurrences[word] = 1

            # Update > Word
            word = ""

        else:
            # Update > Word
            word += character

# Loop > Index Occurrences
for occurrence in occurrences:
    # Print
    print('"' + occurrence + "\":", occurrences[occurrence])
