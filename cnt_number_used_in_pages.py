def count(number):
    _str = str(number) 
    length = len(_str) 
    cnt = [0] * 10 
    # 假设输入为43212
    for idx in range(length):
        # from left to right 
        # idx = 2
        cur_num = int(_str[idx])
        right_length = length - idx - 1
        right_num = int(_str[idx + 1:]) if right_length > 0 else 0
        if idx == 0:
            for num in range(1, cur_num):
                cnt[num] += 10**right_length 
            cnt[cur_num] += right_num + 1
        else:
            left_num = int(_str[:idx]) 
            for num in range(10):
                if num < cur_num:
                    if num == 0:
                        cnt[num] += left_num * 10**right_length
                    else:
                        cnt[num] += (left_num + 1) * 10**right_length 
                elif num == cur_num:
                    if num == 0:
                        cnt[num] += (left_num - 1) * 10**right_length
                    else:
                        cnt[num] += left_num * 10**right_length 
                    cnt[num] += right_num + 1
                else:
                    cnt[num] += left_num * 10**right_length
    return cnt


def bruce_cnt(number):
    cnt = [0] * 10
    for i in range(1,number+1):
        s = str(i)
        for j in s:
            cnt[int(j)] += 1
    return cnt 

n = 4000
print(bruce_cnt(n))
print(count(n))