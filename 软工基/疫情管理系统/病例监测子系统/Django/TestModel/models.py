# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey and OneToOneField has `on_delete` set to the desired behavior
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from django.db import models


class AccountAdmin(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    username = models.CharField(max_length=16)
    password = models.CharField(max_length=16)
    status = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'account_admin'


class AuthGroup(models.Model):
    name = models.CharField(unique=True, max_length=150)

    class Meta:
        managed = False
        db_table = 'auth_group'


class AuthGroupPermissions(models.Model):
    group = models.ForeignKey(AuthGroup, models.DO_NOTHING)
    permission = models.ForeignKey('AuthPermission', models.DO_NOTHING)

    class Meta:
        managed = False
        db_table = 'auth_group_permissions'
        unique_together = (('group', 'permission'),)


class AuthPermission(models.Model):
    name = models.CharField(max_length=255)
    content_type = models.ForeignKey('DjangoContentType', models.DO_NOTHING)
    codename = models.CharField(max_length=100)

    class Meta:
        managed = False
        db_table = 'auth_permission'
        unique_together = (('content_type', 'codename'),)


class AuthUser(models.Model):
    password = models.CharField(max_length=128)
    last_login = models.DateTimeField(blank=True, null=True)
    is_superuser = models.IntegerField()
    username = models.CharField(unique=True, max_length=150)
    first_name = models.CharField(max_length=30)
    last_name = models.CharField(max_length=150)
    email = models.CharField(max_length=254)
    is_staff = models.IntegerField()
    is_active = models.IntegerField()
    date_joined = models.DateTimeField()

    class Meta:
        managed = False
        db_table = 'auth_user'


class AuthUserGroups(models.Model):
    user = models.ForeignKey(AuthUser, models.DO_NOTHING)
    group = models.ForeignKey(AuthGroup, models.DO_NOTHING)

    class Meta:
        managed = False
        db_table = 'auth_user_groups'
        unique_together = (('user', 'group'),)


class AuthUserUserPermissions(models.Model):
    user = models.ForeignKey(AuthUser, models.DO_NOTHING)
    permission = models.ForeignKey(AuthPermission, models.DO_NOTHING)

    class Meta:
        managed = False
        db_table = 'auth_user_user_permissions'
        unique_together = (('user', 'permission'),)


class DailyNewAh(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_ah'


class DailyNewBj(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_bj'


class DailyNewCq(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_cq'


class DailyNewFj(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_fj'


class DailyNewGd(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_gd'


class DailyNewGs(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_gs'


class DailyNewGx(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_gx'


class DailyNewGz(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_gz'


class DailyNewHa(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_ha'


class DailyNewHb(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_hb'


class DailyNewHe(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_he'


class DailyNewHi(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_hi'


class DailyNewHk(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_hk'


class DailyNewHl(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_hl'


class DailyNewHn(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_hn'


class DailyNewIm(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_im'


class DailyNewJl(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_jl'


class DailyNewJs(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_js'


class DailyNewJx(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_jx'


class DailyNewLn(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_ln'


class DailyNewMo(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_mo'


class DailyNewNationwide(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_nationwide'


class DailyNewNx(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_nx'


class DailyNewProvince(models.Model):
    province = models.CharField(max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_province'


class DailyNewQh(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_qh'


class DailyNewSc(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_sc'


class DailyNewSd(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_sd'


class DailyNewSh(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_sh'


class DailyNewSn(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_sn'


class DailyNewSx(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_sx'


class DailyNewTj(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_tj'


class DailyNewTw(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_tw'


class DailyNewXj(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_xj'


class DailyNewXz(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_xz'


class DailyNewYn(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_yn'


class DailyNewZj(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_new_zj'


class DailyTotalAh(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_ah'


class DailyTotalBj(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_bj'


class DailyTotalCq(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_cq'


class DailyTotalFj(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_fj'


class DailyTotalGd(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_gd'


class DailyTotalGs(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_gs'


class DailyTotalGx(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_gx'


class DailyTotalGz(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_gz'


class DailyTotalHa(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_ha'


class DailyTotalHb(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_hb'


class DailyTotalHe(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_he'


class DailyTotalHi(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_hi'


class DailyTotalHk(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_hk'


class DailyTotalHl(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_hl'


class DailyTotalHn(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_hn'


class DailyTotalIm(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_im'


class DailyTotalJl(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_jl'


class DailyTotalJs(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_js'


class DailyTotalJx(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_jx'


class DailyTotalLn(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_ln'


class DailyTotalMo(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_mo'


class DailyTotalNationwide(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_nationwide'


class DailyTotalNx(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_nx'


class DailyTotalProvince(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    province = models.CharField(max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_province'


class DailyTotalQh(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_qh'


class DailyTotalSc(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_sc'


class DailyTotalSd(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_sd'


class DailyTotalSh(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_sh'


class DailyTotalSn(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_sn'


class DailyTotalSx(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_sx'


class DailyTotalTj(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_tj'


class DailyTotalTw(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_tw'


class DailyTotalXj(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_xj'


class DailyTotalXz(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_xz'


class DailyTotalYn(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_yn'


class DailyTotalZj(models.Model):
    id = models.CharField(primary_key=True, max_length=20)
    day = models.DateField()
    diagnosed = models.IntegerField()
    dead = models.IntegerField()
    suspected = models.IntegerField()
    asymptomatic = models.IntegerField()
    cured = models.IntegerField()
    abroad_in = models.IntegerField()

    class Meta:
        managed = False
        db_table = 'daily_total_zj'


class DjangoAdminLog(models.Model):
    action_time = models.DateTimeField()
    object_id = models.TextField(blank=True, null=True)
    object_repr = models.CharField(max_length=200)
    action_flag = models.PositiveSmallIntegerField()
    change_message = models.TextField()
    content_type = models.ForeignKey('DjangoContentType', models.DO_NOTHING, blank=True, null=True)
    user = models.ForeignKey(AuthUser, models.DO_NOTHING)

    class Meta:
        managed = False
        db_table = 'django_admin_log'


class DjangoContentType(models.Model):
    app_label = models.CharField(max_length=100)
    model = models.CharField(max_length=100)

    class Meta:
        managed = False
        db_table = 'django_content_type'
        unique_together = (('app_label', 'model'),)


class DjangoMigrations(models.Model):
    app = models.CharField(max_length=255)
    name = models.CharField(max_length=255)
    applied = models.DateTimeField()

    class Meta:
        managed = False
        db_table = 'django_migrations'


class DjangoSession(models.Model):
    session_key = models.CharField(primary_key=True, max_length=40)
    session_data = models.TextField()
    expire_date = models.DateTimeField()

    class Meta:
        managed = False
        db_table = 'django_session'
