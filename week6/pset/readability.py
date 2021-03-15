
def get_text():
    text = input("Enter your text: ")
    return text

def count_characters(text):
    char_count = 0
    for i in text:
        if i.isalpha():
            char_count +=1
    return char_count

def count_words(text):
    str_array = list(text)
    word_count = 0
    for i in str_array:
        if i == ' ':
            word_count += 1
    return word_count+1

def count_sentences(text):
    str_array = list(text)
    sentences = 0
    for i in str_array:
        if i in ['!', '?', '.']:
            sentences += 1
    return sentences

def coleman_lau_index(char_count, word_count, sent_count):
    word_per_100 = (char_count/word_count)*100
    sent_per_100 = (sent_count/word_count)*100

    c_l_idx = round((0.0588*word_per_100) - (0.296*sent_per_100) - 15.8,0)
    if c_l_idx < 1:
        return 'Below grade 1'
    elif c_l_idx >= 16:
        return 'Above grade 16'
    else:
        return f'Grade: {c_l_idx}'


def main():
    text = get_text()
    char_count = count_characters(text)
    word_count = count_words(text)
    sent_count = count_sentences(text)
    print(coleman_lau_index(char_count, word_count, sent_count))

main()

