from flask import Flask
from flask import render_template
app = Flask(__name__)

@app.route('/')
def index():
    return render_template("index.html")


import threading
sem = threading.Semaphore()
@app.route('/led/<string:cmd>/<string:value>')
def led(cmd, value):
    sem.acquire()
    import serial, time
    s = serial.Serial()
    s.port = 'COM4'    
    s.baudrate = 115200
    s.setDTR(False)
    s.timeout = 1
    s.open()
    cmd_ = "{}{}\n".format(cmd,value).encode()
    print(cmd_, type(cmd_))
    s.write(cmd_)
    time.sleep(1)
    print(s.read(20))
    s.close()
    sem.release()
    return "Ok"

if __name__ == "__main__":
    app.run()