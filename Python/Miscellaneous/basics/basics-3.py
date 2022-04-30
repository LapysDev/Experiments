# Number 1
def generate_multiplication_table(number: int):
  return [number * multiplicand for multiplicand in range(1, 11)]

def square(number: int):
  return number ** 2

# Number 2
def printtypesof(datalist: list):
  for data in datalist:
    print(type(data).__name__, end=' ')
  print()

# Number 3
def generate_stringified_multiplication_table(number: int):
  return '\n'.join([f"{number} × {multiplicand} = {multiplication}" for multiplicand, multiplication in enumerate(generate_multiplication_table(number))])

# ...
print(generate_multiplication_table(12))
print([square(number) for number in generate_multiplication_table(12)])
printtypesof([1452, 11.23, 1+2j, True, "exam", (0, -1), [5, 12], {"class": 'V', "section": 'A'}])
print(generate_stringified_multiplication_table(12))
