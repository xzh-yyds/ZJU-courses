from django.shortcuts import render, HttpResponse
from TestModel import models
from .daily_new_form import dailyform
from .daily_new_form import deleteform
from django.core.exceptions import ValidationError
from django.utils.timezone import now
from TestModel.models import DailyTotalProvince,DailyNewProvince,DailyTotalNationwide,DailyNewNationwide
from datetime import datetime,timedelta
from django.db.models import Avg,Max,Min,Count,Sum
from django.http import JsonResponse
import json

def view(request):
    if request.method=="GET":#get请求
        if request.GET.__contains__('getmap'):#获取地图数据
            array=getmapinfo()
            jsondata = json.dumps(array)
            print(jsondata)
            return JsonResponse(jsondata,safe=False)
        elif request.GET.__contains__('province'):#获取每个省份的疫情信息
            prov_name=request.GET.get("province")
            data_dict=getprovincedata(prov_name)
            return JsonResponse(data_dict)
    elif request.method=="POST":#表单
        if request.POST.__contains__('province'):#提交或更新
            req_data=request.body
            req_dict=json.loads(req_data.decode('utf-8'))#json中数据转化为字典
            if req_dict['operation']==0: #插入
                if DailyNewProvince.objects.filter(day=req_dict['date'],province=req_dict['province']):#该日期有数据,不可新增
                    ret_dict={
                        "status":"Failed",
                        "message":"该日期已经新增过数据"
                    }
                    return JsonResponse(ret_dict)
                else:#可新增
                    insert=DailyNewProvince(province=req_dict['province'],day=req_dict['date'],cured=req_dict['cured'],diagnosed=req_dict['diagnosed'],dead=req_dict['dead'],asymptomatic=req_dict['asymptomatic'],abroad_in=req_dict['abroad_in'],suspected=req_dict['suspected'])
                    insert.save()
                    ret_dict={
                        "status":"Success",
                    }
                    return JsonResponse(ret_dict)
                   
            elif req_dict['operation']==1:#删除
                if DailyNewProvince.objects.filter(day=req_dict['date'],province=req_dict['province']):#该日期有数据可以删除
                    DailyNewProvince.objects.filter(day=req_dict['date'],province=req_dict['province']).delete()
                    ret_dict={
                        "status":"Success",
                    }
                    return JsonResponse(ret_dict)
                else:#没有数据
                    ret_dict={
                        "status":"Failed",
                        "message":"该日期没有数据可供删除"
                    }
                    return JsonResponse(ret_dict)


    def getprovincedata(self,prov_name):
        i=0
        day=now().date()#今日日期
        data_dict=dict()
        date_start=datetime.date(2020,1,1)#数据统计起始日期
        while(i<10):
            date=day-timedelta(days=-10+i+1)#获取从指定日期起往前10天的数据
            daily_data=dict()
            prov_data=DailyNewProvince.objects.filter(day__gte=date_start,day__lte=date,province=prov_name).aggregate(tdiagnosed=Sum("diagnosed"),tdead=Sum("dead"),tcured=Sum("cured"),tsuspected=Sum("suspected"),tabroad_in=Sum("abroad_in"),tasasymptomatic=Sum("asasymptomatic"))#某省总计数据
            daily_data['prov_name']=prov_name
            daily_data['diagnosed']=prov_data['tdiagnosed']
            daily_data['dead']=prov_data['tdead']
            daily_data['cured']=prov_data['tcured']
            daily_data['suspected']=prov_data['tsuspected']
            daily_data['abroad_in']=prov_data['tabroad_in']
            daily_data['asasymptomatic']=prov_data['tasasymptomatic']
            data_dict[date]=daily_data
        return data_dict


    def getmapinfo(self):
        province_list=['AH','BJ','FJ','GS','GD','GX','GZ','HI','HE','HA','HL','HB','HN','JL','JS','JX','LN','IM','NX','QH','SD','SX','SN','SH','SC','TJ','XZ','XJ','YN','ZJ','CQ','MO','HK','TW']
        day=now().date()
        date_start=datetime.date(2020,1,1)#数据统计起始日期
        data_list=[]#最终返回的数组
        prov_datas=DailyNewProvince.objects.filter(day__gte=date_start,day__lte=day)#过滤从数据起始日到当日数据
        for province in province_list:
            prov_data=dict()#字典，暂存每个省份数据
            prov_d=prov_datas.filter(province=province).aggregate(tdiagnosed=Sum("diagnosed"),tdead=Sum("dead"),tcured=Sum("cured"),tsuspected=Sum("suspected"),tabroad_in=Sum("abroad_in"),tasasymptomatic=Sum("asasymptomatic"))#某省总计数据
            prov_data['prov_name']=province
            prov_data['diagnosed']=prov_d['tdiagnosed']
            prov_data['dead']=prov_d['tdead']
            prov_data['cured']=prov_d['tcured']
            prov_data['suspected']=prov_d['tsuspected']
            prov_data['abroad_in']=prov_d['tabroad_in']
            prov_data['asasymptomatic']=prov_d['tasasymptomatic']
            data_list.append(prov_data)
        return data_list
