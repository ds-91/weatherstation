from flask import Flask
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///sensor_data.db'
app.config['JSON_SORT_KEYS'] = False
db = SQLAlchemy(app)

from weatherstation.routes import root
from weatherstation.routes import sensordata