import pandas

data = pandas.read_csv('nato_phonetic_alphabet.csv')

nato_dict = {row.letter: row.code for (index, row) in data.iterrows()}

name = input('Hey, Please enter your name:').upper()

phonetic_name = [nato_dict[letter] for letter in name]
print(phonetic_name)
