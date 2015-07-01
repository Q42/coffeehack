import requests, json

url = 'http://localhost:3000/api/coffeecups'
data = json.dumps({
    'type': 'latte',
    'timestamp': 1435762371
})
response = requests.post(url, data)
print response.json()
