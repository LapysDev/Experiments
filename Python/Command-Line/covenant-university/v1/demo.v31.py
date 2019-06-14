# Import > Random
import random

# Print
print('Program to generate a lottery with native a pseudo-random number generator.', end='\n\n')

# Initialization > Lottery Digits
lottery_digits = list(range(7))

# Loop > Update > Lottery Digits
for index in lottery_digits:
    lottery_digits[index] = random.randint(0, 9)

# Print
print('Lottery Digits:', lottery_digits)
