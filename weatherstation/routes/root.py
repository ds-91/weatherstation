from weatherstation import app
from flask import render_template

@app.route('/')
def root():
    return render_template('root.html'), 200
