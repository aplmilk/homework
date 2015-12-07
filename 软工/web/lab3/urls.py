from django.conf.urls import patterns, include, url

from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'lab3.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^admin/', include(admin.site.urls)),
    url(r'^index/','library.views.index'),
    url(r'^addauthor/','library.views.addauthor'),
    url(r'^addbook/','library.views.addbook'),
    url(r'^search/','library.views.authorpage'),
    url(r'^bookinfo/(.+)/$','library.views.bookinfo'),
    url(r'^books/','library.views.readbook'),
    url(r'^refresh/(.+)/$','library.views.refreshbook'),
)
