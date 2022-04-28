import random

print("Hello, World!")
print(f"""My name is Lapys
I am {0x15} years old
I enjoy software engineering
I current work/ school at Cloudboosta
I come from {{6.5244 North, 3.3792 East}}
I current live in {{51.5761 North, 0.4887 East}}""")

names   = ["Gbemi", "AK", "Tobi"]
numbers = [2, 4, 56, 76, 23]

cars                = ["Audi", "Honda", "Mazda", "Tesla", "Toyota", "Volvo"]
random_numbers      = [random.random() for y in range(15)]
artistes            = ["Taylor Swift", "Ed Sheeran", "Rihanna", "Elton John", "Adele", "Justin Bieber", "Beyoncé"]
cloudboosta_members = ["Olumide", "Ebun", "Funto", "Toyin", "Tosin", "Oluwatobi", "Ogaga", "Ukeme", "", "", ""]
print(cars[2:4])
print(random_numbers[3:11])
print(artistes[2:5])

len(list(fruit for fruit in ["banana", "apple", "guava", "pear", "apple", "orange","mango", "apple", "banana"] if fruit == "apple"))
"wordpseudopseudohypoparathyroidism".upper()
0 == len(list(character for character in "haPpy" if character != character.lower()))
["banana", "apple", "guava", "pear", "apple", "orange","mango", "apple", "banana"].index("orange")

students = dict([
  # --> {"student1": "Bola", "student2": "Godson", "student3": "Azeez", "student4": "Amaka", "student5": "Zainab"}
  ("student1", "Bola"),
  ("student2", "Godson"),
  ("student3", "Azeez"),
  ("student4", "Amaka"),
  ("student5", "Zainab")
])
students.pop("student3", None)         # --> del students["student3"]
students.update({"student6": "Ahmed"}) # --> students["student6"] = "Ahmed"
print(students["student2"])
