from sqlalchemy import Column, Integer, Float, DateTime
from weatherstation import app, db
from datetime import datetime

class SensorData(db.Model):
    id = db.Column(Integer, primary_key=True)
    date = db.Column(Integer, nullable=False)
    temperature = db.Column(Integer, nullable=False)
    humidity = db.Column(Integer, nullable=False)
    pressure = db.Column(Integer, nullable=False)
    vibration = db.Column(Integer, nullable=False)

    def __init__(self, date, temperature, humidity, pressure, vibration):
        self.date = date
        self.temperature = temperature
        self.humidity = humidity
        self.pressure = pressure
        self.vibration = vibration

    def to_json(self):
        data = {
            'date': self.date,
            'temperature': self.temperature,
            'humidity': self.humidity,
            'pressure': self.pressure,
            'vibration': self.vibration,
        }

        return data

    def save(self):
        db.session.add(self)
        db.session.commit()

    @staticmethod
    def find_all():
        query_results = SensorData.query.all()

        all_data = []
        for sensor in query_results:
            date = sensor.date
            date_string = SensorData.convert_date_to_string(date)

            sensor.date = date_string
            all_data.append(sensor.to_json())

        return all_data
    
    @staticmethod
    def get_most_recent():
        query_results = SensorData.query.order_by(SensorData.date.desc()).first()
        obj = SensorData(query_results.date, query_results.temperature,\
                         query_results.humidity, query_results.pressure, \
                         query_results.vibration)
        
        return obj.to_json()
    
    @staticmethod
    def get_plot_from_past_6_hours():
        def convert_time(unix):
            from datetime import datetime

            return datetime.utcfromtimestamp(unix).strftime('%H:%M')

        import matplotlib.pyplot as plt
        from collections import defaultdict

        query_results = SensorData.query.order_by(SensorData.date.desc()).limit(90)

        times = []
        temps = []
        humid = []
        for result in query_results:
            times.append(convert_time(result.date))
            temps.append(result.temperature)
            humid.append(result.humidity)
        
        times.reverse()
        temps.reverse()
        humid.reverse()
        
        plt.plot(times, temps, label='temperature', c='r')
        plt.plot(times, humid, label='humidity', c='b')
        plt.xticks(rotation=90, fontsize=6)
        plt.title('Most recent data (6 hours)')
        plt.legend()
        plt.savefig('./static/past_6_hours.png')


    @staticmethod
    def convert_date_to_string(date):
        return date.strftime('%m/%d/%Y %H:%M:%S')

db.create_all()