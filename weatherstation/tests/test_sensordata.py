# append parent directory (../weatherstation) to python path in order
# to be able for python to find other modules AFTER running.
import sys
sys.path.append('..')

from weatherstation.models.sensordata import SensorData
from datetime import datetime

import unittest
import requests

# python -m unittest discover tests -v
#coverage run --omit ../venv/* -m unittest discover tests -v

class TestSensorData(unittest.TestCase):
    def create_fake_object(self):
        return SensorData(datetime.utcnow(), 99, 99)

    def test_object_creation(self):
        obj = self.create_fake_object()
        
        self.assertNotEqual(obj, None)
    
    def test_object_to_json(self):
        obj = self.create_fake_object()
        
        j = {'date': datetime.utcnow(), 'temperature': 99, 'humidity': 99}
        
        self.assertAlmostEqual(obj.to_json(), j)

    def test_object_find_all(self):
        data = SensorData.find_all()
        
        self.assertNotEqual(data, None)
