from django.shortcuts import render, HttpResponse
from TestModel import models
from django.core.exceptions import ValidationError
from django.utils.timezone import now
from TestModel.models import DailyNewBj
from django.db.models import Avg,Max,Min,Count,Sum
from . import daily_new_form
from .daily_new_form import dailyform,deleteform
from TestModel.models import DailyTotalProvince
from TestModel.models import DailyNewProvince
from TestModel.models import DailyTotalNationwide
from TestModel.models import DailyNewNationwide
from datetime import datetime,timedelta
from django.http import JsonResponse

import random
import datetime
import json
import time

def rqst_process(request):
    if request.method=='GET':
        if 'getmap' in request.GET:
            print('getmap')
            array = []
            if 'bydate' in request.GET:
                array = getMapByDate()
            else:
                array = getMapInfo()
            print(array)
            arrdic = {
                "array": array
            }
            json_res = json.dumps(arrdic)
            return HttpResponse(json_res)
        elif 'province' in request.GET:
            prov_name = request.GET.get("province")
            print(prov_name)
            array = []
            if 'bydate' in request.GET:
                print('province bydate')
                array = getProvByDate(prov_name)
            elif 'date' in request.GET:
                print('province date')
                date = request.GET.get('date')
                print(date)
                array = getProvByday(date, prov_name)
                # try:
                #     if ":" in date:
                #         time.strptime(date, "%Y-%m-%d %H:%M:%S")
                #     else:
                #         time.strptime(date, "%Y-%m-%d")
                #     array = getProvByday(date, prov_name)
                # except:
                #     print("error data type")
                #     return None
            else:
                print('province')
                array = getProvInfo(prov_name)
            # print(array)
            arrdic = {
                "array": array
            }
            json_res = json.dumps(arrdic)
            return HttpResponse(json_res)                
    elif request.method == 'POST':
        print('post')
        json_data = request.body
        #json中数据转化为字典
        req_dict = json.loads(json_data.decode('utf-8'))
        print(req_dict)
        if req_dict['operation']==0: #插入
            if DailyNewProvince.objects.filter(day=req_dict['date'],province=req_dict['province']):#该日期有数据,不可新增
                ret_dict={
                    "status": "Failed",
                    "msg": "该日期已经新增过数据"
                }
                print("该日期已经新增过数据")
                # json_res = json.dumps(ret_dict)
                return JsonResponse(ret_dict)
            else:#可新增
                # new_id = req_dict['province'] + req_dict['date']
                # insert=DailyNewProvince(id=new_id,province=req_dict['province'],day=req_dict['date'],cured=req_dict['cured'],diagnosed=req_dict['diagnosed'],dead=req_dict['dead'],asymptomatic=req_dict['asymptomatic'],abroad_in=req_dict['abroad_in'],suspected=req_dict['suspected'])
                insert=DailyNewProvince(province=req_dict['province'],day=req_dict['date'],cured=req_dict['cured'],diagnosed=req_dict['diagnosed'],dead=req_dict['dead'],asymptomatic=req_dict['asymptomatic'],abroad_in=req_dict['abroad_in'],suspected=req_dict['suspected'])
                insert.save()
                ret_dict={
                    "status":"Success",
                    "msg": "添加成功"
                }
                print("添加成功")
                # json_res = json.dumps(ret_dict)
                return JsonResponse(ret_dict)
        elif req_dict['operation']==1:#删除
            if DailyNewProvince.objects.filter(day=req_dict['date'],province=req_dict['province']):#该日期有数据可以删除
                DailyNewProvince.objects.filter(day=req_dict['date'],province=req_dict['province']).delete()
                ret_dict={
                    "status":"Success",
                    "msg":"删除成功"
                }
                print("删除成功")
                # json_ret = json.dumps(ret_dict)
                return JsonResponse(ret_dict)
            else:#没有数据
                ret_dict={
                    "status":"Failed",
                    "msg":"该日期没有数据可供删除"
                }
                print("该日期没有数据可供删除")
                # json_ret = json.dumps(ret_dict)
                return JsonResponse(ret_dict)

        if request.POST.__contains__('province'):
            # prov_name = request.POST.get("province")
            # print(prov_name)
            json_data = request.body
            print("12")
            #json中数据转化为字典
            req_dict = json.loads(json_data.decode('utf-8'))
            print(req_dict)
            res = {
                "data": 1,
                "status": 0
            }
            json_res = json.dumps(res)
            return HttpResponse(json_res)
        print('12')
    return render(request,'index.html')


def getMapInfo():
    province_list=['AH','BJ','FJ','GS','GD','GX','GZ','HI','HE','HA','HL','HB','HN','JL','JS','JX','LN','IM','NX','QH','SD','SX','SN','SH','SC','TJ','XZ','XJ','YN','ZJ','CQ','MO','HK','TW']
    day=now().date()
    date_start=datetime.date(2020,1,1)#数据统计起始日期
    data_list=[]#最终返回的数组
    prov_datas=DailyNewProvince.objects.filter(day__gte=date_start,day__lte=day)#过滤从数据起始日到当日数据
    for province in province_list:
        prov_data=dict()#字典，暂存每个省份数据
        prov_d=prov_datas.filter(province=province).aggregate(tdiagnosed=Sum("diagnosed"),tdead=Sum("dead"),tcured=Sum("cured"),tsuspected=Sum("suspected"),tabroad_in=Sum("abroad_in"),tasymptomatic=Sum("asymptomatic"))#某省总计数据
        prov_data['prov_name']=province
        prov_data['diagnosed']=prov_d['tdiagnosed']
        prov_data['dead']=prov_d['tdead']
        prov_data['cured']=prov_d['tcured']
        prov_data['suspected']=prov_d['tsuspected']
        prov_data['abroad_in']=prov_d['tabroad_in']
        prov_data['asymptomatic']=prov_d['tasymptomatic']
        data_list.append(prov_data)
    return data_list


def getMapByDate():
    i=0
    prov_list=['AH','BJ','FJ','GS','GD','GX','GZ','HI','HE','HA','HL','HB','HN','JL','JS','JX','LN','IM','NX','QH','SD','SX','SN','SH','SC','TJ','XZ','XJ','YN','ZJ','CQ','MO','HK','TW']
    day=now().date()#今日日期
    data_dict=dict()
    date_start = datetime.date(2020,1,1)#数据统计起始日期
    date_list = []
    while(i<10):
        diag = 0
        dead = 0
        cured = 0
        suspected = 0
        abroad_in = 0
        asym = 0
        daily_data = dict()
        #获取从指定日期起往前10天的数据
        for prov in prov_list:
            date = day + timedelta(days=-10+i+1)
            prov_data = DailyNewProvince.objects.filter(day__gte=date_start,day__lte=date,province=prov).aggregate(tdiagnosed=Sum("diagnosed"),tdead=Sum("dead"),tcured=Sum("cured"),tsuspected=Sum("suspected"),tabroad_in=Sum("abroad_in"),tasymptomatic=Sum("asymptomatic"))#某省总计数据
            diag += prov_data['tdiagnosed']
            dead += prov_data['tdead']
            cured += prov_data['tcured']
            suspected += prov_data['tsuspected']
            abroad_in += prov_data['tabroad_in']
            asym += prov_data['tasymptomatic']
        
        daily_data['diagnosed'] = diag
        daily_data['dead'] = dead
        daily_data['cured'] = cured
        daily_data['suspected'] = suspected
        daily_data['abroad_in'] = abroad_in
        daily_data['asymptomatic'] = asym
        daily_data['date'] = str(date)
        data_dict[date]=daily_data
        print(daily_data)
        date_list.append(daily_data)
        i += 1
    return date_list


def getProvInfo(prov_name):
    province_list = []
    province_list.append(prov_name)
    day = now().date()
    date_start = datetime.date(2020,1,1)#数据统计起始日期
    data_list = []#最终返回的数组
    prov_datas = DailyNewProvince.objects.filter(day__gte=date_start,day__lte=day)#过滤从数据起始日到当日数据
    for province in province_list:
        prov_data = dict()#字典，暂存每个省份数据
        prov_d = prov_datas.filter(province=province).aggregate(tdiagnosed=Sum("diagnosed"),tdead=Sum("dead"),tcured=Sum("cured"),tsuspected=Sum("suspected"),tabroad_in=Sum("abroad_in"),tasymptomatic=Sum("asymptomatic"))#某省总计数据
        prov_data['prov_name'] = province
        prov_data['diagnosed'] = prov_d['tdiagnosed']
        prov_data['dead'] = prov_d['tdead']
        prov_data['cured'] = prov_d['tcured']
        prov_data['suspected'] = prov_d['tsuspected']
        prov_data['abroad_in'] = prov_d['tabroad_in']
        prov_data['asymptomatic'] = prov_d['tasymptomatic']
        data_list.append(prov_data)
    return data_list


def getProvByDate(prov_name):
    i=0
    prov_list=[prov_name]
    day=now().date()#今日日期
    data_dict=dict()
    date_start = datetime.date(2020,1,1)#数据统计起始日期
    date_list = []
    while(i<10):
        diag = 0
        dead = 0
        cured = 0
        suspected = 0
        abroad_in = 0
        asym = 0
        daily_data = dict()
        #获取从指定日期起往前10天的数据
        for prov in prov_list:
            date = day + timedelta(days=-10+i+1)
            prov_data = DailyNewProvince.objects.filter(day__gte=date_start,day__lte=date,province=prov).aggregate(tdiagnosed=Sum("diagnosed"),tdead=Sum("dead"),tcured=Sum("cured"),tsuspected=Sum("suspected"),tabroad_in=Sum("abroad_in"),tasymptomatic=Sum("asymptomatic"))#某省总计数据
            diag += prov_data['tdiagnosed']
            dead += prov_data['tdead']
            cured += prov_data['tcured']
            suspected += prov_data['tsuspected']
            abroad_in += prov_data['tabroad_in']
            asym += prov_data['tasymptomatic']
        
        daily_data['diagnosed'] = diag
        daily_data['dead'] = dead
        daily_data['cured'] = cured
        daily_data['suspected'] = suspected
        daily_data['abroad_in'] = abroad_in
        daily_data['asymptomatic'] = asym
        daily_data['date'] = str(date)
        data_dict[date]=daily_data
        print(daily_data)
        date_list.append(daily_data)
        i += 1
    return date_list


def getProvByday(date, prov_name):
    ret_dict = dict()
    data_list = []
    if isVaildDate(date) == False:
        ret_dict['date'] = date
        ret_dict['province'] = prov_name
        ret_dict['dead'] = '--'
        ret_dict['diagnosed'] = '--'
        ret_dict['asymptomatic'] = '--'
        ret_dict['abroad_in'] = '--'
        ret_dict['suspected'] = '--'
        ret_dict['cured'] = '--'
        data_list.append(ret_dict)
        return data_list

    data = DailyNewProvince.objects.filter(day=date,province=prov_name)
    print(data)
    
    if data.exists() == False:
        ret_dict['date'] = date
        ret_dict['province'] = prov_name
        ret_dict['dead'] = '无'
        ret_dict['diagnosed'] = '无'
        ret_dict['asymptomatic'] = '无'
        ret_dict['abroad_in'] = '无'
        ret_dict['suspected'] = '无'
        ret_dict['cured'] = '无'
    else:
        for e in data:
            ret_dict['date'] = date
            ret_dict['province'] = prov_name
            ret_dict['dead'] = e.dead
            ret_dict['diagnosed'] = e.diagnosed
            ret_dict['asymptomatic'] = e.asymptomatic
            ret_dict['abroad_in'] = e.abroad_in
            ret_dict['suspected'] = e.suspected
            ret_dict['cured'] = e.cured
    data_list.append(ret_dict)
    return data_list


def isVaildDate(date):
    try:
        if ":" in date:
            time.strptime(date, "%Y-%m-%d %H:%M:%S")
        else:
            time.strptime(date, "%Y-%m-%d")
        return True
    except:
        return False


def hello(request):
    data = {}
    data['death'] = 122 + random.randint(1,10)
    data['diag'] = 123
    jsonData = json.dumps(data)
    if request.method == "GET" and 'getdata' in request.GET:
        print("hello")
        return HttpResponse(jsonData)
    print("hel")

    return render(request,'index.html')
