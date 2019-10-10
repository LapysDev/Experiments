# Import > Random
import random

# Function > Sum
def int_sum(int_list):
    # Initialization > Sum
    sum = 0

    # Loop > Update > Sum
    for integer in int_list:
        sum += integer

    # Return
    return sum

# Initialization > (Integer : List)
int_list = list(range(10))

# Print
print('Program to calculate the sum of a random set of 10 integers.', end='\n\n')

# Loop > Update > (Integer : List)
for item in int_list:
    int_list[item] = random.randint(0, 10)

# Print
print('List:', int_list)
print('Sum:', int_sum(int_list))
