import sheller
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/')

def index():
    disc = sheller.run("echo df -h")
    cpu = sheller.run("lscpu")
    
    gpu = sheller.run("nvidia-smi")
    return render_template('index.html', disc=disc, cpu=cpu, gpu=gpu)
@app.route('/ram')

def ram_page():
    ram = sheller.run("echo free -t -h --mega")
    return render_template('ram.html', ram=ram)

if __name__ == '__main__':
    app.run(debug=True)
