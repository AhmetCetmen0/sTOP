import sheller
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/')
def anasayfa():
    ram=sheller.run("free -t -h --mega")
    return render_template('index.html', ram=ram)

if __name__ == '__main__':
    app.run(debug=True)
