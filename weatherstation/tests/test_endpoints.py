# append parent directory (../weatherstation) to python path in order
# to be able for python to find other modules AFTER running.
import sys
sys.path.append('..')

from weatherstation.models.sensordata import SensorData

import unittest
import requests

# python -m unittest discover tests -v
# coverage run --omit ../venv/* -m unittest discover tests -v

class TestApiEndpoints(unittest.TestCase):

    def api_get_request(self, path):
        url = 'http://127.0.0.1:5000/' + path
        res = requests.get(url)

        return res

    def test_root_status_code(self):
        res = self.api_get_request('')

        self.assertEqual(res.status_code, 200)

    def test_get_all_status_code(self):
        res = self.api_get_request('all')

        self.assertEqual(res.status_code, 200)
    
    def test_get_all_json(self):
        res = self.api_get_request('all')

        self.assertIsNotNone(res.json)
    
    def test_add(self):
        temperature = 50.0
        humidity = 100

        url = 'http://127.0.0.1:5000/add'

        sensor_json = {
            "temperature": temperature,
            "humidity": humidity
        }

        res = requests.post(url=url, json=sensor_json)

        self.assertEqual(res.status_code, 201)