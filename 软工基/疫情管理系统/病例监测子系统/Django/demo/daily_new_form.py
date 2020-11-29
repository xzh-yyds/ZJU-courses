from django import forms
from django.core.exceptions import ValidationError
from TestModel import models

class dailyform(forms.Form):
    asymptomatic=forms.IntegerField(label="无症状感染者",error_messages={"required":"请输入数据！"})
    cured=forms.IntegerField(label="治愈",error_messages={"required":"请输入数据！"})
    abroad_in=forms.IntegerField(label="境外输入",error_messages={"required":"请输入数据！"})
    diagnosed=forms.IntegerField(label="确诊",error_messages={"required":"请输入数据！"})
    suspected=forms.IntegerField(label="疑似",error_messages={"required":"请输入数据！"})
    dead=forms.IntegerField(label="死亡",error_messages={"required":"请输入数据！"})
    #day=forms.DateField(label="日期",error_messages={"required":"请输入数据！"})


class deleteform(forms.Form):
    deletedate=forms.DateField(label="日期",error_messages={"required":"请输入数据"})

    def clean_deletedate(self):#钩子，判断日期是否有数据可删除
        val=self.cleaned_data.get("deletedate")

        if models.DailyNewBj.objects.filter(day=val):#数据存在
            return val
        else:
            raise ValidationError("该日期没有数据")

    