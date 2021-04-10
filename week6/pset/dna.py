from sys import argv
import csv
import re
from collections import defaultdict

def check_args(argv):

    if len(argv) < 3:
        raise RuntimeError("Not enough arguments have been passed to the commandline")

    if argv[1].endswith('csv'):
        pass
    else:
        raise RuntimeError('First commandline argument must be a csv file')

    if argv[2].endswith('txt'):
        pass
    else:
        raise RuntimeError('Second commandline argument must be a text file')

def read_database(arg):

    with open(arg, newline = '\n') as f:
        csv_reader = csv.reader(f)
        sequences = next(csv_reader)[1:]

    output = defaultdict(dict)
    with open(arg, newline = '\n') as file:
        reader = csv.DictReader(file, delimiter = ',')
        for row in reader:
            output[row['name']] = row

        for i in output.values():
            del i['name']
    return output, sequences

def read_dna(dna_file):
    with open(dna_file) as file:
        data = file.read()
    return data

def count_dna(dna_string, sequences):

    sequence_counts = {}
    for dna in sequences:
        pattern = "(("+re.escape(dna)+")+)"
        matches  = re.findall(pattern, dna_string)
        dna_count = max(len(m[0])//len(dna) for m in matches)
        sequence_counts[dna] = str(dna_count)
    return sequence_counts

def match_dna(sequence_counts, data):
    matched_name = ''
    for name, dna in data.items():
        if dna == sequence_counts:
            matched_name = name

    if matched_name:
        print(matched_name)
    else:
        print("No match")


def main():
    check_args(argv)
    data, sequences = read_database(argv[1])
    dna_string = str(read_dna(argv[2])).strip()
    dna_counts = count_dna(dna_string, sequences)
    match_dna(dna_counts, data)

main()

