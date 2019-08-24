# Print
print("Program to calculate the total amount of a meal purchased:\n")

# Initialization > (Food Price, Sales Tax, Tip)
tip = food_price * .15
sales_tax = food_price * .07
food_price = float(input("Meal Price: "))

# Print
print("\n15 Percent Tip:", tip)
print("7 Percent Sales Tax:", sales_tax)
print("\nTotal Price:", food_price + tip + sales_tax)
