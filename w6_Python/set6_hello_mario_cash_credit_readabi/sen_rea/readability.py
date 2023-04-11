def main():
    # get valid user text input
    while True:
        user_input_text = input("Text: ")
        if len(user_input_text) > 0:
            break

    # print grade
    print_grade(user_input_text)


def get_text_letters(text: str) -> int:
    letters_count = 0
    for char in text:
        if char.isalpha():
            letters_count += 1
    return letters_count


def get_text_sentences(text: str) -> int:
    sentence_count = 0
    for char in text:
        if char in ["?", "!", "."]:
            sentence_count += 1

    return sentence_count


def get_text_words(text: str) -> int:
    # count number of words in the string. based on whitespaces +1
    word_count = len(text.split(" "))

    return word_count


def get_text_grade(text):
    # Coleman Liau index

    words = get_text_words(text)

    letters_per_100_words = (get_text_letters(text) / words) * 100

    sentences_per_100_words = (get_text_sentences(text) / words) * 100

    grade = round((0.0588 * letters_per_100_words) - (0.296 * sentences_per_100_words) - 15.8)

    return grade


def print_grade(text):
    # print grade
    grade = get_text_grade(text)

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


if __name__ == "__main__":
    main()
