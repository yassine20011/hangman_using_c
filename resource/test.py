data = ['resource/data.txt', 'resource/animals/data.txt', 'resource/foot/data.txt', 'resource/edu/data.txt', 'resource/music/data.txt', 'resource/informatique/data.txt']

output_path = ["resource", "resource/animals", "resource/foot", "resource/edu", "resource/music", "resource/informatique"]


def test(data_path, output_path):
    
    with open(fr'{output_path}\words.txt', 'w') as f:
        f.write('')
        f.close()

    with open(fr'{output_path}\hint1.txt', 'w') as f:
        f.write('')
        f.close()

    with open(fr'{output_path}\hint2.txt', 'w') as f:
        f.write('')
        f.close()


    with open(fr'{output_path}\hint3.txt', 'w') as f:
        f.write('')
        f.close()

    with open(data_path, 'r') as f:
        for line in f:
            word = line.split(':')[0].lower()
            s = line.split(' ')
            hint1 = s[1].replace('\n', '').replace(',', '').lower()
            hint2 = s[2].replace('\n', '').replace(',', '').lower()
            hint3 = s[3].replace('\n', '').replace(',', '').lower()
            with open(fr'{output_path}\words.txt', 'a') as f:
                f.write(word + '\n')
            with open(fr'{output_path}\hint1.txt', 'a') as f:
                f.write(hint1 + '\n')
            with open(fr'{output_path}\hint2.txt', 'a') as f:
                f.write(hint2 + '\n')
            with open(fr'{output_path}\hint3.txt', 'a') as f:
                f.write(hint3 + '\n')


for i in range(len(data)):
    test(data[i], output_path[i])