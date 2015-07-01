import requests, json

url = 'http://iot-api.scalingo.io/api/coffeecups'
data = json.dumps({
    'type': 'latte',
    'timestamp': 1435762371
})
response = requests.post(url, data)
print response.json()
