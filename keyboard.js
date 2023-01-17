const { SerialPort } = require('serialport')
const readline = require('readline');
const keyevents = require('key-events')

let keys = keyevents()

const port = new SerialPort({
    path:'COM4',
    baudRate: 9600,
})

readline.emitKeypressEvents(process.stdin);
if (process.stdin.isTTY) process.stdin.setRawMode(true);

process.stdin.on('keypress', (chunk, key) => {
    if(!key) return;
    isMoving = true;
    switch(key.name){
        case 'up':
            return port.write([255,1]); //arriba
        case 'down':
            return port.write([255,4]); //abajo
        case 'left':
            return port.write([255,2]); //izquierda
        case 'right':
            return port.write([255,3]); //derecha
        case 'w' :
            return port.write([255,1]); //arriba
        case 's' :
            return port.write([255,4]); //abajo
        case 'a' :
            return port.write([255,2]); //izquierda
        case 'd' :
            return port.write([255,3]); //derecha
        case 'space':
            return port.write([0,0]);
        case 'q':
            return process.exit();
    } 
});

keys.on('keyup', () => port.write([0,0]))