const { SerialPort } = require('serialport')
const readline = require('readline');

let isMoving = false;

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
        case 'q':
            return process.exit();
    } 
    if(key.name == 'q') return process.exit();
    setTimeout(() => {
        isMoving = false;
        setTimeout(() => {
            if(!isMoving) console.log('stop')
        },500)
    }, 1);
});