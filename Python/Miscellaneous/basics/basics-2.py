# Number 1
for number in range(1, 101):
  if 0 == number % 5 and 0 == number % 7: # if it is a factor of 5 and 7
    print(number)

# Number 2
even_count = 0 # allows us to count how many even numbers there are
odd_count  = 0 # allows us to count how many odd  numbers there are

for number in [1, 2, 3, 4, 5, 6, 7, 8, 9]:
  if 0 == number % 2: # if divisible by 2, it's an even number
    even_count = even_count + 1
  else: # it's an odd number
    odd_count = odd_count + 1

print(f"Even: {even_count}")
print(f"Odd: {odd_count}")

# Number 3
for number in range(0, 7):
  if number != 3 and number != 6:
    print(number)

# Number 4
for number in range(1, 51):
  if 0 == number % 3 and 0 == number % 5:
    print("FizzBuzz", end=' ')
  elif 0 == number % 3:
    print("Fizz", end=' ')
  elif 0 == number % 5:
    print("Buzz", end=' ')
  else:
    print(number, end=' ')
