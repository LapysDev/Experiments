# Initialization > (Amount Budgeted per Month, Number of Expenses, Total Expense)
amount_budgeted_per_month = float(input('Amount budgeted for a Month: '))
number_of_expenses = int(input('Number of Expenses: '))
total_expense = 0

# Loop > Update > (Expenses, Total Expense)
for expense in range(number_of_expenses):
    expense = float(input('   Expense: '))
    total_expense += expense

# Print
print('\n   ----------------------------')
print('\n   Total Expenses:', total_expense, end='\n\n\n')

# Logic > Print
if total_expense > amount_budgeted_per_month:
    print('You overspent on your budget (Total Expenses > Amount Budgeted...)')

else:
    print('You spent within your expenses (Amount Budgeted... > Total Expenses)')
