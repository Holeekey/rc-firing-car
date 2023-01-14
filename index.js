const { SerialPort } = require('serialport')

const port = new SerialPort(
    {path:'COM4',
    baudRate: 9600}
)

port.write([255,1])