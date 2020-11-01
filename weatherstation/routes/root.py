from weatherstation import app

@app.route('/')
def root():
    return 'root!', 200
