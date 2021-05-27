import csv
import os

# ...
file = open(os.path.dirname(os.path.realpath(__file__)) + '\\' + "input.csv", 'r')
reader = csv.reader(file, delimiter = ',')

# ...
def get_next_state(symbol, state):
  if '0' == symbol:
    if state == "q0": return "q1"
    if state == "q1": return "q2"
    if state == "q2": return "q3"

  return state

# ...
for row in reader:
  for string in row:
    state = "q0"

    for symbol in string:
      state = get_next_state(symbol, state)
      if state == "q3": break

    if state != "q3":
      print(string)

# ...
file.close()
