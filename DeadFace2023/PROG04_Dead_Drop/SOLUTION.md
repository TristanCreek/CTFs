## Description

Players will be given a Python 3 code skeleton containing a seemingly random array of strings, some helper functions, a recovery password string. The goal is to decode the code recovery string to reveal the sequence of numbers that are used with print_password() to return the flag.

## Challenge

> The Incident Response Team at Aurora Pharmaceuticals recently recovered this file from a user’s computer and artifacts show it was accessed by what they believe to be multiple DeadFace members. The program appears to have set up the user’s workstation as a dead drop for DeadFace members to convert a secret numerical code into a password string for further target access. Our decoding attempts have been unsuccessful, but the script appears to contain a recovery code that may be a good starting point.
>
> Submit the flag as `flag{the password}` exactly how print_password() returns it.

```python
# Password recovery:
# buA9kvZ=T_A}b[J8l:@ob_tviPZtb_<olOpxkvZ=T_=xju]olOpxkvZ=T_bxlu]olOpxkvZ=QIEE
arr = ['empty', 'interest', 'current', 'valuable', 'influence', 'from', 'scolded', 'would', 'got', 'key', 'facility', 'run', 'great', 'tack', 'scent', 'close', 'are', 'a', 'plan', 'counter', 'earth', 'self', 'we', 'sick', 'return', 'admit', 'bear', 'cache', 'to', 'grab', 'domination', 'feedback', 'especially', 'motivate', 'tool', 'world', 'phase', 'semblance', 'tone', 'is', 'will', 'the', 'can', 'global', 'tell', 'box', 'alarm', 'life', 'necessary']
def print_password(nums):
    if len(nums) < 1:
        print("Must provide a list of at least one number i.e. [1]")
    print("flag{{{}}}".format(" ".join([arr[num] for num in nums])))

def left_shift(s, n):
    return ''.join(chr(ord(char) - n) for char in s)
```

## Hints

1. The provided left_shift() function may help convert the password recovery string into a more useful string.
2. Identifying unique characteristics of the last character or two may help identify further steps for decoding.
3. Base64 strings are often identifiable by the fact that they end in 1 or 2 equal signs (=).

## Create Answer

The array of strings was manually created. The indices of the words that produce the flag are 41, 2, 18, 39, 35, and 30. Therefore, the password recovery string provided to the players can be generated with the following code. A space is intentionally added to the end of the “answer”  string so the resulting base64 ends in two equal signs.

```python
import base64
def right_shift(s, n):
    return ''.join(chr(ord(char) + n) for char in s)
answer = "fourty-one two eighteen thirty-nine thirty-five thirty "
base64_answer= base64.b64encode(answer.encode('utf-8')).decode('utf-8')
shifted_answer = right_shift(str(base64_answer), 8)
print(shifted_answer)
```

## Solution

One example of how the players are intended to solve this is provided below. As the hints imply, the goal is to shift the password recovery string until it results in a string that ends in an equal sign which may indicate it is Base64. Shifting the string 58 times results in an invalid character, so checking all left shifts from 0 to 57 will result in only one string that ends in an equal sign after shifting left 8 times. The resulting base64 string decodes to “fourty-one two eighteen thirty-nine thirty-five thirty “.

```python
shift_b64 = ""
for i in range(0,57):
    shifted = left_shift("buA9kvZ=T_A}b[J8l:@ob_tviPZtb_<olOpxkvZ=T_=xju]olOpxkvZ=T_bxlu]olOpxkvZ=QIEE", i)
    if shifted[-1] == '=':
        shift_b64 = shifted

dec = base64.b64decode(shift_b64).decode('utf-8')
print(dec)
```

Finally, these numbers are passed to print_password() in an array to print the flag.

```python
print_password([41, 2, 18, 39, 35, 30])
```

## Flag

flag{the current plan is world domination}
