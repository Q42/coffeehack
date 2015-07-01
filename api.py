import requests, json, time

url = 'http://iot-api.scalingo.io/api/coffeecups'
data = json.dumps({
    'type': 'coffee',
    'timestamp': int(time.time())
})
response = requests.post(url, data)
print response.json()
