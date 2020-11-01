from sqlalchemy import Column, Integer, Float, DateTime
from weatherstation import app, db
from datetime import datetime

class SensorData(db.Model):
    id = db.Column(Integer, primary_key=True)
    date = db.Column(DateTime(timezone=False))
    temperature = db.Column(Integer, nullable=False)
    humidity = db.Column(Integer, nullable=False)

    def __init__(self, date, temperature, humidity):
        self.date = date
        self.temperature = temperature
        self.humidity = humidity

    def to_json(self):
        data = {
            'date': self.date,
            'temperature': self.temperature,
            'humidity': self.humidity,
        }

        return data

    def save(self):
        db.session.add(self)
        db.session.commit()

    def find_all():
        query_results = SensorData.query.all()

        all_data = []
        for sensor in query_results:
            date = sensor.date
            date_string = SensorData.convert_date_to_string(date)

            sensor.date = date_string
            all_data.append(sensor.to_json())

        return all_data
    
    def get_most_recent():
        query_results = SensorData.query.order_by(SensorData.date.desc()).first()
        obj = SensorData(query_results.date, query_results.temperature,\
                         query_results.humidity)
        
        return obj.to_json()



    def convert_date_to_string(date):
        return date.strftime('%m/%d/%Y %H:%M:%S')

db.create_all()