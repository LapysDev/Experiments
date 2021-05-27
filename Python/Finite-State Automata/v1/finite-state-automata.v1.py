# Import
import csv # Comma-Separated Values
import os # Operating System
import re # Regular Expression

# Global > Current Working Directory
__cwd__ = os.path.dirname(os.path.realpath(__file__)).replace('\\', '/') + '/'

# Constant > (Accepted Strings, (Input, Output) File, Reader, Writer)
accepted_strings = []

input_file = open(__cwd__ + "input.csv", mode = 'r')
output_file = open(__cwd__ + "output.csv", mode = 'w', newline = "")

reader = csv.reader(input_file, delimiter = ',')
writer = csv.writer(output_file, delimiter = ',', quotechar = '"', quoting = csv.QUOTE_MINIMAL)

# Function > Get Next State --- NOTE (Lapys) -> Resulting transition state from the current state and symbol.
def get_next_state(symbol, state, start_state = 0x0, end_state = 0x0):
    # Evaluation > Next State
    next_state = None

    # ... Update > Next State
    if end_state == state:
        if '1' == symbol: next_state = end_state

    else:
        if '0' == symbol: next_state = state + 1
        if '1' == symbol: next_state = state + 0

    # Return
    return next_state

# [Parse Input] ...
for row in reader:
    for string in row:
        # Initialization > (Expression, ... State)
        expression = re.search(r"1*01*01*", string)

        end_state = 0x2; start_state = 0x0
        state = start_state

        # Loop > ... Update > State
        if expression is not None:
            if expression.span()[1] == len(string):
                state = end_state

        else:
            for character in string:
                state = get_next_state(character, state, start_state, end_state)
                if state is None: break

        # Logic > Update > Accepted Strings
        if end_state == state: accepted_strings.append(string)

# [Parse Output] ...
for accepted_string in accepted_strings:
    # ...
    writer.writerow([accepted_string])
    print(accepted_string)

# Termination
input_file.close()
output_file.close()
