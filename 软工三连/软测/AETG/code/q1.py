import random
import xlwt

def gen_pairs(params:list):
    res = {}
    for i in range(len(params)):
        for j in range(i+1, len(params)):
            pairs = []
            for ii in range(params[i]):
                for jj in range(params[j]):
                    pairs.append((ii,jj))
            res[(i, j)] = pairs
    return res

def uncovered_cnt(pairss:dict):
    cnt = 0
    for pairs in pairss.values():
        cnt += len(pairs)
    return cnt

def gen_case(params:list, uncovered_pairs:dict):
    n = len(params)
    res = []
    covered_cnt = 0

    cnt = [0 for _ in range(params[0])]
    for j in range(0, n):
        if j==0:
            continue
        pairs = uncovered_pairs[(0, j)]
        for v, _ in pairs:
            cnt[v] += 1
    v = cnt.index(max(cnt))
    res.append(v)

    cnt = [0 for _ in range(params[1])]
    for j in range(0, n):
        if j==1:
            continue
        pairs = uncovered_pairs[(1, j) if j>1 else (j, 1)]
        for v in pairs:
            cnt[v[sorted((1,j)).index(1)]] += 1
    v = cnt.index(max(cnt))
    res.append(v)
    
    if (res[0], res[1]) in uncovered_pairs[(0, 1)]:
        uncovered_pairs[(0, 1)].remove((res[0], res[1]))
        covered_cnt += 1
    else:
        if uncovered_pairs[(0, 1)]:
            res[0], res[1] = uncovered_pairs[(0, 1)].pop()
            covered_cnt += 1
        else:
            res[0], res[1] = random.randrange(params[0]), random.randrange(params[1])

    for j in range(2, n):
        cnt = [0 for _ in range(params[j])]
        for v in range(params[j]):
            for i in range(j):
                pairs = uncovered_pairs[(i, j)]
                if (res[i], v) in pairs:
                    cnt[v] += 1
        res.append(cnt.index(max(cnt)))
        cover = False
        for i in range(j):
            pairs = uncovered_pairs[(i, j)]
            if (res[i], res[j]) in pairs:
                pairs.remove((res[i], res[j]))
                covered_cnt += 1
                cover = True
        if not cover:
            res[j] = random.randrange(params[j])
    return res, covered_cnt

def params_shuffle(params:list):
    n = len(params)
    param_no = [i for i in range(n)]
    random.shuffle(param_no)
    back = {param_no[i]:i for i in range(n)}
    res = []
    for i in range(n):
        res.append(params[param_no[i]])
    return res, back

def shuffle_back(cases:list, back:dict):
    res = []
    for case in cases:
        case = [case[back[i]] for i in range(len(case))]
        res.append(case)
    return res

def gen_cases(params):
    pairs = gen_pairs(params)
    cases = []
    cover_cnts = []
    while uncovered_cnt(pairs) > 0:
        case, cnt = gen_case(params, pairs)
        if cnt > 0:
            cases.append(case)
            cover_cnts.append(cnt)
    return cases, cover_cnts

def print_dict(d:dict):
    print('{')
    for k in d.keys():
        print(' ' ,k, d[k])
    print('}')

def print_lislist(ll):
    print('[')
    for l in ll:
        print(' ', l)
    print(']')

def save_as_xls(table:list):
    xls = xlwt.Workbook()
    sheet1 = xls.add_sheet('test cases', cell_overwrite_ok=True)
    for i in range(len(table)):
        for j in range(len(table[i])):
            sheet1.write(i, j, table[i][j])
    xls.save('1.xls')

def problem1():
    param_names = ['用户名', '密码', '切换语言', '项目名称', '项目简介', '项目类型']
    param_vals = {
        0: ['正确用户名', '错误用户名'],
        1: ['正确密码', '错误密码'],
        2: ['中文', 'English'],
        3: ['不超过125位', '含特殊字符', '超过125位', '超过135位并含特殊字符'],
        4: ['不超过125位', '含特殊字符', '超过125位', '超过135位并含特殊字符'],
        5: ['web', 'ios', 'android app', 'win app', 'android小程序', '混合应用']
    }
    # params = [2, 2, 2, 4, 4, 6]
    params = [len(vals) for vals in param_vals.values()]
    # print(params)

    params, back = params_shuffle(params)
    cases, cnts = gen_cases(params)
    cases = shuffle_back(cases, back)

    print('all:', sum([params[i] * params[j]
                            for i in range(len(params))
                            for j in range(i+1, len(params))]))
    print('covered:', sum(cnts))
    print(f'generated {len(cnts)} cases')

    res = []
    for case in cases:
        res.append([param_vals[i][case[i]] for i in range(len(case))])
    for i in range(len(res)):
        res[i].append(cnts[i])
    param_names.append('pairs cover')
    table = [param_names] + res
    save_as_xls(table)
    # print_lislist(res)
    # return res


def main():
    problem1()


main()