# Initialization > Number of Books Purchased
number_of_books_purchased = int(input('Number of books purchased: '))

# Logic > Print
if number_of_books_purchased == 0:
    print('0 points earned')

elif number_of_books_purchased == 1:
    print('5 points earned')

elif number_of_books_purchased == 2:
    print('15 points earned')

elif number_of_books_purchased == 3:
    print('30 points earned')

elif number_of_books_purchased > 3:
    print('60 points earned')
