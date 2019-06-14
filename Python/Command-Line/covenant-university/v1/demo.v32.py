# Print
print('Program to display the statistics of rainfall in a year.', end='\n\n')

# Initialization > (Months, Rainfalls per Month)
months = ('January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December')
rainfalls_per_month = list(range(12))

# Print
print('Enter rainfall data (in integers) for each month of the year:', end='\n\n')

# Loop > Update > Rainfalls per Month
for index in rainfalls_per_month:
    rainfalls_per_month[index] = float(input('Rainfall Amount for ' + months[index] + ': '))

# Function > Get Average Monthly Rainfall
def get_average_monthly_rainfall(rainfalls_per_month):
    # Return
    return get_total_rainfall(rainfalls_per_month) / len(rainfalls_per_month)

# Function > Get Lowest Rainfall
def get_lowest_rainfall(rainfalls_per_month):
    # Initialization > Rainfall
    rainfall = rainfalls_per_month[0]

    # Loop > Logic > Update > Rainfall
    for rainfall_per_month in rainfalls_per_month:
        if rainfall > rainfall_per_month:
            rainfall = rainfall_per_month

    # Return
    return rainfall

# Function > Get Highest Rainfall
def get_highest_rainfall(rainfalls_per_month):
    # Initialization > Rainfall
    rainfall = rainfalls_per_month[0]

    # Loop > Logic > Update > Rainfall
    for rainfall_per_month in rainfalls_per_month:
        if rainfall < rainfall_per_month:
            rainfall = rainfall_per_month

    # Return
    return rainfall

# Function > Get Total Rainfall
def get_total_rainfall(rainfalls_per_month):
    # Initialization > Rainfalls
    rainfalls = 0

    # Loop > Update > Rainfalls
    for rainfall_per_month in rainfalls_per_month:
        rainfalls += rainfall_per_month

    # Return
    return rainfalls

# Print
print('\n\n\n', end='')

# Print
print('Average Monthly Rainfall      :', get_average_monthly_rainfall(rainfalls_per_month))
print('Highest Rainfall              :', get_highest_rainfall(rainfalls_per_month))
print('Lowest Rainfall               :', get_lowest_rainfall(rainfalls_per_month))
print('Total Rainfall                :', get_total_rainfall(rainfalls_per_month))

# Print
print('\n\n', end='')

# Print
print('Rainfall Stats. (for the year):', rainfalls_per_month)
