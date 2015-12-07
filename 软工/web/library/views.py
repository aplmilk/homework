#coding=utf8
from django.shortcuts import render_to_response
from models import Author,book
from django.http import HttpResponse
# Create your views here.

def index(req):
    if req.POST and "Submit" in req.POST:
        post=req.POST
        authorname=post["info"]
        author=Author.objects.filter(Name = authorname)
        if author:
            books=book.objects.filter(AuthorID = author).all()
            return render_to_response("search.html", {"books":books})
        else:
            return render_to_response("searchnone.html", {})
            
    else: 
        lattest=book.objects.all()[:5]
        return render_to_response("index.html", {"lattest":lattest})
    
def addauthor(req):
    if req.POST:
        post = req.POST
        newauthor = Author(
            AuthorID = post["authorID"],
            Name = post["name"],
            Age = post["age"],
            Country = post["country"],)
        newauthor.save() 
        count=Author.objects.all()
        return render_to_response("addsucess.html", {"count":count})
    count=Author.objects.all()
    return render_to_response("addauthor.html", {"count":count})

def addbook(req):
    if req.POST:
        post = req.POST  
        ID=post["AuthorID"]
        author=Author.objects.get(AuthorID = ID)
        if author:            
            newbook = book(
                ISBN = post["ISBN"],
                Title = post["title"],
                AuthorID = author,
                Publisher = post["Publisher"],
                PublishDate = post["publishdate"],
                Price = post["price"],)
            newbook.save()
            count=Author.objects.all()
            return render_to_response("addsucess.html", {"count":count})
    count=Author.objects.all()
    return render_to_response("addbook.html", {"count":count})

def bookinfo(req,i):
    thebook=book.objects.get(ISBN=i)
    theauthor=thebook.AuthorID
    return render_to_response("bookinfo.html", {"book":thebook,"author":theauthor}) 

def readbook(req):
    if req.POST:
        post=req.POST
        if "delete" in post:
            thebook=post["delete"]
            p=book.objects.get(ISBN=thebook)
            p.delete()  
    books=book.objects.all() 
    return render_to_response("books.html", {"books":books}) 

def refreshbook(req,i):
    thebook=book.objects.get(ISBN=i)
    if req.POST:
        post=req.POST
        thebook.Title = post["title"]
        thebook.Publisher = post["Publisher"]
        thebook.PublishDate = post["publishdate"]
        thebook.Price = post["price"]
        thebook.save()
        books=book.objects.all() 
        return render_to_response("books.html", {"books":books}) 
    count=Author.objects.all() 
    return render_to_response("refresh.html", {"count":count,"thebook":thebook}) 