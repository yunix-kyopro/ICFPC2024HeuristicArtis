# 文字列リテラルを94進数に圧縮するプログラム
# 
# [使い方]
# 1. python string_compressor.py -f <file-path> -n <problem_no> を実行する
#    ここで、<file-path>は最終的に出力したい文字列（例: LLLLDDLLUUDDLLUULL）が書かれたファイルのパス
# 2. 出力された文字列（BDから始まる）をコピーする
# 3. 文字列結合演算子（B.）を使って他の命令と合体させる
#    例えば、echoしたい場合は B. S%#(/} <output> のようにする
#    echoの後のスペースを忘れないこと

import argparse

def convert_base10_to_base94(x):
    base94 = ""
    if x == 0:
        base94 = "!"
    else:
        while x > 0:
            v = x % 94
            base94 = chr(v + ord("!")) + base94
            x //= 94

    return "I" + base94

parser = argparse.ArgumentParser()
parser.add_argument('-f', '--file-path')
parser.add_argument('-n', '--problem-no')
args = parser.parse_args()

with open(args.file_path) as f:
    raw_string = f.read()

if len(raw_string) == 0:
    print("File is empty")
    exit()

string_dict = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!"#' + "$%&'()*+,-./:;<=>?@[\]^_`|~ "
inv_string_dict = {}

for i, c in enumerate(string_dict):
    inv_string_dict[c] = chr(i + ord("!"))

inv_string_dict["\n"] = "~"

s = ""

# サボってO(N^2)にしている
for c in raw_string:
    s += inv_string_dict[c]

init_len = len(s)

print()
print(f"Initial length : {init_len}")
print(f"Initial length + S : {init_len + 1}")

chars = []

for c in s:
    if c not in chars:
        chars.append(c)

char_list = "".join(chars)

# n進数
base = len(chars)

# 「n進数」のnを94進数で表現したもの
base_base94 = convert_base10_to_base94(base)
inv_dict = {}

for i, c in enumerate(chars):
    inv_dict[c] = i

result = ""

# "solve lambdamanXX "と結合
result += "B. S"

for c in f"solve lambdaman{args.problem_no} ":
    result += inv_string_dict[c]

# 頭の番兵を消す
result += ' BD I" '

# Yコンビネータとか
result += 'B$ B$ B$ L" B$ L# B$ v" B$ v# v# L# B$ v" B$ v# v# '

# 再帰関数の中身
result += f'L" L# L$ ? B= v$ I! S! B. B$ B$ v" B/ v# {base_base94} B- v$ I" BT I" BD B% v# {base_base94} S{char_list} '

# 元の文字列を一旦10進数に変換
sum = 0

for c in s:
    sum *= base
    sum += inv_dict[c]

# これを94進数にする
sum_base94 = convert_base10_to_base94(sum)

# 先程の再帰関数の引数にする
result += f"{sum_base94} "

# 長さをbase94に変換
len_base94 = convert_base10_to_base94(init_len)

# 先程の再帰関数の引数にする
result += f"{len_base94}"

print(f"Compressed length : {len(result)}")
print()
print(result)
