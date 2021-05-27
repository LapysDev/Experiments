import csv
import os
import re

# ...
__cwd__ = os.path.dirname(os.path.realpath(__file__)).replace('\\', '/') + '/'

accepted_strings = []
input_file = open(__cwd__ + "input.csv", mode = 'r')
output_file = open(__cwd__ + "output.csv", mode = 'w', newline = "")
reader = csv.reader(input_file, delimiter = ',')
writer = csv.writer(output_file, delimiter = ',', quotechar = '"', quoting = csv.QUOTE_MINIMAL)

# ...
def get_next_state(symbol, state):
    next_state = None

    if '1' == symbol: next_state = state
    if '0' == symbol and state <= 0x2: next_state = state + 1

    return next_state

# ...
for row in reader:
    for string in row:
        # ...
        expression = re.search(r"1*(0|)1*(0|)1*", string)
        if expression is not None:
            if expression.span()[1] == len(string):
                accepted_strings.append(string)

        else:
            state = 0x0
            for character in string:
                state = get_next_state(character, state)
                if state is not None: accepted_strings.append(string)

# ...
print("Accepted Strings (", len(accepted_strings), ")\n")

for accepted_string in accepted_strings:
    writer.writerow([accepted_string])
    print(accepted_string)

# ...
input_file.close()
output_file.close()
