
def main():
    height = get_int("height: ", 1, 8)

    print_pyramid(height)


def get_int(text: str = None, min_r: int = None, max_r: int = None) -> int:
    """ get user input int]
        args:
        text str text for user input
        max_r
    """

    while True:
        num = input(f"{text}")
        if num.isnumeric():
            num = int(num)
            if min_r is not None and num < min_r:
                print(f"Value must be greater than or equal to {min_r}")
            elif max_r is not None and num > max_r:
                print(f"Value must be less than or equal to {max_r}")
            else:
                return num


def print_pyramid(height: int = 1) -> None:

    for row in range(1, height+1):
        print(" " * (height - row) + "#" * row + "  " + "#" * row)


if __name__ == "__main__":
    main()
