def main():

    card_no = int(input("type card number (digits-only): "))

    get_card_type_or_invalid(card_no)


def luhn(number: int) -> bool:

    if (sum([get_sum_1(number), get_sum_2(number)]) % 10) == 0:
        return True
    else:
        return False


def get_sum_2(number: int) -> int:
    """get_sum_of_digits_multiplied_from_second_last"""
    result = 0
    number //= 10
    while number != 0:
        product = (number % 10) * 2

        # if product double digits sum them
        if product > 9:
            result += (product % 10)
            product //= 10
            result += (product % 10)
        else:
            result += product

        number //= 100

    return result


def get_sum_1(number: int) -> int:
    """get_sum_of_numbers_from_last_digit"""

    result = 0
    while number != 0:
        result += (number % 10)
        number //= 100

    return result


def get_first_second_digit(number: int) -> tuple:
    return (int(str(number)[0]), int(str(number)[1]))


def get_card_type_or_invalid(number: int) -> None:
    len_n = len(str(number))

    if 12 < len_n < 17 and luhn(number):
        first, second = get_first_second_digit(number)

        if len_n == 15 and first == 3 and (second == 4 or second == 7):
            print("AMEX")

        elif len_n == 16 and first == 5 and (second in range(1, 6)):
            print("MASTERCARD")

        elif (len_n == 16 or len_n == 13) and first == 4:
            print("VISA")

        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
