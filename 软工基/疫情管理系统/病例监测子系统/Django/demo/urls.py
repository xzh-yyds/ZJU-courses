from django.contrib import admin
from django.urls import path
from django.conf.urls import url
from . import views, dbrequest
from django.views.static import serve
from django.conf import settings
from django.conf.urls.static import static

# urlpatterns = [
#     # path('admin/', admin.site.urls),
#     # url(r'^$',views.hello),
#     #url(r'jsons/(?P<path>.*)', serve, {'document_root':settings.MEDIA_ROOT}),
#     path('index',dbrequest.hello),
#     url(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
# ]
urlpatterns = [
    # ... the rest of your URLconf goes here ...

    path('index',dbrequest.hello),
    path('situation',dbrequest.rqst_process),
    path('situation$',dbrequest.rqst_process),
    path('situation/situationMoreInfo',dbrequest.rqst_process),
    path('situation/situationMoreInfo$',dbrequest.rqst_process),
    path('background/Cases',dbrequest.rqst_process),
    path('background/Cases$',dbrequest.rqst_process),
    url(r'^(?P<path>.*)$', serve, {'document_root': ''}),
] #+ static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
