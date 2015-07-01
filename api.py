import urllib2

url = 'http://localhost:3000/api/coffeecups'
response = urllib2.urlopen(url).read()
print response
