import random
import xlwt

def gen_triads(params:list):
    res = {}
    for i in range(len(params)):
        for j in range(i+1, len(params)):
            for k in range(j+1, len(params)):
                pairs = [(ii, jj, kk) 
                        for ii in range(params[i]) 
                        for jj in range(params[j]) 
                        for kk in range(params[k])]
                res[(i, j, k)] = pairs
    return res

def uncovered_cnt(pairss:dict):
    cnt = 0
    for pairs in pairss.values():
        cnt += len(pairs)
    return cnt

def print_dict(d:dict):
    print('{')
    for k in d.keys():
        print(' ' ,k, d[k])
    print('}')

def gen_case(params:list, uncovered_pairs:dict):
    n = len(params)
    res = []
    covered_cnt = 0

    cnt = [0 for _ in range(params[0])]
    for j in range(0, n):
        if j==0:
            continue
        for k in range(j+1, n):
            pairs = uncovered_pairs[(0, j, k)]
            for v, _, __ in pairs:
                cnt[v] += 1
    v = cnt.index(max(cnt))
    res.append(v)

    cnt = [0 for _ in range(params[1])]
    for j in range(0, n):
        if j==1:
            continue
        for k in range(j+1, n):
            if k==1:
                continue
            pairs = uncovered_pairs[tuple(sorted((1,j,k)))]
            for v in pairs:
                cnt[v[sorted((1,j,k)).index(1)]] += 1
    v = cnt.index(max(cnt))
    res.append(v)

    cnt = [0 for _ in range(params[2])]
    for j in range(0, n):
        if j==2:
            continue
        for k in range(j+1, n):
            if k==2:
                continue
            pairs = uncovered_pairs[tuple(sorted((2,j,k)))]
            for v in pairs:
                cnt[v[sorted((2,j,k)).index(2)]] += 1
    v = cnt.index(max(cnt))
    res.append(v)

    if (res[0], res[1], res[2]) in uncovered_pairs[(0, 1, 2)]:
        uncovered_pairs[(0, 1, 2)].remove((res[0], res[1], res[2]))
        covered_cnt += 1
    else:
        if uncovered_pairs[(0, 1, 2)]:
            res[0], res[1], res[2] = uncovered_pairs[(0, 1, 2)].pop()
            covered_cnt += 1
        else:
            res[0] = random.randrange(params[0])
            res[1] = random.randrange(params[1])
            res[2] = random.randrange(params[2])
    
    for k in range(3, n):
        cnt = [0 for _ in range(params[k])]
        for v in range(params[k]):
            for i in range(k):
                for j in range(i+1, k):
                    pairs = uncovered_pairs[(i, j, k)]
                    if (res[i], res[j], v) in pairs:
                        cnt[v] += 1
        res.append(cnt.index(max(cnt)))
        cover = False
        for i in range(k):
            for j in range(i+1, k):
                pairs = uncovered_pairs[(i, j, k)]
                if (res[i], res[j], res[k]) in pairs:
                    pairs.remove((res[i], res[j], res[k]))
                    covered_cnt += 1
                    cover = True
        if not cover:
            res[k] = random.randrange(params[k])
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

def gen_cases(params:list):
    triads = gen_triads(params)
    cases = []
    covers = []
    while uncovered_cnt(triads) > 0:
        case, cover = gen_case(params, triads)
        if cover <= 0:
            continue
        cases.append(case)
        covers.append(cover)
    return cases, covers

def save_as_xls(table:list):
    xls = xlwt.Workbook()
    sheet1 = xls.add_sheet('test cases', cell_overwrite_ok=True)
    for i in range(len(table)):
        for j in range(len(table[i])):
            sheet1.write(i, j, table[i][j])
    xls.save('2.xls')

def problem2():
    param_names = ['品牌', '屏幕尺寸', '能效等级', '分辨率', '电视类型', '品牌类型', '观看距离', '用户优选', '产品渠道']
    param_vals = [
        ['不选', '小米', '创维', 'hisense', 'tcl', 'sony', 'sony', 'changhor', 'knoka', 'haier', '三星', '华为', 'philips', '酷开'],
        ['不选', '78英寸及以上', '70-75英寸', '65英寸', '58-60英寸', '55英寸', '48-50英寸', '39-45英寸', '32英寸及以下'],
        ['不选', '一级能效', '二级能效', '三级能效', '无能效等级'],
        ['不选', '8K超高清(7680x4320)', '4K超高清(3840*2160)', '全高清(1920*1080)', '高清(1366*768)', '1024*600'],
        ['不选', 'OLED', '全面屏', '人工智能', '大屏', '教育电视', '智慧屏', '超薄', '4K超清', '量子点', '曲面', '激光电视', '商业显示', '游戏电视'],
        ['不选', '合资品牌', '国产品牌', '互联网品牌', '商业显示品牌'],
        ['不选', '3.5m以上(70英寸以上)', '3m-3.5m(56-65英寸)', '2.5-3m(46-55英寸)', '2-2.5m(33-45英寸)', '2m以下(小于等于32英寸)'],
        ['不选', '京品电视', '新品电视'],
        ['不选', '线下同款', '线上专供']
    ]
    params = [len(vals) for vals in param_vals]
    # params = [14, 9, 5, 6, 14, 5, 6, 3, 3]
    # print(params)

    params, back = params_shuffle(params)
    cases, cnts = gen_cases(params)
    cases = shuffle_back(cases, back)
    
    print('all:', sum([params[i] * params[j] * params[k] 
                            for i in range(len(params))
                            for j in range(i+1, len(params))
                            for k in range(j+1, len(params))]))
    print('covered:', sum(cnts))
    print(f'generated {len(cnts)} cases')

    res = []
    for case in cases:
        res.append([param_vals[i][case[i]] for i in range(len(case))])
    for i in range(len(res)):
        res[i].append(cnts[i])
    param_names.append('triads cover')
    table = [param_names] + res
    save_as_xls(table)

def main():
    problem2()


main()