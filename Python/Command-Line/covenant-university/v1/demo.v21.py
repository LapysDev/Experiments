# Initialization > (Number of Calories burned Per Minute, Minutes)
number_of_calories_burned_per_minute = 3.9
minutes = [10, 15, 20, 25, 30]

# Print
print('Number of Calories burned per Minute:', number_of_calories_burned_per_minute, end='\n\n')

# Loop > Print
for minute in minutes:
    print('Number of Calories burned in ' + str(minute) + ' Minutes:', number_of_calories_burned_per_minute * minute)
