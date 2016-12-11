"""
This bot checks for new posts in r/sudoku every 2 hours and emails the
title and the link to you. Unlike PHP, you have to actually log in with    
an email address...    
If you run this with gmail (you should), you need to turn on pop/imap
and turn off blocked access under lesssecureappssecurity
"""

import praw
import time
import smtplib
import datetime

r = praw.Reddit(user_agent = "I want notifications for new posts to r/sudoku - [your reddit username here]")
subreddit = r.get_subreddit("sudoku")

cache = []

def main():
    print("Checking at: " + str(datetime.datetime.now().time()))
    posts = subreddit.get_new(limit = 1)
    for post in posts:
        if post.id not in cache:
            smtpObj = smtplib.SMTP('smtp.gmail.com', 587)
            smtpObj.ehlo()
            smtpObj.starttls()
            smtpObj.login('your email address here', 'your email password here')
            print("new post, id = " + post.id)
            cache.append(post.id)
            smtpObj.sendmail('your email address here','target email address here', 'Subject: New Post in r/sudoku\n\n' + post.title + "\n" + post.url + '\n')
            smtpObj.quit()
while True:
    main()
    time.sleep(7200)
        #value in seconds, not milliseconds...

