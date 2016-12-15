from __future__ import print_function
import urllib2
import ssl
import os
import io
import time

sysLoc = os.getcwd()
sysLoc += "\\wikis"
os.mkdir(sysLoc)

def get(url):
    print(url)
    try:
        ssl._create_default_https_context = ssl._create_unverified_context
        response = urllib2.urlopen(url)
    except urllib2.HTTPError:
        time.sleep(60)
        get(url)
    except urllib2.URLError:
        time.sleep(60)
        get(url)    

    return response.read()

def stripSource(source):
    s = ""
    istag = False
    for i, val in enumerate(source):
        if (val == "<"):
            istag = True
        if (val == ">"):
            istag = False
        if(istag == False):
           s += source[i]

    s = s.replace("<", " ").s.replace(">", " ") 
    return s

def saveContent(stringToSave, title, whatAreWeUpTo):
    title = title[0: len(title) - 12]
    #print(title, end = "")
    title = title.replace("\"", "").replace("\\", "").replace("|", "").replace("/", "").replace("*", "").replace("?", "")

    f = open(sysLoc + "\\" + title + ".txt", "w")
    f.write(title + "\n" + stringToSave)

    return whatAreWeUpTo + 1


def getSource(source, urls, whatAreWeUpTo):
    title = ""
    if("<title>" in source and "</title" in source):
        title = source[source.find("<title>") + 7: source.find("</title")]
    else:
        print("something went south in getting the title")
        
    if("</table>" in source):
        if("id=\"See_also\">See also" in source):
            source = source[source.find("</table>"): source.find("id=\"See_also\">See also")]
        elif "id=\"References\"" in source:
            source = source[source.find("</table>"): source.find("id=\"References\"")]
        elif "id=\"Notes\"" in source:
            source = source[source.find("</table>"): source.find("id=\"Notes\"")]
        elif (("id=\"External_links\"") in source):
            source = source[source.find("</table>"): source.find("id=\"External_links\"")]	
        else:
            source = source[source.find("</table>"): source.find("</html>")]
    else:
        if(("id=\"See_also\">See also") in source):
            source = source[source.find("<body"): source.find("id=\"See_also\">See also")]
        elif (("id=\"References\"") in source):
            source = source[source.find("<body"): source.find("id=\"References\"")]
        elif (("id=\"Notes\"") in source):
            source = source[source.find("</body"): source.find("id=\"Notes\"")]	
        elif (("id=\"External_links\"") in source):
            source = source[source.find("<body"): source.find("id=\"External_links\"")]	
        else:
            source = source[source.find("<body"): source.find("</html>")]	

    x = saveContent(stripSource(source), title, whatAreWeUpTo)
    url = "";
    while("href" in source):
        source = source[source.find("href=\"") + 7:]
        url = "https://en.wikipedia.org/" + source[0: source.find('"')]
        loc = url.lower()
         
        if not loc in urls and not url in urls and "/wiki/" in loc and not "-footnote" in loc and not "org/ttps" in loc and not "file:" in loc and not "#" in loc and not ":" in url[30:].lower():
            urls.insert(len(urls) - 1, url)
	    
    return x

def main():
    start = 0
    whatAreWeUpTo = 0
    urls = list()
    urls.insert(whatAreWeUpTo, "https://en.wikipedia.org/wiki/George_Mason")
    while(True):
        print (whatAreWeUpTo, end = "")
        print(": ", end = "")
        if(whatAreWeUpTo % 500 == 0):
            print (time.time() - start)
            start = time.time()
            
        whatAreWeUpTo = getSource(get(urls[whatAreWeUpTo]), urls, whatAreWeUpTo)
        
        
main()







