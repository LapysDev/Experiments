# Initialization > (Denominator, Numerator, Total)
denominator = 30
numerator = 1
total = 0

# Loop
while denominator != 0 and numerator != 31:
    # Update > Total
    total += numerator / denominator

    # Update > (Denominator, Numerator)
    denominator -= 1
    numerator += 1

# Print
print('\n\nTotal:', total)
