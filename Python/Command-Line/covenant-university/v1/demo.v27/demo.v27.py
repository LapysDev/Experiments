# Print
print('Program to write 1 to 100 to a file: `number-list.txt`.\n\n')

# Initialization > File
file = open('number-list.txt', 'w')

# Loop
for number in range(100):
    # Update > (Number, Write Message)
    number += 1
    writeMessage = str(number)

    # Logic > Update > Write Message
    if number != 100:
        writeMessage += ', '

    # File > Write
    file.write(writeMessage)

# Update > File
file = open('number-list.txt', 'r')

# Print
print('number-list.txt Contents:\n    ')

# Loop > Print
for line in file:
    print(line)

# Print
print(end='\n')

# Initialization > Sum
sum = 0

# Loop
for iterator in range(100):
    # Update > (Iterator, Sum)
    iterator += 1
    sum += iterator

# Print
print('Sum:', sum)
