import csv
import os

# ...
file = open(os.path.dirname(os.path.realpath(__file__)) + '\\' + "group7_file.csv", 'r')
# file = open("C:\\LapysDev\\experiments\\Python\\Finite-State Automata\\v7\\group7_file.csv", 'r')
# file = open("group7_file.csv", 'r')
reader = csv.reader(file, delimiter = ',')

# Essentially our DFA
def get_next_state(symbol, state):
  if state == "q0":
    if symbol == '1': return "q1"
    if symbol == '0': return "q2"

  if state == "q1":
    if symbol == '1': return "q0"
    if symbol == '0': return "q0"

  if state == "q2":
    if symbol == '1': return "q2"
    if symbol == '0': return "q2"

# Loop through row
for row in reader:
  for string in row:
    state = "q0"

    # Loop through string
    for symbol in string:
      state = get_next_state(symbol, state)
      if state == "q2": break

    # Check if state is not trap state
    if state != "q2":
      print(string)

# ...
file.close()
