from weatherstation import app
from weatherstation.models.sensordata import SensorData
from datetime import datetime
from flask import request, jsonify

import json

@app.route('/add', methods=['POST'])
def add_data():
    data = request.get_json()

    date = datetime.utcnow()
    temperature = data['temperature']
    humidity = data['humidity']

    sensor = SensorData(date, temperature, humidity)
    sensor.save()
    sensor_json = sensor.to_json()

    return sensor_json, 201

@app.route('/all', methods=['GET'])
def get_all_data():
    data = SensorData.find_all()

    return jsonify(data), 200

@app.route('/recent', methods=['GET'])
def get_most_recent_data():
    data = SensorData.get_most_recent()

    if not data:
        return 404

    return jsonify(data), 200