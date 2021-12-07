#!/usr/bin/python3

import cgi

form = cgi.FieldStorage()

name  = form.getvalue('name')

print 'HTTP/1.1 200 OK'
print 'Content-Type: text/html\r\n\'
print '<html>'
print '<head>'
print '<title>Webserv</title>'
print '</head>'
print '<body>'
print "<h2>Hello, %s</h2>" % (name)
print '</body>'
print '</html>'
