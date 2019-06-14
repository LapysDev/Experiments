# Initialization > (Principal, Rate, Periods)
principal = float(input('Principal: '))
rate = float(input('Rate: '))
periods = float(input('Periods: '))

# Function > Simple Interest
def simple_interest(principal, rate, periods):
    # Return
    return principal * rate * periods

# Print
print('\nInterest: ', format(simple_interest(principal, rate, periods), ',.2f'), sep='')
