import csv
import os

accepted_strings = []
file = open(os.path.dirname(os.path.realpath(__file__)).replace("\\", "/") + "/" + "group2_file.csv", "r")

def get_next_state(symbol, state):
    if state == "q0" and symbol == 1:
        return "q1"

    if state == "q1" and symbol == 0:
        return "q1"
    if state == "q1" and symbol == 1:
        return "q2"

    if state == "q2" and symbol == 0:
        return "q1"
    if state == "q2" and symbol == 1:
        return "q2"

    return ""

for row in csv.reader(file, delimiter = ','):
    for string in row:
        state = "q0"

        for symbol in string:
            state = get_next_state(int(symbol), state)
            if state == "": break

        if "q2" == state:
            accepted_strings.append(string)

for string in accepted_strings:
    print(string)

file.close()
