from cs50 import get_string
import re

# TODO


def main():

    text = get_string("Insert Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    index = get_reading_level(letters, words, sentences)
    print_grade(index)


def count_letters(text):
    n = 0

    for char in text:
        if char.isalpha():
            n += 1
    return n


def count_words(text):
    word_list = text.split()

    number_words = len(word_list)

    return number_words


def count_sentences(text):
    sentences = 0
    for i in (range(len(text))):
        if (text[i] == '?' or text[i] == '!' or text[i] == '.'):
            sentences += 1
    return sentences


def get_reading_level(letters, words, sentences):
    avr_l = (letters / words) * 100
    avr_w = (sentences / words) * 100
    index = ((0.0588 * avr_l) - (0.296 * avr_w) - 15.8)

    return round(index)


def print_grade(index):

    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")
    return


main()