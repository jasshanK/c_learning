import random

pattern = "123"
byte_length = 256

string_of_bytes = ""
for i in range(byte_length):
    rand_num = random.randrange(0, 16)
    string_of_bytes += str(hex(rand_num))[-1]

skip_till = 0
for i in range(byte_length-len(pattern)):
    if skip_till != i and skip_till != 0:
        continue
    else: 
        skip_till = 0

    if string_of_bytes[i] == '1' and i != 0:
        string_of_bytes = string_of_bytes[:i] + pattern + string_of_bytes[i+len(pattern):]
        skip_till = i + len(pattern)

output = f'uint8_t bytes[{byte_length}] = {{'
for char in string_of_bytes:
    output += "0x" + char + ', '

output = output[:-2] + "};"

print(output)
    


