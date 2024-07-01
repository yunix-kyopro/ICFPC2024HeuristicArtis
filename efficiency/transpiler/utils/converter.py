

chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!"#$%&\'()*+,-./:;<=>?@[\]^_`|~ \n'

def icfp_to_string(icfp_str: str) -> str:
    result = ""
    for i in range(0, len(icfp_str)) :
        ascii_num = ord(icfp_str[i]) 
        # print(i, input_str[i], ascii_num, chars[ascii_num-33])
        result += chars[ascii_num-33]
    return result

def icfp_to_int(icfp_str: str) -> int:
    result = 0
    for i in range(0, len(icfp_str)) :
        ascii_num = ord(icfp_str[i])-33
        result += pow(94, len(icfp_str)-i-1)*ascii_num
    return result


def string_to_icfp(input_str: str) -> str:
    result = ""
    for i in range(0, len(input_str)) :
        ascii_num = chars.index(input_str[i])+33
        result += chr(ascii_num)
    return result

def int_to_icfp(input_int: int) -> str:
    result = ""
    while input_int > 0:
        ascii_num = input_int % 94 + 33
        result = chr(ascii_num) + result
        input_int = input_int // 94
    return result

def int_to_string(input_int: int) -> str:
    return icfp_to_string(int_to_icfp(input_int))

def string_to_int(input_str: str) -> int:
    return icfp_to_int(string_to_icfp(input_str))


