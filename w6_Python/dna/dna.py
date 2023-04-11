import csv
import sys
from collections import defaultdict


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv dna.txt")

    dna_base = []
    # Read database file into a variable
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for person in reader:
            name = person["name"]

            dna_dict = {key: int(val) for key, val in person.items() if key != "name"}
            personal_dna = [name, dna_dict]
            dna_base.append(personal_dna)

    sequences = list(dna_base[0][1].keys())

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as dna_file:
        dna_sample = dna_file.read()

    sequence_count = defaultdict(int)
    # Find longest match of each STR in DNA sequence
    for sequence in sequences:
        sequence_count[sequence] = longest_match(dna_sample, sequence)

    match_c = 0
    # Check database for matching profiles
    for person in dna_base:
        name = person[0]
        dna_data = person[1]
        match = all(dna_data[key] == sequence_count[key] for key in sequences)

        if match:
            print(name)
            match_c += 1

        # if person[1].items() == sequence_count.items():
        #     print(person[0])
        #     match_c += 1

    if match_c == 0:
        print("No match")

    return


def longest_match(sequence, subsequence) -> int:
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
