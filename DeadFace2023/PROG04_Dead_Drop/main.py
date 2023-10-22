# Question Prompt
# This file was found on one of DeadFace's Targets of Interest.
# We believe it is used as a dead drop for other DeadFace members to convert a known numerical code into a password string for further target access.
# Our decoding attempts have been unsuccessful, but the script appears to contain some sort of hint that may be a good starting point.

# PLAYER CODE
# Password recovery:
# buA9kvZ=T_A}b[J8l:@ob_tviPZtb_<olOpxkvZ=T_=xju]olOpxkvZ=T_bxlu]olOpxkvZ=QIEE
arr = ['empty', 'interest', 'current', 'valuable', 'influence', 'from', 'scolded', 'would', 'got', 'key', 'facility', 'run', 'great', 'tack', 'scent', 'close', 'are', 'a', 'plan', 'counter', 'earth', 'self', 'we', 'sick', 'return', 'admit', 'bear', 'cache', 'to', 'grab', 'domination', 'feedback', 'especially', 'motivate', 'tool', 'world', 'phase', 'semblance', 'tone', 'is', 'will', 'the', 'can', 'global', 'tell', 'box', 'alarm', 'life', 'necessary']
def print_password(nums):
    if len(nums) < 1:
        print("Must provide a list of at least one number i.e. [1]")
    print("flag{{{}}}".format(" ".join([arr[num] for num in nums])))

def left_shift(s, n):
    return ''.join(chr(ord(char) - n) for char in s)

# HINTS
# Hint #1: The provided left_shift function may help convert the code recovery string into a more useful string.
# Hint #2: Identifying unique characteristics of the last character or two may help identify further steps for decoding.
# Hint #3: Base64 strings are often identifiable by the fact that they end in an equal sign (=).

# CODE TO CREATE ANSWER
import base64
def right_shift(s, n):
    return ''.join(chr(ord(char) + n) for char in s)
answer = "fourty-one two eighteen thirty-nine thirty-five thirty "
base64_answer= base64.b64encode(answer.encode('utf-8')).decode('utf-8')
shifted_answer = right_shift(str(base64_answer), 8)
print(shifted_answer)

# SOLUTION CODE
# 57 is not arbitrary, shifting the characters by 58 results in an invalid character
shift_b64 = ""
for i in range(0,57):
    shifted = left_shift("buA9kvZ=T_A}b[J8l:@ob_tviPZtb_<olOpxkvZ=T_=xju]olOpxkvZ=T_bxlu]olOpxkvZ=QIEE", i)
    if shifted[-1] == '=':
        shift_b64 = shifted

#dec = base64.b64decode('Zm91cnR5LW9uZSB0d28gZWlnaHRlZW4gdGhpcnR5LW5pbmUgdGhpcnR5LWZpdmUgdGhpcnR5IA==').decode('utf-8')
dec = base64.b64decode(shift_b64).decode('utf-8')
print(dec)
print_password([41, 2, 18, 39, 35, 30])