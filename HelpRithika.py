import sys
import math

def get_max_prefix_length_and_deletions(sub_str, target_str, start_idx):
    sub_idx, target_idx, match_length = 0, start_idx, 0
    while sub_idx < len(sub_str) and target_idx < len(target_str):
        if sub_str[sub_idx] == target_str[target_idx]:
            match_length += 1
            target_idx += 1
        sub_idx += 1
    total_deletions = len(sub_str) - match_length
    return match_length, total_deletions

def process_input():
    inp = sys.stdin.read().splitlines()
    pos = 0
    num_strings = int(inp[pos].strip())
    pos += 1
    patterns = []
    for _ in range(num_strings):
        patterns.append(inp[pos].strip())
        pos += 1
    target = inp[pos].strip()
    pos += 1
    max_deletions = int(inp[pos].strip())
    pos += 1

    size = len(target)
    large_num = math.inf
    min_deletions = [large_num] * (size + 1)
    min_deletions[0] = 0

    for idx in range(size):
        if min_deletions[idx] == large_num:
            continue
        for pattern in patterns:
            length, deletions = get_max_prefix_length_and_deletions(pattern, target, idx)
            if length == 0:
                continue
            new_idx = idx + length
            if new_idx > size:
                continue
            if min_deletions[idx] + deletions < min_deletions[new_idx]:
                min_deletions[new_idx] = min_deletions[idx] + deletions

    if min_deletions[size] <= max_deletions:
        print("Possible")
    elif min_deletions[size] == large_num:
        print("Impossible")
    else:
        longest_pos = -1
        for idx in range(size, -1, -1):
            if min_deletions[idx] <= max_deletions:
                longest_pos = idx
                break
        print(target[:longest_pos] if longest_pos > 0 else "Nothing")

if name == "__main__":
    process_input()
